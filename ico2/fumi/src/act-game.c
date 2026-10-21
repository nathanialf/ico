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
#include "camera-root.h"
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

/* The 0x184-byte-per-entry motion record table (USA 0x190), indexed by the
   object's current motion id (obj->0x15C->0x490); the fields this TU reads,
   named as motionOrientManager.h's MotionDef. */
typedef struct { /* field names derived */
    char pad0[332];
    int playMode;
    char pad150[40];
    short priInputEnd;
    short priInputBegin;

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;

        char b;
    } modeBits;

    unsigned int flags;
} MotionRec; /* derived name */

/* const: the table is in .rodata (sugipon's TUs declare it so); the array
   reads in ACTItemWatchMotion are read-only loads, which lets the delay slot
   of its switch range test take the `self` home store */
extern const MotionRec motionKind[];

typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4S; /* derived name */

/* as in boyact.h, which this TU does not include */
extern void SetBoyInfo(GObj *weapon, GObj *item);
/* as in boyact.h, which this TU does not include */
extern void BoyInfoUpdate_StageChange(void);

/* One table: a 100-entry object list, the parallel per-entry view results,
   the entry count and the round-robin cursor the loop below advances one
   entry per frame (ACTGameView_Init clears the two words at 0x320 and 0x324;
   this build has no second, simple view array). */
typedef struct {    /* field names derived */
    GObj *obj[100]; /* 0x000 */
    int view[100];  /* 0x190 */
    int num;        /* 0x320 */
    int cur;        /* 0x324 */
} ActGameViewTbl;   /* derived name */

/* the view table described below, the tail of act-game.o's .bss; no code
   reaches the 0x440 bytes ahead of it */
static ActGameViewTbl actGameView; /* derived name */

/* the motion-play-speed-ratio mode at work+0x54, which
   ACTGame_SetMotionPlaySpeedRatio_Exec dispatches on */
typedef enum { MPSR_OFF, MPSR_ONESHOT, MPSR_HOLD } MpsrMode;

/* unprototyped: weapon.h declares CheckWeaponKind(char *), and
   ACTGame_isWeaponCombustible calls it with no argument */
extern int CheckWeaponKind();

/* The actor's orient-request bitfield: a 96-bit request set at sub+0x474 and
   its 96-bit permission set at sub+0x480, read as 64-bit words: request bit n
   is bit n + 32 of the words at sub+0x470, its permission bit n of the words
   at sub+0x480 (ORM is ORQ two words on). */
#define ORQ(s, i) (((ActStatusWord *)((s) + 0x470))[i].q)       /* derived name */
#define ORM(s, i) (((ActStatusWord *)((s) + 0x470))[(i) + 2].q) /* derived name */
#define ORBIT(w, b) ((int)((w) >> (b)) & 1)                     /* derived name */

/* The hand-mode rows the motion record's two hand nibbles index: 16 bytes a
   row, the mode RequestChangeHandMode wants in the last word. */
typedef struct { /* field names derived */
    char pad0[12];
    int mode;
} HandModeRow; /* derived name */

extern HandModeRow motionIKEffKind[];
static void ACTItemWatchMotion(GObj *self);

/* The pending hand-mode command record: two ints at +0x314 (connect) and
   +0x31C (disconnect) of the actor's hand work block. */
typedef struct { /* field names derived */
    int flag;    /* the hand mode set, 0 for none */
    int pri;     /* the priority it was set at */
} HandModeCmd;   /* derived name */

/* as in weapon.h, which this TU does not include (CheckWeaponKind differs) */
extern int GetTorchGObjOfWeapon(GObj *weapon);
extern int ReleaseWeaponWithFumbleSequential(GObj *g);
extern WeaponEntry weaponKind[];

inline void ACTGameCollisionOff(volatile int *self)
{
    ((int *)self[0x57])[0x14D] = 0;
    ((int *)self[0x57])[0x14F] = 0;
    ((int *)self[0x57])[0x14E] = 0;
    ((int *)self[0x57])[0x1F] = 0;
}

inline void ACTGameCollisionOn(volatile int *self)
{
    ((int *)self[0x57])[0x14D] = 1;
    ((int *)self[0x57])[0x14F] = 1;
    ((int *)self[0x57])[0x14E] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}

inline int ACTGame_CheckHandMotion(GObj *boy, GObj *girl)
{
    const MotionRec *rec0 = &motionKind[GOBJ_SUB(boy)->ctrl.motion];
    const MotionRec *rec1 = &motionKind[GOBJ_SUB(girl)->ctrl.motion];
    int b0 = (rec0->flags >> 22) & 1;
    int b1 = (rec1->flags >> 22) & 1;
    return b0 & b1;
}

inline int ACTGame_CheckItemMotion(GObj *self)
{
    const MotionRec *rec = &motionKind[GOBJ_SUB(self)->ctrl.motion];
    return rec->modeBits.h.hi & 7;
}

void ACTGame_SaveActorInformation(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    if (((int)(s->flags18.ll >> 34) & 1) && s->modeFrame % 30 == 0) {
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

    for (i = 0; i < 256; i++) {
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
    gflagOn(343);
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
        int hasGirl = stageData[stage].attrTopGirl;
        int tbl[4][3] = {
            {47, 1, hasBoy},
            {124, 2, hasGirl},
            {48, 14, hasBoy},
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
                if (cur == 47) {
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
    flag = (int)(GOBJ_ACT(g)->flags18.ll >> 35) & 1;
    return flag;
}

void ACTGame_TryConnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 4, 5, girlGObj, 0, 0);
}

void ACTGame_TryDisconnectHand(void)
{
    RequestChangeHandMode(boyGObj, 1, 4, 0, 0, 0, 0);
}

inline void ACTGame_ConnectHand(void)
{
    Act *s = GOBJ_ACT(((char *)girlGObj));
    RequestChangeHandMode(girlGObj, 0, 4, 6, boyGObj, 0, 0);
    RequestChangeHandMode(boyGObj, 1, 4, 5, girlGObj, 0, 0);
    s->flags18.ll |= (1ULL << 35);
}

void ACTGame_DisconnectHand_WithMail(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy("with mail\n");
}

inline void ACTGame_DisconnectHand(void)
{
    Act *s = GOBJ_ACT(((char *)girlGObj));
    RequestChangeHandMode(girlGObj, 0, 4, 0, 0, 0, 0);
    RequestChangeHandMode(boyGObj, 1, 4, 0, 0, 0, 0);
    s->flags18.ll &= ~(1ULL << 35);
}

inline unsigned char ACTGame_CheckPriInputFrame(GObj *self)
{
    short e;
    short s;

    e = motionKind[GOBJ_SUB(self)->ctrl.motion].priInputEnd;
    if ((float)e < GOBJ_SUB(self)->ctrl.animFrame && e != -1) {
        return 1;
    }
    s = motionKind[GOBJ_SUB(self)->ctrl.motion].priInputBegin;
    if (s != -1 && GOBJ_SUB(self)->ctrl.animFrame < (float)s) {
        return 1;
    }
    return 0;
}

inline int ACTGame_GetCurrentCallStatus(GObj *self)
{
    Act *s = GOBJ_ACT(self);

    if (s->curItem != 0) {
        return 0;
    }
    switch ((int)((&motionKind[GOBJ_SUB(self)->ctrl.motion])->modeBits.w >> 27) & 3) {
    case 1:
        return 1;
    case 2:
        return 2;
    }
    if (((int)(s->wish0.ll >> 44) & 1) && ((int)(s->wish2.ll >> 12) & 1)) {
        /* a switch on the status as an unsigned index */
        switch ((unsigned int)s->actMode) {
        case 1:
        case 2:
        case 3:
            return 2;
        }
    }
    return 0;
}

inline void PAIR_GetPosition_BOY_DITCH(float *pos, float *dir)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    pos[0] = q[0x500 / 4];
    pos[1] = q[0x504 / 4];
    pos[2] = q[0x508 / 4];
    dir[0] = q[0x4B0 / 4];
    dir[1] = q[0x4B4 / 4];
    dir[2] = q[0x4B8 / 4];
}

inline int PAIR_IsStatus_BOY_DITCH(void)
{
    char *b = (char *)boyGObj;

    switch ((unsigned int)GOBJ_ACT(b)->actMode) {
    case 84:
        if (motionKind[GOBJ_SUB(b)->ctrl.motion].playMode != 1) {
            break;
        }
        /* fall through */
    case 85:
    case 88:
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

inline void PAIR_GetPosition_BOY(float *pos, float *dir)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    pos[0] = q[0x4F0 / 4];
    pos[1] = q[0x4F4 / 4];
    pos[2] = q[0x4F8 / 4];
    dir[0] = q[0x4B0 / 4];
    dir[1] = q[0x4B4 / 4];
    dir[2] = q[0x4B8 / 4];
}

inline int PAIR_IsStatus_BOY_PULL(void)
{
    switch ((unsigned int)GOBJ_ACT(boyGObj)->actMode) {
    case 74:
    case 75:
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
    case 68:
    case 76:
    case 77:
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

inline int PAIR_IsStatus_BOY_WAIT(void)
{
    char *b = (char *)boyGObj;

    if (b != 0) {
        switch ((unsigned int)GOBJ_ACT(b)->actMode) {
        case 74:
        case 84:
            if (motionKind[GOBJ_SUB(b)->ctrl.motion].playMode == 1) {
                return 1;
            }
            break;
        }
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
                            int *flagout)
{
    ClipWork work;
    int flag;
    int rv;

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
    if (work.wall.elem == 0) {
        rv = 0;
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

void *floorGObj_ACTCheckCollis_WELL;

void *wallGObj_ACTCheckCollis_WAY;

/* the float is the last parameter */
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

int ACTCheckViewCl(GObj *self, void *target, void *targetPos, int range, float f)
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

inline void ACTGameView_Add(GObj *self, GObj *target)
{
    int n = actGameView.num++;
    if (n >= 100) {
        debug_StdPrintfDummy("too many view check object");
        debug_assert("src/act-game.c", 1465);
        __assert("src/act-game.c", 1465, "0");
    }
    actGameView.obj[n] = target;
    actGameView.view[n] = 0;
}

inline void ACTGameView_Init(void)
{
    actGameView.num = 0;
    actGameView.cur = 0;
}

inline void ACTGameView_FirstSet(char *self)

{
    GObj *g;

    g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        ACTGameView_Add((GObj *)g, (GObj *)g);
        g = isysGObjSearchFromObjKindID_next(g);
    }
}

/* One entry a frame: the cursor steps on first, an entry farther than 5000
   from the actor is out of view without the clip test. */
void ACTGameView_Loop(GObj *self)
{
    float pos[4];
    GObj *obj;
    int i;

    i = actGameView.cur++;
    if (!(actGameView.cur < actGameView.num)) {
        actGameView.cur = 0;
    }
    obj = actGameView.obj[i];
    if (obj != 0) {
        if (!(5000.0f < _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(obj)))) {
            GetRootPosition(pos, obj);
            actGameView.view[i] = ACTCheckViewCl(self, obj, pos, 150, 300.0f);
        } else {
            actGameView.view[i] = 0;
        }
    } else {
        actGameView.view[i] = 0;
    }
}

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

static void ACTGame_LwsEffectProcess(GObj *self)
{
    BgaDisp *m = GOBJ_ACT(self)->enemy->lwsEffect;
    if (m != 0) {
        DispMultiBgaManagerWithKind(396, m, 1);
    }
}

inline void ACTGame_LwsEffectInit(GObj *self)
{
    GOBJ_ACT(self)->enemy->lwsEffect = InitMultiBgaManager(1);
}

inline void ACTGame_LwsEffect_Guard(GObj *self)
{
    float q[4];
    float v[4];
    EnemyBattleWork *p;

    _OrientXZGV(v, test_CURRENTROOT(boyGObj), test_CURRENTROOT(self));
    ActGame_GetOrientQ(q, v, 0);

    stage_SetLoopFlag(396, 0);
    stage_SetFrameStep(396, 1);
    p = GOBJ_ACT(self)->enemy;
    EntryMultiBgaManager(p->lwsEffect, 0, -1, test_CURRENTROOT(self), q);
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
    s->flags18.ll &= ~(1ULL << 42);
    s->flags18.ll &= ~(1ULL << 43);
}

inline void ACTCharctrl_Unlock(GObj *self)
{
    Act *p = GOBJ_ACT(self);
    p->flags18.ll |= (1ULL << 42);
    p->flags18.ll |= (1ULL << 43);
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
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x380))->f = pos[0];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x384))->f = pos[1];
        ((IntFloat *)((char *)(int)GOBJ_SUB(self) + 0x388))->f = pos[2];
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
    s->lastParaStatus = s->paraStatus;
}

void ACTParaStatus_Clear(GObj *self)
{
    GOBJ_ACT(self)->paraStatus = 0;
    _ACTParaStatus_Set(self, 0);
}

inline void _ACTParaStatus_Set(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);
    s->paraStatus |= 1 << bit;
}

inline unsigned long long _ACTParaStatus_Check(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);
    return (s->paraStatus >> bit) & 1;
}

void ACTParaStatus_Exec(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    Sub15C *sub;
    int changed;

    changed = 0;
    if ((int)(s->flags20.ll >> 1) & 1) {
        _ACTParaStatus_Set(self, 4);
    }
    if (s->paraStatus != s->lastParaStatus) {
        s->lastParaStatus = s->paraStatus;
        changed = 1;
    }
    if ((GOBJ_ACT(self)->enemy->paraTimer)++ >= 121) {
        sub = GOBJ_SUB(self);
        if ((sub->ctrl.ctrlFlags & 0x16) || (int)sub->ctrl.frameEnd != 0) {
            if (motionKind[sub->ctrl.motion].playMode == 1) {
                GOBJ_ACT(self)->enemy->paraTimer = 0;
                GOBJ_ACT(self)->enemy->paraRandom = (int)(_GetRandom() * 10.0f);
                changed = 1;
            }
        }
    }
    _ACTParaStatus_Set(self, 1);
    if (changed == 0) {
        return;
    }
    ActPara_MakeTbl(GOBJ_WORK(self)->paraTbl, s->paraStatus, GOBJ_ACT(self)->enemy->paraRandom);
    SetParallelMotionTable(self, GOBJ_WORK(self)->paraTbl, ActPara_GetDefTbl(), 0, 3);
}

inline void _ACTCharStatus_Init(int **self)
{
    int *p = self[0x59];
    p[0x15] = 0;
    p[0x16] = 0;
}

inline void _ACTCharStatus_Clear(void *self)
{
    Act *s = GOBJ_ACT(self);
    int *sel;
    int *g;
    float nearest;
    float d;

    memset((char *)s + 0x54, 0, 0x2C);
    if (self == (char *)boyGObj || self == ((char *)girlGObj)) {
        nearest = 3.40282347e+38f; /* FLT_MAX */
        sel = 0;
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            d = _DistGV(test_CURRENTROOT(self), test_CURRENTROOT((GObj *)g));
            if (actEnemyFlagCheckActive((GObj *)g)) {
                if (d < nearest) {
                    sel = g;
                    nearest = d;
                }
            }
            g = isysGObjSearchFromObjKindID_next((GObj *)g);
        }
        *(int **)((char *)s + 0x70) = sel;
    }
}

inline void _ACTCharStatus_Set(GObj *self, int bit, float f, int val)
{
    Act *s = GOBJ_ACT(self);

    *(int *)((char *)s + 0x54) |= 1 << bit;

    switch (bit) {
    case 6:
        s->statusWait8 = f;
        break;

    case 3:
        s->statusWait5 = f;
        break;

    case 13:
        s->statusVal17 = f;
        break;

    case 14:
        s->statusVal18 = val;
        break;

    case 8:
        s->statusTarget = val;
        break;

    case 0:
        s->statusOther = val;
        break;

    case 9:
        s->statusObj = val;
        break;
    }
}

inline unsigned char _ACTCharStatus_Check(GObj *self, int bit)
{
    Act *s = GOBJ_ACT(self);

    if ((char *)s != 0) {
        if ((*(int *)((char *)s + 0x54) >> bit) & 1) {
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

inline void ACTGame_SetMotionPlaySpeedRatio_Exec(GObj *self)
{
    float ratio;
    int keep;

    ratio = 1.0f;
    keep = (unsigned int)(int)GOBJ_ACT(self)->enemy->speedRatioPri < 3 && self == girlGObj;
    if ((int)GOBJ_ACT(self)->enemy->speedRatioPri == 1) {
        if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->flags >> 23) & 1) {
            ratio = GOBJ_ACT(self)->enemy->speedRatio;
            keep = 0;
        }
    } else {
        if ((((&motionKind[GOBJ_SUB(self)->ctrl.motion])->flags >> 24) & 1) == 0) {
            ratio = GOBJ_ACT(self)->enemy->speedRatio;
        }
    }
    if (keep) {
        ratio = 1.0f;
    }
    speedRatioDebugOverride(&ratio);
    SetMotionPlaySpeedRatio(self, ratio);
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
    mail = 373;
    if (s->actMode == 3) {
        mail = 374;
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
static void ACTGame_InnerVelocityUpdate(GObj *self)
{
    float pos[4];
    int slow;
    int stop;
    ActWork *w;
    float speed;

    slow = 0;
    stop = 0;
    pos[0] = test_CURRENTROOT(self)[0];
    pos[1] = test_CURRENTROOT(self)[1];
    pos[2] = test_CURRENTROOT(self)[2];
    sceVu0SubVector((char *)GOBJ_ACT(self)->work + 0x3B0, pos,
                    (char *)GOBJ_ACT(self)->work + 0x3A0);
    speed = FSqrt(GOBJ_WORK(self)->velX * GOBJ_WORK(self)->velX +
                  GOBJ_WORK(self)->velY * GOBJ_WORK(self)->velY +
                  GOBJ_WORK(self)->velZ * GOBJ_WORK(self)->velZ);
    w = GOBJ_WORK(self);
    w->speed = speed;
    *(float *)((char *)w + 0x3A0) = pos[0];
    *(float *)((char *)w + 0x3A4) = pos[1];
    *(float *)((char *)w + 0x3A8) = pos[2];
    if (speed < 6.0f) {
        slow = 1;
    }
    if (speed < 2.0f) {
        stop = 1;
    }
    if (slow != 0) {
        w->slowFrames += 1;
    } else {
        w->slowFrames = 0;
    }
    if (stop != 0) {
        GOBJ_WORK(self)->stopFrames += 1;
    } else {
        GOBJ_WORK(self)->stopFrames = 0;
    }
    if (4 <= GOBJ_WORK(self)->slowFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x3C8))->q |= 1ULL << 32;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x3C8))->q &= ~(1ULL << 32);
    }
    if (4 <= GOBJ_WORK(self)->stopFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x3C8))->q |= 1ULL << 33;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x3C8))->q &= ~(1ULL << 33);
    }
}

/* mail 188's function in the attack rows: the weapon is dropped (aug6
   has the same release as WithMailFunc_AttackRejectInQueen, commonact.c) */
inline void WithMailFunc_AttackReject(GObj *self) /* derived name */
{
    Act *s = GOBJ_ACT(self);

    if (s->weapon != 0) {
        ReleaseWeaponWithFumbleSequential(s->weapon);
        s->weapon = 0;
    }
}

void ACTGame_BeforeFunc(GObj *self)
{
    Act *s = GOBJ_ACT(self);

    ACTGame_InnerVelocityUpdate(self);

    switch ((unsigned int)s->actMode) {
    case 1: {
        Act *p = GOBJ_ACT(self);
        p->attacker = 0;
        p->hit = 0;
        break;
    }
    }

    if ((((&motionKind[GOBJ_SUB(self)->ctrl.motion])->flags >> 14) & 1) == 0 ||
        GOBJ_SUB(self)->ctrl.reserveBlend != 0) {
        GetRootPosition((char *)s + 0xF0, self);
    }

    ACTParaStatus_Clear(self);
    _ACTCharStatus_Clear(self);
    ACTLookTarget_Init(self);

    memset((char *)s + 0x474, 0, 12);
    memset((char *)s + 0x480, 0, 12);

    ACTGame_SetMotionPlaySpeedRatio_Clear(self);

    if (GOBJ_WORK(self)->downTimer > 0) {
        (GOBJ_WORK(self)->downTimer)--;
    }
    if (s->soundWait > 0) {
        (s->soundWait)--;
    }

    if (self == (girlGObj)) {
        ACTGame_GirlBeforeFunc(self);
    }
}

/* OR the 12 pending-request bytes into the live request bytes. */
static inline void actEnv_OrRequestBytes(unsigned char *dst, unsigned char *src) /* derived name */
{
    int i;

    for (i = 11; i >= 0; i--, dst++, src++) {
        *dst |= *src;
    }
}

/* masks the 12-byte request-flag block in place */
static inline void andRequestFlags(char *d, char *m) /* derived name */
{
    int i;
    for (i = 11; i >= 0; i--) {
        *d = *d & *m;
        d++;
        m++;
    }
}

static void FunctionAboutClingedStatus(GObj *self)
{
    int buf[3];
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
        _ACTCharStatus_Set(self, 25, 0.0f, 0);
        _ACTParaStatus_Set(self, 0);
    }
    cl = _ACTCharStatus_Check(self, 25);
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
        memset(buf, 0, 12);
        buf[0] |= 0x400;
        andRequestFlags((char *)s + 0x480, (char *)buf);
        ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 1.0f / ((float)clinged * 0.25f + 1.0f), 6);
        break;
    case 2:
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            if (self == actEnemy_GetClingTarget(g)) {
                iosOmSendMail(g, 191, self);
                break;
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        GOBJ_ACT(self)->enemy->clingedFrames = 0;
        break;
    }
}

static void ACTEnvGetTest(GObj *self, void *dir)
{
    ActEnv old;
    Act *s = GOBJ_ACT(self);

    s->flags18.ll &= ~(1ULL << 48);
    s->flags18.ll &= ~(1ULL << 49);
    s->flags18.ll &= ~(1ULL << 50);
    s->flags20.ll &= ~(1ULL << 3);

    switch (s->actMode) {
    case 38:
    case 103:
        s->env.motOriReq = *(MotOriReq *)&GOBJ_SUB(self)->root.wall;
        break;

    default:
        old = s->env;
        memset(&s->env, 0, sizeof(ActEnv));
        s->env.turnDir = old.turnDir;
        s->env.motOriReq = old.motOriReq;
        s->env.supportReq = old.supportReq;
        s->env.cliffContact = old.cliffContact;
        ACTGetEnvironment(self, dir, test_CURRENTORIENT(self), (EnvFlag *)((char *)s + 0x474),
                          &s->env);
        break;

    case 10:
    case 12:
    case 14:
    case 26:
    case 36:
    case 45:
    case 46:
    case 47:
    case 48:
    case 51:
    case 52:
    case 53:
    case 54:
    case 63:
    case 64:
    case 65:
    case 66:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 84:
    case 100:
    case 101:
    case 102:
        break;
    }

    ACTSetEnvAllmighty(self);
    ACTGetWish_FromPad(self, dir);

    if (ACTGame_CheckPriInputFrame(self)) {
        actEnv_OrRequestBytes((unsigned char *)((char *)s + 0x48C),
                              (unsigned char *)((char *)s + 0x480));
    } else {
        memset((char *)s + 0x48C, 0, 12);
    }

    if ((int)(s->wish3.ll >> 38) & 1) {
        s->wish2.ll |= 1ULL << 6;
    }
    if ((int)(s->wish3.ll >> 42) & 1) {
        s->wish2.ll |= 1ULL << 10;
    }
    if ((int)(s->wish3.ll >> 43) & 1) {
        s->wish2.ll |= 1ULL << 11;
    }
    if ((int)(s->wish3.ll >> 47) & 1) {
        s->wish2.ll |= 1ULL << 15;
    }
    if ((int)(s->wish3.ll >> 48) & 1) {
        s->wish2.ll |= 1ULL << 16;
    }
    if ((int)(s->wish3.ll >> 49) & 1) {
        s->wish2.ll |= 1ULL << 17;
    }
    if ((int)(s->wish3.ll >> 50) & 1) {
        s->wish2.ll |= 1ULL << 18;
    }
    FunctionAboutClingedStatus(self);
}

static void ActOrientTest(GObj *self)
{
    float v0[4];
    ClipWork w1;
    float p1[4];
    float sk1[4];
    float sk2[4];
    float d1[4];
    ClipWork w2;
    float p2[4];
    float d2[4];
    float c1[4];
    Act *s = GOBJ_ACT(self);
    float *vel;
    int hitA;
    int hitB;
    int near;

    if (ORBIT(ORQ((char *)s, 0), 38) && ORBIT(ORM((char *)s, 0), 6)) {
        ACTSendMailCorrect(self, 171);
    }
    if (ORBIT(ORQ((char *)s, 0), 39) && ORBIT(ORM((char *)s, 0), 7)) {
        ACTSendMailCorrect(self, 172);
    }
    if (ORBIT(ORQ((char *)s, 0), 40) && ORBIT(ORM((char *)s, 0), 8)) {
        ACTSendMailCorrect(self, 173);
    }
    if (ORBIT(ORQ((char *)s, 0), 41) && ORBIT(ORM((char *)s, 0), 9)) {
        ACTSendMailCorrect(self, 174);
    }
    if (ORBIT(ORQ((char *)s, 0), 42) && ORBIT(ORM((char *)s, 0), 10)) {
        if (*(int *)((char *)self + 0xC) == 4) {
            if (rand() & 1) {
                ACTSendMailCorrect(self, 183);
            } else {
                ACTSendMailCorrect(self, 185);
            }
        } else {
            ACTSendMailCorrect(self, 183);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 43) && ORBIT(ORM((char *)s, 0), 11)) {
        ACTSendMailCorrect(self, 184);
    }
    if (ORBIT(ORQ((char *)s, 0), 48) && ORBIT(ORM((char *)s, 0), 16)) {
        ACTSendMailCorrect(self, 253);
    }
    if (self != boyGObj) {
        if (ORBIT(ORQ((char *)s, 0), 47) && ORBIT(ORM((char *)s, 0), 15)) {
            ACTSendMailCorrect(self, 252);
        }
        if (ORBIT(ORQ((char *)s, 0), 49) && ORBIT(ORM((char *)s, 0), 17)) {
            ACTSendMailCorrect(self, 254);
        }
        if (ORBIT(ORQ((char *)s, 0), 50) && ORBIT(ORM((char *)s, 0), 18)) {
            ACTSendMailCorrect(self, 255);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 52) && ORBIT(ORM((char *)s, 0), 20)) {
        ACTSendMailCorrect(self, 181);
    }
    if (ORBIT(ORQ((char *)s, 0), 51) && ORBIT(ORM((char *)s, 0), 19)) {
        if (ACTGame_NoWeapon(self)) {
            ACTSendMailCorrect(self, 180);
        } else {
            ACTSendMailCorrect(self, 179);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 53) && ORBIT(ORM((char *)s, 0), 21)) {
        ACTSendMailCorrect(self, 307);
    }
    if (ORBIT(ORQ((char *)s, 0), 54) && ORBIT(ORM((char *)s, 0), 22)) {
        ACTSendMailCorrect(self, 330);
    }
    if (ORBIT(ORQ((char *)s, 0), 57) && ORBIT(ORM((char *)s, 0), 25)) {
        ACTSendMailCorrect(self, 187);
    }
    if (ORBIT(ORQ((char *)s, 0), 58) && ORBIT(ORM((char *)s, 0), 26)) {
        ACTSendMailCorrect(self, 188);
    }
    if (ORBIT(ORQ((char *)s, 0), 59) && ORBIT(ORM((char *)s, 0), 27)) {
        ACTSendMailCorrect(self, 190);
    }
    if (ORBIT(ORQ((char *)s, 0), 60) && ORBIT(ORM((char *)s, 0), 28)) {
        ActSendMail_WithAdditionalData(self, 238, self, (char *)GOBJ_ACT(self)->enemy + 816);
    }
    if (ORBIT(ORQ((char *)s, 0), 61) && ORBIT(ORM((char *)s, 0), 29)) {
        ActSendMail_WithAdditionalData(self, 239, self, (char *)GOBJ_ACT(self)->enemy + 864);
    }
    if (ORBIT(ORQ((char *)s, 0), 55) && ORBIT(ORM((char *)s, 0), 23)) {
        ACTSendMailCorrect(self, 156);
        ACTSendMailCorrect(self, 155);
    }
    if (ORBIT(ORQ((char *)s, 0), 56) && ORBIT(ORM((char *)s, 0), 24)) {
        ACTSendMailCorrect(self, 150);
    }
    if (ORBIT(ORQ((char *)s, 1), 2) && ORBIT(ORM((char *)s, 0), 34)) {
        ACTSendMailCorrect(self, 193);
        debug_StdPrintfDummy("shoal mail\n");
    } else if (s->actMode == 43) {
        ACTSendMailCorrect(self, 194);
    }
    if (ORBIT(ORQ((char *)s, 1), 3) && ORBIT(ORM((char *)s, 0), 35)) {
        ACTSendMailCorrect(self, 195);
    }
    if (ORBIT(ORQ((char *)s, 1), 4) && ORBIT(ORM((char *)s, 0), 36)) {
        ACTSendMailCorrect(self, 196);
    }
    if (ORBIT(ORQ((char *)s, 1), 5) && ORBIT(ORM((char *)s, 0), 37)) {
        ACTSendMailCorrect(self, 199);
    }
    if (ORBIT(ORQ((char *)s, 1), 6) && ORBIT(ORM((char *)s, 0), 38)) {
        ACTSendMailCorrect(self, 200);
    }
    if (ORBIT(ORQ((char *)s, 1), 7) && ORBIT(ORM((char *)s, 0), 39)) {
        ACTSendMailCorrect(self, 201);
    }
    if (ORBIT(ORQ((char *)s, 1), 26) && ORBIT(ORM((char *)s, 0), 58)) {
        ACTSendMailCorrect(self, 112);
    }
    if (ORBIT(ORQ((char *)s, 1), 28) && ORBIT(ORM((char *)s, 0), 60)) {
        ACTSendMailCorrect(self, 113);
    }
    if (ORBIT(ORQ((char *)s, 1), 30) && ORBIT(ORM((char *)s, 0), 62)) {
        ACTSendMailCorrect(self, 120);
    }
    if (ORBIT(ORQ((char *)s, 1), 29) && ORBIT(ORM((char *)s, 0), 61)) {
        ACTSendMailCorrect(self, 117);
    }
    if (ORBIT(ORQ((char *)s, 1), 31) && ORBIT(ORM((char *)s, 0), 63)) {
        ACTSendMailCorrect(self, 121);
    }
    if (ORBIT(ORQ((char *)s, 1), 32) && ORBIT(ORM((char *)s, 1), 0)) {
        ACTSendMailCorrect(self, 122);
    }
    if (ORBIT(ORQ((char *)s, 1), 33) && ORBIT(ORM((char *)s, 1), 1)) {
        ACTSendMailCorrect(self, 114);
    }
    if (ORBIT(ORQ((char *)s, 1), 34) && ORBIT(ORM((char *)s, 1), 2)) {
        ACTSendMailCorrect(self, 115);
        ACTSendMailCorrect(self, 116);
    }
    if (ORBIT(ORQ((char *)s, 1), 23) && ORBIT(ORM((char *)s, 0), 55)) {
        ACTSendMailCorrect(self, 109);
    }
    if (ORBIT(ORQ((char *)s, 1), 24) && ORBIT(ORM((char *)s, 0), 56)) {
        ACTSendMailCorrect(self, 110);
    }
    if (ORBIT(ORQ((char *)s, 1), 25) && ORBIT(ORM((char *)s, 0), 57)) {
        ACTSendMailCorrect(self, 111);
    }
    if (ORBIT(ORQ((char *)s, 0), 62) && ORBIT(ORM((char *)s, 0), 30)) {
        if (self == (girlGObj)) {
            if (GOBJ_ACT(self)->actMode == 112) {
                ACTSendMailCorrect(self, 105);
            }
        } else {
            ACTSendMailCorrect(self, 105);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 63) && ORBIT(ORM((char *)s, 0), 31)) {
        ACTSendMailCorrect(self, 292);
    }
    if (ORBIT(ORQ((char *)s, 1), 0) && ORBIT(ORM((char *)s, 0), 32)) {
        ACTSendMailCorrect(self, 293);
    }
    if (ORBIT(ORQ((char *)s, 1), 8) && ORBIT(ORM((char *)s, 0), 40)) {
        ACTSendMailCorrect(self, 285);
    }
    if (ORBIT(ORQ((char *)s, 1), 9) && ORBIT(ORM((char *)s, 0), 41)) {
        ACTSendMailCorrect(self, 286);
    }
    if (ORBIT(ORQ((char *)s, 1), 10) && ORBIT(ORM((char *)s, 0), 42)) {
        ACTSendMailCorrect(self, 287);
    }
    if (ORBIT(ORQ((char *)s, 1), 12) && ORBIT(ORM((char *)s, 0), 44)) {
        ACTSendMailCorrect(self, 288);
    }
    if (ORBIT(ORQ((char *)s, 1), 13) && ORBIT(ORM((char *)s, 0), 45)) {
        ACTSendMailCorrect(self, 288);
    }
    if (ORBIT(ORQ((char *)s, 1), 17) && ORBIT(ORM((char *)s, 0), 49)) {
        ACTSendMailCorrect(self, 285);
    }
    if (ORBIT(ORQ((char *)s, 1), 18) && ORBIT(ORM((char *)s, 0), 50)) {
        ACTSendMailCorrect(self, 286);
    }
    if (ORBIT(ORQ((char *)s, 1), 19) && ORBIT(ORM((char *)s, 0), 51)) {
        ACTSendMailCorrect(self, 287);
    }
    if (ORBIT(ORQ((char *)s, 1), 44) && ORBIT(ORM((char *)s, 1), 12)) {
        ACTSendMailCorrect(self, 40);
    }
    if (ORBIT(ORQ((char *)s, 1), 45) && ORBIT(ORM((char *)s, 1), 13)) {
        ACTSendMailCorrect(self, 125);
    }
    if (ORBIT(ORQ((char *)s, 1), 50) && ORBIT(ORM((char *)s, 1), 18)) {
        ACTSendMailCorrect(self, 269);
    }
    if (ORBIT(ORQ((char *)s, 1), 51) && ORBIT(ORM((char *)s, 1), 19)) {
        ACTSendMailCorrect(self, 267);
    }
    if (ORBIT(ORQ((char *)s, 1), 42) && ORBIT(ORM((char *)s, 1), 10)) {
        ACTSendMailCorrect(self, 272);
    }
    if (ORBIT(ORQ((char *)s, 1), 43) && ORBIT(ORM((char *)s, 1), 11)) {
        ACTSendMailCorrect(self, 132);
    }
    if (ORBIT(ORQ((char *)s, 1), 35) && ORBIT(ORM((char *)s, 1), 3)) {
        ACTSendMailCorrect(self, 267);
    }
    if (ORBIT(ORQ((char *)s, 1), 36) && ORBIT(ORM((char *)s, 1), 4)) {
        ACTSendMailCorrect(self, 271);
    }
    if (ORBIT(ORQ((char *)s, 1), 37) && ORBIT(ORM((char *)s, 1), 5)) {
        ACTSendMailCorrect(self, 277);
    }
    if (ORBIT(ORQ((char *)s, 1), 38) && ORBIT(ORM((char *)s, 1), 6)) {
        ACTSendMailCorrect(self, 278);
    }
    if (ORBIT(ORQ((char *)s, 1), 39) && ORBIT(ORM((char *)s, 1), 7)) {
        ACTSendMailCorrect(self, 279);
    }
    if (ORBIT(ORQ((char *)s, 1), 40) && ORBIT(ORM((char *)s, 1), 8)) {
        ACTSendMailCorrect(self, 280);
    }
    if (ORBIT(ORQ((char *)s, 1), 41) && ORBIT(ORM((char *)s, 1), 9)) {
        ACTSendMailCorrect(self, 281);
    }
    if (ORBIT(ORQ((char *)s, 1), 59) && ORBIT(ORM((char *)s, 1), 27)) {
        ACTSendMailCorrect(self, 81);
    }
    if (ORBIT(ORQ((char *)s, 1), 60) && ORBIT(ORM((char *)s, 1), 28)) {
        ACTSendMailCorrect(self, 82);
    }
    if (ORBIT(ORQ((char *)s, 1), 56) && ORBIT(ORM((char *)s, 1), 24)) {
        ACTSendMailCorrect(self, 66);
        s->orientMot = 92;
    }
    if (ORBIT(ORQ((char *)s, 1), 57) && ORBIT(ORM((char *)s, 1), 25)) {
        ACTSendMailCorrect(self, 66);
        s->orientMot = 94;
    }
    if (ORBIT(ORQ((char *)s, 1), 58) && ORBIT(ORM((char *)s, 1), 26)) {
        ACTSendMailCorrect(self, 66);
        s->orientMot = 96;
    }
    if (ORBIT(ORQ((char *)s, 1), 14) && ORBIT(ORM((char *)s, 0), 46)) {
        ACTSendMailCorrect(self, 289);
    }
    if (ORBIT(ORQ((char *)s, 1), 15) && ORBIT(ORM((char *)s, 0), 47)) {
        ACTSendMailCorrect(self, 290);
    }
    if (ORBIT(ORQ((char *)s, 1), 16) && ORBIT(ORM((char *)s, 0), 48)) {
        ACTSendMailCorrect(self, 291);
    }
    if (ORBIT(ORQ((char *)s, 1), 49) && ORBIT(ORM((char *)s, 1), 17)) {
        ACTSendMailCorrect(self, 149);
    }
    if (ORBIT(ORQ((char *)s, 1), 61) && ORBIT(ORM((char *)s, 1), 29)) {
        ACTSendMailCorrect(self, 343);
    }
    if (ORBIT(ORQ((char *)s, 1), 62) && ORBIT(ORM((char *)s, 1), 30)) {
        vel = s->env.cliffOrient;
        sceVu0ScaleVector(v0, vel, -sceVu0InnerProduct((char *)(int)GOBJ_SUB(self) + 0x120, vel));
        sceVu0AddVector((char *)(int)GOBJ_SUB(self) + 0x120, (char *)(int)GOBJ_SUB(self) + 0x120,
                        v0);
        SetRootPosition(self, s->env.cliffBackPos);
    }

    if (GOBJ_ACT(self)->enemy->stoneLevel > 0) {
        ACTSendMailCorrect(self, 102);
    }
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->modeBits.w >> 31) & 1) {
        if (GetMotionFrameFlag1(self)) {
            memset(&w1, 0, sizeof(w1));
            GetSkeltonPosition(sk1, self, 51);
            GetSkeltonPosition(sk2, self, 47);
            sceVu0AddVector(p1, sk1, sk2);
            sceVu0ScaleVector(p1, p1, 0.5f);
            p1[1] = p1[1] + 50.0f;
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), 50.0f);
            sceVu0AddVector(w1.pt[0], p1, d1);
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), -50.0f);
            sceVu0AddVector(w1.pt[1], p1, d1);
            w1.radius = 0.0f;
            ClipWall(&w1);
            if (CompareAttribute(w1.attr, 0x2000)) {
                ACTSendMailCorrect(self, 294);
            }
            if (CompareAttribute(w1.attr, 0x20000)) {
                if (*(int *)((char *)s + 0x65C) != 0) {
                    if (GetMotionFrameFlag1(self)) {
                        char *ext;
                        *(U64ag *)*(int *)((char *)s + 0x65C) = *(U64ag *)((char *)&w1 + 0x80);
                        ext = (char *)*(int *)((char *)s + 0x65C);
                        *(int *)(ext + 8) = *(int *)((char *)&w1 + 0x88);
                        ActSendMail_WithAdditionalData(self, 270, self, ext);
                    }
                }
            }
        }
    }
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->flags >> 0) & 1) {
        memset(&w2, 0, sizeof(w2));
        near = 0;
        p2[0] = test_CURRENTROOT(self)[0];
        p2[1] = test_CURRENTROOT(self)[1];
        p2[2] = test_CURRENTROOT(self)[2];
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), -50.0f);
        sceVu0AddVector(w2.pt[0], p2, d2);
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), 50.0f);
        sceVu0AddVector(w2.pt[1], p2, d2);
        hitA = 0;
        w2.radius = 0.0f;
        ClipWall(&w2);
        hitB = 0;
        if (CompareAttribute(w2.attr, 0x400)) {
            hitA = 1;
        }
        if (CompareAttribute(w2.attr, 0xC000)) {
            hitB = 1;
        }
        if (hitA || hitB) {
            GetCollisCenterPositionSimple(c1, w2.wall.o.obj, w2.wall.elem);
            if (_DistxzSqGV(c1, test_CURRENTROOT(self)) < 400.0f) {
                near = 1;
            }
        }
        if (hitA && near) {
            ACTSendMailCorrect(self, 128);
        }
        if (hitB && near) {
            ACTSendMailCorrect(self, 279);
        }
    }
}

void ACTGame_CommonLoop(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    GObj *gobj;
    unsigned char handL;
    unsigned char handR;
    float third;
    float half;

    /* nonzero when a wall stands between the two hands, either way round
       (a wall of attribute 0x40000 does not count) */
    int GetGirlHandlinkClInfo(float *a, float *b)
    {
        int attr;
        int hit;

        hit = ACTCheckCollis_W(0.0f, a, b, 0, 0, &attr);
        if (CompareAttribute(attr, 0x40000)) {
            return 0;
        }
        if (hit == 0) {
            return 0;
        }
        hit = ACTCheckCollis_W(0.0f, b, a, 0, 0, &attr);
        if (CompareAttribute(attr, 0x40000)) {
            hit = 0;
        }
        return hit;
    }

    int hand_able_connect(void)
    {
        float boyPos[4];
        float girlPos[4];
        float boyHand[4];
        float girlHand[4];
        float dy;

        if (boyGObj != 0 && ((char *)girlGObj) != 0) {
            GetRootProjectionPosOfGObj(boyPos, boyGObj);
            GetRootProjectionPosOfGObj(girlPos, girlGObj);
            if (_DistxzSqGV(boyPos, girlPos) < 12100.0f) {
                dy = boyPos[1] - girlPos[1];
                if ((dy < 0.0f ? -dy : dy) < 60.0f) {
                    GetSkeltonPosition(boyHand, boyGObj, 2);
                    GetSkeltonPosition(girlHand, girlGObj, 18);
                    return GetGirlHandlinkClInfo(boyHand, girlHand) == 0;
                }
            }
        }
        return 0;
    }

    ACTEnvGetTest(self, (char *)s + 0x100);

    ActOrientTest(self);

    ACTItemWatchMotion(self);

    if (CheckFloorAttribute(self, 0x7000)) {
        _ACTParaStatus_Set(self, 19);
        _ACTCharStatus_Set(self, 18, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0x8000)) {
        _ACTParaStatus_Set(self, 18);
        _ACTCharStatus_Set(self, 17, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0x9000)) {
        _ACTParaStatus_Set(self, 17);
        _ACTCharStatus_Set(self, 16, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0xA000)) {
        _ACTParaStatus_Set(self, 16);
        _ACTCharStatus_Set(self, 15, 0.0f, 0);
    }

    if (((int)(s->wish1.ll >> 54) & 1) && ((int)(s->wish3.ll >> 22) & 1)) {
        _ACTParaStatus_Set(self, 21);
        _ACTCharStatus_Set(self, 20, 0.0f, 0);
    }

    if ((((int)(s->wish1.ll >> 52) & 1) && ((int)(s->wish3.ll >> 20) & 1)) ||
        (((int)(s->wish1.ll >> 53) & 1) && ((int)(s->wish3.ll >> 21) & 1))) {
        _ACTParaStatus_Set(self, 20);
        _ACTCharStatus_Set(self, 19, 0.0f, 0);
    }

    handL = 0;
    handR = 0;
    if (((int)(s->wish0.ll >> 35) & 1) && ((int)(s->wish2.ll >> 3) & 1)) {
        _ACTParaStatus_Set(self, 5);
        handL = (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x490)])
                      ->modeBits.w >>
                  12) &
                 0xF) != 0;
    }
    if (((int)(s->wish0.ll >> 36) & 1) && ((int)(s->wish2.ll >> 4) & 1)) {
        _ACTParaStatus_Set(self, 6);
        handR = (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x490)])
                      ->modeBits.w >>
                  8) &
                 0xF) != 0;
    }

    if (handL) {
        RequestChangeHandMode(
            self, 0, 1,
            motionIKEffKind[((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i +
                                                   0x490)])
                                 ->modeBits.w >>
                             12) &
                            0xF]
                .mode,
            0, 0, 0);
    } else {
        RequestChangeHandMode(self, 0, 1, 0, 0, 0, 0);
    }
    if (handR) {
        RequestChangeHandMode(
            self, 1, 1,
            motionIKEffKind[((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i +
                                                   0x490)])
                                 ->modeBits.w >>
                             8) &
                            0xF]
                .mode,
            0, 0, 0);
    } else {
        RequestChangeHandMode(self, 1, 1, 0, 0, 0, 0);
    }

    if (((int)(s->wish0.ll >> 33) & 1) && ((int)(s->wish2.ll >> 1) & 1)) {
        _ACTCharStatus_Set(self, 21, 0.0f, 0);
    }
    if (((int)(s->wish0.ll >> 34) & 1) && ((int)(s->wish2.ll >> 2) & 1)) {
        _ACTCharStatus_Set(self, 22, 0.0f, 0);
    }

    if ((unsigned int)s->actMode < 4) {
        if (s->actMode != 0) {
            _ACTCharStatus_Set(self, 23, 0.0f, 0);
        }
    }

    if (((char *)girlGObj) != 0 && ((int)(GOBJ_ACT(((char *)girlGObj))->flags18.ll >> 35) & 1)) {
        _ACTCharStatus_Set(self, 11, 0.0f, 0);
    }

    gobj = isysGObjSearchFromObjKindID_begin(20);
    while (gobj != 0) {
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }

    switch (ACTGame_GetCurrentCallStatus(self)) {
    case 1:
    case 2: {
        float orient[4];
        int limit;

        if (self == boyGObj && s->actMode == 1 &&
            (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x490)])
                  ->flags >>
              4) &
             1)) {
            limit = 100;
            if (((char *)girlGObj) != 0) {
                _OrientXZGV(orient, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
            } else {
                GetOtherStageGirlOrient(orient);
                orient[1] = 0.0f;
                limit = 45;
            }
            if (limit < _AbsRotyGV(orient, test_CURRENTORIENT(self))) {
                SetMotionDirection(self, orient);
                ResetMotionProgramInterpInfo(self, 35);
            }
        }
        brainAddLevelGirl(20.0f);
        brainSetSpMode();
        if (hand_able_connect()) {
            iosOmSendMail(girlGObj, 58, boyGObj);
        }
        break;
    }
    default:
        if (ACTGame_FLAG_TETSUNAGI() && GOBJ_ACT(((char *)girlGObj))->actMode != 77) {
            brainAddLevelGirl(3.0f);
        }
        break;
    }

    third = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    half = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;

    if (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) != 0) {
        if (0.5f < s->stick.mag) {
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) =
                !*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4);
            (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = third;
        }
    } else {
        if (!(0.5f < s->stick.mag)) {
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) =
                !*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4);
        }
    }

    if (0.5f < s->stick.mag) {
        switch (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8)) {
        case 0:
            if (0.5f < s->stick.dz) {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 1;
                (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = half;
            }
            break;
        case 1:
            if (!(0.5f < s->stick.dz)) {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 0;
                (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = half;
            }
            break;
        case -1:
            if (0.5f < s->stick.dz) {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 1;
            } else {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 0;
            }
            break;
        }
    } else {
        *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = -1;
    }

    if (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) > 0) {
        *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD0) = 1;
    } else {
        *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD0) = 0;
    }
    (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4))--;

    if (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x490)])->flags >>
         13) &
        1) {
        s->msgBlockTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    }

    ACTGame_LwsEffectProcess(self);
    actGame_SendMailToBirds(self);
    ACTGame_SetMotionPlaySpeedRatio_Exec(self);
}

/* the girl's direction from this stage when she is on another one */
void GetOtherStageGirlOrient(float *orient)
{
    StageOrientGet((VECTOR *)orient, stage_no, gamesysGirlStageGet());
}

/* a point 300 ahead of the actor's head, toward the girl on another stage
   (the role the later builds' GetGirlPositionAtThisStage has) */
static inline void GetGirlPositionAtThisStage(float *pos, GObj *obj) /* derived name */
{
    float dir[4];
    float head[4];

    GetOtherStageGirlOrient(dir);
    GetSkeltonPosition(head, obj, 35);
    sceVu0ScaleVector(dir, dir, 300.0f);
    sceVu0AddVector(pos, head, dir);
}

inline float _ACTGame_GetParamF(int idx)
{
    return gameParam[idx];
}

inline void ACTGame_SendSoundMail(GObj *self, int mail, GObj *from, int mot, int waitSkip)
{
    switch (mail) {
    case 366:
        if (waitSkip != 0 && GOBJ_ACT(self)->soundWait > 0) {
            break;
        }
        iosOmSendMail(self, 366, from);
        if (mot == 0) {
            break;
        }
        {
            Act *act = GOBJ_ACT(self);
            act->soundMot = mot;
            *(unsigned long long *)((char *)act + 0x118) =
                (*(unsigned long long *)((char *)act + 0x118) & ~1ULL) | (waitSkip & 1);
        }
        break;

    case 367:
        iosOmSendMail(self, 367, from);
        {
            Act *act = GOBJ_ACT(self);
            act->soundMot = mot;
        }
        break;
    }
}

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

inline void _ACTSetEnemyDisappearSpeed(GObj *self, float speed)
{
    GOBJ_WORK(self)->disappearSpeed = speed;
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
            GetSkeltonPosition(p, self, 35);
            sceVu0ScaleVector(dir, (char *)GOBJ_ACT(self)->work + 0x400, 300.0f);
            sceVu0AddVector(pos, p, dir);
            GOBJ_SUB(self)->root.ikRate0 = 0.3f;
            GOBJ_SUB(self)->root.ikRate1 = 0.3f;
            GOBJ_SUB(self)->root.ikRate2 = 0.3f;
            rv = 1;
            break;
        case 12:
            target = *(GObj **)(s + 0x7C);
            break;
        case 10:
            target = *(GObj **)(s + 0x6C);
            break;
        case 5:
            target = *(GObj **)(s + 0x70);
            break;
        case 4:
            target = girlGObj;
            if (target == 0) {
                GetGirlPositionAtThisStage(pos, self);
                rv = 1;
            }
            break;
        case 11:
            GetRootPosition(pos, *(GObj **)(s + 0x68));
            pos[1] = *(float *)&test_CURRENTROOT(self)[1];
            *pmode = 2;
            rv = 1;
            break;
        case 6:
            target = girlGObj;
            *pmode = 2;
            if (target == 0) {
                GetGirlPositionAtThisStage(pos, self);
                rv = 1;
            }
            break;
        case 8:
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(GObj **)(s + 0x74);
            } else {
                target = boyGObj;
            }
            break;
        case 9:
            target = *(GObj **)(s + 0x78);
            break;
        case 7:
            target = boyGObj;
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(GObj **)(s + 0x74);
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
            sceVu0ScaleVector(pos, test_CURRENTORIENT(self), *(float *)(s + 0x5B8));
            pos[1] = 150.0f;
            sceVu0AddVector(pos, test_CURRENTROOT(self), pos);
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
    int col = ((int *)s)[17];
    int flags;
    int i;

    flags = 0;
    if (_ACTCharStatus_Check(self, 27)) {
        flags = 1;
    }
    if (_ACTCharStatus_Check(self, 8)) {
        flags |= 0x20000;
    }
    if (_ACTCharStatus_Check(self, 9)) {
        flags |= 0x100;
    }
    if (_ACTCharStatus_Check(self, 11)) {
        flags |= 0x40;
    }
    if (_ACTCharStatus_Check(self, 3)) {
        flags |= 0x2000;
    }
    if (_ACTCharStatus_Check(self, 21)) {
        flags |= 0x80;
    }
    if (_ACTCharStatus_Check(self, 22)) {
        flags |= 0x20;
    }
    if (_ACTCharStatus_Check(self, 26)) {
        flags |= 0x200;
    }
    if (_ACTCharStatus_Check(self, 1)) {
        flags |= 0x800;
    }
    if (_ACTCharStatus_Check(self, 0)) {
        flags |= 0x400;
    }
    if (_ACTCharStatus_Check(self, 4)) {
        flags |= 0x4000;
    }
    if (_ACTCharStatus_Check(self, 5)) {
        flags |= 0x8000;
    }
    if (_ACTCharStatus_Check(self, 28)) {
        flags |= 0x2;
    }
    if (_ACTCharStatus_Check(self, 29)) {
        flags |= 0x4;
    }
    if (_ACTCharStatus_Check(self, 30)) {
        flags |= 0x8;
    }
    if (_ACTCharStatus_Check(self, 2)) {
        flags |= 0x1000;
    }
    if (_ACTCharStatus_Check(self, 23)) {
        flags |= 0x100000;
    }
    if (_ACTCharStatus_Check(self, 14)) {
        flags |= 0x10;
    }
    if (_ACTCharStatus_Check(self, 10)) {
        flags |= 0x10000;
    }
    if (_ACTCharStatus_Check(self, 13)) {
        if (*(float *)(s + 0x64) < 1000.0f) {
            flags |= 0x40000;
        }
        if (*(float *)(s + 0x64) < 300.0f) {
            flags |= 0x80000;
        }
    }
    for (i = 0; i < 21; i++) {
        int kind = lookTargetData[i].kind[col];
        if ((flags >> i) & 1) {
            if (GetTarget(kind, pos, &mode) != 0) {
                found = 1;
                break;
            }
        }
    }
    if (found != 0) {
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x380) = pos[0];
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x384) = pos[1];
        *(float *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x388) = pos[2];
        *(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x370) = mode;
    } else {
        GOBJ_SUB(self)->root.lookMode = 0;
    }
}

static void ACTItemWatchMotion(GObj *self)
{
    Act *sub = GOBJ_ACT(self);
    int mode;
    int frame;

    /* nested inline: the "take the pending item" request, expanded at the four
       motion arms below */
    inline void ItemHold(void) /* derived name */
    {
        if (sub->heldItem.i != 0) {
            return;
        }
        if ((sub->heldItem.i = sub->nextItem.i) == 0) {
            return;
        }
        HoldItem(sub->heldItem.p, self);
    }

    /* nested inline: drop whatever is held, read through the slots' pointer
       member */
    inline void ItemRelease(void) /* derived name */
    {
        if (sub->heldItem.p == 0) {
            return;
        }
        ReleaseItem(sub->heldItem.p);
        sub->nextItem.p = sub->heldItem.p = 0;
    }

    /* a GNU nested function, reading `sub` and `self` through the static
       chain */
    void ACTItemThrow(void)
    {
        float v[4];

        if (sub->heldItem.i == 0) {
            return;
        }
        sceVu0ScaleVector(v, test_CURRENTORIENT(self),
                          _ACTGame_GetParamF(8) * 60.0f /
                              (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (GOBJ_SUB(sub->heldItem.p)->modelId == 65) {
            debug_StdPrintfDummy("BOMB!!\n");
            v[0] *= 0.5f;
            v[1] -= 25.0f;
            v[2] *= 0.5f;
        }
        ThrowItem(sub->heldItem.p, v);
        sub->nextItem.i = sub->heldItem.i = 0;
    }

    /* the line maps put `sub` on the body's first line and these two
       statements after the nested functions */
    mode = motionKind[GOBJ_SUB(self)->ctrl.motion].modeBits.h.hi & 7;
    frame = motionKind[GOBJ_SUB(self)->ctrl.motion].modeBits.b;

    switch (mode) {
    case 2:
        if ((float)frame < GOBJ_SUB(self)->ctrl.animFrame) {
            ItemHold();
        } else {
            float pos[4];
            GetRootPosition(pos, sub->heldItem.p);
            SetDirectRootPositionNoFittingWithNodePoint(self, 0x16, pos, 0.2f);
            debug_StdPrintfDummy("!!\n");
        }
        break;

    case 4:
        if (GOBJ_SUB(self)->ctrl.animFrame < (float)frame) {
            ItemHold();
        } else {
            ItemRelease();
        }
        break;

    case 3:
        if (GOBJ_SUB(self)->ctrl.animFrame < (float)frame) {
            ItemHold();
        } else {
            ACTItemThrow();
        }
        break;

    case 1:
        ItemHold();
        break;

    case 0:
        ItemRelease();
        break;
    }

    if (self == boyGObj) {
        *(int *)((char *)sub + 0x134) = sub->heldItem.i;
        SetBoyInfo(sub->weapon, (void *)sub->heldItem.p);
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
    sceVu0ScaleVector(p0, (float *)GetCurrentCameraSet2(), -1.0f);
    sceVu0ScaleVector(p1, test_CURRENTROOT(girlGObj), -1.0f);
    InsertCamera_Set(p0, p1,
                     _ACTGame_GetParamF(9) *
                         (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f);
}

void RequestChangeHandMode(GObj *self, int mode, int pri, int flag, GObj *p5, int p6, float *p7)
{
    HandModeCmd *hmc = 0;

    /* updateHMC is a GNU nested function: it reads self, mode, pri, flag, p5,
       p6, p7 and hmc out of RequestChangeHandMode's frame through the
       static chain. */
    void updateHMC(void)
    {
        hmc->flag = flag;
        hmc->pri = pri;
        switch (mode) {
        case 0:
            GOBJ_SUB(self)->root.hand0.mode = hmc->flag;
            GOBJ_SUB(self)->root.hand0.obj = p5;
            GOBJ_SUB(self)->root.hand0.node = p6;
            if (p7 != 0) {
                GOBJ_SUB(self)->root.hand0.pos[0] = p7[0];
                GOBJ_SUB(self)->root.hand0.pos[1] = p7[1];
                GOBJ_SUB(self)->root.hand0.pos[2] = p7[2];
            }
            break;
        case 1:
            GOBJ_SUB(self)->root.hand1.mode = hmc->flag;
            GOBJ_SUB(self)->root.hand1.obj = p5;
            GOBJ_SUB(self)->root.hand1.node = p6;
            if (p7 != 0) {
                GOBJ_SUB(self)->root.hand1.pos[0] = p7[0];
                GOBJ_SUB(self)->root.hand1.pos[1] = p7[1];
                GOBJ_SUB(self)->root.hand1.pos[2] = p7[2];
            }
            break;
        }
    }

    switch (mode) {
    case 0:
        hmc = (HandModeCmd *)((char *)GOBJ_ACT(self)->enemy + 0x314);
        break;
    case 1:
        hmc = (HandModeCmd *)((char *)GOBJ_ACT(self)->enemy + 0x31C);
        break;
    default:
        debug_assert("src/act-game.c", 3769);
        __assert("src/act-game.c", 3769, "0");
        break;
    }
    if (pri < 3) {
        if (pri > 0) {
            if (flag == 0) {
                if (hmc->pri != pri) {
                    return;
                }
            }
        }
    }
    if (hmc->pri == 0 || hmc->flag == 0) {
        updateHMC();
    } else if (pri >= hmc->pri) {
        updateHMC();
    }
}
