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

/** Diethering table */
uint16_t ditherTable[4] = {100,200,300,400};

/** Diether value */
uint16_t ditherVal = 0;
uint8_t ditherIdx = 0;

/* Private variables ---------------------------------------------------------*/
#define DITHER_TABLE_FIRST_PART         ((uint16_t*) aDitherTable)
#define DITHER_TABLE_SECOND_PART        ((uint16_t*)(aDitherTable + 8))
/* 3-bit dithering resolution implies 2x8 values table */
uint32_t aDitherTable[16];
uint32_t DitherIndex = 0;
uint32_t DCycleIndex = 0;
uint32_t UpCounting = 1;
void UpdateDitherTable(uint16_t *pDitherTable, uint16_t dutyCycle, uint32_t ditherV);
void UpdateIndex(void);

/**
  * @brief  This function handles Timer 2 Handler.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		macroMux.read(&synth_params);

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
		 /* Update the Dither generation table */
		    if(UpCounting == 1)
		    {
		      UpdateDitherTable(DITHER_TABLE_FIRST_PART, DCycleIndex, DitherIndex);
		    }
		    else
		    {
		      UpdateDitherTable(DITHER_TABLE_FIRST_PART, DCycleIndex, 0);
		    }
		    UpdateIndex();
		TIM3->CCR4 = ditherVal;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

/**
  * @brief  This function handles External lines 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
        iprintf("ENCODER SWITCH ON!!!\n");

		/* Clear the  EXTI line 9 pending bit */
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

/**
  * @brief  Update Dither Table
  * @param  None
  * @retval None
  */
void UpdateDitherTable(uint16_t *pDitherTable, uint16_t DutyCycle, uint32_t DitherV)
{
	uint32_t table_index;

	if (DitherV > 7){
		DitherV = 7;
	}

	for (table_index = 0; table_index <= 7; table_index++)
	{
		if(table_index < DitherV){
			pDitherTable[table_index] = DutyCycle + 1;
		}
		else{
			pDitherTable[table_index] = DutyCycle;
		}
	}
}


/**
  * @brief  Update Indexes
  * @param  None
  * @retval None
  */
void UpdateIndex(void){

	if(DitherIndex < 7){
		DitherIndex++;
	}else{
		DitherIndex = 0;

		if(UpCounting == 1){
			if(DCycleIndex < PWM_PERIOD){
				DCycleIndex++;
			}else{
				UpCounting = 0;
			}
		}else{
			if(DCycleIndex > 0){
				DCycleIndex--;
			}else{
				UpCounting = 1;
			}
		}
	}
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

	while(1){


		//pwmDuCy = (uint16_t)((uint32_t)macroMux.am1->pMux_x[1]*PWM_PERIOD)>>12;

//		pwmDuCy =
		ditherIdx++;
		ditherIdx%=4;
		ditherVal = ditherTable[ditherIdx];
		DelayMs(100);

	}
}


int main(void)
{
	/** Configure macromux*/
	macroMux.config(&synth_params);

	/** Initialize the first part of the DitherTable with the needed duty cycle and
	dithering value */
	UpdateDitherTable(DITHER_TABLE_FIRST_PART, 0, 0);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

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





