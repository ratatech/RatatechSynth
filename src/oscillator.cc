/*
 @file fileName.cc

 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Jun 21, 2015
 This file is part of XXXXXXX

 XXXXXXX is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 XXXXXXX is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with XXXXXXX.  If not, see <http://www.gnu.org/licenses/>
 */

#include "oscillator.h"

using namespace std;

/**
 * Compute a new oscillator sample
 * @param synth_params Synth global structure
 * @return interp_lut The computed oscillator sample
 */
int32_t Oscillator::get_sample(synth_params_t *synth_params)
{
	int32_t interp_lut,interp_lut_temp,frac,mod;
	int64_t ph_mod_index = 0;


	/*
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
	if(FM_synth){

		// Get modulator increment scaled by the modulation index I
		ph_mod_index =((synth_params->I*synth_params->FM_mod_amp>>15));

		// Shift 20 bits as the fractional index of the carrier wave
		ph_mod_index <<= 20;

	}

	/* If FM Synthesis is not enabled, the wavetable is read as usual with the calculated
	 * fractional increment
	 * */
	ph_ind_frac += (ph_inc_frac + ph_mod_index);
	if(ph_ind_frac >= LUT_8_BIT<<20){
		ph_ind_frac -= LUT_8_BIT<<20;
	}

	// Interpolate LUT
	interp_lut = arm_linear_interp_q15((int16_t*)wavetable,ph_ind_frac,LUT_8_BIT)<<8;

	return interp_lut;


}

/** Init oscillator.
 *
 * @param osc_param Structure holding init parameters
 */
void Oscillator::init(osc_params_t* osc_param){
	set_shape(osc_param->shape_osc);
	set_freq_frac(osc_param->freq_frac);
}

/**
 * Set oscillator fractional frequency
@param freq Fractional frequency in Hz
*/
void Oscillator::set_freq_frac(double freq)
{
	ph_inc_frac = (int32_t)((((double)LUT_8_BIT/(double)FS)*freq)*SHIFT_20_BIT);
	k_frac = ph_inc_frac & 0xFFFFF;
	freq_frac = freq;
}
