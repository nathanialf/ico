/*
 * ico2/script/include/st13b.h
 *
 * The declarations of what st13b.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST13B_H
#define ST13B_H

#include "typedef.h"

struct SqEntry;

/* st13b.o's .sdata globals */
extern struct SqEntry *sekizo13b;
extern struct SqEntry *sekizo13b2;
extern struct SqEntry *meets_again;
extern struct SqEntry *boss;
extern struct SqEntry *sd;
extern struct SqEntry *boss_dead;
extern struct SqEntry *st13b_up;
extern struct SqEntry *st13b_down;
extern int sekizo_13b;
extern unsigned char sekizo_13b_vol;
extern int st13b_yure;
extern unsigned char st13b_yure_vol;
void actConte10b(GObj *volatile self);
void actSt13bConte02(GObj *volatile self);
void actSt13bElevDown(GObj *volatile self);
void actSt13bElevUpChk(GObj *volatile self);
void actSt13bFloorChk(GObj *volatile self);
void actSt13bSekizo2Chk(GObj *volatile self);
void actSt13bSekizoChk(GObj *volatile self);

#endif /* ST13B_H */
