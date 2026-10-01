/*
 * ico2/script/include/st07a.h
 *
 * The declarations of what st07a.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST07A_H
#define ST07A_H

#include "typedef.h"

/* st07a.o's .sdata globals */
extern char *bridge;
extern char *sekizo7a;
extern char *sekizo_7a;
extern int sekizo_7a_vol;
void actSt07aChanChainChk(GObj *volatile a0);
void actSt07aChanChk(GObj *volatile a0);
void actSt07aChanEffect(GObj *volatile a0);
void actSt07aChanFall(GObj *volatile a0);
void actSt07aChanMot(GObj *volatile a0);
void actSt07aChanReadyChk(GObj *volatile a0);
void actSt07aChanWay1(volatile unsigned int a0);
void actSt07aChanWay2(volatile unsigned int a0);
void actSt07aEne2Chk(GObj *volatile a0);
void actSt07aEneChk(GObj *volatile a0);
void actSt07aGirlWay(volatile unsigned int a0);
void actSt07aIntroChk(GObj *volatile a0);
void actSt07aSekizoChk(GObj *volatile a0);
void actSt07aTsuroChk(GObj *volatile a0);
void actSt07aTsuroConte(GObj *volatile a0);
void actSt07aTsuroEffect(GObj *volatile a0);

#endif /* ST07A_H */
