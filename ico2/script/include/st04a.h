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

void actConte09(volatile int a0);
void actConte09Jimaku(volatile int a0);
void actConte09_2(volatile int a0);
void actConte09_3(volatile int a0);
void actConte09_3Jimaku(volatile int a0);
void actConte09_3_demoCancel(volatile int a0);
void actSt04aConte06(volatile int a0);
void actSt04aConte06Jimaku(volatile int a0);
void actSt04aEnvSe(volatile int a0);
void actSt04aEnvSeWakare1(volatile int a0);
void actSt04aEnvSeWakare2(volatile int a0);
void actSt04aGateChk(volatile int a0);
void actSt04aGateLChk(volatile int a0);
void actSt04aGateLSub(volatile int a0);
void actSt04aGateOpen2Chk(volatile int a0);
void actSt04aGateOpen2ReadyChk(volatile int a0);
void actSt04aGateOpen3Chk(volatile int a0);
void actSt04aGateOpenChk(volatile int a0);
void actSt04aGateRChk(volatile int a0);
void actSt04aGateRSub(volatile int a0);
void actSt04aGirlSitChk(volatile int a0);
void actSt04aModelOffChk(volatile int a0);
void actSt04aModelOnChk(volatile int a0);
void actSt04aTorch1Chk(volatile int a0);
void actSt04aTorchAllFlagfChk(volatile int a0);
void actSt04aTorchHintChk(volatile int a0);
void finishCallBackFunc(int a0);

#endif /* ST04A_H */
