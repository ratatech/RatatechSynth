/*
@file svf.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, May 2, 2017
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

#include "svf.h"

void Svf::configure(synth_params_t* synth_params){

	uint8_t sreg_byte = 0;
	uint8_t SVF_order_msk,SVF_SC_EN_msk;

	/* Filter modes
	 * LP = 0x06
	 * BP = 0x05
	 * HP = 0x03
	 */
	sreg_byte = 0x06;

	/* Filter order 12/24 dB/Oct
	 * 12 = 0x10
	 * 24 = 0x08
	 */
	SVF_order_msk = 0x08;

	// Add order to select filter order
	sreg_byte += SVF_order_msk;

	/* Enable/Disable SC
	 * ON  = 0x00
	 * OFF = 0x20
	 */
	SVF_SC_EN_msk = 0x20;

	// Add soft clipping enabler
	sreg_byte += SVF_SC_EN_msk;

	for(int w=0;w<SHIFT_REGISTER_BITS;w++){
		// LATCH Low
		GPIOA->BRR = GPIO_Pin_11;

		// Transmit the two 8bit SPI messages
		SPI_send(SPI2,sreg_byte);

		// CS High
		GPIOA->BSRR = GPIO_Pin_11;
		// LATCH Low
		GPIOA->BRR = GPIO_Pin_11;

	}

	if(SVF_order_msk == 0x08){
		PWM_SVF = (PWM_PERIOD>>1);
	}else{
		PWM_SVF = PWM_PERIOD;
	}

}

/**
 * Set filter resonance
 * @param q Filter resonance [0..PWM_PERIOD]
 */
void Svf::set_q(synth_params_t* synth_params){
	uint32_t q = (uint32_t)(synth_params->mux_adc_0_out.mux_y[0]*PWM_SVF)>>12;
	TIM3->CCR2 = q;
}

/**
 * Set filter cutoff frequency
 * @param fc Cutoff frequency  [0..PWM_PERIOD]
 */
void Svf::set_fc(synth_params_t* synth_params){
	uint32_t fc_adc = (uint32_t)(synth_params->mux_adc_1_out.mux_x[1]*PWM_PERIOD)>>12;

	uint32_t fc_env = (uint32_t)(synth_params->adsr_vol_amp*PWM_PERIOD)>>15;

	uint32_t fc_lfo = (uint32_t)((*(synth_params->lfo_amp))*(PWM_PERIOD))>>15;

	// Scale ADSR envelope with the adc knob fc selection.
	//fc_adc = ((uint32_t)fc_adc * fc_env)>>15;
	//fc_adc = (fc_adc * ((uint32_t)(synth_params->lfo_amp*PWM_PERIOD)>>15) )>>15;
	TIM3->CCR4 = PWM_PERIOD - (fc_adc-fc_env);
	//TIM3->CCR4 = PWM_PERIOD-fc_env;
//		TIM3->CCR4 = PWM_PERIOD - fc_adc;
//		TIM3->CCR4 = PWM_PERIOD - fc_adc;
//		TIM3->CCR4 = PWM_PERIOD-fc_env;
//		TIM3->CCR4 = PWM_PERIOD - ((fc_adc * fc_lfo)>>15);
	//TIM3->CCR4 = PWM_PERIOD - (fc_lfo);

}
