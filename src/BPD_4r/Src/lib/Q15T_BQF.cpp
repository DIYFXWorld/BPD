#include	"Q15T_BQF.h"

Q15T_BQF& Q15T_BQF::operator = ( const BQF_Param& v )
{
	b0_a0 = Q15T( v.b0 / v.a0 );
	b1_a0 = Q15T( v.b1 / v.a0 );
	b2_a0 = Q15T( v.b2 / v.a0 );
	a1_a0 = Q15T( v.a1 / v.a0 );
	a2_a0 = Q15T( v.a2 / v.a0 );

	return *this;
}

int Q15T_BQF::Process( int input )
{
	output	=       ( b0_a0 * input )
					+ Mul_64( b1_a0, in1    )
					+ Mul_64( b2_a0, in2    )
					+ Mul_64( a1_a0, out1   )
					+ Mul_64( a2_a0, out2   );

	in2  = in1;
	in1  = Q15T( input );

	out2 = out1;
	out1 = output * -1;

	return output.to_round_int();
}

int Q15T_BQF::operator()( int input )
{
	output	=       ( b0_a0 * input )
					+ Mul_64( b1_a0, in1    )
					+ Mul_64( b2_a0, in2    )
					+ Mul_64( a1_a0, out1   )
					+ Mul_64( a2_a0, out2   );

	in2  = in1;
	in1  = Q15T( input );

	out2 = out1;
	out1 = output * -1;

	return output.to_round_int();
}

void Q15T_BQF::Reset()
{
	in1.Value = 0;
	in2.Value	= 0;
	out1.Value = 0;
	out2.Value = 0;
}
