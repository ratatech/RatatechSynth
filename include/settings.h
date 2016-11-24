/*
 * settings.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

#define FS 96000
//#define FS 44100
//#define FS 16000
#define CONTROL_RATE 4000
#define SHIFT_20_BIT 0x100000
#define SHIFT_31_BIT 0x7FFFFFFF
#define SHIFT_15_BIT 0x7FFF
#define PWM_PERIOD   0x3FFF

typedef enum {SIN,SQU,SAW,TRI} osc_shape_t;
typedef enum {OSC1,OSC2,VCF} dest_t;

struct synth_params_t{
	int16_t lfo_amp;
	int16_t lfo_amo;
	dest_t lfo_dest;
	dest_t midi_dest;
	int16_t adsr_amp_vol;
	int16_t osc_mix;
	uint16_t pitch;
	uint16_t vel;
	bool note_ON;
	int16_t FM_mod_amp;
	uint8_t I;
	bool FM_synth;
};

#endif /* INCLUDE_SETTINGS_H_ */
