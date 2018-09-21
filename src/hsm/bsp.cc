//****************************************************************************
// Product: "Blinky" on EFM32-SLSTK3401A board, cooperative QV kernel
// Last Updated for Version: 5.6.5
// Date of the Last Update:  2016-05-02
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

#include <hsm/bsp.h>
#include "qpcpp.h"
#include "stdio.h"

//#include "em_device.h"  // the device specific header (SiLabs)
//#include "em_cmu.h"     // Clock Management Unit (SiLabs)
//#include "em_gpio.h"    // GPIO (SiLabs)
// add other drivers if necessary...
#include "stm32f10x.h"

using namespace QP;


Q_DEFINE_THIS_FILE

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
    SYSTICK_PRIO = QF_AWARE_ISR_CMSIS_PRI, // see NOTE00
    // ...
    MAX_KERNEL_AWARE_CMSIS_PRI // keep always last
};
// "kernel-aware" interrupts should not overlap the PendSV priority
Q_ASSERT_COMPILE(MAX_KERNEL_AWARE_CMSIS_PRI <= (0xFF >>(8-__NVIC_PRIO_BITS)));

// Local-scope objects -------------------------------------------------------
#define LED0_PIN    4
#define LED0_PORT   4

#define LED1_PIN    5
#define LED1_PORT   5

#define BTN_SW1     (1U << 4)
#define BTN_SW2     (1U << 0)

// ISRs used in this project =================================================
extern "C" {

//............................................................................
void SysTick_Handler(void); // prototype
void SysTick_Handler(void) {
    QF::TICK_X(0U, (void *)0); // process time events for rate 0
}

} // extern "C"

// BSP functions =============================================================
void BSP_init(void) {

	GPIO_InitTypeDef  GPIO_InitStructure;

	/* LED (PA5) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


}
//............................................................................
void BSP_ledOff(void) {
	iprintf("\nBLINKY: LED -----------------------> OFF");

	// Set LED2 on nucleo board ---> OFF
	GPIOA->BRR = GPIO_Pin_5;

	// Set LED/D3 on PCB ---> OFF
	GPIOB->BRR = GPIO_Pin_11;
}
//............................................................................
void BSP_ledOn(void) {
	iprintf("\nBLINKY: LED -----------------------> ON");

	// Set LED2 on nucleo board --->  ON
	GPIOA->BSRR = GPIO_Pin_5;

	// Set LED/D3 on PCB ---> ON
	GPIOB->BSRR = GPIO_Pin_11;
}


// QF callbacks ==============================================================
void QF::onStartup(void) {
    // set up the SysTick timer to fire at BSP_TICKS_PER_SEC rate
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    // assing all priority bits for preemption-prio. and none to sub-prio.
    NVIC_SetPriorityGrouping(0U);

    // set priorities of ALL ISRs used in the system, see NOTE00
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    // DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    //
    NVIC_SetPriority(SysTick_IRQn,   SYSTICK_PRIO);
    // ...

    // enable IRQs...
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
//void QS::onFlush(void) {
//    uint16_t b;

//    QF_INT_DISABLE();
//    while ((b = getByte()) != QS_EOD) { // while not End-Of-Data...
//        QF_INT_ENABLE();
//        // while TXE not empty
//        while ((DPP::l_USART0->STATUS & USART_STATUS_TXBL) == 0U) {
//        }
//        DPP::l_USART0->TXDATA  = (b & 0xFFU); // put into the DR register
//        QF_INT_DISABLE();
//    }
//    QF_INT_ENABLE();
//}
//............................................................................
void QV::onIdle(void) { // CATION: called with interrupts DISABLED, NOTE01
    // toggle LED1 on and then off, see NOTE02
    //GPIO_PinOutSet(LED1_PORT, LED1_PIN);
    //GPIO->P[LED1_PORT].DOUT |= (1U << LED1_PIN);
    //GPIO_PinOutClear(LED1_PORT, LED1_PIN);
    //GPIO->P[LED1_PORT].DOUT &= ~(1U << LED1_PIN);

#ifdef NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M MCU.
    //
    QV_CPU_SLEEP();  // atomically go to sleep and enable interrupts
#else
    QF_INT_ENABLE(); // just enable interrupts
#endif
}

//............................................................................
extern "C" void Q_onAssert(char const *module, int loc) {
    //
    // NOTE: add here your application-specific error handling
    //
    (void)module;
    (void)loc;
    QS_ASSERTION(module, loc, static_cast<uint32_t>(10000U));
    NVIC_SystemReset();
}

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
// The QV::onIdle() callback is called with interrupts disabled, because the
// determination of the idle condition might change by any interrupt posting
// an event. QV::onIdle() must internally enable interrupts, ideally
// atomically with putting the CPU to the power-saving mode.
//
// NOTE02:
// One of the LEDs is used to visualize the idle loop activity. The brightness
// of the LED is proportional to the frequency of invcations of the idle loop.
// Please note that the LED is toggled with interrupts locked, so no interrupt
// execution time contributes to the brightness of the User LED.
//
