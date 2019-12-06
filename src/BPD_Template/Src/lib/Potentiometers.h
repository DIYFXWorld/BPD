#ifndef	Potentiometers_h
#define	Potentiometers_h

#include "Myutil.h"
#include "ADCs.h"
#include "Median_9.h"
#include "Average.h"
#include <math.h>	// for abs

struct Potentiometer
{
	Median_9<uint16_t>		MDF;
	Average<uint16_t,10>	Ave;

	uint16_t							Value;
	uint8_t								Index;
	bool									Active;
	uint16_t							Hold_Value;

	Potentiometer():
		Value( 0 ), Index( 255 ), Active( true ),  Hold_Value( 0 )
	{
	}

	void Hold()
	{
		Active = false;
		Hold_Value = Value;
	}

	void Release() { Active = true; }

	uint16_t Get_Value() { return Value; }

	void Update()
	{
		Value = Ave.Process( MDF.Process( ADCs::Get_Value( Index ) ) );

		if( !Active && abs( ( int )Hold_Value - ( int )Value ) > 409 )
				Active = true;
	}
};

struct Potentiometers
{
	static Potentiometer	*Items;

	static void Start()
	{
		Items = new Potentiometer[ ADCs::Get_Count() ];

		for( auto	i( 0 ); i < ADCs::Get_Count(); ++i )
			Items[ i ].Index = i;

		ADCs::Start();
	}

	static void Update()
	{ 
		ADCs::Update();

		for( auto	i( 0 ); i < ADCs::Get_Count(); ++i )
			Items[ i ].Update();
	}

	static int Get_Count() { return ADCs::Get_Count(); }

	Potentiometer& operator[] ( int i )       { return Items[ i ]; }
	Potentiometer& operator[] ( int i ) const { return Items[ i ]; }
};

#endif
