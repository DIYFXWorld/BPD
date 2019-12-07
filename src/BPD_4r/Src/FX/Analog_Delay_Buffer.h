#ifndef	Analog_Delay_Buffer_h
#define	Analog_Delay_Buffer_h

#include 	"Array.h"
#include 	"Q15T.h"
#include	<stdint.h>

struct Analog_Delay_Buffer
{
	Array<int16_t>	Memory;

	uint32_t				Write_Pointer;
	Q15T						Read_Pointer;
	uint32_t				Length;

	Analog_Delay_Buffer( uint32_t memory_length )
	: Memory( memory_length ),
		Write_Pointer( 0 ), Read_Pointer( 0.0 ), Length( 1 )
	{
	}

	void Set_Param( int16_t v )
	{
		Memory[ Write_Pointer ] = v;

		++Write_Pointer;

		if( Write_Pointer == Memory.Length )	Write_Pointer = 0;
	}

	int16_t Get_Value()
	{
		int	index = Read_Pointer.to_int();

		int16_t	v = Memory[ index ];

		Read_Pointer += ( Q15T( Distance() ) / Length );

		if( ( uint32_t )Read_Pointer.to_int() >= Memory.Length )	Read_Pointer = Read_Pointer - Memory.Length;

		return v;
	}

	void Set_Length( uint32_t v )
	{
		if( v < 1 )	v = 1;	// Length�Ŋ���Z����̂�0�̓_����
		if( v > Memory.Length - 1 )	v = Memory.Length - 1;
		Length = v;
	}

	void Reset()
	{
		Read_Pointer = Q15T( int( Write_Pointer - Length ) );
		if( Read_Pointer.to_int() < 0 )	Read_Pointer = Read_Pointer + Memory.Length;
	}

	int Distance() const
	{
		int	v = Write_Pointer - Read_Pointer.to_int();
		if( v < 0 )	v += Memory.Length;
		return v;
	}
};

#endif
