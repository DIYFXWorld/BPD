#ifndef	Q15T_BQF_h
#define	Q15T_BQF_h

#include	"Q15T.h"
#include	"BQF.h"

struct Q15T_BQF_Param
{
	Q15T		b0_a0, b1_a0, b2_a0;
	Q15T		a1_a0, a2_a0;

	constexpr Q15T_BQF_Param():
		b0_a0(0), b1_a0(0), b2_a0(0),
		a1_a0(0), a2_a0(0)
	{
	}

	constexpr Q15T_BQF_Param( const BQF_Param& v )
	{
		b0_a0 = Q15T( v.b0 / v.a0 );
		b1_a0 = Q15T( v.b1 / v.a0 );
		b2_a0 = Q15T( v.b2 / v.a0 );
		a1_a0 = Q15T( v.a1 / v.a0 );
		a2_a0 = Q15T( v.a2 / v.a0 );
	}
};

struct Q15T_BQF
{
	Q15T		b0_a0, b1_a0, b2_a0;
	Q15T		a1_a0, a2_a0;

	Q15T		in1, in2, out1, out2;
	Q15T		output;

public:

	constexpr Q15T_BQF():
		in1( 0 ), in2( 0 ), out1( 0 ), out2( 0 )
	{
	}

	Q15T_BQF( const BQF_Param& v ):
		in1( 0 ), in2( 0 ), out1( 0 ), out2( 0 )
	{
		*this = v;
	}

	Q15T_BQF( const Q15T_BQF_Param& v ):
		in1( 0 ), in2( 0 ), out1( 0 ), out2( 0 )
	{
		b0_a0 = v.b0_a0;
		b1_a0	= v.b1_a0;
		b2_a0 = v.b2_a0;
		a1_a0	= v.a1_a0;
		a2_a0 = v.a2_a0;
	}

	int Process( int input );

	int operator()( int input );

	Q15T_BQF& operator = ( const BQF_Param& v );

	void Reset();
};

#endif
