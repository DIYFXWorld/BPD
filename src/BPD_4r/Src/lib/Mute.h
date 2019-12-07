#ifndef	Mute_h
#define	Mute_h

struct Type_Mute
{
	int		Length;
	int		Value;
	int		Direction;
	bool	Active;

	Type_Mute( int length )
	: Length( length ), Value( length ), Direction( 0 ),  Active( false )
	{
	}

	void Start()
	{
		Value 		= Length-1;
		Direction = -1;
		Active		= true;
	};

	int Process( int v )
	{
		if( Active )
		{
				v = v * Value / Length;

			Value += Direction;

			if( ( Direction == -1 )  && Value ==      0 )	Direction = 1;
			if( ( Direction ==  1 )  && Value == Length )	Active = false;
		}

		return v;
	};

	void Reset()
	{
		Active = false;
	}
};

#endif
