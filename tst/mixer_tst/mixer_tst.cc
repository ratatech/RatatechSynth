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
		17278,18302,19326,20478,21374,22398,23422,24318,25214,26110,27006,27774,28542,29182,29822,30334,30846,31230,31742,31998,32254,32382,32510,32510,32510,32382,32254,31998,
		31742,31230,30846,30334,29822,29182,28542,27774,27006,26110,25342,24446,23550,22526,21502,20478,19454,18430,17406,0,-17535,-18559,-19583,-20735,-21631,-22655,-23679,
		-24575,-25471,-26367,-27263,-28031,-28799,-29439,-30079,-30591,-31103,-31487,-31999,-32255,-32511,-32639,-32767,-32767,-32767,-32639,-32511,-32255,-31999,-31487,-31103,
		-30591,-30079,-29439,-28799,-28159,-27263,-26495,-25599,-24703,-23807,-22783,-21759,-20735,-19711,-18687,-17663,-16895,17278,18302,19326,20478,21374,22398,23422,24318,
		25214,26110,27006,27774,28542,29182,29822,30334,30846,31230,31742,31998,32254,32382,32510,32510,32510,32382,32254,31998,31742,31230,30846,30334,29822,29182,28542,27902,
		27006,26238,25342,24446,23550,22526,21502,20478,19454,18430,17406,0,-17535,-18559,-19583,-20735,-21631,-22655,-23679,-24575,-25471,-26367,-27263,-28031,-28799,-29439,
		-30079,-30591,-31103,-31487,-31999,-32255,-32511,-32639,-32767,-32767,-32767,-32639,-32511,-32255,-31999,-31487,-31103,-30591,-30207,-29439,-28799,-28159,-27263,-26495,
		-25599,-24703,-23807,-22783,-21759,-20735,-19711,-18687,-17663,-16895,17278,18302,19326,20478,21374,22398,23422,24318,25214,26110,27006,27774,28542,29182,29822,30334,
		30846,31230,31742,31998,32254,32382,32510,32510,32510,32382,32254,31998,31742,31358,30846,30334,29950,29182,28542,27902,27006,26238,25342,24446,23550,22526,21502,20478,
		19454,18430,17406,0,-17535,-18559,-19583,-20735,-21631,-22655,-23679,-24575,-25471,-26367,-27263,-28031,-28799,-29439,-30079,-30591,


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

/** Mixer object instance*/
Mixer mixer;

/**
 * MIxer test
 */
void test_mix_out(void){

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
		osc1.get_frame(&synth_params,pOsc1,FRAME_SIZE);
		osc2.get_frame(&synth_params,pOsc2,FRAME_SIZE);

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
