/*
@file adsr_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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
q15_t buff_adsr_out[BUFF_SIZE] = {207,238,269,299,330,361,392,423,454,485,516,546,577,607,638,668,699,730,760,791,822,853,883,914,945,975,1006,1036,1067,1097,
1127,1158,1188,1219,1249,1279,1310,1340,1371,1401,1431,1461,1492,1522,1552,1582,1612,1643,1673,1703,1733,1764,1794,1824,1854,1884,1915,1945,1975,2005,2035,
2065,2095,2125,2155,2184,2214,2244,2274,2304,2334,2364,2393,2423,2453,2483,2513,2543,2573,2603,2632,2662,2692,2721,2751,2781,2810,2840,2870,2899,2929,2959,
2988,3018,3047,3077,3106,3136,3165,3195,3224,3254,3283,3313,3342,3371,3401,3430,3459,3489,3518,3547,3577,3606,3635,3665,3694,3723,3752,3781,3810,3840,3869,
3898,3927,3956,3985,4015,4044,4073,4102,4131,4160,4189,4218,4247,4276,4305,4334,4363,4391,4420,4449,4478,4507,4536,4565,4594,4623,4652,4680,4709,4737,4766,
4795,4824,4852,4881,4910,4939,4967,4996,5024,5053,5081,5110,5138,5167,5196,5224,5253,5282,5310,5339,5367,5395,5424,5452,5481,5509,5537,5565,5594,5622,5650,
5679,5707,5735,5764,5792,5820,5848,5877,5905,5933,5961,5989,6018,6046,6074,6102,6130,6158,6186,6214,6242,6270,6298,6326,6354,6382,6410,6438,6466,6494,6522,
6550,6578,6606,6633,6661,6689,6717,6744,6772,6800,6828,6855,6883,6911,6939,6966,6994,7022,7050,7077,7105,7133,7160,7188,7215,7243,7270,7298,7326,7353,7381,
7408,7436,7463,7490,7518,7545,7573,7600,7627,};


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
