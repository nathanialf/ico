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
    char pad0[390];
    short smzAngle;
    char pad188[12];
} motionKind[];

/* .data: the colour packet prim_DispWireBox draws the debug trigger box
   with, declared as the whole 4-word record. */
static int wireBoxColor[4] = {0, 16, 32, 128}; /* derived name */

/* .data: the two exported door tables, then five read only here.  Each is
   the usual actor mail pair: the mail the door thread answers, then the 392
   end marker act.c walks to. */
ActMail scpInterDoorUpLever1[2] = {{372, scpDoorTypeUpSwitch}, {392}};

ActMail scpInterDoorUpLever2[2] = {{373, scpDoorTypeUpSwitch}, {392}};

static ActMail doorTypeUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorTypeUpSwitchDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorTypeUpSwitchUp_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorTypeUpDown_mes[2] = {{393}, {392}}; /* derived name */

static ActMail doorTypeUpUp_mes[2] = {{393}, {392}}; /* derived name */

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

INCLUDE_ASM(scpPlayMotDirSmz);

INCLUDE_ASM(scpPlayMot);

INCLUDE_ASM(scpPlayJump);

INCLUDE_ASM(scpPlayStart);

INCLUDE_ASM(scpPlayEnd);

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

INCLUDE_ASM(scpSubAdpcmPlay);

inline int scpAdpcmCloseChkFunc(SqEntry **h);

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

INCLUDE_ASM(scpAdpcmFadeClose);

INCLUDE_ASM(scpAdpcmCloseChk);

INCLUDE_ASM(scpDeamon);

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

INCLUDE_ASM(scpTriggerIgnore);

INCLUDE_ASM(scpDoorTypeUpMain);

INCLUDE_ASM(actSubSekizoSe);
