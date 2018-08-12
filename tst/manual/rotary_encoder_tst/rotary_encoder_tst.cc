/*
@file adsr_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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
#include "tst_utils.h"
#include "system_init.h"

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Dummy object pool
 */
object_pool_t object_pool;

// Custom char data (battery symbol)
uint8_t custom_char[] = { 0x0E, 0x1B, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x1F };

uint16_t enc_cnt;
char enc_cnt_buf[8];

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
 * Rotary encoder test
 */
void rotary_encoder_tst(void){

    // Delayinitialization
    DelayInit();

    // Create custom char
    lcd16x2_create_custom_char(0, custom_char);

    while (1)
    {
        // Get encoder value
        enc_cnt = TIM_GetCounter(TIM4)>>2;
        iprintf("ENCODER = %i\n",enc_cnt);

        // Print encoder value
        sprintf(enc_cnt_buf, "%i", enc_cnt);
        lcd16x2_clrscr();
        lcd16x2_puts(enc_cnt_buf);
        DelayMs(250);

    }
}



int main(void)
{

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */
    iprintf("\nTEST:  ROTARY ENCODER\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(rotary_encoder_tst);

    /** FInish unity */
    return UNITY_END();
}
