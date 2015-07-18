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



RCC_ClocksTypeDef RCC_Clocks;


/**
  * @brief   Main program
  * @param  None
  * @retval None
  */


using namespace std;



Oscillator osc;
CircularBuffer out_buffer;
uint16_t data;
uint16_t out_sample;
bool status = true;
int a = 0;

int main(void)
{

	// Configure oscillator

	osc_shape shape = TRI;
	osc.setOscShape(shape);
	osc.setFreqFrac(10000);


	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    // COnfigure and init peripherals
	GPIO_Conf_Init();
	SPI_Config();
	fill_buffer();
	TIM_Config();


	/* Infinite loop */
	while(1)
	{
		//trace_printf("MAIN a = %i\n",a);
		fill_buffer();
//		GPIOC->ODR ^= GPIO_Pin_7;
	}


}


inline void fill_buffer(void)
{

	while(out_buffer.check_status()){


		// Get a new oscillator sample
		switch (osc.shape)
		{
			case SIN:
				data = osc.computeSine();
				data>>=4;
				status = out_buffer.write(data);
				break;
			case SQU:
				data = osc.computeSquare();
				data<<=4;
				status = out_buffer.write(data);
				break;
			case SAW:
				data = osc.computeSaw();
				data<<=4;
				status = out_buffer.write(data);
				break;
			case TRI:
				data = osc.computeTriangle();
				data<<=4;
				status = out_buffer.write(data);
				break;
		}
	}
	a = 0;
	//trace_printf("WRITED\n");
	//GPIOC->ODR ^= GPIO_Pin_7;
}

extern "C" {

//void TIM2_IRQHandler(void)
//{
//	uint8_t timerValue = TIM_GetCounter(TIM2);
//	//trace_printf("timerCounter val = %i\n",timerValue);
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//
//		/* Whatever */
//
//		//audio_out_Callback(&osc);
//	}
//
//
//}

void TIM1_UP_IRQHandler(void)
{

	//trace_printf("READ\n");
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{

		status = out_buffer.read(&out_sample);
		data = out_sample;
		audio_out_Callback(data);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	}


}

}

/**
* @}
*/
// ----------------------------------------------------------------------------
