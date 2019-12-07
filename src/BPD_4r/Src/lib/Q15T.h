#ifndef	Q15T_H
#define	Q15T_H

#include	<stdint.h>
#include	<math.h>

#define	Q15T_TO_16BIT( v )			( v.Value & 0xFF )
#define	Q15T_SET_VALUE( a, b )	( a.Value = (b) )
#define	Q15T_SET_0( v )					( v.Value = 0 )
#define	Q15T_SET_1( v )					( v.Value = 32768 )

#define	Q15T_0_5_VALUE					16384		/* 0.5 */
#define	Q15T_1_VALUE						32768		/* 1.0 */

struct Q15T_Raw_Value
{
	int32_t	Value;

	constexpr Q15T_Raw_Value( const int32_t v = 0 ) : Value( v ){}
};

struct Q15T
{
	int32_t	Value;

	constexpr Q15T():
		Value( 0 )
	{
	}

	constexpr explicit Q15T( const int& v ):
		Value( v * ( 1 << 15 ) )
	{
	}

	constexpr explicit Q15T( const float& v ):
		Value( round( v * ( 1 << 15 ) ) )
	{
	}

	constexpr explicit Q15T( const double& v ):
		Value( round( v * ( 1 << 15 ) ) )
	{
	}

	constexpr explicit Q15T( const Q15T_Raw_Value& v ):
		Value( v.Value )
	{
	}

	inline constexpr Q15T operator = ( const Q15T& v )
	{
		Value = v.Value;
		return *this;
	}

	inline bool operator == ( const Q15T& v ) const { return ( Value == v.Value ); }
	inline bool operator != ( const Q15T& v ) const { return ( Value != v.Value ); }
	inline bool operator <  ( const Q15T& v ) const { return ( Value <  v.Value ); }
	inline bool operator <= ( const Q15T& v ) const { return ( Value <= v.Value ); }
	inline bool operator >  ( const Q15T& v ) const { return ( Value >  v.Value ); }
	inline bool operator >= ( const Q15T& v ) const { return ( Value >= v.Value ); }

	inline int to_16bit() const	{ return Value & 0xFF; }
//	inline int to_int() const 	{ return Value >> 15; }
//	inline int to_round_int() const
//	{
//		return ( Value + Q15T_0_5_VALUE ) >> 15;
//	}

	inline int to_int() const 	{ return ( Value >= 0 ) ? Value >> 15 : ( Value + Q15T_1_VALUE -1/*offset*/ ) >> 15; }
	inline int to_round_int() const
	{
		return ( Value >= 0 ) ? ( Value + Q15T_0_5_VALUE ) >> 15 : ( Value + Q15T_0_5_VALUE -1/*offset*/ ) >> 15;
	}

	inline Q15T operator += ( const Q15T& v ) { Value += v.Value; return *this; }
	inline Q15T operator -= ( const Q15T& v ) { Value -= v.Value; return *this; }

	float to_real() const
	{
		int 	i( 15 );
		float	v( Value );

		while( i )
		{
			v /= 2.0;
			--i;
		}

		return v;
	}
};

////////// Addition //////////

inline Q15T operator + ( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = a.Value + b.Value;
	return Result;
}

inline Q15T operator + ( const int& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( a << 15 ) + b.Value;
	return Result;
}

inline Q15T operator + ( const Q15T& a, const int& b )
{
	Q15T	Result;
	Result.Value = a.Value + ( b << 15 );
	return Result;
}

////////// Subtraction //////////

inline Q15T operator - ( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = a.Value - b.Value;
	return Result;
}

inline Q15T operator - ( const int& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( a << 15 ) - b.Value;
	return Result;
}

inline Q15T operator - ( const Q15T& a, const int& b )
{
	Q15T	Result;
	Result.Value = a.Value - ( b << 15 );
	return Result;
}

////////// Multiplication //////////

inline Q15T operator * ( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( a.Value * b.Value ) >> 15;
	return Result;
}

inline Q15T operator * ( const Q15T& a, const int& b )
{
	Q15T	Result;
	Result.Value = a.Value * b;
	return Result;
}

inline Q15T operator * ( const int& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = a * b.Value;
	return Result;
}

inline Q15T Mul_L( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( a.Value >> 15 ) * b.Value;	// �I�[�o�[�t���[����ꍇ�͂ǂ������𐮐��ɂ���Ε��ʂɌv�Z�ł���
	return Result;
}

inline Q15T Mul_R( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = a.Value * ( b.Value >> 15 );	// �I�[�o�[�t���[����ꍇ�͂ǂ������𐮐��ɂ���Ε��ʂɌv�Z�ł���
	return Result;
}

inline Q15T Mul_64( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( int64_t( a.Value ) * b.Value ) >> 15;	// 64�r�b�g�g���͂ƂĂ��x��
	return Result;
}

////////// Division //////////

inline Q15T operator / ( const Q15T& a, const int& b )
{
	Q15T	Result;
	Result.Value = a.Value / b;
	return Result;
}

inline Q15T operator / ( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( a.Value << 15 ) / b.Value;
	return Result;
}

inline Q15T Div_64( const Q15T& a, const Q15T& b )
{
	Q15T	Result;
	Result.Value = ( int64_t( a.Value ) << 15 ) / b.Value;
	return Result;
}

inline Q15T Div_R( const Q15T& a, Q15T& b )
{
	Q15T	Result;
	Result.Value = a.Value / ( b.Value >> 15 );
	return Result;
}

#define	Q15T_TO_INT( a )		( a.Value >= 0 ) ? a.Value >> 15 : ( a.Value + Q15T_1_VALUE -1/*offset*/ ) >> 15

#define	Q15T_MUL_INT( a, b )	( a.Value * b )
#define	Q15T_DIV_INT( a, b )	( a.Value / b )

////////// constant

constexpr Q15T		Q15T_MAX( Q15T_Raw_Value( 2147483647 ) );
constexpr Q15T		Q15T_1( 1 );
constexpr Q15T		Q15T_M_1( -1 );

#endif
