/*
 * ico2/script/include/st05b.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st05b.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST05B_H
#define ST05B_H

#include "typedef.h"

/* st05b.o's .sdata globals (MAIN.MAP) */
extern char *sekizo5b;
extern int sekizo_5b;
extern unsigned char sekizo_5b_vol;
void actSt05bGirlWay(GObj *volatile a0);
void actSt05bSekizoChk(GObj *volatile a0);

#endif /* ST05B_H */
