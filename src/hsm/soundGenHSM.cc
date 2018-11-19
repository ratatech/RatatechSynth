//$file${.::soundGenHSM.cc} ##################################################
//
// Model: synthControl.qm
// File:  ${.::soundGenHSM.cc}
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
//$endhead${.::soundGenHSM.cc} ###############################################

#include "soundGenHSM.h"

using namespace QP;
using namespace MAINBSP;

Q_DEFINE_THIS_FILE

//*============== ask QM to declare the Blinky class ================*/
//$declare${AOs::SoundGenHSM} ################################################
//${AOs::SoundGenHSM} ........................................................
class SoundGenHSM : public QP::QActive {
private:
    QP::QTimeEvt m_timeEvt;

public:
    SoundGenHSM();

protected:
    static QP::QState initial(SoundGenHSM * const me, QP::QEvt const * const e);
    static QP::QState active(SoundGenHSM * const me, QP::QEvt const * const e);
    static QP::QState start(SoundGenHSM * const me, QP::QEvt const * const e);
    static QP::QState fillFrame(SoundGenHSM * const me, QP::QEvt const * const e);
};
//$enddecl${AOs::SoundGenHSM} ################################################

// local objects --------------------------------------------------------------
SoundGenHSM l_soundGenHSM;

// global objects ------------------------------------------------------------
QActive * const AO_SoundGenHSM = &l_soundGenHSM; // opaque pointer

/*================ ask QM to define the Blinky class ================*/
// Check for the minimum required QP version
#if (QP_VERSION < 630U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpcpp version 6.3.0 or higher required
#endif

//$define${AOs::SoundGenHSM} #################################################
//${AOs::SoundGenHSM} ........................................................
//${AOs::SoundGenHSM::SoundGenHSM} ...........................................
SoundGenHSM::SoundGenHSM()
  : QActive(Q_STATE_CAST(&SoundGenHSM::initial)),
    m_timeEvt(this, TIMEOUT_SIG, 0U)
{}

//${AOs::SoundGenHSM::SM} ....................................................
QP::QState SoundGenHSM::initial(SoundGenHSM * const me, QP::QEvt const * const e) {
    //${AOs::SoundGenHSM::SM::initial}

    QS_FUN_DICTIONARY(&active);
    QS_FUN_DICTIONARY(&start);
    QS_FUN_DICTIONARY(&fillFrame);

    return Q_TRAN(&start);
}
//${AOs::SoundGenHSM::SM::active} ............................................
QP::QState SoundGenHSM::active(SoundGenHSM * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::SoundGenHSM::SM::active::FILL_FRAME}
        case FILL_FRAME_SIG: {
            status_ = Q_TRAN(&fillFrame);
            break;
        }
        default: {
            status_ = Q_SUPER(&top);
            break;
        }
    }
    return status_;
}
//${AOs::SoundGenHSM::SM::active::start} .....................................
QP::QState SoundGenHSM::start(SoundGenHSM * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::SoundGenHSM::SM::active::start}
        case Q_ENTRY_SIG: {
            /** Start sound generator */
            soundGenStart();

            /** Fill first frame */
            fillBuffer();
            fillBuffer();

            /** Enable audio output ISR*/
            TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
            TIM_Cmd(TIM1, ENABLE);

            /** Enable fill buffer ISR*/
            TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
            TIM_Cmd(TIM2, ENABLE);
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&active);
            break;
        }
    }
    return status_;
}
//${AOs::SoundGenHSM::SM::active::fillFrame} .................................
QP::QState SoundGenHSM::fillFrame(SoundGenHSM * const me, QP::QEvt const * const e) {
    QP::QState status_;
    switch (e->sig) {
        //${AOs::SoundGenHSM::SM::active::fillFrame}
        case Q_ENTRY_SIG: {
            fillBuffer();
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&active);
            break;
        }
    }
    return status_;
}
//$enddef${AOs::SoundGenHSM} #################################################


