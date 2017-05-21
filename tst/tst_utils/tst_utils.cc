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
	iprintf("SHIIIIITTT");
	/** Wait for value 1( ASCII 49) as uart confirmation  */
	while( USART_ReceiveData(USART_TST) != 49)

	/** Debug usart confirmation  */
	if(0){
		iprintf("Received data = ");
		uint16_t uart_in = USART_ReceiveData(USART_TST);
		UnityPrintNumber((UNITY_INT)uart_in);
		iprintf("\n");
	}

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
 * Print output buffer to serial output
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

/** This function is used to transmit a string of characters via
 * the USART specified in USARTx.
 *
 * It takes two arguments: USARTx --> can be any of the USARTs e.g. USART1, USART2 etc.
 * 						   (volatile) char *s is the string you want to send
 *
 * Note: The string has to be passed to the function as a pointer because
 * 		 the compiler doesn't know the 'string' data type. In standard
 * 		 C a string is just an array of characters
 *
 * Note 2: At the moment it takes a volatile char because the received_string variable
 * 		   declared as volatile char --> otherwise the compiler will spit out warnings
 *
 * @param USARTx Usart instance
 * @param s Pointer to the string to be sent through USART
 */
void USART_puts(USART_TypeDef* USARTx, const char *s){

	while(*s){
		// wait until data register is empty
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *s);
		*s++;
	}
}

/**
 * Print output buffer to specified usart port
 * @param USARTx Usart instance
 * @param buff_name The name of the buffer to be printed
 * @param p_out_buff Pointer to the output buffer
 * @param buff_size Buffer size
 */
void printUSARTOutBuff(USART_TypeDef* USARTx, const char * buff_name, int32_t* p_out_buff, uint16_t buff_size){

	iprintf("\n");
	iprintf(buff_name);
	iprintf("= [");
	for(int j=0; j<buff_size;  j++ ){
		intNum2CharStr(*p_out_buff++);
		iprintf(",");
	}
	iprintf("]\n");

}


/**
 * Delay for "cnt" NOPs.
 *
 * @param[in]	cnt	number of NOPs to delay
 */
void delay_nops(int cnt) {
    while (cnt-- > 0) {
        asm("nop");
    }
}
