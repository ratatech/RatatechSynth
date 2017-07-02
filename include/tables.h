/*
 * tables.h
 *
 * Created: 05.02.2014 11:52:21
 *  Author: 11jhidalgo
 */


#ifndef TABLES_H_
#define TABLES_H_

#include "arm_math.h"

#define LUT_8_BIT 256
#define LUT_9_BIT 512
#define LUT_10_BIT 1024
#define LUT_5_BIT 32
#define LUT_12_BIT 4096
#define LUT_8_20_BIT LUT_8_BIT << 20
#define LUT_5_20_BIT LUT_5_BIT << 20
#define MIDI_FREQ_LUT_SIZE 128

extern const q15_t sin_lut_q15[LUT_8_BIT];
extern const q15_t tri_lut_q15[LUT_8_BIT];
extern const q15_t saw_lut_q15[LUT_8_BIT];
extern const q15_t squ_lut_q15[LUT_8_BIT];
extern const q15_t sin_lut_lfo[LUT_5_BIT];
extern const double midi_freq_lut[MIDI_FREQ_LUT_SIZE];
extern const q31_t adsr_beta_exp_curve_q31[LUT_12_BIT];

#endif /* TABLES_H_ */
