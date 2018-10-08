/*
@file mixer_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 24, 2017
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

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

/**
 * MIxer unit test reference buffer
 */
q15_t buff_mix_ref[BUFF_SIZE] = { 6377, 12429, 17852, 22376, 25795, 27966, 28819, 28373, 26718, 24014, 20480, 16383, 12001, 7632, 3551, -1, -2829, -4799, -5853,
		-5998, -5316, -3953, -2103, -1, 2100, 3949, 5313, 5994, 5849, 4797, 2825, -2, -3554, -7635, -12004, -16384, -20484, -24017, -26722, -28377, -28823,
		-27969, -25799, -22380, -17856, -12433, -6380, -2, 6377, 12429, 17852, 22376, 25795, 27966, 28819, 28373, 26718, 24014, 20480, 16383, 12001, 7632, 3551,
		-1, -2829, -4799, -5853, -5998, -5316, -3953, -2103, -1, 2100, 3949, 5313, 5994, 5849, 4797, 2825, -2, -3554, -7635, -12004, -16384, -20484, -24017,
		-26722, -28377, -28823, -27969, -25799, -22380, -17856, -12433, -6380, -2, 6377, 12429, 17852, 22376, 25795, 27966, 28819, 28373, 26718, 24014, 20480,
		16383, 12001, 7632, 3551, -1, -2829, -4799, -5853, -5998, -5316, -3953, -2103, -1, 2100, 3949, 5313, 5994, 5849, 4797, 2825, -2, -3554, -7635, -12004,
		-16384, -20484, -24017, -26722, -28377, -28823, -27969, -25799, -22380, -17856, -12433, -6380, -2, 6377, 12429, 17852, 22376, 25795, 27966, 28819,
		28373, 26718, 24014, 20480, 16383, 12001, 7632, 3551, -1, -2829, -4799, -5853, -5998, -5316, -3953, -2103, -1, 2100, 3949, 5313, 5994, 5849, 4797, 2825,
		-2, -3554, -7635, -12004, -16384, -20484, -24017, -26722, -28377, -28823, -27969, -25799, -22380, -17856, -12433, -6380, -2, 6377, 12429, 17852, 22376,
		25795, 27966, 28819, 28373, 26718, 24014, 20480, 16383, 12001, 7632, 3551, -1, -2829, -4799, -5853, -5998, -5316, -3953, -2103, -1, 2100, 3949, 5313,
		5994, 5849, 4797, 2825, -2, -3554, -7635, -12004, -16384, -20484, -24017, -26722, -28377, -28823, -27969, -25799, -22380, -17856, -12433, -6380, -2,
		6377, 12429, 17852, 22376, 25795, 27966, 28819, 28373, 26718, 24014, 20480, 16383, 12001, 7632, 3551, -1, };


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
