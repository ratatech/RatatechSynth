/*
 @file fileName.cc

 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
 This file is part of Ratatech 3019

 Ratatech 3019 is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Ratatech 3019 is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
 */

#include "oscillator.h"


using namespace std;

/**
 * Compute a new oscillator sample
 * @return interp_lut	The computed oscillator sample
 */
q15_t Oscillator::get_sample(void)
{
    return pLut_interp->get_sample(ph_inc_frac,wavetable);
}

/**
 * Compute a new dual oscillator sample
 * @return interp_lut	The computed oscillator sample
 */
q15_t Oscillator::get_sample_dual(void)
{

	uint32_t interp_lut,interp_lut_temp,frac,ph_ind_frac_dual,ind_frac;
	q31_t sample_a,sample_b,sample_out,_y0,_y1,y;
	uint16_t ind_int;

    /** ---------  OSC A --------- */

	ph_ind_frac += ph_inc_frac;
	ph_ind_frac %= WRAP_AROUND_LUT;

    /** 9 bits for the integer part, 23 bits for the fractional part */
    ind_frac 	= (ph_ind_frac & MASK_PHASE_FRAC);
    ind_int 	= (ph_ind_frac >> SHIFT_PHASE_INT);

    /** Read two nearest output values from the index */
    _y0 = wavetable[ind_int];
    _y1 = wavetable[(ind_int + 1 ) % LUT_LENGTH];

    /** Linear interpolation */
    sample_a = interp_q15(_y0,_y1,ind_frac,SHIFT_PHASE_INT);

    /** ---------  OSC B (detuned) --------- */

	ph_ind_frac_dual = ph_ind_frac*synth_params->osc_params.osc_detune;
	ph_ind_frac_dual %= WRAP_AROUND_LUT;

    /** 9 bits for the integer part, 23 bits for the fractional part */
    ind_frac	= (ph_ind_frac_dual & MASK_PHASE_FRAC);
    ind_int 	= (ph_ind_frac_dual >> SHIFT_PHASE_INT);

    /** Read two nearest output values from the index */
    _y0 = wavetable[ind_int];
    _y1 = wavetable[(ind_int + 1 ) % LUT_LENGTH];

    /** Linear interpolation */
    sample_b = interp_q15(_y0,_y1,ind_frac,SHIFT_PHASE_INT);

    /** Mix the two oscillators in a single sample */
    sample_out = mix(synth_params,(q15_t)sample_a,(q15_t)sample_b,synth_params->osc_params.mixAB);

	return sample_out;

}

/**
 * Compute a new fm oscillator sample
 * @return interp_lut	The computed oscillator sample
 */
int32_t Oscillator::get_sample_fm(void)
{
	int32_t interp_lut,interp_lut_temp,frac,mod;
	int64_t ph_mod_index = 0;

	/**
	 * FM Synthesis
	 *
	 * Use a modulation wave to modify the instantaneous frequency of the
	 * carrier wave. The equation for a frequency-modulated wave where both the
	 * carrier and modulating waves are sinusoids is
	 *
	 * 		e = A*sin(alpha*t + I*sin(beta*t))
	 *
	 * 	where
	 *
	 * 		e     = instantaneous amplitude of the modulated carrier
	 * 		alpha = the carrier frequency
	 * 		beta  = the modulating frequency
	 * 		I     = d/m = the modulation index, the ratio of the peak deviation
	 * 		        to the modulating frequency
	 *
	 * See more about this amazing technique on John M.Chowwning paper on FM Synthesis
	 *
	 * */

	/** Get modulator increment scaled by the modulation index I */
	ph_mod_index =((synth_params->I*synth_params->FM_mod_amp>>15));

	/** Shift 20 bits as the fractional index of the carrier wave */
	ph_mod_index <<= 20;

	/** If FM Synthesis is not enabled, the wavetable is read as usual with the calculated
	 * 	fractional increment
	 * */
	ph_ind_frac += (ph_inc_frac + ph_mod_index);
	ph_ind_frac %= LUT_LENGTH<<20;

	/** Interpolate LUT */
	interp_lut = arm_linear_interp_q15((int16_t*)wavetable,ph_ind_frac,LUT_LENGTH)<<8;

	return interp_lut;

}

/**
 * Compute a new oscillator frame
 * @param synth_params 	Synth global structure
 * @param pOsc 			Pointer to store the oscillator samples
 * @param block_size 	Number of samples in the vector
 */
void Oscillator::get_frame(, q15_t* pOsc, uint32_t block_size)
{

	 q15_t *pOut = pOsc;	/* output pointer */

	 /** Generate samples and store it in the output buffer */
	 for(uint i=0;i<block_size;i++){
		 *pOut++ = get_sample(synth_params);
	 }

	 /** Shift/Saturate to get a square wave */
	 if(shape==SQU)
		 arm_shift_q15(pOsc,16,pOsc,block_size);

}

/** Init oscillator.
 *
 * @param osc_param Structure holding init parameters
 */
void Oscillator::init(osc_params_t* osc_param){
	set_shape(osc_param->shape_osc);
	set_freq_frac(osc_param->freq_frac);

	/** Init lut interpolator object */
	pLut_interp = new Lut_interp(LUT_BITS,LUT_FRAC_BITS);

}

/**
 * Set oscillator fractional frequency
@param freq Fractional frequency in Hz
*/
void Oscillator::set_freq_frac(double freq)
{
	ph_inc_frac = (uint32_t)((((double)LUT_LENGTH/(double)FS)*freq)*PHASE_FRAC_MULT);
	freq_frac = freq;
}

/**
 * Set oscillator fractional phase increment directly from the midi2ph table
 * @param midi_num Midi number
 */
void Oscillator::set_freq_midi(uint8_t midi_num)
{
	ph_inc_frac = midi_phinc_lut[midi_num];
	banlim_ind = midi_bandlim_inds_lut[midi_num];
	set_shape(shape);
}

