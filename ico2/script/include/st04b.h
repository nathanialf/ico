/*
 * ico2/script/include/st04b.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04b.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04B_H
#define ST04B_H

#include "typedef.h"

/* st04b.o's .sdata globals (MAIN.MAP) */
extern int sekizo4b;
extern int sekizo_4b;
extern unsigned char sekizo_4b_vol;
void actSt04bEne1Chk(GObj *volatile a0);
void actSt04bGirlWay(GObj *volatile a0);
void actSt04bSekizoChk(GObj *volatile a0);

#endif /* ST04B_H */
