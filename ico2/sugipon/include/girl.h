/*
 * ico2/sugipon/include/girl.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what girl.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GIRL_H
#define GIRL_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order girl.c's inline tail has. */
void SetGirlClothDispSwitch(char *a0, int a1, int a2);
void SetGirlHairDispSwitch(char *a0, int a1);
void setGirlClothSetting(int a0);

#endif /* GIRL_H */
