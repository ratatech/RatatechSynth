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

static unsigned  l_rnd;  // random seed

#ifdef Q_SPY

    QP::QSTimeCtr QS_tickTime_;
    QP::QSTimeCtr QS_tickPeriod_;

    // event-source identifiers used for tracing
    static uint8_t const l_SysTick_Handler    = 0U;
    static uint8_t const l_EXTI0_IRQHandler = 0U;

    enum AppRecords { // application-specific trace records
        BSP_CALL = QP::QS_USER
    };

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

// QF callbacks ==============================================================
void QF::onStartup(void) {
    // set up the SysTick timer to fire at BSP::TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / DPP::BSP::TICKS_PER_SEC);

    // set priorities of ALL ISRs used in the system, see NOTE00
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    // DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    //
    NVIC_SetPriority(SysTick_IRQn, DPP::SYSTICK_PRIO);
    NVIC_SetPriority(EXTI0_IRQn,   DPP::EXTI0_PRIO);
    // ...

    // enable IRQs...
    NVIC_EnableIRQ(EXTI0_IRQn);
}
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

//    // enable peripheral clock for USART2
//    RCC->AHBENR   |=  (1U <<  0);   // Enable GPIOA clock
//    RCC->APB1ENR  |=  (1U << 17);   // Enable USART#2 clock
//
//    // Configure PA3 to USART2_RX, PA2 to USART2_TX
//    GPIOA->AFR[0] &= ~((15U << 4*3) | (15U << 4*2));
//    GPIOA->AFR[0] |=  (( 7U << 4*3) | ( 7U << 4*2));
//    GPIOA->MODER  &= ~(( 3U << 2*3) | ( 3U << 2*2));
//    GPIOA->MODER  |=  (( 2U << 2*3) | ( 2U << 2*2));
//
//    USART2->BRR  = __USART_BRR(SystemCoreClock, 115200U); // baud rate
//    USART2->CR3  = 0x0000U;        // no flow control
//    USART2->CR2  = 0x0000U;        // 1 stop bit
//    USART2->CR1  = ((1U <<  2) |   // enable RX
//                    (1U <<  3) |   // enable TX
//                    (0U << 12) |   // 1 start bit, 8 data bits
//                    (1U << 13));   // enable USART

    DPP::QS_tickPeriod_ = SystemCoreClock / DPP::BSP::TICKS_PER_SEC;
    DPP::QS_tickTime_ = DPP::QS_tickPeriod_; // to start the timestamp at zero

    // setup the QS filters...
    QS_FILTER_ON(QS_QEP_STATE_ENTRY);
    QS_FILTER_ON(QS_QEP_STATE_EXIT);
    QS_FILTER_ON(QS_QEP_STATE_INIT);
    QS_FILTER_ON(QS_QEP_INIT_TRAN);
    QS_FILTER_ON(QS_QEP_INTERN_TRAN);
    QS_FILTER_ON(QS_QEP_TRAN);
    QS_FILTER_ON(QS_QEP_IGNORED);
    QS_FILTER_ON(QS_QEP_DISPATCH);
    QS_FILTER_ON(QS_QEP_UNHANDLED);

    QS_FILTER_ON(DPP::BSP_CALL);

    return true; // return success
}


//............................................................................
void QS::onCleanup(void) {
}
////............................................................................
//QSTimeCtr QS::onGetTime(void) {  // NOTE: invoked with interrupts DISABLED
//    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) { // not set?
//        return DPP::QS_tickTime_ - static_cast<QSTimeCtr>(SysTick->VAL);
//    }
//    else { // the rollover occured, but the SysTick_ISR did not run yet
//        return DPP::QS_tickTime_ + DPP::QS_tickPeriod_
//               - static_cast<QSTimeCtr>(SysTick->VAL);
//    }
//}
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

//        // turn the LED1 on and off (glow)
//        GPIO->P[LED_PORT].DOUT |=  (1U << LED1_PIN);
//        GPIO->P[LED_PORT].DOUT &= ~(1U << LED1_PIN);

        rxParse();  // parse all the received bytes

        if ((USART2->SR & 0x0080U) != 0) {  // is TXE empty?
            QF_INT_DISABLE();
            uint16_t b = QS::getByte();
            QF_INT_ENABLE();

            if (b != QS_EOD) {  // not End-Of-Data?
                USART2->DR  = (b & 0xFFU);  // put into the DR register
            }
        }



//        if ((l_USART0->STATUS & USART_STATUS_TXBL) != 0) { // is TXE empty?
//            uint16_t b = getByte();
//            if (b != QS_EOD) {  // not End-Of-Data?
//                l_USART0->TXDATA = (b & 0xFFU); // put into the DR register
//            }
//        }
    }

    // set inTestLoop to true in case calls to QS_onTestLoop() nest,
    // which can happen through the calls to QS_TEST_WAIT().
    rxPriv_.inTestLoop = true;
}
#endif // Q_SPY
//--------------------------------------------------------------------------*/

} // namespace QP

//****************************************************************************
// NOTE00:
// The QF_AWARE_ISR_CMSIS_PRI constant from the QF port specifies the highest
// ISR priority that is disabled by the QF framework. The value is suitable
// for the NVIC_SetPriority() CMSIS function.
//
// Only ISRs prioritized at or below the QF_AWARE_ISR_CMSIS_PRI level (i.e.,
// with the numerical values of priorities equal or higher than
// QF_AWARE_ISR_CMSIS_PRI) are allowed to call any QF services. These ISRs
// are "QF-aware".
//
// Conversely, any ISRs prioritized above the QF_AWARE_ISR_CMSIS_PRI priority
// level (i.e., with the numerical values of priorities less than
// QF_AWARE_ISR_CMSIS_PRI) are never disabled and are not aware of the kernel.
// Such "QF-unaware" ISRs cannot call any QF services. The only mechanism
// by which a "QF-unaware" ISR can communicate with the QF framework is by
// triggering a "QF-aware" ISR, which can post/publish events.
//
// NOTE01:
// The QV_onIdle() callback is called with interrupts disabled, because the
// determination of the idle condition might change by any interrupt posting
// an event. QV_onIdle() must internally enable interrupts, ideally
// atomically with putting the CPU to the power-saving mode.
//
// NOTE02:
// The User LED is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invcations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//
