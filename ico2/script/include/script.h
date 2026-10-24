/*
 * ico2/script/include/script.h
 *
 * The declarations of what script.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef SCRIPT_H
#define SCRIPT_H

#include "typedef.h"

#ifdef VERSION_AUG6
#include "gobj.h"
#include "enemy_act.h"
#include "act_a_p_1.h"
#include "act-game.h"
#endif

struct GObj;

struct SqEntry;

/* script.o's .sdata globals: the boy-control read lock the
   scripts raise, the sound-environment master volume rate, the statue's
   common ADPCM handle, two dummy GObj words and the statue's pad vibration
   handle and volume. */
extern int scpBoyControlReadDisable;
extern float scpSeEnvMasterVolRate;
extern struct SqEntry *sekizo_common;
extern char *scpDummyGObj;
extern char *scpDummyGObj2;
extern int sekizo_yure;

#ifndef VERSION_JUN26
extern unsigned char sekizo_yure_vol;
#endif

/* script.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order),
 * from scpDispOffAllWithKind on. */
void scpDispOffAllWithKind(int kind);
void scpDispOnAllWithKind(int x);
void scpActivateAllWithKind(int kind);
void scpDisActivateAllWithKind(int kind);
void scpLinkBGAtoLayoutedTarget(int id, int key);
void scpLinkBGAtoLayoutedTargetSkelton(int id, int focus, int key);

#ifndef VERSION_JUN26
void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int id, int focus, int key,
                                                            int localRotation);

inline void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int kind, int focus, int key,
                                                               int localRotation);
#endif

WallCfg *scpGetWallCollision(float x0, float y0, float z0, float x1, float y1, float z1);
void scpDoorTypeUp(struct GObj *volatile self);
inline void scpDoorTypeUpSwitch(struct GObj *volatile self);
void scpAdpcmPlayRequestFunc(int kind, struct SqEntry **id, int ch, int loopNum, int play);
int scpAdpcmPlayRequestNum(void);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
int scpAdpcmFadeClose(struct SqEntry *p, short fade);
int scpAdpcmCloseChk(struct SqEntry *p);
void scpDeamon(struct GObj *volatile self);
#else
int scpAdpcmFadeCloseFunc(struct SqEntry **h, short fade);
int scpAdpcmCloseChkFunc(struct SqEntry **h);
void scpDeamon(struct GObj *volatile self);
void scpGirlHintVoiceCancel(void);
#endif

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
void scpWoodBox(struct GObj *volatile self);
#endif

int scpIsTorchLightOn(int id);
struct GObj *scpIsBombExplode(int x);
float scpGetRotObjectRotCount(int id);
int scpIsRotObjectZPlusDirInclude(int id, int from, int to);
void scpTransLinear(struct GObj *obj, int axis, float target, float step);
void scpRotateLinear(void *obj, int deg, short step, int axis);
int scpTriggerPosBall(float *pos, float *target, float r);
int scpTriggerBall(struct GObj *obj, struct GObj *target, float r);
int scpTriggerFloorAttr(struct GObj *self, int attr);
int scpTriggerWallAttr(struct GObj *self, int attr);
int scpTriggerFloorAttrTargetMan(struct GObj *self, int attr);
int scpTriggerPosBox(float *p, float *pos, float *size);
int scpEffectStart(void *pos, int kind);
void scpSleepEnemyAll(void);
void scpWakeupEnemyAll(void);
inline void scpKillEnemyAll(void);
inline void scpMaskGeneratorAll(void);

#ifdef VERSION_JUN26
int _SCPMoveCharactorByWay(struct GObj *self, int tgt, float *dir, float speed, int flags);
void _SCPBoySupportGirl(float x0, float y0, float z0, float x1, float y1, float z1);
#else
void scpKillEnemyOne(int id);
int _SCPMoveCharactorByWay(struct GObj *self, int tgt, float *dir, float speed, int flags);
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void _SCPBoySupportGirl(float x0, float y0, float z0, float x1, float y1, float z1);
#endif

int _SCPMoveByWay_ToChar(struct GObj *self, struct GObj *target, int deg, int flags, float scale,
                         float speed);

#ifndef VERSION_JUN26
void _SCPCharacterStop(struct GObj *self);
#endif

inline struct GObj *scpSearchGobj(int id);
void scpPlayMotNode(void *self, int mot, void *obj, int node);
void scpPlayMotReq(struct GObj *self, int mot);
void scpPlayPosSet(void *self, float x, float y, float z);
void scpPlayWaitMotEnd(struct GObj *self);
void InitStageChange(void);
int RequestStageChange(int no, struct GObj *g, struct GObj *girl, float speed, float wait);

inline int RequestStageChangeWithColor(int no, struct GObj *g, struct GObj *girl, float speed,
                                       float wait, unsigned char r, unsigned char gr,
                                       unsigned char b);

int RequestStageChangeSimple(int no, float speed, float wait, unsigned char r, unsigned char gr,
                             unsigned char b);

void RequestStageChangeDirect(struct GObj *self, int stage, void *dir, int deg);
inline void scpFadeOut(float speed, int r, int g, int b);
inline void scpFadeIn(float f);
int scpFadeChk(void);
int scpGameStat_BoyWeaponkind(void);
int scpIsWallLever2On(void);
int scpIsHangChain(struct GObj *self);
int scpIsHangChainOptional(struct GObj *self, int b);
void scpBornSpider(int n, float a, float b, float c, float d);

#ifndef VERSION_JUN26
inline int scpActStatusDeathFall(struct GObj *self);
#endif

void scpSetStreamMotionRootOffset(struct GObj *self, float x, float y, float z);
void scpWakeupItemWithBoundary(float x, float y, float z, float r);
int scpCheckReadyAllObjects(void);

#ifdef VERSION_JUN26
int scpTriggerIgnore(struct GObj *self);
inline void scpDoorTypeUpMain(struct GObj *volatile self);
void scpSubAdpcmPlay(struct GObj *volatile self);
inline void actSubSekizoSe(struct GObj *volatile self);
#else
inline void ScpCallCameraSetTarget(float x, float y, float z);
void ScpCallCameraGetTarget(float *dst);
void ScpCallCameraOff(void);
void ScpCallCameraOn(void);
void ScpCallCameraTargetOff(void);
void scpTransGObj(void *self, float dx, float dy, float dz);
void scpExplodeSecretItem(void);

#ifdef VERSION_AUG6
int scpTriggerIgnore(struct GObj *self);
inline void scpDoorTypeUpMain(struct GObj *volatile self);
inline void actSubSekizoSe(struct GObj *volatile self);
#else
int scpCheckExistAliveEnemy(void);
int scpCheckExistAliveSpider(void);
void scpLockMaxRotate(struct GObj *self, float rot);
void scpUnLockMaxRotate(struct GObj *self);

#ifdef VERSION_NTSC
int scpTriggerIgnore(struct GObj *self);
inline void scpDoorTypeUpMain(struct GObj *volatile self);
#else
short scpGetRotObjectCurrentRot(int no);
void scpCheckDisconnectWallStart(struct GObj *self);
void scpCheckDisconnectWallEnd(struct GObj *self);
int scpTriggerIgnore(struct GObj *self);
inline void scpDoorTypeUpMain(struct GObj *volatile self);
void actSubSekizoSe(struct GObj *volatile self);
#endif
#endif
#endif

/* The entry points script.o compiles in place, in its own parse order. */
void scpTorchLightOn(int id);
void scpTorchLightOff(int id);
void scpSetCageVelocityFriction(int id, float friction);
void scpPlayMotDir(struct GObj *self, float *dir);

#if defined(VERSION_NTSC) || defined(VERSION_JUN26)
void scpPlayJump(struct GObj *self, int orient);
#endif

void scpPlayMot(struct GObj *self, int mot);
void scpPlayStart(struct GObj *self);
void scpPlayEnd(struct GObj *self);
void scpDoorTypeUpDown(struct GObj *volatile self);
void scpDoorTypeUpUp(struct GObj *volatile self);

#ifndef VERSION_JUN26
void scpSubAdpcmPlay(struct GObj *volatile self);

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
void scpAdpcmCloseFunc(struct SqEntry **h);
void scpGirlHintVoiceReady(int kind);
void scpGirlHintVoicePlay(void);
void scpGirlHintVoiceTickProc(void *cam);
#endif
#endif

void scpSekizou(struct GObj *self, int flag, int anim, int anim2, int kind, float bx, float by,
                float bz, float gx, float gy, float gz);

#ifdef VERSION_JUN26
void scpSekizouCheckPoint(void);
#else
void _SCPMoveCharactorByWay_Cancel(struct GObj *self);
void scpSekizouCheckPoint(void);
void scpWakeupEnemyOne(int id);
void scpSleepEnemyOne(int id);
void scpSleepSpiderGroupOne(int id);
void scpWakeupSpiderGroupOne(int id);
void scpKillSpiderGroup(int id);
void preload(int idx);

#ifdef VERSION_AUG6
/* Four helpers for the stage scripts that no stage calls yet.  Pinned by
 * the bytes: four function definitions seen before the code of every stage
 * file (each definition makes three hidden static labels, so every
 * static-local `.N` of st03t, st06a and st13a is 12 above a file without
 * them), unreferenced, with no string, static local or code of their own
 * (MAIN.MAP gives st03t.o only .text, .data and .lit4).  Not pinned:
 * which four, and their text.  They are Aug 20's script.c functions that
 * Aug 6's MAIN.MAP lacks, in that file's order, less its debug prints;
 * the spider kind is Aug 6's 60 (script.c's Sleep/Wakeup/KillEnemyAll),
 * the lock flag bit is Aug 20's 20 as written. */
static inline int scpCheckExistAliveEnemy(void) /* derived name */
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (actEnemyFlagCheckDead(g) == 0) {
            return 1;
        }
    }
    return 0;
}

static inline int scpCheckExistAliveSpider(void) /* derived name */
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(60); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (IsActCharDead(g) == 0) {
            return 1;
        }
    }
    return 0;
}

static inline void scpLockMaxRotate(GObj *self, float rot) /* derived name */
{
    GOBJ_ACT(self)->flags20.ll |= (1ULL << 20);
    GOBJ_WORK(self)->lockedMaxRotate = rot;
}

static inline void scpUnLockMaxRotate(GObj *self) /* derived name */
{
    GOBJ_ACT(self)->flags20.ll &= ~(1ULL << 20);
}
#else
void scpSetBoyWeaponGObj(void *w);
#endif
#endif

/* one entry of girlWarpList, the girl's warp table, 0x58 bytes; warpGirl.c
 * reads it */
typedef struct {         /* field names derived */
    float arrive2[4];    /* 0x00, the arrival in to2: y angle, then z, y, x */
    float arrive1[4];    /* 0x10, the arrival in to1 */
    float arrive0[4];    /* 0x20, the arrival in to0 */
    int gflag;           /* 0x30 */
    float box0[3];       /* 0x34 */
    float box1[3];       /* 0x40 */
    unsigned short to0;  /* 0x4C */
    unsigned short to1;  /* 0x4E */
    unsigned short to2;  /* 0x50 */
    unsigned short from; /* 0x52 */
    unsigned char kind;  /* 0x54 */
    char pad55[3];
} WarpRec; /* derived name */

extern const WarpRec girlWarpList[];

#endif /* SCRIPT_H */
