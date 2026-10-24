/*
 * ico2/script/include/st19a.h
 *
 * The declarations of what st19a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST19A_H
#define ST19A_H

#include "typedef.h"

struct SqEntry;

/* st19a.o's .sdata globals */
extern struct SqEntry *fence_up_19a;
extern struct SqEntry *fence_down_19a;
extern struct SqEntry *hgrm_19a;
extern struct SqEntry *pipe19a;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
extern struct SqEntry *chain19a;
void actSt19aChainDown(GObj *volatile self);
void actSt19aChainUp(GObj *volatile self);
#else
void actSt19aChainDown(GObj *volatile self);
#endif
void actSt19aChainMain(GObj *volatile self);
void actSt19aChainSwitch(GObj *volatile self);
void actSt19aHagurumaChk(GObj *volatile self);
void actSt19aOriMain(GObj *volatile self);
void actSt19aOriSwitch(GObj *volatile self);
void actSt19aOriUp(GObj *volatile self);
void actSt19aPipeChk(GObj *volatile self);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void actSt19bIntroChk(GObj *volatile self);
#endif

#endif /* ST19A_H */
