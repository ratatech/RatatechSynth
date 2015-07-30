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
ADSREnv envObj;

int16_t data;
int32_t data_acc;
uint16_t u_data;
uint16_t out_sample;
int16_t envt;
double env=0;
bool status = true;
int a = 0;
double randNumA = 0;
double randNumB = 0;

int main(void)
	{

	// Configure oscillator

	osc_shape shape = SIN;
	osc.setOscShape(shape);
	osc.setFreqFrac(1000);


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


	}


}



inline void fill_buffer(void)
{

	while(out_buffer.check_status()){


		// Get a new oscillator sample
		switch (osc.shape)
		{
			case SIN:
				envObj.updateEnv();
				data = osc.computeSine();
				trace_printf("data val = %i\n",data);
				envt = envObj.adsrAmp;
				data_acc = ((int32_t)(data)*(envt)>>15);
				trace_printf("data val env = %i\n",data_acc);
				u_data = int16_2_uint16(data_acc);
				trace_printf("u_data val = %i\n",u_data>>8);
				u_data>>=4;
				//data = (uint16_t)(data*env);
				status = out_buffer.write(u_data);
				break;

			case SQU:
				data = osc.computeSquare();
				trace_printf("data val = %i\n",data);
				u_data = int16_2_uint16(data);
 				trace_printf("u_data val = %i\n",u_data);
				u_data>>=4;
				//data = (uint16_t)(data*env);
				status = out_buffer.write(u_data);
				break;
			case SAW:
				data = osc.computeSaw();
				//trace_printf("data val = %i\n",data);
				u_data = int16_2_uint16(data);
//				trace_printf("u_data val = %i\n",u_data);
				u_data>>=4;
				//data = (uint16_t)(data*env);
				status = out_buffer.write(u_data);
				break;
			case TRI:
				data = osc.computeTriangle();
				trace_printf("data val = %i\n",data>>8);
				u_data = int16_2_uint16(data<<8);
				trace_printf("u_data val = %i\n",u_data>>8);
				u_data>>=4;
				trace_printf("u_data val_12 = %i\n",u_data);
				//data = (uint16_t)(data*env);
				status = out_buffer.write(u_data);
				break;
		}
	}
	a = 0;
	//trace_printf("WRITED\n");
	//GPIOC->ODR ^= GPIO_Pin_7;
}

extern "C" {

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	//TimingDelay_Decrement();

}


void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);


		//Trigger ADSR
//		randNumA = (double)(random()/(RANDOM_MAX/1024))+5;
//		randNumB = (double)(random()/(RANDOM_MAX/1024))+5;
		//
		//
		envObj.attack =0.1;
		envObj.decay = 0.1;
		envObj.calcAdsrSteps();
		GPIOC->ODR ^= GPIO_Pin_7;

		envObj.adsr_st = ATTACK_STATE;


	}


}

void TIM1_UP_IRQHandler(void)
{

	//trace_printf("READ\n");
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{

		status = out_buffer.read(&out_sample);
		audio_out_write(out_sample);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	}


}

}

/**
* @}
*/
// ----------------------------------------------------------------------------
