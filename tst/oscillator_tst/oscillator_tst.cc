/*
@file oscillator_tst.cc

@brief Oscillator unit test

@ Created by Jordi Hidalgo, Ratatech, Mar 29, 2017
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
#include "oscillator.h"
#include "tst_utils.h"
#include "synthSettings.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * Sine unit test reference buffer
 */
q15_t buff_sin_ref[BUFF_SIZE] = { 4276, 8479, 12538, 16381, 19945, 23168, 25993, 28374, 30271, 31648, 32483, 32766, 32484, 31648, 30272, 28375, 25993, 23169,
		19945, 16381, 12539, 8479, 4276, 0, -4278, -8481, -12540, -16383, -19947, -23170, -25995, -28376, -30273, -31650, -32485, -32767, -32486, -31650,
		-30274, -28377, -25995, -23171, -19947, -16383, -12541, -8481, -4278, -1, 4276, 8479, 12538, 16381, 19945, 23168, 25993, 28374, 30271, 31648, 32483,
		32766, 32484, 31648, 30272, 28375, 25993, 23169, 19945, 16381, 12539, 8479, 4276, 0, -4278, -8481, -12540, -16383, -19947, -23170, -25995, -28376,
		-30273, -31650, -32485, -32767, -32486, -31650, -30274, -28377, -25995, -23171, -19947, -16383, -12541, -8481, -4278, -1, 4276, 8479, 12538, 16381,
		19945, 23168, 25993, 28374, 30271, 31648, 32483, 32766, 32484, 31648, 30272, 28375, 25993, 23169, 19945, 16381, 12539, 8479, 4276, 0, -4278, -8481,
		-12540, -16383, -19947, -23170, -25995, -28376, -30273, -31650, -32485, -32767, -32486, -31650, -30274, -28377, -25995, -23171, -19947, -16383, -12541,
		-8481, -4278, -1, 4276, 8479, 12538, 16381, 19945, 23168, 25993, 28374, 30271, 31648, 32483, 32766, 32484, 31648, 30272, 28375, 25993, 23169, 19945,
		16381, 12539, 8479, 4276, 0, -4278, -8481, -12540, -16383, -19947, -23170, -25995, -28376, -30273, -31650, -32485, -32767, -32486, -31650, -30274,
		-28377, -25995, -23171, -19947, -16383, -12541, -8481, -4278, -1, 4276, 8479, 12538, 16381, 19945, 23168, 25993, 28374, 30271, 31648, 32483, 32766,
		32484, 31648, 30272, 28375, 25993, 23169, 19945, 16381, 12539, 8479, 4276, 0, -4278, -8481, -12540, -16383, -19947, -23170, -25995, -28376, -30273,
		-31650, -32485, -32767, -32486, -31650, -30274, -28377, -25995, -23171, -19947, -16383, -12541, -8481, -4278, -1, 4276, 8479, 12538, 16381, 19945,
		23168, 25993, 28374, 30271, 31648, 32483, 32766, 32484, 31648, 30272, 28375, };

/**
 * Square unit test reference buffer
 */
q15_t buff_squ_ref[BUFF_SIZE] = { 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 0, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 0, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0, -32768, -32768, -32768, -32768, };

/**
 * Saw unit test reference buffer
 */
q15_t buff_saw_ref[BUFF_SIZE] = { -30526, -29201, -27874, -26547, -25219, -23892, -22565, -21238, -19910, -18583, -17256, -15928, -14601, -13274, -11947,
		-10619, -9292, -7965, -6637, -5310, -3983, -2656, -1328, -1, 1326, 2654, 3981, 5308, 6636, 7963, 9290, 10617, 11945, 13272, 14599, 15926, 17254, 18581,
		19908, 21236, 22563, 23890, 25217, 26545, 27872, 29199, 30525, 0, -30526, -29201, -27874, -26547, -25219, -23892, -22565, -21238, -19910, -18583,
		-17256, -15928, -14601, -13274, -11947, -10619, -9292, -7965, -6637, -5310, -3983, -2656, -1328, -1, 1326, 2654, 3981, 5308, 6636, 7963, 9290, 10617,
		11945, 13272, 14599, 15926, 17254, 18581, 19908, 21236, 22563, 23890, 25217, 26545, 27872, 29199, 30525, 0, -30526, -29201, -27874, -26547, -25219,
		-23892, -22565, -21238, -19910, -18583, -17256, -15928, -14601, -13274, -11947, -10619, -9292, -7965, -6637, -5310, -3983, -2656, -1328, -1, 1326, 2654,
		3981, 5308, 6636, 7963, 9290, 10617, 11945, 13272, 14599, 15926, 17254, 18581, 19908, 21236, 22563, 23890, 25217, 26545, 27872, 29199, 30525, 0, -30526,
		-29201, -27874, -26547, -25219, -23892, -22565, -21238, -19910, -18583, -17256, -15928, -14601, -13274, -11947, -10619, -9292, -7965, -6637, -5310,
		-3983, -2656, -1328, -1, 1326, 2654, 3981, 5308, 6636, 7963, 9290, 10617, 11945, 13272, 14599, 15926, 17254, 18581, 19908, 21236, 22563, 23890, 25217,
		26545, 27872, 29199, 30525, 0, -30526, -29201, -27874, -26547, -25219, -23892, -22565, -21238, -19910, -18583, -17256, -15928, -14601, -13274, -11947,
		-10619, -9292, -7965, -6637, -5310, -3983, -2656, -1328, -1, 1326, 2654, 3981, 5308, 6636, 7963, 9290, 10617, 11945, 13272, 14599, 15926, 17254, 18581,
		19908, 21236, 22563, 23890, 25217, 26545, 27872, 29199, 30525, 0, -30526, -29201, -27874, -26547, -25219, -23892, -22565, -21238, -19910, -18583,
		-17256, -15928, -14601, -13274, -11947, -10619, };

/**
 * Triangle  unit test reference buffer
 */
q15_t buff_tri_ref[BUFF_SIZE] = { 29200, 26546, 23891, 21236, 18582, 15927, 13273, 10618, 7964, 5309, 2654, 0, -2655, -5309, -7964, -10618, -13273, -15927,
		-18582, -21237, -23891, -26546, -29200, -31815, -29201, -26547, -23892, -21237, -18583, -15928, -13274, -10619, -7965, -5310, -2655, -1, 2654, 5308,
		7963, 10617, 13272, 15926, 18581, 21236, 23890, 26545, 29199, 31814, 29200, 26546, 23891, 21236, 18582, 15927, 13273, 10618, 7964, 5309, 2654, 0, -2655,
		-5309, -7964, -10618, -13273, -15927, -18582, -21237, -23891, -26546, -29200, -31815, -29201, -26547, -23892, -21237, -18583, -15928, -13274, -10619,
		-7965, -5310, -2655, -1, 2654, 5308, 7963, 10617, 13272, 15926, 18581, 21236, 23890, 26545, 29199, 31814, 29200, 26546, 23891, 21236, 18582, 15927,
		13273, 10618, 7964, 5309, 2654, 0, -2655, -5309, -7964, -10618, -13273, -15927, -18582, -21237, -23891, -26546, -29200, -31815, -29201, -26547, -23892,
		-21237, -18583, -15928, -13274, -10619, -7965, -5310, -2655, -1, 2654, 5308, 7963, 10617, 13272, 15926, 18581, 21236, 23890, 26545, 29199, 31814, 29200,
		26546, 23891, 21236, 18582, 15927, 13273, 10618, 7964, 5309, 2654, 0, -2655, -5309, -7964, -10618, -13273, -15927, -18582, -21237, -23891, -26546,
		-29200, -31815, -29201, -26547, -23892, -21237, -18583, -15928, -13274, -10619, -7965, -5310, -2655, -1, 2654, 5308, 7963, 10617, 13272, 15926, 18581,
		21236, 23890, 26545, 29199, 31814, 29200, 26546, 23891, 21236, 18582, 15927, 13273, 10618, 7964, 5309, 2654, 0, -2655, -5309, -7964, -10618, -13273,
		-15927, -18582, -21237, -23891, -26546, -29200, -31815, -29201, -26547, -23892, -21237, -18583, -15928, -13274, -10619, -7965, -5310, -2655, -1, 2654,
		5308, 7963, 10617, 13272, 15926, 18581, 21236, 23890, 26545, 29199, 31814, 29200, 26546, 23891, 21236, 18582, 15927, 13273, 10618, 7964, 5309, 2654, 0,
		-2655, -5309, -7964, -10618, };



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

    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(pOsc,FRAME_SIZE);

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

    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Set shape */
	osc.set_shape(SQU);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(pOsc,FRAME_SIZE);

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

    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Set shape */
	osc.set_shape(SAW);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(pOsc,FRAME_SIZE);

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

    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	/** Init oscillator with default settings */
	osc.init(&s->osc_params);

	/** Set shape */
	osc.set_shape(TRI);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		osc.get_frame(pOsc,FRAME_SIZE);

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

//	/** Init system and peripherals */
//	ratatech_init(&synth_params);
//
//	/** Load initial default settings */
//	init_settings(&synth_params,object_pool);

    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

    /** Init instance with default settings **/
    s->intDefaultSettings();

	/** Init system and peripherals */
	ratatech_init();

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

