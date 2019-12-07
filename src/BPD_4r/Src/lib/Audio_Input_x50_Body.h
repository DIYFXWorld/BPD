#include "Audio.h"
#include "hal.h"
#include "hal_adc.h"

int8_t	Audio::Lock_Counter	= 1;

extern "C" void Error_Handler();

extern ADC_HandleTypeDef AUDIO_INPUT_HADC;
extern TIM_HandleTypeDef AUDIO_INPUT_HTIM;

#define	DMA_Buffer_Length		(50*2)
static uint16_t	DMA_Buffer[ DMA_Buffer_Length ];

static	uint32_t Value;

#define	SUM_BUFFER_FIRST_HALF(x)	(uint32_t)\
	x[ 0]+x[ 1]+x[ 2]+x[ 3]+x[ 4]+x[ 5]+x[ 6]+x[ 7]+x[ 8]+x[ 9]+\
	x[10]+x[11]+x[12]+x[13]+x[14]+x[15]+x[16]+x[17]+x[18]+x[19]+\
	x[20]+x[21]+x[22]+x[23]+x[24]+x[25]+x[26]+x[27]+x[28]+x[29]+\
	x[30]+x[31]+x[32]+x[33]+x[34]+x[35]+x[36]+x[37]+x[38]+x[39]+\
	x[40]+x[41]+x[42]+x[43]+x[44]+x[45]+x[46]+x[47]+x[48]+x[49]

#define	SUM_BUFFER_SECOND_HALF(x)	(uint32_t)\
	x[50]+x[51]+x[52]+x[53]+x[54]+x[55]+x[56]+x[57]+x[58]+x[59]+\
	x[60]+x[61]+x[62]+x[63]+x[64]+x[65]+x[66]+x[67]+x[68]+x[69]+\
	x[70]+x[71]+x[72]+x[73]+x[74]+x[75]+x[76]+x[77]+x[78]+x[79]+\
	x[80]+x[81]+x[82]+x[83]+x[84]+x[85]+x[86]+x[87]+x[88]+x[89]+\
	x[90]+x[91]+x[92]+x[93]+x[94]+x[95]+x[96]+x[97]+x[98]+x[99]

static const	int	_c_ = 4095*50;
static const	int	_a_ = 65535/15;
static const	int	_b_ = _c_/15;

extern "C" void HAL_ADC_ConvHalfCpltCallback( ADC_HandleTypeDef* hadc )
{
	USER_LED_OFF();		// negative logic

	Value = SUM_BUFFER_FIRST_HALF( DMA_Buffer );
	Value = Value * _a_ / _b_;

	int	v = ( Value & 0xFFFF ) - 32768;

	if( Audio::Lock_Counter )	Audio_Invalid_Callback( v );
	else											Audio_Input_Callback( v );

	USER_LED_ON();		// negative logic
}

extern "C" void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
	USER_LED_OFF();		// negative logic

	Value = SUM_BUFFER_SECOND_HALF( DMA_Buffer );
	Value = Value * _a_ / _b_;

	int	v = ( Value & 0xFFFF ) - 32768;

	if( Audio::Lock_Counter )	Audio_Invalid_Callback( v );
	else											Audio_Input_Callback( v );

	USER_LED_ON();		// negative logic
}

void Audio::Input_Start()
{
#ifndef	STM32F411xE
#ifndef	STM32F401xC
	if( HAL_ADCEx_Calibration_Start( &AUDIO_INPUT_HADC ) != HAL_OK )
    Error_Handler();
#endif
#endif

  if( HAL_ADC_Start_DMA( &AUDIO_INPUT_HADC, ( uint32_t* )DMA_Buffer, DMA_Buffer_Length ) != HAL_OK )
    Error_Handler();

  if( HAL_TIM_OC_Start( &AUDIO_INPUT_HTIM, AUDIO_INPUT_TIM_CH ) != HAL_OK )
    Error_Handler();
}

__weak void Audio_Invalid_Callback( int )
{
  Audio::Set_Output( 0 );
}
