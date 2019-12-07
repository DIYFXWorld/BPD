#ifndef	FX_None_h
#define	FX_None_h

#include	"FX_Interface.h"

struct FX_None : public FX_Interface
{
	FX_None(){}

	void Destroy() { delete this; }

	int Process( int ) { return 0; }

	void Reset() {}

	FX_ID Get_FX_ID() const	{ return FX_ID_None; }
};

#endif
