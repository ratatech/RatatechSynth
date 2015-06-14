/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 31, 2015
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

#include "system_init.h"


void SystemClock_Config(void)
{

//	RCC
//	  RCC_ClkInitTypeDef clkinitstruct = {0};
//	  RCC_OscInitTypeDef oscinitstruct = {0};
//
//	  /* Configure PLL ------------------------------------------------------*/
//	  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
//	  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
//	  /* Enable HSI and activate PLL with HSi_DIV2 as source */
//	  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
//	  oscinitstruct.HSEState        = RCC_HSE_OFF;
//	  oscinitstruct.LSEState        = RCC_LSE_OFF;
//	  oscinitstruct.HSIState        = RCC_HSI_ON;
//	  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
//	  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
//	  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
//	  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
//	  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;
//	  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
//	  {
//	    /* Initialization Error */
//	    while(1);
//	  }
//
//	  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
//	     clocks dividers */
//	  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//	  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
//	  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
//	  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)
//	  {
//	    /* Initialization Error */
//	    while(1);
//	  }

}
/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED2
  * @retval None
  */
void GPIO_Conf_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Enable the GPIO Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/* Configure the GPIO pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


}



