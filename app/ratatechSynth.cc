/*
 @file ratatechSynth.cc


 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
 This file is part of XXXXXXX

 XXXXXXX is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 XXXXXXX is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
 */

#include "ratatechSynth.h"

using namespace std;

/** Parameter structures */
synth_params_t synth_params;
object_pool_t object_pool;

/** Make a local copy of the object instances */
Oscillator 		osc1,osc2;
LFO 				lfo;
CircularBuffer	out_buffer;
MIDI 				midi;
SoundGenerator 	snd_gen;
ADSR				adsr;
Mux					mux;
Svf 				svf;

/** Pointer to main output frame buffer  **/
q15_t pOut[FRAME_SIZE];

/** Sample to be written in the DAC */
q15_t out_sample;

/** Output buffer status */
bool status = true;

uint16_t* pAdc;


uint32_t cycles; // number of cycles //


volatile size_t frame_read_n;
volatile size_t frame_write_n;

int main(void)
{

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_ResetCycleCounter(); 			// reset cycle counter
	KIN1_EnableCycleCounter(); 			// start counting

	/** Put objects in the pool */
	object_pool.osc1 = 			&osc1;
	object_pool.osc2 = 			&osc2;
	object_pool.lfo = 			&lfo;
	object_pool.out_buffer = 	&out_buffer;
	object_pool.midi = 			&midi;
	object_pool.adsr = 			&adsr;
	object_pool.mux = 			&mux;
	object_pool.svf =			&svf;

	/** Link output frame ponter to global structure */
	synth_params.pOut = &pOut[0];

	synth_params.lfo_amp = &lfo.lfo_amp;

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Init oscillator with default settings */
	osc1.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc1.set_freq_frac(1000);
	osc1.set_shape(SAW);


	/** Init oscillator with default settings */
	osc2.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc2.set_freq_frac(2000);
	osc2.set_shape(SQU);

	/** Init adsr */
	adsr.init(&synth_params);

	/** Configure lfo */
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(50);

	/** Init SVF filter params*/
	svf.init(&synth_params);

	/** Pre-fill the output buffer */
	fill_buffer();

	/*******************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

		/** Fill audio buffer with a new sample */
		//low_rate_tasks();
		if(out_buffer.frame_read != out_buffer.frame_write){
			fill_buffer();
		}

		// Add a couple of cycles delay between main loop
	    __asm__("nop");
	    __asm__("nop");

	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){

	/** Read inputs */
	mux.update(&synth_params,synth_params.pMux);
	svf.set_fc(&synth_params);
	svf.set_q(&synth_params);
	adsr.set_params(&synth_params);
	lfo.set_freq_frac((double)((synth_params.pMux[5]*200)>>12));

}

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{

	/** Update midi information */
	midi.update(&synth_params);


	/** Check if a new midi message has arrived */
	if(midi.attack_trigger){

		/** If a new note is received reset ADSR */
		adsr.reset();

		/** Remove attack setting flag */
		midi.attack_trigger = false;

		/** Set OSC freq from the MIDI table */
		osc1.set_freq_midi(synth_params.pitch);

		/** Set OSC freq from the MIDI table */
		osc2.set_freq_midi(synth_params.pitch+4);

	}

#if DEBUG_ADC
	//printf("ADSR STATE = %i ADSR S_LVL = %i ADSR LVL = %i\r",adsr.adsr_state,adsr.sustain_level,synth_params.adsr_vol_amp);
#endif



	/** Sound generation */
	snd_gen.gen_voice(&synth_params, pOut);

    /** Wait DMA transfer to be complete*/
	while(!out_buffer.dma_transfer_complete);

	/** Fill the output buffer with fresh frames*/
	status = out_buffer.write_frame_dma(pOut);



}

/**
 * Read a sample of the output buffer and write it to the DAC @AUDIO FS
 */
void audio_gen(void){
	out_buffer.read(&out_sample);
	audio_out_write(int16_2_uint16(out_sample));
}

/*****************************************************************************************************************************
******************* TIMER INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		audio_gen();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}

}

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		low_rate_tasks();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}


}


/*****************************************************************************************************************************
******************* USART INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
* USART1 interrupt handler
*/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
    	uint16_t midi_in = USART_ReceiveData(USART1);
    	midi.parseMsg(midi_in);
    }

    /** ------------------------------------------------------------ */
    /** Other USART1 interrupts handler can go here ...             */
}


/*****************************************************************************************************************************
******************* DMA INTERRUPTS *******************************************************************************************
******************************************************************************************************************************/
void DMA1_Channel2_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA1_IT_TC2))
  {
    out_buffer.dma_transfer_complete = true;
    DMA_ClearITPendingBit(DMA1_IT_GL2);
  }
}

