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

void ACTCharctrl_Lock(char *a0);
int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3);
int ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckView(char *self, void *a1, void *a2, void *a3, float f);
int ACTCheckViewCl(char *self, void *a1, void *a2, void *a3, float f);
int ACTChkAttackIgnore_BOY(char *a0);
int ACTChkAttackIgnore_ENEMY(char *a0);
int ACTChkAttackIgnore_GIRL(char *a0, int *a1);
void ACTGameCollisionOff(volatile int *self);
void ACTGameCollisionOn(volatile int *self);
void ACTGameView_Add(char *a0, char *a1);
int ACTGameView_Check(int a0, int a1);
int ACTGameViewSimple_Check(int a0, int a1);
void ACTGameView_FirstSet(void);
void ACTGameView_Init(void);
void ACTGame_BeforeFunc(char *self);
int ACTGame_CheckHandMotion(char *a0, char *a1);
void ACTGame_ConnectHand(void);
void ACTGame_DisconnectHand(void);
unsigned char ACTGame_FLAG_TETSUNAGI(void);
int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
void ACTGame_InnerVelocityUpdate(char *self);
void ACTGame_InsertCamera_GirlIsPinch(void);
void ACTGame_LwsEffectInit(char *a0);
void ACTGame_LwsEffect_Guard(char *a0);
unsigned char ACTGame_NoWeapon(char *a0);
void ACTGame_SaveActorInformation(char *a0);
void ACTGame_SendSoundMail(char *a0, int mail, int a2, int a3, int a4);
/* The second parameter is an unsigned char: the ROM masks it on entry with
 * `andi $16, $5, 0xFF` at 0x00146F8C. */
void ACTGame_SetActors_Debug(int stage, unsigned char flag);
void ACTGame_SetMotionPlaySpeedRatio_Reserve(char *a0, float f, unsigned int a1);
void ACTGame_StageChangeGObj(char *self, int idx);
void ACTGame_StageChangeGObjDirect(int *a0, int a1, void *a2, int a3);
int ACTGame_isHangChain(char *a0);
int ACTGame_isWeaponCombustible(void);
int ACTGame_isWeaponEnableCatchfire(int *self);
void ACTItemForceDrop(char *a0);
void ACTLookTarget_Init(char *a0);
int ACTNotNeedCameraOffset(char *a0);
void ACTParaStatus_Init(char *a0);
void ActGame_GetOrientQ(void *q, void *v, int deg);
void FunctionAboutClingedStatus(char *self);
void GetOtherStageGirlOrient(float *a0, float *a1);
void GetSkeltonOrient(float *out, void *obj, int node);
void GetSkeltonPosition(float *dst, char *obj, void *a2);
void PAIR_GetPosition_BOY(float *a0, float *a1);
void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1);
int PAIR_IsStatus_BOY_DITCH(void);
int PAIR_IsStatus_BOY_PULL(void);
void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7);
unsigned long long _ACTCharStatus_Check(char *a0, int bit);
void _ACTCharStatus_Init(int **a0);
void _ACTCharStatus_Set(char *a0, int bit, float f, int val);
float _ACTGame_GetParamF(int idx);
int _ACTGame_SearchGObj(char *self, char *tgt, float range, float height, int angle, float *out);
int _ACTLookTarget_Set(char *a0, int a1, float *a2, int a3, int a4);
void _ACTParaStatus_Set(char *a0, int bit);
void _ACTSetEnemyDisappearSpeed(char *a0, float f);

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef union {
    unsigned long long q;
    unsigned int w[2];
} ActStatusWord;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    char _00[0x4C];
    unsigned int f_4C;
} StatusAttr;

#endif /* ACT_GAME_H */
