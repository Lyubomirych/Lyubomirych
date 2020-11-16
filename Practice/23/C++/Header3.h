#include "Header1.h"
#ifndef _Header3_h_
#define _Header3_h_
int soch(int k, int n)
{
	return fact(n) / (fact(k) * fact(n - k));
}
#endif