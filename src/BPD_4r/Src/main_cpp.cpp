#include "Audio.h"
#include "Potentiometers.h"
#include "FX_Message_Receiver.h"
#include "Board.h"
#include "vcp.h"
#include "FX_Process.h"
#include "main_cpp.h"
#include "FX_Controls.h"
#include "FX_Params.h"

volatile const char* const Signature = { "Blue Pill STM32 FX Projects - Delay" };

uint8_t						UID	= 0xFF;
FMEM<FX_Params>		NVM;
Port							UART_SW( _PA8_ );
Potentiometers		Pots;

extern "C" void main_cpp()
{
	UID = Get_UID();

	Pots.Start();

	Select_FX( FX_Params( FX_ID_Delay, Pots ) );

	Audio::Start();

	HAL_Delay( 1000 );

	UART_SW.ON();
	Start_Receiving_Message();

	Audio::Active();

	while( 1 )
	{
		Get_Controls();

#pragma GCC diagnostic ignored "-Wunused-variable"
	volatile const auto	a = Signature[ 0 ];
#pragma GCC diagnostic warning "-Wunused-variable"
	}
}
