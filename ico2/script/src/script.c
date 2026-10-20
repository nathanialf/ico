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

/* .sdata.  scpDummyGObj is the word an obj-layout row's GObj slot points
   at (the demo's .data holds 0x67A00C once, as the USA's holds its
   scpDummyGObj); scpSekizou stores the pad vibration handle at 0x67A014
   and its volume byte at 0x67A018, so sekizo_yure and sekizo_yure_vol
   follow the two dummy words.  Nothing reads the last word; it keeps
   sekizo_common's name (its place is not measured).  Then scpObj1882's
   string. */
int scpBoyControlReadDisable = 0;

float scpSeEnvMasterVolRate = 1.0f;

char *scpDummyGObj = 0;

char *scpDummyGObj2 = 0;

int sekizo_yure = 0;

unsigned char sekizo_yure_vol = 0;

SqEntry *sekizo_common = 0;

/* the parent link stage_SetParentOfGObj copies into a stage animation: the
   object and its skeleton node, -1 when the node was not found */
struct ParentLink { /* derived name */ /* field names derived */
    GObj *gobj;
    int node;
};

/* .bss: the wall-collision result and the two-slot ADPCM play-request table
   (2 x 0x14 bytes; this build keeps no camera target after it). */
static WallCfg wallColResult; /* derived name */

/* the two-slot ADPCM play-request table */
typedef struct AdpcmReq { /* field names derived */
    int kind;             /* 0x00, the sound id, 0 == slot free */
    SqEntry **id;         /* 0x04: the caller's handle variable */
    int loopNum;          /* 0x08, AdpcmOpen's loop count */
    int ch;               /* 0x0C, AdpcmOpen's channel */
    int play;             /* 0x10, start playing once open (this build's
                             record ends here: scpAdpcmPlayRequestFunc steps
                             the table by 20) */
} AdpcmReq;               /* derived name */

static AdpcmReq adpcmReq[2]; /* derived name */

/* sugipon's motionKind (MotionDef, motionOrientManager.h), read here through
   this file's own view of the record */
extern struct MotTblRec { /* derived name */ /* field names derived */
    char pad0[276];
    int smzAngle;
    char pad118[108];
} motionKind[];

/* .data: the two exported door tables, then five read only here.  Each is
   the usual actor mail pair: the mail the door thread answers, then the 376
   end marker act.c walks to (this build's mail numbers). */
ActMail scpInterDoorUpLever1[2] = {{356, scpDoorTypeUpSwitch}, {376}};

ActMail scpInterDoorUpLever2[2] = {{357, scpDoorTypeUpSwitch}, {376}};

static ActMail doorTypeUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorTypeUpSwitchDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorTypeUpSwitchUp_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorTypeUpDown_mes[2] = {{377}, {376}}; /* derived name */

static ActMail doorTypeUpUp_mes[2] = {{377}, {376}}; /* derived name */

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

void scpPlayMot(GObj *self, int mot)
{
    Act *act = GOBJ_ACT(self);
    int id = -1;

    if (self == boyGObj) {
        id = 1205;
    } else if (self == girlGObj) {
        id = 1768;
    } else if (self == isysGObjSearchFromObjLayoutID(1863)) {
        id = 2112;
    } else if (((GObj *)self)->kind == 4) {
        id = 2104;
    }

    if (id < 0) {
        InitMotionOrient(self, 1772, 2106, -1, -1, mot);
        return;
    }
    ControlMotionOrient(id, mot);
    act->motReq = SetMotionRequest(self, 223, act->env.motOriReq);
}

void scpPlayJump(GObj *self, int orient)
{
    ACTItemForceDrop(self);
    GOBJ_ACT(self)->enemy->jumpOrient = orient;
    iosOmSendMail(self, 43, self);
}

void scpPlayStart(GObj *self)
{
    ACTItemForceDrop(self);
    iosOmSendMail(self, 44, self);
    SetLodLevel(self, 0);
}

void scpPlayEnd(GObj *self)
{
    iosOmSendMail(self, 45, self);
    SetLodLevel(self, 2);
}

void scpTrans(void *self, float *rot)
{
    SetRootMatrixWithTransOffset(self, rot[0], rot[1], rot[2]);
}

INCLUDE_ASM_LIT(func_00172F90);

INCLUDE_ASM_LIT(func_00172B60);

/* The trigger tables stand before the trigger functions: the demo's .rodata
   has them after func_00172B60's string and before func_00172340's. */
/* the colour a trigger ball's wire sphere is drawn in; red while it hits */
static const Col4 triggerBallColor = {{0, 16, 32, 128}}; /* derived name */

/* the object kinds a trigger ball tests */
static const int targetManKind[] = {1, 2, 4}; /* derived name */

inline int scpTriggerIgnore(GObj *self)
{
    /* the object kinds a trigger may ignore, up to the -1 end marker */
    int ignoreKind[4] = {1, 2, 4, -1}; /* derived name */
    int i = 0;

    while (ignoreKind[i] != -1) {
        if (((GObj *)self)->kind == ignoreKind[i]) {
            Sub15C *sub = GOBJ_SUB(self);
            if (_ACTGame_GetParamF(1) < sub->ctrl.groundHeight || GOBJ_ACT(self)->actMode == 22) {
                return 1;
            }
        }
        i++;
    }
    return 0;
}

/* the object kinds a floor-attribute trigger tests */
static const int floorTargetManKind[] = {1, 2, 4, 17}; /* derived name */

INCLUDE_ASM(func_00172178);

INCLUDE_ASM(func_00172340);

INCLUDE_ASM(func_00172490);

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

/* where the stone statue's sound effects play */
static const Vec16 sekizouSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(scpSekizou);

INCLUDE_ASM(func_00172B60);

/* the root position a direct stage change parks the actor at, far out of the map */
static const Vec16 farRootPos = {{-1000000.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

void scpSekizouCheckPoint(void)
{
    int was;

    if (girlGObj != 0) {
        gamesysObjInfoPosSetStage(girlGObj, GOBJ_ACT(girlGObj)->infoPos, 0, stage_no);
    }
    gamesysObjInfoPosSetStage(boyGObj, GOBJ_ACT(boyGObj)->infoPos, 0, stage_no);
    was = gflagChk(332);
    gflagOn(332);
    CheckPoint();
    if (was == 0) {
        gflagOff(332);
    }
}

/* the colour the item-revival boundary's wire sphere is drawn in */
static const Col4 itemBoundaryColor = {{0, 32, 16, 128}}; /* derived name */

INCLUDE_ASM(scpDispOffAllWithKind);

INCLUDE_ASM(scpDispOnAllWithKind);

INCLUDE_ASM(scpActivateAllWithKind);

INCLUDE_ASM(scpDisActivateAllWithKind);

INCLUDE_ASM(scpLinkBGAtoLayoutedTarget);

INCLUDE_ASM(func_00172F90);

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

INCLUDE_ASM(_SCPMoveCharactorByWay);

INCLUDE_ASM(func_001742B0);

inline GObj *scpSearchGobj(int id)
{
    return isysGObjSearchFromObjLayoutID(id);
}

inline void scpPlayMotNode(void *self, int mot, void *obj, int node)
{
    float buf[4];
    memset(buf, 0, 16);
    buf[3] = 1.0f;
    SetMotionNodeFixModeParameter(self, obj, 0, node, buf, 0.0f, 0.0f, 0.0f, 1.0f);
    scpPlayMot(self, mot);
}

inline void scpPlayMotReq(GObj *self, int mot)
{
    Act *p = GOBJ_ACT(self);
    p->motReq = SetMotionRequest(self, mot, p->env.motOriReq);
}

inline void scpPlayPosSet(void *self, float x, float y, float z)
{
    float buf[4];
    memset(buf, 0, 16);
    buf[0] = x;
    buf[1] = y;
    buf[2] = z;
    SetDirectRootPosition(self, buf);
    ClearMotionGeometryInfo(self);
}

inline void scpPlayWaitMotEnd(GObj *self)
{
    Act *p = GOBJ_ACT(self);
    while ((*(int *)((char *)p->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
}

inline void InitStageChange(void)
{
    stageChangeReq = 0;
}

inline int RequestStageChange(int no, GObj *g, GObj *girl, float speed, float wait)
{
    return RequestStageChangeWithColor(no, g, girl, speed, wait, 0, 0, 0);
}

inline int RequestStageChangeWithColor(int no, GObj *g, GObj *girl, float speed, float wait,
                                       unsigned char r, unsigned char gr, unsigned char b)
{
    int ret;
    short next;
    Act *act;

    next = stageData[stage_no].ent[no - 1];
    ret = 0;
    if (gameover_flag == 0 && stageChangeReq == 0 && next != 0) {
        if (g != 0) {
            act = GOBJ_ACT(g);
            ACTGame_StageChangeGObj(g, next);
            if (act->weapon != 0) {
                ACTGame_StageChangeGObj(act->weapon, next);
            }
            if (act->curItem != 0) {
                ACTGame_StageChangeGObj(act->curItem, next);
            }
            BoyInfoUpdate_StageChange();
        }
        if (girl != 0) {
            ACTGame_StageChangeGObj(girlGObj, next);
        }
        stgmgrForceSwitchWithFadeColor(exitData[next].nextStage, speed, wait, r, gr, b);
        ret = 1;
        stageChangeReq = 1;
    }
    return ret;
}

inline int RequestStageChangeSimple(int no, float speed, float wait, unsigned char r,
                                    unsigned char gr, unsigned char b)
{
    int ret = 0;

    if (gameover_flag == 0) {
        if (stageChangeReq == 0) {
            stgmgrForceSwitchWithFadeColor(no, speed, wait, r, gr, b);
            stageChangeReq = 1;
            ret = 1;
        }
    }
    return ret;
}

inline void RequestStageChangeDirect(GObj *self, int stage, void *dir, int deg)

{
    Vec16 pos;
    ACTGame_StageChangeGObjDirect(self, stage, dir, deg);
    ACTCharctrl_Lock(self);
    pos = farRootPos;
    SetDirectRootPosition(self, &pos);
    iosOmSendMail(self, 38, self);
}

inline void scpFadeOut(float speed, int r, int g, int b)
{
    fadeStatus = 1;
    fadeSpeed = speed;
    fadeContinue = 1;
    fadeColor[0] = r;
    fadeColor[1] = g;
    fadeColor[2] = b;
}

inline void scpFadeIn(float f)
{
    fadeStatus = 1;
    fadeContinue = 0;
    fadeSpeed = -f;
}

inline int scpFadeChk(void)
{
    int v = fadeStatus;
    if (v == 0) {
        return 0;
    }
    if (v == 3) {
        v = 0;
        return v;
    }
    return 1;
}

inline int scpGameStat_BoyWeaponkind(void)
{
    GObj *w = GOBJ_ACT(boyGObj)->weapon;
    if (w == 0)
        return 0;
    return CheckWeaponKind(w);
}

inline int scpIsWallLever2On(void)
{
    return IsWallLeverStatus();
}

inline int scpIsHangChain(GObj *self)
{
    return ACTGame_isHangChain(self) != 0;
}

inline int scpIsHangChainOptional(GObj *self, int b)
{
    register GObj *p;        /* v1 */
    register int b_save;     /* s0 */
    register unsigned int v; /* v0 */
    b_save = b;
    p = ACTGame_isHangChain(self);
    v = 0;
    if (p == 0)
        goto out;
    v = (unsigned int)(p->labelId ^ b_save) < 1;
out:
    return (int)v;
}

inline void scpBornSpider(int n, float a, float b, float c, float d)
{
    int i;
    float t1, t2;
    int r;
    GObj *dead;
    for (i = 0; i < n; i++) {
        t1 = random_unit();
        spiderLayout.pos[1] = b;
        spiderLayout.pos[0] = a + d * (t1 + t1 - 1.0f);
        t2 = random_unit();
        spiderLayout.pos[2] = c + d * (t2 + t2 - 1.0f);
        r = rand();
        spiderLayout.obj = 1;
        spiderLayout.rot[1] = (float)((r >> 4) & 0xFFFF) * 3.1415927f * 3.0517578125e-05f;
        dead = MakeAP1GObj(&spiderLayout);
        _ACTWait(1);
        WakeUpAP1(dead);
    }
}

/* the stream motion's root offset; the stream scale word is raised and
   cleared again right after the copy */
inline void scpSetStreamMotionRootOffset(GObj *self, float x, float y, float z)
{
    float v[4] = {x, y, z, 0.0f};
    CopyVector(GOBJ_SUB(self)->streamOfs, v);
    GOBJ_SUB(self)->streamScale = 1;
    GOBJ_SUB(self)->streamScale = 0;
}

inline void scpWakeupItemWithBoundary(float x, float y, float z, float r)
{
    float pos[4];
    Col4 col;

    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    ((int *)pos)[3] = 0;
    ReviveCarryableItemsWithBoundary(pos, r);
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        col = itemBoundaryColor;
        gif_StartPacketPri(11);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

inline int scpCheckReadyAllObjects(void)
{
    return CheckReadyAllSwitches() != 0;
}

inline void scpDoorTypeUpMain(GObj *volatile self)
{
    Act *p = GOBJ_ACT(self);
    p->mainMail = p->doorMail;
    for (;;) {
        _ACTWait(1);
    }
}

/* the ADPCM request thread: no free-area wait or battle-music fallback in
   this build */
inline void scpSubAdpcmPlay(GObj *volatile self)
{
    AdpcmOpenReq work;
    int i;
    SqEntry *h;

    memset(adpcmReq, 0, sizeof(adpcmReq));
    for (;;) {
        AdpcmReq *tbl = adpcmReq;
        for (i = 0; i < 2; i++) {
            if (tbl[i].kind != 0) {
                AdpcmReq *p = &tbl[i];

                soundDataOpen(&work, 2, p->kind, p->ch, p->loopNum);
                while ((h = soundDataOpenSync(&work)) == (SqEntry *)-1) {
                    _ACTWait(1);
                }
                if (h != 0) {
                    if (p->play != 0) {
                        AdpcmPlay(h->stream);
                    }
                    if (p->id != 0) {
                        *p->id = h;
                    }
                }
                p->kind = 0;
            }
        }
        _ACTWait(1);
    }
}

inline void actSubSekizoSe(GObj *volatile self)
{
    int h = soundSeDefPlay(1167, 0, 0, 1);
    _ACTWait((int)((60 - systemStatus[0] * 10) / systemStatus[1] * 9.5f));
    soundSeDefStop(h);
}

/* object 1882's process: scrolls st25a.c's wall01 texture, then, until flag 286
   is set, hands the actor queen_appear_mes */
inline void scpObj1882(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);
    tex_SetUVScroll(wall01Tex, 0.0f, -0.2f, 0.0f, -0.0625f, 0.0f, -0.3f, 1);
    _ACTWait(300);
    tex_SetUVScroll(wall01Tex, 0.0f, -0.3f, 0.0f, -0.001f, 0.0f, -0.7f, 1);
    if (gflagChk(286) == 0) {
        queen_appear_mes[0].func = actSwordEffXL;
        act->mail = queen_appear_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}
