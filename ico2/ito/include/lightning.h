/*
 * ico2/ito/include/lightning.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what lightning.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LIGHTNING_H
#define LIGHTNING_H

/* the lightning's colour, as four channel words or the two doublewords the
   packet takes */
typedef union { /* field names derived */
    unsigned int c[4];
    unsigned long long w[2];
} StructB;

/* one control point or strip vertex, read as floats, words or doublewords */
typedef union { /* field names derived */
    float f[4];
    int i[4];
    unsigned long long w[2];
} LightningVtx;

/* one entry of the caller's node array: a 16-byte position and the sort key
   cmpr compares */
typedef struct {      /* field names derived */
    LightningVtx pos; /* 0x00 */
    int key;          /* 0x10 */
    char pad14[12];   /* 0x14 */
} LightningNode;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order lightning.c's inline tail has. */
void apply_m34(void *out, void *m, void *in);

void DrawLightning(void *p0, void *p1, void *a2, float f0, float f1, float f2, float f3, float f4,
                   float f5, float f6, float f7, float f8, float f9, int a3);

void lightning_test(void);
int cmpr(LightningNode *self, LightningNode *other);

void DrawLightning2(int num, LightningVtx *v, StructB *col, float f0, float f1, float f2, float f3,
                    float f4, float f5, float f6, float f7, float f8, float f9, int c);

#endif /* LIGHTNING_H */
