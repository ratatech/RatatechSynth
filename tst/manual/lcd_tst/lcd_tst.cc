/*
@file mux_tst.cc

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
#include "lcd_tst.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

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

//#define DEBUG_MUX_ADC_0
#define DEBUG_MUX_ADC_1
//#define DEBUG_MUX_GPIO0
//#define DEBUG_MUX_GPIO1
//#define DEBUG_MUX_GPIO2

/** Define possible tests */
enum lcd_test_e{
	LCD_ENC,
	LCD_STR,
	LCD_POT,
};

/** Select test */
lcd_test_e lcd_test = LCD_POT;

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
 * LCD print string
 */
void test_lcd_string(void){

	char stringBuff[8];

	while(1){

		// Print encoder value
		sprintf(stringBuff, "%s", "RATATECH");
		lcd16x2_clrscr();
		lcd16x2_puts(stringBuff);

		DelayMs(100);

	}
}

/**
 * LCD + Encoder
 */
void test_lcd_enc(void){

	uint16_t enc_cnt;
	char enc_cnt_buf[8];

	while(1){

		// Get encoder value
		enc_cnt = TIM_GetCounter(TIM4)>>2;

		// Print encoder value
		sprintf(enc_cnt_buf, "%i", enc_cnt);
		lcd16x2_clrscr();
		lcd16x2_puts(enc_cnt_buf);

		DelayMs(100);

	}
}

/**
 * LCD + POTS
 */
void test_lcd_pots(void){

	uint16_t fc,q,lfo_amo,vcof,vcom,adsrt;
	char enc_cnt_buf[16];

	while(1){

		vcof	= ((uint32_t)macroMux.am1->pMux_x[2]*100)>>12;
		vcom 	= ((uint32_t)macroMux.am1->pMux_x[3]*100)>>12;
		adsrt 	= ((uint32_t)macroMux.am1->pMux_y[0]*100)>>12;
		fc		= ((uint32_t)macroMux.am1->pMux_y[1]*100)>>12;
		q 		= ((uint32_t)macroMux.am1->pMux_y[2]*100)>>12;
		lfo_amo = ((uint32_t)macroMux.am1->pMux_y[3]*100)>>12;

		// Print encoder value
		sprintf(enc_cnt_buf, "FC:%.2i Q:%.2i LF:%.2i\nVO:%.2i V:%.2i AC:%.2i", fc,q,lfo_amo,vcof,vcom,adsrt);
		lcd16x2_clrscr();
		lcd16x2_puts(enc_cnt_buf);
		lcd16x2_display_shift_left();

		DelayMs(100);

	}
}


int main(void)
{
	/** Configure macromux*/
	macroMux.config(&synth_params);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */
    iprintf("\nTEST: LCD\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	DelayInit();

    /** Start unity and trigger tests */
    UNITY_BEGIN();

    switch(lcd_test){
    	case LCD_ENC:
    		RUN_TEST(test_lcd_enc);
    		break;

    	case LCD_STR:
    	 	RUN_TEST(test_lcd_string);
    	 	break;

    	case LCD_POT:
    	 	RUN_TEST(test_lcd_pots);
    	 	break;

    }


	/** Nothing to verify */
	TEST_PASS();

    /** FInish unity */
    return UNITY_END();
}





