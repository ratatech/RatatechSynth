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
		14153,17266,6651,-9058,-17975,-12880,2122,15426,16417,4529,-11040,-18116,-11040,4529,16417,15426,2122,-12880,-17975,-9058,6651,17266,14153,
		0,-14437,-17550,-6936,8774,17691,12596,-2407,-15710,-25008,-7206,16106,26703,16106,-7206,-25008,-23525,-3815,18861,26491,13139,-10385,-26280,
		-21617,-848,21192,25855,10172,-13564,-26916,-19286,3178,23100,24583,6781,-16531,-27127,-16531,6781,24583,23100,3951,-22473,-31363,-16052,11606,
		30127,24694,0,-25189,-30622,-12348,15310,30868,21978,-4199,-27411,-29140,-8397,18767,31115,19014,-8397,-29140,-27411,-4446,21978,30868,15557,
		-12101,-30622,-25189,-988,25599,31231,12287,-16384,-32512,-23296,3839,27903,29695,8191,-19968,-32767,-20224,8191,29695,27903,4095,-23296,-32512,
		-16640,12031,31231,25599,0,-26112,-31744,-12800,15871,31999,22783,-4352,-28416,-17502,-5043,11272,18688,11420,-5043,-17502,-16464,-2670,13200,
		18540,9344,-7268,-18392,-15129,-594,14832,18095,7119,-9493,-18837,-13646,2224,16166,17205,4746,-11569,-18985,-11718,4746,17205,16166,2047,-11648,
		-16256,-8320,6015,15615,12799,0,-13056,-15872,-6400,7935,15999,11519,-2176,-14208,-15104,-4352,9727,16127,9855,-4352,-15104,-14208,-2304,11391,
		15999,8063,-6272,-15872,-13056,-512,9392,11458,4508,-6011,-11929,-8641,1408,10237,10894,3005,-7326,-12022,-7420,3005,10894,10237,1502,-8547,
		-11929,-6105,4414,11458,9392,0,-9581,-11647,-4697,5823,11740,8452,-1597,-10426,-11083,-3194,7138,11834,7231,-3194,-11083,-10426,-1691,8359,11740,
		5917,-4603,-11647,-9581,-376,9392,11458,4508,-6011,-11929,-8641,1408,10237,10894,3005,-7326,-12022,-7420,3005,10894,10237,
};

/**
 * ADSR unit test reference buffer
 */
q15_t buff_adsr_out[BUFF_SIZE] = {
		973,1921,2842,3739,4612,5461,6287,7091,7873,8634,9375,10095,10796,11478,12142,12787,13416,14027,14622,15200,15763,16311,16844,17363,17868,
		18359,18836,19301,19753,20193,20622,21038,21444,21838,22222,22595,22958,23312,23656,23991,24316,24633,24941,25241,25533,25817,26093,26362,
		26624,26878,27126,27367,27601,27829,28051,28267,28477,28681,28880,29074,29262,29445,29624,29797,29966,30130,30290,30445,30596,30744,30887,
		31026,31162,31294,31422,31547,31668,31786,31901,32013,32122,32228,32331,32432,32529,32624,32717,32767,32427,32091,31760,31434,31112,30795,
		30482,30173,29868,29568,29272,28980,28692,28408,28128,27852,27580,27311,27046,26785,26528,26274,26023,25776,25533,25293,25056,24822,24592,
		24365,24141,23920,23702,23487,23275,23066,22936,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,
		22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22860,22154,21467,20799,20148,19516,18900,18301,17718,
		17151,16599,16062,15540,15031,14537,14056,13587,13132,12689,12257,11838,11429,11032,10646,10269,9903,9547,9201,8864,8536,8217,7906,7604,7310,
		7024,6746,6475,6212,5955,5706,5463,5227,4998,4774,4557,4345,4139,3939,3744,3554,3370,3190,3015,2845,2680,2519,2362,2210,2062,1918,1777,1641,
		1508,1379,1253,1130,1011,896,783,673,566,463,362,263,168,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

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


	/** Specify the total number of frames */
	uint16_t NFRAMES = BUFF_SIZE/FRAME_SIZE;

	/** Get ADSR envelope frames */
	for(int i=0; i< NFRAMES; i++){

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
