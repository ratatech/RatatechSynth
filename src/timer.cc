/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 3, 2015
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

#include "timer.h"
#include "diag/Trace.h"


void timer_Config(void)
{
	extern TIM_HandleTypeDef    TimHandle;

	/* Prescaler declaration */
	uint32_t uwPrescalerValue = 0;




	/*##-1- Configure the TIM peripheral #######################################*/
	/* -----------------------------------------------------------------------
	In this example TIM3 input clock (TIM3CLK)  is set to APB1 clock (PCLK1) x2,
	since APB1 prescaler is set to 4 (0x100).
	   TIM3CLK = PCLK1*2
	   PCLK1   = HCLK/2
	=> TIM3CLK = PCLK1*2 = (HCLK/2)*2 = HCLK = SystemCoreClock
	To get TIM3 counter clock at 10 KHz, the Prescaler is computed as following:
	Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	Prescaler = (SystemCoreClock /10 KHz) - 1

	Note:
	 SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f1xx.c file.
	 Each time the core clock (HCLK) changes, user had to update SystemCoreClock
	 variable value. Otherwise, any configuration based on this variable will be incorrect.
	 This variable is updated in three ways:
	  1) by calling CMSIS function SystemCoreClockUpdate()
	  2) by calling HAL API function HAL_RCC_GetSysClockFreq()
	  3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
	----------------------------------------------------------------------- */

	/* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */
	uwPrescalerValue = (uint32_t)(SystemCoreClock / 10000) - 1;

	/* Set TIMx instance */
	TimHandle.Instance = TIMx;

	/* Initialize TIMx peripheral as follows:
	   + Period = 10000 - 1
	   + Prescaler = (SystemCoreClock/10000) - 1
	   + ClockDivision = 0
	   + Counter direction = Up
	*/
	TimHandle.Init.Period            = 10000 - 1;
	TimHandle.Init.Prescaler         = uwPrescalerValue;
	TimHandle.Init.ClockDivision     = 0;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;


}

