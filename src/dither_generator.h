/*
@file dither_generator.h

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
#ifndef DITHER_GENERATOR_H_
#define DITHER_GENERATOR_H_

#include "tables.h"
#include "stm32f10x_tim.h"

/** Dithering resolution, 2^N bits of enhancement */
#define DITHER_BITS 4
#define DITHER_RES 1 << DITHER_BITS

/** Dithering LSB mask used to determine the pattern */
#define DITHER_LSB_MASK 0xF

/**
 * Dithering generator class
 */
class DitherGen{

private:

	/** Diethering pattern */
	uint8_t ditheringPattern[DITHER_RES] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	/** Diether variables */
	uint8_t ditherIdx	 	= 0;
	uint8_t selectedPattern = 0;
	uint8_t ditherIndex		= 0;

	/**
	 *  Update dithering value
	 * @return ditheringVal Dithering value form the current pattern (1/0)
	 */
	uint8_t updateDitheringVal(void);

public:


	/** Constructor.
	 *
	 */
	DitherGen(void){

	}

	/**
	 * @brief Update dithering pattern
	 * @param duCy High resolution duty cicle (matching PWM resolution + DITHER_BITS)
	 */
	void updatePattern(uint16_t duCy);

	/**
	 * Set dithered duty cycle for Capture Compare 1 Register value
	 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
	 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
	 */
	void setDuCy1(uint16_t duCy, TIM_TypeDef* TIMx);

	/**
	 * Set dithered duty cycle for Capture Compare 2 Register value
	 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
	 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
	 */
	void setDuCy2(uint16_t duCy, TIM_TypeDef* TIMx);

	/**
	 * Set dithered duty cycle for Capture Compare 3 Register value
	 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
	 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
	 */
	void setDuCy3(uint16_t duCy, TIM_TypeDef* TIMx);

	/**
	 * Set dithered duty cycle for Capture Compare 4 Register value
	 * @param duCy 			Low resolution duty cycle (matching PWM resolution)
	 * @param TIMx where x can be 1 to 17 to select the TIM peripheral.
	 */
	void setDuCy4(uint16_t duCy, TIM_TypeDef* TIMx);

};




#endif /* DITHER_GENERATOR_H_ */
