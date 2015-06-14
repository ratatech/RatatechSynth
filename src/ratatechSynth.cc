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



#define LEDToggleValue ((uint16_t) 3000)

GPIO_InitTypeDef LEDs;


int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	GPIO_Conf_Init();
	TIM_Config();
	TIM_Init();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);




	uint16_t CurrentTimerVal = 0;

	/* Infinite loop */
	while(1)
	{
	}


}


/**
* @}
*/
// ----------------------------------------------------------------------------
