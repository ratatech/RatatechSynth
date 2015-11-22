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


int32_t Oscillator::compute_osc(synth_params_t *synth_params)
{
	int32_t interp_lut,interp_lut_temp,frac,mod;
	int64_t ph_mod_index;



	ph_mod_index =((ph_inc_frac>>15)*(synth_params->FM_mod_amp));
	ph_mod_index *= 10;

	ph_ind_frac += ph_mod_index;
	if (ph_ind_frac>=(LUT_SIN_20_BIT))
		ph_ind_frac -= (LUT_SIN_20_BIT);

	// Interpolate LUT
	interp_lut = arm_linear_interp_q15((int16_t*)wavetable,ph_ind_frac,LUT_SIN_8_BIT)<<8;




	return interp_lut;


}
