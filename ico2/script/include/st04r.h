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

#include "typedef.h"

/* st04r.o's .sdata globals (MAIN.MAP) */
extern char *solar4r;
extern int ball1_4r;
extern int ball2_4r;
extern int ball3_4r;
extern char *crest1_4r;
extern int crest2_4r;
extern char *crest3_4r;
extern char *stair5d;
extern char *sekizo5c;
extern unsigned char st05d_hasi;
extern int st04r_yure;
extern unsigned char st04r_yure_vol;
extern int sekizo_4r;
void actSt04rBrg1Chk(GObj *volatile a0);
void actSt04rBrg1Sub(GObj *volatile a0);
void actSt04rBrg1WayChk(GObj *volatile a0);
void actSt04rBrg2Chk(GObj *volatile a0);
void actSt04rBrg2WayChk(GObj *volatile a0);
void actSt04rBrgCommon(GObj *volatile a0);
void actSt04rC1BallMain(GObj *volatile a0);
void actSt04rC1BallSwitch(GObj *volatile a0);
void actSt04rC1BallTurn(GObj *volatile a0);
void actSt04rC2BallMain(GObj *volatile a0);
void actSt04rC2BallSwitch(GObj *volatile a0);
void actSt04rC2BallTurn(GObj *volatile a0);
void actSt04rC3BallMain(GObj *volatile a0);
void actSt04rC3BallSwitch(GObj *volatile a0);
void actSt04rC3BallTurn(GObj *volatile a0);
void actSt04rCrest2Main(GObj *volatile a0);
void actSt04rCrestMain(GObj *volatile a0);
void actSt04rGondolaCharaChk(GObj *volatile a0);
void actSt04rSolarBeamChk(GObj *volatile a0);
void actSt04rSolarStageChangeChk(GObj *volatile a0);
void actSt04rTorch1_1Chk(GObj *volatile a0);
void actSt04rTorch1_2Chk(GObj *volatile a0);
void actSt04rTorch2_1Chk(GObj *volatile a0);
void actSt04rTorch2_1XLChk(GObj *volatile a0);
void actSt04rTorch2_2Chk(GObj *volatile a0);
void actSt04rTorch2_2XLChk(GObj *volatile a0);
void actSt04rTorch3_1Chk(GObj *volatile a0);
void actSt04rTorch3_2Chk(GObj *volatile a0);
void openGate(struct GObj *a0);

#endif /* ST04R_H */
