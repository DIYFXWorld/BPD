#ifndef	FX_Reverse_Delay_h
#define	FX_Reverse_Delay_h

#include <FX_Config.h>
#include <Myutil.h>
#include <Volume.h>
#include <FX_Interface.h>
#include <Sub_Process.h>
#include <Q15T_BQF.h>
#include <Reverse_Delay_Buffer.h>
#include <Mute.h>
#include <FX_Config.h>

constexpr Q15T_BQF_Param FX_Reverse_Delay_LPF_Param = BQF_Builder( _FS_ ).LPF( 10000.f, 0.75f );

struct FX_Reverse_Delay : public FX_Interface
{
	static const int 				FS_RATIO			= 2;
	static const int				BUFFER_LENGTH	= FX_REVERSE_DELAY_BUFFER_LENGTH;

	Volume<Curve_A>					Time_Length;
	Volume<Curve_B>					Feedback;
	Volume<Curve_B>					Mix_Level;

	Reverse_Delay_Buffer		Buffer;
	Type_Mute								Mute;

	Q15T_BQF								LPF_Pre, LPF_Post;

	Sub_Process_2<FX_Reverse_Delay>	Sub_Process;
	int															_input_, _output_, _delay_;	// for sub process

	FX_Reverse_Delay():
		Time_Length( 1 ), Feedback( 0 ), Mix_Level( 0 ),
		Buffer( BUFFER_LENGTH ), Mute( 40 ), Sub_Process( *this )
	{
		LPF_Pre 	= FX_Reverse_Delay_LPF_Param;
		LPF_Post	= FX_Reverse_Delay_LPF_Param;
		Buffer.Memory.Reset();
	}

	void Destroy() { delete this; }

	void Sub_Process_0( int input )
	{
		_input_ = input;

		Buffer.Set_Length( Map( Time_Length.Get_Value(), 0, UINT12_MAX, 100, Buffer.Memory.Length-1 ) );

		if( Buffer.Pointer == Buffer.Length - Mute.Length + 1 )
			if( Buffer.Direction > 0 )
				Mute.Start();

		if( Buffer.Pointer == Mute.Length - 2 )
			if( Buffer.Direction < 0 )
				Mute.Start();
	}

	int Sub_Process_1()
	{
		_delay_ = Buffer.Get_Value();
		_delay_ = Mute.Process( _delay_ );

		_input_	-= Feedback.Per( _delay_ );
		_output_ = Mix_Level.Per( _delay_ );

		_input_  = LIMIT_INT16( _input_ );
		_output_ = LIMIT_INT16( _output_ );

		Buffer.Set_Value( _input_ );

		return _output_;
	}

	int Process( int input )
	{
		return LPF_Post( Sub_Process( LPF_Pre( input ) ) );
	}

	void Set_Param_0( int v )	{ Feedback.Set_Value( v ); }
	int Get_Param_0() const		{ return Feedback.Initial_Value; }

	void Set_Param_1( int v ) { Mix_Level.Set_Value( v ); }
	int Get_Param_1() const		{ return Mix_Level.Initial_Value; }

	void Set_Param_2( int v )	{ Time_Length.Set_Value( v ); }
	int Get_Param_2() const		{ return Time_Length.Initial_Value; }

	void Set_Param_3( int v /*ms*/ )
	{
		int length = _MS_2_LENGTH( v, _FS_/FS_RATIO );
		length = Limit<int>( 1, length, Buffer.Memory.Length-1 );
		Time_Length.Set_Value( Map( length, 1, Buffer.Memory.Length-1, 0, UINT12_MAX ) );
	}

	int Get_Param_3() const
	{
		int	length = Map( Time_Length.Initial_Value, 0, UINT12_MAX, 1, Buffer.Memory.Length-1 );
		return _LENGTH_2_MS( length, _FS_/FS_RATIO );
	}

	FX_ID Get_FX_ID() const	{ return FX_ID_Reverse_Delay; }

	void Reset()
	{
		Buffer.Reset();
		Buffer.Memory.Reset();
		Time_Length.Fast_Forward();
		Feedback.Fast_Forward();
		Mix_Level.Fast_Forward();
	}
};
#endif
