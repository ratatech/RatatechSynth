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
 * Get a new adsr envelope sample
 * @param synth_params 	Synth global structure
 * @return				ADSR sample
 */
q15_t ADSR::get_sample(synth_params_t *synth_params)
{

	q15_t adsr_sample;		/** Temp var */

	/** Update note on status*/
	note_ON = synth_params->note_ON;

	adsr_sample = update();
	synth_params->adsr_vol_amp = adsr_sample;
	return(adsr_sample);

}

/**
 * Interpolate adsr samples
 * @param synth_params 	Synth global structure
 * @param y		 		Interpolated value
 */
q15_t ADSR::interp(synth_params_t *synth_params, q15_t y1,uint8_t ind)
{

	q63_t y = interp_q15(interp_state,y1,FRAME_INTERP_K*ind,SHIFT_FRAME_INTERP);
	return (q15_t)y;

}


/**
 * Reset internal variables and go back to attack state
 */
void ADSR::reset(void)
{
	adsr_state = ATTACK_STATE;
	state = 0;
	note_ON = true;
	beta = beta_att;
	base = base_att;
	interp_state = 0;

}


/** Set base multiplier coefficient after updating params
 * @param synth_params 	Synth global structure
 */
void ADSR::set_base(synth_params_t *synth_params){

	volatile int64_t x64;
	volatile q31_t x32;
	volatile int64_t temp;

	x64 = (int64_t)(INT32_MAX + ratio);
	x32 = (INT32_MAX - beta_att);
	x64 = x64 * x32;
	temp = x64>>31;
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

/** Get the newly read values from the ADC and set the coefficients
 * @param synth_params 	Synth global structure
 */
void ADSR::set_params(synth_params_t *synth_params){

	uint32_t	_beta_att,_beta_dec,_beta_rel,_sustain_level;

	beta_att = adsr_beta_exp_curve_q31[synth_params->pMux[0]];
	beta_dec = adsr_beta_exp_curve_q31[synth_params->pMux[1]];
	beta_rel = adsr_beta_exp_curve_q31[synth_params->pMux[3]];

	sustain_level = (q15_t)(synth_params->pMux[2]*MAX_AMP)>>12;
	sustain_level = (q15_t)((int32_t)(synth_params->pMux[2]*MAX_AMP)>>12);

	set_base(synth_params);

}


/**
 *  Compute a new ADSR sample
 * @return ADSR sample
 */
q15_t ADSR::update(void){

	q31_t x32;
	int64_t x64;

	if((adsr_state != SUSTAIN_STATE) && (adsr_state != IDLE_STATE)){

//		x64 = ((int64_t)state) * ((int64_t)beta);	// x64 = s0.31 * s0.31 = s0.62
//		x32 = (q31_t)(x64 >>31);					// x32 = s0.62 >> 31   = s0.31
//		state = base + x32;							// x32 = s0.31 + s0.31 = s0.31
//		arm_add_q31(&base,&x32,&state,1);
//
//		/** saturate */
//		//state = (q15_t) (__SSAT(state, 31));
//		//state = (q15_t) (__USAT(state, 16));
//		if(state<0)
//				state = 0;
//		if(state>=INT32_MAX)
//				state = INT32_MAX;

		state = adsr_table[ind];
		ind += 8;

	}

	//q15_t adsr_sample = (q15_t)(state>>16); // 	 y = s0.31 >> 16   = s0.15
	q15_t adsr_sample = state; // 	 y = s0.31 >> 16   = s0.15


	/** Update states */
	switch(adsr_state){

		case ATTACK_STATE:

			if (adsr_sample >= MAX_AMP){
				beta = beta_dec;
		        base = base_dec;
		        adsr_table =  adsr_dec_exp_q15;
		        ind = 0;


		        /** If sustain level is set to MAX, Go straight to SUSTAIN state,
		         *  otherwise jump to DECAY state */
		        if(sustain_level>=MAX_AMP){
		        	adsr_state = SUSTAIN_STATE;
		        }else{
		        	adsr_state = DECAY_STATE;
		        }

			}

			if (note_ON == false){
				adsr_state = RELEASE_STATE;
				beta = beta_rel;
		        base = base_rel;
			}

		break;

		case DECAY_STATE:

			if (adsr_sample <= sustain_level){
				adsr_sample = sustain_level;
				adsr_state = SUSTAIN_STATE;
			}
			if (note_ON == false){
				adsr_state = RELEASE_STATE;
				beta = beta_rel;
		        base = base_rel;
			}

		break;

		case SUSTAIN_STATE:
			if (note_ON == false){
				adsr_state = RELEASE_STATE;
				beta = beta_rel;
		        base = base_rel;
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

		case IDLE_STATE:
			// Do Nothing

		break;
	}

	return(adsr_sample);
}
