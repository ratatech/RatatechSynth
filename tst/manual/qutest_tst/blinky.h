//$file${.::blinky.h} ########################################################
//
// Model: blinky.qm
// File:  ${.::blinky.h}
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
//$endhead${.::blinky.h} #####################################################

#ifndef blinky_h
#define blinky_h

using namespace QP;

enum BlinkySignals {
    DUMMY_SIG = Q_USER_SIG,
    MAX_PUB_SIG,  // the last published signal

    TIMEOUT_SIG,
    MAX_SIG       // the last signal
};

extern QActive * const AO_Blinky; // opaque pointer

#endif // blinky_h