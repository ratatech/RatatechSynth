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
q15_t buff_lfo_sin_ref[BUFF_SIZE] = {
		17026,17669,18309,18946,19579,20208,20830,21446,22054,22653,23242,23821,24388,24943,25485,26013,26526,27023,27504,27968,28413,28841,29249,29637,30006,30352,30677,
		30980,31261,31520,31753,31964,32151,32313,32452,32564,32653,32716,32753,32767,32753,32716,32653,32564,32452,32313,32151,31964,31753,31520,31261,30980,30677,30352,
		30006,29637,29249,28841,28413,27968,27504,27023,26526,26013,25486,24943,24389,23821,23242,22653,22054,21446,20830,20208,19580,18946,18309,17669,17026,16384,15740,
		15098,14458,13821,13187,12559,11936,11321,10713,10114,9525,8946,8378,7824,7281,6754,6241,5744,5263,4798,4353,3926,3517,3129,2761,2415,2089,1786,1506,1247,1013,802,
		615,453,315,202,114,51,13,0,13,51,114,202,315,453,615,802,1013,1247,1506,1786,2089,2415,2760,3129,3517,3926,4353,4798,5263,5743,6241,6754,7281,7823,8378,8946,9525,
		10113,10713,11321,11936,12559,13187,13821,14457,15098,15740,15981,17026,17669,18309,18946,19579,20208,20830,21446,22054,22653,23242,23821,24388,24943,25485,26013,
		26526,27023,27504,27968,28413,28841,29249,29637,30006,30352,30677,30980,31261,31520,31753,31964,32151,32313,32452,32564,32653,32716,32753,32767,32753,32716,32653,
		32564,32452,32313,32151,31964,31753,31520,31261,30981,30677,30352,30006,29637,29249,28841,28413,27969,27504,27023,26526,26013,25486,24943,24389,23821,23242,22653,
		22054,21446,20830,20208,19580,18946,18309,17669,17026,16384,15740,15098,14458,13821,13187,12559,11936,11321,10713,10114,9525,8946,8378,7824,7281,6754,
};

/**
 * LFO saw unit test reference buffer
 */
q15_t buff_lfo_saw_ref[BUFF_SIZE] = {
		19865,20070,20275,20479,20684,20889,21094,21299,21503,21708,21913,22118,22323,22527,22732,22937,23142,23347,23551,23756,23961,24166,24371,24575,24780,24985,25190,
		25395,25599,25804,26009,26214,26419,26623,26828,27033,27238,27443,27647,27852,28057,28262,28467,28671,28876,29081,29286,29491,29695,29900,30105,30310,30515,30719,
		30924,31129,31334,31539,31743,31948,32153,32358,32563,32640,204,409,614,819,1023,1228,1433,1638,1843,2047,2252,2457,2662,2867,3071,3276,3481,3686,3891,4095,4300,
		4505,4710,4915,5119,5324,5529,5734,5939,6143,6348,6553,6758,6963,7167,7372,7577,7782,7987,8191,8396,8601,8806,9011,9215,9420,9625,9830,10035,10239,10444,10649,
		10854,11059,11263,11468,11673,11878,12083,12287,12492,12697,12902,13107,13311,13516,13721,13926,14131,14335,14540,14745,14950,15155,15359,15564,15769,15974,16179,
		16383,16588,16793,16998,17203,17407,17612,17817,18022,18227,18431,18636,18841,19046,19251,19455,19660,19865,20070,20275,20479,20684,20889,21094,21299,21503,21708,
		21913,22118,22323,22527,22732,22937,23142,23347,23551,23756,23961,24166,24371,24575,24780,24985,25190,25395,25599,25804,26009,26214,26419,26623,26828,27033,27238,
		27443,27647,27852,28057,28262,28467,28671,28876,29081,29286,29491,29695,29900,30105,30310,30515,30719,30924,31129,31334,31539,31743,31948,32153,32358,32563,32640,
		204,409,614,819,1023,1228,1433,1638,1843,2047,2252,2457,2662,2867,3071,3276,3481,3686,3891,4095,4300,4505,4710,4915,5119,5324,5529,5734,5939,6143,6348,6553,
};

/**
 * LFO triangle unit test reference buffer
 */
q15_t buff_lfo_tri_ref[BUFF_SIZE] = {
		13517,13926,14336,14746,15155,15565,15974,16384,16794,17203,17613,18022,18432,18842,19251,19661,20070,20480,20890,21299,21709,22118,22528,22938,23347,23757,24166,
		24576,24986,25395,25805,26214,26624,27034,27443,27853,28262,28672,29082,29491,29901,30310,30720,31130,31539,31949,32358,32766,32357,31947,31538,31128,30719,30309,
		29899,29490,29080,28671,28261,27851,27442,27032,26623,26213,25803,25394,24984,24575,24165,23755,23346,22936,22527,22117,21707,21298,20888,20479,20069,19659,19250,
		18840,18431,18021,17611,17202,16792,16383,15973,15563,15154,14744,14335,13925,13515,13106,12696,12287,11877,11467,11058,10648,10239,9829,9419,9010,8600,8191,7781,
		7371,6962,6552,6143,5733,5323,4914,4504,4095,3685,3275,2866,2456,2047,1637,1227,818,408,255,410,819,1229,1638,2048,2458,2867,3277,3686,4096,4506,4915,5325,5734,
		6144,6554,6963,7373,7782,8192,8602,9011,9421,9830,10240,10650,11059,11469,11878,12288,12698,13107,13517,13926,14336,14746,15155,15565,15974,16384,16793,17203,
		17613,18022,18432,18841,19251,19661,20070,20480,20889,21299,21709,22118,22528,22937,23347,23757,24166,24576,24985,25395,25805,26214,26624,27033,27443,27853,28262,
		28672,29081,29491,29901,30310,30720,31129,31539,31949,32358,32766,32357,31947,31538,31128,30719,30309,29899,29490,29080,28671,28261,27851,27442,27032,26623,26213,
		25803,25394,24984,24575,24165,23755,23346,22936,22527,22117,21707,21298,20888,20479,20069,19659,19250,18840,18431,18021,17611,17202,16792,16383,15973,15563,15154,
		14744,14335,13925,13515,13106,
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

