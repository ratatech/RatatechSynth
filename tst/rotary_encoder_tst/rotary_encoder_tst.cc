/*
@file adsr_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Apr 23, 2017
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

#include <stdio.h>
#include "unity.h"
#include "adsr.h"
#include "tst_utils.h"

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;

/**
 * Dummy object pool
 */
object_pool_t object_pool;


/**
 * Rotary encoder test
 */
void rotary_encoder_tst(void){

	while(1){
		iprintf("\n ROTARY ENCODER TEST -----------------------");
	}

}

int main(void)
{

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

	/** Init system and peripherals */
	ratatech_init(&synth_params);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    /** Wait usart confirmation to start the test  */
    wait_usart_ready();

	/** Ready to start test  */
    iprintf("\nTEST:  ROTARY ENCODER\n-----------------------");

    /** Start unity and trigger tests */
    UNITY_BEGIN();
    RUN_TEST(rotary_encoder_tst);

    /** FInish unity */
    return UNITY_END();
}
