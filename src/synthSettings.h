/*
@file synthSettings.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Nov 4, 2018
This file is part of Ratatech 3019.

    Ratatech 3019 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Ratatech 3019 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Ratatech 3019.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef SYNTHSETTINGS_H_
#define SYNTHSETTINGS_H_

#include "stdint.h"
#include "types.h"

// Header file SynthSettings.h
class SynthSettings {
public:

	/** Structs holding fixed or semi-fixed initial parameters */
	osc_params_t osc_params;
	lfo_params_t lfo_params;
	mov_avg_params_t mov_avg_params;
	adsr_params_t adsr_params;

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

	void intDefaultSettings(void);

	static SynthSettings* getInstance(void){ // Unique point of access
			if (!pInstance_)
				pInstance_ = new SynthSettings;
			return pInstance_;
	}

private:
	SynthSettings(); // Prevent clients from creating a new SynthSettings
	SynthSettings(const SynthSettings&); // Prevent clients from creating
	// a copy of the SynthSettings
	static SynthSettings* pInstance_; // The one and only instance
};

#endif /* SYNTHSETTINGS_H_ */
