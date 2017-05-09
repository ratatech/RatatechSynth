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


// Object instances
Oscillator osc1,osc2;
CircularBuffer out_buffer;

// Structure instances
synth_params_t synth_params;
uint16_t u_data;
uint16_t out_sample;
bool low_rate_ISR_flag = false;





int main(void)
	{

	// Init system and peripherals
	ratatech_init();

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SIN;
	osc1.set_shape(shape_osc1);
	osc1.set_freq_frac(1000);


	//Pre-fill the output buffer
	fill_buffer();

	/* *****************************************************************************************
	 * Main Loop
	 *
	 * *****************************************************************************************/
	while(1)
	{

//		// Events happening every CONTROL_RATE
//		if(low_rate_ISR_flag){
//			low_rate_tasks();
//		}

		// Fill audio buffer with a new sample
		fill_buffer();
	}

}

/**
 * Execute all tasks running at CONTROL_RATE
 */
void low_rate_tasks(void){

}

/**
 * Fill the main buffer containing the output audio samples
 *
 * @param void
 * @return void
 */
inline void fill_buffer(void)
{
	int32_t sample_osc1, sample_osc2, osc_mix;

	/* *****************************************************************************************
	 * AUDIO CHAIN START
	 *
	 * *****************************************************************************************/

		/** 1 - Oscillator 1 */
		sample_osc1 =  osc1.get_sample(&synth_params);

		/** Fill output buffer */
		out_buffer.write(int16_2_uint16(sample_osc1));

}

/** Read if a buton is active or not
 *
 * @param Buttton_port Selected port
 * @param Buttton  Button number
 * @return void
 */
uint32_t ButtonRead(GPIO_TypeDef* Button_Port, uint16_t Button)
{
  return !GPIO_ReadInputDataBit(Button_Port, Button);
}

extern "C" {

/*****************************************************************************************************************************
******************* TIMER INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{

		low_rate_ISR_flag = true;
		//Do something here

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}


}

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void)
{

	//trace_printf("READ\n");
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{

		out_buffer.read(&out_sample);
		audio_out_write(out_sample);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	}


}

}

/*****************************************************************************************************************************
******************* USART INTERRUPTS *****************************************************************************************
******************************************************************************************************************************/


