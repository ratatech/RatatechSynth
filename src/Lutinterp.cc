/*
 @file Lutinterp.cc

 @brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

 @ Created by Jordi Hidalgo, Ratatech, Nov 10, 2017
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

#include "Lutinterp.h"

void Lut_interp::reset(void) {
	ph_ind_frac = 0;
	ph_ind_frac_ovf = 0;
}


q15_t Lut_interp::get_sample(uint32_t ph_inc_frac, const q15_t *wavetable) {

	q15_t _y0, _y1;
	q31_t y;
	uint32_t ind_frac;
	uint16_t ind_int0, ind_int1;

	ph_ind_frac += ph_inc_frac;
	ph_ind_frac_ovf += ph_inc_frac;
	ph_ind_frac %= wrap_lut;
	ph_ind_frac_ovf %= wrap_lut_ovf;

	/** 9 bits for the integer part, 23 bits for the fractional part */
	ind_frac = (ph_ind_frac & mask);
	ind_int0 = (ph_ind_frac >> shift_phase);

	ind_int1 = ind_int0 + 1;
	ind_int1 %= lut_length;

	/** Read two nearest output values from the index */
	_y0 = wavetable[ind_int0];
	_y1 = wavetable[ind_int1];

	/** Linear interpolation */
	y = interp_q15(_y0,_y1,ind_frac,shift_phase);

	return y;
}
