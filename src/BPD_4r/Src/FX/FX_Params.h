#ifndef FX_PARAMS_H_
#define FX_PARAMS_H_

#include <stdint.h>
#include <Potentiometers.h>
#include <FX_Interface.h>

struct	FX_Params
{
	uint8_t		Index;
	uint8_t		FID;
	uint16_t	Param_0;
	uint16_t	Param_1;
	uint16_t	Param_2;

	FX_Params():
		Index( 0 ), FID( 0 ),
		Param_0( 0 ), Param_1( 0 ), Param_2( 0 )
	{
	}

	FX_Params( uint8_t fid, const Potentiometers& Pots ):
		Index( 0 ), FID( 0 ),
		Param_0( 0 ), Param_1( 0 ), Param_2( 0 )
	{
		Pots.Update();
		FID 		= fid;
		Param_0 = Pots[ 0 ].Get_Value();
		Param_1 = Pots[ 1 ].Get_Value();
		Param_2 = Pots[ 2 ].Get_Value();
	}

	FX_Params( uint8_t index, FX_Interface* fx ):
		Index( 0 ), FID( 0 ),
		Param_0( 0 ), Param_1( 0 ), Param_2( 0 )
	{
		Index		= index;
		FID			= fx->Get_FX_ID();
		Param_0 = fx->Get_Param_0();
		Param_1 = fx->Get_Param_1();
		Param_2 = fx->Get_Param_2();
	}

	bool Inspect()
	{
		switch( FID )
		{
			case FX_ID_Delay:break;
			case FX_ID_Analog_Delay:break;
			case FX_ID_Reverse_Delay:break;
			case FX_ID_None:break;
			default:	return false;
		}

		if( Param_0 > UINT12_MAX )	return false;
		if( Param_1 > UINT12_MAX )	return false;
		if( Param_2 > UINT12_MAX )	return false;

		return true;
	}
};

#endif
