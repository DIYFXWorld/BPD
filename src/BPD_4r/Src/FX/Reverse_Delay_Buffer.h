#ifndef	Reverse_Delay_Buffer_h
#define	Reverse_Delay_Buffer_h

#include	<stdint.h>

struct Reverse_Delay_Buffer
{
	Array<int16_t>	Memory;

  int	Length;
	int	Pointer;
	int	Direction;

	Reverse_Delay_Buffer( uint32_t memory_length ):
		Memory( memory_length ),
		Length( Memory.Length ), Pointer( 0 ), Direction( 1 )
	{
	}

	void Set_Length( int new_length )
	{
		if( new_length > ( int )Memory.Length ) new_length = Memory.Length-1;
		if( new_length <= 0 )				  	 				new_length = 1;

		if( new_length < Length )
		{
			for( int16_t* ptr = Memory.Pointer + new_length; ptr < Memory.Pointer + Length; ++ptr )
			{
				*ptr = 0;
			}
		}

		Length = new_length;

		if( Pointer >= Length )	Pointer = Length-1;
	}

	void Set_Value( const int16_t& v )
	{
		if( Pointer >= Length )	Reset();
		if( Pointer <       0 )	Reset();

		Memory[ Pointer ] = v;
		Pointer += Direction;

		     if( Pointer >= Length )	{ Pointer = Length-1; Direction = -1; }
		else if( Pointer <= -1 )			{ Pointer = 0;        Direction =  1; }
	}

	int16_t Get_Value() const { return Memory[ Pointer ]; }

	void Set_Value( uint32_t index, const int16_t& v ) { Memory[ index ] = v; }

	int16_t Get_Value( uint32_t index ) const { return Memory[ index ]; }

	void Reset()
	{
 		Pointer = 0;
 		Direction = 1;
	}
};

#endif
