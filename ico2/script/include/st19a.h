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
void actSt19aChainDown(GObj *volatile self);
void actSt19aChainMain(GObj *volatile self);
void actSt19aChainSwitch(GObj *volatile self);
void actSt19aHagurumaChk(GObj *volatile self);
void actSt19aOriMain(GObj *volatile self);
void actSt19aOriSwitch(GObj *volatile self);
void actSt19aOriUp(GObj *volatile self);
void actSt19aPipeChk(GObj *volatile self);

#endif /* ST19A_H */
