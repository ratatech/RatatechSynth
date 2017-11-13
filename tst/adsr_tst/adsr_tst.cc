/*
@file adsr_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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
#include "adsr.h"
#include "tst_utils.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

#define FRAME_SIZE_TEST 1

/**
 * ADSR unit test reference buffer
 */
q15_t buff_adsr_out[BUFF_SIZE] = { 3189, 6062, 8803, 11418, 13912, 16291, 18561, 20726, 22791, 24761, 26640, 28433, 30143, 32767, 17035, 16383, 16383, 16383,
		16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383, 16383,
		16383, 16383, 16383, 16383, 16383, 16383, 16383, 16186, 15989, 15797, 15605, 15417, 15231, 15046, 14865, 14684, 14508, 14331, 14159, 13987, 13819,
		13651, 13486, 13324, 13162, 13003, 12845, 12691, 12537, 12386, 12236, 12088, 11942, 11797, 11655, 11513, 11375, 11237, 11101, 10967, 10834, 10703,
		10574, 10446, 10319, 10195, 10071, 9950, 9829, 9711, 9593, 9477, 9362, 9249, 9138, 9026, 8918, 8809, 8703, 8598, 8494, 8391, 8289, 8190, 8090, 7993,
		7895, 7800, 7706, 7613, 7520, 7430, 7340, 7251, 7163, 7076, 6991, 6906, 6823, 6740, 6659, 6578, 6498, 6419, 6341, 6265, 6189, 6114, 6040, 5967, 5895,
		5823, 5753, 5683, 5614, 5546, 5479, 5413, 5348, 5283, 5219, 5156, 5093, 5031, 4970, 4910, 4850, 4792, 4733, 4676, 4620, 4564, 4508, 4454, 4400, 4346,
		4294, 4241, 4190, 4139, 4089, 4040, 3991, 3942, 3895, 3848, 3800, 3755, 3709, 3664, 3619, 3576, 3532, 3489, 3447, 3405, 3364, 3323, 3283, 3243, 3204,
		3165, 3126, 3088, 3051, 3014, 2977, 2941, 2905, 2870, 2835, 2801, 2767, 2733, 2700, 2667, 2635, 2602, 2571, 2540, 2509, 2478, 2448, 2418, 2389, 2360,
		2331, 2303, 2275, 2247, 2220, 2193, 2166, 2140, 2114, 2088, 2063, 2038, 2013, 1988, 1964, 1940, 1916, 1893, 1870, 1847, 1824, 1802, 1780, 1759, 1737,
		1716, 1695, 1674, 1654, 1634, 1614, 1594, 1575, 1555, 1536, 1518, 1499, 1481, 1463, 1445, 1427, 1410, 1393, 1376, 1359, 1342, 1326, 1310, 1294, 1278,
		1262, };


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
q15_t pAdsr_out [BUFF_SIZE];


/** ADSR object instance*/
ADSR adsr;


/**
 * ADSR test
 */
void test_adsr_out(void){

	/** Pointer to ADSR envelope frame  **/
	q15_t* pAdsr;

	q15_t adsr_sample;

	/** Define number of samples to stay on sustain state*/
	int8_t sustain_timeout = 30;

	/** Init adsr */
	synth_params.adsr_params.sustain_level = (q15_t)(float(MAX_AMP)*0.5);
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	adsr.ph_inc_att = adsr_time_phinc_lut[2000];
	adsr.ph_inc_dec = adsr_time_phinc_lut[100];
	adsr.ph_inc_rel = adsr_time_phinc_lut[2300];
	synth_params.note_ON = true;
	adsr.ph_inc = adsr.ph_inc_att;
	adsr.pLut_interp->reset();

	/** Get ADSR envelope frames */
	for(int i=0; i< BUFF_SIZE; i++){

		if(adsr.adsr_state == SUSTAIN_STATE){
			sustain_timeout--;
		}
		if(sustain_timeout<=0){
			synth_params.note_ON = false;
		}

		/** Get ADSR envelope frames */
		adsr_sample = adsr.get_sample(&synth_params);

		/** Store frames in outuput buffer */
		arm_copy_q15(&adsr_sample,&pAdsr_out[i],1);

	};

	/** Print output buffer */
	printOutBuff("buff_adsr_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_adsr_out,pAdsr_out,BUFF_SIZE);

}

int main(void)
{

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST:  ADSR\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_adsr_out);

    /** FInish unity */
    return UNITY_END();
}
