/*
@file midi_tst.cc

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
#include "midi_tst.h"

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

/**
 * MacroMux object
 */
MacroMux macroMux;

/**
 * MIDI object
 */
MIDI midi;

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
* USART1 interrupt handler
*/
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
    	uint16_t midi_in = USART_ReceiveData(USART1);

    	midi.parseMsg(midi_in);

    	if(midi.midi_msg_type == DATA_VEL){
    		iprintf("MIDI STATUS = %i MIDI NOTE = %i MIDI VEL = %i\r\r",midi.midi_buffer[0],midi.midi_buffer[1],midi.midi_buffer[2]);
    	}
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
 * LCD text movement
 */
void test_midi(void){

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
		DelayUs(100);

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
    iprintf("\nTEST: MIDI\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	DelayInit();

    /** Start unity and trigger tests */
    UNITY_BEGIN();

    RUN_TEST(test_midi);

	/** Nothing to verify */
	TEST_PASS();

    /** Finish unity */
    return UNITY_END();
}





