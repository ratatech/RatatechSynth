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
		adsr_mode_e adsr_mode_att,adsr_mode_dec,adsr_mode_rel;
		int64_t b_att,range_att,offs_att,state_att,peak_att,sgn_att,b_dec,range_dec,offs_dec,state_dec,peak_dec,sgn_dec;
		int64_t b_rel,range_rel,offs_rel,state_rel,peak_rel,sgn_rel,env_max,k_int,env_state,sustain_lvl,counter,init_state_att,init_state_dec,init_state_rel;
		bool note_ON;


		/** Constructor.
		 * Set the Linear/Exponential envelope generator mode and initialize several parameters
		 * @param mode
		 */
		ADSREnv(adsr_mode_e mode_att,adsr_mode_e mode_dec,adsr_mode_e mode_rel, double k_in){
 	 		adsr_mode_att = mode_att;
 	 		adsr_mode_dec = mode_dec;
 	 		adsr_mode_rel = mode_rel;
 	 		note_ON = false;
 	 		adsr_state = IDLE_STATE;
 	 		k = k_in;
 	 		env_bits = 31;
 	 		env_max = (1<<env_bits)-1;
 	 		k_int = (int64_t)(k*env_max);
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

			switch(mode){

				case EXP:

					b_att = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
					range_att = env_max;
					offs_att = 0;
					state_att = k_int;
					init_state_att = state_att;
					peak_att = 0;
					sgn_att = 1;
				break;

				case LOG:

					b_att = (int64_t)round((double)pow(k/(k+1),1/(time*CONTROL_RATE))*env_max);
					range_att = env_max;
					offs_att = 0;
					state_att = k_int+env_max;
					init_state_att = state_att;
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
		            init_state_dec = state_dec;
		            peak_dec = 0;
		            sgn_dec = 1;
				break;

				case LOG:

					b_dec = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
		            range_dec = env_max-sustain_lvl;
		            offs_dec = 0;
		            state_dec = k_int;
		            init_state_dec = state_dec;
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
		            init_state_rel = state_rel;
		            peak_rel = 0;
		            sgn_rel = 1;
				break;

				case LOG:

		            b_rel = (int64_t)round((double)pow((k+1)/k,1/(time*CONTROL_RATE))*env_max);
		            range_rel = sustain_lvl;
		            offs_rel = 0;
		            state_rel = k_int;
		            init_state_rel = state_rel;
		            peak_rel = sustain_lvl;
		            sgn_rel = -1;
				break;

			}
		}
		/**
		 * Reset state internal values to the original
		 */
		void initStates(void){
				switch(adsr_mode_att){

					case EXP:
						if(adsr_amp==0){
							state_att = init_state_att;
						}else{
							state_att = init_state_att;
							range_att = env_max-(adsr_amp<<16);
							offs_att = (adsr_amp<<16);
						}
					break;
					case LOG:
						if(adsr_amp==0){
							state_att = init_state_att;
							range_att = env_max;

						}else{
							state_att = init_state_att;
							range_att = env_max-(adsr_amp<<16);
						}
					break;
			}
			//state_att = init_state_att;
			state_dec = init_state_dec;
			state_rel = init_state_rel;
			adsr_state = ATTACK_STATE;

		}

		/**
		 * Calculate the number of steps needed in each of the ADSR states
		 */
		void calcAdsrSteps(void){
			sustain_lvl = (int64_t)(sustain*env_max);
			counter = 0;
			calcAttack(attack,adsr_mode_att);
			calcDecay(decay,adsr_mode_dec);
			calcRelease(release,adsr_mode_rel);

		}

		/**
		 * Update ADSR states
		 * @param synth_params
		 */
		int16_t update(void){


			/********************************************//**
			 *  Exponential ADSR
			 ***********************************************/
			switch (adsr_state)
			{
				case ATTACK_STATE:
					int64_t temp;
					temp = (b_att*state_att);
					state_att = temp>>env_bits;
					temp = (peak_att+sgn_att*(((state_att - k_int) * range_att)>>env_bits) + offs_att);
					adsr_amp = temp>>16;
					if (adsr_amp >=(0x7FFF)  || adsr_amp <0)
					{
						adsr_amp = 0x7FFF;
						adsr_state = DECAY_STATE; // TODO(JoH):Seems to be a bug with the DECAY range calculation
						//adsr_state = RELEASE_STATE;
						break;
					}
					counter++;

				break;

				case DECAY_STATE:
					temp = (b_dec*state_dec);
					state_dec = temp>>env_bits;
					temp = peak_dec+sgn_dec*(((state_dec - k_int) * range_dec)>>env_bits) + offs_dec;
					adsr_amp = temp>>16;
					if (adsr_amp <=(sustain_lvl>>16))
					{
						adsr_amp = sustain_lvl>>16;
						if (note_ON)
						{
							adsr_state = SUSTAIN_STATE;
						}else{
							adsr_state = RELEASE_STATE;
							range_rel = adsr_amp<<16;
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
					temp = (peak_rel+sgn_rel*(((state_rel - k_int) * range_rel)>>env_bits) + offs_rel);
					adsr_amp = temp>>16;
//					//trace_printf("%i\n",adsr_amp);
					if (adsr_amp <= 0)
					{
						adsr_amp = 0;
						adsr_state = IDLE_STATE;
						break;
					}

				break;
			}


		}

};


#endif /* INCLUDE_ADSR_H_ */
