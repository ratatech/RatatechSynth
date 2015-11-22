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

		bool top;
		bool FM_synth = false;


		/** BLALALALALALAFAFDDFAF
		@param frequency FADFADFADFDFD
		*/
		void setFreqFrac(double freqHz)
		{
			ph_inc_frac = (int32_t)((((double)LUT_SIN_8_BIT/(double)CONTROL_RATE)*freqHz)*1048576);

			if(shape == TRI)
			{
				ph_inc_frac = (int32_t)((((double)LUT_TRI_8_BIT/(double)CONTROL_RATE)*freqHz)*1048576);

			}

		}


		// Function prototypes
		void update(synth_params_t*);
		void compute_lfo_Sine(void);
		void compute_lfo_Square(void);
		void compute_lfo_Triangle(void);
		void compute_lfo_Saw(void);


};


#endif /* INCLUDE_LFO_H_ */
