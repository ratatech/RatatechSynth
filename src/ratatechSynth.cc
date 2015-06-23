//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "ratatechSynth.h"

/** @addtogroup IO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static __IO uint32_t TimingDelay;
//uint8_t __IO BlinkSpeed = 0;
///* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
///* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */


using namespace std;



Oscillator osc;




int main(void)
{

	osc.setFreqFrac(440);
	osc.setOscShape(0);

	SystemInit();




	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	GPIO_Conf_Init();
	SPI_Config();
	TIM_Config();






	/* Infinite loop */
	while(1)
	{
	}


}

extern "C" {

void TIM2_IRQHandler(void)
{
	uint8_t timerValue = TIM_GetCounter(TIM2);
	trace_printf("timerCounter val = %i\n",timerValue);
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		/* Whatever */

		//audio_out_Callback(&osc);
	}


}

void TIM1_UP_IRQHandler(void)
{
//	uint8_t timerValue = TIM_GetCounter(TIM2);
//	trace_printf("timerCounter val = %i\n",timerValue);
	if (TIM_GetITStatus(TIM1, TIM_IT_Update))
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

		/* Whatever */

		audio_out_Callback(&osc);
	}


}

}

/**
* @}
*/
// ----------------------------------------------------------------------------
