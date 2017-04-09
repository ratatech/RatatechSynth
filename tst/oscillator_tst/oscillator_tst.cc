/*
@file fileName.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Mar 29, 2017
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


#include "unity.h"
#include "ratatechSynth.h"

#include <stdio.h>


void wait_usart_ready(void){

	// Wait for value 1( ASCII 49) as uart confirmation
	while( USART_ReceiveData(USART2) != 49)

	// Debug usart confirmation
	if(0){
		iprintf("Received data = ");
		uint16_t uart_in = USART_ReceiveData(USART2);
		UnityPrintNumber((UNITY_INT)uart_in);
		iprintf("\n");
	}

	// Ready to start test
    iprintf("\nTEST:  Oscillator\n-----------------------");

}

void intNum2CharStr(int num){
	static char string[11];
	sprintf(string, "%d", num);
	iprintf((const char*)string);
}

#define BUFF_SIZE 256
int buff_sin_ref[BUFF_SIZE] = {
		0,3,6,9,12,15,18,21,24,27,30,34,37,39,42,45,48,51,54,57,60,62,65,68,70,73,75,78,80,83,85,87,90,92,94,
		96,98,100,102,104,106,107,109,110,112,113,115,116,117,118,120,121,122,122,123,124,125,125,126,126,126,
		127,127,127,127,127,127,127,126,126,126,125,125,124,123,122,122,121,120,118,117,116,115,113,112,110,
		109,107,106,104,102,100,98,96,94,92,90,87,85,83,80,78,75,73,70,68,65,62,60,57,54,51,48,45,42,39,37,34,
		30,27,24,21,18,15,12,9,6,3,0,-4,-7,-10,-13,-16,-19,-22,-25,-28,-31,-35,-38,-40,-43,-46,-49,-52,-55,-58,
		-61,-63,-66,-69,-71,-74,-76,-79,-81,-84,-86,-88,-91,-93,-95,-97,-99,-101,-103,-105,-107,-108,-110,-111,
		-113,-114,-116,-117,-118,-119,-121,-122,-123,-123,-124,-125,-126,-126,-127,-127,-127,-128,-128,-128,
		-128,-128,-128,-128,-127,-127,-127,-126,-126,-125,-124,-123,-123,-122,-121,-119,-118,-117,-116,-114,
		-113,-111,-110,-108,-107,-105,-103,-101,-99,-97,-95,-93,-91,-88,-86,-84,-81,-79,-76,-74,-71,-69,-66,
		-63,-61,-58,-55,-52,-49,-46,-43,-40,-38,-35,-31,-28,-25,-22,-19,-16,-13,-10,-7,-4};

// Structure instances
synth_params_t synth_params;

Oscillator osc;

int32_t sample;




int buff_sin_out [BUFF_SIZE];

void test_sine_out(void){

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SIN;
	if(synth_params.FM_synth){
		osc_shape_t shape_osc1 = SIN;
		osc.FM_synth = synth_params.FM_synth;
	}
	osc.set_shape(shape_osc1);
	osc.setFreqFrac(1000);

	for(int i=0; i<BUFF_SIZE; i++){
		sample =  osc.compute_osc(&synth_params);

		buff_sin_out[i] = sample;
	}

	iprintf("buff_sin_out = [");
	for(int j=0; j<BUFF_SIZE;  j++ ){
		intNum2CharStr(buff_sin_out[j]);
		iprintf(",");
	}
	iprintf("]\n");


	TEST_ASSERT_EQUAL_INT_ARRAY(buff_sin_ref,buff_sin_out,BUFF_SIZE);

}


int main(void)
{

	RCC_ClocksTypeDef RCC_Clocks;

	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/* SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    // COnfigure and init peripherals
	GPIO_Conf_Init();
	USART_Conf_Init();

    // turn off buffers, so IO occurs immediately
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Wait usart confirmation to start the test
    wait_usart_ready();

    UNITY_BEGIN();

    RUN_TEST(test_sine_out);

    return UNITY_END();
}

