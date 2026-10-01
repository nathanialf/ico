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

char *_setlocale_r(struct Reent *data, int category, const char *locale)
{
    static char lc_ctype[8] = "C";
    static char last_lc_ctype[8] = "C";

    if (locale == 0)
        goto no_check;
    if (strcmp(locale, "C") == 0)
        goto found;
    if (strcmp(locale, "") != 0)
        return 0;
found:
    data->current_category = category;
    data->current_locale = locale;
no_check:
    return "C";
}

struct lconv *_localeconv_r(struct Reent *data)
{
    return (struct lconv *)&lconv;
}

char *setlocale(int category, const char *locale)
{
    return _setlocale_r(_impure_ptr, category, locale);
}

struct lconv *localeconv(void)
{
    return _localeconv_r(_impure_ptr);
}
