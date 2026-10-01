/*
 * ico2/ito/include/lightning.h
 *
 * The declarations of what lightning.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef LIGHTNING_H
#define LIGHTNING_H

/* the lightning's colour, as four channel words or the two doublewords the
   packet takes */
typedef union { /* field names derived */
    unsigned int c[4];
    unsigned long long w[2];
} LightningColor; /* derived name */

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

void apply_m34(void *out, void *m, void *in);

void DrawLightning(void *from, void *to, void *col, float stepMin, float stepMax, float swayStepMin, float swayStepMax, float turnMin,
                   float turnMax, float swayLimit, float width, float texLen, float seed, int c);

void lightning_test(void);

void DrawLightning2(int num, LightningVtx *v, LightningColor *col, float stepMin, float stepMax, float swayStepMin, float swayStepMax,
                    float turnMin, float turnMax, float swayLimit, float width, float texLen, float seed, int c);

#endif /* LIGHTNING_H */
