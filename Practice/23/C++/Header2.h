#include "Header1.h"
#ifndef _Header2_h_
#define _Header2_h_
float sinx(float x, int k)
{
    int i;
    float sinx = x - pow(x,3)/6;
    if (k == 1) return sinx;
    for (i = 2; i <= k; i++)
    {
        int n = 2 * i + 1;
        sinx = sinx + pow(-1, i)*(pow(x,n)/(fact(n)));
    }
    return sinx;

}
#endif
