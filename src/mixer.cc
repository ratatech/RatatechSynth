/*
@file mixer.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 25, 2017
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

#include "mixer.h"

using namespace std;

/**
 *  Mix samples
 * @param sample_osc1 Oscillator 1 sample
 * @param sample_osc2 Oscillator 2 sample
 * @param synth_params Synth global structure
 * @return mix_out The mixed output sample
 */
int32_t Mixer::mix(int32_t sample_osc1,int32_t sample_osc2,synth_params_t *synth_params){


	int16_t lfo_amo = synth_params->lfo_amo;
	  q15_t  pSrcA[3];
	  q15_t  pSrcB[3];
	  q15_t  pDst[3];
	/* *****************************************************************************************
	 * OSCILLATOR 1
	 *
	 * Compute oscillator1 modulations
	 * *****************************************************************************************/
	osc_mix = sample_osc1;
	//osc_mix = mul_int16(osc_mix,synth_params->osc_mix);


//	// Modulate signal with the LFO
//	if(synth_params->lfo_dest == OSC1){
	//		osc1_mix_temp = mul_int16(osc_mix,(MAX_AMP));
	//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
	//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amo);
	//		osc_mix += osc1_mix_temp;
	//		osc_mix = osc1_mix_temp;
//	}

	// Save temporal output
	osc1_mix_temp = osc_mix;

	/* *****************************************************************************************
	 * OSCILLATOR 2
	 *
	 * Compute  oscillator2 modulations
	 * *****************************************************************************************/

	osc_mix = sample_osc2;
	//osc_mix = mul_int16(osc_mix,(MAX_AMP-synth_params->osc_mix));


	// Modulate signal with the LFO
	if(synth_params->lfo_dest == OSC2){
////		//osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
//		osc2_mix_temp = mul_int16(osc_mix,(MAX_AMP - lfo_amo));
////		osc2_mix_temp = ((int32_t)((MAX_AMP)*(MAX_AMP - lfo_amo))>>15);
		arm_mult_q15(pSrcA, pSrcB, pDst,1);
//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amo);
//		osc_mix += osc2_mix_temp;
	}
	osc_mix = mul_int16(osc_mix,(MAX_AMP-synth_params->osc_params.osc_mix));



	/* *****************************************************************************************
	 * OSC1/OSC2 MIXING
	 *
	 * Mix the the two next computed samples and apply ADSR Modulation.
	 * *****************************************************************************************/

	// Mix the two oscillators
	osc_mix += osc1_mix_temp;

	return osc_mix;
}
