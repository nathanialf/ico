/*
 * ico2/script/include/st04a.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what st04a.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ST04A_H
#define ST04A_H

#include "typedef.h"

/* st04a.o's .sdata globals (MAIN.MAP) */
extern char *gate1st;
extern int gate1;
extern char *gate_ready_l;
extern char *gate_ready_r;
extern char *torch;
extern int gate_yure_low;
extern unsigned char gate_yure_low_vol;
extern int yure1;
extern unsigned char vol1;
extern int yure2;
extern unsigned char vol2;
void actConte09(GObj *volatile a0);
void actConte09Jimaku(GObj *volatile a0);
void actConte09_2(GObj *volatile a0);
void actConte09_3(GObj *volatile a0);
void actConte09_3Jimaku(GObj *volatile a0);
void actConte09_3_demoCancel(GObj *volatile a0);
void actSt04aConte06(GObj *volatile a0);
void actSt04aConte06Jimaku(GObj *volatile a0);
void actSt04aEnvSe(GObj *volatile a0);
void actSt04aEnvSeWakare1(GObj *volatile a0);
void actSt04aEnvSeWakare2(GObj *volatile a0);
void actSt04aGateChk(GObj *volatile a0);
void actSt04aGateLChk(GObj *volatile a0);
void actSt04aGateLSub(GObj *volatile a0);
void actSt04aGateOpen2Chk(GObj *volatile a0);
void actSt04aGateOpen2ReadyChk(GObj *volatile a0);
void actSt04aGateOpen3Chk(GObj *volatile a0);
void actSt04aGateOpenChk(GObj *volatile a0);
void actSt04aGateRChk(GObj *volatile a0);
void actSt04aGateRSub(GObj *volatile a0);
void actSt04aGirlSitChk(GObj *volatile a0);
void actSt04aModelOffChk(GObj *volatile a0);
void actSt04aModelOnChk(GObj *volatile a0);
void actSt04aTorch1Chk(GObj *volatile a0);
void actSt04aTorchAllFlagfChk(GObj *volatile a0);
void actSt04aTorchHintChk(GObj *volatile a0);
void finishCallBackFunc(int a0);

#endif /* ST04A_H */
