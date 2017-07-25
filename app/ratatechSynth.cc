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

#define RATATECH_PROFILING

#ifdef RATATECH_PROFILING

/* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
  #define KIN1_DWT_CONTROL             (*((volatile uint32_t*)0xE0001000))
    /*!< DWT Control register */
  #define KIN1_DWT_CYCCNTENA_BIT       (1UL<<0)
    /*!< CYCCNTENA bit in DWT_CONTROL register */
  #define KIN1_DWT_CYCCNT              (*((volatile uint32_t*)0xE0001004))
    /*!< DWT Cycle Counter register */
  #define KIN1_DEMCR                   (*((volatile uint32_t*)0xE000EDFC))
    /*!< DEMCR: Debug Exception and Monitor Control Register */
  #define KIN1_TRCENA_BIT              (1UL<<24)
    /*!< Trace enable bit in DEMCR register */

#define KIN1_InitCycleCounter() \
  KIN1_DEMCR |= KIN1_TRCENA_BIT
  /*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */

#define KIN1_ResetCycleCounter() \
  KIN1_DWT_CYCCNT = 0
  /*!< Reset cycle counter */

#define KIN1_EnableCycleCounter() \
  KIN1_DWT_CONTROL |= KIN1_DWT_CYCCNTENA_BIT
  /*!< Enable cycle counter */

#define KIN1_DisableCycleCounter() \
  KIN1_DWT_CONTROL &= ~KIN1_DWT_CYCCNTENA_BIT
  /*!< Disable cycle counter */

#define KIN1_GetCycleCounter() \
  KIN1_DWT_CYCCNT
  /*!< Read cycle counter register */

/** Usage :


	uint32_t cycles; // number of cycles //

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_ResetCycleCounter(); 			// reset cycle counter
	KIN1_EnableCycleCounter(); 			// start counting
	foo(); 								// call function and count cycles
	cycles = KIN1_GetCycleCounter(); 	// get cycle counter
	KIN1_DisableCycleCounter(); 		// disable counting if not used any more

*/

#endif

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
Svf 				svf;

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

uint16_t* pAdc;

int main(void)
{


	/** Put objects in the pool */
	object_pool.osc = 			&osc;
	object_pool.lfo = 			&lfo;
	object_pool.out_buffer = 	&out_buffer;
	object_pool.midi = 			&midi;
	object_pool.adsr = 			&adsr;
	object_pool.mux = 			&mux;
	object_pool.svf =			&svf;

	/** Link ADSR and LFO pointers to the global structure */
	pAdsr = &synth_params.adsr_vol_amp;
	pLfo  = &synth_params.lfo_amp;
	pAdc  = &synth_params.adc_read;


	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(100);
	osc.set_shape(SAW);

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
		fill_buffer();

	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){
	//iprintf("ALIVE!\r");
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

	/** Read inputs */
	mux.update(&synth_params,synth_params.pMux);

	svf.set_fc(&synth_params);
	svf.set_q(&synth_params);
	adsr.set_params(&synth_params);

	/** Check if a new midi message has arrived */
	if(midi.attack_trigger){

		/** If a new note is received reset ADSR */
		adsr.reset();

		/** Remove attack setting flag */
		midi.attack_trigger = false;

		/** Set OSC freq from the MIDI table */
		osc.set_freq_midi(synth_params.pitch);

	}
	//printf("ADSR STATE = %i ADSR S_LVL = %i ADSR LVL = %i\r",adsr.adsr_state,adsr.sustain_level,synth_params.adsr_vol_amp);

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
		//low_rate_tasks();
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



