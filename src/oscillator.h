/*
 * oscillator.h
 *
 *  Created on: Jun 21, 2015
 *      Author: rata
 */

#ifndef INCLUDE_OSCILLATOR_H_
#define INCLUDE_OSCILLATOR_H_

#include <math.h>
#include <stdint.h>
#include "arm_math.h"
#include "tables.h"
#include "types.h"
#include "synthSettings.h"
#include "Lutinterp.h"
#include "system_init.h"

class Lut_interp;

/**
 * Oscillator class
 */
class Oscillator {


public:
	osc_shape_t _shape_osc;
	int16_t mixAB;
	double freq_frac;
	double phaseInd;
	double phaseIncFrac;
	uint16_t phaseInc;
	uint16_t K;
	double KFrac;
	const q15_t *wavetable;
	uint16_t tableShift;
	double sampleDebug;
	double sampleDebug2;
	double sampleDebug3;
	uint16_t sampleDebugInt;
	unsigned char debugChar;
	int32_t sampleRef;
	uint16_t trianfgleTop;
	uint16_t triangleMax;
	uint16_t sawTop;
	uint16_t squareTop;
	osc_shape_t shape;
	uint32_t ph_inc_frac;
	volatile uint32_t ph_ind_frac;
	int32_t triangle_out;
	int32_t triangle_ref;
	int32_t square_out;
	bool top,FM_synth;
	int32_t scaled_LUT;
	uint8_t banlim_ind;
	Lut_interp *pLut_interp;




	/** Constructor.
	 *
	 */
	Oscillator(void){

	}

	/** Init oscillator.
	 *
	 * @param osc_param Structure holding init parameters
	 */
	void init(osc_params_t* osc_param);

	/**
	 * Set oscillator fractional frequency
	@param freq Fractional frequency in Hz
	*/
	void set_freq_frac(double freq);

	/**
	 * Set oscillator fractional phase increment directly from the midi2ph table
	 * @param midi_num Midi number
	 */
	void set_freq_midi(uint8_t midi_num);

	/**
	 * Set oscillator shape
	 * @param _shape The selected shape of the oscillator to be chosen between {SIN,SQU,SAW,TRI}
	 */
	void set_shape(osc_shape_t _shape)
	{
		shape = _shape;
		switch(_shape)
		{
			case SIN:
				wavetable = sin_lut_q15;
			break;

			case TRI:
				wavetable = tri_bandlim_lut_q15[banlim_ind];
			break;

			case SAW:
				wavetable = saw_bandlim_lut_q15[banlim_ind];
			break;

			case SQU:
				wavetable = squ_bandlim_lut_q15[banlim_ind];
			break;
		}


	}

	/**
	 * Compute a new oscillator sample
	 * @return interp_lut The computed oscillator sample
	 */
	q15_t get_sample(void);

	/**
	 * Compute a new dual oscillator sample
	 * @param synth_params	Synth global structure
	 * @return interp_lut	The computed oscillator sample
	 */
	q15_t get_sample_dual(void);

	/**
	 * Compute a new fm oscillator sample
	 * @param synth_params	Synth global structure
	 * @return interp_lut	The computed oscillator sample
	 */
	int32_t get_sample_fm(void);

	/**
	 * Compute a new oscillator frame
	 * @param synth_params 	Synth global structure
	 * @param pOsc 			Pointer to store the oscillator samples
	 * @param block_size 	Number of samples in the vector
	 */
	void get_frame(q15_t* pOsc, uint32_t block_size);
};


#endif /* INCLUDE_OSCILLATOR_H_ */
