/*
 * ico2/script/include/st19a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st19a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST19A_H
#define ST19A_H

#include "typedef.h"

/* st19a.o's .sdata globals (MAIN.MAP) */
extern char *fence_up_19a;
extern char *fence_down_19a;
extern char *hgrm_19a;
extern char *pipe19a;
void actSt19aChainDown(GObj *volatile a0);
void actSt19aChainDownSub(GObj *volatile a0);
void actSt19aChainMain(GObj *volatile a0);
void actSt19aChainSwitch(GObj *volatile a0);
void actSt19aHagurumaChk(GObj *volatile a0);
void actSt19aOriMain(GObj *volatile a0);
void actSt19aOriSwitch(GObj *volatile a0);
void actSt19aOriUp(GObj *volatile a0);
void actSt19aPipeChk(GObj *volatile a0);

#endif /* ST19A_H */
