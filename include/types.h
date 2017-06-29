/*
@file types.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 21, 2017
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
#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#include <stdint.h>
#include "arm_math.h"

struct object_pool_t
{
	void* 	osc;
	void* 	lfo;
	void*	out_buffer;
	void*	midi;
};

typedef enum {OSC1,OSC2,VCF} dest_t;
typedef enum {SIN,SQU,SAW,TRI} osc_shape_t;

struct osc_params_t{
	osc_shape_t shape_osc;
	int16_t osc_mix;
	double freq_frac;
};

struct lfo_params_t{
	osc_shape_t shape_osc;
	int16_t lfo_amo;
	double freq_frac;
};

struct mov_avg_params_t{
	q31_t beta;
	q31_t state;
	q31_t init_state;
};

struct adsr_params_t{
	q31_t beta_att;
	q31_t beta_dec;
	q31_t beta_rel;
};

struct synth_params_t{
	osc_params_t osc_params;
	lfo_params_t lfo_params;
	mov_avg_params_t mov_avg_params;
	adsr_params_t adsr_params;
	object_pool_t object_pool;

	int16_t lfo_amp;
	int16_t lfo_amo;
	dest_t lfo_dest;
	dest_t midi_dest;
	int16_t adsr_amp_vol;

	uint16_t pitch;
	uint16_t vel;
	bool note_ON;
	int16_t FM_mod_amp;
	uint8_t I;
	bool FM_synth;
};


#endif /* INCLUDE_TYPES_H_ */
