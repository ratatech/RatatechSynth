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
q15_t buff_lfo_sin_ref[BUFF_SIZE] = { 17669, 18946, 20208, 21446, 22653, 23821, 24943, 26013, 27023, 27968, 28841, 29637, 30352, 30980, 31519, 31964, 32313,
		32564, 32716, 32767, 32716, 32564, 32313, 31964, 31520, 30980, 30352, 29637, 28841, 27968, 27023, 26013, 24943, 23821, 22653, 21446, 20208, 18946,
		17669, 16384, 15098, 13821, 12559, 11321, 10114, 8946, 7824, 6754, 5744, 4799, 3926, 3130, 2415, 1786, 1247, 802, 454, 203, 51, 0, 51, 203, 453, 802,
		1247, 1786, 2415, 3130, 3926, 4798, 5743, 6754, 7823, 8946, 10113, 11321, 12559, 13821, 15098, 16383, 17669, 18946, 20208, 21446, 22653, 23821, 24943,
		26013, 27023, 27968, 28841, 29637, 30352, 30980, 31519, 31964, 32313, 32564, 32716, 32767, 32716, 32564, 32313, 31964, 31520, 30980, 30352, 29637,
		28841, 27968, 27023, 26013, 24943, 23821, 22653, 21446, 20208, 18946, 17669, 16384, 15098, 13821, 12559, 11321, 10114, 8946, 7824, 6754, 5744, 4799,
		3926, 3130, 2415, 1786, 1247, 802, 454, 203, 51, 0, 51, 203, 453, 802, 1247, 1786, 2415, 3130, 3926, 4798, 5743, 6754, 7823, 8946, 10113, 11321, 12559,
		13821, 15098, 16383, 17669, 18946, 20208, 21446, 22653, 23821, 24943, 26013, 27023, 27968, 28841, 29637, 30352, 30980, 31519, 31964, 32313, 32564,
		32716, 32767, 32716, 32564, 32313, 31964, 31520, 30980, 30352, 29637, 28841, 27968, 27023, 26013, 24943, 23821, 22653, 21446, 20208, 18946, 17669,
		16384, 15098, 13821, 12559, 11321, 10114, 8946, 7824, 6754, 5744, 4799, 3926, 3130, 2415, 1786, 1247, 802, 454, 203, 51, 0, 51, 203, 453, 802, 1247,
		1786, 2415, 3130, 3926, 4798, 5743, 6754, 7823, 8946, 10113, 11321, 12559, 13821, 15098, 16383, 17669, 18946, 20208, 21446, 22653, 23821, 24943, 26013,
		27023, 27968, 28841, 29637, 30352, 30980, 31519, 31964, };

/**
 * LFO saw unit test reference buffer
 */
q15_t buff_lfo_saw_ref[BUFF_SIZE] = { 7225, 7623, 8022, 8420, 8818, 9216, 9614, 10013, 10410, 10809, 11207, 11605, 12004, 12401, 12800, 13198, 13596, 13995,
		14392, 14791, 15189, 15587, 15985, 16383, 16782, 17180, 17578, 17976, 18374, 18772, 19171, 19569, 19967, 20365, 20763, 21162, 21560, 21958, 22356,
		22754, 23153, 23551, 23949, 24347, 24745, 25144, 25542, 25940, 26338, 26736, 27135, 27533, 27931, 28329, 28727, 29125, 29524, 29922, 30320, 30718,
		31116, 31514, 31911, 16384, 856, 1253, 1651, 2049, 2447, 2845, 3243, 3642, 4040, 4438, 4836, 5234, 5632, 6031, 6429, 6827, 7225, 7623, 8022, 8420, 8818,
		9216, 9614, 10013, 10410, 10809, 11207, 11605, 12004, 12401, 12800, 13198, 13596, 13995, 14392, 14791, 15189, 15587, 15985, 16383, 16782, 17180, 17578,
		17976, 18374, 18772, 19171, 19569, 19967, 20365, 20763, 21162, 21560, 21958, 22356, 22754, 23153, 23551, 23949, 24347, 24745, 25144, 25542, 25940,
		26338, 26736, 27135, 27533, 27931, 28329, 28727, 29125, 29524, 29922, 30320, 30718, 31116, 31514, 31911, 16384, 856, 1253, 1651, 2049, 2447, 2845, 3243,
		3642, 4040, 4438, 4836, 5234, 5632, 6031, 6429, 6827, 7225, 7623, 8022, 8420, 8818, 9216, 9614, 10013, 10410, 10809, 11207, 11605, 12004, 12401, 12800,
		13198, 13596, 13995, 14392, 14791, 15189, 15587, 15985, 16383, 16782, 17180, 17578, 17976, 18374, 18772, 19171, 19569, 19967, 20365, 20763, 21162,
		21560, 21958, 22356, 22754, 23153, 23551, 23949, 24347, 24745, 25144, 25542, 25940, 26338, 26736, 27135, 27533, 27931, 28329, 28727, 29125, 29524,
		29922, 30320, 30718, 31116, 31514, 31911, 16384, 856, 1253, 1651, 2049, 2447, 2845, 3243, 3642, 4040, 4438, 4836, 5234, 5632, 6031, 6429, 6827, 7225,
		7623, 8022, 8420, 8818, 9216, 9614, 10013, 10410, 10809, 11207, 11605, 12004, 12401, 12800, 13198, };

/**
 * LFO triangle unit test reference buffer
 */
q15_t buff_lfo_tri_ref[BUFF_SIZE] = { 6031, 5234, 4438, 3642, 2845, 2049, 1252, 476, 1252, 2049, 2845, 3642, 4438, 5234, 6031, 6827, 7623, 8420, 9216, 10013,
		10809, 11605, 12401, 13198, 13994, 14791, 15587, 16383, 17180, 17976, 18773, 19569, 20365, 21162, 21958, 22754, 23551, 24347, 25144, 25940, 26736,
		27533, 28329, 29125, 29922, 30718, 31515, 32291, 31515, 30718, 29922, 29125, 28329, 27533, 26736, 25940, 25144, 24347, 23551, 22754, 21958, 21162,
		20366, 19569, 18773, 17976, 17180, 16384, 15587, 14791, 13994, 13198, 12402, 11605, 10809, 10013, 9216, 8420, 7623, 6827, 6031, 5234, 4438, 3642, 2845,
		2049, 1252, 476, 1252, 2049, 2845, 3642, 4438, 5234, 6031, 6827, 7623, 8420, 9216, 10013, 10809, 11605, 12401, 13198, 13994, 14791, 15587, 16383, 17180,
		17976, 18773, 19569, 20365, 21162, 21958, 22754, 23551, 24347, 25144, 25940, 26736, 27533, 28329, 29125, 29922, 30718, 31515, 32291, 31515, 30718,
		29922, 29125, 28329, 27533, 26736, 25940, 25144, 24347, 23551, 22754, 21958, 21162, 20366, 19569, 18773, 17976, 17180, 16384, 15587, 14791, 13994,
		13198, 12402, 11605, 10809, 10013, 9216, 8420, 7623, 6827, 6031, 5234, 4438, 3642, 2845, 2049, 1252, 476, 1252, 2049, 2845, 3642, 4438, 5234, 6031,
		6827, 7623, 8420, 9216, 10013, 10809, 11605, 12401, 13198, 13994, 14791, 15587, 16383, 17180, 17976, 18773, 19569, 20365, 21162, 21958, 22754, 23551,
		24347, 25144, 25940, 26736, 27533, 28329, 29125, 29922, 30718, 31515, 32291, 31515, 30718, 29922, 29125, 28329, 27533, 26736, 25940, 25144, 24347,
		23551, 22754, 21958, 21162, 20366, 19569, 18773, 17976, 17180, 16384, 15587, 14791, 13994, 13198, 12402, 11605, 10809, 10013, 9216, 8420, 7623, 6827,
		6031, 5234, 4438, 3642, 2845, 2049, 1252, 476, 1252, 2049, 2845, 3642, 4438, 5234, 6031, 6827, };


/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * LFO class instance
 */
LFO lfo;

/**
 * Oscillator class instance
 */
Oscillator osc;

/**
 * Unit test output buffer
 */
q15_t pLfoOut[BUFF_SIZE];

/**
 * LFO sine oscillator unit test
 */
void test_lfo_sine_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pLfo[FRAME_SIZE];

	/** Init oscillator with default settings */
	lfo.init(&synth_params.lfo_params);

	/** Set lfo freq */
	lfo.set_freq_frac(600);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		lfo.get_frame(&synth_params,pLfo,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pLfo,&pLfoOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_lfo_sin_out", pLfoOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_lfo_sin_ref,pLfoOut,BUFF_SIZE);

}


/**
 * LFO saw oscillator unit test
 */
void test_lfo_saw_out(void){

	/** Pointer to oscillator frame  **/
	q15_t pLfo[FRAME_SIZE];

	/** Init oscillator with default settings */
	lfo.init(&synth_params.lfo_params);

	/** Set the lfo shape */
	lfo.set_shape(SAW);

	/** Set lfo freq */
	lfo.set_freq_frac(600);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		lfo.get_frame(&synth_params,pLfo,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pLfo,&pLfoOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_lfo_saw_out", pLfoOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_lfo_saw_ref,pLfoOut,BUFF_SIZE);

}

/**
 * LFO triangle oscillator unit test
 */
void test_lfo_tri_out(void){


	/** Pointer to oscillator frame  **/
	q15_t pLfo[FRAME_SIZE];

	/** Init oscillator with default settings */
	lfo.init(&synth_params.lfo_params);

	/** Set the lfo shape */
	lfo.set_shape(TRI);

	/** Set lfo freq */
	lfo.set_freq_frac(600);

	/** Store frames in outuput buffer */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		lfo.get_frame(&synth_params,pLfo,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pLfo,&pLfoOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_lfo_tri_out", pLfoOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_lfo_tri_ref,pLfoOut,BUFF_SIZE);

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
    iprintf("\nTEST:  LFO\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_lfo_sine_out);
    RUN_TEST(test_lfo_saw_out);
    RUN_TEST(test_lfo_tri_out);


    /** FInish unity */
    return UNITY_END();
}

