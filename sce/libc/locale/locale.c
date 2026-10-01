/* libc.a member locale.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <locale.h>

/* newlib's C locale.  CHAR_MAX in every numeric field is newlib's "not
   available" marker; the three strings are the only ones the member owns. */

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

struct lconv *_localeconv_r(struct Reent *data)
{
    return (struct lconv *)&lconv;
}

int setlocale(int a0, int a1)
{
    return _setlocale_r((int)_impure_ptr, a0, a1);
}

struct lconv *localeconv(void)
{
    return _localeconv_r(_impure_ptr);
}
