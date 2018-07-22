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
#include "tst_utils.h"
#include "system_init.h"
#include "mux_tst.h"

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

MacroMux macro_mux;


//#define DEBUG_MUX_ADC_0
//#define DEBUG_MUX_ADC_1

static void print_mux_adc(void){


	iprintf("pot0 =%.4i pot2 =%.4i pot4 =%.4i pot6 =%.4i\r",
			macro_mux.am_0->pMux_x[0] ,
			macro_mux.am_0->pMux_x[1] ,
			macro_mux.am_0->pMux_x[2] ,
			macro_mux.am_0->pMux_x[3] );




#ifdef DEBUG_MUX_ADC_0
		iprintf("m0_x0 =%.4i m0_x1 =%.4i m0_x2 =%.4i m0_x3 =%.4i m0_y0 =%.4i m0_y1 =%.4i m0_y2 =%.4i m0_y3 =%.4i \r",
		synth_params.mux_adc_0_out.mux_x[0],synth_params.mux_adc_0_out.mux_x[1],synth_params.mux_adc_0_out.mux_x[2],synth_params.mux_adc_0_out.mux_x[3],
		synth_params.mux_adc_0_out.mux_y[0],synth_params.mux_adc_0_out.mux_y[1],synth_params.mux_adc_0_out.mux_y[2],synth_params.mux_adc_0_out.mux_y[3]);
#endif

#ifdef DEBUG_MUX_ADC_1
		iprintf("m1_x0 =%.4i m1_x1 =%.4i m1_x2 =%.4i m1_x3 =%.4i m1_y0 =%.4i m1_y1 =%.4i m1_y2 =%.4i m1_y3 =%.4i \r",
		synth_params.mux_adc_1_out.mux_x[0],synth_params.mux_adc_1_out.mux_x[1],synth_params.mux_adc_1_out.mux_x[2],synth_params.mux_adc_1_out.mux_x[3],
		synth_params.mux_adc_1_out.mux_y[0],synth_params.mux_adc_1_out.mux_y[1],synth_params.mux_adc_1_out.mux_y[2],synth_params.mux_adc_1_out.mux_y[3]);
#endif

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
		macro_mux.update(&synth_params);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

}

int main(void)
{

	macro_mux.config(&synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOB, GPIO_Pin_9, GPIO_Pin_14,  MUX_ADC_0);


	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    //wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST: MUX\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	DelayInit();

	while(1){

		DelayMs(10);
		print_mux_adc();
	}

	/** Nothing to verify */
	TEST_PASS();



    /** FInish unity */
    return UNITY_END();
}





