#ifndef	Average_h
#define	Average_h

template <typename T, int Length>
struct Average
{
	T								Array[ Length ];
	      uint16_t	Write_Pointer;
	int32_t					Sum;

	Average(): Write_Pointer( 0 ), Sum( 0 )
	{
		for( uint16_t i( 0 ); i < Length; ++i )
			Array[ i ] = T();
	}

	void Set_Value( const T& v )
	{
		Sum -= Array[ Write_Pointer ];
		Array[ Write_Pointer ] = v;
		++Write_Pointer;
		if( Write_Pointer >= Length ) Write_Pointer = 0;
		Sum += v;
	}

	T Get_Value() const
	{
		return Sum / Length;
	}

	T Process( const T& v )
	{
		Sum -= Array[ Write_Pointer ];
		Array[ Write_Pointer ] = v;
		++Write_Pointer;
		if( Write_Pointer >= Length ) Write_Pointer = 0;
		Sum += v;
		return Sum / Length;
	}
};

#endif
