/*
@file adsr.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 14, 2017
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

#include "adsr.h"
#include "tst_utils.h"

using namespace std;

/**
 * Get a new adsr envelope frame
 * @param synth_params 	Synth global structure
 * @param pAdsr 		ADSR envelope output buffer
 * @param block_size 	Number of samples in the vector
 */
void ADSR::get_frame(synth_params_t *synth_params, q15_t* pAdsr,uint32_t block_size)
{

	q15_t * pOut = pAdsr;	/** Output pointer */
	q15_t adsr_sample;		/** Temp var */

	/** Update note on status*/
	note_ON = synth_params->note_ON;

	/** Whenever not in sustain or idle state, process frame */
	if((adsr_state != SUSTAIN_STATE) && (adsr_state != IDLE_STATE)){

		for(uint i=0;i<block_size;i++){
			adsr_sample = update();
			*pOut++ = adsr_sample;
		}
	}

	/** Update states */
	switch(adsr_state){

		case ATTACK_STATE:

			if (adsr_sample >= target_level_att){
				beta = beta_dec;
		        base = base_dec;
				adsr_state = DECAY_STATE;

			}

		break;

		case DECAY_STATE:

			if (adsr_sample <= target_level_dec){
				beta = beta_rel;
		        base = base_rel;
				adsr_state = SUSTAIN_STATE;
			}

		break;

		case SUSTAIN_STATE:
			if (note_ON == false){
				adsr_state = RELEASE_STATE;
			}

		break;

		case RELEASE_STATE:

			if (adsr_sample <= 0){
				/** End of ADSR envelope Already set level and coeff for a possible new attack state. Remain on idle state */
				beta = beta_att;
		        base = base_att;
				adsr_state = IDLE_STATE;
				adsr_sample = 0;

			}

		break;
	}

}

/**
 * Reset internal variables and go back to attack state
 */
void ADSR::reset(void)
{
	target_level = MAX_AMP;
	adsr_state = ATTACK_STATE;
	note_ON = true;
	beta = beta_att;
}

void ADSR::set_base(synth_params_t *synth_params){

	int64_t x64;
	q31_t x32;

	x64 = (int64_t)(INT32_MAX + ratio);
	x32 = (INT32_MAX - beta_att);
	x64 = x64 * x32;
	base_att = (q31_t)(x64>>31);


	x64 = (int64_t)(((q31_t)sustain_level<<15) - ratio);
	x32 = (INT32_MAX - beta_dec);
	x64 = x64 * x32;
	base_dec = (q31_t)(x64>>31);


	x64 = (int64_t)(ratio);
	x32 = (INT32_MAX - beta_rel);
	x64 = x64 * x32;
	base_rel = -(q31_t)(x64>>31);


}

/** Get the newly read values from the ADC and set the coefficients */
void ADSR::set_params(synth_params_t *synth_params){

	beta_att = adsr_beta_exp_curve_q31[synth_params->pMux[0]];
	beta_dec = adsr_beta_exp_curve_q31[synth_params->pMux[1]];
	beta_rel = adsr_beta_exp_curve_q31[synth_params->pMux[3]];

	sustain_level = (q15_t)(synth_params->pMux[2]*MAX_AMP)>>12;
	sustain_level = (q15_t)((int32_t)(synth_params->pMux[2]*MAX_AMP)>>12);

	/** Saturate sustain level */
//	if(sustain_level>target_level_att)
//		sustain_level = target_level_att;

	target_level_dec = sustain_level+(sustain_level - ((sustain_level*TARGET_REACH)>>15));


	set_base(synth_params);

}


/**
 *  Compute a new ADSR sample
 * @return ADSR sample
 */
q15_t ADSR::update(void){

	q31_t x32;
	int64_t x64;

	x64 = ((int64_t)state) * ((int64_t)beta);	// x64 = s0.31 * s0.31 = s0.62
	x32 = (q31_t)(x64 >>31);					// x32 = s0.62 >> 31   = s0.31
	state = base + x32;							// x32 = s0.31 + s0.31 = s0.31
	arm_add_q31(&base,&x32,&state,1);

    /** saturate */
	//state = (q15_t) (__SSAT(state, 31));
	//state = (q15_t) (__USAT(state, 16));
	if(state<0)
			state = 0;
	if(state>=INT32_MAX)
			state = INT32_MAX;

	q15_t adsr_sample = (q15_t)(state>>16); // 	 y = s0.31 >> 16   = s0.15

	return(adsr_sample);
}
