/* libc.a member dtoa.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);

/* newlib Bigint: _next, _k, _maxwds, _sign, _wds, then the word array. */
typedef struct _Bigint {
    struct _Bigint *next; /* 0x00 */
    int k;                /* 0x04 */
    int maxwds;           /* 0x08 */
    int sign;             /* 0x0C */
    int wds;              /* 0x10 */
    unsigned int x[1];    /* 0x14 */
} Bigint;

extern int __mcmp(Bigint *a, Bigint *b);

static int quorem(Bigint *b, Bigint *S)
{
    int n;
    int borrow, y;
    unsigned int carry, q, ys;
    unsigned int *bx, *bxe, *sx, *sxe;
    int z;
    unsigned int si, zs;

    n = S->wds;
    if (b->wds < n) {
        return 0;
    }
    sx = S->x;
    sxe = sx + --n;
    bx = b->x;
    bxe = bx + n;
    q = *bxe / (*sxe + 1);
    if (q) {
        borrow = 0;
        carry = 0;
        do {
            si = *sx++;
            ys = (si & 0xFFFF) * q + carry;
            zs = (si >> 16) * q + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xFFFF) - (ys & 0xFFFF) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xFFFF) + borrow;
            borrow = z >> 16;
            ((unsigned short *)bx)[1] = (unsigned short)z;
            ((unsigned short *)bx)[0] = (unsigned short)y;
            bx++;
        } while (sx <= sxe);
        if (!*bxe) {
            bx = b->x;
            while (--bxe > bx && !*bxe) {
                --n;
            }
            b->wds = n;
        }
    }
    if (__mcmp(b, S) >= 0) {
        q++;
        borrow = 0;
        carry = 0;
        bx = b->x;
        sx = S->x;
        do {
            si = *sx++;
            ys = (si & 0xFFFF) + carry;
            zs = (si >> 16) + (ys >> 16);
            carry = zs >> 16;
            y = (*bx & 0xFFFF) - (ys & 0xFFFF) + borrow;
            borrow = y >> 16;
            z = (*bx >> 16) - (zs & 0xFFFF) + borrow;
            borrow = z >> 16;
            ((unsigned short *)bx)[1] = (unsigned short)z;
            ((unsigned short *)bx)[0] = (unsigned short)y;
            bx++;
        } while (sx <= sxe);
        bx = b->x;
        bxe = bx + n;
        if (!*bxe) {
            while (--bxe > bx && !*bxe) {
                --n;
            }
            b->wds = n;
        }
    }
    return q;
}

/* newlib mprec.h, IEEE little-endian: the double's high word is i[1]. */
union double_union {
    double d;
    unsigned int i[2];
};

#define word0(x) ((x).i[1])
#define word1(x) ((x).i[0])
#define Exp_shift1 20
#define Exp_msk1 0x100000
#define Exp_mask 0x7ff00000
#define P 53
#define Bias 1023
#define Exp_11 0x3ff00000
#define Frac_mask 0xfffff
#define Frac_mask1 0xfffff
#define Ten_pmax 22
#define Bletch 0x10
#define Bndry_mask 0xfffff
#define Log2P 1
#define Quick_max 14
#define Int_max 14
#define Sign_bit 0x80000000
#define n_bigtens 5

extern void _Bfree(void *ptr, Bigint *v);
extern Bigint *_Balloc(void *ptr, int k);
extern Bigint *_d2b(void *ptr, double d, int *e, int *bits);
extern Bigint *_i2b(void *ptr, int i);
extern Bigint *_pow5mult(void *ptr, Bigint *b, int k);
extern Bigint *_multiply(void *ptr, Bigint *a, Bigint *b);
extern Bigint *_lshift(void *ptr, Bigint *b, int k);
extern Bigint *__mdiff(void *ptr, Bigint *a, Bigint *b);
extern Bigint *_multadd(void *ptr, Bigint *b, int m, int a);
extern int _hi0bits(unsigned int x);
extern void *memcpy(void *dst, const void *src, unsigned int n);
/* mprec.o's tables: tens[23] and bigtens[5] */
extern const double D_006388A0[];
extern const double D_00638968[];

/* the reentrancy record's cached result string */
typedef struct {
    char pad0[0x40];
    Bigint *_result; /* 0x40 */
    int _result_k;   /* 0x44 */
} DtoaReent;

char *_dtoa_r(DtoaReent *ptr, double _d, int mode, int ndigits, int *decpt, int *sign, char **rve)
{
    int bbits, b2, b5, be, dig, i, ieps, ilim, ilim0, ilim1, j, j1, k, k0, k_check, leftright, m2,
        m5, s2, s5, spec_case, try_quick;
    union double_union d, d2, eps;
    int L;
    int denorm;
    unsigned int x;
    Bigint *b, *b1, *delta, *mlo, *mhi, *S;
    double ds;
    char *s, *s0;

    d.d = _d;

    if (ptr->_result) {
        ptr->_result->k = ptr->_result_k;
        ptr->_result->maxwds = 1 << ptr->_result_k;
        _Bfree(ptr, ptr->_result);
        ptr->_result = 0;
    }

    if (word0(d) & Sign_bit) {
        /* set sign for everything, including 0's */
        *sign = 1;
        word0(d) &= ~Sign_bit; /* clear sign bit */
    } else {
        *sign = 0;
    }

    if ((word0(d) & Exp_mask) == Exp_mask) {
        /* Infinity or NaN */
        *decpt = 9999;
        s = !word1(d) && !(word0(d) & 0xfffff) ? "Infinity" : "NaN";
        if (rve) {
            *rve = s[3] ? s + 8 : s + 3;
        }
        return s;
    }
    if (!d.d) {
        *decpt = 1;
        s = "0";
        if (rve) {
            *rve = s + 1;
        }
        return s;
    }

    b = _d2b(ptr, d.d, &be, &bbits);
    if ((i = (int)(word0(d) >> Exp_shift1 & (Exp_mask >> Exp_shift1))) != 0) {
        d2.d = d.d;
        word0(d2) &= Frac_mask1;
        word0(d2) |= Exp_11;

        i -= Bias;
        denorm = 0;
    } else {
        /* d is denormalized */

        i = bbits + be + (Bias + (P - 1) - 1);
        x = i > 32 ? word0(d) << (64 - i) | word1(d) >> (i - 32) : word1(d) << (32 - i);
        d2.d = x;
        word0(d2) -= 31 * Exp_msk1; /* adjust exponent */
        i -= (Bias + (P - 1) - 1) + 1;
        denorm = 1;
    }
    ds = (d2.d - 1.5) * 0.289529654602168 + 0.1760912590558 + i * 0.301029995663981;
    k = (int)ds;
    if (ds < 0. && ds != k) {
        k--; /* want k = floor(ds) */
    }
    k_check = 1;
    if (k >= 0 && k <= Ten_pmax) {
        if (d.d < D_006388A0[k]) {
            k--;
        }
        k_check = 0;
    }
    j = bbits - i - 1;
    if (j >= 0) {
        b2 = 0;
        s2 = j;
    } else {
        b2 = -j;
        s2 = 0;
    }
    if (k >= 0) {
        b5 = 0;
        s5 = k;
        s2 += k;
    } else {
        b2 -= k;
        b5 = -k;
        s5 = 0;
    }
    if (mode < 0 || mode > 9) {
        mode = 0;
    }
    try_quick = 1;
    if (mode > 5) {
        mode -= 4;
        try_quick = 0;
    }
    leftright = 1;
    switch (mode) {
    case 0:
    case 1:
        ilim = ilim1 = -1;
        i = 18;
        ndigits = 0;
        break;
    case 2:
        leftright = 0;
        /* no break */
    case 4:
        if (ndigits <= 0) {
            ndigits = 1;
        }
        ilim = ilim1 = i = ndigits;
        break;
    case 3:
        leftright = 0;
        /* no break */
    case 5:
        i = ndigits + k + 1;
        ilim = i;
        ilim1 = i - 1;
        if (i <= 0) {
            i = 1;
        }
    }
    j = sizeof(unsigned int);
    for (ptr->_result_k = 0; sizeof(Bigint) - sizeof(unsigned int) + j <= i; j <<= 1) {
        ptr->_result_k++;
    }
    ptr->_result = _Balloc(ptr, ptr->_result_k);
    s = s0 = (char *)ptr->_result;

    if (ilim >= 0 && ilim <= Quick_max && try_quick) {
        /* Try to get by with floating-point arithmetic. */

        i = 0;
        d2.d = d.d;
        k0 = k;
        ilim0 = ilim;
        ieps = 2; /* conservative */
        if (k > 0) {
            ds = D_006388A0[k & 0xf];
            j = k >> 4;
            if (j & Bletch) {
                /* prevent overflows */
                j &= Bletch - 1;
                d.d /= D_00638968[n_bigtens - 1];
                ieps++;
            }
            for (; j; j >>= 1, i++) {
                if (j & 1) {
                    ieps++;
                    ds *= D_00638968[i];
                }
            }
            d.d /= ds;
        } else if ((j1 = -k) != 0) {
            d.d *= D_006388A0[j1 & 0xf];
            for (j = j1 >> 4; j; j >>= 1, i++) {
                if (j & 1) {
                    ieps++;
                    d.d *= D_00638968[i];
                }
            }
        }
        if (k_check && d.d < 1. && ilim > 0) {
            if (ilim1 <= 0) {
                goto fast_failed;
            }
            ilim = ilim1;
            k--;
            d.d *= 10.;
            ieps++;
        }
        eps.d = ieps * d.d + 7.;
        word0(eps) -= (P - 1) * Exp_msk1;
        if (ilim == 0) {
            S = mhi = 0;
            d.d -= 5.;
            if (d.d > eps.d) {
                goto one_digit;
            }
            if (d.d < -eps.d) {
                goto no_digits;
            }
            goto fast_failed;
        }
        if (leftright) {
            /* Use Steele & White method of only
             * generating digits needed.
             */
            eps.d = 0.5 / D_006388A0[ilim - 1] - eps.d;
            for (i = 0;;) {
                L = d.d;
                d.d -= L;
                *s++ = '0' + (int)L;
                if (d.d < eps.d) {
                    goto ret1;
                }
                if (1. - d.d < eps.d) {
                    goto bump_up;
                }
                if (++i >= ilim) {
                    break;
                }
                eps.d *= 10.;
                d.d *= 10.;
            }
        } else {
            /* Generate ilim digits, then fix them up. */
            eps.d *= D_006388A0[ilim - 1];
            for (i = 1;; i++, d.d *= 10.) {
                L = d.d;
                d.d -= L;
                *s++ = '0' + (int)L;
                if (i == ilim) {
                    if (d.d > 0.5 + eps.d) {
                        goto bump_up;
                    } else if (d.d < 0.5 - eps.d) {
                        while (*--s == '0')
                            ;
                        s++;
                        goto ret1;
                    }
                    break;
                }
            }
        }
    fast_failed:
        s = s0;
        d.d = d2.d;
        k = k0;
        ilim = ilim0;
    }

    /* Do we have a "small" integer? */

    if (be >= 0 && k <= Int_max) {
        /* Yes. */
        ds = D_006388A0[k];
        if (ndigits < 0 && ilim <= 0) {
            S = mhi = 0;
            if (ilim < 0 || d.d <= 5 * ds) {
                goto no_digits;
            }
            goto one_digit;
        }
        for (i = 1;; i++) {
            L = d.d / ds;
            d.d -= L * ds;
            *s++ = '0' + (int)L;
            if (i == ilim) {
                d.d += d.d;
                if (d.d > ds || (d.d == ds && L & 1)) {
                bump_up:
                    while (*--s == '9') {
                        if (s == s0) {
                            k++;
                            *s = '0';
                            break;
                        }
                    }
                    ++*s++;
                }
                break;
            }
            if (!(d.d *= 10.)) {
                break;
            }
        }
        goto ret1;
    }

    m2 = b2;
    m5 = b5;
    mhi = mlo = 0;
    if (leftright) {
        if (mode < 2) {
            i = denorm ? be + (Bias + (P - 1) - 1 + 1) : 1 + P - bbits;
        } else {
            j = ilim - 1;
            if (m5 >= j) {
                m5 -= j;
            } else {
                s5 += j -= m5;
                b5 += j;
                m5 = 0;
            }
            if ((i = ilim) < 0) {
                m2 -= i;
                i = 0;
            }
        }
        b2 += i;
        s2 += i;
        mhi = _i2b(ptr, 1);
    }
    if (m2 > 0 && s2 > 0) {
        i = m2 < s2 ? m2 : s2;
        b2 -= i;
        m2 -= i;
        s2 -= i;
    }
    if (b5 > 0) {
        if (leftright) {
            if (m5 > 0) {
                mhi = _pow5mult(ptr, mhi, m5);
                b1 = _multiply(ptr, mhi, b);
                _Bfree(ptr, b);
                b = b1;
            }
            if ((j = b5 - m5) != 0) {
                b = _pow5mult(ptr, b, j);
            }
        } else {
            b = _pow5mult(ptr, b, b5);
        }
    }
    S = _i2b(ptr, 1);
    if (s5 > 0) {
        S = _pow5mult(ptr, S, s5);
    }

    /* Check for special case that d is a normalized power of 2. */

    if (mode < 2) {
        if (!word1(d) && !(word0(d) & Bndry_mask) && word0(d) & Exp_mask) {
            /* The special case */
            b2 += Log2P;
            s2 += Log2P;
            spec_case = 1;
        } else {
            spec_case = 0;
        }
    }

    /* Arrange for convenient computation of quotients:
     * shift left if necessary so divisor has 4 leading 0 bits.
     */
    if ((i = ((s5 ? 32 - _hi0bits(S->x[S->wds - 1]) : 1) + s2) & 0x1f) != 0) {
        i = 32 - i;
    }
    if (i > 4) {
        i -= 4;
        b2 += i;
        m2 += i;
        s2 += i;
    } else if (i < 4) {
        i += 28;
        b2 += i;
        m2 += i;
        s2 += i;
    }
    if (b2 > 0) {
        b = _lshift(ptr, b, b2);
    }
    if (s2 > 0) {
        S = _lshift(ptr, S, s2);
    }
    if (k_check) {
        if (__mcmp(b, S) < 0) {
            k--;
            b = _multadd(ptr, b, 10, 0); /* we botched the k estimate */
            if (leftright) {
                mhi = _multadd(ptr, mhi, 10, 0);
            }
            ilim = ilim1;
        }
    }
    if (ilim <= 0 && mode > 2) {
        if (ilim < 0 || __mcmp(b, S = _multadd(ptr, S, 5, 0)) <= 0) {
            /* no digits, fcvt style */
        no_digits:
            k = -1 - ndigits;
            goto ret;
        }
    one_digit:
        *s++ = '1';
        k++;
        goto ret;
    }
    if (leftright) {
        if (m2 > 0) {
            mhi = _lshift(ptr, mhi, m2);
        }

        /* Compute mlo -- check for special case
         * that d is a normalized power of 2.
         */

        mlo = mhi;
        if (spec_case) {
            mhi = _Balloc(ptr, mhi->k);
            memcpy((char *)&mhi->sign, (char *)&mlo->sign,
                   mlo->wds * sizeof(int) + 2 * sizeof(int));
            mhi = _lshift(ptr, mhi, Log2P);
        }

        for (i = 1;; i++) {
            dig = quorem(b, S) + '0';
            /* Do we yet have the shortest decimal string
             * that will round to d?
             */
            j = __mcmp(b, mlo);
            delta = __mdiff(ptr, S, mhi);
            j1 = delta->sign ? 1 : __mcmp(b, delta);
            _Bfree(ptr, delta);
            if (j1 == 0 && !mode && !(word1(d) & 1)) {
                if (dig == '9') {
                    goto round_9_up;
                }
                if (j > 0) {
                    dig++;
                }
                *s++ = dig;
                goto ret;
            }
            if (j < 0 || (j == 0 && !mode && !(word1(d) & 1))) {
                if (j1 > 0) {
                    b = _lshift(ptr, b, 1);
                    j1 = __mcmp(b, S);
                    if ((j1 > 0 || (j1 == 0 && dig & 1)) && dig++ == '9') {
                        goto round_9_up;
                    }
                }
                *s++ = dig;
                goto ret;
            }
            if (j1 > 0) {
                if (dig == '9') { /* possible if i == 1 */
                round_9_up:
                    *s++ = '9';
                    goto roundoff;
                }
                *s++ = dig + 1;
                goto ret;
            }
            *s++ = dig;
            if (i == ilim) {
                break;
            }
            b = _multadd(ptr, b, 10, 0);
            if (mlo == mhi) {
                mlo = mhi = _multadd(ptr, mhi, 10, 0);
            } else {
                mlo = _multadd(ptr, mlo, 10, 0);
                mhi = _multadd(ptr, mhi, 10, 0);
            }
        }
    } else {
        for (i = 1;; i++) {
            *s++ = dig = quorem(b, S) + '0';
            if (i >= ilim) {
                break;
            }
            b = _multadd(ptr, b, 10, 0);
        }
    }

    /* Round off last digit */

    b = _lshift(ptr, b, 1);
    j = __mcmp(b, S);
    if (j > 0 || (j == 0 && dig & 1)) {
    roundoff:
        while (*--s == '9') {
            if (s == s0) {
                k++;
                *s++ = '1';
                goto ret;
            }
        }
        ++*s++;
    } else {
        while (*--s == '0')
            ;
        s++;
    }
ret:
    _Bfree(ptr, S);
    if (mhi) {
        if (mlo && mlo != mhi) {
            _Bfree(ptr, mlo);
        }
        _Bfree(ptr, mhi);
    }
ret1:
    _Bfree(ptr, b);
    *s = 0;
    *decpt = k + 1;
    if (rve) {
        *rve = s;
    }
    return s0;
}
