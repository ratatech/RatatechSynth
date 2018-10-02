/*
@file pwm_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
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

#include <stdio.h>
#include "unity.h"
#include "drv/mux.h"
#include "drv/macro_mux.h"
#include "drv/adc_mux.h"
#include "tst_utils.h"
#include "system_init.h"
#include "pwm_tst.h"
#include "dither_generator.h"

#define MAX_SHIFT 16
#define PWM_BITS 7
#define PWM_TEST_PERIOD 1 << PWM_BITS
#define HI_RES_BITS (PWM_BITS + DITHER_BITS)
#define WAVETABLE_SCL (16 - HI_RES_BITS)

/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/** Dither generator objects */
DitherGen ditherGenA,ditherGenB,ditherGenC,ditherGenD;

/** Diether variables */
uint8_t lutInd			= 0;
uint32_t duCyValHigRes 	= 0;
uint32_t duCyValLowRes 	= 0;

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		duCyValHigRes = int16_2_uint16(sin_lut_q15[lutInd])>>WAVETABLE_SCL;
		ditherGenA.updatePattern(duCyValHigRes);
		ditherGenB.updatePattern(duCyValHigRes>>1);
		ditherGenC.updatePattern(duCyValHigRes>>2);
		ditherGenD.updatePattern(duCyValHigRes>>3);
		duCyValLowRes = duCyValHigRes>>DITHER_BITS;
		lutInd++;
		lutInd%=LUT_8_BIT;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

/**
  * @brief  This function handles Timer 3Handler.
  */
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{
		ditherGenA.setDuCy1(duCyValLowRes,TIM3);
		ditherGenB.setDuCy2(duCyValLowRes>>1,TIM3);
		ditherGenC.setDuCy3(duCyValLowRes>>2,TIM3);
		ditherGenD.setDuCy4(duCyValLowRes>>3,TIM3);
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

static void timer_cfg(void){

	TIM_TimeBaseInitTypeDef timerInitStructure;
	TIM_OCInitTypeDef timeOCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//*************************************************************************************
	/* PWM Timer2 configuration*/
	//*************************************************************************************

	/* TIM2 NVIC configuration */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM2 configuration
	 * Timer 2 configured to work with slow speed tasks like envelope update,lfo etc...*/
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 32768>>10;
	timerInitStructure.TIM_Prescaler = 2197>>1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	//*************************************************************************************
	/* PWM Timer3 configuration*/
	//*************************************************************************************
	/*
	 * PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
	*/
	TIM_TimeBaseStructInit( &timerInitStructure );
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = PWM_TEST_PERIOD;   // 0..999
	timerInitStructure.TIM_Prescaler = 0; // Div 240
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);
	/* TIM3 Main Output Enable */

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

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd( TIM3, ENABLE );

}

/**
 * PWM test
 *
 * The idea of this test is to verify how the resolution of the PWM generated signal is improved
 * by using dithering. As example, we start by using a PWM generated sine wave by means of a wavetable.
 * The PWM frequency is set to 4 bits only intentionally to better observe later the low resolution
 * stair like signal when dithering is not enabled. By enabling the dithering, 4 additional bits are
 * added to the output signal, generating a much more smooth response. This thest requires additional
 * HW setup in order to LPF the output PWM signal. A single pole RC filter is used with values C=1uF,
 * R=560 providing a rough fc of 284Hz.
 *
 *   _____________________________
 * |                            |
 * |                            |
 * |                            |
 * |                            |     __R___
 * |     STM32F302   PWM output |-----|_____|---|---> low-pass filter's output
 * |                            |               |
 * |                            |              _|_
 * |                            |              ___ C
 * |______________________GND___|               |
 *                         |                    |
 *                         |____________________|
 *
 */
static void test_pwm(void){

	char stringBuff[8];
	// Print encoder value
	sprintf(stringBuff, "%s", "PWM TEST");
	lcd16x2_clrscr();
	lcd16x2_puts(stringBuff);

	while(1);
}


int main(void)
{

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Init timers locally */
	timer_cfg();

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */
    iprintf("\nTEST: PWM\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	DelayInit();

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	RUN_TEST(test_pwm);

	/** Nothing to verify */
	TEST_PASS();

    /** Finish unity */
    return UNITY_END();
}





