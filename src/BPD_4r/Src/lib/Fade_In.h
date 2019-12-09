#ifndef	Fade_In_h
#define	Fade_In_h

struct Fade_In
{
	int		Step;
	int		Value;

	Fade_In( int step )
	: Step( step ), Value( step )
	{
	}

	void Start()	{ Value = 0; };

	int Process( int v )
	{
		if( Value != Step )
		{
				v = v * Value / Step;

			++Value;
		}

		return v;
	};
};

#endif
