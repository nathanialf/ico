/*
 * ico2/fumi/include/act-game.h
 *
 * The declarations of what act-game.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ACT_GAME_H
#define ACT_GAME_H

struct GObj;

/* The actor's character work, the record at Act+0x688 (held there as a
 * word, like the object's own actor slot): the boy's, the girl's and the
 * enemies' per-character state. */
typedef struct ActWork { /* field names derived */
    char pad0[800];
    float defIkRate0;       /* 0x320 */
    float defIkRate1;       /* 0x324 */
    float defIkRate2;       /* 0x328 */
    float boyDist;          /* 0x32C */
    float escortOffset;     /* 0x330 */
    float disappearSpeed;   /* 0x334 */
    float fallDamageHeight; /* 0x338 */
    char pad33C[4];
    float stickMag;        /* 0x340 */
    float lockedMaxRotate; /* 0x344 */
    float parallelInterp;  /* 0x348 */
    char pad34C[4];
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
    int sofaRestTimer;   /* 0x3A4, the longer sofa rest the girl's attract waits out */
    int orientFrames;    /* 0x3A8 */
    int timer3AC;        /* 0x3AC */
    int timer3B0;        /* 0x3B0 */
    int jumpTimer;       /* 0x3B4 */
    int footIkFrames;    /* 0x3B8 */
    int bit37Frames;     /* 0x3BC */
    int bit38Frames;     /* 0x3C0 */
    int mailB1Timer;     /* 0x3C4 */
    int ditchTimer;      /* 0x3C8 */
    char pad3CC[24];
    int dangerObj; /* 0x3E4 */
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
    char *genTarget;         /* 0x460 */
    int motherLabel;         /* 0x464 */
    struct GObj *motherGObj; /* 0x468, the generator object motherLabel names */
    char pad46C[52];
    float pinchPosX; /* 0x4A0 */
    float pinchPosY; /* 0x4A4 */
    float pinchPosZ; /* 0x4A8 */
    char pad4AC[4];
    int pinchFrames; /* 0x4B0 */
    char pad4B4[12];
    float handrailOrient[4]; /* 0x4C0, the wall orientation actCommonHandrail keeps */
    int basePosSet;          /* 0x4D0 */
    char pad4D4[12];
    float basePos[4]; /* 0x4E0, the position the enemy guards when basePosSet */
    char pad4F0[32];
    float boyOrient[4]; /* 0x510, the girl's direction to the boy (ACTGetEnvironment) */
    float hintPosX;     /* 0x520 */
    float hintPosY;     /* 0x524 */
    float hintPosZ;     /* 0x528 */
    char pad52C[4];
    float boxDir[4]; /* 0x530, the direction a box is pushed and pulled in (actCommonBox) */
    char pad540[480];
    int viewResult; /* 0x720, the clip request ACTGameView_Loop runs (clipCollisionManager.c's ClipColWork): done */
    char pad724[124];
    float viewRadius; /* 0x7A0, the clip radius (ClipWork+0x70) */
    char pad7A4[20];
    int viewHitWall; /* 0x7B8, the wall the clip hit */
    char pad7BC[8];
    int viewHitFloor; /* 0x7C4, the floor the clip hit */
    char pad7C8[40];
    char *viewObj; /* 0x7F0 */
    char pad7F4[12];
    int viewState; /* 0x800 */
    char pad804[156];
    float emgPosX; /* 0x8A0 */
    float emgPosY; /* 0x8A4 */
    float emgPosZ; /* 0x8A8 */
    char pad8AC[28];
    void *cliffWall; /* 0x8C8 */
    char pad8CC[4];
} ActWork; /* derived name */

#define GOBJ_WORK(o) ((ActWork *)GOBJ_ACT(o)->work) /* derived name */

/* act-game.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int ACTNotNeedCameraOffset(struct GObj *a0);
void ACTGameCollisionOn(volatile int *self);
void ACTGameCollisionOff(volatile int *self);
int ACTGame_CheckItemMotion(struct GObj *a0);
int ACTGame_CheckHandMotion(char *a0, char *a1);
void ACTGame_StageChangeGObjID(int no, int kind, int idx);
void ACTGame_StageChangeGObjDirect(struct GObj *a0, int a1, void *a2, int a3);
int ACTGame_FLAG_LIFEPINCH(struct GObj *a0);
unsigned char ACTGame_FLAG_TETSUNAGI(void);
int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
inline void GetSkeltonPosition(float *dst, struct GObj *obj, int node);

void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0,
                                             float farg1);

void ACTGameView_Init(void);
void ACTCharctrl_Lock(struct GObj *a0);
void ACTCharctrl_Unlock(struct GObj *a0);
void ACTGame_ConnectHand(void);
inline void ACTGame_DisconnectHand(void);
void PAIR_GetPosition_BOY(float *a0, float *a1);
int PAIR_IsStatus_BOY_PULL(void);
int PAIR_IsStatus_GIRL_PULL(void);
int PAIR_IsStatus_BOY_WAIT(void);
void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1);
int PAIR_IsStatus_BOY_DITCH(void);
struct GObj *ACTGame_isHangChain(struct GObj *a0);
int ACTGame_isWeaponEnableCatchfire(int *self);
int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout);

int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget,
                     int *flagout);

int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3);
int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f);
unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout);
int ACTCheckViewCl(struct GObj *self, void *a1, void *a2, int range, float f);
void ACTGameView_FirstSet(char *self);
void ACTGameView_Add(struct GObj *self, struct GObj *obj);
int ACTGameView_Check(struct GObj *self, struct GObj *obj);
int ACTGameViewSimple_Check(struct GObj *self, struct GObj *obj);
int ACTGame_GetMotOrientFromWeapon(struct GObj *a0);
unsigned char ACTGame_NoWeapon(struct GObj *a0);
inline int ACTGame_isWeaponCombustible(void);
int *ACTGame_GetNearestGObj(struct GObj *a0, int a1);
void ACTLookTarget_Init(struct GObj *a0);
int _ACTLookTarget_Set(struct GObj *a0, struct GObj *a1, float *a2, int a3, int a4);
void ACTParaStatus_Init(struct GObj *a0);
inline void _ACTParaStatus_Set(struct GObj *a0, int bit);
unsigned long long _ACTParaStatus_Check(struct GObj *a0, int bit);
void _ACTCharStatus_Init(int **a0);
void _ACTCharStatus_Set(struct GObj *a0, int bit, float f, int val);
unsigned char _ACTCharStatus_Check(struct GObj *a0, int bit);
void _ACTCharStatus_Exec(void);
void _ACTSetEnemyDisappearSpeed(struct GObj *a0, float f);
void ACTGame_SetMotionPlaySpeedRatio_Reserve(struct GObj *a0, float f, unsigned int a1);
float _ACTGame_GetParamF(int idx);
int ACTGame_GetCurrentCallStatus(struct GObj *a0);
unsigned char ACTGame_CheckPriInputFrame(struct GObj *a0);
void ACTGame_SendSoundMail(struct GObj *a0, int mail, struct GObj *from, int a3, int a4);
void ACTGame_LwsEffectInit(struct GObj *a0);
void ACTGame_LwsEffect_Guard(struct GObj *a0);
inline void ActGame_GetOrientQ(void *q, void *v, int deg);
void _GetRootObjectOrient(void *a0, char *a1);
void ACTItemForceDrop(struct GObj *a0);
inline void GetOtherStageGirlOrient(float *a0, float *a1);
int ACTChkAttackIgnore_BOY(struct GObj *a0, struct GObj *actor);
int ACTChkAttackIgnore_GIRL(struct GObj *a0, struct GObj *actor);
int ACTChkAttackIgnore_ENEMY(struct GObj *a0, struct GObj *actor);
unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor);
int ACTCheckViewClDetail(struct GObj *self, void *a1, void *a2, int range, float f);
void ACTGame_SetMotionPlaySpeedRatio_Clear(struct GObj *a0);
void ACTGame_SetMotionPlaySpeedRatio_Exec(struct GObj *a0);
void GetGirlPositionAtThisStage(float *a0);
int ACTCheckView(struct GObj *self, void *a1, void *a2, int range, float f);
void ACTGame_BeforeFunc(struct GObj *self);
void ACTGame_InsertCamera_GirlIsPinch(void);
void ACTParaStatus_Clear(struct GObj *a0);
void ACTGame_SaveActorInformation(struct GObj *a0);
void ACTGame_DeleteActorInformation(struct GObj *a0);
/* The second parameter is an unsigned char. */
void ACTGame_SetActors_Debug(int stage, unsigned char flag);
void ACTGame_StageChangeGObj(struct GObj *self, int idx);
void GetSkeltonOrient(float *out, void *obj, int node);
void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7);

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
