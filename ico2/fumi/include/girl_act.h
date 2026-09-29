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

/* girl_act.c defines these `inline`, so the compiler emits them after the
   rest of the file in the order they are first declared: this list is the
   ROM's order of the TU's closing run, 0x17B760..0x17C840.  The four
   subGirlBrain_* states, enemy_list_compare and ACTCheckCollis_SAFE follow
   through their first declarations in girl_act.c. */
void ACTGame_GirlBeforeFunc(void *self);
void *FindGirlPullupFloorBoxGObj(void);
void actGirlSupportGBBegin(volatile int a0);
void actGirlSupportGBLoop(volatile int a0);
void actGirlSupportGBEnd(volatile int a0);
void actGirlHangG3M(volatile int a0);
void actGirlDitch3mExec(volatile int a0);
void actGirlStand(volatile int a0);
void actGirlWalk(volatile int a0);
void actGirlRun(volatile int a0);
void actGirlHang(volatile int a0);
void actGirlBHang(volatile int a0);
void actGirlAttack(volatile int a0);
void actGirlBecall(volatile int a0);
void actGirlBehanged(volatile int a0);
void actGirlAttractAction(volatile int a0);
void actGirlHintVoice(volatile int a0);
void actGirlCannotReach(volatile int a0);
void actGirlHand50(volatile int a0);
void afterGirlHand50(volatile int a0);
void actGirlHand100(volatile int a0);
void afterGirlHand100(volatile int a0);
void actGirlHand200(volatile int a0);
void afterGirlHand200(volatile int a0);
int NotNeedBackHand(void);
void SetGirlDangerGObj(int a0);
void ClearGirlDangerGObj(void);
void GirlAct_BoyAndMeCollisionMail(void *a0);
int IsGirlStatusEscortEnable(int a0, int a1);
void _girlBrainHide_MakeHidePoint(float *p, float dist);
int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n);
int girlBrainMain_CheckWarningMode(unsigned char check);
int isEnterHideadv_EnemyLocation(float *bpos, float *gpos);
void subGirlBrainMain(volatile int a0);
void subGirlCollision(volatile int a0);
void subGirlControl(volatile int a0);

#endif /* GIRL_ACT_H */
