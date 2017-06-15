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

/**
 * ADSR unit test reference buffer
 */
q15_t buff_adsr_ref[BUFF_SIZE] = {
		1255,2462,3623,4739,5813,6846,7839,8794,9712,10595,11445,12261,13047,13802,14529,15228,15899,16546,17167,17765,18339,18892,19424,19935,
		20426,20899,21354,21791,22211,22616,23005,23379,23738,24084,24417,24737,25044,25340,25625,25898,26161,26414,26658,26892,27117,27333,27541,
		27742,27934,28119,28297,28468,28633,28791,28944,29090,29231,29366,29497,29622,29742,29858,29970,30077,30180,30279,30374,30466,30554,30639,
		30720,30799,30874,30947,31016,31083,31148,31210,31269,31327,31382,31435,31486,31535,31582,31628,31671,31713,31754,31792,31830,31866,31900,
		31933,31965,31996,32025,32054,32081,32107,32133,32157,32180,32203,32224,32245,32265,32284,32303,32321,32338,32354,32370,32385,32400,32414,
		32427,32440,32453,32465,32476,32487,32498,32508,32518,32528,32537,32546,32554,32562,32570,32578,32585,32592,32599,32605,32611,32617,32623,
		32628,32634,32639,32644,32648,32653,32657,32661,32665,32669,32673,32677,32680,32683,32687,32690,32693,32695,32698,32701,32703,32706,32708,
		32710,32712,32714,32716,32718,32720,32722,32724,32725,32727,32728,32730,32731,32733,32734,32735,32736,32738,32739,32740,32741,32742,32743,
		32744,32744,32745,32746,32747,32748,32748,32749,32750,32750,32751,32752,32752,32753,32753,32754,32754,32755,32755,32756,32756,32756,32757,
		32757,32758,32758,32758,32759,32759,32759,32759,32760,32760,32760,32760,32761,32761,32761,32761,32762,32762,32762,32762,32762,32762,32763,
		32763,32763,32763,32763,32763,32763,32763,32764,32764,32764,32764,32764,32764,32764,32764,32764,32764,32765,32765,32765,32765,32765,32765,
		32765,32765,


};

/**
 * ADSR + OSC unit test reference buffer
 */
q15_t buff_adsr_osc_ref[BUFF_SIZE] = {
		1255,2462,3623,4739,5813,6846,7839,8794,9712,10595,11445,12261,13047,13802,14529,15228,15899,16546,17167,17765,18339,18892,19424,19935,
		20426,20899,21354,21791,22211,22616,23005,23379,23738,24084,24417,24737,25044,25340,25625,25898,26161,26414,26658,26892,27117,27333,27541,
		27742,27934,28119,28297,28468,28633,28791,28944,29090,29231,29366,29497,29622,29742,29858,29970,30077,30180,30279,30374,30466,30554,30639,
		30720,30799,30874,30947,31016,31083,31148,31210,31269,31327,31382,31435,31486,31535,31582,31628,31671,31713,31754,31792,31830,31866,31900,
		31933,31965,31996,32025,32054,32081,32107,32133,32157,32180,32203,32224,32245,32265,32284,32303,32321,32338,32354,32370,32385,32400,32414,
		32427,32440,32453,32465,32476,32487,32498,32508,32518,32528,32537,32546,32554,32562,32570,32578,32585,32592,32599,32605,32611,32617,32623,
		32628,32634,32639,32644,32648,32653,32657,32661,32665,32669,32673,32677,32680,32683,32687,32690,32693,32695,32698,32701,32703,32706,32708,
		32710,32712,32714,32716,32718,32720,32722,32724,32725,32727,32728,32730,32731,32733,32734,32735,32736,32738,32739,32740,32741,32742,32743,
		32744,32744,32745,32746,32747,32748,32748,32749,32750,32750,32751,32752,32752,32753,32753,32754,32754,32755,32755,32756,32756,32756,32757,
		32757,32758,32758,32758,32759,32759,32759,32759,32760,32760,32760,32760,32761,32761,32761,32761,32762,32762,32762,32762,32762,32762,32763,
		32763,32763,32763,32763,32763,32763,32763,32764,32764,32764,32764,32764,32764,32764,32764,32764,32764,32765,32765,32765,32765,32765,32765,
		32765,32765,

};


/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

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
	q15_t pAdsr[FRAME_SIZE];

	int32_t sample;

	/** Configure oscillator 1 */
	osc_shape_t shape_osc1 = SIN;
	osc.set_shape(shape_osc1);
	osc.set_freq_frac(1000);

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 50;

	/** Init adsr */
	adsr.init(&synth_params);

	//adsr.target_level = 0x7fff;

	//beta = 2065214841; // tau = 0.1, fs=256hz

//	/** Get oscillator samples */
//	for(int i=0; i<BUFF_SIZE; i++){
//		if(adsr.adsr_state == SUSTAIN_STATE){
//			sustain_timeout--;
//		}
//		if(sustain_timeout<=0){
//			adsr.adsr_state = RELEASE_STATE;
//		}
//		adsr.update_states(&synth_params);
//		adsr_out[i] = sample;
//	}
//
	/** Specify the total number of frames */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get ADSR envelope frames */
	for(int i=0; i< NFRAMES; i++){

		adsr.get_frame(&synth_params,pAdsr);

		/** Store frames in outuput buffer */
		arm_copy_q15(pAdsr,&pAdsr_out[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_adsr_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_adsr_ref,pAdsr_out,BUFF_SIZE);

}

///**
// * ADSR + osc test
// */
//void test_adsr_osc_out(void){
//
//	/* *****************************************************************************************
//	 *
//	 * ADSR
//	 *
//	 * Configure ADSR. Values correspond for duration of the states in seconds except for
//	 * the sustain which is the amplitude (substracted from 1, -1 corresponds to 1). Duration
//	 * of the Decay and release states is calculated based on the amplitude of the sustain value.
//	 * * *****************************************************************************************/
//	// Volume envelope
//	adsr_vol.attack  = 0.01;
//	adsr_vol.decay   = 0.01;
//	adsr_vol.sustain = 0.8;
//	adsr_vol.release = 0.03;
//	adsr_vol.calcAdsrSteps();
//	adsr_vol.initStates();
//
//
//	int32_t sample;
//
//	/** Configure oscillator 1 */
//	osc_shape_t shape_osc1 = SIN;
//	osc.set_shape(shape_osc1);
//	osc.set_freq_frac(15000);
//
//	adsr_vol.note_ON = true;
//
//	/** Define number of samples to stay on sustain state*/
//	uint8_t sustain_tmo = 50;
//
//	/** Get oscillator samples */
//	for(int i=0; i<BUFF_SIZE; i++){
//		sample =  osc.get_sample(&synth_params);
//
//		if(adsr_vol.adsr_state == SUSTAIN_STATE){
//			sustain_tmo--;
//		}
//		if(sustain_tmo<=0){
//			adsr_vol.adsr_state = RELEASE_STATE;
//		}
//		adsr_vol.update();
//		sample = ((int32_t)(sample)*(adsr_vol.adsr_amp)>>15);
//		buff_out[i] = sample;
//	}
//
//	/** Print output buffer */
//	printOutBuff("buff_adsr_osc_out", &buff_out[0], BUFF_SIZE);
//
//	/** Compare output vs reference */
//	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_adsr_osc_ref,buff_out,BUFF_SIZE);
//
//}

int main(void)
{

	/** Init system and peripherals */
	ratatech_init();

	/** Load initial default settings */
	init_settings(&synth_params);

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
    //RUN_TEST(test_adsr_osc_out);

    /** FInish unity */
    return UNITY_END();
}
