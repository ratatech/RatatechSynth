//$file${.::blinky.cc} #######################################################
//
// Model: blinky.qm
// File:  ${.::blinky.cc}
//
// This code has been generated by QM 4.3.0 (https://www.state-machine.com/qm).
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
//$endhead${.::blinky.cc} ####################################################
#include "qpcpp.h"
#include "blinky.h"

#include <hsm/bsp.h>
#include <stdio.h>
#include <stdlib.h> /* for exit() */

using namespace QP;

Q_DEFINE_THIS_FILE

//*============== ask QM to declare the Blinky class ================*/
//$declare${AOs::Blinky} #####################################################
//${AOs::Blinky} .............................................................
class Blinky : public QP::QActive {
private:
    QP::QTimeEvt m_timeEvt;

public:
    Blinky();

protected:
    static QP::QState initial(Blinky * const me, QP::QEvt const * const e);
    static QP::QState off(Blinky * const me, QP::QEvt const * const e);
    static QP::QState on(Blinky * const me, QP::QEvt const * const e);
};
//$enddecl${AOs::Blinky} #####################################################

// local objects --------------------------------------------------------------
Blinky l_blinky;

// global objects ------------------------------------------------------------
QActive * const AO_Blinky = &l_blinky; // opaque pointer

/*================ ask QM to define the Blinky class ================*/
// Check for the minimum required QP version
#if (QP_VERSION < 630U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.3.0 or higher required
#endif

//$define${AOs::Blinky} ######################################################
//${AOs::Blinky} .............................................................
//${AOs::Blinky::Blinky} .....................................................
Blinky::Blinky()
  : QActive(Q_STATE_CAST(&Blinky::initial)),
    m_timeEvt(this, TIMEOUT_SIG, 0U)
{}

//${AOs::Blinky::SM} .........................................................
QP::QState Blinky::initial(Blinky * const me, QP::QEvt const * const e) {
    //${AOs::Blinky::SM::initial}
    me->m_timeEvt.armX(BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
    return Q_TRAN(&off);
}
//${AOs::Blinky::SM::off} ....................................................
QP::QState Blinky::off(Blinky * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::off}
        case Q_ENTRY_SIG: {
            BSP_ledOff();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::off::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&on);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Blinky::SM::on} .....................................................
QP::QState Blinky::on(Blinky * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Blinky::SM::on}
        case Q_ENTRY_SIG: {
            BSP_ledOn();
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Blinky::SM::on::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&off);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::Blinky} ######################################################


