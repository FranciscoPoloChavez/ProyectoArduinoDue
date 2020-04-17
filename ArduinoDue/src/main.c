/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
//#include <avr.io>
#include <asf.h>

#include <conf_board.h>

#include <string.h>

void adc_setup (void);





#define VOLT_REF 3300 //mV

#define MAX_DIGITAL 4095

volatile uint32_t ADC_result[2];

enum adc_channel_num_t ch_list[4] = { ADC_CHANNEL_7,ADC_CHANNEL_6,ADC_CHANNEL_5,ADC_CHANNEL_4};


uint8_t aut=0;
uint8_t man=0;
uint8_t on_off=0;

uint8_t i=0;
uint8_t X_AxisREF=0;
uint8_t Y_AxisREF=0;
uint8_t Z_AxisREF=0;

uint8_t X_Axis=0;
uint8_t Y_Axis=0;
uint8_t Z_Axis=0;
uint8_t temx_Axis=0;
uint8_t temy_Axis=0;
static volatile Bool pin_val;
static volatile Bool pin_val2;
int	estado=2;
int	jogger=0;
uint32_t current_data;

uint32_t current_channel;

uint32_t current_value;
void adc_setup (void)
{
	sysclk_enable_peripheral_clock(ID_ADC);
	adc_init (ADC, sysclk_get_cpu_hz(), 3200000, ADC_STARTUP_TIME_4);
	//adc_init (ADC, sysclk_get_cpu_hz(), 3200000, ADC_STARTUP_TIME_15);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); // Set timings - standard values
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_tag(ADC);
	adc_configure_sequence(ADC, ch_list, 4);
	adc_start_sequencer(ADC);
	//adc_enable_channel(ADC, ADC_CHANNEL_0);
	//adc_enable_channel(ADC, ADC_CHANNEL_0);
	adc_enable_channel(ADC, (enum adc_channel_num_t)0);
	adc_set_bias_current(ADC, 1);
	adc_disable_ts(ADC); // disable temperature sensor
	adc_enable_interrupt(ADC, ADC_IER_DRDY);
	NVIC_EnableIRQ(ADC_IRQn);
}
void statusjoystick()
{	
	if (X_Axis<(X_AxisREF-10))
	{
		ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_HIGH);
		ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
	}
	else{
		if (X_Axis>X_AxisREF+10)
		{
		
		ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_HIGH);
		}
		else
		{
		
		ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);

		}
	}
	
	if (Y_Axis<(Y_AxisREF-10))
	{
		
		ioport_set_pin_level(Ldown, IOPORT_PIN_LEVEL_HIGH);
		ioport_set_pin_level(Lup, IOPORT_PIN_LEVEL_LOW);
	}
	else{
		if (Y_Axis>Y_AxisREF+10)
		{
		
		ioport_set_pin_level(Lup, IOPORT_PIN_LEVEL_HIGH);
		ioport_set_pin_level(Ldown, IOPORT_PIN_LEVEL_LOW);
		}
		else
		{
		ioport_set_pin_level(Lup, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(Ldown, IOPORT_PIN_LEVEL_LOW);
		}
	}
	if (Z_Axis<(Z_AxisREF-10))
	{
		ioport_set_pin_level(LZinc, IOPORT_PIN_LEVEL_HIGH);
		ioport_set_pin_level(LZdec, IOPORT_PIN_LEVEL_LOW);
		
	}
	else{
		if (Z_Axis>Z_AxisREF+10)
		{
			ioport_set_pin_level(LZdec, IOPORT_PIN_LEVEL_HIGH);
			ioport_set_pin_level(LZinc, IOPORT_PIN_LEVEL_LOW);
		
		}
		else
		{
			ioport_set_pin_level(LZinc, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(LZdec, IOPORT_PIN_LEVEL_LOW);
		

		}
	}

}


void ADC_Handler(void)
{
	// Check the ADC conversion status
	//      if ((adc_get_status(ADC) & ADC_ISR_DRDY)==ADC_ISR_DRDY) {
	//             // Get latest value from ADC, this clears the interrupt
	//             currentAdc = adc_get_latest_value(ADC);
	//
	//      }
	i=i+1;
	switch (i)
	{
		case 1:
		
		if ((adc_get_status(ADC) & ADC_ISR_DRDY) ==		ADC_ISR_DRDY)
		{
			X_Axis = adc_get_latest_value(ADC);
			current_channel = (current_data & ADC_LCDR_CHNB_Msk) >> ADC_LCDR_CHNB_Pos;
			current_value = (current_data & ADC_LCDR_LDATA_Msk);
			//ADC_result[current_channel] = current_value;
		}
		X_Axis;
		adc_disable_channel(ADC, (enum adc_channel_num_t)0);
		adc_enable_channel(ADC, (enum adc_channel_num_t)1);
		temx_Axis=X_Axis;
		adc_start(ADC);
		break;
		
		case 2:
		
		if ((adc_get_status(ADC) & ADC_ISR_DRDY) ==		ADC_ISR_DRDY)
		{
			Y_Axis = adc_get_latest_value(ADC);
			//current_channel = (current_data & ADC_LCDR_CHNB_Msk) >> ADC_LCDR_CHNB_Pos;
			//current_value = (current_data & ADC_LCDR_LDATA_Msk);
			//ADC_result[current_channel] = current_value;
		}
		Y_Axis;
		adc_disable_channel(ADC, (enum adc_channel_num_t)1);
		adc_enable_channel(ADC, (enum adc_channel_num_t)2);
		temy_Axis=Y_Axis;
		adc_start(ADC);
		break;
		
		case 3:

		if ((adc_get_status(ADC) & ADC_ISR_DRDY) ==		ADC_ISR_DRDY)
		{
			Z_Axis = adc_get_latest_value(ADC);
			//current_channel = (current_data & ADC_LCDR_CHNB_Msk) >> ADC_LCDR_CHNB_Pos;
			//current_value = (current_data & ADC_LCDR_LDATA_Msk);
			//ADC_result[current_channel] = current_value;
		}
		Z_Axis;
		adc_disable_channel(ADC, (enum adc_channel_num_t)2);
		adc_enable_channel(ADC, (enum adc_channel_num_t)0);
		adc_start(ADC);
		i=0;
	
	statusjoystick();
	
		break;
		
		
	}
	
}
void adccali()
{

	X_AxisREF=X_Axis;
	Y_AxisREF=Y_Axis;
	Z_AxisREF=Z_Axis;
}


void JoystickButton()
{
		//Since the interrupt could be any pin on PORTC we need to
		//  check if PC12 is the one triggering the interrupt.
			ioport_toggle_pin_level(LED);
			delay_ms(1000);
}
void Manual()
{	
		delay_ms(50);
		pin_val=ioport_get_pin_level(MANUALPIN);

	if (pin_val==true)
	{
		ioport_set_pin_level(LManual, IOPORT_PIN_LEVEL_HIGH);
		
		pio_handler_set(PIOC,ID_PIOC,PIO_PC15,PIO_IT_FALL_EDGE,Manual);
	}
	else
	{
		ioport_set_pin_level(LManual, IOPORT_PIN_LEVEL_LOW);
		pio_handler_set(PIOC,ID_PIOC,PIO_PC15,PIO_IT_EDGE,Manual);
	}
	
}
void Automatic()
{
	delay_ms(50);
	pin_val=ioport_get_pin_level(AUTOPIN);
	if (pin_val==true)
	{
		ioport_set_pin_level(LAuto, IOPORT_PIN_LEVEL_HIGH);
		pio_handler_set(PIOC,ID_PIOC,PIO_PC14,PIO_IT_EDGE,Automatic);
	}
	else
	{
		ioport_set_pin_level(LAuto, IOPORT_PIN_LEVEL_LOW);
		
		pio_handler_set(PIOC,ID_PIOC,PIO_PC14,PIO_IT_FALL_EDGE,Automatic);
	}
	
}
void Start_Button()
{	
		ioport_set_pin_level(LInicio, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(LParo, IOPORT_PIN_LEVEL_HIGH);
		adccali();
		
}
void Stop_Button()
{
			ioport_set_pin_level(LParo, IOPORT_PIN_LEVEL_LOW);
			ioport_set_pin_level(LInicio, IOPORT_PIN_LEVEL_HIGH);
			
}

/*void PIOC_Handler ()
{
	if ((PIOC->PIO_ISR & PIO_PC12)== PIO_PC12)
	{
		Stop_Button();
	}

}*/

void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOC) && (index == PIO_PC16)){
		if (pio_get(PIOC, PIO_TYPE_PIO_INPUT, PIO_PC16))
		Automatic();
		else
		Manual();
	}
}
void Encouderau ()
{	
	if (ioport_get_pin_level(valuedecrementa)==true)
	{
		jogger=jogger-1;
		ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
		ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_HIGH);
			
	}
	else
	{
		ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_LOW);
	/*while(1)
	{
		if (ioport_get_pin_level(valuedecrementa)==true)
		{
			break;
		}

	}
	*/
	jogger=jogger+1;
	}
/*	while (1)
	{
		delay_ms(100);
		pin_val=ioport_get_pin_level(valuedecrementa);
		if (pin_val==false)
		{
			break;
		}
	}
	*/

/*	estado=estado+1;
	if (estado!=5)
	{
	estado=0;
		pio_handler_set(PIOC, ID_PIOC, PIO_PC17, PIO_IT_EDGE, Encouderau);
	pin_val=ioport_get_pin_level(valuees2);
	if (pin_val==true)
	{
			ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_HIGH);
			ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_LOW);
			jogger=jogger+1;	
			
	}
	else
	{
				ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_HIGH);
				jogger=jogger-1;
		
	}
	}*/
		//estado=0;
		/*pio_handler_set(PIOC, ID_PIOC, PIO_PC17, PIO_IT_EDGE, Encouderau);
		pin_val=ioport_get_pin_level(valuees2);
		if (pin_val==true)
		{
			ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_HIGH);
			ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_LOW);
			jogger=jogger+1;
			
		}

		else
		{
			ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
			ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_HIGH);
			jogger=jogger-1;
			
		}
	}*/
	
	/*
	pio_disable_interrupt(PIOC, PIO_PC18);
	estado=estado+1;
//	delay_ms(20);
	
	pin_val=ioport_get_pin_level(valuees);
	while(1)
	{
	pin_val=ioport_get_pin_level(valuees);
	if (pin_val==false)
	{
	break;
	}
	}
	
	pin_val2;
	pin_val;
//	if (estado==3)
	//{
	//estado=0;
			ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_HIGH);
			ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_LOW);
			jogger=jogger+1;
	
	delay_s(1);	
	pio_enable_interrupt(PIOC, PIO_PC18);
	
	*/
	pio_enable_interrupt(PIOC, PIO_PC18);
	
}
void Encouderdec ()
	{
	pio_disable_interrupt(PIOC, PIO_PC17);
	
	jogger=jogger-1;
	ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_HIGH);
/*	while(1)
	{
		if (ioport_get_pin_level(valueaumenta)==false)
		{
			break;
		}

	}
	while (1)
	{
		pin_val2=ioport_get_pin_level(valueaumenta);

		if (pin_val2==true)
		{
			break;
		}
	}*/
	/*
		pio_disable_interrupt(PIOC, PIO_PC17);
	while(1)
	{
		pin_val=ioport_get_pin_level(valuees2);
		if (pin_val==false)
		{
			break;
		}
	}	
			ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
			ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_HIGH);
			jogger=jogger-1;
			delay_s(1);		
		pio_enable_interrupt(PIOC, PIO_PC17);
		

	//}

	switch (estado)
	{
		case 1:
			if (pin_val==true)
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_HIGH);
				jogger=jogger-1;
				estado=4;
			}
			else
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
				jogger=jogger+1;
				estado=2;
			}
			break;
		case 2:
			if (pin_val==true)
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
				jogger=jogger+1;
				estado=3;
			}
			else
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_HIGH);
				jogger=jogger-1;
				estado=1;
			}
			break;
			case 3:
			
			if (pin_val==true)
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
				jogger=jogger+1;
				estado=4;
			}
			else
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_HIGH);
				jogger=jogger-1;
				estado=2;
			}
			break;
			case 4:
			
			if (pin_val==true)
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_HIGH);
				jogger=jogger-1;
				estado=3;
			}
			else
			{
				ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_HIGH);
				ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
				jogger=jogger+1;
				estado=1;
			}
			break;
		}

jogger;
*/
pio_enable_interrupt(PIOC, PIO_PC17);

}


void avr_example()
{
	pmc_enable_periph_clk(ID_PIOC);
	pio_set_output(PIOC, LAuto, LOW, DISABLE, ENABLE);
	pio_set_output(PIOC, LManual, LOW, DISABLE, ENABLE);
	pio_set_output(PIOC, LParo, LOW, DISABLE, ENABLE);
	pio_set_output(PIOC, LInicio, LOW, DISABLE, ENABLE);
	pio_set_output(PIOC, Ldecrementa, LOW, DISABLE, ENABLE);
	pio_set_output(PIOC, Licrementa, LOW, DISABLE, ENABLE);
	pio_set_input(PIOC,PIO_PC13,PIO_PULLUP);
	pio_set_input(PIOC,PIO_PC12,PIO_PULLUP);
	pio_set_input(PIOC,PIO_PC14,PIO_PULLUP);
	pio_set_input(PIOC,PIO_PC15,PIO_PULLUP);
	pio_set_input(PIOC, PIO_PC16, PIO_PULLUP);
	pio_set_input(PIOC, PIO_PC17, PIO_PULLUP);
	pio_set_input(PIOC, PIO_PC18, PIO_PULLUP);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC12, PIO_IT_EDGE, JoystickButton);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC13, PIO_IT_EDGE, Start_Button);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC14, PIO_IT_EDGE, Automatic);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC15, PIO_IT_EDGE, Manual);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC16, PIO_IT_EDGE, Stop_Button);
	pio_handler_set(PIOC, ID_PIOC, PIO_PC17, PIO_IT_RISE_EDGE, Encouderau);
	//pio_handler_set(PIOC, ID_PIOC, PIO_PC18, PIO_IT_FALL_EDGE, Encouderdec);
	
	pio_enable_interrupt(PIOC, PIO_PC12);
	pio_enable_interrupt(PIOC, PIO_PC13);
	pio_enable_interrupt(PIOC, PIO_PC14);
	pio_enable_interrupt(PIOC, PIO_PC15);
	pio_enable_interrupt(PIOC, PIO_PC16);
	pio_enable_interrupt(PIOC, PIO_PC17);
	//pio_enable_interrupt(PIOC, PIO_PC18);
	NVIC_EnableIRQ(PIOC_IRQn);

}
void port_init()
{
	ioport_set_pin_dir(LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LInicio, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LParo, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LManual, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LAuto, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Licrementa, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Ldecrementa, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LIzquierda, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Lderecha, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Lup, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(Ldown, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LZinc, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LZdec, IOPORT_DIR_OUTPUT);

	ioport_set_pin_level(LInicio, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_level(LParo, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(LManual, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_level(LAuto, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_level(Licrementa, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(LIzquierda, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(Lderecha, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(Lup, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(Ldown, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(LZdec, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(LZinc, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_level(Ldecrementa, IOPORT_PIN_LEVEL_LOW);


}
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();

	
WDT->WDT_MR = WDT_MR_WDDIS;
//ioport_init();
avr_example();
port_init();
adc_setup();
NVIC_EnableIRQ(ADC_IRQn);

//printf("ADC ready.\r");

adc_start(ADC);

//InitPIO();
//otherPio();

pin_val=ioport_get_pin_level(valueaumenta);
pin_val2=ioport_get_pin_level(valuedecrementa);
/*if (pin_val==true)
{
	if (pin_val2==true)
	{
		estado=3;
	}
	else
	{
		estado=4;
	}
}
else
{
	if (pin_val2==true)
	{
		estado=2;
	}
	else
	{
		estado=1;
	}

}*/
jogger=0;
estado=2;
ioport_set_pin_level(LED, IOPORT_PIN_LEVEL_HIGH);

while (1){
			//ioport_toggle_pin_level(LAuto);
			//ioport_toggle_pin_level(LInicio);
			//ioport_toggle_pin_level(LParo);
			//ioport_toggle_pin_level(LManual);
			
			jogger;
			ioport_toggle_pin_level(LED);

					delay_ms(1000);

		}	/* Insert application code here, after the board has been initialized. */
}

