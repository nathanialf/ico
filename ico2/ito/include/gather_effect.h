/*
 * ico2/ito/include/gather_effect.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gather_effect.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GATHER_EFFECT_H
#define GATHER_EFFECT_H

extern int GatherEffect_Set(int kind, char *a, float *b, char *c, float f, void *fn);
extern void GatherEffect_SetGoal(int a0, void *a1);

#endif /* GATHER_EFFECT_H */
