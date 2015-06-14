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
static __IO uint32_t TimingDelay;
uint8_t __IO BlinkSpeed = 0;
/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{


	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	//SystemClock_Config();

	/* Initialize GPIO */
    GPIO_Conf_Init();




  /* Initiate Blink Speed variable */
  BlinkSpeed = 0;

  /* Infinite loop */
  while (1)
  {
    /* Test on blink speed */
    if(BlinkSpeed == 0)
    {
      /*LED2 Toggle each 50ms*/
    	GPIOA->ODR ^= GPIO_Pin_5;
      Delay(50);
    }
    else if(BlinkSpeed == 1)
    {
		GPIOA->ODR ^= GPIO_Pin_5;
      /*LED2 Toggle each 200ms */
      Delay(200);
    }
  }
}

/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}



/**
* @}
*/
// ----------------------------------------------------------------------------
