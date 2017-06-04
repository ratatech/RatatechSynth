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
int32_t buff_adsr_ref[BUFF_SIZE] = {
		3679,6949,9855,12438,14734,16773,18586,20197,21629,22902,24032,25037,25931,26724,27430,28057,28614,29109,29549,29940,30287,30596,30871,31115,31331,
		31524,31695,31847,31983,32103,32210,32304,32389,32464,32530,32590,32642,32689,32731,32767,32032,31378,30796,30280,29821,29413,29050,28728,28442,28187,
		27961,27760,27581,27423,27281,27156,27045,26946,26858,26779,26710,26648,26593,26544,26501,26463,26428,26398,26371,26347,26325,26307,26290,26275,26261,
		26249,26239,26230,26221,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,
		26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,26214,
		26214,26214,26214,26214,25194,24213,23270,22364,21492,20654,19848,19074,18329,17613,16925,16263,15627,15015,14427,13861,13317,12795,12292,11809,11344,
		10898,10468,10056,9659,9277,8910,8557,8218,7892,7579,7277,6988,6709,6441,6184,5936,5698,5469,5249,5038,4834,4639,4451,4270,4096,3929,3768,3614,3465,3323,
		3185,3053,2926,2805,2687,2574,2466,2362,2262,2165,2073,1984,1898,1816,1737,1660,1587,1517,1449,1384,1322,1262,1204,1148,1095,1044,994,947,901,857,815,775,
		736,698,662,627,594,562,531,502,473,446,420,394,370,347,324,302,282,262,242,224,206,189,173,157,142,127,113,100,87,74,62,51,40,29,19,9,0,0,0,0,0,0,0,0,


};

/**
 * ADSR + OSC unit test reference buffer
 */
int32_t buff_adsr_osc_ref[BUFF_SIZE] = {
		3017,6297,1770,-8843,-14504,-6421,10019,19881,11659,-8768,-23657,-17800,4659,24218,22501,0,-23920,-26835,-5772,20817,29340,11234,-17124,-31115,-17379,
		11575,30704,22143,-6247,-29595,-26926,0,26569,29420,5845,-23170,-32132,-12514,17644,32255,17267,-12012,-30315,-21528,5358,26655,23830,0,-23776,-25985,
		-5462,19301,26719,10069,-15133,-27156,-15002,9894,26018,18619,-5217,-24567,-22231,0,21739,23982,4748,-18768,-25959,-10086,14190,25895,14171,-10059,-25851,
		-18662,4714,23770,21509,0,-21914,-24167,-5120,18226,25394,9625,-14541,-26214,-14541,9625,25394,18226,-5120,-24167,-21914,0,21503,23756,4710,-18637,-25805,
		-10036,14130,25804,14130,-10036,-25805,-18637,4710,23756,21503,0,-21914,-24167,-5120,18226,25394,9625,-14541,-26214,-14541,9625,25394,18226,-5120,-24167,
		-21914,0,21503,22832,4350,-16544,-22015,-8228,11133,19537,10282,-7017,-17338,-12033,2922,14161,12316,0,-11587,-12277,-2500,8546,11439,4165,-6045,-10468,
		-5578,3546,8987,6195,-1672,-7576,-6598,0,5969,6332,1205,-4580,-6088,-2273,3071,5383,2829,-1929,-4759,-3299,799,3869,3360,0,-3150,-3332,-677,2310,3085,1121,
		-1624,-2805,-1491,945,2388,1642,-442,-1996,-1733,0,1556,1645,312,-1181,-1563,-581,781,1362,712,-484,-1186,-817,196,946,815,0,-754,-791,-160,538,713,256,-368,-627,
		-330,206,514,349,-93,-412,-352,0,303,314,58,-215,-278,-101,130,220,111,-73,-171,-112,25,115,92,0,-73,-69,-13,35,38,10,-11,-9,0,0,0,0,0,0,0,0,


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
int32_t buff_out [BUFF_SIZE];

/** ADSR object instance*/
ADSREnv adsr_vol(LOG,EXP,EXP,0.009);

/**
 * ADSR test
 */
void test_adsr_out(void){

	/* *****************************************************************************************
	 *
	 * ADSR
	 *
	 * Configure ADSR. Values correspond for duration of the states in seconds except for
	 * the sustain which is the amplitude (substracted from 1, -1 corresponds to 1). Duration
	 * of the Decay and release states is calculated based on the amplitude of the sustain value.
	 * * *****************************************************************************************/
	// Volume envelope
	adsr_vol.attack  = 0.01;
	adsr_vol.decay   = 0.01;
	adsr_vol.sustain = 0.8;
	adsr_vol.release = 0.03;
	adsr_vol.calcAdsrSteps();
	adsr_vol.initStates();


	int32_t sample;

	/** Configure oscillator 1 */
	osc_shape_t shape_osc1 = SIN;
	osc.set_shape(shape_osc1);
	osc.set_freq_frac(1000);

	adsr_vol.note_ON = true;

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_tmo = 50;

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){
		if(adsr_vol.adsr_state == SUSTAIN_STATE){
			sustain_tmo--;
		}
		if(sustain_tmo<=0){
			adsr_vol.adsr_state = RELEASE_STATE;
		}
		adsr_vol.update();
		sample =  adsr_vol.adsr_amp;
		buff_out[i] = sample;
	}

	/** Print output buffer */
	printOutBuff("buff_adsr_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_adsr_ref,buff_out,BUFF_SIZE);

}

/**
 * ADSR + osc test
 */
void test_adsr_osc_out(void){

	/* *****************************************************************************************
	 *
	 * ADSR
	 *
	 * Configure ADSR. Values correspond for duration of the states in seconds except for
	 * the sustain which is the amplitude (substracted from 1, -1 corresponds to 1). Duration
	 * of the Decay and release states is calculated based on the amplitude of the sustain value.
	 * * *****************************************************************************************/
	// Volume envelope
	adsr_vol.attack  = 0.01;
	adsr_vol.decay   = 0.01;
	adsr_vol.sustain = 0.8;
	adsr_vol.release = 0.03;
	adsr_vol.calcAdsrSteps();
	adsr_vol.initStates();


	int32_t sample;

	/** Configure oscillator 1 */
	osc_shape_t shape_osc1 = SIN;
	osc.set_shape(shape_osc1);
	osc.set_freq_frac(15000);

	adsr_vol.note_ON = true;

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_tmo = 50;

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){
		sample =  osc.get_sample(&synth_params);

		if(adsr_vol.adsr_state == SUSTAIN_STATE){
			sustain_tmo--;
		}
		if(sustain_tmo<=0){
			adsr_vol.adsr_state = RELEASE_STATE;
		}
		adsr_vol.update();
		sample = ((int32_t)(sample)*(adsr_vol.adsr_amp)>>15);
		buff_out[i] = sample;
	}

	/** Print output buffer */
	printOutBuff("buff_adsr_osc_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_adsr_osc_ref,buff_out,BUFF_SIZE);

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
    RUN_TEST(test_adsr_osc_out);

    /** FInish unity */
    return UNITY_END();
}
