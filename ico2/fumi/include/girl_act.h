/*
 * ico2/fumi/include/girl_act.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what girl_act.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GIRL_ACT_H
#define GIRL_ACT_H

extern void ACTGame_GirlBeforeFunc(void *self);
extern void ClearGirlDangerGObj(void);
extern void Danger_Gondola(void *self);
extern void GirlAct_BoyAndMeCollisionMail(void *a0);
extern int IsGirlStatusEscortEnable(int a0, int a1);
extern void SetGirlDangerGObj(int a0);
extern void _girlBrainHide_MakeHidePoint(float *p, float dist);
extern void afterGirlHand(unsigned int a0);
extern void afterGirlHand100(volatile int a0);
extern void afterGirlHand200(volatile int a0);
extern void afterGirlHand50(volatile int a0);
extern void afterGirlHintPoint(volatile int a0);
extern void afterGirlPulledGo(void *a0);
extern void afterGirlSupportBGBegin(unsigned int a0);
extern int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n);
extern int girlBrainMain_CheckWarningMode(unsigned char check);
extern int isEnterHideadv_EnemyLocation(float *bpos, float *gpos);
extern int isMustCheckCylinder(void *a, void *b);
extern void subGirlBrainMain(void);
extern void subGirlCollision(void);
extern void subGirlControl(void);

#endif /* GIRL_ACT_H */
