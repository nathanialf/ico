/*
 * ico2/script/include/st19a.h
 *
 * The declarations of what st19a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST19A_H
#define ST19A_H

#include "typedef.h"

/* st19a.o's .sdata globals */
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
