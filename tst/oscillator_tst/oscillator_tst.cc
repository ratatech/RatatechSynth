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

void intNum2CharStr(int32_t num){
	static char string[11];
	sprintf(string, "%d", num);
	iprintf((const char*)string);
}

#define BUFF_SIZE 256
int32_t buff_sin_ref[BUFF_SIZE] = {
		1792,3840,5888,8192,9984,12032,14080,15872,17664,19456,21248,22784,24320,25600,26880,27904,28928,29696,30720,31232,31744,32000,32256,
		32256,32256,32000,31744,31232,30720,29696,28928,27904,26880,25600,24320,22784,21248,19456,17920,16128,14336,12288,10240,8192,6144,4096,
		2048,0,-2304,-4352,-6400,-8704,-10496,-12544,-14592,-16384,-18176,-19968,-21760,-23296,-24832,-26112,-27392,-28416,-29440,-30208,-31232,-31744,
		-32256,-32512,-32768,-32768,-32768,-32512,-32256,-31744,-31232,-30208,-29440,-28416,-27392,-26112,-24832,-23552,-21760,-20224,-18432,-16640,
		-14848,-12800,-10752,-8704,-6656,-4608,-2560,-1024,1792,3840,5888,8192,9984,12032,14080,15872,17664,19456,21248,22784,24320,25600,26880,
		27904,28928,29696,30720,31232,31744,32000,32256,32256,32256,32000,31744,31232,30720,29696,28928,27904,26880,25600,24320,23040,21248,
		19712,17920,16128,14336,12288,10240,8192,6144,4096,2048,0,-2304,-4352,-6400,-8704,-10496,-12544,-14592,-16384,-18176,-19968,-21760,-23296,
		-24832,-26112,-27392,-28416,-29440,-30208,-31232,-31744,-32256,-32512,-32768,-32768,-32768,-32512,-32256,-31744,-31232,-30208,-29440,-28416,
		-27648,-26112,-24832,-23552,-21760,-20224,-18432,-16640,-14848,-12800,-10752,-8704,-6656,-4608,-2560,-1024,1792,3840,5888,8192,9984,12032,14080,
		15872,17664,19456,21248,22784,24320,25600,26880,27904,28928,29696,30720,31232,31744,32000,32256,32256,32256,32000,31744,31232,30720,29952,
		28928,27904,27136,25600,24320,23040,21248,19712,17920,16128,14336,12288,10240,8192,6144,4096,2048,0,-2304,-4352,-6400,-8704,-10496,-12544,
		-14592,-16384,-18176,-19968,-21760,-23296,-24832,-26112,-27392,-28416
};

int32_t buff_squ_ref[BUFF_SIZE] = {
		32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,
		32256,32256,32256,32256,32256,32256,32256,32512,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,
		32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,
		32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32512,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,
		32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,
		32256,32256,32256,32256,32256,32256,32256,32256,32256,32256,32512,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,

};

int32_t buff_saw_ref[BUFF_SIZE] = {
		-10496,-9728,-8960,-8448,-7680,-6912,-6400,-5632,-4864,-4352,-3584,-2816,-2304,-1536,-768,-256,512,1280,1792,2560,3328,3840,4608,5376,5888,6656,
		7424,7936,8704,9472,9984,10752,11520,12032,12800,13568,14080,14848,15616,16128,16896,17664,18176,18944,19712,20224,20992,21760,22272,23040,
		23808,24320,25088,25856,26368,27136,27904,28416,29184,29952,30464,31232,32000,0,-32256,-31488,-30976,-30208,-29440,-28928,-28160,-27392,-26880,
		-26112,-25344,-24832,-24064,-23296,-22784,-22016,-21248,-20736,-19968,-19200,-18688,-17920,-17152,-16640,-15872,-15104,-14592,-13824,-13056,-12544,
		-11776,-11008,-10496,-9728,-8960,-8448,-7680,-6912,-6400,-5632,-4864,-4352,-3584,-2816,-2304,-1536,-768,-256,512,1280,1792,2560,3328,3840,4608,5376,
		5888,6656,7424,7936,8704,9472,9984,10752,11520,12032,12800,13568,14080,14848,15616,16128,16896,17664,18176,18944,19712,20224,20992,21760,22272,
		23040,23808,24320,25088,25856,26368,27136,27904,28416,29184,29952,30464,31232,32000,0,-32256,-31488,-30976,-30208,-29440,-28928,-28160,-27392,-26880,
		-26112,-25344,-24832,-24064,-23296,-22784,-22016,-21248,-20736,-19968,-19200,-18688,-17920,-17152,-16640,-15872,-15104,-14592,-13824,-13056,-12544,-11776,
		-11008,-10496,-9728,-8960,-8448,-7680,-6912,-6400,-5632,-4864,-4352,-3584,-2816,-2304,-1536,-768,-256,512,1280,1792,2560,3328,3840,4608,5376,5888,6656,7424,
		7936,8704,9472,9984,10752,11520,12032,12800,13568,14080,14848,15616,16128,16896,17664,18176,18944,19712,20224,20992,21760,22272,23040,23808,24320,
		25088,25856,26368,27136,27904,28416,29184,29952,30464,31232,32000,0,
};

// Structure instances
synth_params_t synth_params;

Oscillator osc;

int32_t sample;




int32_t buff_sin_out [BUFF_SIZE];
int32_t buff_squ_out [BUFF_SIZE];
int32_t buff_saw_out [BUFF_SIZE];

void test_sine_out(void){

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SIN;
	osc.set_shape(shape_osc1);
	osc.setFreqFrac(1000);

	for(int i=0; i<BUFF_SIZE; i++){
		sample =  osc.compute_osc(&synth_params);

		buff_sin_out[i] = sample;
	}

	iprintf("]\nbuff_sin_out = [");
	for(int j=0; j<BUFF_SIZE;  j++ ){
		intNum2CharStr(buff_sin_out[j]);
		iprintf(",");
	}
	iprintf("]\n");


	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_sin_ref,buff_sin_out,BUFF_SIZE);

}

void test_square_out(void){

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SQU;
	osc.set_shape(shape_osc1);
	osc.setFreqFrac(1000);

	for(int i=0; i<BUFF_SIZE; i++){
		sample =  osc.compute_osc(&synth_params);

		buff_squ_out[i] = sample;
	}

	iprintf("]\nbuff_squ_out = [");
	for(int j=0; j<BUFF_SIZE;  j++ ){
		intNum2CharStr(buff_squ_out[j]);
		iprintf(",");
	}
	iprintf("]\n");


	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_squ_ref,buff_squ_out,BUFF_SIZE);

}

void test_saw_out(void){

	// Configure oscillator 1
	osc_shape_t shape_osc1 = SAW;
	osc.set_shape(shape_osc1);
	osc.setFreqFrac(1000);

	for(int i=0; i<BUFF_SIZE; i++){
		sample =  osc.compute_osc(&synth_params);

		buff_saw_out[i] = sample;
	}

	iprintf("]\nbuff_saw_out = [");
	for(int j=0; j<BUFF_SIZE;  j++ ){
		intNum2CharStr(buff_saw_out[j]);
		iprintf(",");
	}
	iprintf("]\n");


	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_saw_ref,buff_saw_out,BUFF_SIZE);

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
    RUN_TEST(test_square_out);
    RUN_TEST(test_saw_out);

    return UNITY_END();
}

