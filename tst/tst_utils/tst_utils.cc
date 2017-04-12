/*
@file tst_utils.cc

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
#include "tst_utils.h"

/**
 * Wait usart interface until is ready
 */
void wait_usart_ready(void) {

	/** Wait for value 1( ASCII 49) as uart confirmation  */
	while( USART_ReceiveData(USART2) != 49)

	/** Debug usart confirmation  */
	if(0){
		iprintf("Received data = ");
		uint16_t uart_in = USART_ReceiveData(USART2);
		UnityPrintNumber((UNITY_INT)uart_in);
		iprintf("\n");
	}

	/** Ready to start test  */
    iprintf("\nTEST:  Oscillator\n-----------------------");

}

/**
 * Convert integers to char strings
 * @param num an integer
 */
void intNum2CharStr(int32_t num){
	static char string[11];
	sprintf(string, "%d", num);
	iprintf((const char*)string);
}

/**
 * Print output buffer
 * @param buff_name The name of the buffer to be printed
 * @param p_out_buff Pointer to the output buffer
 * @param buff_size Buffer size
 */
void printOutBuff(const char * buff_name, int32_t* p_out_buff, uint16_t buff_size){

	iprintf("\n");
	iprintf(buff_name);
	iprintf("= [");
	for(int j=0; j<buff_size;  j++ ){
		intNum2CharStr(*p_out_buff++);
		iprintf(",");
	}
	iprintf("]\n");

}
