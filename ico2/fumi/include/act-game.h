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

/* act-game.c defines these `inline`, so the compiler emits them after the
 * rest of the file in the order they are first declared: this list is the
 * ROM's order of the TU's closing run, from ACTNotNeedCameraOffset to
 * GetGirlPositionAtThisStage. */
int ACTNotNeedCameraOffset(char *a0);
void ACTGameCollisionOn(volatile int *self);
void ACTGameCollisionOff(volatile int *self);
int ACTGame_CheckItemMotion(char *a0);
int ACTGame_CheckHandMotion(char *a0, char *a1);
void ACTGame_StageChangeGObjID(char *self, char *other, int idx);
void ACTGame_StageChangeGObjDirect(int *a0, int a1, void *a2, int a3);
int ACTGame_FLAG_LIFEPINCH(char *a0);
unsigned char ACTGame_FLAG_TETSUNAGI(void);
int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
void GetSkeltonPosition(float *dst, char *obj, void *a2);
void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0, float farg1);
void ACTGameView_Init(void);
void ACTCharctrl_Lock(char *a0);
void ACTCharctrl_Unlock(char *a0);
void ACTGame_ConnectHand(void);
void ACTGame_DisconnectHand(void);
void PAIR_GetPosition_BOY(float *a0, float *a1);
int PAIR_IsStatus_BOY_PULL(void);
int PAIR_IsStatus_GIRL_PULL(void);
int PAIR_IsStatus_BOY_WAIT(void);
void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1);
int PAIR_IsStatus_BOY_DITCH(void);
int ACTGame_isHangChain(char *a0);
int ACTGame_isWeaponEnableCatchfire(int *self);
int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget, int *flagout);
int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3);
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f);
unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckViewCl(char *self, void *a1, void *a2, int range, float f);
void ACTGameView_FirstSet(char *self);
void ACTGameView_Add(char *a0, char *a1);
int ACTGameView_Check(int a0, int a1);
int ACTGameViewSimple_Check(int a0, int a1);
int ACTGame_GetMotOrientFromWeapon(int a0);
unsigned char ACTGame_NoWeapon(char *a0);
int ACTGame_isWeaponCombustible(void);
int *ACTGame_GetNearestGObj(int a0, int a1);
void ACTLookTarget_Init(char *a0);
int _ACTLookTarget_Set(char *a0, int a1, float *a2, int a3, int a4);
void ACTParaStatus_Init(char *a0);
void _ACTParaStatus_Set(char *a0, int bit);
unsigned long long _ACTParaStatus_Check(char *a0, int bit);
void _ACTCharStatus_Init(int **a0);
void _ACTCharStatus_Set(char *a0, int bit, float f, int val);
unsigned char _ACTCharStatus_Check(char *a0, int bit);
void _ACTCharStatus_Exec(void);
void _ACTSetEnemyDisappearSpeed(char *a0, float f);
void ACTGame_SetMotionPlaySpeedRatio_Reserve(char *a0, float f, unsigned int a1);
float _ACTGame_GetParamF(int idx);
int ACTGame_GetCurrentCallStatus(char *a0);
unsigned char ACTGame_CheckPriInputFrame(char *a0);
void ACTGame_SendSoundMail(char *a0, int mail, int a2, int a3, int a4);
void ACTGame_LwsEffectInit(char *a0);
void ACTGame_LwsEffect_Guard(char *a0);
void ActGame_GetOrientQ(void *q, void *v, int deg);
void _GetRootObjectOrient(void *a0, char *a1);
void ACTItemForceDrop(char *a0);
void GetOtherStageGirlOrient(float *a0, float *a1);
int ACTChkAttackIgnore_BOY(char *a0);
int ACTChkAttackIgnore_GIRL(char *a0, int *a1);
int ACTChkAttackIgnore_ENEMY(char *a0);
unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor);
int ACTCheckViewClDetail(char *self, void *a1, void *a2, int range, float f);
void ACTGame_SetMotionPlaySpeedRatio_Clear(char *a0);
void ACTGame_SetMotionPlaySpeedRatio_Exec(char *a0);
void GetGirlPositionAtThisStage(float *a0);

int ACTCheckView(char *self, void *a1, void *a2, int range, float f);
void ACTGame_BeforeFunc(char *self);
void ACTGame_InnerVelocityUpdate(char *self);
void ACTGame_InsertCamera_GirlIsPinch(void);
void ACTParaStatus_Clear(char *a0);
void ACTGame_SaveActorInformation(char *a0);
/* The second parameter is an unsigned char: the ROM masks it on entry with
 * `andi $16, $5, 0xFF` at 0x00146F8C. */
void ACTGame_SetActors_Debug(int stage, unsigned char flag);
void ACTGame_StageChangeGObj(char *self, int idx);
void FunctionAboutClingedStatus(char *self);
void GetSkeltonOrient(float *out, void *obj, int node);
void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7);
int _ACTGame_SearchGObj(char *self, char *tgt, float range, float height, int angle, float *out);

/* MAIN.MAP globals of act-game.o's .sdata, the last two words of its run:
 * the floor and wall records ACTCheckCollis_WELL and ACTCheckCollis_WAY
 * publish. */
extern void *floorGObj_ACTCheckCollis_WELL;
extern void *wallGObj_ACTCheckCollis_WAY;

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

void ACTGameView_Loop(char *self);

#endif /* ACT_GAME_H */
