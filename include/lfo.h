/*
 * lfo.h
 *
 *  Created on: Aug 8, 2015
 *      Author: rata
 */

#ifndef INCLUDE_LFO_H_
#define INCLUDE_LFO_H_

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
class LFO {

	public:



	    osc_shape_t shape;
		int32_t ph_inc_frac;
		int32_t ph_ind_frac;
		int32_t ph_inc;
		int32_t ph_ind;
		int32_t k_frac;
		int32_t lfo_amp = 0;
		int32_t lfo_amo = 0;
		const int16_t *wavetable;

		bool top;
		bool FM_synth;


		/** BLALALALALALAFAFDDFAF
		@param frequency FADFADFADFDFD
		*/
		void setFreqFrac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)LUT_8_BIT/(double)CONTROL_RATE)*freqHz)*1048576);

			if(shape == TRI)
			{
				ph_inc_frac = (int32_t)((((double)LUT_8_BIT/(double)CONTROL_RATE)*freqHz)*1048576);

			}

		}

		/**
		 * Set lfo shape
		 * @param _shape The selected shape of the oscillator to be chosen between {SIN,SAW,TRI}
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

			}
		}

		// Function prototypes
		void update(synth_params_t*);
		int32_t compute_lfo(void);

};


#endif /* INCLUDE_LFO_H_ */
