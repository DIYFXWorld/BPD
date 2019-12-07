#ifndef FX_Interface_h
#define FX_Interface_h

#include	<FX_ID.h>

struct FX_Interface
{
	virtual ~FX_Interface(){}

	virtual	void Destroy() = 0;

	virtual	int Process( int ) = 0;

	virtual void Set_Param_0( int )		{}
	virtual int  Get_Param_0() const	{ return 0; }

	virtual void Set_Param_1( int )		{}
	virtual int  Get_Param_1() const 	{ return 0; }

	virtual void Set_Param_2( int )		{}
	virtual int  Get_Param_2() const	{ return 0; }

	virtual void Set_Param_3( int )		{}
	virtual int  Get_Param_3() const	{ return 0; }

	virtual void Set_Param_4( int )		{}
	virtual int  Get_Param_4() const	{ return 0; }

	virtual void Set_Param_5( int )		{}
	virtual int  Get_Param_5() const	{ return 0; }

	virtual void Set_Param_6( int )		{}
	virtual int  Get_Param_6() const	{ return 0; }

	virtual void Set_Param_7( int )		{}
	virtual int  Get_Param_7() const	{ return 0; }

	virtual void Reset() = 0;

	virtual FX_ID Get_FX_ID() const = 0;
};

#endif
