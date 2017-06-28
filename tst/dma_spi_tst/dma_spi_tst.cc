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
		25599,31231,12031,-16384,-32512,-23296,3839,27903,29695,8191,-19968,-32767,-19968,8191,29695,27903,3839,-23296,-32512,-16384,12031,31231,25599,
		0,-26112,-31744,-12544,15871,31999,22783,-4352,-28416,-28022,-7536,15814,24759,14181,-6056,-20162,-18278,-2869,13779,18867,9152,-7095,-17652,
		-14308,-554,13697,16551,6459,-8551,-16866,-12022,1972,14279,15145,4166,-10131,-16589,-10091,4133,14964,14044,2059,-11705,-16324,-8350,6033,15656,
		12827,0,-13077,-15894,-6408,7943,16012,11399,-2178,-14215,-15110,-4354,9730,16130,9857,-4353,-15106,-14209,-2305,11392,16000,8064,-6272,-15872,
		-13056,-512,12799,15615,6143,-8192,-16256,-11648,1919,13951,14847,4095,-9984,-16383,-10112,4095,14847,13951,2047,-11648,-16256,-8320,6015,15615,
		12799,0,-13056,-15872,-6400,7935,15999,11391,-2176,-14208,-14526,-4025,8652,13794,8106,-3443,-11491,-10395,-1621,7707,10411,5045,-3775,-9186,
		-7266,-275,6588,7729,2924,-3751,-7157,-4986,781,5462,5591,1483,-3478,-5487,-3257,1268,4423,3997,564,-3087,-4142,-2039,1417,3538,2789,0,-2632,
		-3077,-1193,1422,2757,1909,-347,-2179,-2228,-618,1326,2115,1242,-528,-1762,-1594,-249,1182,1595,773,-579,-1409,-1115,-42,1010,1184,448,-575,
		-1098,-765,119,837,857,227,-534,-841,-500,194,677,612,86,-473,-635,-313,217,542,427,0,-404,-472,-183,217,422,292,-54,-334,-342,-95,203,323,
		190,-81,-271,-244,-39,180,244,118,-89,-216,-171,-7,154,181,68,-88,-168,-118,18,127,131,34,-82,-129,-77,29,103,93,

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

	/** Pointer to oscillator frame  **/
	q15_t pOsc[FRAME_SIZE];

	int32_t sample;

	/** Init oscillator with default settings */
	osc.init(&synth_params.osc_params);

	/** Configure oscillator*/
	osc.set_freq_frac(14000);

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_timeout = 1;

	/** Init adsr */
	adsr.init(&synth_params);

	/** ADSR time params*/
	adsr.beta_att = 1453060120; /** tau = 0.01,  fs = 256Hz */
	adsr.beta_dec = 1836840104; /** tau = 0.025, fs = 256Hz */
	adsr.beta_rel = 2065214841; /** tau = 0.1,   fs = 256Hz */

	//adsr.target_level = 0x7fff;

	//beta = 2065214841; // tau = 0.1, fs=256hz


	/** Specify the total number of frames */
	uint8_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get ADSR envelope frames */
	for(int i=0; i< NFRAMES; i++){

		if(adsr.adsr_state == SUSTAIN_STATE){
			sustain_timeout--;
		}
		if(sustain_timeout<=0){
			adsr.note_ON = false;
		}
		/** Get ADSR envelope frames */
		adsr.get_frame(&synth_params,pAdsr);

		/** Get oscillator frames */
		osc.get_frame(&synth_params,pOsc);

		arm_mult_q15(pAdsr,pOsc,pAdsr,FRAME_SIZE);

		/** Store frames in outuput buffer */
		arm_copy_q15(pAdsr,&pAdsr_out[i*FRAME_SIZE],FRAME_SIZE);

	};

	/** Print output buffer */
	printOutBuff("buff_adsr_out", &pAdsr_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT16_ARRAY(buff_adsr_ref,pAdsr_out,BUFF_SIZE);

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
    iprintf("\nTEST:  ADSR\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(test_adsr_out);

    /** FInish unity */
    return UNITY_END();
}
