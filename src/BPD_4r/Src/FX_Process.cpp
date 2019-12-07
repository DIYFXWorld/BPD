#include "hal.h"
#include "Myutil.h"
#include "Audio.h"
#include "FX_Process.h"
#include "FX_Controls.h"
#include "main_cpp.h"

FX_Interface	*FX;
Fade_In				Audio_Fade_In( 400 );	// 10ms

void Audio_Input_Callback( int input )
{
	Audio::Set_Output( FX->Process( Audio_Fade_In.Process( input ) ) );
}

template <typename T>
FX_Interface* Construct( FX_Interface* v )
{
	if( v )	v->Destroy();
	return new T;
}

#include	"FX_Delay.h"
#include	"FX_Analog_Delay.h"
#include	"FX_Reverse_Delay.h"
#include	"FX_None.h"

void Select_FX( const FX_Params& Params )
{
	if( !FX )	FX = new FX_None;

	Audio::Inactive();

	if( Params.FID != FX->Get_FX_ID() )
	{
		if( Params.FID == FX_ID_Delay )					FX = Construct<FX_Delay>( FX );
		if( Params.FID == FX_ID_Analog_Delay )	FX = Construct<FX_Analog_Delay>( FX );
		if( Params.FID == FX_ID_Reverse_Delay )	FX = Construct<FX_Reverse_Delay>( FX );
	}

	FX->Set_Param_0( Params.Param_0 );
	FX->Set_Param_1( Params.Param_1 );
	FX->Set_Param_2( Params.Param_2 );
	FX->Reset();

	Audio_Fade_In.Start();

	Audio::Active();
}
