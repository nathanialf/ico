/*
 * ico2/fumi/include/act-env.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act-env.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_ENV_H
#define ACT_ENV_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order act-env.c's inline tail has. */
void ACTSetEnvAllmighty(char *a0);
void GetSofaPosition(char *a0, char *a1);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);
int CheckWallAttributeEdegWall(int a0);

/* RECONSTRUCTION: ACTGetEnvironment's flag words (the caller passes the
 * actor's status block + 0x47C), read both as whole words and as single-bit
 * fields; the ROM proves the one-bit field stores (and/shift/or sequences)
 * and the word ORs.  The b0..b31 names are placeholders, not the developers'. */
typedef union {
    int w;

    struct {
        unsigned int b0 : 1;
        unsigned int b1 : 1;
        unsigned int b2 : 1;
        unsigned int b3 : 1;
        unsigned int b4 : 1;
        unsigned int b5 : 1;
        unsigned int b6 : 1;
        unsigned int b7 : 1;
        unsigned int b8 : 1;
        unsigned int b9 : 1;
        unsigned int b10 : 1;
        unsigned int b11 : 1;
        unsigned int b12 : 1;
        unsigned int b13 : 1;
        unsigned int b14 : 1;
        unsigned int b15 : 1;
        unsigned int b16 : 1;
        unsigned int b17 : 1;
        unsigned int b18 : 1;
        unsigned int b19 : 1;
        unsigned int b20 : 1;
        unsigned int b21 : 1;
        unsigned int b22 : 1;
        unsigned int b23 : 1;
        unsigned int b24 : 1;
        unsigned int b25 : 1;
        unsigned int b26 : 1;
        unsigned int b27 : 1;
        unsigned int b28 : 1;
        unsigned int b29 : 1;
        unsigned int b30 : 1;
        unsigned int b31 : 1;
    } bit;
} EnvFlag;

void ACTGetEnvironment(void *self, void *a1, float *orient, EnvFlag *flags, char *env);

#endif /* ACT_ENV_H */
