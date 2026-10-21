/*
 * ico2/fumi/include/act-game.h
 *
 * The declarations of what act-game.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_GAME_H
#define ACT_GAME_H

#include "typedef.h" /* WayRequest, which ActWork carries */
#include "clipCollisionManager.h"

struct GObj;

/* The actor's character work, the record at Act+0x658 (held there as a
 * word, like the object's own actor slot): the boy's, the girl's and the
 * enemies' per-character state.  This build's: no boy distance, locked
 * rotation, floor object or September's frame timers (ACTGame_BeforeFunc
 * counts only downTimer down); the fields after pinchFrames keep PAL's order
 * and are not measured. */
typedef struct ActWork { /* field names derived */
    int paraTbl[86];        /* 0x000, each parallel slot's motion (ActPara_MakeTbl) */
    char pad158[456];
    float defIkRate0;       /* 0x320 */
    float defIkRate1;       /* 0x324 */
    float defIkRate2;       /* 0x328 */
    float escortOffset;     /* 0x32C (ACTGame_StageChangeGObj, IsGirlStatusEscortEnable) */
    float disappearSpeed;   /* 0x330 (_ACTSetEnemyDisappearSpeed, actCommonDie) */
    float fallDamageHeight; /* 0x334, place not measured */
    char pad338[4];
    float stickMag;   /* 0x33C (subGirlBrain_Idle) */
    float padWish[4]; /* 0x340, the pad wish direction a jump turns to (ACTGetWish_FromPad,
                         funcCommonJumpDircorrect) */
    float fallDir[4]; /* 0x350, the direction a fall turns to (funcCommonFallDircorrect) */
    char *hideObj;    /* 0x360 */
    void *bga;        /* 0x364 */
    int downTimer;    /* 0x368, counted down each frame (ACTGame_BeforeFunc, actAfterDown) */
    MotOriTarget bellowWall400;  /* 0x36C, the wall of attribute 0x400 actCommonLadderBellow
                                    found below, which mail 144 turns to */
    MotOriTarget bellowWall3000; /* 0x378, the same for attribute 0x3000 and mail 145 */
    struct GObj *dangerObj;      /* 0x384, the object SetGirlDangerGObj marks for the girl */
    char pad388[8];
    float hideDirX; /* 0x390 (girlBrainHide_GoalTurn) */
    float hideDirY; /* 0x394 */
    float hideDirZ; /* 0x398 */
    char pad39C[20];
    float velX; /* 0x3B0 (ACTGame_InnerVelocityUpdate) */
    float velY; /* 0x3B4 */
    float velZ; /* 0x3B8 */
    char pad3BC[4];
    float speed;    /* 0x3C0 */
    int slowFrames; /* 0x3C4 */
    int stopFrames; /* 0x3C8 */
    char pad3CC[4];
    GObj *genTarget;         /* 0x3D0, the generator the enemy heads for */
    int motherLabel;         /* 0x3D4 */
    struct GObj *motherGObj; /* 0x3D8, the generator object motherLabel names */
    char pad3DC[4];
    float hangOrient[3]; /* 0x3E0, the cliff orientation actBoyHangBefore keeps */
    char pad3EC[4];
    MotOriTarget cliffReq; /* 0x3F0, the target actBoyHangBefore keeps: the
                              actor's motion request's b */
    char pad3FC[4];
    float pinchPosX; /* 0x400 */
    float pinchPosY; /* 0x404 */
    float pinchPosZ; /* 0x408 */
    char pad40C[4];
    int pinchFrames; /* 0x410 */
    char pad414[12];
    float handrailOrient[4]; /* 0x420, the wall orientation actCommonHandrail keeps */
    int basePosSet;          /* 0x430 */
    char pad434[12];
    float basePos[4]; /* 0x440, the position the enemy guards when basePosSet */
    unsigned char
        boxSideSet; /* 0x450, set when the cliff edge is at a box side (ACTGetEnvironment) */
    char pad451[15];
    float boxSidePos[4]; /* 0x460, where the actor stands at that box side */
    float boyOrient[4];  /* 0x470, the girl's direction to the boy (ACTGetEnvironment) */
    float hintPosX;      /* 0x480 */
    float hintPosY;      /* 0x484 */
    float hintPosZ;      /* 0x488 */
    int carryGirlFrames; /* 0x48C, commonact.c's IsFlyTimeOver counts it (no reader in this
                            build's code) */
    float boxDir[4]; /* 0x490, the direction a box is pushed and pulled in (actCommonBox) */
    char pad4A0[64];
    WayRequest wayReq; /* 0x4E0, the way search RequestWayBegin hands to the way system manager */
    char pad598[232];
    float emgPosX; /* 0x680 */
    float emgPosY; /* 0x684 */
    float emgPosZ; /* 0x688 */
    char pad68C[4];
    MotOriReq intrReq; /* 0x690, the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
} ActWork;             /* derived name */

#define GOBJ_WORK(o) ((ActWork *)GOBJ_ACT(o)->work) /* derived name */

/* act-game.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
void WithMailFunc_AttackReject(struct GObj *self);
void ACTGameCollisionOn(volatile int *self);
void ACTGameCollisionOff(volatile int *self);
int ACTGame_CheckItemMotion(struct GObj *self);
int ACTGame_CheckHandMotion(struct GObj *boy, struct GObj *girl);
void ACTGame_StageChangeGObjID(int no, int kind, int idx);
void ACTGame_StageChangeGObjDirect(struct GObj *self, int stage, void *dir, int deg);
int ACTGame_FLAG_LIFEPINCH(struct GObj *self);
unsigned char ACTGame_FLAG_TETSUNAGI(void);
int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
inline void GetSkeltonPosition(float *dst, struct GObj *obj, int node);

void SetDirectRootPositionWithNodePointLimit(void *self, int node, void *pos, float t, float limit);

void ACTGameView_Init(void);
void ACTCharctrl_Lock(struct GObj *self);
void ACTCharctrl_Unlock(struct GObj *self);
void ACTGame_ConnectHand(void);
inline void ACTGame_DisconnectHand(void);
void PAIR_GetPosition_BOY(float *pos, float *dir);
int PAIR_IsStatus_BOY_PULL(void);
int PAIR_IsStatus_GIRL_PULL(void);
int PAIR_IsStatus_BOY_WAIT(void);
void PAIR_GetPosition_BOY_DITCH(float *pos, float *dir);
int PAIR_IsStatus_BOY_DITCH(void);
struct GObj *ACTGame_isHangChain(struct GObj *self);
int ACTGame_isWeaponEnableCatchfire(struct GObj *self);
int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout);

int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, int *flagout);

int ACTCheckCollis_CI(float *start, float *end, int *attr, WallCfg *wallHit);
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, float f, void *posout);
unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckViewCl(struct GObj *self, void *target, void *targetPos, int range, float f);
void ACTGameView_FirstSet(char *self);
void ACTGameView_Add(struct GObj *self, struct GObj *target);
int ACTGameView_Check(struct GObj *self, struct GObj *obj);
int ACTGameViewSimple_Check(struct GObj *self, struct GObj *obj);
int ACTGame_GetMotOrientFromWeapon(struct GObj *weapon);
unsigned char ACTGame_NoWeapon(struct GObj *self);
inline int ACTGame_isWeaponCombustible(void);
struct GObj *ACTGame_GetNearestGObj(float *pos, int kind);
void ACTLookTarget_Init(struct GObj *self);
int _ACTLookTarget_Set(struct GObj *self, struct GObj *target, float *pos, int pri, int mode);
void ACTParaStatus_Init(struct GObj *self);
inline void _ACTParaStatus_Set(struct GObj *self, int bit);
unsigned long long _ACTParaStatus_Check(struct GObj *self, int bit);
void _ACTCharStatus_Init(int **self);
void _ACTCharStatus_Clear(void *self);
void _ACTCharStatus_Set(struct GObj *self, int bit, float f, int val);
unsigned char _ACTCharStatus_Check(struct GObj *self, int bit);
void _ACTCharStatus_Exec(void);
void _ACTSetEnemyDisappearSpeed(struct GObj *self, float f);
void ACTGame_SetMotionPlaySpeedRatio_Reserve(struct GObj *self, float f, unsigned int pri);
float _ACTGame_GetParamF(int idx);
int ACTGame_GetCurrentCallStatus(struct GObj *self);
unsigned char ACTGame_CheckPriInputFrame(struct GObj *self);
void ACTGame_SendSoundMail(struct GObj *self, int mail, struct GObj *from, int mot, int waitSkip);
void ACTGame_LwsEffectInit(struct GObj *self);
void ACTGame_LwsEffect_Guard(struct GObj *self);
inline void ActGame_GetOrientQ(void *q, void *v, int deg);
void _GetRootObjectOrient(void *orient, struct GObj *obj);
void ACTItemForceDrop(struct GObj *self);
void GetOtherStageGirlOrient(float *orient);
int ACTChkAttackIgnore_BOY(struct GObj *self, struct GObj *actor);
int ACTChkAttackIgnore_GIRL(struct GObj *self, struct GObj *actor);
int ACTChkAttackIgnore_ENEMY(struct GObj *self, struct GObj *actor);
unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor);
int ACTCheckViewClDetail(struct GObj *self, void *target, void *targetPos, int range, float f);
void ACTGame_SetMotionPlaySpeedRatio_Clear(struct GObj *self);
void ACTGame_SetMotionPlaySpeedRatio_Exec(struct GObj *self);
int ACTCheckView(struct GObj *self, void *target, void *targetPos, int range, float f);
void ACTGame_BeforeFunc(struct GObj *self);
void ACTGame_InsertCamera_GirlIsPinch(void);
void ACTParaStatus_Clear(struct GObj *self);
void ACTGame_SaveActorInformation(struct GObj *self);
void ACTGame_DeleteActorInformation(struct GObj *self);
/* The second parameter is an unsigned char. */
void ACTGame_SetActors_Debug(int stage, unsigned char flag);
void ACTGame_StageChangeGObj(struct GObj *self, int idx);
void GetSkeltonOrient(float *out, void *obj, int node);
void RequestChangeHandMode(GObj *self, int mode, int pri, int flag, GObj *p5, int p6, float *p7);

int _ACTGame_SearchGObj(struct GObj *self, struct GObj *tgt, float range, float height, int angle,
                        float *out);

/* act-game.o's last two .sdata globals: the floor and wall records
 * ACTCheckCollis_WELL and ACTCheckCollis_WAY publish. */
extern void *floorGObj_ACTCheckCollis_WELL;
extern void *wallGObj_ACTCheckCollis_WAY;

/* a 64-bit status word, read whole or as two words */
typedef union { /* field names derived */
    unsigned long long q;
    unsigned int w[2];
} ActStatusWord; /* derived name */

void ACTGameView_Loop(struct GObj *self);

/* look-target-data: the look target kinds of one entry, 0x0C bytes, 27
 * rows, one column per character kind (Act+0x48). Reader:
 * ico2/fumi/src/act-game.c. Owner: ico2/fumi/include/act-game.h. */
typedef struct { /* field names derived */
    int kind[3]; /* 0x00, one per column */
} LookTarget;    /* derived name */

extern const LookTarget lookTargetData[];
void ACTGame_CommonLoop(struct GObj *self);
void ACTParaStatus_Exec(struct GObj *self);
void ACTLookTargetSystem_Exec(struct GObj *self);
extern float gameParam[]; /* game-param: the tuning values _ACTGame_GetParamF returns */

#endif /* ACT_GAME_H */
