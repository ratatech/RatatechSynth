/*
@file dither_generator.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Aug 19, 2018
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

#include "dither_generator.h"

/**
 * @brief Update dithering pattern
 * @param duCy High resolution duty cicle (matching PWM resolution + DITHER_BITS)
 */
void DitherGen::updatePattern(uint16_t duCy){
	selectedPattern = duCy & DITHER_LSB_MASK;
	for(int i=0;i<DITHER_RES;i++){
		ditheringPattern[i] = dithering_lut[selectedPattern][i];
	}
}

/**
 * Set dithered duty cycle for Capture Compare 1 Register value
 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
 */
void DitherGen::setDuCy1(uint16_t duCy, TIM_TypeDef* TIMx){
	TIMx->CCR1 = duCy + updateDitheringVal();
}

/**
 * Set dithered duty cycle for Capture Compare 2 Register value
 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
 */
void DitherGen::setDuCy2(uint16_t duCy, TIM_TypeDef* TIMx){
	TIMx->CCR2 = duCy + updateDitheringVal();
}

/**
 * Set dithered duty cycle for Capture Compare 3 Register value
 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
 */
void DitherGen::setDuCy3(uint16_t duCy, TIM_TypeDef* TIMx){
	TIMx->CCR3 = duCy + updateDitheringVal();
}

/**
 * Set dithered duty cycle for Capture Compare 4 Register value
 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
 */
void DitherGen::setDuCy4(uint16_t duCy, TIM_TypeDef* TIMx){
	TIMx->CCR4 = duCy + updateDitheringVal();
}

/**
 *  Update dithering value
 * @return ditheringVal Dithering value form the current pattern (1/0)
 */
uint8_t DitherGen::updateDitheringVal(void){

	/** Get new dithering value */
	uint8_t ditheringVal = ditheringPattern[ditherIndex];

	/** Increase dithering table index */
	ditherIndex++;
	ditherIndex%=DITHER_RES;

	return(ditheringVal);
}
