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

#define LFO_DC_OFF 0x4000
#define LFO_DC_OFF 0x4000

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
		q15_t lfo_amp = 0;
		q15_t lfo_amo = 0;
		const int16_t *wavetable;

		bool top;
		bool FM_synth;


		/**
		 * Set lfo  frequency
		@param freqHz Frequency in Hz
		*/
		void set_freq_frac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)LUT_8_BIT/(double)FS)*freqHz)*SHIFT_20_BIT);
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

		/** Init lfo.
		 *
		 * @param lfo_param Structure holding init parameters
		 */
		void init(lfo_params_t* lfo_param);

		/**
		 * Compute a new lfo sample
		 * @return lfo_amp The computed lfo sample
		 */
		q15_t get_sample(synth_params_t* synth_params);

		/**
		 * Compute a new lfo frame
		 * @param synth_params Synth global structure
		 * @param pLfo Pointer to store the oscillator samples
		 * @param block_size 	Number of samples in the vector
		 */
		void get_frame(synth_params_t *synth_params, q15_t* pLfo, uint32_t block_size);

};


#endif /* INCLUDE_LFO_H_ */
