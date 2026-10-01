/*
 * ico2/script/include/st07a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st07a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST07A_H
#define ST07A_H

#include "typedef.h"

/* st07a.o's .sdata globals (MAIN.MAP) */
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
