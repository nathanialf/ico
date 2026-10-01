/* libc.a member atof.o */
#include <stdlib.h>

/* newlib's atof: strtod without an end pointer.  The ELF carries no symbol
 * for it; __svfscanf's float arm calls it. */
double atof(const char *ascii)
{
    return strtod(ascii, 0);
}
