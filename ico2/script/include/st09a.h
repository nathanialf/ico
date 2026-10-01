/*
 * ico2/script/include/st09a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st09a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST09A_H
#define ST09A_H

#include "typedef.h"

/* st09a.o's .sdata globals (MAIN.MAP) */
extern char *st09a_brg;
void actSt09aBrgDown(GObj *volatile a0);
void actSt09aBrgDownSub(GObj *volatile a0);
void actSt09aBrgMain(GObj *volatile a0);
void actSt09aBrgSwitch(GObj *volatile a0);
void actSt09aElvDown(GObj *volatile a0);
void actSt09aElvMain(GObj *volatile a0);
void actSt09aElvSwitch(GObj *volatile a0);
void actSt09aElvUp(GObj *volatile a0);
void actSt09aHint1Chk(GObj *volatile a0);
void actSt09aHint2Chk(GObj *volatile a0);
void actSt09aIntroChk(GObj *volatile a0);

#endif /* ST09A_H */
