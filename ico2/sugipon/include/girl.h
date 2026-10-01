/*
 * ico2/sugipon/include/girl.h
 *
 * The declarations of what girl.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GIRL_H
#define GIRL_H

struct GObj;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order girl.c's inline tail has. */
void SetGirlClothDispSwitch(struct GObj *a0, int a1, int a2);
void SetGirlHairDispSwitch(struct GObj *a0, int a1);
void setGirlClothSetting(int a0);

#endif /* GIRL_H */
