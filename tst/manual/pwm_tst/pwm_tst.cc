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
#include "tables.h"

/**
 * Max shift size
 */
#define MAX_SHIFT 16
/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/*
 * MacroMux object
 */
MacroMux macroMux;

/** Dithering resolution, 2^N bits of enhancement */
#define DITHER_BITS 4
#define DITHER_RES 1 << DITHER_BITS

/** Dithering LSB mask used to determine the pattern */
#define DITHER_LSB_MASK 0xF

/** Diethering table */
uint8_t ditheringLut[DITHER_RES][DITHER_RES] = {
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
				{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
				{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
				{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
				{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1},
				{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1},
				{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
				{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

uint8_t ditheringPattern[DITHER_RES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/** Diether value */
uint16_t ditherVal = 0;
uint8_t ditherIdx = 0;
uint8_t lutInd = 0;
volatile uint8_t selectedPattern = 0;

/* Private variables ---------------------------------------------------------*/
#define PWM_BITS 4
#define PWM_TEST_PERIOD 1 << PWM_BITS
#define HI_RES_BITS 16
#define RES_DIFF HI_RES_BITS - PWM_BITS

uint32_t duCyValHigRes 	= 0;
uint32_t duCyValLowRes 	= 0;
uint8_t ditherIndex	= 0;

volatile void updateDitherPattern(uint16_t duCy, uint8_t* pPat){
	selectedPattern = duCyValHigRes & DITHER_LSB_MASK;
	for(int i=0;i<DITHER_RES;i++){
		ditheringPattern[i] = ditheringLut[selectedPattern][i];
	}

}

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		duCyValHigRes = int16_2_uint16(sin_lut_q15[lutInd]);
		updateDitherPattern(duCyValHigRes,ditheringPattern);
		duCyValLowRes = duCyValHigRes>>RES_DIFF;
		lutInd++;
		lutInd%=LUT_8_BIT;

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

}

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{
		volatile uint8_t ditheringVal = ditheringPattern[ditherIndex];
		TIM3->CCR4 = duCyValLowRes;// + ditheringVal;
		ditherIndex++;
		ditherIndex%=DITHER_RES;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

void timer_cfg(void){

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
	timerInitStructure.TIM_Period = PWM_TEST_PERIOD<<DITHER_BITS;
	timerInitStructure.TIM_Prescaler = 0;
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
 */
void test_pwm(void){

	char stringBuff[8];
	uint16_t pwmDuCy;

	// Print encoder value
	sprintf(stringBuff, "%s", "PWM TEST");
	lcd16x2_clrscr();
	lcd16x2_puts(stringBuff);

	TIM3->CCR4 = 32768;
	while(1){
	}
}


int main(void)
{
	/** Configure macromux*/
	macroMux.config(&synth_params);

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





