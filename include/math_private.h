#ifndef MATH_PRIVATE_H
#define MATH_PRIVATE_H

/* Float<->word access macros, re-derived clean-room from the public-domain
 * fdlibm reference (freely published, e.g. netlib's fdlibm) — NOT copied from
 * any SDK or other proprietary source. This is the well-known IEEE-754 idiom:
 * a union store/read whose do{}while(0) wrapper is the standard multi-statement
 * macro form, and also the natural source of the basic-block boundary the ROM's
 * isnanf/fabsf/copysignf bit-twiddles were compiled with. Recovering the
 * canonical public idiom lets those functions match in clean, faithful C. */

typedef union {
    float value;
    unsigned int word;
} ieee_float_shape_type;

/* Get a 32-bit int from a float. */
#define GET_FLOAT_WORD(i, d)                    \
    do {                                        \
        ieee_float_shape_type gf_u;             \
        gf_u.value = (d);                       \
        (i) = gf_u.word;                        \
    } while (0)

/* Set a float from a 32-bit int. */
#define SET_FLOAT_WORD(d, i)                    \
    do {                                        \
        ieee_float_shape_type sf_u;             \
        sf_u.word = (i);                        \
        (d) = sf_u.value;                       \
    } while (0)

#endif /* MATH_PRIVATE_H */
