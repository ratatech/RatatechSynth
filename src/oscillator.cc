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


uint16_t Oscillator::compute_osc(amp_mod_t *amp_mod)
{
	int32_t interp_lut,interp_lut_temp;
	uint16_t u_interp_lut;

	ph_ind_frac += ph_inc_frac;
	if (ph_ind_frac>=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);


	// Interpolate LUT
	interp_lut = arm_linear_interp_q15((int16_t*)wavetable,ph_ind_frac,LUT_SIN_8_BIT)<<8;

	// Modulate signal with the LFO
	interp_lut_temp = interp_lut;
	interp_lut = ((int32_t)(interp_lut)*(amp_mod->lfo_amp)>>15);

	// Mix LFO with amount parameter
	interp_lut = interp_lut + ((int32_t)(interp_lut_temp)*(0x7FFF - amp_mod->lfo_amo)>>15);

	// Modulate signal with the ADSR envelope
	interp_lut = ((int32_t)(interp_lut)*(amp_mod->adsr_amp)>>15);

	// Convert to unsigned
	u_interp_lut = int16_2_uint16(interp_lut);

	// Shift back to 12 bits required by the DAC
	u_interp_lut>>=4;

	return u_interp_lut;


}
