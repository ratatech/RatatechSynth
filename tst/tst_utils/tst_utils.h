/*
@file tst_utils.h

@brief A set of small functions used commonly by the unit tests

@ Created by Jordi Hidalgo, Ratatech, Apr 12, 2017
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
#ifndef TST_TST_UTILS_TST_UTILS_H_
#define TST_TST_UTILS_TST_UTILS_H_

#include<string>
#include <stdio.h>
#include "unity.h"
#include "ratatechSynth.h"


/**
 * Wait usart interface until is ready
 */
void wait_usart_ready(void);

/**
 * Convert integers to char strings
 * @param num an integer
 */
void intNum2CharStr(int32_t num);

/**
 * Print output buffer
 * @param buff_name The name of the buffer to be printed
 * @param p_out_buff Pointer to the output buffer
 * @param buff_size Buffer size
 */
void printOutBuff(const char * buff_name, int32_t* p_out_buff, uint16_t buff_size);


#endif /* TST_TST_UTILS_TST_UTILS_H_ */
