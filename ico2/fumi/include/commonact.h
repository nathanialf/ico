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

void ACTAcceptMail(char *a0, int a1);
void ACTAdjustPlane(int a0, int a1);
int ACTGetOrientFromIntrK(char *self, int kind, void *buf, int i);

/* Reconstruction: the 0x18-byte actor mail record ico2/fumi/src/act.c
 * reconstructs as IntrMail (id at 0x10, flag word at 0x14); commonact.c
 * spells its members where the body needs them. */
struct IntrRec;

void ACTRunIntrCorrect(char *self, struct IntrRec *a1, struct IntrRec *a2);
void ACTSendMailCorrect(char *a0, int a1);
void ACTSetPositionWithFitting(void *a0, float *pos);
void ACT_LAYOUT_GAMEOVER(void);
int CollisCheckInRope(void *a0, int chain);
void ContinueCorrectPosition(void *obj);
void ControlMotionOrient(int a0, int a1);
void DamageFunc(char *a0);
void GetCorrectOrientOfChain(void *buf, void *obj);
int IsCorrectPosition(char *a0);
int SetMotionDirectionSmooze(int a0, float *dir, float s);
void StartCorrectPosition(char *a0, float *pos, float *dir, int mode, float t);
void TestCageUpDown(int cage, char *gobj);
int _ACTCorrectMsg(char *self, int msg, void *arg);
void _ACTDebugPrint(char *a0);
int _ACTMotDirSmzDirect(char *a0, float *a1);
void _boxbar_set_sound(int a0, int mode);
void actAfterDown(volatile int a0);
void actAfterFly(volatile int a0);
void actAfterForceRope(volatile int a0);
void actAfterForceRopeSwing(volatile int a0);
void actAfterJump(volatile int a0);
void actAfterRopeJump(volatile int a0);
void afterCommonBar(volatile int a0);
void afterCommonOneWall(int x);
void afterCommonRevive(volatile unsigned int a0);
void afterCommonRope(volatile int a0);
void afterCommonRopeTurnSpecial(volatile int a0);
void afterCommonStone(volatile int a0);
void afterCommonTruckLever(volatile int a0);
void flyCoreLoop(char *a0, char *target, int flag);
void subCommonIdle(volatile int a0);
void *test_CURRENTORIENT(char *a0);
void *test_CURRENTROOT(void *a0);

#endif /* COMMONACT_H */
