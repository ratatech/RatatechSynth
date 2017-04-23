/*
 * oscillator.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_OSCILLATOR_H_
#define INCLUDE_OSCILLATOR_H_

#include "ratatechSynth.h"
#include "arm_math.h"
#include "tables.h"
#include <math.h>



/**
 * Oscillator class
 */
class Oscillator {

	public:
		double phaseInd;
		double phaseIncFrac;
		uint16_t phaseInc;
		uint16_t K;
		double KFrac;
		const int16_t *wavetable;
		uint16_t tableShift;
		double sampleDebug;
		double sampleDebug2;
		double sampleDebug3;
		uint16_t sampleDebugInt;
		unsigned char debugChar;
		int32_t sampleRef;
		uint16_t triangleTop;
		uint16_t triangleMax;
		uint16_t sawTop;
		uint16_t squareTop;
		osc_shape_t shape;


		int32_t ph_inc_frac;
		int32_t ph_ind_frac;
		int32_t k_frac;
		int32_t triangle_out;
		int32_t triangle_ref;
		int32_t square_out;

		bool top,FM_synth;
		int32_t scaled_LUT;

		/** Constructor.
		@param Scale table size.
		*/
		Oscillator(void){
			scaled_LUT = (int32_t)(((double)LUT_8_BIT)*SHIFT_20_BIT);
		}

		/**
		 * Set oscillator fractional frequency
		@param frequency Fractional frequency in Hz
		*/
		void set_freq_frac(double freqHz)
		{	//TODO(JoH):Define global variable with table length
			ph_inc_frac = (int32_t)((((double)LUT_8_BIT/(double)FS)*freqHz)*SHIFT_20_BIT);
			k_frac = ph_inc_frac & 0xFFFFF;

		}

		/**
		 * Set oscillator shape
		 * @param _shape The selected shape of the oscillator to be chosen between {SIN,SQU,SAW,TRI}
		 */
		void set_shape(osc_shape_t _shape)
		{
			shape = _shape;
			switch(_shape)
			{
				case SIN:
					wavetable = sin_lut_q15;
				break;

				case TRI:
					wavetable = tri_lut_q15;
				break;

				case SAW:
					wavetable = saw_lut_q15;
				break;

				case SQU:
					wavetable = squ_lut_q15;
				break;
			}


		}

		/**
		 * Compute a new oscillator sample
		 * @param synth_params Synth global structure
		 * @return interp_lut The computed oscillator sample
		 */
		int32_t get_sample(synth_params_t *synth_params);


};


#endif /* INCLUDE_OSCILLATOR_H_ */
