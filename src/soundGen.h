/*
@file soundGen.h

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Oct 9, 2018
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
#ifndef SOUNDGEN_H_
#define SOUNDGEN_H_

#include "stm32f10x.h"
#include "circular_buffer.h"
#include "audio_out.h"
#include "oscillator.h"

extern "C" {

/**
  * @brief  This function handles Timer 1 Handler.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler(void);

/**
 * @brief  This function handles DMA1 channel 2 Handler.
 */
void DMA1_Channel2_IRQHandler(void);

}

/**
 * @brief Fill the main buffer containing the output audio samples
 */
void fillBuffer(void);

#endif /* SOUNDGEN_H_ */
