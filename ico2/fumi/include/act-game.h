/*
 * ico2/fumi/include/act-game.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what act-game.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef ACT_GAME_H
#define ACT_GAME_H

extern void ACTCharctrl_Lock(char *a0);
extern int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3);
extern int ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
extern int ACTCheckView(char *self, void *a1, void *a2, void *a3, float f);
extern int ACTCheckViewCl(char *self, void *a1, void *a2, void *a3, float f);
extern int ACTChkAttackIgnore_BOY(char *a0);
extern int ACTChkAttackIgnore_ENEMY(char *a0);
extern int ACTChkAttackIgnore_GIRL(char *a0, int *a1);
extern void ACTGameCollisionOff(volatile int *self);
extern void ACTGameCollisionOn(volatile int *self);
extern void ACTGameView_Add(char *a0, char *a1);
extern int ACTGameView_Check(int a0, int a1);
extern void ACTGameView_FirstSet(void);
extern void ACTGameView_Init(void);
extern void ACTGame_BeforeFunc(char *self);
extern int ACTGame_CheckHandMotion(char *a0, char *a1);
extern void ACTGame_ConnectHand(void);
extern void ACTGame_DisconnectHand(void);
extern unsigned char ACTGame_FLAG_TETSUNAGI(void);
extern int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
extern void ACTGame_InnerVelocityUpdate(char *self);
extern void ACTGame_InsertCamera_GirlIsPinch(void);
extern void ACTGame_LwsEffectInit(char *a0);
extern void ACTGame_LwsEffect_Guard(char *a0);
extern unsigned char ACTGame_NoWeapon(char *a0);
extern void ACTGame_SaveActorInformation(char *a0);
extern void ACTGame_SendSoundMail(char *a0, int mail, int a2, int a3, int a4);
extern void ACTGame_SetActors_Debug(int stage, int a1);
extern void ACTGame_SetMotionPlaySpeedRatio_Reserve(char *a0, float f, unsigned int a1);
extern void ACTGame_StageChangeGObj(char *self, int idx);
extern void ACTGame_StageChangeGObjDirect(int *a0, int a1, void *a2, int a3);
extern int ACTGame_isHangChain(char *a0);
extern int ACTGame_isWeaponCombustible(void);
extern int ACTGame_isWeaponEnableCatchfire(int *self);
extern void ACTItemForceDrop(char *a0);
extern void ACTLookTarget_Init(char *a0);
extern int ACTNotNeedCameraOffset(char *a0);
extern void ACTParaStatus_Init(char *a0);
extern void ActGame_GetOrientQ(void *q, void *v, int deg);
extern void FunctionAboutClingedStatus(char *self);
extern void GetOtherStageGirlOrient(float *a0, float *a1);
extern void GetSkeltonOrient(float *out, void *obj, int node);
extern void GetSkeltonPosition(float *dst, char *obj, void *a2);
extern void PAIR_GetPosition_BOY(float *a0, float *a1);
extern void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1);
extern int PAIR_IsStatus_BOY_DITCH(void);
extern int PAIR_IsStatus_BOY_PULL(void);
extern void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7);
extern unsigned long long _ACTCharStatus_Check(char *a0, int bit);
extern void _ACTCharStatus_Init(int **a0);
extern void _ACTCharStatus_Set(char *a0, int bit, float f, int val);
extern float _ACTGame_GetParamF(int idx);
extern int _ACTGame_SearchGObj(char *self, char *tgt, float range, float height, int angle, float *out);
extern int _ACTLookTarget_Set(char *a0, int a1, float *a2, int a3, int a4);
extern void _ACTParaStatus_Set(char *a0, int bit);
extern void _ACTSetEnemyDisappearSpeed(char *a0, float f);

#endif /* ACT_GAME_H */
