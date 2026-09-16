/*
 * ico2/script/include/st04r.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04r.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04R_H
#define ST04R_H

void actSt04rBrg1Chk(volatile int a0);
void actSt04rBrg1Sub(volatile int a0);
void actSt04rBrg1WayChk(volatile int a0);
void actSt04rBrg2Chk(volatile int a0);
void actSt04rBrg2WayChk(volatile int a0);
void actSt04rBrgCommon(volatile int a0);
void actSt04rC1BallMain(volatile int a0);
void actSt04rC1BallSwitch(volatile int a0);
void actSt04rC1BallTurn(volatile int a0);
void actSt04rC2BallMain(volatile int a0);
void actSt04rC2BallSwitch(volatile int a0);
void actSt04rC2BallTurn(volatile int a0);
void actSt04rC3BallMain(volatile int a0);
void actSt04rC3BallSwitch(volatile int a0);
void actSt04rC3BallTurn(volatile int a0);
void actSt04rCrest2Main(volatile int a0);
void actSt04rCrestMain(volatile int a0);
void actSt04rGondolaCharaChk(volatile int a0);
void actSt04rSolarBeamChk(volatile int a0);
void actSt04rSolarStageChangeChk(volatile int a0);
void actSt04rTorch1_1Chk(volatile int a0);
void actSt04rTorch1_2Chk(volatile int a0);
void actSt04rTorch2_1Chk(volatile int a0);
void actSt04rTorch2_1XLChk(volatile int a0);
void actSt04rTorch2_2Chk(volatile int a0);
void actSt04rTorch2_2XLChk(volatile int a0);
void actSt04rTorch3_1Chk(volatile int a0);
void actSt04rTorch3_2Chk(volatile int a0);
void openGate(int a0);

#endif /* ST04R_H */
