/* libgcc.a member _floatdidf.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include "libgcc2.h"

typedef int SItype;

typedef unsigned int USItype;

typedef long long DItype;

typedef double DFtype;

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((unsigned long long)1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((unsigned long long)1) << WORD_SIZE)

DFtype __floatdidf(DItype u)
{
    DFtype d;

    d = (SItype)(u >> WORD_SIZE);
    d *= HIGH_HALFWORD_COEFF;
    d *= HIGH_HALFWORD_COEFF;
    d += (USItype)(u & (HIGH_WORD_COEFF - 1));
    return d;
}
