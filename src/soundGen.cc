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

static CircularBuffer out_buffer;
static Oscillator osc;
static q15_t out_sample;
q15_t pOut[FRAME_SIZE];


static uint8_t const l_Fb_IRQHandler = 0U;
uint32_t cycles; // number of cycles //

/**
 * @brief Start the sound generator
 */
void soundGenStart(void){

	/** Unique instance of SynthSettings **/
	SynthSettings* s = SynthSettings::getInstance();

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Configure oscillator*/
	osc.set_shape(SQU);

	KIN1_InitCycleCounter(); 			// enable DWT hardware
	KIN1_EnableCycleCounter(); 			// start counting
}

/**
 * @brief Fill the main buffer containing the output audio samples
 * @param synth_params	Synth global structure
 */
void fillBuffer(void)
{

	if(out_buffer.frame_read != out_buffer.frame_write){

		/** Sound generation */
		osc.get_frame(pOut, FRAME_SIZE);

		/** Fill the output buffer with fresh frames */
		out_buffer.write_frame(pOut);

	}

}

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		QK_ISR_ENTRY();
		if(!(out_buffer.start % FRAME_SIZE)){
			GPIOA->ODR ^= GPIO_Pin_12;

			FillFrameEvt *pFfeEvt = Q_NEW(FillFrameEvt, FILL_FRAME_SIG);
			AO_SoundGenHSM->POST(pFfeEvt,&l_Fb_IRQHandler);

		}
		QK_ISR_EXIT();

		GPIOA->ODR ^= GPIO_Pin_9;
		out_buffer.read(&out_sample);
		audio_out_write(int16_2_uint16(out_sample));


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
		GPIOA->ODR ^= GPIO_Pin_12;
		QK_ISR_ENTRY();
		FillFrameEvt *pFfe = Q_NEW(FillFrameEvt, FILL_FRAME_SIG);
		AO_SoundGenHSM->POST(pFfe,&l_Fb_IRQHandler);
		QK_ISR_EXIT();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

