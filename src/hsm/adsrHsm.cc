//$file${.::adsrHsm.cc} ######################################################
//
// Model: adsrHsm.qm
// File:  ${.::adsrHsm.cc}
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
//$endhead${.::adsrHsm.cc} ###################################################
#include "qpcpp.h"
#include "adsrHsm.h"
#include "bsp.h"
#include <stdio.h>
#include <stdlib.h> /* for exit() */

//Q_DEFINE_THIS_FILE

//$declare${AOs::Adsr} #######################################################
namespace ADSRHSM {

//${AOs::Adsr} ...............................................................
class Adsr : public QP::QActive {
private:
    QP::QTimeEvt m_timeEvt;

public:
    Adsr();

protected:
    static QP::QState initial(Adsr * const me, QP::QEvt const * const e);
    static QP::QState idle(Adsr * const me, QP::QEvt const * const e);
    static QP::QState attack(Adsr * const me, QP::QEvt const * const e);
    static QP::QState decay(Adsr * const me, QP::QEvt const * const e);
    static QP::QState sustain(Adsr * const me, QP::QEvt const * const e);
    static QP::QState release(Adsr * const me, QP::QEvt const * const e);
};

} // namespace ADSRHSM
//$enddecl${AOs::Adsr} #######################################################

namespace ADSRHSM {

// local objects -------------------------------------------------------------
static Adsr l_adsr; // the sole instance of the Adsr active object

} // namespace ADSRHSM

// Public-scope objects ------------------------------------------------------
// Check for the minimum required QP version
#if (QP_VERSION < 630U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.3.0 or higher required
#endif

//$define${AOs::AO_Adsr} #####################################################
namespace ADSRHSM {

//${AOs::AO_Adsr} ............................................................
QP::QActive *const AO_Adsr = &l_adsr;

} // namespace ADSRHSM
//$enddef${AOs::AO_Adsr} #####################################################

// Active object definition --------------------------------------------------
//$define${AOs::Adsr} ########################################################
namespace ADSRHSM {

//${AOs::Adsr} ...............................................................
//${AOs::Adsr::Adsr} .........................................................
Adsr::Adsr()
  : QActive(Q_STATE_CAST(&Adsr::initial)),
    m_timeEvt(this, TIMEOUT_SIG, 0U)
{
    // body
}

//${AOs::Adsr::SM} ...........................................................
QP::QState Adsr::initial(Adsr * const me, QP::QEvt const * const e) {
    //${AOs::Adsr::SM::initial}
    me->m_timeEvt.armX(BSP_TICKS_PER_SEC/2, BSP_TICKS_PER_SEC/2);
    return Q_TRAN(&idle);
}
//${AOs::Adsr::SM::idle} .....................................................
QP::QState Adsr::idle(Adsr * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Adsr::SM::idle}
        case Q_ENTRY_SIG: {
            iprintf("\nADSR_HSM ---------------------> IDLE STATE");
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Adsr::SM::idle::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&attack);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Adsr::SM::attack} ...................................................
QP::QState Adsr::attack(Adsr * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Adsr::SM::attack}
        case Q_ENTRY_SIG: {
            iprintf("\nADSR_HSM ---------------------> ATTACK STATE");
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Adsr::SM::attack::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&decay);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Adsr::SM::decay} ....................................................
QP::QState Adsr::decay(Adsr * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Adsr::SM::decay}
        case Q_ENTRY_SIG: {
            iprintf("\nADSR_HSM ---------------------> DECAY STATE");
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Adsr::SM::decay::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&sustain);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Adsr::SM::sustain} ..................................................
QP::QState Adsr::sustain(Adsr * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Adsr::SM::sustain}
        case Q_ENTRY_SIG: {
            iprintf("\nADSR_HSM ---------------------> SUSTAIN STATE");
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Adsr::SM::sustain::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&release);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::Adsr::SM::release} ..................................................
QP::QState Adsr::release(Adsr * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::Adsr::SM::release}
        case Q_ENTRY_SIG: {
            iprintf("\nADSR_HSM ---------------------> RELEASE STATE");
            status_ = Q_HANDLED();
            break;
        }
        //${AOs::Adsr::SM::release::TIMEOUT}
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&idle);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}

} // namespace ADSRHSM
//$enddef${AOs::Adsr} ########################################################
