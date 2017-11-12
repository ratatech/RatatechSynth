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
q15_t buff_adsr_out[BUFF_SIZE] = {
		788,1564,2327,3079,3818,4545,5261,5965,6658,7339,8010,8670,9320,9959,10587,11206,11815,12414,13003,13583,14154,14715,15268,15811,16346,16872,17390,
		17900,18401,18894,19380,19857,20327,20790,21245,21693,22133,22567,22993,23413,23826,24232,24632,25025,25412,25793,26168,26536,26899,27256,27607,27953,
		28293,28628,28957,29281,29600,29914,30222,30526,30825,31119,31408,31693,31973,32248,32519,32767,32442,32120,31800,31484,31170,30858,30550,30244,29940,
		29639,29341,29046,28753,28462,28174,27889,27606,27325,27047,26771,26498,26227,25958,25691,25427,25166,24906,24649,24394,24141,23890,23641,23395,23151,
		22936,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,
		22909,22909,22909,22909,22909,22909,22278,21658,21048,20447,19856,19275,18703,18140,17586,17041,16505,15977,15458,14947,14444,13950,13463,12984,12513,
		12050,11593,11145,10703,10268,9841,9420,9006,8599,8198,7804,7416,7034,6658,6288,5925,5567,5215,4868,4527,4192,3861,3537,3217,2903,2593,2289,1989,1694,
		1404,1119,838,562,290,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,
};

/**
 * Midi note status indicator
 */
q15_t midi_note_ON[BUFF_SIZE] = {
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,
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
	adsr.ph_inc_att = adsr_time_phinc_lut[30];
	adsr.ph_inc_dec = adsr_time_phinc_lut[50];
	adsr.ph_inc_rel = adsr_time_phinc_lut[100];
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
//		if(i == 15	){
//			synth_params.note_ON = false;
//		}
//		if(i == 50){
//			synth_params.note_ON = true;
//			adsr.reset();
//		}


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
