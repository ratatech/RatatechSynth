/*
 * tables.h
 *
 * Created: 05.02.2014 11:52:21
 *  Author: 11jhidalgo
 */


#ifndef TABLES_H_
#define TABLES_H_

#include "arm_math.h"

#define LUT_SIN_8_BIT 256
#define LUT_TRI_8_BIT 512
#define LUT_ENV_5_BIT 32
#define LUT_LFO_5_BIT 32
#define LUT_SIN_20_BIT LUT_SIN_8_BIT << 20
#define LUT_TRI_20_BIT LUT_TRI_8_BIT << 20
#define LUT_ENV_20_BIT LUT_ENV_5_BIT << 20

extern const int16_t sin_lut_q15[LUT_SIN_8_BIT];
extern const int16_t tri_lut_q15[LUT_TRI_8_BIT];
extern const int16_t saw_lut_q15[LUT_TRI_8_BIT];
extern const int16_t square_lut_q15[LUT_TRI_8_BIT];
extern const int16_t env_up_lut_q15[LUT_ENV_5_BIT];
extern const int16_t env_down_lut_q15[LUT_ENV_5_BIT];
extern const int16_t sin_lut_lfo[LUT_ENV_5_BIT];


#endif /* TABLES_H_ */
