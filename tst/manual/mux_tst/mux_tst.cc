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

/*
 * MacroMux object
 */
MacroMux macroMux;

#define DEBUG_MUX_ADC_0
//#define DEBUG_MUX_ADC_1
//#define DEBUG_MUX_GPIO0
//#define DEBUG_MUX_GPIO1
//#define DEBUG_MUX_GPIO2

static void print_mux(void){

#ifdef DEBUG_MUX_ADC_0
	iprintf("P7 =%.4i P5 =%.4i P2 =%.4i P6 =%.4i P1 =%.4i P3 =%.4i P9 =%.4i P8 =%.4i\r",
		macroMux.am0->pMux_x[0],
		macroMux.am0->pMux_x[1] ,
		macroMux.am0->pMux_x[2] ,
		macroMux.am0->pMux_x[3] ,
		macroMux.am0->pMux_y[0] ,
		macroMux.am0->pMux_y[1] ,
		macroMux.am0->pMux_y[2] ,
		macroMux.am0->pMux_y[3] );
#endif

#ifdef DEBUG_MUX_ADC_1
	iprintf("P4 =%.4i P0 =%.4i P10 =%.4i P11 =%.4i P12 =%.4i P13 =%.4i P14 =%.4i P15 =%.4i\r",
		macroMux.am1->pMux_x[0],
		macroMux.am1->pMux_x[1] ,
		macroMux.am1->pMux_x[2] ,
		macroMux.am1->pMux_x[3] ,
		macroMux.am1->pMux_y[0] ,
		macroMux.am1->pMux_y[1] ,
		macroMux.am1->pMux_y[2] ,
		macroMux.am1->pMux_y[3] );
#endif


#ifdef DEBUG_MUX_GPIO0
	iprintf("x0=%i x1=%i x2=%i x3=%i y0=%i y1=%i y2=%i y3=%i\r",
		macroMux.gm0->pMux_x[0],
		macroMux.gm0->pMux_x[1],
		macroMux.gm0->pMux_x[2],
		macroMux.gm0->pMux_x[3],
		macroMux.gm0->pMux_y[0],
		macroMux.gm0->pMux_y[1],
		macroMux.gm0->pMux_y[2],
		macroMux.gm0->pMux_y[3] );
#endif

#ifdef DEBUG_MUX_GPIO1
	iprintf("x0=%i x1=%i x2=%i x3=%i y0=%i y1=%i y2=%i y3=%i\r",
		macroMux.gm1->pMux_x[0],
		macroMux.gm1->pMux_x[1],
		macroMux.gm1->pMux_x[2],
		macroMux.gm1->pMux_x[3],
		macroMux.gm1->pMux_y[0],
		macroMux.gm1->pMux_y[1],
		macroMux.gm1->pMux_y[2],
		macroMux.gm1->pMux_y[3] );
#endif

#ifdef DEBUG_MUX_GPIO2
	iprintf("x0=%i x1=%i x2=%i x3=%i y0=%i y1=%i y2=%i y3=%i\r",
		macroMux.gm2->pMux_x[0],
		macroMux.gm2->pMux_x[1],
		macroMux.gm2->pMux_x[2],
		macroMux.gm2->pMux_x[3],
		macroMux.gm2->pMux_y[0],
		macroMux.gm2->pMux_y[1],
		macroMux.gm2->pMux_y[2],
		macroMux.gm2->pMux_y[3] );
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
		macroMux.read(&synth_params);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
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
    iprintf("\nTEST: MUX\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();

	DelayInit();

	while(1){
		print_mux();
		DelayMs(100);
	}

	/** Nothing to verify */
	TEST_PASS();

    /** FInish unity */
    return UNITY_END();
}





