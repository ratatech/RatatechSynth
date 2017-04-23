/*
@file lfo_tst.cc

@brief LFO unit test

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

#include <stdio.h>
#include "unity.h"
#include "ratatechSynth.h"
#include "tst_utils.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * LFO sine unit test reference buffer
 */
int32_t buff_lfo_sin_ref[BUFF_SIZE] = {
		18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,30848,29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,
		5120,3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,15872,18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,
		32000,30848,29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,5120,3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,
		15872,18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,30848,29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,
		5120,3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,15872,18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,
		30848,29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,5120,3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,15872,
		18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,30848,29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,5120,
		3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,15872,18688,21120,23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,30848,
		29696,28160,25984,24064,21376,19072,16768,13952,11520,8960,6912,5120,3200,1920,768,256,0,128,640,1792,2944,4480,6656,8576,11264,13568,15872,18688,21120,
		23680,25728,27520,29440,30720,31872,32384,32640,32512,32000,30848,29696,28160,25984,
};



/**
 * LFO saw unit test reference buffer
 */
int32_t buff_lfo_saw_ref[BUFF_SIZE] = {
		13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,22016,22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,31104,31872,16384,
		768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,9728,10624,11392,12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,22016,
		22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,31104,31872,16384,768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,9728,10624,11392,
		12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,22016,22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,31104,31872,
		16384,768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,9728,10624,11392,12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,
		22016,22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,31104,31872,16384,768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,9728,10624,
		11392,12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,22016,22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,
		31104,31872,16384,768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,9728,10624,11392,12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,
		20352,21248,22016,22912,23680,24448,25344,26112,27008,27776,28544,29440,30208,31104,31872,16384,768,1536,2432,3200,3968,4864,5632,6528,7296,8064,8960,
		9728,10624,11392,12160,13056,13824,14720,15488,16256,17152,17920,18816,19584,20352,21248,22016,22912,23680,24448,25344,26112,

};

/**
 * LFO triangle unit test reference buffer
 */
int32_t buff_lfo_tri_ref[BUFF_SIZE] = {
		11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,7936,9728,11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,27648,29440,30976,
		32512,31104,29568,27776,26240,24704,22912,21376,19584,18048,16512,14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,7936,9728,
		11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,27648,29440,30976,32512,31104,29568,27776,26240,24704,22912,21376,19584,18048,16512,
		14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,7936,9728,11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,27648,
		29440,30976,32512,31104,29568,27776,26240,24704,22912,21376,19584,18048,16512,14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,
		7936,9728,11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,27648,29440,30976,32512,31104,29568,27776,26240,24704,22912,21376,19584,18048,
		16512,14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,7936,9728,11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,
		27648,29440,30976,32512,31104,29568,27776,26240,24704,22912,21376,19584,18048,16512,14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,
		4864,6400,7936,9728,11264,13056,14592,16128,17920,19456,21248,22784,24320,26112,27648,29440,30976,32512,31104,29568,27776,26240,24704,22912,21376,
		19584,18048,16512,14720,13184,11392,9856,8320,6528,4992,3200,1664,128,1536,3072,4864,6400,7936,9728,11264,13056,

};

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * LFO class instance
 */
LFO lfo;

/**
 * Unit test output buffer
 */
int32_t buff_out [BUFF_SIZE];

/**
 * LFO sine oscillator unit test
 */
void test_lfo_sine_out(void){

	int32_t sample;

	/** Configure lfo */
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(100);

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){
		buff_out[i] = lfo.get_sample();
	}

	/** Print output buffer */
	printOutBuff("buff_lfo_sin_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_lfo_sin_ref,buff_out,BUFF_SIZE);

}


/**
 * LFO saw oscillator unit test
 */
void test_lfo_saw_out(void){

	int32_t sample;

	/** Configure lfo */
	osc_shape_t shape_lfo = SAW;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(100);

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){
		buff_out[i] = lfo.get_sample();
	}

	/** Print output buffer */
	printOutBuff("buff_lfo_saw_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_lfo_saw_ref,buff_out,BUFF_SIZE);

}

/**
 * LFO triangle oscillator unit test
 */
void test_lfo_tri_out(void){

	int32_t sample;

	/** Configure lfo */
	osc_shape_t shape_lfo = TRI;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(100);

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){
		buff_out[i] = lfo.get_sample();
	}

	/** Print output buffer */
	printOutBuff("buff_lfo_tri_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_lfo_tri_ref,buff_out,BUFF_SIZE);

}

int main(void)
{

	/** System init */
	RCC_ClocksTypeDef RCC_Clocks;
	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/** SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    /** Configure and init peripherals  */
	GPIO_Conf_Init();
	USART_Conf_Init();

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();
	/** Ready to start test  */
    iprintf("\nTEST:  LFO\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_lfo_sine_out);
    RUN_TEST(test_lfo_saw_out);
    RUN_TEST(test_lfo_tri_out);

    /** FInish unity */
    return UNITY_END();
}

