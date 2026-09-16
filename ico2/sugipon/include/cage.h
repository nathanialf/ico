/*
 * ico2/sugipon/include/cage.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what cage.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CAGE_H
#define CAGE_H

int GetCageChainPoint(char *a0, char *a1, char *a2);
void HotInitCageGeo(char *self);
void SetCageVelocityFriction(char *a0, float a1);
void StabilizeAllLayoutedCage(void);

#endif /* CAGE_H */
