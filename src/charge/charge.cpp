#include "charge.h"

void charge(int me, int n, int np, int *iBeg, int *iEnd)
{
//entre me, n et np et modifie les pointeurs iBeg et iEnd
    int q = n/np;
    int r = n - q*np;

    if (me < r)
    {
        *iBeg = me*(q+1);
        *iEnd = (me+1)*(q+1)-1;
    }
    else
    {
        *iBeg = r + me*(q);
        *iEnd = *iBeg + q-1;
    }
    
}