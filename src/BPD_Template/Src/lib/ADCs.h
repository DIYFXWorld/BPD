#ifndef	ADCs_h
#define	ADCs_h

#include	<stdint.h>

struct ADCs
{
private:

	static int16_t	*Elements;

public:

	static void Start();

	static void Update();

	static int16_t Get_Value( int i );

	static int Get_Count();
};

#endif
