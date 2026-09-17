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

void ACTGetEnvironment(char *self, void *a1, float *orient, void *a3, void *a4);

#endif /* ACT_ENV_H */
