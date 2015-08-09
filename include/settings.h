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
#define CONTROL_RATE 16000

typedef enum {SIN,SQU,SAW,TRI} osc_shape_t;

struct synth_params_t{
	int16_t lfo_amp;
	int16_t lfo_amo;
	int16_t adsr_amp;
	uint16_t osc_mix;
};

#endif /* INCLUDE_SETTINGS_H_ */
