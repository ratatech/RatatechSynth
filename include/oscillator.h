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
BABLALBALBALBL
ABABABA
BABAB
BABABA
@todo BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
@note BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
@section BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
BBJBJALDJBJBJBLBLBLBLABLBLBLABLAB
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

		bool top;
		int32_t scaled_LUT;

		/** Constructor.
		@param Scale table size.
		*/
		Oscillator(void){
			scaled_LUT = (int32_t)(((double)LUT_SIN_8_BIT)*SHIFT_20_BIT);
		}

		/** BLALALALALALAFAFDDFAF
		@param frequency FADFADFADFDFD
		*/
		void setFreqFrac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)LUT_SIN_8_BIT/(double)FS)*freqHz)*SHIFT_20_BIT);
			k_frac = ph_inc_frac & 0xFFFFF;


			if(shape == TRI)
			{
				ph_inc_frac = (int32_t)((((double)LUT_TRI_8_BIT/(double)FS)*(freqHz/2))*SHIFT_20_BIT);
				k_frac = ph_inc_frac & 0xFFFFF;

			}

		}
		/** BLALALALALALAFAFDDFAF
		@param frequency FADFADFADFDFD
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
					wavetable = square_lut_q15;
				break;
			}


		}

		// Function prototypes
		int32_t compute_osc(synth_params_t *synth_params);


};


#endif /* INCLUDE_OSCILLATOR_H_ */
