#include "Audio.h"
#include "Potentiometers.h"
#include "FX_Message.h"
#include "FX_Controls.h"
#include "FX_Process.h"
#include "main_cpp.h"

const	int	Max_Bank_Number	= 30;
      int	Bank_Number			= 0;

extern Potentiometers	Pots;

bool Check_Message_ID( const FX_Message& msg )
{
	if( msg.DID == FX_DID_Common )	return true;
	if( msg.DID == FX_DID_BPD )			return true;
	return false;
}

void Hold_Controls();

void Change_Program( const FX_Message& msg )
{
	auto	v = NVM.Read( msg.Param_Byte + ( Bank_Number*10 ) );

	if( ( v.Index != 0xFF ) && v.Inspect() )
	{
		Hold_Controls();
		Select_FX( v );
	}
}

void Store_Program( const FX_Message& msg )
{
	auto	index = msg.Param_Byte + ( Bank_Number*10 );

	NVM.Write( FX_Params( index, FX ) );
}

void Set_Time( const FX_Message& msg )
{
	Pots[ 2 ].Hold();
 	FX->Set_Param_3( msg.Param_Word );
}

void Change_Bank( const FX_Message& msg )
{
	Bank_Number = Limit<int>( 0, msg.Param_Byte, Max_Bank_Number );
	FX_Message	m = msg;
	m.Param_Byte = 0;
	Change_Program( m );
}

void Release_Controls( const FX_Message& )
{
 	Release_Controls();
}
