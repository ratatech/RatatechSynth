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

uint8_t sinetable[256] = {
  128,131,134,137,140,143,146,149,152,156,159,162,165,168,171,174,
  176,179,182,185,188,191,193,196,199,201,204,206,209,211,213,216,
  218,220,222,224,226,228,230,232,234,236,237,239,240,242,243,245,
  246,247,248,249,250,251,252,252,253,254,254,255,255,255,255,255,
  255,255,255,255,255,255,254,254,253,252,252,251,250,249,248,247,
  246,245,243,242,240,239,237,236,234,232,230,228,226,224,222,220,
  218,216,213,211,209,206,204,201,199,196,193,191,188,185,182,179,
  176,174,171,168,165,162,159,156,152,149,146,143,140,137,134,131,
  128,124,121,118,115,112,109,106,103,99, 96, 93, 90, 87, 84, 81,
  79, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39,
  37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10,
  9,  8,  7,  6,  5,  4,  3,  3,  2,  1,  1,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  1,  1,  2,  3,  3,  4,  5,  6,  7,  8,
  9,  10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35,
  37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76,
  79, 81, 84, 87, 90, 93, 96, 99, 103,106,109,112,115,118,121,124
};

#define LEDToggleValue ((uint16_t) 3000)

GPIO_InitTypeDef LEDs;

uint16_t counter = 0;
uint16_t data = 0;
uint8_t counterHigh = 0;
uint8_t counterLow = 0;
int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	RCC_Clocks_Init();
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
	//GPIOC->ODR ^= GPIO_Pin_7;
	counter+=1;
	counter%=256;
	data = sinetable[counter]<<4;
	counterHigh = 0b00110000 | data>>8;
	counterLow  = 0x00FF & data;
//	trace_printf("counter = %i\n",data);
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
