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
 * Set initial ADSR parameters
 * @param synth_params Synth global structure
 */
void ADSR::init(synth_params_t* synth_params){

	ph_inc_att = synth_params->adsr_params.ph_inc_att;
	ph_inc_dec = synth_params->adsr_params.ph_inc_dec;
	ph_inc_rel = synth_params->adsr_params.ph_inc_rel;
	ph_inc = ph_inc_att;

    adsr_state = IDLE_STATE;
    sustain_level = synth_params->adsr_params.sustain_level;

    interp_state = 0;
    ind = 0;
    adsr_table = adsr_att_exp_q15;

	/** Init lut interpolator object */
	pLut_interp = new Lut_interp(LUT_BITS,LUT_FRAC_BITS);

}

/**
 * Get a new adsr envelope sample
 * @param synth_params 	Synth global structure
 * @return				ADSR sample
 */
q15_t ADSR::get_sample(synth_params_t *synth_params)
{

	q15_t adsr_sample;		/** Temp var */

	adsr_sample = update(synth_params);

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
	interp_state = 0;
	adsr_table = adsr_att_exp_q15;
	ph_inc = ph_inc_att;
	pLut_interp->reset();

}


/** Get the newly read values from the ADC and set the coefficients
 * @param synth_params 	Synth global structure
 */
void ADSR::set_params(synth_params_t *synth_params) {

	ph_inc_att = adsr_time_phinc_lut[synth_params->pMux[0]];
	ph_inc_dec = adsr_time_phinc_lut[synth_params->pMux[1]];
	ph_inc_rel = adsr_time_phinc_lut[synth_params->pMux[3]];

	sustain_level = (q15_t) (synth_params->pMux[2] * MAX_AMP) >> 12;
	sustain_level = (q15_t) ((int32_t) (synth_params->pMux[2] * MAX_AMP) >> 12);

}


/**
 *  Compute a new ADSR sample
 * @return ADSR sample
 */
q15_t ADSR::update(synth_params_t *synth_params){

	q31_t x32;
	int64_t x64;
	q15_t adsr_sample;

	adsr_sample = pLut_interp->get_sample(ph_inc,adsr_table);


	if((adsr_state != SUSTAIN_STATE) && (adsr_state != IDLE_STATE)){
		adsr_sample = pLut_interp->get_sample(ph_inc,adsr_table);
	}
	//printf("ADSR STATE = %i ADSR S_LVL = %i ADSR LVL = %i ADSR TOPREL = %i\r",adsr_state,sustain_level,adsr_sample,top_level_rel);

	/** Update states */
	switch (adsr_state) {

	case ATTACK_STATE:
		top_level_rel = adsr_sample;
		top_level_dec = adsr_sample;

		if ( (pLut_interp->ph_ind_frac + ph_inc ) > pLut_interp->wrap_lut) {
			ph_inc = ph_inc_dec;
			//adsr_sample = state;
			pLut_interp->reset();
			adsr_table = adsr_dec_exp_q15;
			ind = 0;

			/** If sustain level is set to MAX, Go straight to SUSTAIN state,
			 *  otherwise jump to DECAY state */
			if (sustain_level >= MAX_AMP) {
				adsr_state = SUSTAIN_STATE;
			} else {
				adsr_state = DECAY_STATE;

			}

		}

		if (synth_params->note_ON == false) {
			adsr_state = RELEASE_STATE;
			ph_inc = ph_inc_rel;
			adsr_table = adsr_dec_exp_q15;
			top_level_rel = adsr_sample;
			pLut_interp->reset();

		}

		break;

	case DECAY_STATE:
		adsr_sample = mul_q15_q15(adsr_sample,top_level_dec - sustain_level);
		adsr_sample += sustain_level;

		if( (pLut_interp->ph_ind_frac + ph_inc ) > pLut_interp->wrap_lut) {
			adsr_sample = sustain_level;
			top_level_rel = adsr_sample;
			adsr_state = SUSTAIN_STATE;
			ph_inc = ph_inc_rel;
			pLut_interp->reset();
		}
		if (synth_params->note_ON == false) {
			adsr_state = RELEASE_STATE;
			ph_inc = ph_inc_rel;
			top_level_rel = adsr_sample;
			pLut_interp->reset();
		}

		break;

	case SUSTAIN_STATE:
		adsr_sample = sustain_level;
		if (synth_params->note_ON == false) {
			adsr_state = RELEASE_STATE;
			ph_inc = ph_inc_rel;
			pLut_interp->reset();
			top_level_rel = sustain_level;

		}

		break;

	case RELEASE_STATE:

		adsr_sample = mul_q15_q15(adsr_sample,top_level_rel);

		if( (pLut_interp->ph_ind_frac + ph_inc ) > pLut_interp->wrap_lut) {
			/** End of ADSR envelope Already set level and coeff for a possible new attack state. Remain on idle state */
			ph_inc = ph_inc_att;
			adsr_state = IDLE_STATE;
			adsr_sample = 0;
			pLut_interp->reset();

		}

		break;

	case IDLE_STATE:
		adsr_sample = 0;

		break;
	}

	state = adsr_sample;
	synth_params->adsr_vol_amp = adsr_sample;


	return (adsr_sample);
}
