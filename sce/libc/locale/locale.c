/* libc.a member locale.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern void fiprintf();
extern void abort(void);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void _fwalk(int a0, void *a1);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);

/* newlib's C locale.  CHAR_MAX in every numeric field is newlib's "not
   available" marker; the three strings are the only ones the member owns. */
struct lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
};

static const struct lconv lconv = {
    ".", "", "", "", "", "", "", "", "", "", 127, 127, 127, 127, 127, 127, 127, 127,
};

int _setlocale_r(void *a0, int a1, const char *a2)
{
    if (a2 == 0)
        goto no_check;
    if (strcmp(a2, "C") == 0)
        goto found;
    if (strcmp(a2, "") != 0)
        return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = (int)a2;
no_check:
    return (int)"C";
}

void *_localeconv_r(int a0)
{
    return (void *)&lconv;
}

int setlocale(int a0, int a1)
{
    return _setlocale_r(D_0054CEAC[0], a0, a1);
}

void *localeconv(void)
{
    return _localeconv_r(D_0054CEAC[0]);
}

extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);
extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
