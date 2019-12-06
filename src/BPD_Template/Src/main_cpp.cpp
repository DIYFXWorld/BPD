#include "main_cpp.h"
#include "FX_Process.h"

Potentiometers	Pots;
Toggle_Switch		Tgl_Switch( _PC14_, _PC15_, false );

extern "C" void main_cpp()
{
	Pots.Start();

	Audio::Start();

	Audio::Active();

	while( 1 )
	{
		HAL_Delay( 10 );

		Pots.Update();

		Tgl_Switch.Update();
	}
}
