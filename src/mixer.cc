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
 * Mix two frames with a given mix parameter
 * @param synth_params 	Synth global structure
 * @param pFrame_a		Frame A to mix
 * @param pFrame_b 		Frame B to mix
 * @param pFrame_mix 	Destination mix frame
 * @param mix_par 		Mix parameter(0...0x7FFF), 0 ---> MIX A 100%, 0x7FFF ---> MIX B 100%,
 */
void Mixer::mix(synth_params_t *synth_params,q15_t* pFrame_a, q15_t* pFrame_b, q15_t* pFrame_mix , q15_t mix_par){


	q15_t *_pFrame_a = pFrame_a;			/* Frame A */
	q15_t *_pFrame_b = pFrame_b;			/* Frame B */
	q15_t *_pFrame_mix = pFrame_mix;		/* Mixed frame */
	q15_t _pFrame_mix_temp[FRAME_SIZE];		/* Intermediate calculation frame */

	arm_scale_q15(_pFrame_a,(MAX_AMP-mix_par),0,_pFrame_mix,FRAME_SIZE);
	arm_scale_q15(_pFrame_b,(mix_par),0,_pFrame_mix_temp,FRAME_SIZE);
	arm_add_q15(_pFrame_mix, _pFrame_mix_temp ,_pFrame_mix,FRAME_SIZE);



//	/* *****************************************************************************************
//	 * OSCILLATOR 1
//	 *
//	 * Compute oscillator1 modulations
//	 * *****************************************************************************************/
//	osc_mix = sample_osc1;
//	//osc_mix = mul_int16(osc_mix,synth_params->osc_mix);
//
//
////	// Modulate signal with the LFO
////	if(synth_params->lfo_dest == OSC1){
//	//		osc1_mix_temp = mul_int16(osc_mix,(MAX_AMP));
//	//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
//	//		osc_mix = mul_int16(osc_mix,synth_params->lfo_amo);
//	//		osc_mix += osc1_mix_temp;
//	//		osc_mix = osc1_mix_temp;
////	}
//
//	// Save temporal output
//	osc1_mix_temp = osc_mix;
//
//	/* *****************************************************************************************
//	 * OSCILLATOR 2
//	 *
//	 * Compute  oscillator2 modulations
//	 * *****************************************************************************************/
//
//	osc_mix = sample_osc2;
//	//osc_mix = mul_int16(osc_mix,(MAX_AMP-synth_params->osc_mix));
//
//
//	// Modulate signal with the LFO
//	if(synth_params->lfo_dest == OSC2){
//////		//osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
////		osc2_mix_temp = mul_int16(osc_mix,(MAX_AMP - lfo_amo));
//////		osc2_mix_temp = ((int32_t)((MAX_AMP)*(MAX_AMP - lfo_amo))>>15);
////		arm_mult_q15(pSrcA, pSrcB, pDst,1);
////		osc_mix = mul_int16(osc_mix,synth_params->lfo_amp);
////		osc_mix = mul_int16(osc_mix,synth_params->lfo_amo);
////		osc_mix += osc2_mix_temp;
//	}
//	osc_mix = mul_int16(osc_mix,(MAX_AMP-synth_params->osc_params.osc_mix));
//
//
//
//	/* *****************************************************************************************
//	 * OSC1/OSC2 MIXING
//	 *
//	 * Mix the the two next computed samples and apply ADSR Modulation.
//	 * *****************************************************************************************/
//
//	// Mix the two oscillators
//	osc_mix += osc1_mix_temp;
//
//	return osc_mix;
}
