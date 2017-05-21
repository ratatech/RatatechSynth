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



typedef enum {OSC1,OSC2,VCF} dest_t;
typedef enum {SIN,SQU,SAW,TRI} osc_shape_t;



struct osc_params_t{
	osc_shape_t shape_osc;
	int16_t osc_mix;
	double freq_frac;
};

struct synth_params_t{
	osc_params_t osc_params;
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
