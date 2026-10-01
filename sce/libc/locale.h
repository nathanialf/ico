/*
 * sce/libc/locale.h
 *
 * Declarations of the entry points this tree calls, under the public name
 * of the newlib header for them (locale.h): the numeric and monetary
 * conventions record and the call that returns the C locale's.  Each one is
 * the signature of the member that defines the symbol in sce/.  Nothing here
 * is copied from an SDK header.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_LOCALE_H
#define SCE_LIBC_LOCALE_H

struct Reent;

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

struct lconv *localeconv(void);                  /* definition in sce/ */
struct lconv *_localeconv_r(struct Reent *data); /* definition in sce/ */

#endif /* SCE_LIBC_LOCALE_H */
