#include "main_cpp.h"
#include "FX_Process.h"

void Audio_Input_Callback( int input )
{
	int	a = Pots[ 0 ].Get_Value();
	int	b = Tgl_Switch.Get_Value();

	Audio::Set_Output( input );
}
