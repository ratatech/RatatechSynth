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
			adsr_sample = update(target_level);
			*pOut++ = adsr_sample;
		}
	}

	/** Update states */
	switch(adsr_state){

		case ATTACK_STATE:

			if (adsr_sample >= target_level_att){
				target_level = sustain_level;
				beta = beta_dec;
				adsr_state = DECAY_STATE;

			}

		break;

		case DECAY_STATE:

			if (adsr_sample <= target_level_dec){
				target_level = 0;
				beta = beta_rel;
				adsr_state = SUSTAIN_STATE;
			}

		break;

		case SUSTAIN_STATE:
			arm_fill_q15(sustain_level,pOut,FRAME_SIZE);
			if (note_ON == false){
				adsr_state = RELEASE_STATE;
			}

		break;

		case RELEASE_STATE:

			if (adsr_sample <= 1){
				/** End of ADSR envelope Already set level and coeff for a possible new attack state. Remain on idle state */
				target_level = MAX_AMP;
				beta = beta_att;
				adsr_state = IDLE_STATE;

			}

		break;
	}


}


void ADSR::reset(void)
{
	target_level = MAX_AMP;
	adsr_state = ATTACK_STATE;
	note_ON = true;
	beta = beta_att;
}

