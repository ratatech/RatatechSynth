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
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"
#include "_bsp.h"
#include "dpp.h"

using namespace QP;
using namespace DPP;

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

    iprintf("\n\nTEST: QSPY\n-----------------------\n");

    static QP::QEvt const *tableQueueSto[N_PHILO];
	static QP::QEvt const *philoQueueSto[N_PHILO][N_PHILO];
	static QP::QSubscrList subscrSto[MAX_PUB_SIG];
	static QF_MPOOL_EL(TableEvt) smlPoolSto[2*N_PHILO];

	QP::QF::init();  // initialize the framework and the underlying RT kernel

	BSP::init(argc, argv); // initialize the BSP

	// object dictionaries...
	QS_OBJ_DICTIONARY(AO_Table);
	QS_OBJ_DICTIONARY(AO_Philo[0]);
	QS_OBJ_DICTIONARY(AO_Philo[1]);
	QS_OBJ_DICTIONARY(AO_Philo[2]);
	QS_OBJ_DICTIONARY(AO_Philo[3]);
	QS_OBJ_DICTIONARY(AO_Philo[4]);
	QS_OBJ_DICTIONARY(smlPoolSto);

	// pause execution of the test and wait for the test script to continue
	QS_TEST_PAUSE();

	// initialize publish-subscribe...
	QP::QF::psInit(subscrSto, Q_DIM(subscrSto));

	// initialize event pools...
	QP::QF::poolInit(smlPoolSto,
				  sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

	// start the active objects...
	for (uint8_t n = 0U; n < N_PHILO; ++n) {
	 AO_Philo[n]->start((uint_fast8_t)(n + 1U), // priority
						philoQueueSto[n], Q_DIM(philoQueueSto[n]),
						(void *)0, 0U);
	}

	AO_Table->start((uint_fast8_t)(N_PHILO + 1U), // priority
				 tableQueueSto, Q_DIM(tableQueueSto),
				 (void *)0, 0U);

	return QP::QF::run(); // run the QF application
}





