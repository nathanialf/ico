/* libc.a member atof.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

extern double strtod(const char *nptr, char **endptr);

/* newlib's atof: strtod without an end pointer. The ELF carries no symbol
 * for it; MAIN.MAP lists the member, and __svfscanf's float arm calls it. */
double atof(const char *ascii)
{
    return strtod(ascii, 0);
}
