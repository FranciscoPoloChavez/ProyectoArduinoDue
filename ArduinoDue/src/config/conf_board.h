/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H
#define CONSOLE_UART	UART0
// clock
#define BOARD_FREQ_SLCK_XTAL      (32768U)
#define BOARD_FREQ_SLCK_BYPASS    (32768U)
#define BOARD_FREQ_MAINCK_XTAL    (12000000U)
#define BOARD_FREQ_MAINCK_BYPASS  (12000000U)
#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
#define BOARD_OSC_STARTUP_US      15625

// LED
#define LED    IOPORT_CREATE_PIN(PIOB, 27)

#define LInicio    IOPORT_CREATE_PIN(PIOC, 21)

#define Licrementa    IOPORT_CREATE_PIN(PIOB, 26)
#define Ldecrementa   IOPORT_CREATE_PIN(PIOA, 14)

#define Lderecha    IOPORT_CREATE_PIN(PIOD, 0)
#define LIzquierda   IOPORT_CREATE_PIN(PIOD, 1)
#define Lup    IOPORT_CREATE_PIN(PIOD, 2)
#define Ldown   IOPORT_CREATE_PIN(PIOD, 3)
#define LZinc   IOPORT_CREATE_PIN(PIOD, 6)
#define LZdec   IOPORT_CREATE_PIN(PIOD, 9)

#define LParo    IOPORT_CREATE_PIN(PIOC, 25)

#define LManual    IOPORT_CREATE_PIN(PIOC, 23)

#define LAuto    IOPORT_CREATE_PIN(PIOC, 24)
#define valueaumenta    IOPORT_CREATE_PIN(PIOC, 17)
#define valuedecrementa    IOPORT_CREATE_PIN(PIOC, 18)
#define AUTOPIN    IOPORT_CREATE_PIN(PIOC, 14)
#define MANUALPIN    IOPORT_CREATE_PIN(PIOC, 15)



#endif // CONF_BOARD_H
