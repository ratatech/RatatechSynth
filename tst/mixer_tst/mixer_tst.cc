/*
@file mixer_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 24, 2017
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
 * MIxer unit test reference buffer
 */
q15_t buff_mix_ref[BUFF_SIZE] = { 3207, 6375, 9463, 12428, 15236, 17850, 20239, 22375, 24235, 25794, 27040, 27964, 28556, 28818, 28755, 28372, 27687, 26718,
		25483, 24012, 22335, 20479, 18483, 16382, 14207, 12000, 9798, 7631, 5539, 3550, 1695, -1, -1515, -2829, -3926, -4799, -5443, -5853, -6036, -5998, -5752,
		-5316, -4708, -3953, -3076, -2104, -1069, -1, 1065, 2099, 3071, 3948, 4704, 5312, 5749, 5993, 6031, 5848, 5438, 4796, 3922, 2824, 1511, -2, -1699,
		-3554, -5543, -7636, -9801, -12005, -14211, -16384, -18487, -20484, -22340, -24017, -25487, -26722, -27691, -28377, -28759, -28823, -28560, -27969,
		-27045, -25799, -24240, -22380, -20244, -17856, -15240, -12433, -9468, -6380, -3211, -2, 3207, 6375, 9463, 12428, 15236, 17850, 20239, 22375, 24235,
		25794, 27040, 27964, 28556, 28818, 28755, 28372, 27687, 26718, 25483, 24012, 22335, 20479, 18483, 16382, 14207, 12000, 9798, 7631, 5539, 3550, 1695, -1,
		-1515, -2829, -3926, -4799, -5443, -5853, -6036, -5998, -5752, -5316, -4708, -3953, -3076, -2104, -1069, -1, 1065, 2099, 3071, 3948, 4704, 5312, 5749,
		5993, 6031, 5848, 5438, 4796, 3922, 2824, 1511, -2, -1699, -3554, -5543, -7636, -9801, -12005, -14211, -16384, -18487, -20484, -22340, -24017, -25487,
		-26722, -27691, -28377, -28759, -28823, -28560, -27969, -27045, -25799, -24240, -22380, -20244, -17856, -15240, -12433, -9468, -6380, -3211, -2, 3207,
		6375, 9463, 12428, 15236, 17850, 20239, 22375, 24235, 25794, 27040, 27964, 28556, 28818, 28755, 28372, 27687, 26718, 25483, 24012, 22335, 20479, 18483,
		16382, 14207, 12000, 9798, 7631, 5539, 3550, 1695, -1, -1515, -2829, -3926, -4799, -5443, -5853, -6036, -5998, -5752, -5316, -4708, -3953, -3076, -2104,
		-1069, -1, 1065, 2099, 3071, 3948, 4704, 5312, 5749, 5993, 6031, 5848, 5438, 4796, 3922, 2824, 1511, -2,
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
Oscillator osc1,osc2;

/**
 * LFO class instance
 */
LFO lfo;


/**
 * Unit test output buffer
 */
q15_t pMixOut[BUFF_SIZE];

/**
 * MIxer test
 */
void test_mix_out(void){

	/** Init oscillator with default settings */
	osc1.init(&synth_params.osc_params);
	/** Set shape */
	osc1.set_shape(SIN);
	synth_params.osc_params.mixAB = 0;

	/** Init oscillator with default settings */
	osc2.init(&synth_params.osc_params);

	/** Set shape */
	osc2.set_shape(SIN);
	osc2.set_freq_frac(2000);
	synth_params.osc_params.mixAB = MAX_AMP;

	/** Frame pointers  **/
	q15_t pOsc1[FRAME_SIZE];
	q15_t pOsc2[FRAME_SIZE];
	q15_t pMix[FRAME_SIZE];

	/** Mix parameter */
	q15_t mix_par = MAX_AMP>>1;

	/** Number of frames */
	uint8_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< _NFRAMES; i++){

		/** Get oscillator frames */
		osc1.get_frame(&synth_params,pOsc1,FRAME_SIZE);
		osc2.get_frame(&synth_params,pOsc2,FRAME_SIZE);

		/** Mix frames */
		mix_frames(&synth_params,pOsc1,pOsc2,pMix,mix_par);


		/** Store frames in outuput buffer */
		arm_copy_q15(pMix,&pMixOut[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_mix_out", pMixOut, BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_mix_ref,pMixOut,BUFF_SIZE);


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
    iprintf("\nTEST:  MIXER\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_mix_out);

    /** FInish unity */
    return UNITY_END();
}
