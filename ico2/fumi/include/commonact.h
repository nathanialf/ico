/*
 * ico2/fumi/include/commonact.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what commonact.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef COMMONACT_H
#define COMMONACT_H

extern void ACTAcceptMail(char *a0, int a1);
extern void ACTAdjustPlane(int a0, int a1);
extern int ACTGetOrientFromIntrK(char *self, int kind, void *buf, int i);
extern void ACTRunIntrCorrect(char *self, void *a1, void *a2);
extern void ACTSendMailCorrect(char *a0, int a1);
extern void ACTSetPositionWithFitting(void *a0, float *pos);
extern void ACT_LAYOUT_GAMEOVER(void);
extern int CollisCheckInRope(void *a0, int chain);
extern void ContinueCorrectPosition(void *obj);
extern void ControlMotionOrient(int a0, int a1);
extern void DamageFunc(char *a0);
extern void GetCorrectOrientOfChain(void *buf, void *obj);
extern int IsCorrectPosition(char *a0);
extern int SetMotionDirectionSmooze(int a0, float *dir, float s);
extern void StartCorrectPosition(char *a0, float *pos, float *dir, int mode, float t);
extern void TestCageUpDown(int cage, char *gobj);
extern int _ACTCorrectMsg(char *self, int msg, void *arg);
extern void _ACTDebugPrint(char *a0);
extern int _ACTMotDirSmzDirect(char *a0, float *a1);
extern void _boxbar_set_sound(int a0, int mode);
extern void actAfterDown(volatile int a0);
extern void actAfterFly(volatile int a0);
extern void actAfterForceRope(volatile int a0);
extern void actAfterForceRopeSwing(volatile int a0);
extern void actAfterJump(volatile int a0);
extern void actAfterRopeJump(volatile int a0);
extern void afterCommonBar(volatile int a0);
extern void afterCommonOneWall(int x);
extern void afterCommonRevive(volatile unsigned int a0);
extern void afterCommonRope(volatile int a0);
extern void afterCommonRopeTurnSpecial(volatile int a0);
extern void afterCommonStone(volatile int a0);
extern void afterCommonTruckLever(volatile int a0);
extern void flyCoreLoop(volatile int a0, char *target, int flag);
extern void subCommonIdle(void);
extern void *test_CURRENTORIENT(char *a0);
extern void *test_CURRENTROOT(void *a0);

#endif /* COMMONACT_H */
