#ifndef MATH_PRIVATE_H
#define MATH_PRIVATE_H

/* fdlibm float<->word access, as shipped in the PS2 SDK libm (sys/fdlibm).
 * The do{}while(0) is the standard macro idiom — it is NOT a codegen bandaid:
 * the union store/read it wraps is the natural source of the basic-block
 * boundary the ROM's isnanf/fabsf/copysignf bit-twiddles were compiled with.
 * Mirror fdlibm exactly so those functions recover in clean, faithful C. */

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
