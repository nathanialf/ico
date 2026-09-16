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

void ACTGame_GirlBeforeFunc(void *self);
void ClearGirlDangerGObj(void);
void Danger_Gondola(void *self);
void GirlAct_BoyAndMeCollisionMail(void *a0);
int IsGirlStatusEscortEnable(int a0, int a1);
void SetGirlDangerGObj(int a0);
void _girlBrainHide_MakeHidePoint(float *p, float dist);
void afterGirlHand(unsigned int a0);
void afterGirlHand100(volatile int a0);
void afterGirlHand200(volatile int a0);
void afterGirlHand50(volatile int a0);
void afterGirlHintPoint(volatile int a0);
void afterGirlPulledGo(void *a0);
void afterGirlSupportBGBegin(unsigned int a0);
int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n);
int girlBrainMain_CheckWarningMode(unsigned char check);
int isEnterHideadv_EnemyLocation(float *bpos, float *gpos);
int isMustCheckCylinder(void *a, void *b);
void subGirlBrainMain(void);
void subGirlCollision(void);
void subGirlControl(void);

#endif /* GIRL_ACT_H */
