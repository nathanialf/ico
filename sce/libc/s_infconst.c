/* libc.a member s_infconst.o (newlib libm/math/s_infconst.c): no code, the
 * one read-only double HUGE_VAL reads, +infinity (MAIN.MAP lines 670,
 * 6785-6786: .rodata 0x8). */
/* Infinity as a constant value.   This is used for HUGE_VAL.
 * Added by Cygnus Support.
 */

/* math.h's union, as strtod.c spells it; fdlibm.h would also bring the
 * endianness macros, and the EE is little-endian. */
union __dmath {
    unsigned int i[2];
    double d;
};

#ifndef _DOUBLE_IS_32BITS
#ifdef __IEEE_BIG_ENDIAN

const union __dmath __infinity = {0x7ff00000, 0};

#else

const union __dmath __infinity = {0, 0x7ff00000};

#endif
#else /* defined (_DOUBLE_IS_32BITS) */

const union __dmath __infinity = {0x7f800000, 0};

#endif /* defined (_DOUBLE_IS_32BITS) */
