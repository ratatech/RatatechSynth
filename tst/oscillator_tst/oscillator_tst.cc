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
#include "oscillator.h"
#include "tst_utils.h"


/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * Sine unit test reference buffer
 */
q15_t buff_sin_ref[BUFF_SIZE] = { 2141, 4275, 6390, 8478, 10530, 12537, 14489,
		16380, 18202, 19944, 21601, 23167, 24632, 25992, 27242, 28373, 29384,
		30270, 31024, 31647, 32135, 32482, 32693, 32765, 32693, 32483, 32136,
		31647, 31024, 30271, 29384, 28374, 27243, 25992, 24632, 23168, 21601,
		19944, 18203, 16380, 14490, 12538, 10530, 8478, 6391, 4275, 2141, 0,
		-2144, -4278, -6393, -8481, -10533, -12540, -14492, -16383, -18205,
		-19947, -21604, -23170, -24635, -25995, -27245, -28376, -29387, -30273,
		-31027, -31650, -32138, -32485, -32696, -32767, -32696, -32486, -32139,
		-31650, -31027, -30274, -29387, -28377, -27246, -25995, -24635, -23171,
		-21604, -19947, -18206, -16383, -14493, -12541, -10533, -8481, -6394,
		-4278, -2144, -1, 2141, 4275, 6390, 8478, 10530, 12537, 14489, 16380,
		18202, 19944, 21601, 23167, 24632, 25992, 27242, 28373, 29384, 30270,
		31024, 31647, 32135, 32482, 32693, 32765, 32693, 32483, 32136, 31647,
		31024, 30271, 29384, 28374, 27243, 25992, 24632, 23168, 21601, 19944,
		18203, 16380, 14490, 12538, 10530, 8478, 6391, 4275, 2141, 0, -2144,
		-4278, -6393, -8481, -10533, -12540, -14492, -16383, -18205, -19947,
		-21604, -23170, -24635, -25995, -27245, -28376, -29387, -30273, -31027,
		-31650, -32138, -32485, -32696, -32767, -32696, -32486, -32139, -31650,
		-31027, -30274, -29387, -28377, -27246, -25995, -24635, -23171, -21604,
		-19947, -18206, -16383, -14493, -12541, -10533, -8481, -6394, -4278,
		-2144, -1, 2141, 4275, 6390, 8478, 10530, 12537, 14489, 16380, 18202,
		19944, 21601, 23167, 24632, 25992, 27242, 28373, 29384, 30270, 31024,
		31647, 32135, 32482, 32693, 32765, 32693, 32483, 32136, 31647, 31024,
		30271, 29384, 28374, 27243, 25992, 24632, 23168, 21601, 19944, 18203,
		16380, 14490, 12538, 10530, 8478, 6391, 4275, 2141, 0, -2144, -4278,
		-6393, -8481, -10533, -12540, -14492, -16383, -18205, -19947, -21604,
		-23170, -24635, -25995, -27245, -28376, };

/**
 * Square unit test reference buffer
 */
q15_t buff_squ_ref[BUFF_SIZE] = { -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768,
		-32768, -32768, -32768, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767,
		32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767, 0,
		-32768, -32768, -32768, -32768, -32768, -32768, -32768, -32768, };

/**
 * Saw unit test reference buffer
 */
q15_t buff_saw_ref[BUFF_SIZE] = { -10002, -9335, -8668, -8002, -7335, -6668,
		-6002, -5335, -4668, -4001, -3334, -2667, -2001, -1334, -667, -1, 665,
		1332, 1998, 2665, 3332, 3998, 4666, 5333, 5999, 6666, 7333, 7999, 8666,
		9333, 9999, 10666, 11333, 11999, 12667, 13334, 14000, 14667, 15334,
		16000, 16667, 17334, 18000, 18667, 19334, 20000, 20668, 21335, 22001,
		22668, 23335, 24001, 24668, 25335, 26001, 26668, 27335, 28002, 28669,
		29336, 30001, 30668, 31332, 0, -31335, -30670, -30004, -29338, -28671,
		-28005, -27337, -26670, -26004, -25337, -24670, -24004, -23337, -22670,
		-22004, -21337, -20670, -20003, -19336, -18669, -18003, -17336, -16669,
		-16003, -15336, -14669, -14003, -13336, -12669, -12002, -11335, -10668,
		-10002, -9335, -8668, -8002, -7335, -6668, -6002, -5335, -4668, -4001,
		-3334, -2667, -2001, -1334, -667, -1, 665, 1332, 1998, 2665, 3332, 3998,
		4666, 5333, 5999, 6666, 7333, 7999, 8666, 9333, 9999, 10666, 11333,
		11999, 12667, 13334, 14000, 14667, 15334, 16000, 16667, 17334, 18000,
		18667, 19334, 20000, 20668, 21335, 22001, 22668, 23335, 24001, 24668,
		25335, 26001, 26668, 27335, 28002, 28669, 29336, 30001, 30668, 31332, 0,
		-31335, -30670, -30004, -29338, -28671, -28005, -27337, -26670, -26004,
		-25337, -24670, -24004, -23337, -22670, -22004, -21337, -20670, -20003,
		-19336, -18669, -18003, -17336, -16669, -16003, -15336, -14669, -14003,
		-13336, -12669, -12002, -11335, -10668, -10002, -9335, -8668, -8002,
		-7335, -6668, -6002, -5335, -4668, -4001, -3334, -2667, -2001, -1334,
		-667, -1, 665, 1332, 1998, 2665, 3332, 3998, 4666, 5333, 5999, 6666,
		7333, 7999, 8666, 9333, 9999, 10666, 11333, 11999, 12667, 13334, 14000,
		14667, 15334, 16000, 16667, 17334, 18000, 18667, 19334, 20000, 20668,
		21335, 22001, 22668, 23335, 24001, 24668, 25335, 26001, 26668, 27335,
		28002, 28669, 29336, 30001, 30668, 31332, 0, };

/**
 * Triangle  unit test reference buffer
 */
q15_t buff_tri_ref[BUFF_SIZE] = { 30669, 29336, 28002, 26668, 25335, 24002,
		22668, 21335, 20001, 18667, 17334, 16001, 14667, 13334, 12000, 10666,
		9333, 8000, 6666, 5333, 3999, 2665, 1332, 0, -1334, -2667, -4000, -5335,
		-6668, -8001, -9335, -10668, -12001, -13336, -14669, -16002, -17336,
		-18669, -20002, -21337, -22670, -24003, -25337, -26670, -28003, -29338,
		-30671, -31974, -30671, -29338, -28004, -26670, -25337, -24004, -22670,
		-21337, -20003, -18669, -17336, -16003, -14669, -13336, -12002, -10668,
		-9335, -8002, -6668, -5335, -4001, -2667, -1334, -1, 1332, 2665, 3998,
		5333, 6666, 7999, 9333, 10666, 11999, 13334, 14667, 16000, 17334, 18667,
		20000, 21335, 22668, 24001, 25335, 26668, 28001, 29336, 30669, 31972,
		30669, 29336, 28002, 26668, 25335, 24002, 22668, 21335, 20001, 18667,
		17334, 16001, 14667, 13334, 12000, 10666, 9333, 8000, 6666, 5333, 3999,
		2665, 1332, 0, -1334, -2667, -4000, -5335, -6668, -8001, -9335, -10668,
		-12001, -13336, -14669, -16002, -17336, -18669, -20002, -21337, -22670,
		-24003, -25337, -26670, -28003, -29338, -30671, -31974, -30671, -29338,
		-28004, -26670, -25337, -24004, -22670, -21337, -20003, -18669, -17336,
		-16003, -14669, -13336, -12002, -10668, -9335, -8002, -6668, -5335,
		-4001, -2667, -1334, -1, 1332, 2665, 3998, 5333, 6666, 7999, 9333,
		10666, 11999, 13334, 14667, 16000, 17334, 18667, 20000, 21335, 22668,
		24001, 25335, 26668, 28001, 29336, 30669, 31972, 30669, 29336, 28002,
		26668, 25335, 24002, 22668, 21335, 20001, 18667, 17334, 16001, 14667,
		13334, 12000, 10666, 9333, 8000, 6666, 5333, 3999, 2665, 1332, 0, -1334,
		-2667, -4000, -5335, -6668, -8001, -9335, -10668, -12001, -13336,
		-14669, -16002, -17336, -18669, -20002, -21337, -22670, -24003, -25337,
		-26670, -28003, -29338, -30671, -31974, -30671, -29338, -28004, -26670,
		-25337, -24004, -22670, -21337, -20003, -18669, -17336, -16003, -14669,
		-13336, -12002, -10668,

};



/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Dummy object pool
 */
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
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

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
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

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
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

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
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

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
	ratatech_init(&synth_params);

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

