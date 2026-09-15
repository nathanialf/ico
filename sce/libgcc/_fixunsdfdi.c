/* libgcc.a member _fixunsdfdi.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
    unsigned long long f10;
} PCmpV2;

typedef unsigned int USItype;

typedef long long DItype;

typedef unsigned long long UDItype;

typedef double DFtype;

#define WORD_SIZE 32
#define HIGH_WORD_COEFF (((UDItype)1) << WORD_SIZE)

DItype __fixunsdfdi(DFtype a)
{
    DFtype b;
    UDItype v;

    if (a < 0)
        return 0;

    /* Compute high word of result, as a flonum.  */
    b = (a / HIGH_WORD_COEFF);
    /* Convert that to fixed (but not to DItype!),
       and shift it into the high word.  */
    v = (USItype)b;
    v <<= WORD_SIZE;
    /* Remove high part from the DFtype, leaving the low part as flonum.  */
    a -= (DFtype)v;
    /* Convert that to fixed (but not to DItype!) and add it in.  */
    if (a < 0)
        v -= (USItype)(-a);
    else
        v += (USItype)a;

    return v;
}
