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

void actSt07aChanChainChk(volatile int a0);
void actSt07aChanChk(volatile int a0);
void actSt07aChanEffect(volatile int a0);
void actSt07aChanFall(volatile int a0);
void actSt07aChanMot(volatile int a0);
void actSt07aChanReadyChk(volatile int a0);
void actSt07aChanWay1(volatile unsigned int a0);
void actSt07aChanWay2(volatile unsigned int a0);
void actSt07aEne2Chk(volatile int a0);
void actSt07aEneChk(volatile int a0);
void actSt07aGirlWay(volatile unsigned int a0);
void actSt07aIntroChk(volatile int a0);
void actSt07aSekizoChk(volatile int a0);
void actSt07aTsuroChk(volatile int a0);
void actSt07aTsuroConte(volatile int a0);
void actSt07aTsuroEffect(volatile int a0);

#endif /* ST07A_H */
