#include "typedef.h"
#include "act-game.h"
#include "debug.h"
#include "gamesys.h"
#include "main.h"
#include "sceneManager.h"
#include "act-env.h"
#include "act-wish.h"
#include "girl_act.h"
#include "stage_orient.h"
#include "mail-add-data.h"
#include "script.h"
#include "StageAnimation.h"
#include "clipCollisionManager.h"
#include "matrixDrive.h"
#include "motionManager.h"
#include "motionOrientManager.h"
#include "camera-editor.h"
#include "multiBgaManager.h"
#include "quaternion.h"
#include <stdlib.h>
#include "motionManager2.h"
#include "geometryManager.h"
#include "act-parallel-control.h"
#include "brain.h"
#include <string.h>
#include "gflag.h"
#include "Matrix.h"
#include "debug_exception.h"
#include <libvu0.h>
#include "enemy_act.h"
#include "gobj.h"
#include "act_bird.h"
#include "item.h"
#include "commonact.h"
#include "obj_manager.h"
#include "gv.h"
#include "fieldCollision.h"
#include <assert.h>
#include "poly-flat.h"
#include "act.h"
#include "brain.h"
#include "include_asm.h"

/* weapon.h's WeaponDef, which this TU does not include (CheckWeaponKind
   differs): the weapon kind's motion orient at 0x1C */
typedef struct { /* field names derived */
    char pad0[28];
    int motOrient;
    char pad20[4];
} WeaponEntry; /* derived name */

typedef struct { /* field names derived */
    long long w;
} __attribute__((packed)) U64ag; /* derived name */

/* The 0x194-byte-per-entry motion record table, indexed by the object's
   current motion id (obj->0x15C->0x4A0); the fields this TU reads, named as
   motionOrientManager.h's MotionDef. */
typedef struct { /* field names derived */
    char pad0[336];
    int playMode;
    char pad154[44];
    short priInputBegin;
    short girlDirFrames;
    short priInputEnd;
    char pad186[2];

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;

        char b;
    } modeBits;

    unsigned int flags;
    unsigned int flags2;
} MotionRec; /* derived name */

extern MotionRec motionKind[];

typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4S; /* derived name */

/* as in boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void SetBoyInfo(GObj *weapon, GObj *item);
/* as in boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void BoyInfoUpdate_StageChange(void);

/* One table: a 100-entry object list, two parallel per-entry int arrays
   (the full view result and the simple one), the entry count and the
   round-robin cursor the loop below advances one entry per frame. */
typedef struct {     /* field names derived */
    GObj *obj[100];  /* 0x000 */
    int view[100];   /* 0x190 */
    int simple[100]; /* 0x320 */
    int num;         /* 0x4B0 */
    int cur;         /* 0x4B4 */
} ActGameViewTbl;    /* derived name */

/* the view table described below, the tail of act-game.o's .bss; no code
   reaches the 0x440 bytes ahead of it */
static ActGameViewTbl actGameView; /* derived name */

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* the motion-play-speed-ratio mode at work+0x54, which
   ACTGame_SetMotionPlaySpeedRatio_Exec dispatches on */
typedef enum { MPSR_OFF, MPSR_ONESHOT, MPSR_HOLD } MpsrMode;

/* self->0x164->0x688, the per-actor motion work block, re-derived at every
   use */
#define ACTWORK(g) ((char *)GOBJ_ACT(g)->work) /* derived name */

/* unprototyped: weapon.h declares CheckWeaponKind(char *), and
   ACTGame_isWeaponCombustible calls it with no argument */
extern int CheckWeaponKind();

/* The actor's orient-request bitfield: three 64-bit request words at
   sub+0x478, each paired with the permission mask 16 bytes further on. */
#define ORQ(s, i) (((ActStatusWord *)((s) + 0x478))[i].q)       /* derived name */
#define ORM(s, i) (((ActStatusWord *)((s) + 0x478))[(i) + 2].q) /* derived name */
#define ORBIT(w, b) ((int)((w) >> (b)) & 1)                     /* derived name */

/* The pair of hand-link wall probes the debug overlay draws, mirrored into
   the actor work area at +0x540; handClInfoClear is the cleared template
   each frame starts from. */
typedef struct {        /* field names derived */
    unsigned char on;   /* 0x00 */
    unsigned char hit;  /* 0x01 */
    unsigned char attr; /* 0x02 */
    char pad3[13];
    long long orient[2]; /* 0x10 -- GetOrientOfWall's output */
    unsigned char hit2;  /* 0x20 */
    unsigned char attr2; /* 0x21 */
    char pad22[14];
    long long orient2[2]; /* 0x30 */
} HandClInfo;             /* derived name */

static HandClInfo handClInfoClear = {0}; /* derived name */

/* The hand-mode rows the motion record's two hand nibbles index: 16 bytes a
   row, the mode RequestChangeHandMode wants in the last word. */
typedef struct { /* field names derived */
    char pad0[12];
    int mode;
} HandModeRow; /* derived name */

extern HandModeRow motionIKEffKind[];
static void ACTItemWatchMotion(GObj *self);
/* as in boyact.h, which this TU does not include */
extern void PrivInsCamSet(float *pos, float *tgt, GObj *track, int inFrames, int outFrames,
                          float inRate, float blend, unsigned char control);

/* The pending hand-mode command record: two ints at +0x314 (connect) and
   +0x31C (disconnect) of the actor's hand work block. */
typedef struct { /* field names derived */
    int flag;    /* the hand mode set, 0 for none */
    int pri;     /* the priority it was set at */
} HandModeCmd;   /* derived name */

/* as in weapon.h, which this TU does not include (CheckWeaponKind differs) */
extern int GetTorchGObjOfWeapon(GObj *weapon);
extern WeaponEntry weaponKind[];

inline void ACTGameCollisionOff(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 0;
    ((int *)self[0x57])[0x153] = 0;
    ((int *)self[0x57])[0x152] = 0;
    ((int *)self[0x57])[0x1F] = 0;
}

inline void ACTGameCollisionOn(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 1;
    ((int *)self[0x57])[0x153] = 1;
    ((int *)self[0x57])[0x152] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}

void ACTGame_SaveActorInformation(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    if (((int)(s->flags18.ll >> 39) & 1) && s->modeFrame % 30 == 0) {
        gamesysObjInfoPosSetStage(self, s->infoPos, 0, stage_no);
    }
}

void ACTGame_DeleteActorInformation(GObj *self)
{
    gamesysObjInfoCls(self->kind, self->labelId);
}

static void EXITDATA_GetNextPosition(int idx, float *pos, float *rot)
{
    exit_no = idx;
    test_nextstage_firstwalk_set(idx, exitData[idx].firstWalk0, exitData[idx].firstWalk1,
                                 exitData[idx].firstWalk2);

    pos[0] = -exitData[idx].pos[0];
    pos[1] = -exitData[idx].pos[1];
    pos[2] = -exitData[idx].pos[2];

    rot[0] = exitData[idx].rot[0];
    rot[1] = exitData[idx].rot[1];
    rot[2] = exitData[idx].rot[2];

    sceVu0ScaleVector(rot, rot, 0.017453292f);
}

inline void ACTGame_StageChangeGObjID(int no, int kind, int idx)
{
    float tmp_a[4];
    float tmp_b[4];
    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    gamesysObjInfoPosNewStageSet(no, kind, exitData[idx].nextStage, tmp_a, tmp_b);
}

void ACTGame_StageChangeGObj(GObj *self, int idx)
{
    float tmp_a[4];
    float tmp_b[4];
    float buf[4];
    Vec4S buf2;
    Vec4S buf3;

    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    if (self->kind == 0x11) {
        memset(buf, 0, 0x10);
        buf[2] = 250.0f;
        _ApplyRyGV(buf, -tmp_b[1]);
        sceVu0AddVector(tmp_a, tmp_a, buf);
    }
    if (self == girlGObj) {
        if (0.0f <= GOBJ_WORK(self)->escortOffset) {
            memset(&buf3, 0, 0x10);
            buf3.z = -GOBJ_WORK(girlGObj)->escortOffset;
            buf2 = buf3;
            _ApplyRyGV(&buf2.x, -tmp_b[1]);
            sceVu0AddVector(tmp_a, tmp_a, &buf2);
        }
    }
    gamesysObjInfoPosNewStageSet(self->labelId, self->kind, exitData[idx].nextStage, tmp_a, tmp_b);
}

inline void ACTGame_StageChangeGObjDirect(GObj *self, int stage, void *dir, int deg)
{
    float buf0[4];
    float buf1[4];
    memset(buf1, 0, 0x10);
    buf1[1] = (float)deg * 3.1415927f / 180.0f;
    sceVu0ScaleVector(buf0, dir, -1.0f);
    gamesysObjInfoPosNewStageSet(self->labelId, self->kind, stage, buf0, buf1);
}

/* the first exit whose next stage is this one */
static inline int getExitIndexOfStage(int stage) /* derived name */
{
    int i;

    for (i = 0; i < 261; i++) {
        if (exitData[i].nextStage == stage) {
            return i;
        }
    }
    return 0;
}

void ACTGame_SetActors_Debug(int stage, unsigned char flag)
{
    GObj *boy;
    GObj *girl;
    int idx;

    boy = 0;
    girl = 0;
    idx = getExitIndexOfStage(stage);
    gflagOn(394);
    if (flag != 0) {
        if (boyGObj != 0) {
            Act *s = GOBJ_ACT(boyGObj);
            boy = s->weapon;
            girl = s->curItem;
            SetBoyInfo(boy, girl);
            BoyInfoUpdate_StageChange();
        }
    }
    {
        int hasBoy = stageData[stage].attrTop;
        int hasGirl = stageData[stage].flag0;
        int tbl[4][3] = {
            {54, 1, hasBoy},
            {148, 2, hasGirl},
            {55, 14, hasBoy},
            {-1, -1},
        };
        float pos[4];
        float rot[4];
        int n;
        int cur;
        int obj;
        int chk;

        EXITDATA_GetNextPosition(idx, pos, rot);
        for (n = 0; tbl[n][0] != -1; n++) {
            cur = tbl[n][0];
            obj = tbl[n][1];
            chk = tbl[n][2];
            if (n == 2 && boy != 0) {
                break;
            }
            if (chk != 0) {
                if (!(cur < stageData[stage].labelTop) && cur < stageData[stage].labelEnd &&
                    gamesysObjInfoGet(obj, cur) == 0) {
                    debug_StdPrintfDummy("first\n");
                } else {
                    debug_StdPrintfDummy("set\n");
                    gamesysObjInfoPosNewStageSet(cur, obj, stage, pos, rot);
                }
                if (cur == 54) {
                    if (boy != 0) {
                        gamesysObjInfoPosNewStageSet(boy->labelId, boy->kind, stage, pos, rot);
                    }
                    if (girl != 0) {
                        gamesysObjInfoPosNewStageSet(girl->labelId, girl->kind, stage, pos, rot);
                    }
                }
            }
        }
    }
}

inline int ACTGame_FLAG_LIFEPINCH(GObj *self)
{
    if (GOBJ_ACT(self)->life <= 20.0f)
        return 1;
    return 0;
}

/* Returns a char-width boolean, through an `int` intermediate. */
inline unsigned char ACTGame_FLAG_TETSUNAGI(void)
{
    GObj *g = girlGObj;
    int flag;
    if (g == 0)
        return 0;
    flag = (int)(GOBJ_ACT(g)->flags18.ll >> 40) & 1;
    return flag;
}

inline int ACTGame_FLAG_TETSUNAGI_VISUAL(void)
{
    GObj *g = girlGObj;
    if (g == 0)
        return 0;
    return (int)(GOBJ_ACT(g)->flags18.ll >> 42) & 1;
}

void ACTGame_TryConnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 5, 5, girlGObj, 0, 0);
}

void ACTGame_TryDisconnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 5, 0, 0, 0, 0);
}

inline void ACTGame_ConnectHand(void)
{
    Act *s = GOBJ_ACT(((char *)girlGObj));
    RequestChangeHandMode(girlGObj, 0, 5, 6, boyGObj, 0, 0);
    RequestChangeHandMode(boyGObj, 1, 5, 5, girlGObj, 0, 0);
    s->flags18.ll |= (1ULL << 40);
}

void ACTGame_DisconnectHand_WithMail(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy("with mail\n");
}

inline void ACTGame_DisconnectHand(void)
{
    Act *s = GOBJ_ACT(((char *)girlGObj));
    RequestChangeHandMode(girlGObj, 0, 5, 0, 0, 0, 0);
    RequestChangeHandMode(boyGObj, 1, 5, 0, 0, 0, 0);
    s->flags18.ll &= ~(1ULL << 40);
}

inline void PAIR_GetPosition_BOY_DITCH(float *pos, float *dir)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    pos[0] = q[0x510 / 4];
    pos[1] = q[0x514 / 4];
    pos[2] = q[0x518 / 4];
    dir[0] = q[0x520 / 4];
    dir[1] = q[0x524 / 4];
    dir[2] = q[0x528 / 4];
}

inline void PAIR_GetPosition_BOY(float *pos, float *dir)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    pos[0] = q[0x500 / 4];
    pos[1] = q[0x504 / 4];
    pos[2] = q[0x508 / 4];
    dir[0] = q[0x4C0 / 4];
    dir[1] = q[0x4C4 / 4];
    dir[2] = q[0x4C8 / 4];
}

inline int PAIR_IsStatus_BOY_PULL(void)
{
    switch ((unsigned int)GOBJ_ACT(boyGObj)->actMode) {
    case 0x4E:
    case 0x4F:
        return 1;

    case 1:
    case 2:
    case 3:
        if (ACTGame_FLAG_TETSUNAGI()) {
            return 1;
        }
        break;
    }
    return 0;
}

inline int PAIR_IsStatus_GIRL_PULL(void)
{
    switch ((unsigned int)GOBJ_ACT(((char *)girlGObj))->actMode) {
    case 4:
    case 0x45:
    case 0x50:
    case 0x51:
        return 1;

    case 1:
    case 2:
    case 3:
        if (ACTGame_FLAG_TETSUNAGI()) {
            return 1;
        }
        break;
    }
    return 0;
}

inline int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout)
{
    ClipWork work;
    int flag;
    int rv;

    memset(&work, 0, sizeof(work));
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work.radius = f;
    sceVu0CopyVector(work.pt[0], p0);
    sceVu0CopyVector(work.pt[1], p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (work.wall.elem == 0) {
        ClipFloor(&work);
        if (work.floor.elem == 0) {
            rv = 0;
        }
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work.pt[2][0];
        *(float *)((char *)posout + 4) = work.pt[2][1];
        *(float *)((char *)posout + 8) = work.pt[2][2];
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv & 0xFF;
}

inline int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout,
                            void *magtarget, int *flagout)
{
    ClipWork work;
    int flag;
    int rv;
    struct FcWallEnt *wall;

    memset(&work, 0, sizeof(work));
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work.radius = f;
    sceVu0CopyVector(work.pt[0], hand0);
    sceVu0CopyVector(work.pt[1], hand1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (flagout != 0) {
        *flagout = work.attr;
    }
    wall = work.wall.elem;
    if (wall == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work.pt[2][0];
        *(float *)((char *)posout + 4) = work.pt[2][1];
        *(float *)((char *)posout + 8) = work.pt[2][2];
    }
    if (wall != 0 && magtarget != 0) {
        GetOrientOfWall(magtarget, wall, &work.wall.o);
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv & 0xFF;
}

inline int ACTCheckCollis_CI(float *start, float *end, int *attr, WallCfg *wallHit)
{
    ClipWork buf;
    memset(&buf, 0, 0xC0);
    buf.radius = 0;
    sceVu0CopyVector(buf.pt[0], start);
    sceVu0CopyVector(buf.pt[1], end);
    ClipWall(&buf);
    if (attr != 0) {
        *attr = buf.attr;
    }
    if (wallHit != 0) {
        wallHit->o = buf.wall.o;
        wallHit->elem = buf.wall.elem;
    }
    return buf.wall.elem != 0;
}

void *floorGObj_ACTCheckCollis_WELL;

void *wallGObj_ACTCheckCollis_WAY;

/* the float is the last parameter */
inline int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f)
{
    ClipWork work;
    int flag;
    int rv;

    memset(&work, 0, sizeof(work));
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work.radius = f;
    floorGObj_ACTCheckCollis_WELL = 0;
    sceVu0CopyVector(work.pt[0], p0);
    sceVu0CopyVector(work.pt[1], p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipFloor(&work);
    if (work.floor.elem == 0) {
        rv = 0;
    } else {
        floorGObj_ACTCheckCollis_WELL = work.floor.o.obj;
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work.pt[2][0];
        *(float *)((char *)posout + 4) = work.pt[2][1];
        *(float *)((char *)posout + 8) = work.pt[2][2];
    }
    return rv;
}

inline unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout)
{
    ClipWork work;
    int flag;
    int attr;

    memset(&work, 0, sizeof(work));
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work.radius = f;
    wallGObj_ACTCheckCollis_WAY = 0;
    sceVu0CopyVector(work.pt[0], p0);
    sceVu0CopyVector(work.pt[1], p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    attr = work.attr;
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    /* the wall record is published on both paths */
    if (work.wall.elem == 0) {
        if (flag != 0) {
            GOBJ_SUB(actor)->disp = 0;
        }
        ClipWallField(&work);
        if (flag != 0) {
            GOBJ_SUB(actor)->disp = 1;
        }
        if (work.wall.elem == 0) {
            return 0;
        }
        wallGObj_ACTCheckCollis_WAY = work.wall.o.obj;
    } else {
        wallGObj_ACTCheckCollis_WAY = work.wall.o.obj;
    }
    if (CompareAttribute(attr, 0x30000) != 0) {
        return 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work.pt[2][0];
        *(float *)((char *)posout + 4) = work.pt[2][1];
        *(float *)((char *)posout + 8) = work.pt[2][2];
    }
    return 1;
}

inline unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor)
{
    ClipWork work;
    int flag;
    int rv;

    memset(&work, 0, sizeof(work));
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;

    if (!(_DistSqGV((int *)p0, p1) < 25000000.0f)) {
        return 1;
    }

    work.radius = f;
    sceVu0CopyVector(work.pt[0], p0);
    sceVu0CopyVector(work.pt[1], p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (work.wall.elem == 0) {
        ClipFloor(&work);
        if (work.floor.elem == 0) {
            rv = 0;
        }
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv;
}

int ACTCheckView(GObj *self, void *target, void *targetPos, int range, float f)
{
    float pos[4];
    float v[4];
    float d[4];
    float *m;
    int n;

    n = GetSkeltonFocusNode(self, 35) << 6;
    m = (float *)(n + GOBJ_SUB(self)->nodeMtx);
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    if (_DistGV(pos, targetPos) < f) {
        return 1;
    }
    if (range >= 360) {
        return 1;
    }
    /* each arm a three-component vector set; v[3] is zeroed on the next
       line */
    if (*(int *)((char *)self + 0xC) == 4) {
        v[0] = 0.0f;
        v[1] = -1.0f;
        v[2] = 0.0f;
    } else {
        v[0] = 0.0f;
        v[1] = 1.0f;
        v[2] = 0.0f;
    }
    v[3] = 0.0f;
    sceVu0ApplyMatrix(v, (char *)GOBJ_SUB(self)->nodeMtx + n, v);
    sceVu0SubVector(d, targetPos, pos);
    if (0.8f < (v[1] < 0.0f ? -v[1] : v[1])) {
        v[0] = test_CURRENTORIENT(self)[0];
        v[1] = test_CURRENTORIENT(self)[1];
        v[2] = test_CURRENTORIENT(self)[2];
    }
    if (range / 2 < (_RotyGV(v, d) < 0 ? -_RotyGV(v, d) : _RotyGV(v, d))) {
        return 0;
    }
    return 1;
}

inline int ACTCheckViewCl(GObj *self, void *target, void *targetPos, int range, float f)
{
    float pos[4];
    float *m;
    int n;

    if (*(int *)((char *)self + 0xC) == 4) {
        return 1;
    }
    n = GetSkeltonFocusNode(self, 35) << 6;
    m = (float *)(n + *(int *)((int)((GObj *)(self))->dobj + 0xC));
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    if (ACTCheckView(self, target, targetPos, range, f) == 0) {
        return 0;
    }
    return ACTCheckCollis_VIEW(0.0f, pos, targetPos, target) == 0;
}

inline int ACTCheckViewClDetail(GObj *self, void *target, void *targetPos, int range, float f)
{
    float pos[4];
    float *m;
    int n;
    int ret;

    if (*(int *)((char *)self + 0xC) == 4) {
        return 1;
    }
    n = GetSkeltonFocusNode(self, 35) << 6;
    m = (float *)(n + *(int *)((int)((GObj *)(self))->dobj + 0xC));
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    ret = ACTCheckView(self, target, targetPos, range, f);
    if (ACTCheckCollis_VIEW(0.0f, pos, targetPos, target)) {
        return 0;
    }
    if (ret != 0) {
        return 1;
    }
    return 2;
}

/* actGameView is one table: a 100-entry object list at +0x000, two parallel
   100-entry int arrays at +0x190 and +0x320, and the entry count at +0x4B0. */
inline void ACTGameView_Init(void)
{
    actGameView.num = 0;
    actGameView.cur = 0;
}

/* The view work record is reached as `self->act->view`, its two chase loads
   read as int. */
INCLUDE_ASM(ACTGameView_Loop);

inline int ACTGameView_Check(GObj *self, GObj *obj)
{
    int i;
    for (i = 0; i < actGameView.num; i++) {
        if (actGameView.obj[i] == obj) {
            return *(unsigned char *)&actGameView.view[i];
        }
    }
    return 0;
}

inline int ACTGameViewSimple_Check(GObj *self, GObj *obj)
{
    int i;
    for (i = 0; i < actGameView.num; i++) {
        if (actGameView.obj[i] == obj) {
            return *(unsigned char *)&actGameView.simple[i];
        }
    }
    return 0;
}

INCLUDE_ASM(ACTGame_LwsEffectProcess);

inline void ACTGame_LwsEffectInit(GObj *self)
{
    GOBJ_ACT(self)->enemy->lwsEffect = InitMultiBgaManager(1);
}

inline void ActGame_GetOrientQ(void *q, void *v, int deg)
{
    float tmp[4];
    int n;

    sceVu0ScaleVector(tmp, v, -1.0f);
    n = (int)(_GetDirection(tmp) / 3.1415927f * 180.0f) + deg;
    SetIdentityQuaternion(q);
    RotQuaternionY(q, (short)(n * 32768 / 180));
}

inline void ACTCharctrl_Lock(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    s->flags18.ll &= ~(1ULL << 48);
    s->flags18.ll &= ~(1ULL << 49);
}

inline void ACTCharctrl_Unlock(GObj *self)
{
    Act *p = GOBJ_ACT(self);
    p->flags18.ll |= (1ULL << 48);
    p->flags18.ll |= (1ULL << 49);
}

inline GObj *ACTGame_GetNearestGObj(float *pos, int kind)
{
    float best_val = 3.40282347e+38f; /* FLT_MAX */
    GObj *best = 0;
    GObj *node;

    node = isysGObjSearchFromObjKindID_begin(kind);
    if (node != 0) {
        do {
            float val = _DistSqGV(test_CURRENTROOT(node), pos);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
    return best;
}

inline void _GetRootObjectOrient(void *orient, GObj *obj)
{
    float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    sceVu0ApplyMatrix(orient, (void *)GOBJ_SUB(obj)->nodeMtx, v);
}

inline int ACTGame_isWeaponEnableCatchfire(GObj *self)
{
    int ret = 0;
    unsigned long combustible = ACTGame_isWeaponCombustible();
    if (combustible) {
        ret = GetTorchGObjOfWeapon(self);
    }
    return ret;
}

inline GObj *ACTGame_isHangChain(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    if (self == boyGObj) {
        const ActModeRec *attr = &actModeTbl[s->actMode];
        if (attr->onChain) {
            return s->chain;
        }
    }
    return 0;
}

inline int ACTGame_GetMotOrientFromWeapon(GObj *weapon)
{
    int rv;
    if (weapon != 0) {
        rv = weaponKind[CheckWeaponKind(weapon)].motOrient;
    } else {
        rv = 0;
    }
    return rv;
}

inline unsigned char ACTGame_NoWeapon(GObj *self)
{
    GObj *w = GOBJ_ACT(self)->weapon;
    unsigned char r = 0;
    if (w == 0 || CheckWeaponKind(w) == 0)
        r = 1;
    return r;
}

inline int ACTGame_isWeaponCombustible(void)
{
    return CheckWeaponKind() == 1;
}

/* both absolute values are written as `((x) < 0 ? -(x) : (x))` */
int _ACTGame_SearchGObj(GObj *self, GObj *tgt, float range, float height, int angle, float *out)
{
    float buf[4];
    int n;

    if (!(_DistxzSqGV(test_CURRENTROOT(self), test_CURRENTROOT(tgt)) < range * range)) {
        return 0;
    }
    if ((test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1] < 0.0f
             ? -(test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1])
             : test_CURRENTROOT(self)[1] - test_CURRENTROOT(tgt)[1]) < height) {
        sceVu0SubVector(buf, test_CURRENTROOT(tgt), test_CURRENTROOT(self));
        n = _RotyGV(buf, test_CURRENTORIENT(self)) < 0 ? -_RotyGV(buf, test_CURRENTORIENT(self))
                                                       : _RotyGV(buf, test_CURRENTORIENT(self));
        if (n < angle) {
            out[0] = buf[0];
            out[1] = buf[1];
            out[2] = buf[2];
            return 1;
        }
    }
    return 0;
}

inline void ACTLookTarget_Init(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    s->lookTarget = 0;
    s->lookMode = 0;
    s->lookPri = 0;
}

inline int _ACTLookTarget_Set(GObj *self, GObj *target, float *pos, int pri, int mode)
{
    Act *s = GOBJ_ACT(self);
    int ret = 0;

    if (pri == 6) {
        ACTLookTarget_Init(self);
    } else if (pri >= s->lookPri) {
        s->lookTarget = target;
        if (pos != 0) {
            s->lookPosX = pos[0];
            s->lookPosY = pos[1];
            s->lookPosZ = pos[2];
        }
        s->lookMode = mode;
        s->lookPri = pri;
        ret = 1;
    }
    return ret;
}

int ACTLookTarget_Exec(GObj *self)
{
    float pos[4];
    Act *s = GOBJ_ACT(self);
    GObj *t = s->lookTarget;
    int rv;
    int b0;

    if (debug_font_flag & 1) {
        debug_Printf(10, 170, 0x0FFFFFFF, "mode=[%d]\n", GOBJ_SUB(self)->root.lookMode);
    }
    rv = 0;
    if (s->lookPri == 0) {
        GOBJ_SUB(self)->root.lookMode = 0;
    } else {
        if (t == 0) {
            pos[0] = s->lookPosX;
            pos[1] = s->lookPosY;
            pos[2] = s->lookPosZ;
        } else if (t == boyGObj) {
            /* the boy's skeleton position read in place */
            int idx = GetSkeltonFocusNode(t, 35) << 6;
            pos[0] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x30);
            pos[1] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x34);
            pos[2] = *(float *)(idx + *(int *)(((IntFloat *)&t->dobj)->i + 0xC) + 0x38);
        } else {
            GetRootPosition(pos, t);
        }
        b0 = s->lookMode;
        rv = 1;
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x390))->f = pos[0];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x394))->f = pos[1];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x398))->f = pos[2];
        GOBJ_SUB(self)->root.lookMode = b0;
    }
    return rv;
}

inline void ACTParaStatus_Init(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    ActPara_InitSystem();
    ACTParaStatus_Clear(self);
    ActPara_MakeTbl(GOBJ_WORK(self)->paraTbl, s->paraStatus, 0);
    *(long long *)((char *)s + 0x98) = s->paraStatus;
}

void ACTParaStatus_Clear(GObj *self)
{
    GOBJ_ACT(self)->paraStatus = 0;
    _ACTParaStatus_Set(self, 0);
}

inline void _ACTParaStatus_Set(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);
    *(unsigned long long *)((char *)s + 0x90) |= (1ULL << bit) & ~(unsigned long long)s->flags;
}

inline unsigned long long _ACTParaStatus_Check(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);
    return ((unsigned long long)s->paraStatus >> bit) & 1;
}

INCLUDE_ASM(ACTParaStatus_Exec);

inline void _ACTCharStatus_Init(int **self)
{
    long long *p = (long long *)self[0x59];
    p[0xB] = 0;
    p[0xC] = 0;
}

void _ACTCharStatus_Clear(void *self)
{
    Act *s = GOBJ_ACT(self);
    int old = s->statusOther;
    int *sel;
    int *g;
    float nearest;
    float d;

    memset((char *)s + 0x58, 0, 0x38);
    if (self == (char *)boyGObj || self == ((char *)girlGObj)) {
        nearest = 3.40282347e+38f; /* FLT_MAX */
        sel = 0;
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            d = _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(g));
            if (actEnemyFlagCheckActive(g)) {
                if (d < nearest) {
                    sel = g;
                    nearest = d;
                }
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        *(int **)((char *)s + 0x7C) = sel;
        if (self == (char *)boyGObj) {
            if (old != 0 && s->frame % ((60 - systemStatus[0] * 10) / systemStatus[1] * 2) != 0) {
                s->statusOther = old;
            }
        }
    }
}

inline void _ACTCharStatus_Set(GObj *self, int bit, float f, int val)
{
    Act *s = GOBJ_ACT(self);

    *(long long *)((char *)s + 0x58) |= 1LL << bit;

    switch (bit) {
    case 8:
        s->statusWait8 = f;
        break;

    case 5:
        s->statusWait5 = f;
        break;

    case 17:
        s->statusVal17 = f;
        break;

    case 18:
        s->statusVal18 = val;
        break;

    case 10:
        s->statusTarget = val;
        break;

    case 2:
        s->statusOther = val;
        break;

    case 11:
        s->statusObj = val;
        break;
    }
}

inline unsigned char _ACTCharStatus_Check(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);
    int r;

    if ((char *)s != 0) {
        r = (*(unsigned long long *)((char *)s + 0x58) >> bit) & 1;
        if (r != 0) {
            return 1;
        }
    }
    return 0;
}

inline void _ACTCharStatus_Exec(void) {}

inline void ACTGame_SetMotionPlaySpeedRatio_Clear(GObj *self)
{
    EnemyBattleWork *p = GOBJ_ACT(self)->enemy;
    p->speedRatio = 1.0f;
    *(MpsrMode *)((char *)p + 0x54) = MPSR_OFF;
}

inline void ACTGame_SetMotionPlaySpeedRatio_Reserve(GObj *self, float ratio, unsigned int pri)
{
    EnemyBattleWork *p = GOBJ_ACT(self)->enemy;
    if (p->speedRatioPri <= pri) {
        p->speedRatio = ratio;
        p->speedRatioPri = pri;
    }
}

/* The play-speed ratio's debug override, built only when DEBUG is defined:
   the debug build can fix the ratio from the debugger before it is applied;
   the retail build leaves the helper without a body. */
static __inline__ void speedRatioDebugOverride(float *ratio) /* derived name */
{
#ifdef DEBUG
    if (dbgSpeedRatioFix) {
        *ratio = dbgSpeedRatio;
    }
#endif
}

inline void SetDirectRootPositionWithNodePointLimit(void *self, int node, void *pos, float t,
                                                    float limit)
{
    float buf0[4];
    float buf18[4];
    float buf16[4];

    GetSkeltonPosition(buf0, self, node);
    sceVu0SubVector(buf16, pos, buf0);
    if (limit < FSqrt(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        sceVu0Normalize(buf16, buf16);
        sceVu0ScaleVector(buf16, buf16, limit);
        sceVu0AddVector(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *)((char *)pos + 4)) {
            buf18[1] = *(float *)((char *)pos + 4);
        }
        SetDirectRootPositionNoFittingWithNodePoint(self, node, buf18, 1.0f);
        return;
    }
    SetDirectRootPositionNoFittingWithNodePoint(self, node, pos, t);
}

void GetSkeltonOrient(float *out, void *obj, int node)
{
    int n = GetSkeltonFocusNode(obj, node);
    if (((GObj *)obj)->kind == 4) {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = -1.0f;
        *(int *)((char *)out + 0x8) = 0;
    } else {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = 1.0f;
        *(int *)((char *)out + 0x8) = 0;
    }
    *(int *)((char *)out + 0xC) = 0;
    sceVu0ApplyMatrix(out, (char *)(GOBJ_SUB(obj)->nodeMtx + (n << 6)), out);
}

inline void GetSkeltonPosition(float *dst, GObj *obj, int node)
{
    int idx = GetSkeltonFocusNode(obj, node) << 6;
    dst[0] = *(float *)(idx + *(int *)(((IntFloat *)((char *)obj + 0x15C))->i + 0xC) + 0x30);
    dst[1] = *(float *)(idx + *(int *)(((IntFloat *)((char *)obj + 0x15C))->i + 0xC) + 0x34);
    dst[2] = *(float *)(idx + *(int *)(((IntFloat *)((char *)obj + 0x15C))->i + 0xC) + 0x38);
}

/* the bird broadcast, between GetSkeltonPosition and
   ACTGame_InnerVelocityUpdate */
static inline void actGame_SendMailToBirds(GObj *self) /* derived name */
{
    float other[4];
    float mine[4];
    GObj *bird;
    int mail;

    Act *s = GOBJ_ACT(self);
    bird = isysGObjSearchFromObjKindID_begin(32);
    mail = 423;
    if (s->actMode == 3) {
        mail = 424;
    }
    GetRootPosition(mine, self);
    while (bird != 0) {
        GetRootPosition(other, bird);
        if (_DistSqGV((int *)mine, other) < 160000.0f) {
            _ACTSendMailToBird(bird, mail, self);
        }
        bird = isysGObjSearchFromObjKindID_next(bird);
    }
}

/* The speed is computed before the parameter block is fetched, both hops of
   that fetch going through one pointer variable; the pos stores go through
   it and the two thresholds test the speed itself. */
INCLUDE_ASM(ACTGame_InnerVelocityUpdate);

inline int ACTNotNeedCameraOffset(GObj *self)
{
    Act *s;
    if (self != 0 && self == boyGObj) {
        s = GOBJ_ACT(self);
        if ((char *)s != 0) {
            return (int)(s->flags20.ll >> 41) & 1;
        }
    }
    return 0;
}

INCLUDE_ASM(ACTGame_BeforeFunc);

/* OR the 16 pending-request bytes into the live request bytes. */
static inline void actEnv_OrRequestBytes(unsigned char *dst, unsigned char *src) /* derived name */
{
    int i;

    for (i = 15; i >= 0; i--, dst++, src++) {
        *dst |= *src;
    }
}

/* masks the 16-byte request-flag block in place */
static inline void andRequestFlags(char *d, char *m) /* derived name */
{
    int i;
    for (i = 15; i >= 0; i--) {
        *d = *d & *m;
        d++;
        m++;
    }
}

static void FunctionAboutClingedStatus(GObj *self)
{
    int buf[4];
    Act *s;
    GObj *g;
    int clinged;
    int mode;
    int st;
    EnemyBattleWork *p;
    unsigned char cl;

    clinged = 0;
    mode = 0;
    s = GOBJ_ACT(self);
    g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        if (self == actEnemy_GetClingTarget(g)) {
            clinged = 1;
            break;
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    if (clinged != 0) {
        _ACTCharStatus_Set(self, 30, 0.0f, 0);
        _ACTParaStatus_Set(self, 37);
    }
    cl = _ACTCharStatus_Check(self, 30);
    if (cl != 0) {
        st = s->actMode;
        if (st != 0) {
            if ((unsigned int)st >= 4) {
                if (st == 15) {
                    mode = 1;
                    if (s->modeFrame == 0) {
                        p = GOBJ_ACT(self)->enemy;
                        p->clingedFrames += 1;
                        if (GOBJ_ACT(self)->enemy->clingedFrames >= 5) {
                            mode = 2;
                        }
                    }
                }
            } else {
                mode = 1;
            }
        }
    } else {
        GOBJ_ACT(self)->enemy->clingedFrames = 0;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        memset(buf, 0, 0x10);
        buf[0] |= 0x1000;
        andRequestFlags((char *)s + 0x48C, (char *)buf);
        ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 1.0f / ((float)clinged * 0.25f + 1.0f), 6);
        break;
    case 2:
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            if (self == actEnemy_GetClingTarget(g)) {
                iosOmSendMail(g, 0xD6, self);
                break;
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        GOBJ_ACT(self)->enemy->clingedFrames = 0;
        break;
    }
}

INCLUDE_ASM(ACTEnvGetTest);

INCLUDE_ASM(ActOrientTest);

INCLUDE_ASM(GetGirlHandlinkClInfo);

INCLUDE_ASM(hand_able_connect_267);
INCLUDE_ASM(ACTGame_CommonLoop);

inline void GetGirlPositionAtThisStage(float *pos)
{
    float buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(pos, stage_no, id, buf);
}

inline void GetOtherStageGirlOrient(float *orient, float *root)
{
    float pos[4];
    GetGirlPositionAtThisStage(pos);
    _OrientGV(orient, pos, root);
}

void ACTLookTargetSystem_Exec(GObj *self)
{
    char *s = (char *)((int *)self)[89];

    /* GNU nested function GetTarget: it reads `self` and `s` from
       ACTLookTargetSystem_Exec's frame through the static chain. */
    int GetTarget(int kind, float *pos, int *pmode)
    {
        float dir[4];
        float p[4];
        GObj *target = 0;
        int rv = 0;

        switch (kind) {
        case 13:
            GetSkeltonPosition(p, self, 0x23);
            sceVu0ScaleVector(dir, (char *)GOBJ_ACT(self)->work + 0x4A0, 300.0f);
            sceVu0AddVector(pos, p, dir);
            GOBJ_SUB(self)->root.ikRate0 = 0.3f;
            GOBJ_SUB(self)->root.ikRate1 = 0.3f;
            GOBJ_SUB(self)->root.ikRate2 = 0.3f;
            rv = 1;
            break;
        case 12:
            target = *(GObj **)(s + 0x88);
            break;
        case 10:
            target = *(GObj **)(s + 0x78);
            break;
        case 5:
            target = *(GObj **)(s + 0x7C);
            break;
        case 4:
            target = girlGObj;
            if (target == 0 && (*(unsigned long long *)(s + 0x20) & 0x3800000) == 0x800000) {
                GetGirlPositionAtThisStage(pos);
                rv = 1;
            }
            if ((int)(*(unsigned long long *)(s + 0x20) >> 24) & 3) {
                ScpCallCameraGetTarget(pos);
                target = 0;
                rv = 1;
            }
            break;
        case 11:
            GetRootPosition(pos, *(GObj **)(s + 0x74));
            pos[1] = *(float *)&test_CURRENTROOT(self)[1];
            *pmode = 2;
            rv = 1;
            break;
        case 6:
            if ((int)(*(unsigned long long *)(s + 0x20) >> 23) & 1) {
                target = girlGObj;
                *pmode = 2;
                if (target == 0) {
                    GetGirlPositionAtThisStage(pos);
                    rv = 1;
                }
            }
            if ((int)(*(unsigned long long *)(s + 0x20) >> 24) & 3) {
                ScpCallCameraGetTarget(pos);
                target = 0;
                rv = 1;
            }
            break;
        case 8:
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(GObj **)(s + 0x80);
            } else {
                target = boyGObj;
            }
            break;
        case 9:
            target = *(GObj **)(s + 0x84);
            break;
        case 7:
            target = boyGObj;
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(GObj **)(s + 0x80);
            }
            break;
        case 3:
            target = boyGObj;
            break;
        case 1:
            sceVu0ScaleVector(pos, test_CURRENTORIENT(self), 200.0f);
            pos[1] = 0.0f;
            sceVu0AddVector(pos, test_CURRENTROOT(self), pos);
            rv = 1;
            break;
        case 2:
            sceVu0ScaleVector(pos, test_CURRENTORIENT(self), *(float *)(s + 0x5E8));
            pos[1] = 150.0f;
            sceVu0AddVector(pos, test_CURRENTROOT(self), pos);
            rv = 1;
            break;
        case 14:
            pos[0] = GOBJ_WORK(self)->hintPosX;
            pos[1] = GOBJ_WORK(self)->hintPosY;
            pos[2] = GOBJ_WORK(self)->hintPosZ;
            rv = 1;
            break;
        }
        if (target != 0) {
            if (target == boyGObj) {
                /* these two statements written out instead of calling
                   GetSkeltonPosition: the node comes off `target` and the
                   skeleton off the global */
                int idx = GetSkeltonFocusNode(target, 35) << 6;
                ((IntFloat *)pos)[0].f =
                    *(float *)(idx + *(int *)((int)((GObj *)boyGObj)->dobj + 0xC) + 0x30);
                ((IntFloat *)pos)[1].f =
                    *(float *)(idx + *(int *)((int)((GObj *)boyGObj)->dobj + 0xC) + 0x34);
                ((IntFloat *)pos)[2].f =
                    *(float *)(idx + *(int *)((int)((GObj *)boyGObj)->dobj + 0xC) + 0x38);
            } else {
                GetRootPosition(pos, target);
            }
            rv = 1;
        }
        return rv;
    }

    float pos[4];
    int mode = 1;
    int found = 0;
    int col = ((int *)s)[18];
    int flags;
    int i;

    flags = 0;
    if (_ACTCharStatus_Check(self, 32)) {
        flags = 1;
    }
    if (_ACTCharStatus_Check(self, 13)) {
        flags |= 0x10;
    }
    if (_ACTCharStatus_Check(self, 14)) {
        flags |= 0x20;
    }
    if (_ACTCharStatus_Check(self, 28)) {
        if (GOBJ_WORK(self)->boyDist < 300.0f) {
            flags |= 0x40;
        } else {
            flags |= 0x800;
        }
    }
    if (_ACTCharStatus_Check(self, 10)) {
        flags |= 0x800000;
    }
    if (_ACTCharStatus_Check(self, 11)) {
        flags |= 0x1000;
    }
    if (_ACTCharStatus_Check(self, 15)) {
        if (self == (girlGObj)) {
            if ((int)(*(unsigned long long *)(s + 0x20) >> 14) & 1) {
                flags |= 0x200;
            }
        } else {
            flags |= 0x200;
        }
    }
    if (_ACTCharStatus_Check(self, 5)) {
        flags |= 0x20000;
    }
    if (_ACTCharStatus_Check(self, 25)) {
        flags |= 0x400;
    }
    if (_ACTCharStatus_Check(self, 26)) {
        flags |= 0x100;
    }
    if (_ACTCharStatus_Check(self, 31)) {
        flags |= 0x2000;
    }
    if (_ACTCharStatus_Check(self, 3)) {
        flags |= 0x8000;
    }
    if (_ACTCharStatus_Check(self, 2)) {
        flags |= 0x4000;
    }
    if (_ACTCharStatus_Check(self, 6)) {
        flags |= 0x40000;
    }
    if (_ACTCharStatus_Check(self, 7)) {
        flags |= 0x80000;
    }
    if (_ACTCharStatus_Check(self, 33)) {
        flags |= 0x2;
    }
    if (_ACTCharStatus_Check(self, 34)) {
        flags |= 0x4;
    }
    if (_ACTCharStatus_Check(self, 35)) {
        flags |= 0x8;
    }
    if (_ACTCharStatus_Check(self, 4)) {
        flags |= 0x10000;
    }
    if (_ACTCharStatus_Check(self, 27)) {
        flags |= 0x4000000;
    }
    if (_ACTCharStatus_Check(self, 18)) {
        flags |= 0x80;
    }
    if (_ACTCharStatus_Check(self, 12)) {
        flags |= 0x100000;
    }
    if (_ACTCharStatus_Check(self, 0)) {
        flags |= 0x200000;
    }
    if (_ACTCharStatus_Check(self, 1)) {
        flags |= 0x400000;
    }
    if (_ACTCharStatus_Check(self, 17)) {
        if (*(float *)(s + 0x70) < 1000.0f) {
            flags |= 0x1000000;
        }
        if (*(float *)(s + 0x70) < 300.0f) {
            flags |= 0x2000000;
        }
    }
    for (i = 0; i < 27; i++) {
        int kind = lookTargetData[i].kind[col];
        if ((flags >> i) & 1) {
            if (GetTarget(kind, pos, &mode) != 0) {
                found = 1;
                break;
            }
        }
    }
    if (found != 0) {
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x390) = pos[0];
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x394) = pos[1];
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x398) = pos[2];
        *(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x380) = mode;
        if (self == (girlGObj)) {
            debug_NMarker((float *)((char *)(int)GOBJ_SUB(self) + 0x390), 0xFF, 0xFF, 0xFF, 100.0f);
        }
    } else {
        GOBJ_SUB(self)->root.lookMode = 0;
    }
}

inline float _ACTGame_GetParamF(int idx)
{
    return gameParam[idx];
}

inline void ACTGame_SendSoundMail(GObj *self, int mail, GObj *from, int mot, int waitSkip)
{
    switch (mail) {
    case 0x1A0:
        if (waitSkip != 0 && GOBJ_ACT(self)->soundWait > 0) {
            break;
        }
        iosOmSendMail(self, 0x1A0, from);
        if (mot == 0) {
            break;
        }
        {
            Act *act = GOBJ_ACT(self);
            act->soundMot = mot;
            *(unsigned long long *)((char *)act + 0x138) =
                (*(unsigned long long *)((char *)act + 0x138) & ~1ULL) | (waitSkip & 1);
        }
        break;

    case 0x1A1:
        iosOmSendMail(self, 0x1A1, from);
        {
            Act *act = GOBJ_ACT(self);
            act->soundMot = mot;
        }
        break;
    }
}

INCLUDE_ASM(ACTItemThrow_301);
INCLUDE_ASM(ACTItemWatchMotion);

inline void ACTItemForceDrop(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    GObj *item = s->heldItem.p;
    if (item != 0) {
        ReleaseItem(item);
        s->heldItem.i = 0;
        s->nextItem.i = 0;
    }
}

void ACTGame_InsertCamera_GirlIsPinch(void)
{
    float p0[4];
    float p1[4];
    float p2[4];

    if (boyGObj == 0 || ((char *)girlGObj) == 0) {
        return;
    }
    GetRootPosition(p0, boyGObj);
    GetRootPosition(p1, girlGObj);
    if (_DistSqGV((int *)p0, p1) < 22500.0f) {
        return;
    }
    if (IsPointIsInScreen(p2, test_CURRENTROOT(girlGObj)) > 0.0f) {
        return;
    }
    if (boyGObj == 0 || ((char *)girlGObj) == 0) {
        return;
    }
    PrivInsCamSet(test_CURRENTROOT(boyGObj), test_CURRENTROOT((girlGObj)), boyGObj,
                  (60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60,
                  (60 - systemStatus[0] * 10) / systemStatus[1] * 45 / 60, 0.05f, 0.25f, 1);
}

INCLUDE_ASM(updateHMC_314);
INCLUDE_ASM(RequestChangeHandMode);

inline void _ACTSetEnemyDisappearSpeed(GObj *self, float speed)
{
    GOBJ_WORK(self)->disappearSpeed = speed;
}

inline int ACTChkAttackIgnore_BOY(GObj *self, GObj *actor)
{
    Act *s = GOBJ_ACT(self);
    if (s->actMode == 0x35 ||
        (((ActWork *)s->work)->leverTimer != 0 && scpBoyControlReadDisable != 0) ||
        ((int)(s->flags18.ll >> 35) & 1) == 0) {
        return 1;
    }
    return 0;
}

inline int ACTChkAttackIgnore_GIRL(GObj *self, GObj *actor)
{
    Act *s = GOBJ_ACT(self);
    switch (s->actMode) {
    case 0x6F:
        return 1;

    case 5:
        if (actor != 0 && actor->kind == 17) {
            return 1;
        }
        break;
    }
    return 0;
}

INCLUDE_ASM(ACTGame_CheckItemMotion);

INCLUDE_ASM(ACTGame_CheckHandMotion);

INCLUDE_ASM(PAIR_IsStatus_BOY_WAIT);

INCLUDE_ASM(PAIR_IsStatus_BOY_DITCH);

INCLUDE_ASM(ACTGameView_FirstSet);

INCLUDE_ASM(ACTGameView_Add);

INCLUDE_ASM(ACTGame_GetCurrentCallStatus);

INCLUDE_ASM(ACTGame_CheckPriInputFrame);

INCLUDE_ASM(ACTGame_LwsEffect_Guard);

INCLUDE_ASM(ACTChkAttackIgnore_ENEMY);

INCLUDE_ASM(ACTGame_SetMotionPlaySpeedRatio_Exec);
