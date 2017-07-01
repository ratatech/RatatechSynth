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
Oscillator 		osc;
LFO 				lfo;
CircularBuffer		out_buffer;
MIDI 				midi;
SoundGenerator 	snd_gen;
ADSR				adsr;
Mux					mux;

/** Pointer to main output frame buffer  **/
q15_t pOut[FRAME_SIZE];

/** ADSR out pointer*/
q15_t* pAdsr;

/** LFO out pointer*/
q15_t* pLfo;


/** Sample to be written in the DAC */
uint16_t out_sample;

/** Output buffer status */
bool status = true;



int main(void)
{

	/** Init system and peripherals */
	ratatech_init();

	/** Put objects in the pool */
	object_pool.osc = 			&osc;
	object_pool.lfo = 			&lfo;
	object_pool.out_buffer = 	&out_buffer;
	object_pool.midi = 			&midi;
	object_pool.adsr = 			&adsr;
	object_pool.mux = 			&mux;

	/** Link ADSR and LFO pointers to the global structure */
	pAdsr = &synth_params.adsr_vol_amp;
	pLfo  = &synth_params.lfo_amp;

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(1000);
	osc.set_shape(TRI);

	/** Init adsr */
	adsr.init(&synth_params);

	/** Configure lfo */
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(50);

	/** Pre-fill the output buffer */
	fill_buffer();

	/*******************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{
		/** Fill audio buffer with a new sample */
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){

	/** Update midi information */
	midi.update(&synth_params);

	/** Read inputs */
	mux.update(&synth_params,synth_params.pMux);

	/** Compute a new LFO envelope frame/sample */
	lfo.get_frame(&synth_params,pLfo,LFO_BLOCK_SIZE);

	/** Compute a new ADSR envelope frame/sample */
	adsr.get_frame(&synth_params,pAdsr,ADSR_BLOCK_SIZE);

	/** Check if a new midi message has arrived */
	if(midi.attack_trigger){

		/** If a new note is received reset ADSR */
		adsr.reset();

		/** Remove attack setting flag */
		midi.attack_trigger = false;

		/** Set OSC freq from the MIDI table */
		osc.set_freq_frac(midi_freq_lut[synth_params.pitch]);
	}
	iprintf("putaaaaa");
	//iprintf("x0=%i\n",synth_params.pMux[0]);
}

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{

	/** Sound generation */
	snd_gen.gen_voice(&synth_params, pOut);

	/** Fill the output buffer with fresh frames*/
	status = out_buffer.write_frame(pOut);
}

/**
 * Read a sample of the output buffer and write it to the DAC @AUDIO FS
 */
void audio_gen(void){

	out_buffer.read(&out_sample);
	audio_out_write(out_sample);
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
