/*
@file lcd_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
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

#include <stdio.h>
#include "unity.h"
#include "drv/mux.h"
#include "drv/macro_mux.h"
#include "drv/adc_mux.h"
#include "tst_utils.h"
#include "system_init.h"
#include "lcd_tst.h"

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

/** Define possible tests */
enum lcd_test_e{
	LCD_ENC,
	LCD_STR,
	LCD_POT,
	LCD_CUR,
	LCD_TMV,
};

/** Select test */
lcd_test_e lcd_test = LCD_TMV;

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

	int16_t enc_cnt;
	char enc_cnt_buf[8];

	while(1){

		// Get encoder value
		enc_cnt = (int16_t)(TIM_GetCounter(TIM4)>>2);


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

		DelayMs(100);

	}
}

/**
 * LCD cursor interaction
 */
void test_lcd_cursor(void){

	char stringBuff[8];
	lcd16x2_cursor_on();
	lcd16x2_blink_on();

	uint16_t shift_x = 0,shift_y = 0;

	uint8_t speed = 4;
	while(1){

		/** Pot controls how fast the cursor is moved through the screen */
		speed = ((uint32_t)macroMux.am1->pMux_y[3]*8)>>12;

		// Print encoder value
		sprintf(stringBuff, "%s", "RATATECH");
		lcd16x2_clrscr();
		lcd16x2_puts(stringBuff);
		lcd16x2_cursor_shift_right();
		lcd16x2_gotoxy(shift_x,shift_y>>4);
		shift_x+=speed;
		shift_x%=MAX_SHIFT;
		shift_y+=speed;
		shift_y%=(MAX_SHIFT*2);
		DelayMs(100);
	}
}

/**
 * LCD text movement
 */
void test_lcd_text_mov(void){

	char stringBuff[8];
	// Print encoder value
	sprintf(stringBuff, "%s", "RATATECH");
	lcd16x2_clrscr();
	lcd16x2_puts(stringBuff);

	uint16_t enc_cnt,enc_cnt_mem = 0;

	while(1){

		// Get encoder value
		enc_cnt = (int16_t)TIM_GetCounter(TIM4)>>2;

		if((enc_cnt - enc_cnt_mem)<0 || (enc_cnt - enc_cnt_mem)>1000){
			lcd16x2_display_shift_left();
		}
		if( (enc_cnt - enc_cnt_mem)==1){
			lcd16x2_display_shift_right();
		}

		enc_cnt_mem = enc_cnt;
		DelayUs(250);

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

    	case LCD_CUR:
    	 	RUN_TEST(test_lcd_cursor);
    	 	break;

    	case LCD_TMV:
    	 	RUN_TEST(test_lcd_text_mov);
    	 	break;
    }

	/** Nothing to verify */
	TEST_PASS();

    /** Finish unity */
    return UNITY_END();
}





