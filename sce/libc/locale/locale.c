/* libc.a member locale.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

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

int __mb_cur_max = 1;

static const struct lconv lconv = {
    ".", "", "", "", "", "", "", "", "", "", 127, 127, 127, 127, 127, 127, 127, 127,
};

int _setlocale_r(void *a0, int a1, const char *a2)
{
    static char lc_ctype[8] = "C";
    static char last_lc_ctype[8] = "C";

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
    return _setlocale_r((int)_impure_ptr, a0, a1);
}

void *localeconv(void)
{
    return _localeconv_r((int)_impure_ptr);
}
