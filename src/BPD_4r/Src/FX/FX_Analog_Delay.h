#ifndef	FX_Analog_Delay_h
#define	FX_Analog_Delay_h

#include <FX_Config.h>
#include <Myutil.h>
#include <Volume.h>
#include <FX_Interface.h>
#include <Sub_Process.h>
#include <Q15T_BQF.h>
#include <Delay_Buffer.h>

constexpr BQF_Param FX_Analog_Delay_LPF_Param 	= BQF_Builder( _FS_ ).LPF( 3000.f, 0.75f );
constexpr BQF_Param FX_Analog_Delay_LPF_1_Param = BQF_Builder( 10000 ).LPF( 1500.f, 1.f );

struct FX_Analog_Delay : public FX_Interface
{
	static const int			FS_RATIO 			= 4;
	static const int			BUFFER_LENGTH	= FX_ANALOG_DELAY_BUFFER_LENGTH;

	Volume_x<Curve_D>			Time_Length;	// 0...4095
	Volume<Curve_B>				Feedback;			// 0...4095
	Volume<Curve_B>				Mix_Level;		// 0...4095

	Delay_Buffer					Buffer;

	Q15T_BQF							LPF_Pre, LPF_Post, LPF;

	Sub_Process_4<FX_Analog_Delay>	Sub_Process;
	int															_input_, _output_, _delay_; // for sub process

	FX_Analog_Delay():
		Time_Length( 0 ), Feedback( 0 ), Mix_Level( 0 ),
		Buffer( BUFFER_LENGTH ), Sub_Process( *this )
	{
		LPF_Pre 	= FX_Analog_Delay_LPF_Param;
		LPF_Post	= FX_Analog_Delay_LPF_Param;
		LPF 			= FX_Analog_Delay_LPF_1_Param;
	}

	void Destroy() { delete this; }

	void Sub_Process_0( int v )
	{
		_input_ = v;
		Buffer.Set_Length( Map( Time_Length.Get_Value(), 0, UINT12_MAX, 1, Buffer.Memory.Length-1 ) );
	}

	void Sub_Process_1()
	{
		_delay_ = Buffer.Get_Value();
		_input_	-= Feedback.Per( _delay_ );
		_output_ = Mix_Level.Per( _delay_ );
	}

	void Sub_Process_2()
	{
		_input_ = LPF.Process( _input_ );
		_input_  = LIMIT_INT16( _input_ );
		Buffer.Set_Value( _input_ );
	}

	int Sub_Process_3()
	{
		_output_ = LIMIT_INT16( _output_ );
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

	void Set_Param_2( int v )	{ Time_Length.Set_Value( v );	}
	int Get_Param_2() const		{ return Time_Length.Initial_Value; }

	void Set_Param_3( int ms )
	{
		int	length = _MS_2_LENGTH( ms, _FS_/FS_RATIO );
		length = Limit<int>( 1, length, Buffer.Memory.Length-1 );
		Time_Length.Set_Value( Map( length, 1, Buffer.Memory.Length-1, 0, UINT12_MAX ) );
	}

	int Get_Param_3() const
	{
		int length = Map( Time_Length.Initial_Value, 0, UINT12_MAX, 1, Buffer.Memory.Length-1 );
		return _LENGTH_2_MS( length, _FS_/FS_RATIO );
	}

	FX_ID Get_FX_ID() const	{ return FX_ID_Analog_Delay; }

	void Reset()
	{
		Buffer.Memory.Reset();
		Buffer.Set_Length( Map( Time_Length.Get_Value(), 0, UINT12_MAX, 1, Buffer.Memory.Length-1 ) );
		Buffer.Fast_Forward();
		Feedback.Fast_Forward();
		Mix_Level.Fast_Forward();
	}
};

#endif
