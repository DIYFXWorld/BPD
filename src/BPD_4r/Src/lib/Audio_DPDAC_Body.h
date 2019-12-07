#include	"Audio.h"
#include	"hal.h"
#include	"hal_tim.h"
#include	"Myutil.h"

extern TIM_HandleTypeDef	AUDIO_DPDAC_HTIM;

void Audio::Output_Start()
{
//  HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, AUDIO_DPDAC_TIM_CH_HI );
//	HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, AUDIO_DPDAC_TIM_CH_LO );

	if( AUDIO_DPDAC_HTIM.Instance->CCMR1 & ( 0x60 << 0 ) )	HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, TIM_CHANNEL_1 );
	if( AUDIO_DPDAC_HTIM.Instance->CCMR1 & ( 0x60 << 8 ) )	HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, TIM_CHANNEL_2 );
  if( AUDIO_DPDAC_HTIM.Instance->CCMR2 & ( 0x60 << 0 ) )	HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, TIM_CHANNEL_3 );
  if( AUDIO_DPDAC_HTIM.Instance->CCMR2 & ( 0x60 << 8 ) )	HAL_TIM_PWM_Start( &AUDIO_DPDAC_HTIM, TIM_CHANNEL_4 );
}

void Audio::Set_Output( int v )
{
	v = LIMIT_INT16( v );

	v += 32768;

	AUDIO_DPDAC_HTIM.Instance->CCR1 = LO_BYTE( v );
	AUDIO_DPDAC_HTIM.Instance->CCR2 = HI_BYTE( v );
}

void Audio::Set_Output( int L, int R )
{
	L = LIMIT_INT16( L );
	L += 32768;

	R = LIMIT_INT16( R );
	R += 32768;

	AUDIO_DPDAC_HTIM.Instance->CCR1 = LO_BYTE( L );
	AUDIO_DPDAC_HTIM.Instance->CCR2 = HI_BYTE( L );

	AUDIO_DPDAC_HTIM.Instance->CCR3 = LO_BYTE( R );
	AUDIO_DPDAC_HTIM.Instance->CCR4 = HI_BYTE( R );
}
