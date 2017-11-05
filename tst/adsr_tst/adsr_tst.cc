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
//#include "ratatechSynth.h"
#include "adsr.h"
#include "tst_utils.h"

/**
 * Size of reference and output buffers
 */
#define BUFF_SIZE 256

#define FRAME_SIZE_TEST 1

/**
 * ADSR envelope unit test reference buffer
 */
q15_t buff_adsr_env_out[BUFF_SIZE] = {
	7034,11161,10676,5777,-1509,-8172,-11458,-10009,-4424,2990,9167,11555,9167,2990,-4423,-10008,-11458,-8173,-1509,5777,10675,11161,7034,0,-7036,-11163,-10678,-5779,1507,8170,
	11456,10007,7804,-5280,-16182,-20397,-16182,-5280,7803,17661,20219,14421,2661,-10198,-18844,-19702,-12417,-1,12414,19699,18842,10196,-2663,-14423,-20221,-17664,-7807,5277,
	16179,20395,16179,5277,-7806,-17664,-26925,-19205,-3546,13575,25087,26228,16529,0,-16533,-26232,-25091,-13579,3543,19200,26920,23516,10391,-7030,-21545,-27158,-21545,-7030,
	10390,23515,26921,19201,3543,-13579,-25091,-26232,-16533,-1,19677,31223,29866,16161,-4221,-22861,-32051,-27998,-12374,8364,25644,32327,25644,8364,-12373,-27997,-32052,-22862,
	-4221,16161,29865,31223,19677,0,-19681,-31227,-29870,-16165,4217,22857,32047,27994,12537,-8481,-25995,-32767,-25995,-8481,12536,28372,32482,23167,4274,-16383,-30273,-31650,
	-19947,-1,19943,31646,30270,16379,-4278,-23170,-32485,-28377,-12541,8477,25991,32764,25991,8477,-12540,-28376,-22038,-15719,-2903,11111,20534,21468,13529,0,-13532,-21471,-20538,
	-11114,2900,15715,22034,19248,8505,-5754,-17635,-22229,-17635,-5754,8504,19247,22035,15716,2900,-11114,-20537,-21471,-13532,-1,9971,15822,15134,8189,-2139,-11585,-16242,-14188,
	-6271,4238,12995,16381,12995,4238,-6270,-14188,-16243,-11585,-2139,8189,15134,15822,9971,0,-9973,-15825,-15137,-8192,2137,11582,16240,14186,5510,-3728,-11426,-14402,-11426,-3728,
	5510,12470,14276,10182,1878,-7201,-13306,-13911,-8767,-1,8765,13909,13304,7199,-1881,-10184,-14278,-12473,-5512,3726,11423,14400,11423,3726,-5512,-12472,
};

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
void test_adsr_env_out(void){

	/** Pointer to ADSR envelope frame  **/
	q15_t pAdsr[FRAME_SIZE];

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	q15_t adsr_sample;

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(10000);
	synth_params.osc_params.mixAB = 0;

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 10;

	/** Init adsr */
	synth_params.adsr_params.sustain_level = MAX_AMP>>1;
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.base = adsr.base_att;

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	//TODO(JoH): Find better adsr params for frame based envelope
	adsr.beta_att = adsr_beta_exp_curve_q31[150];
	adsr.beta_dec = adsr_beta_exp_curve_q31[100];
	adsr.beta_rel = adsr_beta_exp_curve_q31[20];
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.beta = adsr.beta_att;
	adsr.base = adsr.base_att;

	/** Specify the total number of frames */
	uint16_t _NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get ADSR envelope frames */
	for(int i=0; i< _NFRAMES; i++){

		if(adsr.adsr_state == SUSTAIN_STATE){
			sustain_timeout--;
		}
		if(sustain_timeout<=0){
			synth_params.note_ON = false;
		}
		/** Get ADSR envelope frames */
		adsr_sample = adsr.get_sample(&synth_params);

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc,FRAME_SIZE);

		arm_scale_q15(pOsc,adsr_sample,0,pAdsr,FRAME_SIZE);


		/** Store frames in outuput buffer */
		arm_copy_q15(pAdsr,&pAdsr_out[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_adsr_env_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_adsr_env_out,pAdsr_out,BUFF_SIZE);

}

/**
 * ADSR test
 */
void test_adsr_out(void){

	/** Pointer to ADSR envelope frame  **/
	q15_t* pAdsr;

	q15_t adsr_sample;

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(14000);

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 30;

	/** Init adsr */
	synth_params.adsr_params.sustain_level = (q15_t)(float(MAX_AMP)*0.7);
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.adsr_state = ATTACK_STATE;
	adsr.beta_att = adsr_beta_exp_curve_q31[1500];	/** tau = 0.029188, fs = 3000Hz */
	adsr.beta_dec = adsr_beta_exp_curve_q31[1800];	/** tau = 0.057311, fs = 3000Hz */
	adsr.beta_rel = adsr_beta_exp_curve_q31[1500];	/** tau = 0.029188, fs = 3000Hz */
	synth_params.note_ON = true;
	adsr.set_base(&synth_params);
	adsr.beta = adsr.beta_att;
	adsr.base = adsr.base_att;


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
    RUN_TEST(test_adsr_env_out);
    RUN_TEST(test_adsr_out);

    /** FInish unity */
    return UNITY_END();
}
