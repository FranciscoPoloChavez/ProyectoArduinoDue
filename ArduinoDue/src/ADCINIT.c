//#include <asf.h>

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
		i=0;

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
		adc_enable_channel(ADC, (enum adc_channel_num_t)3);
				i=0;

		adc_start(ADC);
		break;
		
	}
	

}




