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
int32_t buff_mix_ref[BUFF_SIZE] = {
		1710,2986,3888,60793,60371,60431,4574,4339,4056,61207,61825,62248,2127,1671,1286,63901,64089,64287,64382,117,119,239,64093,63842,63349,1848,2353,
		2986,60844,60085,58953,6688,7592,8624,9785,53361,52212,51061,14832,16000,17268,46816,46097,45259,20269,21371,22015,42321,41787,41241,40468,25049,
		25427,25817,38980,38579,27035,26736,26753,38757,26291,26331,26481,26026,25570,25016,24570,41057,41691,42320,21801,20964,20231,45617,46536,47756,
		16297,15369,14442,51409,52719,53626,54533,9319,8499,7271,58364,59170,59876,4199,3277,2663,62597,63101,63504,717,512,307,205,64613,64613,64512,410,
		615,1024,63202,62799,62295,3072,3687,4608,59372,58666,57860,56952,9114,10035,10957,53021,52114,50804,15053,15974,16998,47175,45965,45159,20685,
		21402,22118,23040,41429,40925,40421,25088,25600,25805,26003,25902,25802,39322,26112,25907,39413,39817,40321,40724,23859,23245,22630,43345,44151,
		44857,19354,18432,17203,48687,49594,50501,13517,12186,11264,10343,55541,56348,57557,6451,5632,4915,60581,61488,62093,2151,1639,1229,64008,64210,
		64412,64512,103,103,205,64311,64109,63706,1536,1946,2458,61690,61085,60178,5427,6144,6963,7885,55743,54836,53928,11879,12800,14131,49897,48989,47981,
		17818,19046,19866,44353,43647,42941,42034,23654,24166,24678,40018,39514,26205,26010,26112,39322,25802,25902,26104,25702,25293,24781,24371,41228,
		41833,42437,21709,20890,20173,45663,46570,47780,16282,15360,14438,51409,52719,53626,54533,9319,8499,7271,58364,59170,59876,4199,3277,2663,62597,
	    63101,63504,717,


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
int32_t buff_out [BUFF_SIZE];

/** ADSR object instance*/
ADSREnv adsr_vol(LOG,EXP,EXP,0.009);

/** ADSR object instance*/
Mixer mixer;

/**
 * MIxer test
 */
void test_mix_out(void){

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


	int32_t sample_osc1,sample_osc2,sample_lfo;

	/** Configure oscillator 1 */
	osc_shape_t shape_osc1 = SIN;
	osc1.set_shape(shape_osc1);
	osc1.set_freq_frac(100);

	/** Configure oscillator 2 */
	osc_shape_t shape_osc2 = SQU;
	osc2.set_shape(shape_osc2);
	osc2.set_freq_frac(15000);

	/** Mix Parameter between osc1 and osc2
	 *
	 * synth_params.osc_mix = 32768;
	 * 0x0000 Mix 100% Osc2
	 * 0x Mix 100% Osc1
	 * 0x3FFF Mix 50%
	 *
	 * */
	synth_params.osc_mix = 0x0;

	/** Configure lfo */
	osc_shape_t shape_lfo = SIN;
	lfo.FM_synth = false;
	lfo.set_shape(shape_lfo);
	lfo.set_freq_frac(50);
	lfo.lfo_amo = 0x3FFF;
	synth_params.lfo_dest = OSC2;

	/** Trigger note from the start to go on ATTACK state */
	adsr_vol.note_ON = true;

	/** Define number of samples to stay on sustain state*/
	uint8_t sustain_tmo = 1000;

	/** Mixer variables */
	int32_t osc_mix,osc1_mix_temp,osc2_mix_temp;

	/** Get oscillator samples */
	for(int i=0; i<BUFF_SIZE; i++){


		if(adsr_vol.adsr_state == SUSTAIN_STATE){
			sustain_tmo--;
		}
		if(sustain_tmo<=0){
			adsr_vol.adsr_state = RELEASE_STATE;
		}

		/** Update ADSR,OSCs and LFO */
		sample_osc1 =  osc1.get_sample(&synth_params);
		sample_osc2 =  osc2.get_sample(&synth_params);
		sample_lfo =  lfo.get_sample(&synth_params);
		adsr_vol.update();

		/** Mix samples */
		osc_mix = mixer.mix(sample_osc1,sample_osc2,&synth_params);

		/** Mini VCA */
		osc_mix = mul_int16(osc_mix,adsr_vol.adsr_amp);

		buff_out[i] = osc_mix;
	}

	/** Print output buffer */
	printOutBuff("buff_mix_out", &buff_out[0], BUFF_SIZE);

	/** Compare output vs reference */
	TEST_ASSERT_EQUAL_INT32_ARRAY(buff_mix_ref,buff_out,BUFF_SIZE);

}

int main(void)
{

	/** System init */
	RCC_ClocksTypeDef RCC_Clocks;
	SystemInit();
	RCC_Clocks_Init();
	SystemCoreClockUpdate();

	/** SysTick end of count event each 1ms */
	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

    /** Configure and init peripherals  */
	GPIO_Conf_Init();
	USART_Conf_Init();

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
    RUN_TEST(test_mix_out);

    /** FInish unity */
    return UNITY_END();
}
