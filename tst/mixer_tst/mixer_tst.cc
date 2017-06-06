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
q15_t buff_mix_ref[BUFF_SIZE] = {
		-15487,-14463,-13439,-12287,-11391,-10367,-9343,-8447,-7551,-6655,-5759,-4991,-4223,-3583,-2943,-2431,-1919,-1535,-1023,-767,-511,
		-383,-255,-255,-255,-383,-511,-767,-1023,-1535,-1919,-2431,-2943,-3583,-4223,-4991,-5759,-6655,-7423,-8319,-9215,-10239,-11263,-12287,
		-13311,-14335,-15359,16127,14975,13951,12927,11775,10879,9855,8831,7935,7039,6143,5247,4479,3711,3071,2431,1919,1407,1023,511,255,-1,
		-129,-257,-257,-257,-129,-1,255,511,1023,1407,1919,2431,3071,3711,4351,5247,6015,6911,7807,8703,9727,10751,11775,12799,13823,14847,
		15743,-15487,-14463,-13439,-12287,-11391,-10367,-9343,-8447,-7551,-6655,-5759,-4991,-4223,-3583,-2943,-2431,-1919,-1535,-1023,-767,
		-511,-383,-255,-255,-255,-383,-511,-767,-1023,-1535,-1919,-2431,-2943,-3583,-4223,-4863,-5759,-6527,-7423,-8319,-9215,-10239,-11263,
		-12287,-13311,-14335,-15359,16127,14975,13951,12927,11775,10879,9855,8831,7935,7039,6143,5247,4479,3711,3071,2431,1919,1407,1023,511,
		255,-1,-129,-257,-257,-257,-129,-1,255,511,1023,1407,1919,2303,3071,3711,4351,5247,6015,6911,7807,8703,9727,10751,11775,12799,13823,
		14847,15743,-15487,-14463,-13439,-12287,-11391,-10367,-9343,-8447,-7551,-6655,-5759,-4991,-4223,-3583,-2943,-2431,-1919,-1535,-1023,
		-767,-511,-383,-255,-255,-255,-383,-511,-767,-1023,-1407,-1919,-2431,-2815,-3583,-4223,-4863,-5759,-6527,-7423,-8319,-9215,-10239,
		-11263,-12287,-13311,-14335,-15359,16127,14975,13951,12927,11775,10879,9855,8831,7935,7039,6143,5247,4479,3711,3071,2431,1919,
};


/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

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

/** ADSR object instance*/
ADSREnv adsr_vol(LOG,EXP,EXP,0.009);

/** ADSR object instance*/
Mixer mixer;

/**
 * MIxer test
 */
void test_mix_out(void){

	/** Load initial default settings */
	init_settings(&synth_params);

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
//	int32_t sample_osc1,sample_osc2,sample_lfo;
//
	/** Init oscillator with default settings */
	osc1.init(&synth_params.osc_params);
	/** Set shape */
	osc1.set_shape(SIN);

	/** Init oscillator with default settings */
	osc2.init(&synth_params.osc_params);

	/** Set shape */
	osc2.set_shape(SQU);


	/** Frame pointers  **/
	q15_t pOsc1[FRAME_SIZE];
	q15_t pOsc2[FRAME_SIZE];
	q15_t pMix[FRAME_SIZE];

	/** Mix parameter */
	q15_t mix_par = MAX_AMP>>1;

	/** Number of frames */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get oscillator samples */
	for(int i=0; i< NFRAMES; i++){

		/** Get oscillator frames */
		osc1.get_frame(&synth_params,pOsc1);
		osc2.get_frame(&synth_params,pOsc2);

		/** Mix frames */
		mixer.mix(&synth_params,pOsc1,pOsc2,pMix,mix_par);

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
    iprintf("\nTEST:  MIXER\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_mix_out);

    /** FInish unity */
    return UNITY_END();
}
