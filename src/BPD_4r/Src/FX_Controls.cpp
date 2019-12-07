#include "main.h"
#include "hal.h"
#include "FX_Message_Receiver.h"
#include "Audio.h"
#include "Potentiometers.h"
#include "FX_Controls.h"
#include "FX_Process.h"
#include "main_cpp.h"

extern Potentiometers			Pots;
Toggle_Switch							Tgl_Switch( _PC14_, _PC15_, false );

typedef	void( *Proc_Ptr )( int );

static void Process( Proc_Ptr proc, int i )
{
	Lock_Message_Process = true;
	proc( i );
	Post_Message_Process();
	Lock_Message_Process = false;
}

void Get_Potentiometer( int i )
{
	if( Pots[ i ].Active )
	{
		     if( i == 0 )	FX->Set_Param_0( Pots[ i ].Get_Value() );
		else if( i == 1 )	FX->Set_Param_1( Pots[ i ].Get_Value() );
		else if( i == 2 )	FX->Set_Param_2( Pots[ i ].Get_Value() );
	}
}

void Change_FX( FX_ID id )
{
	if( FX->Get_FX_ID() != id )
	{
		Release_Controls();
		Select_FX( FX_Params( id, Pots ) );
	}
}

void Get_Toggle_Switch( int )
{
	auto v = Tgl_Switch.Get_Value();

	if( Tgl_Switch.Active )
	{
		if( v == Toggle_Switch::Pin_0 )			Change_FX( FX_ID_Reverse_Delay );
		if( v == Toggle_Switch::Pin_OFF )		Change_FX( FX_ID_Delay );
		if( v == Toggle_Switch::Pin_1 )			Change_FX( FX_ID_Analog_Delay );
	}
}

void Get_Controls()
{
	HAL_Delay( 10 );

	Pots.Update();

	for( auto i( 0 ); i < Pots.Get_Count(); ++i )
		Process( Get_Potentiometer, i );

	static auto	j( 0 );

	if( j == 5 )
	{
		Tgl_Switch.Update();
		Process( Get_Toggle_Switch, 0 );
	}

	j = Circuler<0,5>( ++j );
}

void Hold_Controls()
{
 	for( auto i( 0 ); i < Pots.Get_Count(); ++i )
 		Pots[ i ].Hold();

	Tgl_Switch.Hold();
}

void Release_Controls()
{
 	for( auto i( 0 ); i < Pots.Get_Count(); ++i )
 		Pots[ i ].Release();

	Tgl_Switch.Release();
}
