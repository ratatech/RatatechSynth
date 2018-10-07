///***************************************************************************
// Product: ADSR example, STM32 NUCLEO-L152RE board, cooperative QV kernel
// Last updated for version 5.9.5
// Last updated on  2017-07-20
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// https://state-machine.com
// mailto:info@state-machine.com
//****************************************************************************
#include "qpcpp.h"
#include "hsm/bsp.h"
#include "_bsp.h"
#include "hsm/adsrHsm.h"

// add other drivers if necessary...
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"

Q_DEFINE_THIS_FILE
using namespace MAINBSP;
using namespace ADSRHSM;

// namespace QP **************************************************************
namespace QP {

// QS callbacks ==============================================================
#ifdef Q_SPY

//............................................................................
QSTimeCtr QS::onGetTime(void) {  // NOTE: invoked with interrupts DISABLED
//    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) { // not set?
//        return DPP::QS_tickTime_ - static_cast<QSTimeCtr>(SysTick->VAL);
//    }
//    else { // the rollover occured, but the SysTick_ISR did not run yet
//        return DPP::QS_tickTime_ + DPP::QS_tickPeriod_
//               - static_cast<QSTimeCtr>(SysTick->VAL);
//    }
}

#endif // Q_SPY

} // namespace QP

