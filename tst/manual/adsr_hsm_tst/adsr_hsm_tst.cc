/*
@file adsr_hsm_tst.cc

@brief Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.

@ Created by Jordi Hidalgo, Ratatech, Jun 13, 2017
This file is part of Ratatech 3019

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

#include <stdio.h>
#include "unity.h"
#include "tst_utils.h"
#include "system_init.h"
#include "qpcpp.h"
#include "stm32f10x_conf.h"
#include "stm32f10x.h"
#include "hsm/adsrHsm.h"
#include "hsm/bsp.h"
#include "_bsp.h"

using namespace QP;
using namespace ADSRHSM;
using namespace MAINBSP;

Q_DEFINE_THIS_FILE

/**
 * Dummy object pool
 */
object_pool_t object_pool;

/**
 * Structure holding the main synth parameters
 */
synth_params_t synth_params;



int main(int argc, char *argv[]) {

	/** Init system and peripherals */
	ratatech_init(&synth_params);

	/** Load initial default settings */
	init_settings(&synth_params,object_pool);

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	/** Ready to start test  */

    iprintf("\n\nTEST: MANUAL ADSR HSM\n-----------------------\n");

    static QEvt const *adsrQSto[10]; // Event queue storage for Adsr

    QF::init(); // initialize the framework and the underlying RT kernel
    BSP::init(argc, argv); // initialize the BSP

	// object dictionaries...
	QS_OBJ_DICTIONARY(ADSRHSM::AO_Adsr);
	QS_OBJ_DICTIONARY(adsrQSto);

    // publish-subscribe not used, no call to QF::psInit()
    // dynamic event allocation not used, no call to QF::poolInit()
    // initialize event pools...
    QP::QF::poolInit(adsrQSto,
                     sizeof(adsrQSto), sizeof(adsrQSto[0]));

    // instantiate and start the active objects...
    ADSRHSM::AO_Adsr->start(1U,                            // priority
                     adsrQSto, Q_DIM(adsrQSto), // event queue
                     (void *)0, 0U);                // stack (unused)

    return QF::run(); // run the QF application
}





