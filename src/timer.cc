/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 3, 2015
This file is part of Ratatech 3019

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/

#include "timer.h"
#include "diag/Trace.h"


void TIM_Config(void)
{

#ifndef LOCAL_TIMER_CFG

	TIM_TimeBaseInitTypeDef timerInitStructure;
	TIM_OCInitTypeDef timeOCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);    //4 bits for preemp priority 0 bit for sub priority

	//*************************************************************************************
	/* PWM Timer1 configuration*/
	//*************************************************************************************
#ifdef USE_AUDIO_TIMER

	/* TIM1 configuration
	 * Timer 1 configured to work with an output audio sampling
	 * frequency of FS */

	/* TIM1 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/*
	 * 	Prescaler = ((((ClockSpeed) / ((period) / (1 / frequency))) + 0.5) - 1)
	 *
	 * 	Parameters to configure timer at 1hz ie. every 1s:
	 *	timerInitStructure.TIM_Period    = 32768;
	 *	timerInitStructure.TIM_Prescaler = 2197; */
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = SystemCoreClock/FS;
	timerInitStructure.TIM_Prescaler = 0;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &timerInitStructure);

#if 0
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
#endif

#endif

#ifdef USE_LOW_RATE_TIMER

	//*************************************************************************************
	/* PWM Timer2 configuration*/
	//*************************************************************************************

	/* TIM2 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 configuration
	 * Timer 2 configured to work with slow speed tasks like envelope update,lfo etc...*/
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 1000;
	timerInitStructure.TIM_Prescaler = 47;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);

#if 0
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
#endif
#endif

#ifdef USE_PWM_TIMER

	//*************************************************************************************
	/* PWM Timer3 configuration*/
	//*************************************************************************************
	/*
	 * PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
	*/
	TIM_TimeBaseStructInit( &timerInitStructure );
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = PWM_PERIOD;   // 0..999
	timerInitStructure.TIM_Prescaler = 0; // Div 240
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	/* TIM3 Main Output Enable */

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd( TIM3, ENABLE );


	TIM_OCStructInit( &timeOCInitStructure );
	timeOCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	timeOCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	timeOCInitStructure.TIM_Pulse = 0;
	timeOCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init( TIM3, &timeOCInitStructure );
    TIM_OC2Init( TIM3, &timeOCInitStructure );
    TIM_OC3Init( TIM3, &timeOCInitStructure );
    TIM_OC4Init( TIM3, &timeOCInitStructure );

	/* TIM3 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#endif

#endif


}

