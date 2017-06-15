/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include "tables.h"
#include "mov_avg.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ENV_LUT_LENGTH 256
enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP,LOG};



class ADSR: MovAvg{

	public:

//		double attack,decay,sustain,release,k;
//		int8_t env_bits;
//		int16_t adsr_amp;
//		adsr_state_e adsr_state;
//		adsr_mode_e adsr_mode_att,adsr_mode_dec,adsr_mode_rel;
//		int64_t b_att,range_att,offs_att,state_att,peak_att,sgn_att,b_dec,range_dec,offs_dec,state_dec,peak_dec,sgn_dec;
//		int64_t b_rel,range_rel,offs_rel,state_rel,peak_rel,sgn_rel,env_max,k_int,env_state,sustain_lvl,counter,init_state_att,init_state_dec,init_state_rel;
//		bool note_ON;

		q31_t beta_att,beta_dec,beta_rel;
		q15_t target_level,sustain_level;
		adsr_state_e adsr_state;
		bool note_ON;




		/** ADSR Constructor.
		 *
		 */
		ADSR(void){}


		void init(synth_params_t* synth_params){

			beta_att = synth_params->adsr_params.beta_att;
			beta_dec = synth_params->adsr_params.beta_dec;
			beta_rel = synth_params->adsr_params.beta_rel;
			state = synth_params->mov_avg_params.init_state;
            beta  = synth_params->mov_avg_params.beta;
            target_level = MAX_AMP;
            adsr_state = ATTACK_STATE;
            sustain_level = MAX_AMP>>1;
            note_ON = true;



			beta = beta_att;
		}

		/**
		 * Get a new adsr envelope frame
		 * @param synth_params Synth global structure
		 * @param pAdsr ADSR envelope output buffer
		 */
		void get_frame(synth_params_t *synth_params, q15_t* pAdsr);

};


#endif /* INCLUDE_ADSR_H_ */
