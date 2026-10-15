#include "sugiCommon.h"
#include "backStage.h"
#include "debug.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "obj_manager.h"
#include "act-way.h"
#include "enemy_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gv.h"
#include "gflag.h"
#include "st25a.h"
#include "Primitive.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "a_p_1.h"
#include "cage.h"
#include "particleEffect.h"
#include "spider.h"
#include <string.h>
#include <stdlib.h>
#include "StageManager.h"
#include "act.h"
#include "motionOrientManager.h"
#include "typedef.h"
#include "torch.h"
#include "matrixDrive.h"
#include "script.h"
#include "layout_action.h"
#include "Basic.h"
#include "GifPacket.h"
#include <libvu0.h>
#include "lodManager.h"
#include "geometryManager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "Matrix.h"
#include "item.h"
#include "pad.h"
#include "rotObject.h"
#include "quaternion.h"
#include "act_a_p_1.h"
#include "gobj.h"
#include "boyact.h"
#include "act-game.h"
#include "commonact.h"
#include "fieldCollision.h"
#include "main.h"
#include "motionManager2.h"
#include "weapon.h"
#include "include_asm.h"

/* .sdata */
int scpBoyControlReadDisable = 0;

float scpSeEnvMasterVolRate = 1.0f;

SqEntry *sekizo_common = 0;

char *scpDummyGObj = 0;

char *scpDummyGObj2 = 0;

int sekizo_yure = 0;

unsigned char sekizo_yure_vol = 0;

/* the parent link stage_SetParentOfGObj copies into a stage animation: the
   object and its skeleton node, -1 when the node was not found */
struct ParentLink { /* derived name */ /* field names derived */
    GObj *gobj;
    int node;
};

/* .bss: the wall-collision result, the two-slot ADPCM play-request table
   (2 x 0x18 bytes), and the camera target the script last asked for. */
static WallCfg wallColResult; /* derived name */

/* the two-slot ADPCM play-request table */
typedef struct AdpcmReq { /* field names derived */
    int kind;             /* 0x00, the sound id, 0 == slot free */
    SqEntry **id;         /* 0x04: the caller's handle variable */
    int loopNum;          /* 0x08, AdpcmOpen's loop count */
    int ch;               /* 0x0C, AdpcmOpen's channel */
    int play;             /* 0x10, start playing once open */
    int cancel;           /* 0x14, close as soon as it opens */
} AdpcmReq;               /* derived name */

static AdpcmReq adpcmReq[2]; /* derived name */

static float scriptCameraTarget[4]; /* derived name */

/* sugipon's motionKind (MotionDef, motionOrientManager.h), read here through
   this file's own view of the record */
extern struct MotTblRec { /* derived name */ /* field names derived */
    char pad0[312];
    int smzAngle;
    char pad13C[84];
} motionKind[];

/* .data: the colour packet prim_DispWireBox draws the debug trigger box
   with, declared as the whole 4-word record. */
static int wireBoxColor[4] = {0, 16, 32, 128}; /* derived name */

/* .data: the two exported door tables, then five read only here.  Each is
   the usual actor mail pair: the mail the door thread answers, then the 396
   end marker act.c walks to. */
ActMail scpInterDoorUpLever1[2] = {{376, scpDoorTypeUpSwitch}, {396}};

ActMail scpInterDoorUpLever2[2] = {{377, scpDoorTypeUpSwitch}, {396}};

static ActMail doorTypeUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorTypeUpSwitchDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorTypeUpSwitchUp_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorTypeUpDown_mes[2] = {{397}, {396}}; /* derived name */

static ActMail doorTypeUpUp_mes[2] = {{397}, {396}}; /* derived name */

/* the 0x30-byte wood-bridge table entry at woodBoxTbl: an object id, the
   trigger `kind` that selects which axis test runs, the bridge end offset the
   way group is built from, and the four axis bounds the tests read. */
struct WoodBoxEnt { /* derived name */ /* field names derived */
    short id;                          /* 0x00 */
    char kind;                         /* 0x02 */
    char pad3[13];                     /* 0x03 */
    float ofs[4];                      /* 0x10 */
    float b0;                          /* 0x20 */
    float b1;                          /* 0x24 */
    float b2;                          /* 0x28 */
    float b3;                          /* 0x2C */
};

/* .data: the wood-bridge trigger table, one row per bridge object, walked by
   object id. */
static struct WoodBoxEnt woodBoxTbl[7] = {
    {1589, 0, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -1410.0f, 1000.0f, 0.0f, 0.0f},
    {1584, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, 707.0f, 2000.0f, 570.0f, 1027.0f},
    {1586, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, 707.0f, 2000.0f, 570.0f, 1027.0f},
    {902, 6, {0}, {0.0f, -200.0f, 100.0f, 0.0f}, -1431.0f, 105.0f, -470.0f, -259.0f},
    {806, 8, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -350.0f, -285.0f, -450.0f, -280.0f},
    {807, 8, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, -350.0f, -285.0f, -450.0f, -280.0f},
    {1643, 7, {0}, {-100.0f, -200.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f},
}; /* derived name */

/* .sbss: a stage change has been requested and no further one is
   accepted. */
static int stageChangeReq; /* derived name */

/* declared (void) here: the call passes no object (the ROM leaves a0 as
   scpIsWallLever2On received it), while switch.h takes the lever's GObj *
   (so neither switch.h nor box.h, which includes it, is included) */
extern int IsWallLeverStatus(void);

/* .data: the layout record scpBornSpider fills and hands MakeAP1GObj for
   each spider */
static SObjSimpleSetting spiderLayout = {{0.0f}, {0.0f}, {1.0f, 1.0f, 1.0f}}; /* derived name */

/* box.c's, defined in switch.c.inc */
extern int CheckReadyAllSwitches(void);

/* Before flag 332 this hands the actor queen_appear_mes and posts it; after
 * it, it shows object 2149, plays its motion and starts the face shadow
 * scrolls and the stage animations. */
void scpTorchLightOn(int id)
{
    void *r = scpSearchGobj(id);
    if (r) {
        LightTorchOn(r);
    }
}

void scpTorchLightOff(int id)
{
    GObj *v = scpSearchGobj(id);
    if (v) {
        LightTorchOff(v);
    }
}

void scpSetCageVelocityFriction(int id, float friction)
{
    GObj *v = scpSearchGobj(id);
    if (v) {
        SetCageVelocityFriction(v, friction);
    }
    /* no hanging object found */
    debug_StdPrintfDummy("ぶら下がりオブジェクトが見つかりません。(scpSetCageVelocityFriction)\n");
}

INCLUDE_ASM_LIT(scpGetRotObjectRotCount);

INCLUDE_ASM_LIT(scpIsRotObjectZPlusDirInclude);

INCLUDE_ASM_LIT(scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag);

INCLUDE_ASM_LIT(scpGetWallCollision);

void scpPlayMotDir(GObj *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirection(self, dir);
}

void scpPlayMotDirSmz(GObj *self, float *dir)
{
    sceVu0Normalize(dir, dir);
    SetMotionDirectionSmooze(self, dir, (float)motionKind[GOBJ_SUB(self)->ctrl.motion].smzAngle);
}

INCLUDE_ASM(scpPlayMot);

void scpPlayJump(GObj *self, int orient)
{
    ACTItemForceDrop(self);
    GOBJ_ACT(self)->enemy->jumpOrient = orient;
    iosOmSendMail(self, 45, self);
}

void scpPlayStart(GObj *self)
{
    ACTItemForceDrop(self);
    iosOmSendMail(self, 46, self);
    SetLodLevel(self, 0);
}

void scpPlayEnd(GObj *self)
{
    iosOmSendMail(self, 47, self);
    SetLodLevel(self, 2);
}

void scpTrans(void *self, float *rot)
{
    SetRootMatrixWithTransOffset(self, rot[0], rot[1], rot[2]);
}

/* one linear step of *p toward TARGET; returns non-zero once it arrives */
static inline int scpTransStep(float *p, float target, float step) /* derived name */
{
    int done = 0;

    if (0.0f < target) {
        *p += step;
        if (target < *p) {
            *p = target;
            done = 1;
        }
    } else {
        *p -= step;
        if (*p < target) {
            *p = target;
            done = 1;
        }
    }
    return done;
}

/* the colour a trigger ball's wire sphere is drawn in; red while it hits */
static const Col4 triggerBallColor = {{0, 16, 32, 128}}; /* derived name */

/* the object kinds a trigger ball tests */
static const int targetManKind[] = {1, 2, 4}; /* derived name */

INCLUDE_ASM(scpTriggerBallTargetMan);

/* the object kinds a trigger may ignore, up to the -1 end marker */
static const int ignoreKind[] = {1, 2, 4, -1}; /* derived name */

/* the object kinds a floor-attribute trigger tests */
static const int floorTargetManKind[] = {1, 2, 4, 17}; /* derived name */

INCLUDE_ASM(scpDoorTypeUpDown);

INCLUDE_ASM(scpDoorTypeUpUp);

INCLUDE_ASM(func_0017BA00);

/* the slot of the pending play request whose id is ID, or -1 (inlined into
   scpAdpcmCloseChkFunc, scpGirlHintVoiceCancel and others) */
static inline int scpAdpcmRequestSlot(SqEntry **id) /* derived name */
{
    int i;
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind != 0 && adpcmReq[i].id == id)
            goto found;
    }
    i = -1;
found:
    return i;
}

/* flag the pending play request whose id is ID so the ADPCM daemon closes
   it (inlined into scpAdpcmCloseFunc and scpAdpcmFadeCloseFunc) */
static inline void scpAdpcmRequestClose(SqEntry **id) /* derived name */
{
    int i;
    for (i = 0; i < 2; i++)
        if (adpcmReq[i].kind != 0 && adpcmReq[i].id == id) {
            adpcmReq[i].cancel = 1;
            break;
        }
}

INCLUDE_ASM_LIT(scpDeamon);

INCLUDE_ASM(scpWoodSrh);

/* where the stone statue's sound effects play */
static const Vec16 sekizouSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(scpSekizou);

/* the root position a direct stage change parks the actor at, far out of the map */
static const Vec16 farRootPos = {{-1000000.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(_SCPBoySupportGirl);

INCLUDE_ASM(_SCPMoveCharactorByWay_Cancel);

INCLUDE_ASM(scpSekizouCheckPoint);

void scpWakeupEnemyOne(int id)
{
    void *rc = isysGObjSearchFromObjLayoutID(id);
    if (rc) {
        iosOmSendMail(rc, 31, rc);
    }
}

void scpSleepEnemyOne(int id)
{
    void *rc = isysGObjSearchFromObjLayoutID(id);
    if (rc) {
        iosOmSendMail(rc, 32, rc);
    }
}

void scpSleepSpiderGroupOne(int id)
{
    void *v = isysGObjSearchFromObjLayoutID(id);
    if (v) {
        SleepSpiderGroup(v);
    }
}

void scpWakeupSpiderGroupOne(int id)
{
    void *v = isysGObjSearchFromObjLayoutID(id);
    if (v) {
        WakeupSpiderGroup(v);
    }
}

void scpKillSpiderGroup(int id)
{
    DeleteAllSpidersOfLayoutGroup(isysGObjSearchFromObjLayoutID(id));
}

/* the colour the item-revival boundary's wire sphere is drawn in */
static const Col4 itemBoundaryColor = {{0, 32, 16, 128}}; /* derived name */

void preload(int idx)
{
    short s;

    s = stageData[stage_no].ent[idx - 1];
    stgmgrNextStagePreLoadForceStageSet(exitData[s].nextStage);
    stgmgrNextStagePreLoadForceNoCancel(1);
}

void scpSetBoyWeaponGObj(void *w)
{
    SetBoyWeaponGObj(w);
}

INCLUDE_ASM_LIT(scpCheckExistAliveEnemy);

INCLUDE_ASM_LIT(scpCheckExistAliveSpider);

INCLUDE_ASM(scpDispOffAllWithKind);

INCLUDE_ASM(scpDispOnAllWithKind);

INCLUDE_ASM(scpActivateAllWithKind);

INCLUDE_ASM(scpDisActivateAllWithKind);

INCLUDE_ASM(scpLinkBGAtoLayoutedTarget);

INCLUDE_ASM(scpLinkBGAtoLayoutedTargetSkelton);

INCLUDE_ASM(scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag);

INCLUDE_ASM(scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag);

INCLUDE_ASM(scpGetWallCollision);

INCLUDE_ASM(scpDoorTypeUp);

INCLUDE_ASM(scpDoorTypeUpSwitch);

INCLUDE_ASM(scpAdpcmPlayRequestFunc);

INCLUDE_ASM(scpAdpcmPlayRequestNum);

int scpAdpcmFadeCloseFunc(SqEntry *p, short fade)
{
    if (p == 0 || p->stream == 0) {
        return 0;
    }
    p->stream->fadeStep = fade;
    return 1;
}

int scpAdpcmCloseChkFunc(SqEntry *p)
{
    if (p == 0 || p->stream == 0 || p->stream->bg == 0) {
        return 0;
    }
    return 1;
}

INCLUDE_ASM(scpDeamon);

INCLUDE_ASM(scpWoodBox);

INCLUDE_ASM(scpIsTorchLightOn);

INCLUDE_ASM(scpIsBombExplode);

INCLUDE_ASM(scpGetRotObjectRotCount);

INCLUDE_ASM(scpIsRotObjectZPlusDirInclude);

INCLUDE_ASM(scpTransLinear);

INCLUDE_ASM(scpRotateLinear);

INCLUDE_ASM(scpTriggerPosBall);

INCLUDE_ASM(scpTriggerBall);

INCLUDE_ASM(scpTriggerFloorAttr);

INCLUDE_ASM(scpTriggerWallAttr);

INCLUDE_ASM(scpTriggerFloorAttrTargetMan);

INCLUDE_ASM(scpTriggerPosBox);

INCLUDE_ASM(scpEffectStart);

INCLUDE_ASM(scpSleepEnemyAll);

INCLUDE_ASM(scpWakeupEnemyAll);

INCLUDE_ASM(scpKillEnemyAll);

INCLUDE_ASM(scpMaskGeneratorAll);

INCLUDE_ASM(scpKillEnemyOne);

INCLUDE_ASM(_SCPMoveCharactorByWay);

INCLUDE_ASM(_SCPMoveByWay_ToChar);

INCLUDE_ASM(_SCPCharacterStop);

INCLUDE_ASM(scpSearchGobj);

INCLUDE_ASM(scpPlayMotNode);

INCLUDE_ASM(scpPlayMotReq);

INCLUDE_ASM(scpPlayPosSet);

INCLUDE_ASM(scpPlayWaitMotEnd);

INCLUDE_ASM(InitStageChange);

INCLUDE_ASM(RequestStageChange);

INCLUDE_ASM(RequestStageChangeWithColor);

INCLUDE_ASM(RequestStageChangeSimple);

INCLUDE_ASM(RequestStageChangeDirect);

INCLUDE_ASM(scpFadeOut);

INCLUDE_ASM(scpFadeIn);

INCLUDE_ASM(scpFadeChk);

INCLUDE_ASM(scpGameStat_BoyWeaponkind);

INCLUDE_ASM(scpIsWallLever2On);

INCLUDE_ASM(scpIsHangChain);

INCLUDE_ASM(scpIsHangChainOptional);

INCLUDE_ASM(scpBornSpider);

INCLUDE_ASM(scpActStatusDeathFall);

INCLUDE_ASM(scpSetStreamMotionRootOffset);

INCLUDE_ASM(scpWakeupItemWithBoundary);

INCLUDE_ASM(scpCheckReadyAllObjects);

INCLUDE_ASM(ScpCallCameraSetTarget);

INCLUDE_ASM(ScpCallCameraGetTarget);

INCLUDE_ASM(ScpCallCameraOff);

INCLUDE_ASM(ScpCallCameraOn);

INCLUDE_ASM(ScpCallCameraTargetOff);

INCLUDE_ASM(scpTransGObj);

INCLUDE_ASM(scpExplodeSecretItem);

INCLUDE_ASM(scpCheckExistAliveEnemy);

INCLUDE_ASM(scpCheckExistAliveSpider);

INCLUDE_ASM(func_0017EC50);

INCLUDE_ASM(scpCheckDisconnectWallStart);

INCLUDE_ASM(scpTriggerIgnore);

INCLUDE_ASM(scpDoorTypeUpMain);

INCLUDE_ASM(actSubSekizoSe);
