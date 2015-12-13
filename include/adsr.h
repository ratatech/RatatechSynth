/*
 * adsr.h
 *
 *  Created on: Jul 18, 2015
 *      Author: rata
 */

#ifndef INCLUDE_ADSR_H_
#define INCLUDE_ADSR_H_

#include "ratatechSynth.h"
#include "tables.h"
#include <math.h>

#define ENV_LUT_LENGTH 256
enum adsr_state_e {ATTACK_STATE,DECAY_STATE ,SUSTAIN_STATE,RELEASE_STATE,IDLE_STATE};
enum adsr_mode_e {LIN,EXP,LOG};


class ADSREnv {
	public:

		double attack,decay,sustain,release,k;
		int8_t env_bits;
		int16_t adsr_amp;
		adsr_state_e adsr_state;
		adsr_mode_e adsr_mode;
		int64_t b_att,range_att,offs_att,state_att,peak_att,sgn_att,b_dec,range_dec,offs_dec,state_dec,peak_dec,sgn_dec;
		int64_t b_rel,range_rel,offs_rel,state_rel,peak_rel,sgn_rel,env_max,k_int,env_state,sustain_lvl;
		bool note_ON;


		/** Constructor.
		 * Set the Linear/Exponential envelope generator mode and initialize several parameters
		 * @param mode
		 */
		ADSREnv(adsr_mode_e mode, double k_in){
 	 		adsr_mode = mode;
 	 		note_ON = false;
 	 		adsr_state = IDLE_STATE;
 	 		k = k_in;
 	 		env_bits = 31;
 	 		env_max = (1<<env_bits)-1;
 	 		k_int = (int32_t)(k*env_max);
		}

		/**
		 * Calculate an exponential coefficient
		 * @param time The duration of the ADSR state being calculated
		 * @return The exponential coefficient
		 */
		double calcExpCoeff(double time){
			return((exp(-log((1.0 + k) / k) / (time*CONTROL_RATE))));
		}

		/**
		 * Calculate Attack state parameters
		 * @param time
		 * @param mode
		 */
		void calcAttack(double time, adsr_mode_e mode){
			double tempCalc;

			switch(mode){

				case EXP:

					b_att = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
					range_att = env_max;
					offs_att = 0;
					state_att = k_int;
					peak_att = 0;
					sgn_att = 1;
				break;

				case LOG:

					b_att = (int64_t)round((double)pow(k/(k+1),1/(time*CONTROL_RATE))*env_max);
					range_att = env_max;
					offs_att = 0;
					state_att = k_int+env_max;
					peak_att = env_max;
					sgn_att = -1;
				break;

			}

		}

		/**
		 * Calculate Decay state parameters
		 * @param time
		 * @param mode
		 */
		void calcDecay(double time, adsr_mode_e mode){

			switch(mode){

				case EXP:
					b_dec = (int64_t)round((double)pow(k/(k+1),1/(time*CONTROL_RATE))*env_max);
		            range_dec = env_max-sustain_lvl;
		            offs_dec = sustain_lvl;
		            state_dec = k_int+env_max;
		            peak_dec = 0;
		            sgn_dec = 1;
				break;

				case LOG:

					b_dec = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
		            range_dec = env_max-sustain_lvl;
		            offs_dec = 0;
		            state_dec = k_int;
		            peak_dec = env_max;
		            sgn_dec = -1;
				break;

			}
		}

		/**
		 * Calculate Release state parameters
		 * @param time
		 * @param mode
		 */
		void calcRelease(double time, adsr_mode_e mode){

			switch(mode){

				case EXP:

					b_rel = (int64_t)round((double)pow(k/(k+1),1/(time*CONTROL_RATE))*env_max);
					range_rel = sustain_lvl;
		            offs_rel = 0;
		            state_rel = env_max+k_int;
		            peak_rel = 0;
		            sgn_rel = 1;
				break;

				case LOG:

		            b_rel = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
		            range_rel = sustain_lvl;
		            offs_rel = 0;
		            state_rel = k_int;
		            peak_rel = sustain_lvl;
		            sgn_rel = -1;
				break;

			}
		}

		/**
		 * Calculate the number of steps needed in each of the ADSR states
		 */
		void calcAdsrSteps(void){
			sustain_lvl = (int64_t)(sustain*env_max);
			calcAttack(attack,LOG);
			calcDecay(decay,LOG);
			calcRelease(release,LOG);


//			if(adsr_mode == LIN){
//
//				/********************************************//**
//				 *  Linear ADSR Steps
//				 ***********************************************/
//				ph_inc_A = (int32_t)((((double)LUT_ENV_5_BIT/(double)(CONTROL_RATE*attack)))*SHIFT_20_BIT);
//				decay_len = (int64_t)((((double)LUT_ENV_5_BIT*sustain))*SHIFT_20_BIT);
//				ph_inc_D = (int32_t)((((double)decay_len/(double)(CONTROL_RATE*decay))));
//				int32_t release_len = (LUT_ENV_5_BIT<<20)-decay_len;
//				ph_inc_R = (int32_t)((((double)(release_len)/(double)(CONTROL_RATE*release))));
//
//			}else{
//
//				/********************************************//**
//				 *  Exponential ADSR coeffs and initial levels
//				 ***********************************************/
//				sustain_lvl = (int32_t)(sustain*SHIFT_15_BIT);
//
//				double exp_coeff_temp = calcExpCoeff(attack);
//				attack_coeff = (int32_t)(exp_coeff_temp*SHIFT_31_BIT);
//				attack_init_val = (int32_t)((1.0 + k) * (1.0 - exp_coeff_temp)*SHIFT_31_BIT);
//
//				exp_coeff_temp = calcExpCoeff(decay);
//				decay_coeff = (int32_t)(exp_coeff_temp*SHIFT_31_BIT);
//				decay_init_val = (int32_t)((sustain_lvl - k) * (1.0 - exp_coeff_temp)*SHIFT_31_BIT);
//
//				exp_coeff_temp = calcExpCoeff(release);
//				release_coeff = (int32_t)(exp_coeff_temp*SHIFT_31_BIT);
//				release_init_val = (int32_t)((-k) * (1.0 - exp_coeff_temp)*SHIFT_31_BIT);
//
//				sustain_lvl = (int32_t)(sustain*SHIFT_15_BIT);
//
//			}


		}

		/**
		 * Update ADSR states
		 * @param synth_params
		 */
		void update(synth_params_t *synth_params){


			/********************************************//**
			 *  Exponential ADSR
			 ***********************************************/
			switch (adsr_state)
			{
				case ATTACK_STATE:
					int64_t temp;
					temp = (b_att*state_att);
					state_att = temp>>env_bits;
					temp = (peak_att+sgn_att*(((state_att - k_int)) * range_att)>>env_bits + offs_att);
					adsr_amp = temp>>15;
					if (adsr_amp >=(0x7FFF)  || adsr_amp <0)
					{
						adsr_amp = 0x7FFF;
						adsr_state = DECAY_STATE;
						break;
					}

				break;

				case DECAY_STATE:
					temp = (b_dec*state_dec);
					state_dec = temp>>env_bits;
					temp = (peak_dec+sgn_dec*(((state_dec - k_int)) * range_dec)>>env_bits + offs_dec);
					adsr_amp = temp>>15;
					if (adsr_amp <=(sustain_lvl>>15))
					{
						adsr_amp = sustain_lvl>>15;
						if (note_ON)
						{
							adsr_state = SUSTAIN_STATE;
						}else{
							adsr_state = RELEASE_STATE;
						}
						break;
					}

				break;

				case SUSTAIN_STATE:
					//do nothing, wait the key to be released and jump to the next state
					//trace_printf("SUSTAINEDDD!\n");
					//adsr_amp = (int16_t) arm_linear_interp_q15((int16_t*)env_up_lut_q15,ph_ind,LUT_ENV_5_BIT);
				break;

				case RELEASE_STATE:

					temp = (b_rel*state_rel);
					state_rel = temp>>env_bits;
					temp = (peak_rel+sgn_rel*(((state_rel - k_int)) * range_rel)>>env_bits + offs_rel);
					adsr_amp = temp>>15;
//					//trace_printf("%i\n",adsr_amp);
					if (adsr_amp < 0)
					{
						adsr_amp = 0;
						adsr_state = IDLE_STATE;
						break;
					}

				break;
			}


			// Save calculated amplitude to the data structure
			synth_params->adsr_amp = adsr_amp;


		}

};


#endif /* INCLUDE_ADSR_H_ */
