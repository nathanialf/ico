/*
 * sce/libgcc/libgcc2.h
 *
 * PUBLIC SDK NAMING RUNG.  The disc attests no declaration-only header.  This
 * file carries the record shapes that this archive's members all carried a
 * private copy of; its name is the public one the archive's own sources use.
 * The shapes are read back from the ROM's loads and stores, not copied from
 * any SDK header.
 */
#ifndef SCE_LIBGCC_LIBGCC2_H
#define SCE_LIBGCC_LIBGCC2_H

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 10 TUs. */
typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 10 TUs. */
typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
    unsigned long long f10;
} PCmpV2;

typedef void (*func_ptr)(void);
/* _ctors.o's constructor and destructor lists, which __main.o walks. */
extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];
long long __fixunsdfdi(double a); /* definition in sce/libgcc/_fixunsdfdi.c */
/* The software floating point members' shared helpers: dp-bit.o's
   double-precision unpacker, which fp-bit.o's conversions call, and
   fp-bit.o's __make_fp, which dp-bit.o's conversions call. */
void __unpack_d(void *in, void *out);           /* definition in sce/libgcc/dp-bit.c */
void __make_fp(int a0, int a1, int a2, int a3); /* definition in sce/libgcc/fp-bit.c */

#endif /* SCE_LIBGCC_LIBGCC2_H */
