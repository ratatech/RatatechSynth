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
#define LUT_5_20_BIT LUT_5_BIT << 20
#define LUT_8_20_BIT LUT_8_BIT << 20
#define MIDI_FREQ_LUT_SIZE 128
#define MIDI_PHINC_LUT_SIZE 128
#define LFO_PHINC_LUT_SIZE LUT_12_BIT
#define N_BANDLIM 10
#define MIDI_BANDLIM_INDS_LUT_SIZE 128
#define ADSR_TIME_PHINC_LUT_SIZE LUT_12_BIT
#define DITHERING_LUT_SIZE 16

extern const q15_t sin_lut_q15[LUT_8_BIT];
extern const q15_t squ_bandlim_lut_q15[N_BANDLIM][LUT_8_BIT];
extern const q15_t saw_bandlim_lut_q15[N_BANDLIM][LUT_8_BIT];
extern const q15_t tri_bandlim_lut_q15[N_BANDLIM][LUT_8_BIT];


extern const q15_t sin_lut_lfo[LUT_5_BIT];
extern const double midi_freq_lut[MIDI_FREQ_LUT_SIZE];
extern q15_t adsr_att_exp_q15[LUT_8_BIT];
extern q15_t adsr_dec_exp_q15[LUT_8_BIT];
extern const uint32_t midi_phinc_lut[MIDI_PHINC_LUT_SIZE];
extern const uint32_t lfo_phinc_lut[LFO_PHINC_LUT_SIZE];
extern const uint8_t  midi_bandlim_inds_lut[MIDI_BANDLIM_INDS_LUT_SIZE];
extern const uint32_t adsr_time_phinc_lut[ADSR_TIME_PHINC_LUT_SIZE];
extern const uint8_t  dithering_lut[DITHERING_LUT_SIZE][DITHERING_LUT_SIZE];

#endif /* TABLES_H_ */
