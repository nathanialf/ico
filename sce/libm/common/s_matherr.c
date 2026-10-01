/* libm.a member s_matherr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */

#include <math.h>

/* kept local: libgcc's soft-float entry point (dp-bit.c, long arguments), and libgcc2.h is not
   on this archive's include path */
extern int dpcmp(long a0, long a1);

int matherr(void *a0)
{
    long p = *(long *)((char *)a0 + 8);
    dpcmp(p, p);
    return 0;
}
