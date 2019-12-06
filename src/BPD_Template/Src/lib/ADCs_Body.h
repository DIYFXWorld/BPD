int16_t* 	ADCs::Elements = 0;

extern "C" void Error_Handler();

void ADCs::Start()
{
	if( !Elements )
	{
		Elements = new int16_t[ HADC.Init.NbrOfConversion ];

#if	defined( STM32F103xB ) || defined( STM32F103xE )
		if( HAL_ADCEx_Calibration_Start( &HADC ) != HAL_OK )
  	{
  		Error_Handler();
	  }
#endif

  	while( HAL_ADC_GetState( &HADC ) != HAL_ADC_STATE_READY ){}
	}
}

void ADCs::Update()
{
	if( Elements )
	{
		for( auto i( 0 ); i < ( int )HADC.Init.NbrOfConversion; ++i )
		{
			if( HAL_ADC_Start( &HADC ) == HAL_OK )
			{
				if( HAL_ADC_PollForConversion( &HADC, 10 ) != HAL_OK )
				{
					Error_Handler();
				}

				Elements[ i ] = HAL_ADC_GetValue( &HADC );
			}
		}
	}
}

int16_t ADCs::Get_Value( int i )
{
	return Elements[ i ];
}

int ADCs::Get_Count()
{
	return ( int )HADC.Init.NbrOfConversion;
}

