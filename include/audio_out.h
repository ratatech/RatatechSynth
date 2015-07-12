/*
 * audio_out.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_AUDIO_OUT_H_
#define INCLUDE_AUDIO_OUT_H_



#include "ratatechSynth.h"
#include "oscillator.h"

using namespace std;


#define BUFFER_FAIL     0
#define BUFFER_SUCCESS  1

void audio_out_Callback(uint16_t data);



#endif /* INCLUDE_AUDIO_OUT_H_ */
