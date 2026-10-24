/*
 * ico2/script/include/st07a.h
 *
 * The declarations of what st07a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST07A_H
#define ST07A_H

#include "typedef.h"

struct SqEntry;

/* st07a.o's .sdata globals */
extern struct SqEntry *bridge;

#ifndef VERSION_JUN26
extern struct SqEntry *sekizo7a;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
extern int sekizo_7a;
extern unsigned char sekizo_7a_vol;
#else
extern struct SqEntry *sekizo_7a;
extern int sekizo_7a_vol;
#endif
#endif

void actSt07aChanChk(GObj *volatile self);
void actSt07aChanEffect(GObj *volatile self);
void actSt07aChanFall(GObj *volatile self);
void actSt07aChanMot(GObj *volatile self);

#ifndef VERSION_JUN26
void actSt07aChanWay1(volatile unsigned int self);
void actSt07aChanWay2(volatile unsigned int self);
void actSt07aEne2Chk(GObj *volatile self);
#endif

void actSt07aEneChk(GObj *volatile self);
void actSt07aGirlWay(volatile unsigned int self);
void actSt07aIntroChk(GObj *volatile self);

#ifdef VERSION_JUN26
void actSt07aTsuroChk(GObj *volatile self);
#else
void actSt07aSekizoChk(GObj *volatile self);
void actSt07aTsuroChk(GObj *volatile self);
void actSt07aTsuroConte(GObj *volatile self);
#endif

void actSt07aTsuroEffect(GObj *volatile self);

#endif /* ST07A_H */
