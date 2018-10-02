///***************************************************************************
// Product: DPP example, STM32 NUCLEO-L152RE board, cooperative QV kernel
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
#include "dpp.h"
#include "_bsp.h"

// add other drivers if necessary...
#include "stm32f10x_conf.h"
#include "system_init.h"
#include "stm32f10x.h"

Q_DEFINE_THIS_FILE

// namespace DPP *************************************************************
namespace DPP {

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
// DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
//
enum KernelUnawareISRs { // see NOTE00
    // ...
    MAX_KERNEL_UNAWARE_CMSIS_PRI  // keep always last
};
// "kernel-unaware" interrupts can't overlap "kernel-aware" interrupts
Q_ASSERT_COMPILE(MAX_KERNEL_UNAWARE_CMSIS_PRI <= QF_AWARE_ISR_CMSIS_PRI);

enum KernelAwareISRs {
    EXTI0_PRIO = QF_AWARE_ISR_CMSIS_PRI, // see NOTE00
    SYSTICK_PRIO,
    // ...
    MAX_KERNEL_AWARE_CMSIS_PRI // keep always last
};
// "kernel-aware" interrupts should not overlap the PendSV priority
Q_ASSERT_COMPILE(MAX_KERNEL_AWARE_CMSIS_PRI <= (0xFF >>(8-__NVIC_PRIO_BITS)));

// Local-scope objects -------------------------------------------------------
// LED pins available on the board (just one user LED LD2--Green on PA.5)
#define LED_LD2  (1U << 5)

// Button pins available on the board (just one user Button B1 on PC.13)
#define BTN_B1   (1U << 13)

static uint32_t l_rnd; // random seed

enum {
	BSP_CALL = QP::QS_USER,
};

#ifdef Q_SPY

QP::QSTimeCtr QS_tickTime_;
QP::QSTimeCtr QS_tickPeriod_;

// event-source identifiers used for tracing
static uint8_t const l_SysTick_Handler    = 0U;
static uint8_t const l_EXTI0_IRQHandler = 0U;

#endif

// ISRs used in this project =================================================
extern "C" {

//............................................................................
void SysTick_Handler(void); // prototype
void SysTick_Handler(void) {
    // state of the button debouncing, see below
    static struct ButtonsDebouncing {
        uint32_t depressed;
        uint32_t previous;
    } buttons = { ~0U, ~0U };
    uint32_t current;
    uint32_t tmp;

#ifdef Q_SPY
    {
        tmp = SysTick->CTRL; // clear SysTick_CTRL_COUNTFLAG
        QS_tickTime_ += QS_tickPeriod_; // account for the clock rollover
    }
#endif

    QP::QF::TICK_X(0U, &l_SysTick_Handler); // process time events for rate 0

    // Perform the debouncing of buttons. The algorithm for debouncing
    // adapted from the book "Embedded Systems Dictionary" by Jack Ganssle
    // and Michael Barr, page 71.
    //
    current = ~GPIOC->IDR; // read Port C with the state of Button B1
    tmp = buttons.depressed; // save the debounced depressed buttons
    buttons.depressed |= (buttons.previous & current); // set depressed
    buttons.depressed &= (buttons.previous | current); // clear released
    buttons.previous   = current; // update the history
    tmp ^= buttons.depressed;     // changed debounced depressed
//    if ((tmp & BTN_B1) != 0U) {  // debounced BTN_B1 state changed?
//        if ((buttons.depressed & BTN_B1) != 0U) { // is BTN_B1 depressed?
//            static QP::QEvt const pauseEvt = { DPP::PAUSE_SIG, 0U, 0U};
//            QP::QF::PUBLISH(&pauseEvt, &l_SysTick_Handler);
//        }
//        else {            // the button is released
//            static QP::QEvt const serveEvt = { DPP::SERVE_SIG, 0U, 0U};
//            QP::QF::PUBLISH(&serveEvt, &l_SysTick_Handler);
//        }
//    }
}
//............................................................................
void EXTI0_IRQHandler(void); // prototype
void EXTI0_IRQHandler(void) {
    // for testing..
    DPP::AO_Table->POST(Q_NEW(QP::QEvt, DPP::MAX_PUB_SIG),
                        &l_EXTI0_IRQHandler);
}

// ISR for receiving bytes from the QSPY Back-End
// NOTE: This ISR is "QF-unaware" meaning that it does not interact with
// the QF/QK and is not disabled. Such ISRs don't need to call QK_ISR_ENTRY/
// QK_ISR_EXIT and they cannot post or publish events.
//
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
    	uint16_t b = USART_ReceiveData(USART2);
        QP::QS::rxPut(b);
    }
}



} // extern "C"

// BSP functions =============================================================

void BSP::ledOff(void) {
	iprintf("\nBLINKY: LED -----------------------> OFF");

	// Set LED2 on nucleo board ---> OFF
	GPIOA->BRR = GPIO_Pin_5;

	// Set LED/D3 on PCB ---> OFF
	GPIOB->BRR = GPIO_Pin_11;
}
//............................................................................
void BSP::ledOn(void) {
	iprintf("\nBLINKY: LED -----------------------> ON");

	// Set LED2 on nucleo board --->  ON
	GPIOA->BSRR = GPIO_Pin_5;

	// Set LED/D3 on PCB ---> ON
	GPIOB->BSRR = GPIO_Pin_11;

}

// BSP functions =============================================================
void BSP::init(int argc, char **argv) {
    Q_ALLEGE(QS_INIT(argc <= 1 ? (void *)0 : argv[1]));

    QS_FUN_DICTIONARY(&BSP::displayPaused);
    QS_FUN_DICTIONARY(&BSP::displayPhilStat);
    QS_FUN_DICTIONARY(&BSP::random);
    QS_FUN_DICTIONARY(&BSP::randomSeed);
    QS_FUN_DICTIONARY(&QP::QHsm::top);

    QS_USR_DICTIONARY(BSP_CALL);

    BSP::randomSeed(1234U);
}
//............................................................................
void BSP::displayPaused(uint8_t paused) {
    QS_TEST_PROBE_DEF(&BSP::displayPaused)

    QS_TEST_PROBE(
        Q_ASSERT_ID(100, 0);
    )
    QS_BEGIN(BSP_CALL, 0) // application-specific record
        QS_FUN(&BSP::displayPaused);
        QS_U8(0, paused);
    QS_END()
}
//............................................................................
void BSP::displayPhilStat(uint8_t n, char const *stat) {
    QS_BEGIN(BSP_CALL, 0) // application-specific record
        QS_FUN(&BSP::displayPhilStat);
        QS_U8(0, n);
        QS_STR(stat);
    QS_END()
}
//............................................................................
uint32_t BSP::random(void) {
    QS_TEST_PROBE_DEF(&BSP::random)
    uint32_t rnd = 123U;

    QS_TEST_PROBE(
        rnd = qs_tp_;
    )
    QS_BEGIN(BSP_CALL, 0) // application-specific record
        QS_FUN(&BSP::random);
        QS_U32(0, rnd);
    QS_END()
    return rnd;
}
//............................................................................
void BSP::randomSeed(uint32_t seed) {
    QS_TEST_PROBE_DEF(&BSP::randomSeed)

    QS_TEST_PROBE(
        seed = qs_tp_;
    )
    l_rnd = seed;
    QS_BEGIN(BSP_CALL, 0) // application-specific record
        QS_FUN(&BSP::randomSeed);
        QS_U32(0, seed);
    QS_END()
}

//............................................................................
void BSP::terminate(int16_t result) {
    (void)result;
}

} // namespace DPP

// namespace QP **************************************************************
namespace QP {

//// QF callbacks ==============================================================
//void QF::onStartup(void) {
//    // set up the SysTick timer to fire at BSP::TICKS_PER_SEC rate
//    SysTick_Config(SystemCoreClock / DPP::BSP::TICKS_PER_SEC);
//
//    // set priorities of ALL ISRs used in the system, see NOTE00
//    //
//    // !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    // Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
//    // DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
//    //
//    NVIC_SetPriority(SysTick_IRQn, DPP::SYSTICK_PRIO);
//    NVIC_SetPriority(EXTI0_IRQn,   DPP::EXTI0_PRIO);
//    // ...
//
//    // enable IRQs...
//    NVIC_EnableIRQ(EXTI0_IRQn);
//}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QV::onIdle(void) { // called with interrupts disabled, see NOTE01
    // toggle the User LED on and then off (not enough LEDs, see NOTE02)
	GPIOB->BSRR |= GPIO_Pin_11;  // turn LED on
	GPIOB->BRR |= GPIO_Pin_11;  // turn LED off

#ifdef Q_SPY
    QF_INT_ENABLE();
    if ((USART2->SR & 0x0080U) != 0) {  // is TXE empty?
        QF_INT_DISABLE();
        uint16_t b = QS::getByte();
        QF_INT_ENABLE();

        if (b != QS_EOD) {  // not End-Of-Data?
            USART2->DR  = (b & 0xFFU);  // put into the DR register
        }
    }
#elif defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M3 MCU.
    //
    // !!!CAUTION!!!
    // The WFI instruction stops the CPU clock, which unfortunately disables
    // the JTAG port, so the ST-Link debugger can no longer connect to the
    // board. For that reason, the call to __WFI() has to be used with CAUTION.
    //
    // NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
    // reset the board, then connect with ST-Link Utilities and erase the part.
    // The trick with BOOT(0) is it gets the part to run the System Loader
    // instead of your broken code. When done disconnect BOOT0, and start over.
    //
    //QV_CPU_SLEEP();  // atomically go to sleep and enable interrupts
    QF_INT_ENABLE(); // for now, just enable interrupts
#else
    QF_INT_ENABLE(); // just enable interrupts
#endif
}

//............................................................................
//extern "C" void Q_onAssert(char const *module, int loc) {
//    //
//    // NOTE: add here your application-specific error handling
//    //
//    (void)module;
//    (void)loc;
//    QS_ASSERTION(module, loc, static_cast<uint32_t>(10000U));
//    NVIC_SystemReset();
//}

// QS callbacks ==============================================================
#ifdef Q_SPY

/*..........................................................................*/
#define __DIV(__PCLK, __BAUD)       (((__PCLK / 4U) * 25U)/(__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100U)
#define __DIVFRAQ(__PCLK, __BAUD)   \
    (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100U)) \
        * 16U + 50U) / 100U)
#define __USART_BRR(__PCLK, __BAUD) \
    ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0FU))


//............................................................................
bool QS::onStartup(void const *arg) {
    static uint8_t qsTxBuf[2*1024]; // buffer for QS transmit channel
    static uint8_t qsRxBuf[100];    // buffer for QS receive channel

    initBuf  (qsTxBuf, sizeof(qsTxBuf));
    rxInitBuf(qsRxBuf, sizeof(qsRxBuf));

    DPP::QS_tickPeriod_ = SystemCoreClock / DPP::BSP::TICKS_PER_SEC;
    DPP::QS_tickTime_ = DPP::QS_tickPeriod_; // to start the timestamp at zero

//    // setup the QS filters...
//    QS_FILTER_ON(QS_QEP_STATE_ENTRY);
//    QS_FILTER_ON(QS_QEP_STATE_EXIT);
//    QS_FILTER_ON(QS_QEP_STATE_INIT);
//    QS_FILTER_ON(QS_QEP_INIT_TRAN);
//    QS_FILTER_ON(QS_QEP_INTERN_TRAN);
//    QS_FILTER_ON(QS_QEP_TRAN);
//    QS_FILTER_ON(QS_QEP_IGNORED);
//    QS_FILTER_ON(QS_QEP_DISPATCH);
//    QS_FILTER_ON(QS_QEP_UNHANDLED);
//
//    QS_FILTER_ON(DPP::BSP_CALL);

    return true; // return success
}


//............................................................................
void QS::onCleanup(void) {
}

//............................................................................
void QS::onFlush(void) {
    uint16_t b;

    QF_INT_DISABLE();
    while ((b = getByte()) != QS_EOD) { // while not End-Of-Data...
        QF_INT_ENABLE();
        while ((USART2->SR & 0x0080U) == 0U) { // while TXE not empty
        }
        USART2->DR  = (b & 0xFFU);  // put into the DR register
        QF_INT_DISABLE();
    }
    QF_INT_ENABLE();
}
//............................................................................
//! callback function to reset the target (to be implemented in the BSP)
void QS::onReset(void) {
	NVIC_SystemReset();
}
//............................................................................

void QS::onTestLoop() {
    rxPriv_.inTestLoop = true;
    while (rxPriv_.inTestLoop) {

        rxParse();  // parse all the received bytes

        if ((USART2->SR & 0x0080U) != 0) {  // is TXE empty?
            QF_INT_DISABLE();
            uint16_t b = QS::getByte();
            QF_INT_ENABLE();

            if (b != QS_EOD) {  // not End-Of-Data?
                USART2->DR  = (b & 0xFFU);  // put into the DR register
            }
        }
    }

    // set inTestLoop to true in case calls to QS_onTestLoop() nest,
    // which can happen through the calls to QS_TEST_WAIT().
    rxPriv_.inTestLoop = true;
}
#endif // Q_SPY
//--------------------------------------------------------------------------*/

} // namespace QP

