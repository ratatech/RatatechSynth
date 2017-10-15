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
#include "utils.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define ENV_LUT_LENGTH 256

enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP,LOG};

class ADSR{

	public:

		q31_t beta,beta_att,beta_dec,beta_rel;
		q31_t base,base_att,base_dec,base_rel;
		q31_t state;
		q15_t target_level,target_level_att,target_level_dec,sustain_level,interp_state;
		int64_t ratio;
		adsr_state_e adsr_state;
		bool note_ON;



		/** ADSR Constructor.
		 *
		 */
		ADSR(void){}

		/**
		 * Set initial ADSR parameters
		 * @param synth_params Synth global structure
		 */
		void init(synth_params_t* synth_params){

			beta_att = synth_params->adsr_params.beta_att;
			beta_dec = synth_params->adsr_params.beta_dec;
			beta_rel = synth_params->adsr_params.beta_rel;
			state = synth_params->mov_avg_params.init_state;
            beta  = synth_params->mov_avg_params.beta;

            adsr_state = IDLE_STATE;
            sustain_level = synth_params->adsr_params.sustain_level;

            note_ON = false;
	        ratio = synth_params->adsr_params.ratio;

	        set_base(synth_params);
			beta = beta_att;
	        base = base_att;

	        interp_state = 0;
		}

		/**
		 * Get a new adsr envelope sample
		 * @param synth_params 	Synth global structure
		 * @return ADSR envelope output
		 */
		q15_t get_sample(synth_params_t *synth_params);

		/**
		 * Reset internal variables and go back to attack state
		 */
		void reset(void);

		/** Get the newly read values from the ADC and set the coefficients
		 * @param synth_params 	Synth global structure
		 */
		void set_params(synth_params_t *synth_params);

		/**
		 *  Compute a new ADSR sample
		 * @return ADSR sample
		 */
		q15_t update(void);

		void set_base(synth_params_t *synth_params);

		/**
		 * Interpolate adsr samples
		 * @param synth_params 	Synth global structure
		 * @param pAdsr 		interpolated value
		 */
		q15_t interp(synth_params_t *synth_params, q15_t y1, uint8_t ind);


};


#endif /* INCLUDE_ADSR_H_ */
