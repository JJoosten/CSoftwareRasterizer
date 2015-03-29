#include "Validate.h"

bool IsPow2( const unsigned int x)
{
	return (bool)((x & ( x - 1)) == 0);
}