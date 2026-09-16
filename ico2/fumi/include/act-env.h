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

void ACTGetEnvironment(char *self, void *a1, float *orient, void *a3, void *a4);
void ACTSetEnvAllmighty(char *a0);
int CheckWallAttributeEdegWall(int a0);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);

#endif /* ACT_ENV_H */
