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

uint16_t counter = 0;
uint8_t counterHigh = 0;
uint8_t counterLow = 0;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	GPIO_Conf_Init();
	SPI_Config();
	TIM_Config();


	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);


	/* Infinite loop */
	while(1)
	{
	}


}
void SPI_Callback(void)
{
	GPIOC->ODR ^= GPIO_Pin_7;
	counter+=20;
	counter%=4095;
	counterHigh = 0b00110000 | counter>>8;
	counterLow  = 0x00FF & counter;
//	trace_printf("counter = %i\n",counter);
//	trace_printf("counterHigh = %i\n",counterHigh);
//	trace_printf("counterLow  = %i\n",counterLow);
//	trace_printf("\n");
	GPIOA->BRR = GPIO_Pin_9;
	SPI_send(counterHigh);
	SPI_send(counterLow);

//	trace_printf("SPI1-DR = %i\n",SPI_send(63));
//	trace_printf("SPI1-DR = %i\n\n",SPI_send(205));
	GPIOA->BSRR = GPIO_Pin_9;

}
/**
* @}
*/
// ----------------------------------------------------------------------------
