/// @file
/// @brief QUTEST port for the EFM32-SLSTK3401A board
/// @ingroup qs
/// @cond
///***************************************************************************
/// Last updated for version 5.9.0
/// Last updated on  2017-05-17
///
///                    Q u a n t u m     L e a P s
///                    ---------------------------
///                    innovating embedded systems
///
/// Copyright (C) 2005-2017 Quantum Leaps, LLC. All rights reserved.
///
/// This program is open source software: you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as published
/// by the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Alternatively, this program may be distributed and modified under the
/// terms of Quantum Leaps commercial licenses, which expressly supersede
/// the GNU General Public License and are specifically designed for
/// licensees interested in retaining the proprietary status of their code.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <http://www.gnu.org/licenses/>.
///
/// Contact information:
/// https://state-machine.com
/// mailto:info@state-machine.com
///***************************************************************************
/// @endcond

#include "qpcpp.h"



//Q_DEFINE_THIS_MODULE("qutest_port")

using namespace QP;

// QS callbacks ==============================================================
bool QS::onStartup(void const *arg) {

    return true; // success
}
//............................................................................
void QS::onCleanup(void) {
}
//............................................................................
void QS::onFlush(void) {
}
//............................................................................
// callback function to reset the target (to be implemented in the BSP)
void QS::onReset(void) {
}
//............................................................................
void QS::onTestLoop() {
}
