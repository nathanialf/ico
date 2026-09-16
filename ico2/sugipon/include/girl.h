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

extern void SetGirlClothDispSwitch(char *a0, int a1, int a2);
extern void SetGirlHairDispSwitch(char *a0, int a1);
extern void setGirlClothSetting(int a0);

#endif /* GIRL_H */
