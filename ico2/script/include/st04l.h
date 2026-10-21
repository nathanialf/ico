/*
 * ico2/script/include/st04l.h
 *
 * The declarations of what st04l.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST04L_H
#define ST04L_H

#include "typedef.h"

struct SqEntry;

/* st04l.o's .sdata globals */
extern struct SqEntry *crest1;
extern struct SqEntry *crest2;
extern struct SqEntry *solar4l;
extern unsigned int st04l_yure;
extern unsigned char st04l_yure_vol;
extern unsigned int sekizo_4l;
extern unsigned char sekizo_4l_vol;
/* st04l.c's out-of-line handlers; the inline ones are declared in st04l.c,
   in the order the demo outputs them. */
void actSt04lBrg1Chk(GObj *volatile self);
void actSt04lBrg2Chk(GObj *volatile self);
void actSt04lC1BallTurn(GObj *volatile self);
void actSt04lC2BallTurn(GObj *volatile self);
void actSt04lCrest2Main(GObj *volatile self);
void actSt04lCrest3Main(GObj *volatile self);
void actSt04lCrestMain(GObj *volatile self);
void actSt04lGondolaChk(GObj *volatile self);
void actSt04lMonyou07Chk(GObj *volatile self);
void actSt04lOri2Chk(GObj *volatile self);
void actSt04lOriChk(GObj *volatile self);
void actSt04lSekizoChk(GObj *volatile self);
void actSt04lStairChk(GObj *volatile self);

#endif /* ST04L_H */
