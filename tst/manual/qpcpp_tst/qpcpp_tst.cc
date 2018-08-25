/*
@file qpc_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
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
#include "tst_utils.h"
#include "system_init.h"
#include "qpcpp.h"
#include "blinky.h"
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"
#include "bsp.h"

/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;


int main(void)
{

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */

    iprintf("\n\nTEST: QPC\n-----------------------\n");

    static QEvt const *blinkyQSto[10]; // Event queue storage for Blinky

    BSP_init(); // initialize the Board Support Package
    QF::init(); // initialize the framework and the underlying RT kernel

    // publish-subscribe not used, no call to QF::psInit()
    // dynamic event allocation not used, no call to QF::poolInit()

    // instantiate and start the active objects...
    AO_Blinky->start(1U,                            // priority
                     blinkyQSto, Q_DIM(blinkyQSto), // event queue
                     (void *)0, 0U);                // stack (unused)

    return QF::run(); // run the QF application

}





