#ifndef BQF_H_
#define BQF_H_

#include	<math.h>

struct BQF_Param
{
	float	a0, a1, a2;
	float	b0, b1, b2;

	constexpr BQF_Param():
		a0(0.f), a1(0.f), a2(0.f), b0(0.f), b1(0.f), b2(0.f)
	{
	}

	constexpr BQF_Param( float A0, float A1, float A2, float B0, float B1, float B2 ):
		a0(A0), a1(A1), a2(A2), b0(B0), b1(B1), b2(B2)
	{
	}
};

struct BQF_Param_B
{
	float		b0_a0, b1_a0, b2_a0;
	float		a1_a0, a2_a0;

	constexpr BQF_Param_B():
		b0_a0(0.f), b1_a0(0.f), b2_a0(0.f),
		a1_a0(0.f), a2_a0(0.f)
	{
	}

	constexpr BQF_Param_B( const BQF_Param& v ):
		b0_a0(v.b0/v.a0),
		b1_a0(v.b1/v.a0),
		b2_a0(v.b2/v.a0),
		a1_a0(v.a1/v.a0),
		a2_a0(v.a2/v.a0)
	{
	}
};

struct BQF
{
	float		b0_a0, b1_a0, b2_a0;
	float		a1_a0, a2_a0;

	float		in1, in2, out1, out2;
	float		output;

public:

	constexpr BQF():
		b0_a0(0.f), b1_a0(0.f), b2_a0(0.f),
		a1_a0(0.f), a2_a0(0.f),
		in1(0.f), in2(0.f), out1(0.f), out2(0.f), output(0.f)
	{
	}

	constexpr BQF( const BQF_Param& v ):
		b0_a0(0.f), b1_a0(0.f), b2_a0(0.f),
		a1_a0(0.f), a2_a0(0.f),
		in1(0.f), in2(0.f), out1(0.f), out2(0.f), output(0.f)
	{
		*this = v;
	}

	constexpr BQF( const BQF_Param_B& v ):
		b0_a0(0.f), b1_a0(0.f), b2_a0(0.f),
		a1_a0(0.f), a2_a0(0.f),
		in1(0.f), in2(0.f), out1(0.f), out2(0.f), output(0.f)
	{
		*this = v;
	}

	float Process( float input )
	{
		output	=	b0_a0 * input
						+ b1_a0 * in1
						+ b2_a0 * in2
						- a1_a0 * out1
						- a2_a0 * out2;

		in2  = in1;
		in1  = input;

		out2 = out1;
		out1 = output;

		return output;
	}

	BQF& operator = ( const BQF_Param& v )
	{
		*this = BQF_Param_B( v );
		return *this;
	};

	BQF& operator = ( const BQF_Param_B& v )
	{
		b0_a0 = v.b0_a0;
		b1_a0	= v.b1_a0;
		b2_a0 = v.b2_a0;
		a1_a0	= v.a1_a0;
		a2_a0 = v.a2_a0;
		return *this;
	};

	void Clear()	{ in1 = in2 = out1 = out2 = output = 0.f; }
};

struct BQF_Builder
{
	const int	samplerate;

	constexpr BQF_Builder( int fs = 40000 ) : samplerate( fs ){}

	inline constexpr BQF_Param LPF( float Frequency, float Q ) const;
	inline constexpr BQF_Param HPF( float Frequency, float Q ) const;
	inline constexpr BQF_Param BPF( float Frequency, float Band_Width ) const;
	inline constexpr BQF_Param NTC( float Frequency, float Band_Width ) const;
	inline constexpr BQF_Param LSF( float Frequency, float Q, float Gain ) const;
	inline constexpr BQF_Param HSF( float Frequency, float Q, float Gain ) const;
	inline constexpr BQF_Param PK ( float Frequency, float Band_Width, float Gain ) const;
	inline constexpr BQF_Param APF( float Frequency, float Q ) const;
};

constexpr BQF_Param BQF_Builder::LPF( float freq, float q ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	return BQF_Param
	(
		 1.0f + alpha,
		-2.0f * cos(omega),
		 1.0f - alpha,
		(1.0f - cos(omega)) / 2.0f,
		 1.0f - cos(omega),
		(1.0f - cos(omega)) / 2.0f
	);
}

constexpr BQF_Param BQF_Builder::HPF( float freq, float q ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	return BQF_Param
	(
		  1.0f + alpha,
		 -2.0f * cos(omega),
		  1.0f - alpha,
		 (1.0f + cos(omega)) / 2.0f,
		-(1.0f + cos(omega)),
		 (1.0f + cos(omega)) / 2.0f
	);
}

constexpr BQF_Param BQF_Builder::BPF( float freq, float bw ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	return BQF_Param
	(
		1.0f + alpha,
		-2.0f * cos(omega),
		1.0f - alpha,
		alpha,
		0.0f,
		-alpha
	);
}

constexpr BQF_Param BQF_Builder::NTC( float freq, float bw ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	return BQF_Param
	(
		1.0f + alpha,
		-2.0f * cos(omega),
		1.0f - alpha,
		1.0f,
		-2.0f * cos(omega),
		1.0f
	);
}

constexpr BQF_Param BQF_Builder::LSF( float freq, float q, float gain ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float A = pow(10.0f, (gain/40.0f));
	float beta = sqrt(A) / q;

	return BQF_Param
	(
		(A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega),
		-2.0f * ((A - 1.0f) + (A + 1.0f) * cos(omega)),
		(A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega),
		A * ((A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega)),
		2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos(omega)),
		A * ((A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega))
	);
}

constexpr BQF_Param BQF_Builder::HSF( float freq, float q, float gain ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float A = pow(10.0f, (gain/40.0f));
	float beta = sqrt(A) / q;

	return BQF_Param
	(
		(A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega),
		2.0f * ((A - 1.0f) - (A + 1.0f) * cos(omega)),
		(A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega),
		A * ((A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega)),
		-2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos(omega)),
		A * ((A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega))
	);
}

constexpr BQF_Param BQF_Builder::PK( float freq, float bw, float gain ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
	float A = pow(10.0f, (gain/40.0f));

	return BQF_Param
	(
		1.0f + alpha / A,
		-2.0f * cos(omega),
		1.0f - alpha / A,
		1.0f + alpha * A,
		-2.0f * cos(omega),
		1.0f - alpha * A
	);
}

constexpr BQF_Param BQF_Builder::APF( float freq, float q ) const
{
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	return BQF_Param
	(
		1.0f + alpha,
		-2.0f * cos(omega),
		1.0f - alpha,
		1.0f - alpha,
		-2.0f * cos(omega),
		1.0f + alpha
	);
}

#endif /* BQF_H_ */
