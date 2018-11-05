/*
 * lfo.h
 *
 *  Created on: Aug 8, 2015
 *      Author: rata
 */

#ifndef INCLUDE_LFO_H_
#define INCLUDE_LFO_H_

#include "utils.h"
#include "arm_math.h"
#include "tables.h"
#include "types.h"


#include <math.h>

#define LFO_DC_OFFSET 0x4000

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
		uint32_t ph_inc_frac,ph_ind_frac,ph_inc,ph_ind;
		q15_t lfo_amp,interp_state;
		q15_t lfo_amo;
		const q15_t *wavetable;

		bool top;
		bool FM_synth;


		/**
		 * Set LFO fractional frequency
		@param freqHz Frequency in Hz
		*/
		void set_freq_frac(double freq)
		{
			ph_inc_frac = (uint32_t)((((double)LUT_LENGTH/(double)FS)*freq)*PHASE_FRAC_MULT);
		}

		/**
		 * Set LFO fractional frequency from a given LUT
		 * @param ind	Index to retrieve the fractinal frequency increment
		 */
		void set_freq_lut(uint32_t ind)
		{
			ph_inc_frac = lfo_phinc_lut[ind];
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
					wavetable = tri_bandlim_lut_q15[0];
				break;

				case SAW:
					wavetable = saw_bandlim_lut_q15[0];
				break;

				case SQU:
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
		q15_t get_sample(void);

		/**
		 * Compute a new lfo frame
		 * @param pLfo Pointer to store the oscillator samples
		 * @param block_size 	Number of samples in the vector
		 */
		void get_frame(q15_t* pLfo, uint32_t block_size);

		/**
		 * Interpolate lfo samples
		 * @param y		 		Interpolated value
		 */
		q15_t interp(q15_t y1,uint8_t ind);

};


#endif /* INCLUDE_LFO_H_ */
