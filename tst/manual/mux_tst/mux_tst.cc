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

AdcMux adcMux0,adcMux1;
GpioMux gpioMux0,gpioMux1,gpioMux2;

//#define DEBUG_MUX_ADC_0
//#define DEBUG_MUX_ADC_1
#define DEBUG_MUX_GPIOS

static void print_mux(void){

#ifdef DEBUG_MUX_ADC_0
	iprintf("P7 =%.4i P5 =%.4i P2 =%.4i P6 =%.4i P1 =%.4i P3 =%.4i P9 =%.4i P8 =%.4i\r",
			adcMux0.pMux_x[0],
			adcMux0.pMux_x[1] ,
			adcMux0.pMux_x[2] ,
			adcMux0.pMux_x[3] ,
			adcMux0.pMux_y[0] ,
			adcMux0.pMux_y[1] ,
			adcMux0.pMux_y[2] ,
			adcMux0.pMux_y[3] );
#endif

#ifdef DEBUG_MUX_ADC_1
	iprintf("P4 =%.4i P0 =%.4i P10 =%.4i P11 =%.4i P12 =%.4i P13 =%.4i P14 =%.4i P15 =%.4i\r",
			adcMux1.pMux_x[0],
			adcMux1.pMux_x[1] ,
			adcMux1.pMux_x[2] ,
			adcMux1.pMux_x[3] ,
			adcMux1.pMux_y[0] ,
			adcMux1.pMux_y[1] ,
			adcMux1.pMux_y[2] ,
			adcMux1.pMux_y[3] );
#endif


#ifdef DEBUG_MUX_GPIOS
		iprintf("x0=%i x1=%i x2=%i x3=%i y0=%i y1=%i y2=%i y3=%i\r",
		gpioMux0.pMux_x[0],
		gpioMux0.pMux_x[1],
		gpioMux0.pMux_x[2],
		gpioMux0.pMux_x[3],
		gpioMux0.pMux_y[0],
		gpioMux0.pMux_y[1],
		gpioMux0.pMux_y[2],
		gpioMux0.pMux_y[3] );
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
		adcMux0.update(&synth_params);
		adcMux1.update(&synth_params);
		gpioMux0.update(&synth_params);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

}

int main(void)
{

	adcMux0.config(&synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_0_CH0, MUX_ADC_0_CH1);
	adcMux1.config(&synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, 0, 0, 0,  MUX_ADC_1_CH0, MUX_ADC_1_CH1);
	gpioMux0.config(&synth_params, GPIOB, GPIO_Pin_1, GPIO_Pin_12, GPIOA, GPIO_Pin_8, GPIO_Pin_12, 0, 0);

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
		print_mux();
		DelayMs(100);
	}

	/** Nothing to verify */
	TEST_PASS();

    /** FInish unity */
    return UNITY_END();
}





