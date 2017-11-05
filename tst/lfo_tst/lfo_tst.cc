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
		17026,17669,18309,18946,19579,20208,20830,21446,22053,22653,23242,23821,24388,24943,25485,26013,26526,27023,27503,27968,28413,28841,29249,29637,30005,30352,
		30677,30980,31261,31519,31753,31964,32151,32313,32452,32564,32652,32716,32753,32767,32753,32716,32652,32564,32452,32313,32151,31964,31753,31520,31261,30980,
		30677,30352,30006,29637,29249,28841,28413,27968,27504,27023,26526,26013,25486,24943,24388,23821,23242,22653,22053,21446,20830,20208,19580,18946,18309,17669,
		17026,16384,15740,15098,14458,13821,13187,12559,11936,11321,10713,10114,9525,8946,8378,7824,7281,6754,6241,5744,5263,4799,4353,3926,3518,3130,2761,2415,2089,
		1786,1506,1247,1014,802,615,454,315,203,114,51,14,0,13,51,114,203,314,453,615,802,1013,1247,1506,1786,2089,2415,2761,3130,3518,3926,4353,4798,5263,5743,6241,
		6754,7281,7823,8378,8946,9525,10113,10713,11321,11936,12559,13187,13821,14457,15098,15740,16383,17026,17669,18309,18946,19579,20208,20830,21446,22053,22653,
		23242,23821,24388,24943,25485,26013,26526,27023,27503,27968,28413,28841,29249,29637,30005,30352,30677,30980,31261,31519,31753,31964,32151,32313,32452,32564,
		32652,32716,32753,32767,32753,32716,32652,32564,32452,32313,32151,31964,31753,31520,31261,30980,30677,30352,30006,29637,29249,28841,28413,27968,27504,27023,
		26526,26013,25486,24943,24388,23821,23242,22653,22053,21446,20830,20208,19580,18946,18309,17669,17026,16384,15740,15098,14458,13821,13187,12559,11936,11321,
		10713,10114,9525,8946,8378,7824,7281,6754,
};

/**
 * LFO saw unit test reference buffer
 */
q15_t buff_lfo_saw_ref[BUFF_SIZE] = {
		19784,19984,20184,20384,20584,20784,20984,21184,21384,21584,21784,21984,22184,22384,22584,22784,22984,23184,23384,23584,23784,23984,24184,24384,24584,24784,
		24984,25184,25384,25584,25784,25984,26184,26384,26585,26785,26985,27185,27385,27585,27785,27985,28185,28385,28585,28785,28985,29185,29385,29585,29785,29985,
		30185,30385,30585,30785,30985,31185,31385,31585,31785,31984,32183,16384,583,783,982,1182,1382,1582,1781,1981,2181,2381,2582,2782,2982,3182,3382,3582,3782,3982,
		4182,4382,4582,4782,4982,5182,5382,5582,5782,5982,6182,6382,6582,6782,6982,7182,7382,7582,7782,7982,8182,8382,8582,8782,8982,9182,9382,9582,9782,9982,10182,
		10383,10583,10783,10983,11183,11383,11583,11783,11983,12183,12383,12583,12783,12983,13183,13383,13583,13783,13983,14183,14383,14583,14783,14983,15183,15383,
		15583,15783,15983,16183,16383,16583,16783,16983,17183,17383,17583,17783,17983,18183,18383,18584,18784,18984,19184,19384,19584,19784,19984,20184,20384,20584,
		20784,20984,21184,21384,21584,21784,21984,22184,22384,22584,22784,22984,23184,23384,23584,23784,23984,24184,24384,24584,24784,24984,25184,25384,25584,25784,
		25984,26184,26384,26585,26785,26985,27185,27385,27585,27785,27985,28185,28385,28585,28785,28985,29185,29385,29585,29785,29985,30185,30385,30585,30785,30985,
		31185,31385,31585,31785,31984,32183,16384,583,783,982,1182,1382,1582,1781,1981,2181,2381,2582,2782,2982,3182,3382,3582,3782,3982,4182,4382,4582,4782,4982,
		5182,5382,5582,5782,5982,6182,6382,6582,6782,
};

/**
 * LFO triangle unit test reference buffer
 */
q15_t buff_lfo_tri_ref[BUFF_SIZE] = {
		19184,18784,18384,17984,17584,17184,16784,16384,15984,15584,15184,14784,14384,13983,13583,13183,12783,12383,11983,11583,11183,10783,10383,9983,9583,9183,8783,
		8383,7983,7583,7183,6783,6383,5982,5582,5182,4782,4382,3982,3582,3182,2782,2382,1982,1582,1182,782,397,781,1181,1581,1982,2382,2782,3182,3582,3982,4382,4782,
		5182,5582,5982,6382,6782,7182,7582,7982,8382,8782,9182,9582,9982,10383,10783,11183,11583,11983,12383,12783,13183,13583,13983,14383,14783,15183,15583,15983,16383,
		16783,17183,17583,17983,18383,18784,19184,19584,19984,20384,20784,21184,21584,21984,22384,22784,23184,23584,23984,24384,24784,25184,25584,25984,26384,26785,
		27185,27585,27985,28385,28785,29185,29585,29985,30385,30785,31185,31585,31985,32370,31986,31586,31186,30785,30385,29985,29585,29185,28785,28385,27985,27585,
		27185,26785,26385,25985,25585,25185,24785,24385,23985,23585,23185,22785,22384,21984,21584,21184,20784,20384,19984,19584,19184,18784,18384,17984,17584,17184,
		16784,16384,15984,15584,15184,14784,14384,13983,13583,13183,12783,12383,11983,11583,11183,10783,10383,9983,9583,9183,8783,8383,7983,7583,7183,6783,6383,5982,
		5582,5182,4782,4382,3982,3582,3182,2782,2382,1982,1582,1182,782,397,781,1181,1581,1982,2382,2782,3182,3582,3982,4382,4782,5182,5582,5982,6382,6782,7182,7582,
		7982,8382,8782,9182,9582,9982,10383,10783,11183,11583,11983,12383,12783,13183,13583,13983,14383,14783,15183,15583,15983,16383,16783,17183,17583,17983,18383,
		18784,19184,19584,
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

