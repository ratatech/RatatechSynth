/*
@file oscillator_tst.cc

@brief Oscillator unit test

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
#include "arm_math.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * Sine unit test reference buffer
 */
q15_t buff_sin_ref[BUFF_SIZE] = {
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

/**
 * Square unit test reference buffer
 */
q15_t buff_squ_ref[BUFF_SIZE] = {
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
		32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
		32767,32767,32767,32767,32767,32767,32767,0,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
		32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
		32767,32767,32767,32767,32767,32767,32767,0,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
		-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,
		32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,32767,

};

/**
 * Saw unit test reference buffer
 */
q15_t buff_saw_ref[BUFF_SIZE] = {
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

/**
 * Triangle  unit test reference buffer
 */
q15_t buff_tri_ref[BUFF_SIZE] = {
	-31488,-30208,-28928,-27392,-26112,-24832,-23296,-22016,-20736,-19200,-17920,-16640,-15104,-13824,-12544,-11008,-9728,-8448,-6912,-5632,-4352,-2816,-1536,-256,
	1280,2560,3840,5376,6656,7936,9472,10752,12032,13568,14848,16128,17664,18944,20224,21760,23040,24320,25856,27136,28416,29952,31232,32256,30976,29696,
	28416,26880,25600,24320,22784,21504,20224,18688,17408,16128,14592,13312,12032,10496,9216,7936,6400,5120,3840,2304,1024,-256,-1792,-3072,-4352,-5888,-7168,
	-8448,-9984,-11264,-12544,-14080,-15360,-16640,-18176,-19456,-20736,-22272,-23552,-24832,-26368,-27648,-28928,-30464,-31744,-32512,-31488,-30208,-28928,-27392,
	-26112,-24832,-23296,-22016,-20736,-19200,-17920,-16640,-15104,-13824,-12544,-11008,-9728,-8448,-6912,-5632,-4352,-2816,-1536,-256,1280,2560,3840,5376,6656,7936,
	9472,10752,12032,13568,14848,16128,17664,18944,20224,21760,23040,24320,25856,27136,28416,29952,31232,32256,30976,29696,28416,26880,25600,24320,22784,
	21504,20224,18688,17408,16128,14592,13312,12032,10496,9216,7936,6400,5120,3840,2304,1024,-256,-1792,-3072,-4352,-5888,-7168,-8448,-9984,-11264,-12544,-14080,
	-15360,-16640,-18176,-19456,-20736,-22272,-23552,-24832,-26368,-27648,-28928,-30464,-31744,-32512,-31488,-30208,-28928,-27392,-26112,-24832,-23296,-22016,-20736,
	-19200,-17920,-16640,-15104,-13824,-12544,-11008,-9728,-8448,-6912,-5632,-4352,-2816,-1536,-256,1280,2560,3840,5376,6656,7936,9472,10752,12032,13568,14848,
	16128,17664,18944,20224,21760,23040,24320,25856,27136,28416,29952,31232,32256,30976,29696,28416,26880,25600,24320,22784,21504,20224,18688,17408,16128,
	14592,13312,12032,10496,
};



/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;
object_pool_t object_pool;

/**
 * Oscillator class instance
 */
Oscillator osc;

/**
 * Unit test output buffer
 */
q15_t pOscOut[BUFF_SIZE];

/**
 * Sine oscillator unit test
 */
void test_sine_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Store frames in outuput buffer */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pOsc,&pOscOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_sin_out", pOscOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_sin_ref,pOscOut,BUFF_SIZE);

}

/**
 * Square oscillator unit test
 */
void test_square_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);


	/** Set shape */
	osc.set_shape(SQU);

	/** Store frames in outuput buffer */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pOsc,&pOscOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_squ_out", pOscOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_squ_ref,pOscOut,BUFF_SIZE);

}

/**
 * Saw oscillator unit test
 */
void test_saw_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Set shape */
	osc.set_shape(SAW);

	/** Store frames in outuput buffer */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pOsc,&pOscOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_saw_out", pOscOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_saw_ref,pOscOut,BUFF_SIZE);

}

/**
 * Triangle oscillator unit test
 */
void test_triangle_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Set shape */
	osc.set_shape(TRI);

	/** Store frames in outuput buffer */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pOsc,&pOscOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_tri_out", pOscOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_tri_ref,pOscOut,BUFF_SIZE);

}

int main(void)
{

	/** Init system and peripherals */
	ratatech_init();

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST:  Oscillator\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_sine_out);
    RUN_TEST(test_square_out);
    RUN_TEST(test_saw_out);
    RUN_TEST(test_triangle_out);

    /** FInish unity */
    return UNITY_END();
}

