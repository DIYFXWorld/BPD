#ifndef	Volume_h
#define	Volume_h

#include	"Myutil.h"

#define	VOLUME_RADIX	4095		// 10 bits

template <typename CurveT>
struct Volume
{
	int16_t		Initial_Value;
private:
	int16_t		Expected_Value;
public:
	int16_t		Current_Value;
	CurveT		Curve;

	Volume( const int16_t& v = 0 ) :
		Initial_Value( v ), Expected_Value( Curve( v ) ), Current_Value( Expected_Value )
	{}

	inline void Set_Value( const int16_t& v )
	{
		Initial_Value = v;
		Expected_Value = Curve( Initial_Value );
	}

	inline int16_t Get_Value()
	{
		if( Current_Value < Expected_Value ){	++Current_Value; }
		if( Current_Value > Expected_Value ){	--Current_Value; }

		return Current_Value;
	}

	inline void Fast_Forward()
	{
		Current_Value = Expected_Value;
	}

	inline int Per /*centage*/ ( int v )
	{
		return v * Get_Value() / VOLUME_RADIX;
	}
};


template <typename CurveT>
struct Volume_x
{
	int16_t		Initial_Value;
	int16_t		Current_Value;
	CurveT		Curve;
	
	Volume_x( const int16_t& v = 0 ):
		Initial_Value( v ), Current_Value( Curve( v ) )
	{
	}

	void Set_Value( const int16_t& v )
	{
		Initial_Value = v;
		Current_Value = Curve( Initial_Value );
	}

	int16_t Get_Value() const
	{
		return Current_Value;
	}

	inline int Per /*centage*/ ( int v )
	{
		return v * Current_Value / VOLUME_RADIX;
	}
};

//////////

const int	Potentiometer_Curve_Per_100	= VOLUME_RADIX;
const	int	Potentiometer_Curve_Per_10 	= Potentiometer_Curve_Per_100 * 10 / 100;
const	int	Potentiometer_Curve_Per_20 	= Potentiometer_Curve_Per_100 * 20 / 100;
const	int	Potentiometer_Curve_Per_35 	= Potentiometer_Curve_Per_100 * 35 / 100;
const	int	Potentiometer_Curve_Per_50	= Potentiometer_Curve_Per_100 * 50 / 100;
const	int	Potentiometer_Curve_Per_65	= Potentiometer_Curve_Per_100 * 65 / 100;
const	int	Potentiometer_Curve_Per_80 	= Potentiometer_Curve_Per_100 * 80 / 100;
const	int	Potentiometer_Curve_Per_90 	= Potentiometer_Curve_Per_100 * 90 / 100;

template <int width, int height>
int To_Curve_X( int v )
{
	v = Limit<0,Potentiometer_Curve_Per_100>( v );

       if(     0 <= v && v <  width   )      	 							return Map<    0,                       width,      0,                      height>( v );
	else if( width <= v && v <= Potentiometer_Curve_Per_100 )	return Map<width, Potentiometer_Curve_Per_100, height, Potentiometer_Curve_Per_100>( v );

	return 0;
}

inline int To_Curve_A( int v ) /*log*/ { return To_Curve_X<Potentiometer_Curve_Per_50, Potentiometer_Curve_Per_20>( v ); }
inline int To_Curve_B( int v ) /*lin*/ { return v; }
inline int To_Curve_C( int v ) /*exp*/ { return To_Curve_X<Potentiometer_Curve_Per_50, Potentiometer_Curve_Per_80>( v ); }
inline int To_Curve_D( int v ) /*log*/ { return To_Curve_X<Potentiometer_Curve_Per_65, Potentiometer_Curve_Per_20>( v ); }
inline int To_Curve_E( int v ) /*exp*/ { return To_Curve_X<Potentiometer_Curve_Per_35, Potentiometer_Curve_Per_80>( v ); }
inline int To_Curve_F( int v ) /*log*/ { return To_Curve_X<Potentiometer_Curve_Per_80, Potentiometer_Curve_Per_20>( v ); }
inline int To_Curve_G( int v ) /*exp*/ { return To_Curve_X<Potentiometer_Curve_Per_20, Potentiometer_Curve_Per_80>( v ); }
inline int To_Curve_H( int v ) /*log*/ { return To_Curve_X<Potentiometer_Curve_Per_90, Potentiometer_Curve_Per_10>( v ); }
inline int To_Curve_I( int v ) /*exp*/ { return To_Curve_X<Potentiometer_Curve_Per_10, Potentiometer_Curve_Per_90>( v ); }

struct Curve_A { int operator()( int v ) const { return To_Curve_A( v ); } };
struct Curve_B { int operator()( int v ) const { return To_Curve_B( v ); } };
struct Curve_C { int operator()( int v ) const { return To_Curve_C( v ); } };
struct Curve_D { int operator()( int v ) const { return To_Curve_D( v ); } };
struct Curve_E { int operator()( int v ) const { return To_Curve_E( v ); } };
struct Curve_F { int operator()( int v ) const { return To_Curve_F( v ); } };
struct Curve_G { int operator()( int v ) const { return To_Curve_G( v ); } };
struct Curve_H { int operator()( int v ) const { return To_Curve_H( v ); } };
struct Curve_I { int operator()( int v ) const { return To_Curve_I( v ); } };

#endif
