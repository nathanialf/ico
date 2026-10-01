/*
 * sce/libgcc/libgcc2.h
 *
 * The record shapes this archive's members share, under the public name the
 * archive's own sources use for this header.  The shapes follow the members'
 * loads and stores; nothing here is copied from an SDK header.
 */
#ifndef SCE_LIBGCC_LIBGCC2_H
#define SCE_LIBGCC_LIBGCC2_H

typedef struct {
    unsigned int type;
    int f4;
    int f8;
    int fC;
} PCmpV;

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
