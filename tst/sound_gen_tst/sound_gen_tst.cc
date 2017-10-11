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
#define BUFF_SIZE 1024

#define FRAME_SIZE_TEST 1

/**
 * ADSR envelope unit test reference buffer
 */
q15_t buff_sound_gen_out[BUFF_SIZE] = {
		788,1564,2327,3079,3818,4545,5261,5965,6658,7339,8010,8670,9320,9959,10587,11206,11815,12414,13003,13583,14154,14715,15268,15811,16346,16872,17390,
		17900,18401,18894,19380,19857,20327,20790,21245,21693,22133,22567,22993,23413,23826,24232,24632,25025,25412,25793,26168,26536,26899,27256,27607,27953,
		28293,28628,28957,29281,29600,29914,30222,30526,30825,31119,31408,31693,31973,32248,32519,32767,32442,32120,31800,31484,31170,30858,30550,30244,29940,
		29639,29341,29046,28753,28462,28174,27889,27606,27325,27047,26771,26498,26227,25958,25691,25427,25166,24906,24649,24394,24141,23890,23641,23395,23151,
		22936,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,
		22909,22909,22909,22909,22909,22909,22278,21658,21048,20447,19856,19275,18703,18140,17586,17041,16505,15977,15458,14947,14444,13950,13463,12984,12513,
		12050,11593,11145,10703,10268,9841,9420,9006,8599,8198,7804,7416,7034,6658,6288,5925,5567,5215,4868,4527,4192,3861,3537,3217,2903,2593,2289,1989,1694,
		1404,1119,838,562,290,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,
		788,1564,2327,3079,3818,4545,5261,5965,6658,7339,8010,8670,9320,9959,10587,11206,11815,12414,13003,13583,14154,14715,15268,15811,16346,16872,17390,
		17900,18401,18894,19380,19857,20327,20790,21245,21693,22133,22567,22993,23413,23826,24232,24632,25025,25412,25793,26168,26536,26899,27256,27607,27953,
		28293,28628,28957,29281,29600,29914,30222,30526,30825,31119,31408,31693,31973,32248,32519,32767,32442,32120,31800,31484,31170,30858,30550,30244,29940,
		29639,29341,29046,28753,28462,28174,27889,27606,27325,27047,26771,26498,26227,25958,25691,25427,25166,24906,24649,24394,24141,23890,23641,23395,23151,
		22936,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,
		22909,22909,22909,22909,22909,22909,22278,21658,21048,20447,19856,19275,18703,18140,17586,17041,16505,15977,15458,14947,14444,13950,13463,12984,12513,
		12050,11593,11145,10703,10268,9841,9420,9006,8599,8198,7804,7416,7034,6658,6288,5925,5567,5215,4868,4527,4192,3861,3537,3217,2903,2593,2289,1989,1694,
		1404,1119,838,562,290,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,
		788,1564,2327,3079,3818,4545,5261,5965,6658,7339,8010,8670,9320,9959,10587,11206,11815,12414,13003,13583,14154,14715,15268,15811,16346,16872,17390,
		17900,18401,18894,19380,19857,20327,20790,21245,21693,22133,22567,22993,23413,23826,24232,24632,25025,25412,25793,26168,26536,26899,27256,27607,27953,
		28293,28628,28957,29281,29600,29914,30222,30526,30825,31119,31408,31693,31973,32248,32519,32767,32442,32120,31800,31484,31170,30858,30550,30244,29940,
		29639,29341,29046,28753,28462,28174,27889,27606,27325,27047,26771,26498,26227,25958,25691,25427,25166,24906,24649,24394,24141,23890,23641,23395,23151,
		22936,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,22909,
		22909,22909,22909,22909,22909,22909,22278,21658,21048,20447,19856,19275,18703,18140,17586,17041,16505,15977,15458,14947,14444,13950,13463,12984,12513,
		12050,11593,11145,10703,10268,9841,9420,9006,8599,8198,7804,7416,7034,6658,6288,5925,5567,5215,4868,4527,4192,3861,3537,3217,2903,2593,2289,1989,1694,
		1404,1119,838,562,290,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,
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
Oscillator osc1,osc2;

/**
 * Unit test output buffer
 */
q15_t pAdsr_out [BUFF_SIZE];


/** ADSR object instance*/
ADSR adsr;

/** Sound generator object instance*/
SoundGenerator snd_gen;

/** LFO object instance*/
LFO lfo;

/**
 * Sound generator test
 */
void test_sound_gen_out(void){

	/** Pointer to ADSR envelope frame  **/
	q15_t pAdsr[FRAME_SIZE];

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	q15_t adsr_sample;

	/** Put objects in the pool */
	object_pool.osc1 = 			&osc1;
	object_pool.osc2 = 			&osc2;
	object_pool.lfo = 			&lfo;
	object_pool.adsr = 			&adsr;

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init oscillator with default settings */
	osc1.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc1.set_freq_frac(10000);

	/** Init oscillator with default settings */
	osc2.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc2.set_freq_frac(5000);
	osc2.set_shape(SAW);

	/** Configure lfo */
	lfo.FM_synth = false;
	lfo.set_shape(SAW);
	lfo.set_freq_frac(300);


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
	adsr.beta_att = adsr_beta_exp_curve_q31[250];
	adsr.beta_dec = adsr_beta_exp_curve_q31[100];
	adsr.beta_rel = adsr_beta_exp_curve_q31[1000];
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


		/** Sound generation */
		snd_gen.gen_voice(&synth_params, pAdsr);


		/** Store frames in outuput buffer */
		arm_copy_q15(pAdsr,&pAdsr_out[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_sound_gen_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_sound_gen_out,pAdsr_out,BUFF_SIZE);

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
    iprintf("\nTEST:  SOUND GEN\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_sound_gen_out);

    /** FInish unity */
    return UNITY_END();
}
