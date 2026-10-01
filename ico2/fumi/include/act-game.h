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

/* The actor's character work, the record at Act+0x688 (held there as a
 * word, like the object's own actor slot): the boy's, the girl's and the
 * enemies' per-character state.  Rung: ROM bytes for every offset; the
 * field names are this repository's. */
typedef struct ActWork { /* derived name */
    char _pad0[0x320];
    float f_320; /* 0x320 */
    float f_324; /* 0x324 */
    float f_328; /* 0x328 */
    float f_32C; /* 0x32C */
    float f_330; /* 0x330 */
    float f_334; /* 0x334 */
    float f_338; /* 0x338 */
    char _pad33C[0x4];
    float f_340; /* 0x340 */
    float f_344; /* 0x344 */
    float f_348; /* 0x348 */
    char _pad34C[0x4];
    float f_350; /* 0x350 */
    float f_354; /* 0x354 */
    float f_358; /* 0x358 */
    char _pad35C[0x14];
    char *f_370; /* 0x370 */
    void *f_374; /* 0x374 */
    void *f_378; /* 0x378 */
    int f_37C;   /* 0x37C */
    int f_380;   /* 0x380 */
    int f_384;   /* 0x384 */
    int f_388;   /* 0x388 */
    int f_38C;   /* 0x38C */
    int f_390;   /* 0x390 */
    int f_394;   /* 0x394 */
    int f_398;   /* 0x398 */
    int f_39C;   /* 0x39C */
    int f_3A0;   /* 0x3A0 */
    int f_3A4;   /* 0x3A4 */
    int f_3A8;   /* 0x3A8 */
    int f_3AC;   /* 0x3AC */
    int f_3B0;   /* 0x3B0 */
    int f_3B4;   /* 0x3B4 */
    int f_3B8;   /* 0x3B8 */
    int f_3BC;   /* 0x3BC */
    int f_3C0;   /* 0x3C0 */
    int f_3C4;   /* 0x3C4 */
    int f_3C8;   /* 0x3C8 */
    char _pad3CC[0x18];
    int f_3E4; /* 0x3E4 */
    char _pad3E8[0x8];
    float f_3F0; /* 0x3F0 */
    float f_3F4; /* 0x3F4 */
    float f_3F8; /* 0x3F8 */
    char _pad3FC[0x4];
    void *f_400; /* 0x400 */
    char _pad404[0x10];
    float f_414; /* 0x414 */
    char _pad418[0x18];
    float f_430; /* 0x430 */
    float f_434; /* 0x434 */
    float f_438; /* 0x438 */
    char _pad43C[0x4];
    float f_440; /* 0x440 */
    int f_444;   /* 0x444 */
    int f_448;   /* 0x448 */
    char _pad44C[0x4];
    int f_450;          /* 0x450 */
    unsigned int f_454; /* 0x454 */
    char _pad458[0x8];
    char *f_460; /* 0x460 */
    int f_464;   /* 0x464 */
    int f_468;   /* 0x468 */
    char _pad46C[0x34];
    float f_4A0; /* 0x4A0 */
    float f_4A4; /* 0x4A4 */
    float f_4A8; /* 0x4A8 */
    char _pad4AC[0x4];
    int f_4B0; /* 0x4B0 */
    char _pad4B4[0x1C];
    int f_4D0; /* 0x4D0 */
    char _pad4D4[0xC];
    float f_4E0; /* 0x4E0 */
    float f_4E4; /* 0x4E4 */
    float f_4E8; /* 0x4E8 */
    char _pad4EC[0x34];
    float f_520; /* 0x520 */
    float f_524; /* 0x524 */
    float f_528; /* 0x528 */
    char _pad52C[0x1F4];
    int f_720; /* 0x720 */
    char _pad724[0x7C];
    void *f_7A0; /* 0x7A0 */
    char _pad7A4[0x14];
    int f_7B8; /* 0x7B8 */
    char _pad7BC[0x8];
    int f_7C4; /* 0x7C4 */
    char _pad7C8[0x28];
    char *f_7F0; /* 0x7F0 */
    char _pad7F4[0xC];
    int f_800; /* 0x800 */
    char _pad804[0x9C];
    float f_8A0; /* 0x8A0 */
    float f_8A4; /* 0x8A4 */
    float f_8A8; /* 0x8A8 */
    char _pad8AC[0x1C];
    void *f_8C8; /* 0x8C8 */
    char _pad8CC[0x4];
} ActWork;

#define GOBJ_WORK(o) ((ActWork *)GOBJ_ACT(o)->f_688) /* derived name */

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
void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0,
                                             float farg1);
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
int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget,
                     int *flagout);
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
