/*
@file soundGen.cc

@brief Main sound generation tasks

@ Created by Jordi Hidalgo, Ratatech, Oct 9, 2018
This file is part of Ratatech 3019.

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/

#include "soundGen.h"
#include "hsm/soundGenHSM.h"
#include "qep.h"

static Oscillator osc;
static q15_t out_sample;
q15_t pOut[FRAME_SIZE];
uint32_t cycles; // number of cycles //

/** Instance of CircularBuffer **/
CircularBuffer* out_buff = CircularBuffer::getInstance();

/**
 * @brief Start the sound generator
 */
void soundGenStart(void){

	/** Unique instance of SynthSettings **/
	SynthSettings* s = SynthSettings::getInstance();

	/** Init output buffer */
	out_buff->init();

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Configure oscillator*/
	osc.set_shape(SIN);

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_EnableCycleCounter(); 			// start counting
}

/**
 * @brief Fill the main buffer containing the output audio samples
 * @param synth_params	Synth global structure
 */
void fillBuffer(void)
{
	if(out_buff->hasFrameFree()){

		GPIOA->ODR ^= GPIO_Pin_12;
		/** Sound generation */
		osc.get_frame(pOut, FRAME_SIZE);

		/** Fill the output buffer with fresh frames */
		out_buff->write_frame(pOut);
	}
}

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{
	QK_ISR_ENTRY();
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		out_buff->read(&out_sample);
		audio_out_write(int16_2_uint16(out_sample));
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
	QK_ISR_EXIT();

}


