/*
@file ratatechSynth.cc

@brief Main Ratatech 3019 synth file

@ Created by Jordi Hidalgo, Ratatech, Oct 8, 2018
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

#include <stdio.h>
#include "hsm/bsp.h"
#include "unity.h"
#include "tst_utils.h"
#include "system_init.h"
#include "qpcpp.h"
#include "hsm/soundGenHSM.h"
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"
#include "ratatechSynth.h"

using namespace QP;
using namespace MAINBSP;
Q_DEFINE_THIS_FILE


int main(int argc, char *argv[])
{
    /** Unique instance of SynthSettings **/
    SynthSettings* s = SynthSettings::getInstance();

    /** Init instance with default settings **/
    s->intDefaultSettings();

	/** Init system and peripherals */
	ratatech_init();

    /** Turn off buffers, so IO occurs immediately  */
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    static QF_MPOOL_EL(QEvt) smlPoolSto[10]; // storage for small pool
    static QEvt const *soundGenHSMQSto[10]; // event queue storage for soundGenHSM

    QF::init();  // initialize the framework

    // initialize the QS software tracing
    Q_ALLEGE(QS_INIT(argc > 1 ? argv[1] : (void *)0));

    BSP::init(); // initialize the BSP

    // dictionaries...
    QS_OBJ_DICTIONARY(smlPoolSto);
    QS_OBJ_DICTIONARY(soundGenHSMQSto);

    QS_SIG_DICTIONARY(TIMEOUT_SIG, (void *)0);


    // publish-subscribe not used, no call to QF_psInit()

    // initialize event pools...
    QF::poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    // start the active objects...
    AO_SoundGenHSM->start(1U,
                     soundGenHSMQSto, Q_DIM(soundGenHSMQSto),
                     (void *)0, 0U, (QEvt *)0);

    return QF::run();

}





