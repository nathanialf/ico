/*
 * ico2/script/include/st04l.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04l.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04L_H
#define ST04L_H

void actSt04eSolarBeamChk(volatile int a0);
void actSt04eSolarBeamChkSub(volatile int a0);
void actSt04lBallTurnCommon(volatile int a0);
void actSt04lBallTurnCommonSub(volatile int a0);
void actSt04lBrg1Chk(volatile int a0);
void actSt04lBrg1WayChk(volatile int a0);
void actSt04lBrg2Chk(volatile int a0);
void actSt04lBrg2WayChk(volatile int a0);
void actSt04lC1BallMain(volatile int a0);
void actSt04lC1BallSwitch(volatile int a0);
void actSt04lC1BallTurn(volatile int a0);
void actSt04lC2BallMain(volatile int a0);
void actSt04lC2BallSwitch(volatile int a0);
void actSt04lC2BallTurn(volatile int a0);
void actSt04lC3BallMain(volatile int a0);
void actSt04lC3BallSwitch(volatile int a0);
void actSt04lC3BallTurn(volatile int a0);
void actSt04lCrest2Main(volatile int a0);
void actSt04lCrest2Sub(volatile int a0);
void actSt04lCrest3Main(volatile int a0);
void actSt04lCrest3Sub(volatile int a0);
void actSt04lCrestMain(volatile int a0);
void actSt04lCrestSub(volatile int a0);
void actSt04lGondolaCharaChk(volatile int a0);
void actSt04lGondolaChk(volatile int a0);
void actSt04lMonyou01Chk(volatile int a0);
void actSt04lMonyou02Chk(volatile int a0);
void actSt04lMonyou03Chk(volatile int a0);
void actSt04lMonyou04Chk(volatile int a0);
void actSt04lMonyou05Chk(volatile int a0);
void actSt04lMonyou06Chk(volatile int a0);
void actSt04lMonyou07Chk(volatile int a0);
void actSt04lOri2Chk(volatile int a0);
void actSt04lOri2Sub(volatile int a0);
void actSt04lOriChk(volatile int a0);
void actSt04lOriRopeCutLChk(volatile int a0);
void actSt04lOriRopeCutRChk(volatile int a0);
void actSt04lOriSub(volatile int a0);
void actSt04lRope1Chk(volatile int a0);
void actSt04lRope2Chk(volatile int a0);
void actSt04lRope3Chk(volatile int a0);
void actSt04lRope4Chk(volatile int a0);
void actSt04lSekizoChk(volatile int a0);
void actSt04lStairChk(volatile int a0);
void actSt04lStairSub(volatile int a0);
void actSt04lSwordChk(volatile int a0);
void actSt04lTorch1_1Chk(volatile int a0);
void actSt04lTorch1_2Chk(volatile int a0);
void actSt04lTorch2_1Chk(volatile int a0);
void actSt04lTorch2_1XLChk(volatile int a0);
void actSt04lTorch2_2Chk(volatile int a0);
void actSt04lTorch2_2XLChk(volatile int a0);
void actSt04lTorch3_1Chk(volatile int a0);
void actSt04lTorch3_2Chk(volatile int a0);
void actSt04lTuriChk(volatile int a0);

#endif /* ST04L_H */
