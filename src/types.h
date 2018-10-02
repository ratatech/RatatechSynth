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

#define FS 48000
#define CONTROL_RATE 4000
#define SHIFT_20_BIT 0x100000
#define SHIFT_31_BIT 0x7FFFFFFF
#define SHIFT_15_BIT 0x7FFF
#define PWM_PERIOD   0x7FFF
#define FRAME_SIZE 32
#define ADSR_BLOCK_SIZE 1
#define LFO_BLOCK_SIZE 1
#define MAX_AMP 0x7FFF
#define SHIFT_REGISTER_BITS 8
#define LUT_LENGTH LUT_8_BIT
#define MASK_PHASE_FRAC 0x7FFFFF
#define SHIFT_PHASE_INT 23
#define WRAP_AROUND_LUT LUT_LENGTH << SHIFT_PHASE_INT
#define PHASE_FRAC_MULT 0x800000
#define FRAME_INTERP_K 0x4000000
#define SHIFT_FRAME_INTERP 31
#define LUT_FRAC_BITS 23
#define LUT_BITS 8
#define ADC_CHANNELS 4
#define N_ADC 2
#define ADC_ARRAY_SIZE ADC_CHANNELS
#define MUX_INPUTS 4


struct object_pool_t
{
	void* 	osc1;
	void* 	osc2;
	void* 	osc3;
	void* 	osc4;
	void* 	lfo;
	void*	out_buffer;
	void*	midi;
	void*	adsr;
	void*	mux;
	void*	svf;
};

typedef enum {OSC1,OSC2,VCF} dest_t;
typedef enum {SIN,SQU,SAW,TRI} osc_shape_t;

struct osc_params_t{
	osc_shape_t shape_osc;
	q15_t mixAB;
	q15_t osc_detune;
	uint8_t banlim_ind;
	double freq_frac;
};

struct lfo_params_t{
	osc_shape_t shape_osc;
	q15_t lfo_amo;
	double freq_frac;
};

struct mov_avg_params_t{
	q31_t beta;
	q31_t state;
	q31_t init_state;
};

struct adsr_params_t{
	q31_t ph_inc_att;
	q31_t ph_inc_dec;
	q31_t ph_inc_rel;
	q15_t sustain_level;
};

struct mux_out_t{
	uint16_t mux_x[MUX_INPUTS];
	uint16_t mux_y[MUX_INPUTS];
};

struct synth_params_t{

	/** Structs holding fixed or semi-fixed initial parameters */
	osc_params_t osc_params;
	lfo_params_t lfo_params;
	mov_avg_params_t mov_avg_params;
	adsr_params_t adsr_params;
	object_pool_t object_pool;

	/** LFO */
	q15_t* lfo_amp;
	q15_t lfo_amo;
	dest_t lfo_dest;

	/** ADSR  */
	q15_t adsr_vol_amp;

	/** MIDI */
	dest_t midi_dest;
	uint16_t pitch;
	uint16_t vel;
	bool note_ON;

	/** MUX */
	mux_out_t mux_adc_0_out;
	mux_out_t mux_adc_1_out;
	mux_out_t mux_gpio_0_out;
	mux_out_t mux_gpio_1_out;
	mux_out_t mux_gpio_2_out;

	uint16_t adc_read[ADC_ARRAY_SIZE];
	bool DMA_ADC_transfer_complete;

	/** DAC out sample*/
	uint16_t dac_write;

	int16_t FM_mod_amp;
	uint8_t I;
	bool FM_synth;

	/** Pointer to output frame*/
	q15_t* pOut;


};


#endif /* INCLUDE_TYPES_H_ */
