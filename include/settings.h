/*
 * settings.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */


#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

#include "types.h"


#define FS 96000
//#define FS 44100
//#define FS 16000
#define CONTROL_RATE 4000
#define SHIFT_20_BIT 0x100000
#define SHIFT_31_BIT 0x7FFFFFFF
#define SHIFT_15_BIT 0x7FFF
#define PWM_PERIOD   0x3FFF

#define MAX_AMP 0x7FFF

void init_settings(synth_params_t* synth_params);

#endif /* INCLUDE_SETTINGS_H_ */
