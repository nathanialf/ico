/*
 * ico2/script/include/st04l.h
 *
 * The declarations of what st04l.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ST04L_H
#define ST04L_H

#include "typedef.h"

/* st04l.o's .sdata globals */
extern unsigned int ball1_4l;
extern char *ball2_4l;
extern char *ball3_4l;
extern char *crest1;
extern char *crest2;
extern int solar4l;
extern unsigned int oriup4c;
extern unsigned char oridown4c;
extern unsigned int st04l_yure;
extern unsigned char st04l_yure_vol;
void actSt04eSolarBeamChk(GObj *volatile a0);
void actSt04lBrg1Chk(GObj *volatile a0);
void actSt04lBrg1WayChk(GObj *volatile a0);
void actSt04lBrg2Chk(GObj *volatile a0);
void actSt04lBrg2WayChk(GObj *volatile a0);
void actSt04lC1BallMain(GObj *volatile a0);
void actSt04lC1BallSwitch(GObj *volatile a0);
void actSt04lC1BallTurn(GObj *volatile a0);
void actSt04lC2BallMain(GObj *volatile a0);
void actSt04lC2BallSwitch(GObj *volatile a0);
void actSt04lC2BallTurn(GObj *volatile a0);
void actSt04lC3BallMain(GObj *volatile a0);
void actSt04lC3BallSwitch(GObj *volatile a0);
void actSt04lC3BallTurn(GObj *volatile a0);
void actSt04lCrest2Main(GObj *volatile a0);
void actSt04lCrest3Main(GObj *volatile a0);
void actSt04lCrestMain(GObj *volatile a0);
void actSt04lGondolaCharaChk(GObj *volatile a0);
void actSt04lGondolaChk(GObj *volatile a0);
void actSt04lMonyou01Chk(GObj *volatile a0);
void actSt04lMonyou02Chk(GObj *volatile a0);
void actSt04lMonyou03Chk(GObj *volatile a0);
void actSt04lMonyou04Chk(GObj *volatile a0);
void actSt04lMonyou05Chk(GObj *volatile a0);
void actSt04lMonyou06Chk(GObj *volatile a0);
void actSt04lMonyou07Chk(GObj *volatile a0);
void actSt04lOri2Chk(GObj *volatile a0);
void actSt04lOriChk(GObj *volatile a0);
void actSt04lOriRopeCutLChk(GObj *volatile a0);
void actSt04lOriRopeCutRChk(GObj *volatile a0);
void actSt04lRope1Chk(GObj *volatile a0);
void actSt04lRope2Chk(GObj *volatile a0);
void actSt04lRope3Chk(GObj *volatile a0);
void actSt04lRope4Chk(GObj *volatile a0);
void actSt04lSekizoChk(GObj *volatile a0);
void actSt04lStairChk(GObj *volatile a0);
void actSt04lSwordChk(GObj *volatile a0);
void actSt04lTorch1_1Chk(GObj *volatile a0);
void actSt04lTorch1_2Chk(GObj *volatile a0);
void actSt04lTorch2_1Chk(GObj *volatile a0);
void actSt04lTorch2_1XLChk(GObj *volatile a0);
void actSt04lTorch2_2Chk(GObj *volatile a0);
void actSt04lTorch2_2XLChk(GObj *volatile a0);
void actSt04lTorch3_1Chk(GObj *volatile a0);
void actSt04lTorch3_2Chk(GObj *volatile a0);
void actSt04lTuriChk(GObj *volatile a0);
void turnBall(GObj *a0, int a1, int a2, int a3, int a4);

#endif /* ST04L_H */
