/*
 * sce/libc/ctype.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header.  What
 * places this file is newlib's public naming: the classification bits and
 * the table ctype_.o defines, which newlib's header is called ctype.h for.
 * The bit values are the ROM's own table bytes read back.
 *
 * Only what this tree uses is declared.
 */
#ifndef SCE_LIBC_CTYPE_H
#define SCE_LIBC_CTYPE_H

#define _U 01
#define _L 02
#define _N 04
#define _S 010
#define _P 020
#define _C 040
#define _X 0100
#define _B 0200

extern const char _ctype_[]; /* definition in sce/ (ctype/ctype_.c) */

/* the table is read one byte in, so that EOF (-1) reads its leading zero; the
 * members and the game subscript it by the int value, and the GNU C toupper
 * reads its argument once */
#define isspace(c) ((_ctype_ + 1)[(int)(c)] & _S)
#define isupper(c) ((_ctype_ + 1)[(int)(c)] & _U)
#define islower(c) ((_ctype_ + 1)[(int)(c)] & _L)
#define toupper(c)                                                                                 \
    ({                                                                                             \
        int __x = (c);                                                                             \
        islower(__x) ? (__x - 'a' + 'A') : __x;                                                    \
    })

#endif /* SCE_LIBC_CTYPE_H */
