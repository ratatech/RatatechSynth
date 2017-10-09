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
#include "ratatechSynth.h"
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
		9028,11015,4243,-5779,-11467,-8217,1354,9841,10473,2889,-7043,-11557,-7043,2889,10473,9841,1354,-8217,-11467,-5779,4243,11015,9028,0,-9210,-11196,
		-4425,5597,11286,8035,-1535,-10023,-18804,-5418,12110,20078,12110,-5418,-18804,-17689,-2869,14182,19918,9879,-7809,-19760,-16254,-638,15935,19440,
		7648,-10199,-20238,-14501,2390,17369,18484,5099,-12430,-20397,-12430,5099,18484,17369,3394,-19308,-26946,-13792,9972,25884,21217,0,-21642,-26310,
		-10609,13154,26521,18883,-3607,-23552,-25037,-7214,16125,26733,16337,-7214,-25037,-23552,-3820,18883,26521,13366,-10397,-26310,-21642,-849,25257,
		30814,12123,-16165,-32078,-22985,3788,27531,29299,8082,-19702,-32330,-19954,8082,29299,27531,4041,-22985,-32078,-16418,11871,30814,25257,0,-25763,
		-31320,-12629,15659,31572,22479,-4294,-28037,-30208,-8704,19455,32255,19711,-8704,-30208,-28416,-4608,22783,31999,16127,-12544,-31744,-26112,-1024,
		25599,31231,12287,-16384,-32512,-23552,3839,27903,29695,8191,-19968,-32767,-20224,8191,29695,27903,2778,-15804,-22056,-11289,8162,21187,17366,0,-17714,
		-21535,-8684,10767,21708,15629,-2953,-19277,-20493,-5905,13198,21881,13372,-5905,-20493,-19277,-3126,15456,21708,10940,-8510,-21535,-17714,-695,12799,
		15615,6143,-8192,-16256,-11776,1919,13951,14847,4095,-9984,-16383,-10112,4095,14847,13951,2047,-11648,-16256,-8320,6015,15615,12799,0,-13056,-15872,
		-6400,7935,15999,11519,-2176,-14208,-13277,-3826,8551,14176,8663,-3826,-13277,-12490,-2026,10013,14064,7088,-5514,-13952,-11477,-451,11251,13726,5400,
		-7201,-14290,-10352,1687,12264,13051,3600,-8777,-14402,-8889,3600,13051,12264,
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
	osc.set_freq_frac(14000);

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
		adsr.get_sample(&synth_params,&adsr_sample);

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
		adsr.get_sample(&synth_params,&adsr_sample);

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
