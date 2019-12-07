#ifndef	Toggle_Switch_h
#define	Toggle_Switch_h

#include	"Port.h"

struct Toggle_Switch
{
	enum Pin_State { Pin_None, Pin_0, Pin_1, Pin_OFF };

private:

	Port				Pin[ 2 ];
	Pin_State		Last;

public:

	Pin_State		State;
	bool				Edge;
	bool				Active;

	Toggle_Switch
	(
		GPIO_TypeDef*	gpio_0, uint16_t pin_0,
		GPIO_TypeDef*	gpio_1, uint16_t pin_1,
		bool logic = true
	) :
		Last( Pin_None ), State( Pin_None ), Edge( false ), Active( true )
	{
		Pin[ 0 ] = Port( gpio_0, pin_0, logic );
		Pin[ 1 ] = Port( gpio_1, pin_1, logic );
	}

	void Update()
	{
		     if( Pin[ 0 ].Read() )	State = Pin_0;
		else if( Pin[ 1 ].Read() )	State = Pin_1;
		else												State = Pin_OFF;

		if( !Active && ( Last != State ) )	Active = true;

		if( Active )
		{
			Edge  = ( Last != State );
			Last	= State;
		}
	}

	bool Is_ON_Edge() const 	{ return Edge && ( State != Pin_OFF ); }
	bool Is_OFF_Edge() const	{ return Edge && ( State == Pin_OFF ); }
	bool Is_Edge() const 			{ return ( Is_ON_Edge() || Is_OFF_Edge() ); }

	Pin_State Get_Value() const { return State; }

	void Hold()
	{
		Active = false;
		Last = State;
	}
	void Release() { Active = true; }
};

#endif
