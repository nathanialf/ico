/*
 * ico2/fumi/include/act-game.h
 *
 * The declarations of what act-game.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_GAME_H
#define ACT_GAME_H

#ifdef VERSION_JUN26
#include "typedef.h" /* WayRequest, which ActWork carries */
#else
#include "typedef.h" /* WayRequest, which ActWork carries at 0x580 (JPN and KOR 0x570) */
#include "clipCollisionManager.h"
#endif

struct GObj;

/* The actor's character work, the record at Act+0x688 (held there as a
 * word, like the object's own actor slot): the boy's, the girl's and the
 * enemies' per-character state. */
typedef struct ActWork { /* field names derived */
    int paraTbl[86];     /* 0x000, each parallel slot's motion (ActPara_MakeTbl) */
    char pad158[456];
    float defIkRate0; /* 0x320 */
    float defIkRate1; /* 0x324 */
    float defIkRate2; /* 0x328 */
#ifdef VERSION_JUN26
    float escortOffset;     /* 0x32C (ACTGame_StageChangeGObj, IsGirlStatusEscortEnable) */
    float disappearSpeed;   /* 0x330 (_ACTSetEnemyDisappearSpeed, actCommonDie) */
    float fallDamageHeight; /* 0x334, no reader in this build */
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
    float boxDir[4];     /* 0x490, the direction a box is pushed and pulled in (actCommonBox) */
    char pad4A0[64];
    WayRequest wayReq; /* 0x4E0, PAL's way search slot (RequestWayBegin); the demo has no way
                          system manager and nothing here reads it */
    char pad598[232];
    float emgPosX; /* 0x680 */
    float emgPosY; /* 0x684 */
    float emgPosZ; /* 0x688 */
    char pad68C[4];
    MotOriReq intrReq; /* 0x690, the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
#else
    float boyDist;        /* 0x32C */
    float escortOffset;   /* 0x330 */
    float disappearSpeed; /* 0x334 */
#ifdef VERSION_AUG6
    float stickMag;        /* 0x338 (subBoyControl 0x14D6D0 swc1 $f0,824(v0)) */
    float lockedMaxRotate; /* 0x33C, not pinned: Aug 20's field after stickMag (scpLockMaxRotate) */
    float padWish[4]; /* 0x340, the pad wish direction a jump turns to (funcCommonJumpDircorrect
                         0x157654 addiu a1,a1,832; June 26's place, PAL's is 0x350) */
    float fallDir[4]; /* 0x350, the direction a fall turns to (funcCommonFallDircorrect 0x157664) */
    char *hideObj;    /* 0x360 */
    void *bga;        /* 0x364 */
    int downTimer;    /* 0x368 (actAfterDown 0x15D508 sw v1,872(a0)) */
    int brainTimer;   /* 0x36C, not pinned */
    int turnTimer;    /* 0x370 (_ACTCorrectMsg 0x153888 lw a0,880(v1)) */
    int turnTimer2;   /* 0x374 (_ACTCorrectMsg 0x1538A8 lw a0,884(v1)) */
    int noInterpTimer; /* 0x378 (subCommonIdle 0x15AB1C lw v0,888(a0)) */
    int wishHoldTimer; /* 0x37C (ACTGame_BeforeFunc 0x144868 lw v0,892(v1)) */
    int leverTimer; /* 0x380, frames the boy keeps hold of a lever (actCommonLever 0x156104 sw v0,896(a1)) */
    int nakaBossCount; /* 0x384 (NakaBoss 0x160E28 lw v0,900(v1)) */
    int carryGirlFrames; /* 0x388, the fly's frame count IsFlyTimeOver tests (emergencyCheck 0x15890C lw v1,904(a0)) */
    MotOriTarget bellowWall400;  /* 0x38C, the wall of attribute 0x400 actCommonLadderBellow
                                    found below, which mail 132 turns to
                                    (ACTGetOrientFromIntrK 0x1543F8 lw t2,916(v1)) */
    MotOriTarget bellowWall3000; /* 0x398, the same for attribute 0x3000 and mail 133 */
    struct GObj *dangerObj; /* 0x3A4, the object SetGirlDangerGObj marks for the girl (0x17383C) */
    char pad3A8[8];
    float hideDirX; /* 0x3B0 (girlBrainHide_GoalTurn 0x16C840 swc1 $f1,944(v0)) */
    float hideDirY; /* 0x3B4 */
    float hideDirZ; /* 0x3B8 */
    char pad3BC[20];
    float velX; /* 0x3D0 (ACTGame_InnerVelocityUpdate 0x1444AC lwc1 $f0,976(v1)) */
    float velY; /* 0x3D4 */
    float velZ; /* 0x3D8 */
    char pad3DC[4];
    float speed;    /* 0x3E0 */
    int slowFrames; /* 0x3E4 */
    int stopFrames; /* 0x3E8 */
    char pad3EC[4];
    int noMoveFrames;        /* 0x3F0 (ACTGame_InnerVelocityUpdate 0x144650 lw v0,1008(v1)) */
    unsigned int enemyFlags; /* 0x3F4 (subEnemyBrainMain 0x160078 lwu v0,1012(a0)) */
    char pad3F8[8];
    GObj *genTarget;         /* 0x400, the generator the enemy heads for */
    int motherLabel;         /* 0x404 */
    struct GObj *motherGObj; /* 0x408, the generator object motherLabel names */
    char pad40C[4];
    float hangOrient[3]; /* 0x410, the cliff orientation actBoyHangBefore keeps (0x152140) */
    char pad41C[4];
    MotOriTarget cliffReq; /* 0x420, the target mail 285 turns to (ACTGetOrientFromIntrK
                              0x154290 ldl a0,1063(v1)); a MotOriTarget as June 26's */
    char pad42C[4];
    float pinchPosX; /* 0x430 (SetStatusBoy_OtherStageGirlPinch 0x1518FC swc1 $f0,1072(v0)) */
    float pinchPosY; /* 0x434 */
    float pinchPosZ; /* 0x438 */
    char pad43C[4];
    int pinchFrames; /* 0x440 (SetStatusBoy_OtherStageGirlPinch 0x1518F8 sw s0,1088(v0)) */
    char pad444[76];
    WayRequest wayReq; /* 0x490 (ACTWayMove_BeginDetail 0x1FE7F8 addiu s0,s1,1168), the way
                          search RequestWayBegin hands to the way system manager */
    char pad548[232];
    ClipColReq view; /* 0x630 (ACTGameView_Loop 0x143C6C lw v0,1584(v1)), the clip
                        ACTGameView_Loop runs to the object it looks at */
    int viewState;   /* 0x710 (ACTGameView_Loop 0x143C00 sw a0,1808(v1)) */
    char pad714[156];
    float emgPosX; /* 0x7B0, June 26's place before intrReq; not pinned */
    float emgPosY; /* 0x7B4 */
    float emgPosZ; /* 0x7B8 */
    char pad7BC[4];
    MotOriReq
        intrReq; /* 0x7C0 (actCommonBar 0x157428 addiu a2,a2,1984), the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
#else
    float fallDamageHeight; /* 0x338 */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    float stickMag;        /* 0x33C */
    float lockedMaxRotate; /* 0x340 */
    char pad344[12];
#else
    float ropeClimbHeight; /* 0x33C, the chain top over the actor, sent with mail 316 */
    float stickMag;        /* 0x340 */
    float lockedMaxRotate; /* 0x344 */
    float parallelInterp;  /* 0x348 */
    char pad34C[4];
#endif
    float padWish[4]; /* 0x350, the pad wish direction a jump turns to (funcCommonJumpDircorrect) */
    float fallDir[4]; /* 0x360, the direction a fall turns to (funcCommonFallDircorrect) */
    char *hideObj;    /* 0x370 */
    void *floorObj;   /* 0x374 */
    void *bga;        /* 0x378 */
    int downTimer;    /* 0x37C */
    int brainTimer;   /* 0x380 */
    int turnTimer;    /* 0x384 */
    int turnTimer2;   /* 0x388 */
    int noInterpTimer;   /* 0x38C */
    int wishHoldTimer;   /* 0x390 */
    int leverTimer;      /* 0x394, frames the boy keeps hold of a lever (actCommonLever) */
    int nakaBossCount;   /* 0x398 */
    int carryGirlFrames; /* 0x39C */
    int sofaTimer;       /* 0x3A0, frames since the actor sat on the sofa (actCommonSofa) */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    int orientFrames;            /* 0x3A4 */
    MotOriTarget bellowWall400;  /* 0x3A8, the wall of attribute 0x400 actCommonLadderBellow
                                    found below, which mail 144 turns to */
    MotOriTarget bellowWall3000; /* 0x3B4, the same for attribute 0x3000 and mail 145 */
    struct GObj *dangerObj;      /* 0x3C0, the object SetGirlDangerGObj marks for the girl */
    char pad3C4[12];
    float hideDirX; /* 0x3D0 */
    float hideDirY; /* 0x3D4 */
    float hideDirZ; /* 0x3D8 */
    char pad3DC[20];
    float velX; /* 0x3F0 */
    float velY; /* 0x3F4 */
    float velZ; /* 0x3F8 */
    char pad3FC[4];
    float speed;    /* 0x400 */
    int slowFrames; /* 0x404 */
    int stopFrames; /* 0x408 */
    char pad40C[4];
    int noMoveFrames;        /* 0x410 */
    unsigned int enemyFlags; /* 0x414 */
    char pad418[8];
    GObj *genTarget;         /* 0x420, the generator the enemy heads for */
    int motherLabel;         /* 0x424 */
    struct GObj *motherGObj; /* 0x428, the generator object motherLabel names */
    char pad42C[4];
    float hangOrient[3]; /* 0x430, the cliff orientation actBoyHangBefore keeps */
    char pad43C[4];
    MotOriTarget cliffReq; /* 0x440, the target actBoyHangBefore keeps: the
                              actor's motion request's b */
    char pad44C[4];
    float pinchPosX; /* 0x450 */
    float pinchPosY; /* 0x454 */
    float pinchPosZ; /* 0x458 */
    char pad45C[4];
    int pinchFrames; /* 0x460 */
    char pad464[76];
    WayRequest wayReq; /* 0x4B0, the way search RequestWayBegin hands to the way system manager */
    char pad568[232];
    ClipColReq view; /* 0x650, the clip ACTGameView_Loop runs to the object it looks at */
    int viewState;   /* 0x730 */
    char pad734[156];
    float emgPosX; /* 0x7D0 */
    float emgPosY; /* 0x7D4 */
    float emgPosZ; /* 0x7D8 */
    char pad7DC[4];
    MotOriReq intrReq; /* 0x7E0, the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
#else
    int sofaRestTimer;           /* 0x3A4, the longer sofa rest the girl's attract waits out */
    int orientFrames;            /* 0x3A8 */
    int timer3AC;                /* 0x3AC */
    int turnMailWait;            /* 0x3B0, the girl holds back girlAttractTurnMailR while it runs */
    int jumpTimer;               /* 0x3B4 */
    int footIkFrames;            /* 0x3B8 */
    int bit37Frames;             /* 0x3BC */
    int bit38Frames;             /* 0x3C0 */
    int mailB1Timer;             /* 0x3C4 */
    int ditchTimer;              /* 0x3C8 */
    MotOriTarget bellowWall400;  /* 0x3CC, the wall of attribute 0x400 actCommonLadderBellow
                                    found below, which mail 144 turns to */
    MotOriTarget bellowWall3000; /* 0x3D8, the same for attribute 0x3000 and mail 145 */
    struct GObj *dangerObj;      /* 0x3E4, the object SetGirlDangerGObj marks for the girl */
    char pad3E8[8];
    float hideDirX; /* 0x3F0 */
    float hideDirY; /* 0x3F4 */
    float hideDirZ; /* 0x3F8 */
    char pad3FC[4];
    void *ropeCage; /* 0x400 */
    char pad404[16];
    float handPosY; /* 0x414 */
    char pad418[24];
    float velX; /* 0x430 */
    float velY; /* 0x434 */
    float velZ; /* 0x438 */
    char pad43C[4];
    float speed;    /* 0x440 */
    int slowFrames; /* 0x444 */
    int stopFrames; /* 0x448 */
    char pad44C[4];
    int noMoveFrames;        /* 0x450 */
    unsigned int enemyFlags; /* 0x454 */
    char pad458[8];
    GObj *genTarget;         /* 0x460, the generator the enemy heads for */
    int motherLabel;         /* 0x464 */
    struct GObj *motherGObj; /* 0x468, the generator object motherLabel names */
    char pad46C[4];
    float hangOrient[3]; /* 0x470, the cliff orientation actBoyHangBefore keeps */
    char pad47C[4];
    MotOriReq cliffReq; /* 0x480, the request mails 140 and 305 turn to: b the
                           wall under the cliff edge (actBoyCliffHesitate),
                           a the actor's motion request's b (actBoyHangBefore) */
    float pinchPosX;    /* 0x4A0 */
    float pinchPosY;    /* 0x4A4 */
    float pinchPosZ;    /* 0x4A8 */
    char pad4AC[4];
    int pinchFrames; /* 0x4B0 */
    char pad4B4[12];
    float handrailOrient[4]; /* 0x4C0, the wall orientation actCommonHandrail keeps */
    int basePosSet;          /* 0x4D0 */
    char pad4D4[12];
    float basePos[4]; /* 0x4E0, the position the enemy guards when basePosSet */
    unsigned char
        boxSideSet; /* 0x4F0, set when the cliff edge is at a box side (ACTGetEnvironment) */
    char pad4F1[15];
    float boxSidePos[4]; /* 0x500, where the actor stands at that box side */
    float boyOrient[4];  /* 0x510, the girl's direction to the boy (ACTGetEnvironment) */
    float hintPosX;      /* 0x520 */
    float hintPosY;      /* 0x524 */
    float hintPosZ;      /* 0x528 */
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    char pad52C[68];
    WayRequest wayReq; /* 0x570, the way search RequestWayBegin hands to the way system manager */
    char pad628[232];
    ClipColReq view; /* 0x710, the clip ACTGameView_Loop runs to the object it looks at */
    int viewState;   /* 0x7F0 */
    char pad7F4[156];
    float emgPosX; /* 0x890 */
    float emgPosY; /* 0x894 */
    float emgPosZ; /* 0x898 */
    char pad89C[4];
    MotOriReq intrReq; /* 0x8A0, the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
#else
    char pad52C[4];
    float boxDir[4]; /* 0x530, the direction a box is pushed and pulled in (actCommonBox) */
    char pad540[64];
    WayRequest wayReq; /* 0x580, the way search RequestWayBegin hands to the way system manager */
    char pad638[232];
    ClipColReq view; /* 0x720, the clip ACTGameView_Loop runs to the object it looks at */
    int viewState;   /* 0x800 */
    char pad804[156];
    float emgPosX; /* 0x8A0 */
    float emgPosY; /* 0x8A4 */
    float emgPosZ; /* 0x8A8 */
    char pad8AC[4];
    MotOriReq intrReq; /* 0x8B0, the orient request of the interrupt motion
                          act_check_intr_list started; the hang and climb acts
                          lay the root against its walls, b's element the wall
                          under the cliff edge */
#endif
#endif
#endif
#endif
} ActWork; /* derived name */

#define GOBJ_WORK(o) ((ActWork *)GOBJ_ACT(o)->work) /* derived name */

/* act-game.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
#ifdef VERSION_JUN26
void WithMailFunc_AttackReject(struct GObj *self);
#else
int ACTNotNeedCameraOffset(struct GObj *self);
#endif

void ACTGameCollisionOn(volatile int *self);
void ACTGameCollisionOff(volatile int *self);
int ACTGame_CheckItemMotion(struct GObj *self);
int ACTGame_CheckHandMotion(struct GObj *boy, struct GObj *girl);
void ACTGame_StageChangeGObjID(int no, int kind, int idx);
void ACTGame_StageChangeGObjDirect(struct GObj *self, int stage, void *dir, int deg);
int ACTGame_FLAG_LIFEPINCH(struct GObj *self);
unsigned char ACTGame_FLAG_TETSUNAGI(void);

#ifdef VERSION_JUN26
inline void GetSkeltonPosition(float *dst, struct GObj *obj, int node);
void SetDirectRootPositionWithNodePointLimit(void *self, int node, void *pos, float t, float limit);
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
#endif

inline void GetSkeltonPosition(float *dst, struct GObj *obj, int node);
void SetDirectRootPositionWithNodePointLimit(void *self, int node, void *pos, float t, float limit);
#endif

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

#ifdef VERSION_JUN26
int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, int *flagout);
int ACTCheckCollis_CI(float *start, float *end, int *attr, WallCfg *wallHit);
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, float f, void *posout);
#else
int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget,
                     int *flagout);

int ACTCheckCollis_CI(float *start, float *end, int *attr, WallCfg *wallHit);

#ifdef VERSION_AUG6
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, float f, void *posout);
#else
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f);
#endif
#endif

unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckViewCl(struct GObj *self, void *target, void *targetPos, int range, float f);
void ACTGameView_FirstSet(char *self);
void ACTGameView_Add(struct GObj *self, struct GObj *target);
int ACTGameView_Check(struct GObj *self, struct GObj *obj);

#ifndef VERSION_JUN26
int ACTGameViewSimple_Check(struct GObj *self, struct GObj *obj);
#endif

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

#ifdef VERSION_JUN26
void _ACTCharStatus_Clear(void *self);
#endif

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

#ifdef VERSION_JUN26
void GetOtherStageGirlOrient(float *orient);
unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor);
void ACTGame_SetMotionPlaySpeedRatio_Clear(struct GObj *self);
void ACTGame_SetMotionPlaySpeedRatio_Exec(struct GObj *self);
#else
#ifdef VERSION_AUG6
/* June 26's one-argument form, a plain function at 0x147780 (MAIN.MAP's GetOtherStageGirlOrient,
   0x448 before ACTLookTargetSystem_Exec; OtherStageGirlPinchCamera_After 0x14EAEC passes a0 only) */
void GetOtherStageGirlOrient(float *orient);
int ACTChkAttackIgnore_BOY(struct GObj *self); /* boyact.c (0x152A38 reads a0 only) */
#else
inline void GetOtherStageGirlOrient(float *orient, float *root);

#ifdef VERSION_NTSC
int ACTChkAttackIgnore_BOY(struct GObj *self);
int ACTChkAttackIgnore_GIRL(struct GObj *self);
int ACTChkAttackIgnore_ENEMY(struct GObj *self);
#else
int ACTChkAttackIgnore_BOY(struct GObj *self, struct GObj *actor);
int ACTChkAttackIgnore_GIRL(struct GObj *self, struct GObj *actor);
int ACTChkAttackIgnore_ENEMY(struct GObj *self, struct GObj *actor);
#endif
#endif

unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor);
int ACTCheckViewClDetail(struct GObj *self, void *target, void *targetPos, int range, float f);
void ACTGame_SetMotionPlaySpeedRatio_Clear(struct GObj *self);
void ACTGame_SetMotionPlaySpeedRatio_Exec(struct GObj *self);
void GetGirlPositionAtThisStage(float *pos);
#endif

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
