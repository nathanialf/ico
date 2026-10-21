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

inline void scpDispOffAllWithKind(int kind)
{
    void *v0 = isysGObjSearchFromObjKindID_begin(kind);
    while (v0 != 0) {
        ((GObj *)v0)->drawMask = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}

inline void scpDispOnAllWithKind(int x)
{
    GObj *p = isysGObjSearchFromObjKindID_begin(x);
    while (p != 0) {
        ((unsigned int *)p)[80 / 4] = 0xFFFFFFFF;
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

inline void scpActivateAllWithKind(int kind)
{
    GObj *p = isysGObjSearchFromObjKindID_begin(kind);
    while (p != 0) {
        p->active = 1;
        p = isysGObjSearchFromObjKindID_next(p);
    }
}

inline void scpDisActivateAllWithKind(int kind)
{
    void *v0 = isysGObjSearchFromObjKindID_begin(kind);
    while (v0 != 0) {
        ((GObj *)v0)->active = 0;
        v0 = isysGObjSearchFromObjKindID_next(v0);
    }
}

inline int scpIsTorchLightOn(int id)
{
    GObj *ret1 = scpSearchGobj(id);
    GObj *ret2 = scpSearchGobj(0);
    ret2->active = 1;
    return IsTorchLightOn(ret1);
}

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

inline GObj *scpIsBombExplode(int x)
{
    GObj *p = isysGObjSearchFromObjKindID_begin(x);
    if (p != 0) {
        do {
            if (IsBombExplode(p) != 0) {
                return p;
            }
            p = isysGObjSearchFromObjKindID_next(p);
        } while (p != 0);
    }
    return 0;
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

inline float scpGetRotObjectRotCount(int id)
{
    GObj *v = scpSearchGobj(id);
    if (v != 0) {
        return GetRotObjectRotCount(v);
    }
    /* no push-turn object found */
    debug_StdPrintfDummy("押し回しオブジェクトが見つかりません。(scpGetRotObjectRotCount)\n");
    return 0.0f;
}

inline int scpIsRotObjectZPlusDirInclude(int id, int from, int to)
{
    GObj *q = scpSearchGobj(id);
    if (q != 0) {
        int e = GetRotObjectZPlusDirection(q);
        short A1 = (from << 15) / 180;
        short A2 = (to << 15) / 180;
        if (A2 < A1) {
            if (A1 < e || e < A2)
                return 1;
            return 0;
        }
        if (A1 < e && e < A2)
            return 1;
        return 0;
    }
    /* no push-turn object found */
    debug_StdPrintfDummy("押し回しオブジェクトが見つかりません。(scpGetRotObjectZDirInclude)\n");
    return 0;
}

inline void scpLinkBGAtoLayoutedTarget(int id, int key)
{
    GObj *ret = scpSearchGobj(id);
    if (ret != 0) {
        struct ParentLink link = {ret, 0};
        stage_SetParentOfGObj(key, &link);
    }
}

/* this build parents through stage_SetParentOfGObj: no local-rotation flag
   yet, and no WithLocalRotationFlag or kind-target variants */
inline void scpLinkBGAtoLayoutedTargetSkelton(int id, int focus, int key)
{
    GObj *ret = scpSearchGobj(id);
    if (ret != 0) {
        struct ParentLink copy;
        struct ParentLink pair;
        pair.gobj = ret;
        pair.node = GetSkeltonFocusNode(ret, focus);
        copy = pair;
        if (copy.node == -1)
            /* LWS skeleton parenting: the node was not found */
            debug_StdPrintfDummy(
                "LWSのスケルトンペアレント処理において,ノードが見つかりませんでした\n");
        else
            stage_SetParentOfGObj(key, &copy);
    }
}

inline WallCfg *scpGetWallCollision(float x0, float y0, float z0, float x1, float y1, float z1)
{
    ClipWork work;

    work.pt[0][0] = x0;
    work.pt[0][1] = y0;
    work.pt[0][2] = z0;
    work.pt[0][3] = 1.0f;
    work.pt[1][0] = x1;
    work.pt[1][1] = y1;
    work.pt[1][2] = z1;
    work.pt[1][3] = 1.0f;
    work.radius = 0.0f;
    ClipWall(&work);
    wallColResult.elem = work.wall.elem;
    wallColResult.o = work.wall.o;
    if (work.wall.elem == 0) {
        /* no wall collision found */
        debug_StdPrintfDummy(
            "scpGetWallCollision: (%4.3f, %4.3f, %4.3f) => (%4.3f, %4.3f, %4.3f)\n\t壁コリジョンが見つかりません。\n",
            x0, y0, z0, x1, y1, z1);
    }
    return &wallColResult;
}

inline GObj *scpSearchGobj(int id)
{
    return isysGObjSearchFromObjLayoutID(id);
}

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

inline void scpPlayWaitMotEnd(GObj *self)
{
    Act *p = GOBJ_ACT(self);
    while ((*(int *)((char *)p->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
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

inline void scpTransLinear(GObj *obj, int axis, float target, float step)
{
    int done = 0;
    float pos[4];

    GetRootMatrixTransOffset(pos, obj);
    while (done == 0) {
        done = scpTransStep(&pos[axis], target, step);
        scpTrans(obj, pos);
        _ACTWait(1);
    }
}

inline void scpRotateLinear(void *obj, int deg, short step, int axis)
{
    float q[4];
    int t;
    int n;
    short rem;

    t = (deg << 15) / 180;
    rem = (short)(t % step);
    n = t / step < 0 ? -(t / step) : t / step;
    if (deg < 0) {
        step = -step;
    }
    while (n-- > 0 || rem != 0) {
        if (n < 0) {
            step = rem;
            rem = 0;
        }
        GetRootMatrixRotOffset(q, obj);
        step = -step;
        switch (axis) {
        case 0:
            RotQuaternionX(q, step);
            break;
        case 1:
            RotQuaternionY(q, step);
            break;
        case 2:
            RotQuaternionZ(q, step);
            break;
        }
        SetRootMatrixRotOffset(obj, q);
        _ACTWait(1);
    }
}

/* the colour a trigger's debug wire sphere or box is drawn in; red while it
   hits */
static const Col4 triggerBallColor = {{0, 16, 32, 128}}; /* derived name */

inline int scpTriggerPosBall(float *pos, float *target, float r)
{
    float d[4];
    Col4 col;
    float rr;
    int hit;

    sceVu0SubVector(d, target, pos);
    rr = r * r;
    if (sceVu0InnerProduct(d, d) < rr) {
        hit = 1;
    } else {
        hit = 0;
    }
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        col = triggerBallColor;
        if (hit != 0) {
            col.c[0] = 255;
        }
        gif_StartPacketPri(11);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}

inline int scpTriggerBall(GObj *obj, GObj *target, float r)
{
    float tpos[4];
    float pos[4];

    GetRootPosition(tpos, target);
    GetRootPosition(pos, obj);
    return scpTriggerPosBall(pos, tpos, r);
}

int scpTriggerBallTargetMan(GObj *obj, float r)
{
    /* the object kinds a trigger ball tests */
    int targetManKind[3] = {1, 2, 4}; /* derived name */
    GObj *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 3 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(targetManKind[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerBall(obj, g, r) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}

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

inline int scpTriggerFloorAttr(GObj *self, int attr)
{
    if (scpTriggerIgnore(self) != 0) {
        return 0;
    }
    return CheckFloorAttribute(self, attr);
}

inline int scpTriggerWallAttr(GObj *self, int attr)
{
    if (scpTriggerIgnore(self) != 0) {
        return 0;
    }
    return CheckWallAttribute(self, attr);
}

inline int scpTriggerFloorAttrTargetMan(GObj *self, int attr)
{
    /* the object kinds a floor-attribute trigger tests */
    int floorTargetManKind[4] = {1, 2, 4, 17}; /* derived name */
    GObj *g;
    unsigned int i;
    int hit = 0;

    for (i = 0; i < 4 && hit == 0; i++) {
        for (g = isysGObjSearchFromObjKindID_begin(floorTargetManKind[i]); g != 0;
             g = isysGObjSearchFromObjKindID_next(g)) {
            if (scpTriggerFloorAttr(g, attr) != 0) {
                hit = 1;
                break;
            }
        }
    }
    return hit;
}

inline int scpTriggerPosBox(float *p, float *pos, float *size)
{
    Col4 col;
    int hit = 0;

    if (pos[0] - size[0] < p[0] && p[0] < pos[0] + size[0] && pos[1] - size[1] < p[1] &&
        p[1] < pos[1] + size[1] && pos[2] - size[2] < p[2] && p[2] < pos[2] + size[2]) {
        hit = 1;
    }
    if (debug_wallcheck_flag != 0) {
        MatrixDrive_PushMatrix();
        col = triggerBallColor;
        if (hit != 0) {
            col.c[0] = 255;
        }
        gif_StartPacketPri(11);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireBox(size, &col);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
    return hit;
}

inline int scpEffectStart(void *pos, int kind)
{
    int buf[4];
    SetIdentityQuaternion(buf);
    return SetParticleEffect(kind, pos, buf);
}

inline void scpDoorTypeUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (gflagChk(act->doorFlag) != 0) {
        GObj *obj = self;
        scpTransLinear(obj, 1, -act->doorDist, act->doorDist);
    }
    doorTypeUp_mes[0].func = scpDoorTypeUpMain;
    act->mail = doorTypeUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void scpDoorTypeUpMain(GObj *volatile self)
{
    Act *p = GOBJ_ACT(self);
    p->mainMail = p->doorMail;
    for (;;) {
        _ACTWait(1);
    }
}

inline void scpDoorTypeUpSwitch(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    act->mainMail = 0;
    if (gflagChk(act->doorFlag) != 0) {
        doorTypeUpSwitchDown_mes[0].func = scpDoorTypeUpDown;
        act->mail = doorTypeUpSwitchDown_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
    doorTypeUpSwitchUp_mes[0].func = scpDoorTypeUpUp;
    act->mail = doorTypeUpSwitchUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

inline void scpAdpcmPlayRequestFunc(int kind, SqEntry **id, int ch, int loopNum, int play)
{
    int i;

    if (id != 0) {
        *id = 0;
    }
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind == 0) {
            goto found;
        }
    }
    return;

found:
    adpcmReq[i].kind = kind;
    adpcmReq[i].id = id;
    adpcmReq[i].loopNum = loopNum;
    adpcmReq[i].ch = ch;
    adpcmReq[i].play = play;
}

inline int scpAdpcmPlayRequestNum(void)
{
    int i;
    int n = 0;
    for (i = 0; i < 2; i++) {
        if (adpcmReq[i].kind != 0) {
            n++;
        }
    }
    return n;
}

void scpDoorTypeUpDown(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (act->doorCamera != 0) {
        Camctrl_SetTarget(act->doorCamera, 0, 3);
        if (act->doorCamWait != 0) {
            _ACTWait(act->doorCamWait);
        }
    }
    debug_StdPrintfDummy("start animation down\n");
    gflagOff(act->doorFlag);
    scpTransLinear(self, 1, act->doorDist, act->doorStep);
    if (act->doorEndWait != 0) {
        _ACTWait(act->doorEndWait);
    }
    Camctrl_ExitEveRock();
    doorTypeUpDown_mes[0].func = scpDoorTypeUpMain;
    act->mail = doorTypeUpDown_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void scpDoorTypeUpUp(GObj *volatile self)
{
    Act *act = GOBJ_ACT(self);

    if (act->doorCamera != 0) {
        Camctrl_SetTarget(act->doorCamera, 0, 3);
        if (act->doorCamWait != 0) {
            _ACTWait(act->doorCamWait);
        }
    }
    debug_StdPrintfDummy("start animation up\n");
    gflagOn(act->doorFlag);
    scpTransLinear(self, 1, -act->doorDist, act->doorStep);
    if (act->doorEndWait != 0) {
        _ACTWait(act->doorEndWait);
    }
    Camctrl_ExitEveRock();
    doorTypeUpUp_mes[0].func = scpDoorTypeUpMain;
    act->mail = doorTypeUpUp_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
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

/* the stage's script daemon; after its setup it watches pad 0 for the demo
   disc's exit combination (0x900) */
inline void scpDeamon(GObj *volatile self)
{
    _ACTWait(1);
    actCreateSubThread(scpSubAdpcmPlay, 21);
    scpSeEnvMasterVolRate = 1.0f;
    _ACTWait(3);
    StabilizeAllLayoutedCage();
    _ACTWait(1);
    backStageProcessInStage(0.0f);
    gflagOff(343);
    for (;;) {
        if ((pad[0].flags & 0x900) == 0x900 && systemStatus[6] == 0 && lock_execIcoMisc == 0) {
            func_00102790();
        }
        _ACTWait(1);
    }
}

/* where the stone statue's sound effects play */
static const Vec16 sekizouSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}}; /* derived name */

void scpSekizou(GObj *self, int flag, int anim, int anim2, int kind, float bx, float by, float bz,
                float gx, float gy, float gz)
{
    if (gflagChk(flag) != 0) {
        stage_SetAnimation(anim, 0, -1);
        return;
    }
    stage_SetAnimation(anim, 0, 0);
    if (girlGObj == 0) {
        return;
    }
    for (;;) {
        if (scpTriggerBall(self, girlGObj, 200.0f) == 0 ||
            scpTriggerBall(self, boyGObj, 200.0f) == 0 ||
            ForMotionViewer_GetCurrentMotion(boyGObj) == 83) {
            _ACTWait(1);
        } else {
            break;
        }
    }
    scpSekizouCheckPoint();
    scpAdpcmPlayRequestFunc(kind, 0, 1, 1, 1);
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    _ACTWait(30);
    scpKillEnemyAll();
    scpMaskGeneratorAll();
    stage_SetAnimation(anim, 1, 0);
    sekizo_yure = iosPadActRequest(boyPad, 9);
    sekizo_yure_vol = 128;
    iosPadActVolumeSet(sekizo_yure, 128);
    actCreateSubThread(actSubSekizoSe, 21);
    scpPlayStart(girlGObj);
    scpPlayMot(girlGObj, 521);
    scpPlayPosSet(girlGObj, gx, gy, gz);
    scpPlayPosSet(boyGObj, bx, by, bz);
    _ACTWait(1);
    {
        Vec16 v;

        sceVu0SubVector(v.f, test_CURRENTROOT(self), test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, v.f);
        scpBoyControlReadDisable = 1;
        sceVu0SubVector(v.f, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
        scpPlayMotDir(boyGObj, v.f);
        scpPlayMot(girlGObj, 584);
        scpPlayWaitMotEnd(girlGObj);
        gflagOn(flag);
        if (anim2 != 0) {
            int h;

            stage_SetAnimation(anim2, 1, 0);
            v = sekizouSePos;
            soundSeDefPlay(1170, 0, v.f, 1);
            _ACTWait(30);
            h = soundSeDefPlay(1171, 0, v.f, 1);
            _ACTWait(30);
            soundSeDefStop(h);
            soundSeDefPlay(1172, 0, v.f, 1);
        }
    }
    while (stage_CheckAnimationFinish(anim) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActStop(sekizo_yure);
    scpPlayMot(girlGObj, 521);
    scpPlayEnd(girlGObj);
    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
}

/* the root position a direct stage change parks the actor at, far out of the map */
static const Vec16 farRootPos = {{-1000000.0f, 0.0f, 0.0f, 0.0f}}; /* derived name */

void _SCPBoySupportGirl(float x0, float y0, float z0, float x1, float y1, float z1)
{
    float v0[4] = {x0, y0, z0};
    float v1[4] = {x1, y1, z1};
    WallCfg *wc;

    if (boyGObj == 0 || girlGObj == 0) {
        return;
    }
    sceVu0ScaleVector(v0, v0, -1.0f);
    sceVu0ScaleVector(v1, v1, -1.0f);
    wc = scpGetWallCollision(v0[0], v0[1], v0[2], v1[0], v1[1], v1[2]);
    if (wc != 0) {
        GOBJ_ACT(boyGObj)->env.supportReq.b.wall = *wc;
        GOBJ_ACT(girlGObj)->env.supportReq.a.wall = *wc;
        iosOmSendMail(boyGObj, 337, boyGObj);
        iosOmSendMail(girlGObj, 338, boyGObj);
    }
}

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

inline void scpWakeupEnemyAll(void)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 31, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(59); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 31, g);
    }
}

inline void scpSleepEnemyAll(void)
{
    GObj *g;
    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 32, g);
    }
    for (g = isysGObjSearchFromObjKindID_begin(59); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 32, g);
    }
}

inline void scpKillEnemyAll(void)
{
    GObj *g;

    for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 37, g);
        objLayout[g->labelId].reviveCount = 0;
    }
    for (g = isysGObjSearchFromObjKindID_begin(59); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        iosOmSendMail(g, 37, g);
    }
}

inline void scpMaskGeneratorAll(void)
{
    GObj *p = isysGObjSearchFromObjKindID_begin(33);
    while (p != 0) {
        Generator_Mask(p);
        p = isysGObjSearchFromObjKindID_next(p);
    }
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

inline int scpCheckReadyAllObjects(void)
{
    return CheckReadyAllSwitches() != 0;
}

/* the colour the item-revival boundary's wire sphere is drawn in */
static const Col4 itemBoundaryColor = {{0, 32, 16, 128}}; /* derived name */

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

inline int scpAdpcmFadeClose(SqEntry *p, short fade)
{
    if (p == 0 || p->stream == 0) {
        return 0;
    }
    p->stream->fadeStep = fade;
    return 1;
}

inline int scpAdpcmCloseChk(SqEntry *p)
{
    if (p == 0 || p->stream == 0 || p->stream->bg == 0) {
        return 0;
    }
    return 1;
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

inline int _SCPMoveCharactorByWay(GObj *self, int tgt, float *dir, float speed, int flags)
{
    Act *act = GOBJ_ACT(self);

    act->flags18.ll |= 1ULL << 41;
    ACTCharctrl_Lock(self);
    ACTSendMailCorrect(self, 237);
    ACTWayExec_Position(self, tgt, dir, speed, flags);
    act->flags18.ll &= ~(1ULL << 41);
    ACTCharctrl_Unlock(self);
    return 0;
}

inline int _SCPMoveByWay_ToChar(GObj *self, GObj *target, int deg, int flags, float scale,
                                float speed)
{
    float v[4];
    float w[4];

    v[0] = test_CURRENTORIENT(target)[0];
    v[1] = test_CURRENTORIENT(target)[1];
    v[2] = test_CURRENTORIENT(target)[2];
    _ApplyRyGV(v, (float)deg * 3.1415927f / 180.0f);
    sceVu0ScaleVector(v, v, scale);
    sceVu0AddVector(w, test_CURRENTROOT(target), v);
    return _SCPMoveCharactorByWay(self, (int)target, w, speed, flags);
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
