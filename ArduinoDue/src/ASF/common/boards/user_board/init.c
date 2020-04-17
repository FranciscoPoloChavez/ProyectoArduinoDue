/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	WDT->WDT_MR = WDT_MR_WDDIS;

	ioport_init();

	ioport_set_port_mode(IOPORT_PIOA, PIO_PA8A_URXD | PIO_PA9A_UTXD,IOPORT_MODE_MUX_A);
	ioport_disable_port(IOPORT_PIOA, PIO_PA8A_URXD | PIO_PA9A_UTXD);

	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
}
