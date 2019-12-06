#ifndef	Myutil_h
#define	Myutil_h

#include <stdint.h>

#define	DECI	(1/10)
#define	CENTI	(1/100)
#define	MILLI	(1/1000)
#define	MICRO	(1/1000/1000)
#define	NANO	(1/1000/1000/1000)
#define	PICO	(1/1000/1000/1000/1000)

#define	DECI_F	(1.0f/10.0f)
#define	CENTI_F	(1.0f/100.0f)
#define	MILLI_F	(1.0f/1000.0f)
#define	MICRO_F	(1.0f/1000.0f/1000.0f)
#define	NANO_F	(1.0f/1000.0f/1000.0f/1000.0f)
#define	PICO_F	(1.0f/1000.0f/1000.0f/1000.0f/1000.0f)

#define DECA	(10)
#define HECTO	(100)
#define	KILO	(1000)
#define	MEGA	(1000*1000)
#define	GIGA	(1000*1000*1000)
#define	TERA	(1000*1000*1000*1000)

template<typename T>
inline T Limit( const T& lo, const T& v, const T& hi )
{ 
	return ( v < lo ) ? lo : ( ( v > hi ) ? hi : v );
}

template<int lo, int hi>
inline int Limit( int v )
{
	return ( v < lo ) ? lo : ( ( v > hi ) ? hi : v );
}

template<typename T>
inline T Circuler( const T& lo, const T& v, const T& hi )
{ 
	return ( v < lo ) ? hi : ( ( v > hi ) ? lo : v );
}

template<int lo, int hi>
inline int Circuler( int v )
{ 
	return ( v < lo ) ? hi : ( ( v > hi ) ? lo : v );
}

inline int Map( const int& value, const int& from_low, const int& from_high, const int& to_low, const int& to_high )
{
	return ( value - from_low ) * ( to_high - to_low ) / ( from_high - from_low ) + to_low;
}

template <int from_low, int from_high, int to_low, int to_high>
inline int Map( const int& value )
{
	return ( value - from_low ) * ( to_high - to_low ) / ( from_high - from_low ) + to_low;
}

#define	MAP( v, LOW, HIGH )	((v)*(HIGH)/(LOW) )

#define Bit_Read( value, bit ) ( ( ( value ) >> ( bit ) ) & 0x01 )

#ifdef	USE_HAL_DRIVER
	#define	LIMIT_INT16( v )	__SSAT( v,  16 )
#else
	#define LIMIT_INT16( v )		Limit( INT16_MIN, v, INT16_MAX )
#endif

////////// 16bit utility

extern const	uint16_t	UINT16_HALF;

#define	  SIGNED_16( hoge )		( (hoge) - UINT16_HALF )
#define	UNSIGNED_16( hoge )		( (hoge) + UINT16_HALF )
#define	LIMIT_MIN_16( hoge )	if( hoge < INT16_MIN ){ hoge = INT16_MIN; }
#define	LIMIT_MAX_16( hoge )	if( hoge > INT16_MAX ){ hoge = INT16_MAX; }
#define	LIMIT_16( hoge )		 	if( hoge < INT16_MIN ){ hoge = INT16_MIN; }\
															else if( hoge > INT16_MAX ){ hoge = INT16_MAX; }

#define	HI_BYTE( v )				( ( v >> 8 ) & 0xFF )
#define	LO_BYTE( v )				( ( v >> 0 ) & 0xFF )

////////// 14bit utility

extern const	uint16_t	UINT14_MAX;
extern const	uint16_t	UINT14_HALF;
extern const	 int16_t	INT14_MAX;
extern const	 int16_t  INT14_MIN;

#define	  SIGNED_14( hoge )		( hoge - UINT14_HALF )
#define	UNSIGNED_14( hoge )		( hoge + UINT14_HALF )
#define	LIMIT_MIN_14( hoge )	if( hoge < INT14_MIN ){ hoge = INT14_MIN; }
#define	LIMIT_MAX_14( hoge )	if( hoge > INT14_MAX ){ hoge = INT14_MAX; }
#define	LIMIT_14( hoge )		 	if( hoge < INT14_MIN ){ hoge = INT14_MIN; }\
															else if( hoge > INT14_MAX ){ hoge = INT14_MAX; }

#define	HI_BIT_14( v )	(( v >> 7 ) & 0x7F )
#define	LO_BIT_14( v )	( v & 0x7F )

////////// 12bit utility

extern const	uint16_t	UINT12_MAX;
extern const	uint16_t	UINT12_HALF;
extern const	 int16_t	INT12_MAX;
extern const	 int16_t  INT12_MIN;

#define	  SIGNED_12( hoge )		( hoge - UINT12_HALF )
#define	UNSIGNED_12( hoge )		( hoge + UINT12_HALF )
#define	LIMIT_MIN_12( hoge )	if( hoge < INT12_MIN ){ hoge = INT12_MIN; }
#define	LIMIT_MAX_12( hoge )	if( hoge > INT12_MAX ){ hoge = INT12_MAX; }
#define	LIMIT_12( hoge )		 	if( hoge < INT12_MIN ){ hoge = INT12_MIN; }\
															else if( hoge > INT12_MAX ){ hoge = INT12_MAX; }

#define	HI_BIT_12( v )				(( v >> 6 ) & 0x3F )
#define	LO_BIT_12( v )				( v & 0x3F )

#define	_MS_2_LENGTH( ms, fs )		((ms)*(fs)/1000)
#define	_LENGTH_2_MS( len, fs )		(1000*(len)/(fs))

#define	MS_2_LENGTH( ms )		((ms)*(FS)/1000)
#define	LENGTH_2_MS( len )	(1000*(len)/(FS))

#define	MS_TO_UINT12( MS, MS_MAX )	( 4095 * MS / MS_MAX )

unsigned long Random();

template <typename T>
int Circuler_Inc( T v, T min, T max )
{
	++v;
	if( v > max )	v = min;
	return v;
}

template <typename T>
int Circuler_Dec( T v, T min, T max )
{
	--v;
	if( v < min )	v = max;
	return v;
}

#endif
