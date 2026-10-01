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

typedef struct {
    char pad0[28];
    int f_1C;
    char _20[4];
} WeaponEntry;

typedef struct {
    long long w;
} __attribute__((packed)) U64ag;

typedef struct {
    char pad0[32];
    float _20, _24, _28;
    char pad2C[68];
    float _70;
    char pad74[12];
    int _80;
    char pad84[4];
    int _88;
    int _8c;
    char pad90[4];
    int _94;
    int _98;
    char pad9C[36];
} HandWork;

/* The 0x194-byte-per-entry motion record table, indexed by the object's
   current motion id (obj->0x15C->0x4A0). */
typedef struct {
    char pad0[336];
    int f_150;
    char pad154[44];
    short f_180;
    short f_182;
    short f_184;
    char pad186[2];

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;

        char b;
    } u_188;

    unsigned int f_18C;
    unsigned int f_190;
} MotionRec;

extern MotionRec motionKind[];

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4S;

/* kept local: agrees with boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void SetBoyInfo(int *a0, int *a1);
/* kept local: agrees with boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void BoyInfoUpdate_StageChange(void);

/* One table: a 100-entry object list, two parallel per-entry int arrays
   (the full view result and the simple one), the entry count and the
   round-robin cursor the loop below advances one entry per frame. */
typedef struct {
    GObj *obj[100];  /* 0x000 */
    int view[100];   /* 0x190 */
    int simple[100]; /* 0x320 */
    int num;         /* 0x4B0 */
    int cur;         /* 0x4B4 */
} ActGameViewTbl;

/* .bss, owned by act-game.o: the view table described below.  It is the TAIL
   of act-game.o's .bss run; the 0x440 bytes before it are not reached from
   anywhere in the ROM and stay in the blob. */
static ActGameViewTbl actGameView;

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* The motion-play-speed-ratio mode at work+0x54 is an enumerated mode, not a
   plain int: ACTGame_SetMotionPlaySpeedRatio_Exec dispatches on 0..2, and the
   ROM proves the type here -- only an enum-typed store lets the scheduler
   hoist the neighbouring +0x37C timer load past it (an `int` store aliases
   that load and pins it below). */
typedef enum { MPSR_OFF, MPSR_ONESHOT, MPSR_HOLD } MpsrMode;

/* The 64-bit actor status words are a union view in the dev's TU: the ROM
   re-reads sub+0x18 after every `int` store to the work block, which only a
   union whose members include a 32-bit integer produces -- a plain
   `unsigned long long` load survives an `int` store under TBAA. */

/* self->0x164->0x688 -- the per-actor motion work block.  Every use in this
   function re-derives the chase (the ROM reloads both links after each
   store), so it is spelled as one accessor rather than a cached local. */
#define ACTWORK(g) ((char *)GOBJ_ACT(g)->work)

/* The environment work block the actor rebuilds every frame: 464 bytes at
   +0x4B0, plus the four sub-blocks that survive the rebuild. */
typedef struct {
    long long d[0x1D0 / 8];
} EnvWork;

/* 8-aligned 16-byte and 4-aligned 32-byte sub-blocks of that work area. */
typedef struct {
    long long d[2];
} EnvPair;

typedef struct {
    float f[8];
} EnvOct;

/* kept local and unprototyped: weapon.h declares CheckWeaponKind(char *), and
   ACTGame_isWeaponCombustible calls it with no argument */
extern int CheckWeaponKind();

/* The actor's orient-request bitfield: three 64-bit request words at
   sub+0x478, each paired with the permission mask 16 bytes further on. */
#define ORQ(s, i) (((ActStatusWord *)((s) + 0x478))[i].q)
#define ORM(s, i) (((ActStatusWord *)((s) + 0x478))[(i) + 2].q)
#define ORBIT(w, b) ((int)((w) >> (b)) & 1)

/* The pair of hand-link wall probes the debug overlay draws, mirrored into
   the actor work area at +0x540; handClInfoClear is the cleared template
   each frame starts from. */
typedef struct {
    unsigned char on;   /* 0x00 */
    unsigned char hit;  /* 0x01 */
    unsigned char attr; /* 0x02 */
    char pad3[13];
    long long orient[2]; /* 0x10 -- GetOrientOfWall's output */
    unsigned char hit2;  /* 0x20 */
    unsigned char attr2; /* 0x21 */
    char pad22[14];
    long long orient2[2]; /* 0x30 */
} HandClInfo;

static HandClInfo handClInfoClear = {0}; /* derived name */

/* The hand-mode rows the motion record's two hand nibbles index: 16 bytes a
   row, the mode RequestChangeHandMode wants in the last word. */
typedef struct {
    char pad0[12];
    int mode;
} HandModeRow;

extern HandModeRow motionIKEffKind[];
/* kept local: brain.h is not in this TU's include list and does not declare
   brainAddLevelGirlDetail */
extern void brainAddLevelGirlDetail(int a0, float f);
void ACTItemWatchMotion(GObj *self);
/* kept local: agrees with boyact.h, which this TU does not include (PrivInsCamSet differs) */
extern void SetBoyInfo(int *a0, int *a1);
/* kept local: f5 is int here, float in boyact.h; a7 is float here, unsigned char in boyact.h */
extern void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, int a5, float f6,
                          float f1);

/* The pending hand-mode command record: two ints at +0x314 (connect) and
   +0x31C (disconnect) of the actor's hand work block. */
typedef struct {
    int f_0;
    int f_4;
} HandModeCmd;

/* kept local: agrees with weapon.h, which this TU does not include (CheckWeaponKind differs) */
extern int GetTorchGObjOfWeapon(char *a0);
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

inline int ACTGame_CheckHandMotion(char *a0, char *a1)
{
    MotionRec *rec0 = &motionKind[GOBJ_SUB(a0)->ctrl.motion];
    MotionRec *rec1 = &motionKind[GOBJ_SUB(a1)->ctrl.motion];
    int b0 = (rec0->f_18C >> 18) & 1;
    int b1 = (rec1->f_18C >> 18) & 1;
    return b0 & b1;
}

inline int ACTGame_CheckItemMotion(GObj *a0)
{
    MotionRec *rec = &motionKind[GOBJ_SUB(a0)->ctrl.motion];
    return (rec->u_188.w >> 19) & 7;
}

void ACTGame_SaveActorInformation(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    if (((int)(s->flags18.ll >> 39) & 1) && s->modeFrame % 30 == 0) {
        gamesysObjInfoPosSetStage(a0, s->infoPos, 0, stage_no);
    }
}

void ACTGame_DeleteActorInformation(GObj *a0)
{
    gamesysObjInfoCls(a0->kind, a0->labelId);
}

void EXITDATA_GetNextPosition(int idx, float *pos, float *rot)
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
            _ApplyRyGV(&buf2, -tmp_b[1]);
            sceVu0AddVector(tmp_a, tmp_a, &buf2);
        }
    }
    gamesysObjInfoPosNewStageSet(self->labelId, self->kind, exitData[idx].nextStage, tmp_a, tmp_b);
}

inline void ACTGame_StageChangeGObjDirect(GObj *a0, int a1, void *a2, int a3)
{
    float buf0[4];
    float buf1[4];
    memset(buf1, 0, 0x10);
    buf1[1] = (float)a3 * 3.1415927f / 180.0f;
    sceVu0ScaleVector(buf0, a2, -1.0f);
    gamesysObjInfoPosNewStageSet(a0->labelId, a0->kind, a1, buf0, buf1);
}

/* act-game.c:1069-1075 -- the exit whose f_24 names this stage. */
static inline int getExitIndexOfStage(int stage)
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
    char *boy;
    char *girl;
    int idx;

    boy = 0;
    girl = 0;
    idx = getExitIndexOfStage(stage);
    gflagOn(394);
    if (flag != 0) {
        if (boyGObj != 0) {
            Act *s = GOBJ_ACT(boyGObj);
            boy = (char *)s->weapon;
            girl = s->curItem;
            SetBoyInfo((int *)boy, (int *)girl);
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
                        gamesysObjInfoPosNewStageSet(*(int *)(boy + 8), *(int *)(boy + 0xC), stage,
                                                     pos, rot);
                    }
                    if (girl != 0) {
                        gamesysObjInfoPosNewStageSet(*(int *)(girl + 8), *(int *)(girl + 0xC),
                                                     stage, pos, rot);
                    }
                }
            }
        }
    }
}

inline int ACTGame_FLAG_LIFEPINCH(GObj *a0)
{
    if (GOBJ_ACT(a0)->life <= 20.0f)
        return 1;
    return 0;
}

/* Returns a char-width boolean: the three PAIR_IsStatus_* sites the listing
   inlines this into all mask the result with `andi 0xff`, which only a
   narrower-than-int return type produces.  The `int` intermediate keeps the
   SI->QI conversion at the `return`; folding it into the `& 1` (i.e. writing
   the expression directly in the return) makes gcc distribute the narrowing
   over the mask and emit a second `andi`. */
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
    RequestChangeHandMode((char *)boyGObj, 1, 5, 5, (int)((char *)girlGObj), 0, 0);
}

void ACTGame_TryDisconnectHand(void)
{
    RequestChangeHandMode((char *)boyGObj, 1, 5, 0, 0, 0, 0);
}

inline void ACTGame_ConnectHand(void)
{
    Act *s = GOBJ_ACT(((char *)girlGObj));
    RequestChangeHandMode(((char *)girlGObj), 0, 5, 6, (int)boyGObj, 0, 0);
    RequestChangeHandMode((char *)boyGObj, 1, 5, 5, (int)((char *)girlGObj), 0, 0);
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
    RequestChangeHandMode(((char *)girlGObj), 0, 5, 0, 0, 0, 0);
    RequestChangeHandMode((char *)boyGObj, 1, 5, 0, 0, 0, 0);
    s->flags18.ll &= ~(1ULL << 40);
}

inline unsigned char ACTGame_CheckPriInputFrame(GObj *a0)
{
    short e;
    short s;

    e = motionKind[GOBJ_SUB(a0)->ctrl.motion].f_184;
    if ((float)e < GOBJ_SUB(a0)->ctrl.animFrame && e != -1) {
        return 1;
    }
    s = motionKind[GOBJ_SUB(a0)->ctrl.motion].f_180;
    if (s != -1 && GOBJ_SUB(a0)->ctrl.animFrame < (float)s) {
        return 1;
    }
    return 0;
}

inline int ACTGame_GetCurrentCallStatus(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);

    if (a0 != boyGObj) {
        return 0;
    }
    switch (motionKind[GOBJ_SUB(a0)->ctrl.motion].u_188.h.hi & 7) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 0;
    }
    if (((int)(s->wish0.ll >> 46) & 1) && ((int)(s->wish2.ll >> 46) & 1)) {
        /* The ROM'(char *)s `sltiu 4; beqz` then `st != 0` pair is the decision tree
           of a switch on an unsigned index (listing row 1298 holds the whole
           dispatch, rows 1299-1306 are code-free case lines); the cast
           stands for the status field'(char *)s own unsigned type, which the bytes
           cannot name. */
        switch ((unsigned int)s->actMode) {
        case 1:
        case 2:
        case 3:
            return 2;
        }
    }
    return 0;
}

inline void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    a0[0] = q[0x510 / 4];
    a0[1] = q[0x514 / 4];
    a0[2] = q[0x518 / 4];
    a1[0] = q[0x520 / 4];
    a1[1] = q[0x524 / 4];
    a1[2] = q[0x528 / 4];
}

inline int PAIR_IsStatus_BOY_DITCH(void)
{
    char *b = (char *)boyGObj;

    switch ((unsigned int)GOBJ_ACT(b)->actMode) {
    case 0x58:
        if (motionKind[GOBJ_SUB(b)->ctrl.motion].f_150 != 1) {
            break;
        }
        /* fall through */
    case 0x59:
    case 0x5C:
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

inline void PAIR_GetPosition_BOY(float *a0, float *a1)
{
    float *q = (float *)(char *)GOBJ_ACT(boyGObj);
    a0[0] = q[0x500 / 4];
    a0[1] = q[0x504 / 4];
    a0[2] = q[0x508 / 4];
    a1[0] = q[0x4C0 / 4];
    a1[1] = q[0x4C4 / 4];
    a1[2] = q[0x4C8 / 4];
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

inline int PAIR_IsStatus_BOY_WAIT(void)
{
    char *b = (char *)boyGObj;

    if (b != 0) {
        switch ((unsigned int)GOBJ_ACT(b)->actMode) {
        case 0x4E:
        case 0x58:
            if (motionKind[GOBJ_SUB(b)->ctrl.motion].f_150 == 1) {
                return 1;
            }
            break;
        }
    }
    return 0;
}

inline int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work._70 = f;
    sceVu0CopyVector(&work, p0);
    sceVu0CopyVector((char *)&work + 0x10, p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (work._88 == 0) {
        ClipFloor(&work);
        if (work._94 == 0) {
            rv = 0;
        }
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv & 0xFF;
}

inline int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout,
                            void *magtarget, int *flagout)
{
    HandWork work;
    int flag;
    int rv;
    int cnt;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work._70 = f;
    sceVu0CopyVector(&work, hand0);
    sceVu0CopyVector((char *)&work + 0x10, hand1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (flagout != 0) {
        *flagout = work._98;
    }
    cnt = work._88;
    if (cnt == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    if (cnt != 0 && magtarget != 0) {
        GetOrientOfWall(magtarget, cnt, &work._80);
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv & 0xFF;
}

inline int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3)
{
    char buf[192];
    memset(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 0x10, a1);
    ClipWall(buf);
    if (a2 != 0) {
        *a2 = *(int *)(buf + 0x98);
    }
    if (a3 != 0) {
        *(U64ag *)a3 = *(U64ag *)(buf + 0x80);
        *(int *)(a3 + 8) = *(int *)(buf + 0x88);
    }
    return *(int *)(buf + 0x88) != 0;
}

void *floorGObj_ACTCheckCollis_WELL;

void *wallGObj_ACTCheckCollis_WAY;

/* the float is the LAST parameter, not the first: girl_act.c's
   subGirlBrain_Pulledup call site puts `mtc1 $0,$f12` after the fourth
   pointer's argument move, and load_register_parameters emits the moves in
   declared order, which is what breaks the scheduler's INSN_LUID tie there
   (the same class as ACTGame_SetMotionPlaySpeedRatio_Reserve).  The EE ABI
   puts the single float in $f12 wherever it sits, so this function's own
   bytes do not change. */
inline int ACTCheckCollis_WELL(void *p0, void *p1, void *actor, void *posout, float f)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work._70 = f;
    floorGObj_ACTCheckCollis_WELL = 0;
    sceVu0CopyVector(&work, p0);
    sceVu0CopyVector((char *)&work + 0x10, p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipFloor(&work);
    if (work._94 == 0) {
        rv = 0;
    } else {
        floorGObj_ACTCheckCollis_WELL = (void *)work._8c;
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    return rv;
}

inline unsigned char ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout)
{
    HandWork work;
    int flag;
    int attr;

    memset(&work, 0, 0xC0);
    flag = actor ? GOBJ_SUB(actor)->disp : 0;
    work._70 = f;
    wallGObj_ACTCheckCollis_WAY = 0;
    sceVu0CopyVector(&work, p0);
    sceVu0CopyVector((char *)&work + 0x10, p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    attr = work._98;
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    /* The wall record is published on BOTH paths: SRCFILE.TXT rows put the
       surviving `sw ...%gp_rel(wallGObj_ACTCheckCollis_WAY)` on line 1586 with a seven-line
       gap (1579-1585) above it, i.e. an else arm; jump.c cross-jumps the two
       copies back into the one store ROM carries. */
    if (work._88 == 0) {
        if (flag != 0) {
            GOBJ_SUB(actor)->disp = 0;
        }
        ClipWallField(&work);
        if (flag != 0) {
            GOBJ_SUB(actor)->disp = 1;
        }
        if (work._88 == 0) {
            return 0;
        }
        wallGObj_ACTCheckCollis_WAY = (void *)work._80;
    } else {
        wallGObj_ACTCheckCollis_WAY = (void *)work._80;
    }
    if (CompareAttribute(attr, 0x30000) != 0) {
        return 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    return 1;
}

inline unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;

    if (!(_DistSqGV((int *)p0, p1) < 25000000.0f)) {
        return 1;
    }

    work._70 = f;
    sceVu0CopyVector(&work, p0);
    sceVu0CopyVector((char *)&work + 0x10, p1);
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (work._88 == 0) {
        ClipFloor(&work);
        if (work._94 == 0) {
            rv = 0;
        }
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv;
}

int ACTCheckView(GObj *self, void *a1, void *a2, int range, float f)
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
    if (_DistGV(pos, a2) < f) {
        return 1;
    }
    if (range >= 360) {
        return 1;
    }
    /* SRCFILE.TXT rows put the whole of each arm on ONE source line (1666 /
       1667) -- a three-component vector set; v[3] is zeroed on the next line.
       The duplicated v[0]/v[2] stores are cross-jumped back into one copy. */
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
    sceVu0SubVector(d, a2, pos);
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

inline int ACTCheckViewCl(GObj *self, void *a1, void *a2, int range, float f)
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
    if (ACTCheckView(self, a1, a2, range, f) == 0) {
        return 0;
    }
    return ACTCheckCollis_VIEW(0.0f, pos, a2, a1) == 0;
}

inline int ACTCheckViewClDetail(GObj *self, void *a1, void *a2, int range, float f)
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
    ret = ACTCheckView(self, a1, a2, range, f);
    if (ACTCheckCollis_VIEW(0.0f, pos, a2, a1)) {
        return 0;
    }
    if (ret != 0) {
        return 1;
    }
    return 2;
}

/* actGameView is one table: a 100-entry object list at +0x000, two parallel
   100-entry int arrays at +0x190 and +0x320, and the entry count at +0x4B0.
   The list slot holds a pointer, so its store is in a different alias set
   from the two int stores -- that is what lets ROM schedule the +0x190
   address ahead of the list address. */
inline void ACTGameView_Add(GObj *a0, GObj *a1)
{
    int n = actGameView.num++;
    if (n >= 100) {
        debug_StdPrintfDummy("too many view check object");
        debug_assert("src/act-game.c", 1791);
        __assert("src/act-game.c", 1791, "0");
    }
    actGameView.obj[n] = a1;
    actGameView.view[n] = 0;
    actGameView.simple[n] = 0;
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

/* The view work record is reached as `self->act->view`, and the two chase
   loads are spelled as int reads: that puts them in the same alias set as the
   table's own int fields, so the `simple[i]` / `cur` stores in the later arms
   invalidate the chase and the arm re-reads it, while the record's own
   pointer slots (the clip callback, the target object, the cleared result
   pointer) leave it alone. */
void ACTGameView_Loop(GObj *self)
{
    float pos[4];
    int i;

    i = actGameView.cur;
    if (actGameView.simple[i] != 0) {
        GetRootPosition(pos, actGameView.obj[i]);
        actGameView.view[i] = ACTCheckView(self, actGameView.obj[i], pos, 150, 300.0f);
    } else {
        actGameView.view[i] = 0;
    }

    switch (GOBJ_WORK(self)->viewState) {
    case 0:
        if (5000.0f < _DistGV(test_CURRENTROOT(self), test_CURRENTROOT(actGameView.obj[i]))) {
            GOBJ_WORK(self)->viewState = 6;
        } else {
            GOBJ_WORK(self)->viewState = 1;
        }
        break;
    case 1:
        *(void (**)(void *))(GOBJ_ACT(self)->work + 0x7F4) = ClipWall;
        GOBJ_WORK(self)->viewObj = actGameView.obj[i];
        GOBJ_WORK(self)->view7A0 = 0;
        GetSkeltonPosition((float *)(GOBJ_ACT(self)->work + 0x730), self, 0x23);
        GetRootPosition(GOBJ_ACT(self)->work + 0x740, actGameView.obj[i]);
        RequestClipCollision(GOBJ_ACT(self)->work + 0x720);
        GOBJ_WORK(self)->viewState = 2;
        break;
    case 2:
        if (GOBJ_WORK(self)->view720 != 0) {
            if (GOBJ_WORK(self)->view7B8 != 0) {
                GOBJ_WORK(self)->viewState = 6;
            } else {
                GOBJ_WORK(self)->viewState = 3;
            }
        }
        break;
    case 3:
        *(void (**)(void *))(GOBJ_ACT(self)->work + 0x7F4) = ClipFloor;
        GOBJ_WORK(self)->viewObj = actGameView.obj[i];
        GOBJ_WORK(self)->view7A0 = 0;
        GetSkeltonPosition((float *)(GOBJ_ACT(self)->work + 0x730), self, 0x23);
        GetRootPosition(GOBJ_ACT(self)->work + 0x740, actGameView.obj[i]);
        RequestClipCollision(GOBJ_ACT(self)->work + 0x720);
        GOBJ_WORK(self)->viewState = 4;
        break;
    case 4:
        if (GOBJ_WORK(self)->view720 != 0) {
            if (GOBJ_WORK(self)->view7C4 != 0) {
                GOBJ_WORK(self)->viewState = 6;
            } else {
                GOBJ_WORK(self)->viewState = 5;
            }
        }
        break;
    case 5:
        actGameView.simple[i] = 1;
        GOBJ_WORK(self)->viewState = 7;
        break;
    case 6:
        actGameView.simple[i] = 0;
        GOBJ_WORK(self)->viewState = 7;
        break;
    case 7:
        actGameView.cur++;
        if (!(actGameView.cur < actGameView.num)) {
            actGameView.cur = 0;
        }
        GOBJ_WORK(self)->viewState = 0;
        break;
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

void ACTGame_LwsEffectProcess(GObj *a0)
{
    int m = GOBJ_ACT(a0)->enemy->lwsEffect;
    if (m != 0) {
        DispMultiBgaManagerWithKind(0x1F8, m, 1);
    }
}

inline void ACTGame_LwsEffectInit(GObj *a0)
{
    GOBJ_ACT(a0)->enemy->lwsEffect = InitMultiBgaManager(1);
}

inline void ACTGame_LwsEffect_Guard(GObj *a0)
{
    float q[4];
    float v[4];
    EnemyBattleWork *p;

    _OrientXZGV(v, test_CURRENTROOT(boyGObj), test_CURRENTROOT(a0));
    ActGame_GetOrientQ(q, v, 0);

    stage_SetLoopFlag(504, 0);
    stage_SetFrameStep(0x1F8, 1);
    p = GOBJ_ACT(a0)->enemy;
    EntryMultiBgaManager(p->lwsEffect, 0, -1, test_CURRENTROOT(a0), q);
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

inline void ACTCharctrl_Lock(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    s->flags18.ll &= ~(1ULL << 48);
    s->flags18.ll &= ~(1ULL << 49);
}

inline void ACTCharctrl_Unlock(GObj *a0)
{
    Act *p = GOBJ_ACT(a0);
    p->flags18.ll |= (1ULL << 48);
    p->flags18.ll |= (1ULL << 49);
}

inline int *ACTGame_GetNearestGObj(GObj *a0, int a1)
{
    float best_val = 3.40282347e+38f; /* FLT_MAX */
    int *best = 0;
    GObj *node;

    node = isysGObjSearchFromObjKindID_begin(a1);
    if (node != 0) {
        do {
            float val = _DistSqGV(test_CURRENTROOT(node), a0);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
    return best;
}

inline void _GetRootObjectOrient(void *a0, char *a1)
{
    float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    sceVu0ApplyMatrix(a0, (void *)GOBJ_SUB(a1)->nodeMtx, v);
}

inline int ACTGame_isWeaponEnableCatchfire(int *self)
{
    int ret = 0;
    unsigned long combustible = ACTGame_isWeaponCombustible();
    if (combustible) {
        ret = GetTorchGObjOfWeapon((char *)self);
    }
    return ret;
}

inline GObj *ACTGame_isHangChain(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    if (a0 == boyGObj) {
        const ActModeRec *attr = &actModeTbl[s->actMode];
        if (attr->onChain) {
            return s->chain;
        }
    }
    return 0;
}

inline int ACTGame_GetMotOrientFromWeapon(GObj *a0)
{
    int rv;
    if (a0 != 0) {
        rv = weaponKind[CheckWeaponKind(a0)].f_1C;
    } else {
        rv = 0;
    }
    return rv;
}

inline unsigned char ACTGame_NoWeapon(GObj *a0)
{
    char *w = (char *)GOBJ_ACT(a0)->weapon;
    unsigned char r = 0;
    if (w == 0 || CheckWeaponKind(w) == 0)
        r = 1;
    return r;
}

inline int ACTGame_isWeaponCombustible(void)
{
    return CheckWeaponKind() == 1;
}

/* Both absolute values are MACRO-shaped: ROM re-calls test_CURRENTROOT twice
   per arm of the height test and _RotyGV once per arm of the angle test, i.e.
   the classic `((x) < 0 ? -(x) : (x))` triple evaluation. */
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

inline void ACTLookTarget_Init(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    s->lookTarget = 0;
    s->lookMode = 0;
    s->lookPri = 0;
}

inline int _ACTLookTarget_Set(GObj *a0, GObj *a1, float *a2, int a3, int a4)
{
    Act *s = GOBJ_ACT(a0);
    int ret = 0;

    if (a3 == 6) {
        ACTLookTarget_Init(a0);
    } else if (a3 >= s->lookPri) {
        s->lookTarget = a1;
        if (a2 != 0) {
            s->lookPosX = a2[0];
            s->lookPosY = a2[1];
            s->lookPosZ = a2[2];
        }
        s->lookMode = a4;
        s->lookPri = a3;
        ret = 1;
    }
    return ret;
}

int ACTLookTarget_Exec(GObj *a0)
{
    float pos[4];
    Act *s = GOBJ_ACT(a0);
    char *t = (char *)s->lookTarget;
    int rv;
    int b0;

    if (debug_font_flag & 1) {
        debug_Printf(10, 170, 0x0FFFFFFF, "mode=[%d]\n", GOBJ_SUB(a0)->root.lookMode);
    }
    rv = 0;
    if (s->lookPri == 0) {
        GOBJ_SUB(a0)->root.lookMode = 0;
    } else {
        if (t == 0) {
            pos[0] = s->lookPosX;
            pos[1] = s->lookPosY;
            pos[2] = s->lookPosZ;
        } else if (t == (char *)boyGObj) {
            /* the boy's skeleton position read in place: the listing gives
               the focus-node call line 2243 and all three copies line 2244,
               not GetSkeltonPosition's lines, which it defines later (2597) */
            int idx = GetSkeltonFocusNode(t, 35) << 6;
            pos[0] = *(float *)(idx + *(int *)(((IntFloat *)(t + 0x15C))->i + 0xC) + 0x30);
            pos[1] = *(float *)(idx + *(int *)(((IntFloat *)(t + 0x15C))->i + 0xC) + 0x34);
            pos[2] = *(float *)(idx + *(int *)(((IntFloat *)(t + 0x15C))->i + 0xC) + 0x38);
        } else {
            GetRootPosition(pos, t);
        }
        b0 = s->lookMode;
        rv = 1;
        ((IntFloat *)((char *)(int)GOBJ_SUB(a0) + 0x390))->f = pos[0];
        ((IntFloat *)((char *)(int)GOBJ_SUB(a0) + 0x394))->f = pos[1];
        ((IntFloat *)((char *)(int)GOBJ_SUB(a0) + 0x398))->f = pos[2];
        GOBJ_SUB(a0)->root.lookMode = b0;
    }
    return rv;
}

inline void ACTParaStatus_Init(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    ActPara_InitSystem();
    ACTParaStatus_Clear(a0);
    ActPara_MakeTbl(GOBJ_ACT(a0)->work, s->paraStatus, 0);
    *(long long *)((char *)s + 0x98) = s->paraStatus;
}

void ACTParaStatus_Clear(GObj *a0)
{
    GOBJ_ACT(a0)->paraStatus = 0;
    _ACTParaStatus_Set(a0, 0);
}

inline void _ACTParaStatus_Set(GObj *a0, int bit)
{
    Act *s = GOBJ_ACT(a0);
    *(unsigned long long *)((char *)s + 0x90) |= (1ULL << bit) & ~(unsigned long long)s->flags;
}

inline unsigned long long _ACTParaStatus_Check(GObj *a0, int bit)
{
    Act *s = GOBJ_ACT(a0);
    return ((unsigned long long)s->paraStatus >> bit) & 1;
}

void ACTParaStatus_Exec(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    Sub15C *sub;
    EnemyBattleWork *p;
    int changed;

    changed = 0;
    if ((int)(s->flags20.ll >> 16) & 1) {
        _ACTParaStatus_Set(self, 42);
    }
    if ((int)(s->flags20.ll >> 17) & 1) {
        _ACTParaStatus_Set(self, 43);
    }
    if ((unsigned long long)s->paraStatus != s->lastParaStatus) {
        s->lastParaStatus = (unsigned long long)s->paraStatus;
        changed = 1;
    }
    p = s->enemy;
    if ((p->paraTimer)++ >= 121) {
        sub = GOBJ_SUB(self);
        if ((sub->ctrl.ctrlFlags & 0x16) || (int)sub->ctrl.frameEnd != 0) {
            if (motionKind[sub->ctrl.motion].f_150 == 1) {
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
    ActPara_MakeTbl(GOBJ_ACT(self)->work, s->paraStatus, GOBJ_ACT(self)->enemy->paraRandom);
    SetParallelMotionTable(self, GOBJ_ACT(self)->work, ActPara_GetDefTbl(), 0,
                           (int)GOBJ_WORK(self)->parallelInterp);
}

inline void _ACTCharStatus_Init(int **a0)
{
    long long *p = (long long *)a0[0x59];
    p[0xB] = 0;
    p[0xC] = 0;
}

void _ACTCharStatus_Clear(void *a0)
{
    Act *s = GOBJ_ACT(a0);
    int old = s->statusOther;
    int *sel;
    int *g;
    float nearest;
    float d;

    memset((char *)s + 0x58, 0, 0x38);
    if (a0 == (char *)boyGObj || a0 == ((char *)girlGObj)) {
        nearest = 3.40282347e+38f; /* FLT_MAX */
        sel = 0;
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            d = _DistGV(test_CURRENTROOT(a0), test_CURRENTROOT(g));
            if (actEnemyFlagCheckActive(g)) {
                if (d < nearest) {
                    sel = g;
                    nearest = d;
                }
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        *(int **)((char *)s + 0x7C) = sel;
        if (a0 == (char *)boyGObj) {
            if (old != 0 &&
                s->frame % ((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 2) != 0) {
                s->statusOther = old;
            }
        }
    }
}

inline void _ACTCharStatus_Set(GObj *a0, int bit, float f, int val)
{
    Act *s = GOBJ_ACT(a0);

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

inline unsigned char _ACTCharStatus_Check(GObj *a0, int bit)
{
    Act *s = GOBJ_ACT(a0);
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

inline void ACTGame_SetMotionPlaySpeedRatio_Clear(GObj *a0)
{
    EnemyBattleWork *p = GOBJ_ACT(a0)->enemy;
    p->speedRatio = 1.0f;
    *(MpsrMode *)((char *)p + 0x54) = MPSR_OFF;
}

inline void ACTGame_SetMotionPlaySpeedRatio_Reserve(GObj *a0, float f, unsigned int a1)
{
    EnemyBattleWork *p = GOBJ_ACT(a0)->enemy;
    if (p->speedRatioPri <= a1) {
        p->speedRatio = f;
        p->speedRatioPri = a1;
    }
}

/* The play-speed ratio's debug override, built only when DEBUG is defined:
   the debug build can pin the ratio from the debugger before it is applied;
   the retail build does not define DEBUG, so the helper has no body.  The
   January link runs its own debug check at the same place (listing rows
   2532-2537: the motion viewer's mode word, which sets the viewed object's
   speed itself, guards the call).  WHAT THE BYTES PIN: the Exec's text takes
   one of its locals' address, so the function uses ADDRESSOF and
   sibcall.c:404-419 keeps the final call a jal with a frame (the plain call
   is a `j`, and a body with a sibling call is never inlined, integrate.c
   226-232, where the ROM inlines it into ACTGame_CommonLoop);
   purge_addressof then returns ratio to its register, so nothing is stored.
   WHAT THEY CANNOT PIN: which local, the helper's name or its debug body,
   which are ours. */
static __inline__ void speedRatioDebugOverride(float *ratio)
{
#ifdef DEBUG
    if (dbgSpeedRatioFix) {
        *ratio = dbgSpeedRatio;
    }
#endif
}

inline void ACTGame_SetMotionPlaySpeedRatio_Exec(GObj *a0)
{
    float ratio;
    int keep;

    ratio = 1.0f;
    keep = (unsigned int)(int)GOBJ_ACT(a0)->enemy->speedRatioPri < 3 && a0 == girlGObj;
    if ((int)GOBJ_ACT(a0)->enemy->speedRatioPri == 1) {
        if (((&motionKind[GOBJ_SUB(a0)->ctrl.motion])->f_18C >> 30) & 1) {
            ratio = GOBJ_ACT(a0)->enemy->speedRatio;
            keep = 0;
        }
    } else {
        if ((((&motionKind[GOBJ_SUB(a0)->ctrl.motion])->f_18C >> 26) & 1) == 0) {
            ratio = GOBJ_ACT(a0)->enemy->speedRatio;
        }
    }
    if (keep) {
        ratio = 1.0f;
    }
    speedRatioDebugOverride(&ratio);
    SetMotionPlaySpeedRatio(a0, ratio);
}

inline void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0,
                                                    float farg1)
{
    float buf0[4];
    float buf18[4];
    float buf16[4];

    GetSkeltonPosition(buf0, a0, a1);
    sceVu0SubVector(buf16, a2, buf0);
    if (farg1 < FSqrt(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        sceVu0Normalize(buf16, buf16);
        sceVu0ScaleVector(buf16, buf16, farg1);
        sceVu0AddVector(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *)((char *)a2 + 4)) {
            buf18[1] = *(float *)((char *)a2 + 4);
        }
        SetDirectRootPositionNoFittingWithNodePoint(a0, a1, buf18, 1.0f);
        return;
    }
    SetDirectRootPositionNoFittingWithNodePoint(a0, a1, a2, farg0);
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

/* The bird broadcast the listing keeps at lines 2603-2614, between
   GetSkeltonPosition and ACTGame_InnerVelocityUpdate: a file static with no
   symbol of its own, so the name here is reconstructed. */
static inline void actGame_SendMailToBirds(GObj *self)
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

/* listing rows fumi/src/act-game.c:2619-2674.  Line 2626 carries the FSqrt
   call, the speed's copy, both loads of the parameter-block pointer and the
   store of the speed, and line 2627 the three stores of pos.  WHAT THE BYTES
   PIN: the speed is computed before the block pointer is fetched (the chase
   follows the call), and both hops of that fetch go through one pointer
   variable (a single pseudo set twice, global because the stores and the
   2649 counter use it, which is the ROM's `lw $3,0x164($16)` then
   `lw $3,0x688($3)`; the one-assignment spelling gives $2 then $3); the pos
   stores go through it and the two thresholds test the speed itself.  WHAT
   THEY CANNOT PIN: whether the 2001 source wrote those steps as separate
   statements on that one line or through a macro. */
void ACTGame_InnerVelocityUpdate(GObj *self)
{
    float pos[4];
    int slow;
    int stop;
    int nomove;
    char *p;
    float speed;

    slow = 0;
    stop = 0;
    pos[0] = test_CURRENTROOT(self)[0];
    pos[1] = test_CURRENTROOT(self)[1];
    pos[2] = test_CURRENTROOT(self)[2];
    sceVu0SubVector((char *)GOBJ_ACT(self)->work + 0x430, pos,
                    (char *)GOBJ_ACT(self)->work + 0x420);
    speed = FSqrt(GOBJ_WORK(self)->velX * GOBJ_WORK(self)->velX +
                  GOBJ_WORK(self)->velY * GOBJ_WORK(self)->velY +
                  GOBJ_WORK(self)->velZ * GOBJ_WORK(self)->velZ);
    p = (char *)GOBJ_ACT(self);
    p = (char *)*(int *)(p + 0x688);
    *(float *)(p + 0x440) = speed;
    *(float *)(p + 0x420) = pos[0];
    *(float *)(p + 0x424) = pos[1];
    *(float *)(p + 0x428) = pos[2];
    if (speed < 6.0f) {
        slow = 1;
    }
    if (speed < 2.0f) {
        stop = 1;
    }
    if (slow != 0) {
        GOBJ_WORK(self)->slowFrames += 1;
    } else {
        GOBJ_WORK(self)->slowFrames = 0;
    }
    if (stop != 0) {
        GOBJ_WORK(self)->stopFrames += 1;
    } else {
        GOBJ_WORK(self)->stopFrames = 0;
    }
    if (4 <= GOBJ_WORK(self)->slowFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x448))->q |= 1ULL << 32;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x448))->q &= ~(1ULL << 32);
    }
    if (4 <= GOBJ_WORK(self)->stopFrames) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x448))->q |= 1ULL << 33;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x448))->q &= ~(1ULL << 33);
    }
    nomove = 0;
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->f_18C >> 10) & 1) {
        if (GOBJ_WORK(self)->speed < 4.0f) {
            nomove = 1;
        }
    }
    if (nomove != 0) {
        GOBJ_WORK(self)->noMoveFrames += 1;
    } else {
        GOBJ_WORK(self)->noMoveFrames = 0;
    }
    if (GOBJ_WORK(self)->noMoveFrames > (60 - systemStatus[0] * 10) / systemStatus[1] * 5) {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x450))->q |= 1ULL << 32;
    } else {
        ((ActStatusWord *)((char *)GOBJ_ACT(self)->work + 0x450))->q &= ~(1ULL << 32);
    }
}

inline int ACTNotNeedCameraOffset(GObj *a0)
{
    Act *s;
    if (a0 != 0 && a0 == boyGObj) {
        s = GOBJ_ACT(a0);
        if ((char *)s != 0) {
            return (int)(s->flags20.ll >> 41) & 1;
        }
    }
    return 0;
}

void ACTGame_BeforeFunc(GObj *self)
{
    Act *s = GOBJ_ACT(self);

    ((ActWork *)s->work)->parallelInterp = 3.0f;
    ACTGame_InnerVelocityUpdate(self);

    switch ((unsigned int)s->actMode) {
    case 1:
    case 2:
    case 3: {
        Act *p = GOBJ_ACT(self);
        p->attacker = 0;
        p->hit = 0;
        break;
    }
    }

    if (((int)(s->flags20.ll >> 40) & 1) == 0 &&
        ((int)(&motionKind[GOBJ_SUB(self)->ctrl.motion])->f_18C >= 0 ||
         GOBJ_SUB(self)->ctrl.reserveMoved != 0)) {
        GetRootPosition((char *)s + 0x110, self);
    }

    s->flags20.ll &= ~(1ULL << 41);
    s->flags20.ll &= ~(1ULL << 40);

    ACTParaStatus_Clear(self);
    _ACTCharStatus_Clear(self);
    ACTLookTarget_Init(self);

    memset((char *)s + 0x47C, 0, 0x10);
    memset((char *)s + 0x48C, 0, 0x10);

    ACTGame_SetMotionPlaySpeedRatio_Clear(self);

    if (GOBJ_WORK(self)->downTimer > 0) {
        (GOBJ_WORK(self)->downTimer)--;
    }
    if (s->soundWait > 0) {
        (s->soundWait)--;
    }
    if (GOBJ_WORK(self)->turnTimer > 0) {
        (GOBJ_WORK(self)->turnTimer)--;
    }
    if (GOBJ_WORK(self)->turnTimer2 > 0) {
        (GOBJ_WORK(self)->turnTimer2)--;
    }
    if (GOBJ_WORK(self)->wishHoldTimer != 0) {
        (GOBJ_WORK(self)->wishHoldTimer)--;

        switch ((unsigned int)s->actMode) {
        case 2:
        case 3:
            break;

        default:
            GOBJ_WORK(self)->wishHoldTimer = 0;
            break;
        }
        if (scpBoyControlReadDisable != 0) {
            GOBJ_WORK(self)->wishHoldTimer = 0;
        }
    }

    if (((char *)girlGObj) != 0 && GOBJ_ACT(((char *)girlGObj))->actMode == 0x6F &&
        GOBJ_ACT(((char *)girlGObj))->carrier == (int)self &&
        ((int)(s->flags20.ll >> 21) & 1) == 0) {
        (GOBJ_WORK(self)->carryGirlFrames)++;
    } else {
        GOBJ_WORK(self)->carryGirlFrames = 0;
    }

    if (GOBJ_WORK(self)->timer394 != 0) {
        (GOBJ_WORK(self)->timer394)--;
    }
    if (GOBJ_WORK(self)->noInterpTimer > 0) {
        (GOBJ_WORK(self)->noInterpTimer)--;
        SetDirectMotionProgramInterpInfo(self, 0x2C, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 1, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0x22, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0x23, 0.0f);
    }
    if (GOBJ_WORK(self)->timer3A0 != 0) {
        (GOBJ_WORK(self)->timer3A0)--;
    }
    if (GOBJ_WORK(self)->timer3A4 != 0) {
        (GOBJ_WORK(self)->timer3A4)--;
    }
    if (GOBJ_WORK(self)->timer3AC != 0) {
        (GOBJ_WORK(self)->timer3AC)--;
    }
    if (GOBJ_WORK(self)->timer3B0 != 0) {
        (GOBJ_WORK(self)->timer3B0)--;
    }
    if (GOBJ_WORK(self)->jumpTimer != 0) {
        (GOBJ_WORK(self)->jumpTimer)--;
    }
    if (GOBJ_WORK(self)->mailB1Timer != 0) {
        (GOBJ_WORK(self)->mailB1Timer)--;
    }
    if (GOBJ_WORK(self)->ditchTimer != 0) {
        (GOBJ_WORK(self)->ditchTimer)--;
    }

    if ((int)(s->flags18.ll >> 36) & 1) {
        (GOBJ_WORK(self)->footIkFrames)++;
    } else {
        GOBJ_WORK(self)->footIkFrames = 0;
    }
    if ((int)(s->flags18.ll >> 37) & 1) {
        (GOBJ_WORK(self)->bit37Frames)++;
    } else {
        GOBJ_WORK(self)->bit37Frames = 0;
    }

    if ((((&motionKind[GOBJ_SUB(self)->ctrl.motion])->f_18C >> 14) & 1) ||
        actModeTbl[GOBJ_ACT(self)->actMode].bit14) {
        s->flags18.ll |= 1ULL << 38;
        if (self == boyGObj) {
            if (((char *)girlGObj) != 0) {
                GOBJ_WORK(((char *)girlGObj))->timer3B0 =
                    (0x3C - systemStatus[0] * 0xA) / systemStatus[1];
            }
        }
    }

    if ((int)(s->flags18.ll >> 38) & 1) {
        (GOBJ_WORK(self)->bit38Frames)++;
    } else {
        GOBJ_WORK(self)->bit38Frames = 0;
    }

    if (self == (girlGObj)) {
        ACTGame_GirlBeforeFunc(self);
    }

    if (*(int *)((char *)self + 0x8) == 0xEAD) {
        if ((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 2 < s->frame) {
            if (!(((char *)girlGObj) != 0 && GOBJ_ACT(((char *)girlGObj))->actMode == 0x6F &&
                  GOBJ_ACT(((char *)girlGObj))->carrier == (int)self)) {
                s->flags20.ll &= ~(1ULL << 30);
            }
        }
    }
}

/* OR the 16 pending-request bytes into the live request bytes. */
static inline void actEnv_OrRequestBytes(unsigned char *dst, unsigned char *src)
{
    int i;

    for (i = 15; i >= 0; i--, dst++, src++) {
        *dst |= *src;
    }
}

/* act-game.c:2853-2859 -- masks the 16-byte request-flag block in place. */
static inline void andRequestFlags(char *d, char *m)
{
    int i;
    for (i = 15; i >= 0; i--) {
        *d = *d & *m;
        d++;
        m++;
    }
}

void FunctionAboutClingedStatus(GObj *self)
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

void ACTEnvGetTest(GObj *self, void *a1)
{
    EnvWork old;
    Act *s = GOBJ_ACT(self);

    s->flags18.ll &= ~(1ULL << 59);
    s->flags18.ll &= ~(1ULL << 60);
    s->flags18.ll &= ~(1ULL << 61);
    s->flags20.ll &= ~(1ULL << 19);
    s->flags20.ll &= ~(1ULL << 38);
    s->flags20.ll &= ~(1ULL << 39);

    switch (s->actMode) {
    case 38:
    case 107:
        *(EnvOct *)((char *)s + 0x620) = *(EnvOct *)((char *)GOBJ_SUB(self) + 0x180);
        break;

    default:
        old = *(EnvWork *)((char *)s + 0x4B0);
        memset((char *)s + 0x4B0, 0, sizeof(EnvWork));
        *(EnvPair *)((char *)s + 0x5C0) = *(EnvPair *)((char *)&old + 0x110);
        *(EnvOct *)((char *)s + 0x620) = *(EnvOct *)((char *)&old + 0x170);
        *(EnvOct *)((char *)s + 0x660) = *(EnvOct *)((char *)&old + 0x1B0);
        *(EnvOct *)((char *)s + 0x640) = *(EnvOct *)((char *)&old + 0x190);
        ACTGetEnvironment(self, a1, test_CURRENTORIENT(self), (char *)s + 0x47C,
                          (ActEnv *)&s->wallOrientX);
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
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 88:
    case 104:
    case 105:
    case 106:
        break;
    }

    ACTSetEnvAllmighty(self);
    ACTGetWish_FromPad(self, a1);

    if (ACTGame_CheckPriInputFrame(self)) {
        actEnv_OrRequestBytes((unsigned char *)((char *)s + 0x49C),
                              (unsigned char *)((char *)s + 0x48C));
    } else {
        memset((char *)s + 0x49C, 0, 0x10);
    }

    if ((int)(s->wish4.ll >> 39) & 1) {
        s->wish2.ll |= 1ULL << 39;
    }
    if ((int)(s->wish4.ll >> 44) & 1) {
        s->wish2.ll |= 1ULL << 44;
    }
    if ((int)(s->wish4.ll >> 45) & 1) {
        s->wish2.ll |= 1ULL << 45;
    }
    if ((int)(s->wish4.ll >> 50) & 1) {
        s->wish2.ll |= 1ULL << 50;
    }
    if ((int)(s->wish4.ll >> 51) & 1) {
        s->wish2.ll |= 1ULL << 51;
    }
    if ((int)(s->wish4.ll >> 52) & 1) {
        s->wish2.ll |= 1ULL << 52;
    }
    if ((int)(s->wish4.ll >> 53) & 1) {
        s->wish2.ll |= 1ULL << 53;
    }
    FunctionAboutClingedStatus(self);
}

void ActOrientTest(GObj *self)
{
    float v0[4];
    HandWork w1;
    float p1[4];
    float sk1[4];
    float sk2[4];
    float d1[4];
    HandWork w2;
    float p2[4];
    float d2[4];
    float c1[4];
    HandWork w3;
    float sk3[4];
    float sk4[4];
    float d3[4];
    float ow[4];
    Act *s = GOBJ_ACT(self);
    char *vel;
    int hitA;
    int hitB;
    int near;
    int i;

    if (ORBIT(ORQ((char *)s, 0), 39) && ORBIT(ORM((char *)s, 0), 39)) {
        ACTSendMailCorrect(self, 189);
    }
    if (ORBIT(ORQ((char *)s, 0), 40) && ORBIT(ORM((char *)s, 0), 40)) {
        ACTSendMailCorrect(self, 191);
    }
    if (ORBIT(ORQ((char *)s, 0), 41) && ORBIT(ORM((char *)s, 0), 41)) {
        ACTSendMailCorrect(self, 192);
    }
    if (ORBIT(ORQ((char *)s, 0), 42) && ORBIT(ORM((char *)s, 0), 42)) {
        ACTSendMailCorrect(self, 193);
    }
    if (ORBIT(ORQ((char *)s, 0), 43) && ORBIT(ORM((char *)s, 0), 43)) {
        ACTSendMailCorrect(self, 197);
    }
    if (ORBIT(ORQ((char *)s, 0), 44) && ORBIT(ORM((char *)s, 0), 44)) {
        if (*(int *)((char *)self + 0xC) == 4) {
            if (rand() & 1) {
                ACTSendMailCorrect(self, 205);
            } else {
                ACTSendMailCorrect(self, 207);
            }
        } else {
            ACTSendMailCorrect(self, 205);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 45) && ORBIT(ORM((char *)s, 0), 45)) {
        ACTSendMailCorrect(self, 206);
    }
    if (ORBIT(ORQ((char *)s, 0), 51) && ORBIT(ORM((char *)s, 0), 51)) {
        ACTSendMailCorrect(self, 279);
    }
    if (self != boyGObj) {
        if (ORBIT(ORQ((char *)s, 0), 50) && ORBIT(ORM((char *)s, 0), 50)) {
            ACTSendMailCorrect(self, 278);
        }
        if (ORBIT(ORQ((char *)s, 0), 52) && ORBIT(ORM((char *)s, 0), 52)) {
            ACTSendMailCorrect(self, 280);
        }
        if (ORBIT(ORQ((char *)s, 0), 53) && ORBIT(ORM((char *)s, 0), 53)) {
            ACTSendMailCorrect(self, 281);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 55) && ORBIT(ORM((char *)s, 0), 55)) {
        ACTSendMailCorrect(self, 203);
    }
    if (ORBIT(ORQ((char *)s, 0), 54) && ORBIT(ORM((char *)s, 0), 54)) {
        if (ACTGame_NoWeapon(self)) {
            ACTSendMailCorrect(self, 202);
        } else {
            ACTSendMailCorrect(self, 201);
        }
    }
    if (ORBIT(ORQ((char *)s, 0), 56) && ORBIT(ORM((char *)s, 0), 56)) {
        ACTSendMailCorrect(self, 348);
    }
    if (ORBIT(ORQ((char *)s, 0), 58) && ORBIT(ORM((char *)s, 0), 58)) {
        ACTSendMailCorrect(self, 345);
    }
    if (ORBIT(ORQ((char *)s, 0), 57) && ORBIT(ORM((char *)s, 0), 57)) {
        ACTSendMailCorrect(self, 346);
    }
    if (ORBIT(ORQ((char *)s, 0), 59) && ORBIT(ORM((char *)s, 0), 59)) {
        ACTSendMailCorrect(self, 378);
    }
    if (ORBIT(ORQ((char *)s, 0), 62) && ORBIT(ORM((char *)s, 0), 62)) {
        ACTSendMailCorrect(self, 209);
    }
    if (ORBIT(ORQ((char *)s, 0), 63) && ORBIT(ORM((char *)s, 0), 63)) {
        ACTSendMailCorrect(self, 210);
    }
    if (ORBIT(ORQ((char *)s, 1), 0) && ORBIT(ORM((char *)s, 1), 0)) {
        ACTSendMailCorrect(self, 212);
    }
    if (ORBIT(ORQ((char *)s, 1), 1) && ORBIT(ORM((char *)s, 1), 1)) {
        ACTSendMailCorrect(self, 213);
    }
    if (ORBIT(ORQ((char *)s, 1), 2) && ORBIT(ORM((char *)s, 1), 2)) {
        ActSendMail_WithAdditionalData(self, 263, self, ACTWORK(self) + 2064);
    }
    if (ORBIT(ORQ((char *)s, 1), 3) && ORBIT(ORM((char *)s, 1), 3)) {
        ActSendMail_WithAdditionalData(self, 264, self, ACTWORK(self) + 2112);
    }
    if (ORBIT(ORQ((char *)s, 1), 4) && ORBIT(ORM((char *)s, 1), 4)) {
        ActSendMail_WithAdditionalData(self, 265, self, ACTWORK(self) + 2160);
    }
    if (ORBIT(ORQ((char *)s, 0), 60) && ORBIT(ORM((char *)s, 0), 60)) {
        ACTSendMailCorrect(self, 174);
        ACTSendMailCorrect(self, 173);
    }
    if (ORBIT(ORQ((char *)s, 0), 61) && ORBIT(ORM((char *)s, 0), 61)) {
        ACTSendMailCorrect(self, 166);
    }
    if (ORBIT(ORQ((char *)s, 1), 11) && ORBIT(ORM((char *)s, 1), 11)) {
        ACTSendMailCorrect(self, 216);
        debug_StdPrintfDummy("shoal mail\n");
    } else if (s->actMode == 43) {
        ACTSendMailCorrect(self, 217);
    }
    if (ORBIT(ORQ((char *)s, 1), 12) && ORBIT(ORM((char *)s, 1), 12)) {
        ACTSendMailCorrect(self, 218);
    }
    if (ORBIT(ORQ((char *)s, 1), 13) && ORBIT(ORM((char *)s, 1), 13)) {
        ACTSendMailCorrect(self, 219);
    }
    if (ORBIT(ORQ((char *)s, 1), 14) && ORBIT(ORM((char *)s, 1), 14)) {
        ACTSendMailCorrect(self, 220);
    }
    if (ORBIT(ORQ((char *)s, 1), 15) && ORBIT(ORM((char *)s, 1), 15)) {
        ACTSendMailCorrect(self, 223);
    }
    if (ORBIT(ORQ((char *)s, 1), 16) && ORBIT(ORM((char *)s, 1), 16)) {
        ACTSendMailCorrect(self, 224);
    }
    if (ORBIT(ORQ((char *)s, 1), 17) && ORBIT(ORM((char *)s, 1), 17)) {
        ACTSendMailCorrect(self, 225);
    }
    if (ORBIT(ORQ((char *)s, 1), 36) && ORBIT(ORM((char *)s, 1), 36)) {
        ACTSendMailCorrect(self, 121);
    }
    if (ORBIT(ORQ((char *)s, 1), 38) && ORBIT(ORM((char *)s, 1), 38)) {
        ACTSendMailCorrect(self, 122);
    }
    if (ORBIT(ORQ((char *)s, 1), 40) && ORBIT(ORM((char *)s, 1), 40)) {
        ACTSendMailCorrect(self, 130);
    }
    if (ORBIT(ORQ((char *)s, 1), 39) && ORBIT(ORM((char *)s, 1), 39)) {
        ACTSendMailCorrect(self, 127);
    }
    if (ORBIT(ORQ((char *)s, 1), 41) && ORBIT(ORM((char *)s, 1), 41)) {
        ACTSendMailCorrect(self, 131);
    }
    if (ORBIT(ORQ((char *)s, 1), 42) && ORBIT(ORM((char *)s, 1), 42)) {
        ACTSendMailCorrect(self, 132);
    }
    if (ORBIT(ORQ((char *)s, 1), 43) && ORBIT(ORM((char *)s, 1), 43)) {
        ACTSendMailCorrect(self, 123);
    }
    if (ORBIT(ORQ((char *)s, 1), 44) && ORBIT(ORM((char *)s, 1), 44)) {
        ACTSendMailCorrect(self, 124);
        ACTSendMailCorrect(self, 125);
    }
    if (ORBIT(ORQ((char *)s, 1), 33) && ORBIT(ORM((char *)s, 1), 33)) {
        ACTSendMailCorrect(self, 118);
    }
    if (ORBIT(ORQ((char *)s, 1), 34) && ORBIT(ORM((char *)s, 1), 34)) {
        ACTSendMailCorrect(self, 119);
    }
    if (ORBIT(ORQ((char *)s, 1), 35) && ORBIT(ORM((char *)s, 1), 35)) {
        ACTSendMailCorrect(self, 120);
    }
    if (ORBIT(ORQ((char *)s, 1), 5) && ORBIT(ORM((char *)s, 1), 5)) {
        if (self == (girlGObj)) {
            int ok = 0;
            if (girlControlMode != 0) {
                ok = 1;
            }
            if (GOBJ_ACT(self)->actMode == 0x75) {
                ok = 1;
            }
            if (ok) {
                ACTSendMailCorrect(self, 114);
            }
        } else {
            ACTSendMailCorrect(self, 114);
        }
    }
    if (ORBIT(ORQ((char *)s, 1), 6) && ORBIT(ORM((char *)s, 1), 6)) {
        ACTSendMailCorrect(self, 324);
    }
    if (ORBIT(ORQ((char *)s, 1), 8) && ORBIT(ORM((char *)s, 1), 8)) {
        ACTSendMailCorrect(self, 325);
    }
    if (ORBIT(ORQ((char *)s, 1), 7) && ORBIT(ORM((char *)s, 1), 7)) {
        ACTSendMailCorrect(self, 326);
    }
    if (ORBIT(ORQ((char *)s, 1), 9) && ORBIT(ORM((char *)s, 1), 9)) {
        ACTSendMailCorrect(self, 328);
    }
    if (ORBIT(ORQ((char *)s, 1), 18) && ORBIT(ORM((char *)s, 1), 18)) {
        ACTSendMailCorrect(self, 317);
    }
    if (ORBIT(ORQ((char *)s, 1), 19) && ORBIT(ORM((char *)s, 1), 19)) {
        ACTSendMailCorrect(self, 318);
    }
    if (ORBIT(ORQ((char *)s, 1), 20) && ORBIT(ORM((char *)s, 1), 20)) {
        ACTSendMailCorrect(self, 319);
    }
    if (ORBIT(ORQ((char *)s, 1), 22) && ORBIT(ORM((char *)s, 1), 22)) {
        ACTSendMailCorrect(self, 320);
    }
    if (ORBIT(ORQ((char *)s, 1), 23) && ORBIT(ORM((char *)s, 1), 23)) {
        ACTSendMailCorrect(self, 320);
    }
    if (ORBIT(ORQ((char *)s, 1), 27) && ORBIT(ORM((char *)s, 1), 27)) {
        ACTSendMailCorrect(self, 317);
    }
    if (ORBIT(ORQ((char *)s, 1), 28) && ORBIT(ORM((char *)s, 1), 28)) {
        ACTSendMailCorrect(self, 318);
    }
    if (ORBIT(ORQ((char *)s, 1), 29) && ORBIT(ORM((char *)s, 1), 29)) {
        ACTSendMailCorrect(self, 319);
    }
    if (ORBIT(ORQ((char *)s, 1), 55) && ORBIT(ORM((char *)s, 1), 55)) {
        ACTSendMailCorrect(self, 42);
    }
    if (ORBIT(ORQ((char *)s, 1), 56) && ORBIT(ORM((char *)s, 1), 56)) {
        ACTSendMailCorrect(self, 41);
    }
    if (ORBIT(ORQ((char *)s, 1), 57) && ORBIT(ORM((char *)s, 1), 57)) {
        ACTSendMailCorrect(self, 135);
    }
    if (ORBIT(ORQ((char *)s, 1), 58) && ORBIT(ORM((char *)s, 1), 58)) {
        ACTSendMailCorrect(self, 136);
    }
    if (ORBIT(ORQ((char *)s, 1), 63) && ORBIT(ORM((char *)s, 1), 63)) {
        ACTSendMailCorrect(self, 297);
    }
    if (ORBIT(ORQ((char *)s, 2), 0) && ORBIT(ORM((char *)s, 2), 0)) {
        ACTSendMailCorrect(self, 299);
    }
    if ((ORBIT(ORQ((char *)s, 2), 1) && ORBIT(ORM((char *)s, 2), 1)) ||
        (ORBIT(ORQ((char *)s, 2), 2) && ORBIT(ORM((char *)s, 2), 2))) {
        ACTSendMailCorrect(self, 295);
    }
    if (ORBIT(ORQ((char *)s, 1), 53) && ORBIT(ORM((char *)s, 1), 53)) {
        ACTSendMailCorrect(self, 301);
    }
    if (ORBIT(ORQ((char *)s, 1), 54) && ORBIT(ORM((char *)s, 1), 54)) {
        ACTSendMailCorrect(self, 146);
    }
    if (ORBIT(ORQ((char *)s, 1), 45) && ORBIT(ORM((char *)s, 1), 45)) {
        ACTSendMailCorrect(self, 295);
    }
    if (ORBIT(ORQ((char *)s, 1), 46) && ORBIT(ORM((char *)s, 1), 46)) {
        ACTSendMailCorrect(self, 300);
    }
    if (ORBIT(ORQ((char *)s, 1), 47) && ORBIT(ORM((char *)s, 1), 47)) {
        ACTSendMailCorrect(self, 306);
        if (stage_no == 32) {
            ACTSendMailCorrect(self, 308);
        }
    }
    if (ORBIT(ORQ((char *)s, 1), 48) && ORBIT(ORM((char *)s, 1), 48)) {
        ACTSendMailCorrect(self, 307);
    }
    if (ORBIT(ORQ((char *)s, 1), 50) && ORBIT(ORM((char *)s, 1), 50)) {
        ACTSendMailCorrect(self, 310);
    }
    if (ORBIT(ORQ((char *)s, 1), 51) && ORBIT(ORM((char *)s, 1), 51)) {
        ACTSendMailCorrect(self, 311);
    }
    if (ORBIT(ORQ((char *)s, 1), 49) && ORBIT(ORM((char *)s, 1), 49)) {
        ACTSendMailCorrect(self, 309);
    }
    if (ORBIT(ORQ((char *)s, 1), 52) && ORBIT(ORM((char *)s, 1), 52)) {
        ACTSendMailCorrect(self, 312);
    }
    if (ORBIT(ORQ((char *)s, 2), 10) && ORBIT(ORM((char *)s, 2), 10)) {
        ACTSendMailCorrect(self, 90);
    }
    if (ORBIT(ORQ((char *)s, 2), 11) && ORBIT(ORM((char *)s, 2), 11)) {
        ACTSendMailCorrect(self, 91);
    }
    if (ORBIT(ORQ((char *)s, 2), 12) && ORBIT(ORM((char *)s, 2), 12)) {
        (GOBJ_WORK(self)->orientFrames)++;
    } else {
        GOBJ_WORK(self)->orientFrames = 0;
    }
    if (ORBIT(ORQ((char *)s, 2), 7) && ORBIT(ORM((char *)s, 2), 7)) {
        ACTSendMailCorrect(self, 72);
        s->orientMot = 106;
    }
    if (ORBIT(ORQ((char *)s, 2), 8) && ORBIT(ORM((char *)s, 2), 8)) {
        ACTSendMailCorrect(self, 72);
        s->orientMot = 108;
    }
    if (ORBIT(ORQ((char *)s, 2), 9) && ORBIT(ORM((char *)s, 2), 9)) {
        ACTSendMailCorrect(self, 72);
        s->orientMot = 110;
    }
    if (ORBIT(ORQ((char *)s, 1), 24) && ORBIT(ORM((char *)s, 1), 24)) {
        ACTSendMailCorrect(self, 321);
    }
    if (ORBIT(ORQ((char *)s, 1), 25) && ORBIT(ORM((char *)s, 1), 25)) {
        ACTSendMailCorrect(self, 322);
    }
    if (ORBIT(ORQ((char *)s, 1), 26) && ORBIT(ORM((char *)s, 1), 26)) {
        ACTSendMailCorrect(self, 323);
    }
    if (ORBIT(ORQ((char *)s, 1), 62) && ORBIT(ORM((char *)s, 1), 62)) {
        ACTSendMailCorrect(self, 165);
    }
    if (ORBIT(ORQ((char *)s, 2), 13) && ORBIT(ORM((char *)s, 2), 13)) {
        ACTSendMailCorrect(self, 392);
    }
    if (ORBIT(ORQ((char *)s, 2), 14) && ORBIT(ORM((char *)s, 2), 14)) {
        vel = (char *)s + 0x4C0;
        sceVu0ScaleVector(v0, vel, -sceVu0InnerProduct((char *)(int)GOBJ_SUB(self) + 0x130, vel));
        sceVu0AddVector((char *)(int)GOBJ_SUB(self) + 0x130, (char *)(int)GOBJ_SUB(self) + 0x130,
                        v0);
        SetRootPosition(self, (char *)s + 0x540);
    }
    if (GOBJ_ACT(self)->enemy->stoneLevel > 0) {
        ACTSendMailCorrect(self, 111);
    }
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->f_190 >> 2) & 1) {
        if (GetMotionFrameFlag1(self)) {
            memset(&w1, 0, 0xC0);
            GetSkeltonPosition(sk1, self, 0x33);
            GetSkeltonPosition(sk2, self, 0x2F);
            sceVu0AddVector(p1, sk1, sk2);
            sceVu0ScaleVector(p1, p1, 0.5f);
            p1[1] = p1[1] + 50.0f;
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), 50.0f);
            sceVu0AddVector(&w1, p1, d1);
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), -50.0f);
            sceVu0AddVector((char *)&w1 + 0x10, p1, d1);
            w1._70 = 0.0f;
            ClipWall(&w1);
            if (CompareAttribute(w1._98, 0x2000)) {
                ACTSendMailCorrect(self, 327);
            }
            if (CompareAttribute(w1._98, 0x20000)) {
                if (*(int *)((char *)s + 0x68C) != 0) {
                    if (GetMotionFrameFlag1(self)) {
                        char *ext;
                        *(U64ag *)*(int *)((char *)s + 0x68C) = *(U64ag *)((char *)&w1 + 0x80);
                        ext = (char *)*(int *)((char *)s + 0x68C);
                        *(int *)(ext + 8) = *(int *)((char *)&w1 + 0x88);
                        ActSendMail_WithAdditionalData(self, 298, self, ext);
                    }
                }
            }
        }
    }
    if (((&motionKind[GOBJ_SUB(self)->ctrl.motion])->f_190 >> 3) & 1) {
        memset(&w2, 0, 0xC0);
        near = 0;
        p2[0] = test_CURRENTROOT(self)[0];
        p2[1] = test_CURRENTROOT(self)[1];
        p2[2] = test_CURRENTROOT(self)[2];
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), -50.0f);
        sceVu0AddVector(&w2, p2, d2);
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), 50.0f);
        sceVu0AddVector((char *)&w2 + 0x10, p2, d2);
        hitA = 0;
        w2._70 = 0.0f;
        ClipWall(&w2);
        hitB = 0;
        if (CompareAttribute(w2._98, 0x400)) {
            hitA = 1;
        }
        if (CompareAttribute(w2._98, 0xC000)) {
            hitB = 1;
        }
        if (hitA || hitB) {
            GetCollisCenterPositionSimple(c1, w2._80, w2._88);
            if (_DistxzSqGV(c1, test_CURRENTROOT(self)) < 400.0f) {
                near = 1;
            }
        }
        if (hitA && near) {
            ACTSendMailCorrect(self, 139);
        }
        if (hitB && near) {
            ACTSendMailCorrect(self, 310);
        }
    }
    if (s->intrKind == 313) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (((int)(s->flags20.ll >> 42) & 1) == 0) {
            continue;
        }
        memset(&w3, 0, 0xC0);
        GetSkeltonPosition(sk3, self, 0x33);
        GetSkeltonPosition(sk4, self, 0x2F);
        sceVu0AddVector(c1, sk3, sk4);
        sceVu0ScaleVector(c1, c1, 0.5f);
        c1[1] = c1[1] + 50.0f;
        sceVu0ScaleVector(d3, test_CURRENTORIENT(self), 50.0f);
        _ApplyRyGV(d3, -1.5707964f);
        sceVu0AddVector(&w3, c1, d3);
        sceVu0ScaleVector(d3, test_CURRENTORIENT(self), 50.0f);
        _ApplyRyGV(d3, 1.5707964f);
        sceVu0AddVector((char *)&w3 + 0x10, c1, d3);
        if (i == 1) {
            SwapGV(&w3, (char *)&w3 + 0x10);
        }
        w3._70 = 0.0f;
        ClipWall(&w3);
        if (w3._88 != 0) {
            GetOrientOfWall(ow, w3._88, &w3._80);
            SetMotionDirection(self, ow);
            s->flags20.ll &= ~(1ULL << 42);
            return;
        }
    }
}

void GetGirlHandlinkClInfo(void)
{
    float boyPos[4];
    float girlPos[4];
    float boyHand[4];
    float girlHand[4];
    int attr;
    int ok;
    float dy;

    *(HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540) = handClInfoClear;
    if (boyGObj == 0 || ((char *)girlGObj) == 0) {
        return;
    }
    GetRootProjectionPosOfGObj(boyPos, boyGObj);
    GetRootProjectionPosOfGObj(girlPos, girlGObj);
    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        if (!(_DistxzSqGV(boyPos, girlPos) < 12100.0f)) {
            goto draw;
        }
        dy = boyPos[1] - girlPos[1];
        if (dy < 0.0f) {
            if (-dy < 60.0f) {
                goto work;
            }
            goto draw;
        }
        if (!(dy < 60.0f)) {
            goto draw;
        }
    }
work:
    ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->on = 1;
    GetSkeltonPosition(boyHand, boyGObj, 44);
    GetSkeltonPosition(girlHand, (girlGObj), 44);

    ok = ACTCheckCollis_W(
        20.0f, girlHand, boyHand, 0, 0,
        ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->orient, &attr);
    ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->hit = ok;
    if (CompareAttribute(attr, 0x40000)) {
        ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->attr = 1;
    }
    ok = ACTCheckCollis_W(
        20.0f, boyHand, girlHand, 0, 0,
        ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->orient2, &attr);
    ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->hit2 = ok;
    if (CompareAttribute(attr, 0x40000)) {
        ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->attr2 = 1;
    }

draw:
    if (((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->hit) {
        debug_Arrow(100.0f, test_CURRENTROOT(girlGObj),
                    ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->orient,
                    255, 0, 0);
    }
    if (((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->hit2) {
        debug_Arrow(100.0f, test_CURRENTROOT(boyGObj),
                    ((HandClInfo *)((char *)GOBJ_ACT(((char *)girlGObj))->work + 0x540))->orient2,
                    0, 0, 255);
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

    int hand_able_connect(void)
    {
        unsigned char *h;
        float boy[4];
        float girl[4];

        if (boyGObj == 0 || ((char *)girlGObj) == 0) {
            return 0;
        }
        if (debug_font_flag & 1) {
            unsigned char *d = (unsigned char *)GOBJ_ACT(((char *)girlGObj))->work;

            debug_Printf(10, 120, 0x0FFFFFFF, "[%d] [%d] [%d] [%d] [%d]\n", d[0x540], d[0x541],
                         d[0x542], d[0x560], d[0x561]);
        }
        h = (unsigned char *)GOBJ_ACT(((char *)girlGObj))->work;
        if (h[0x540] != 0) {
            if (h[0x541] != 0 || h[0x560] != 0) {
                if (h[0x542] != 0) {
                    return 1;
                }
                if (h[0x561] == 0) {
                    return 0;
                }
            }
            return 1;
        }
        boy[0] = test_CURRENTROOT(boyGObj)[0];
        boy[1] = test_CURRENTROOT(boyGObj)[1];
        boy[2] = test_CURRENTROOT(boyGObj)[2];
        girl[0] = test_CURRENTROOT(girlGObj)[0];
        girl[1] = test_CURRENTROOT(girlGObj)[1];
        girl[2] = test_CURRENTROOT(girlGObj)[2];
        if (GOBJ_ACT(((char *)girlGObj))->actMode != 29 || _DistSqGV((int *)boy, girl) < 10000.0f) {
            return 0;
        }
        return 0;
    }

    if (self == (girlGObj)) {
        GetGirlHandlinkClInfo();
    }

    ACTEnvGetTest(self, (char *)s + 0x120);

    ActOrientTest(self);

    ACTItemWatchMotion(self);

    if (CheckFloorAttribute(self, 0x7000)) {
        _ACTParaStatus_Set(self, 17);
        _ACTCharStatus_Set(self, 22, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0x8000)) {
        _ACTParaStatus_Set(self, 16);
        _ACTCharStatus_Set(self, 21, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0x9000)) {
        _ACTParaStatus_Set(self, 15);
        _ACTCharStatus_Set(self, 20, 0.0f, 0);
    }
    if (CheckFloorAttribute(self, 0xA000)) {
        _ACTParaStatus_Set(self, 14);
        _ACTCharStatus_Set(self, 19, 0.0f, 0);
    }

    if (((int)(s->wish2.ll >> 5) & 1) && ((int)(s->wish4.ll >> 5) & 1)) {
        _ACTParaStatus_Set(self, 18);
        _ACTCharStatus_Set(self, 24, 0.0f, 0);
    }

    if ((((int)(s->wish2.ll >> 3) & 1) && ((int)(s->wish4.ll >> 3) & 1)) ||
        (((int)(s->wish2.ll >> 4) & 1) && ((int)(s->wish4.ll >> 4) & 1))) {
        _ACTParaStatus_Set(self, 26);
        _ACTCharStatus_Set(self, 23, 0.0f, 0);
    }

    if (girlControlMode != 0 && ((int)(s->wish0.ll >> 33) & 1) && ((int)(s->wish2.ll >> 33) & 1)) {
        _ACTParaStatus_Set(self, 27);
    }

    handL = 0;
    handR = 0;
    if (((int)(s->wish0.ll >> 36) & 1) && ((int)(s->wish2.ll >> 36) & 1)) {
        _ACTParaStatus_Set(self, 24);
        handL = (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x4A0)])
                      ->u_188.w >>
                  12) &
                 0xF) != 0;
    }
    if (((int)(s->wish0.ll >> 37) & 1) && ((int)(s->wish2.ll >> 37) & 1)) {
        _ACTParaStatus_Set(self, 25);
        handR = (((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x4A0)])
                      ->u_188.w >>
                  8) &
                 0xF) != 0;
    }

    if (handL) {
        RequestChangeHandMode(
            self, 0, 1,
            motionIKEffKind[((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i +
                                                   0x4A0)])
                                 ->u_188.w >>
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
                                                   0x4A0)])
                                 ->u_188.w >>
                             8) &
                            0xF]
                .mode,
            0, 0, 0);
    } else {
        RequestChangeHandMode(self, 1, 1, 0, 0, 0, 0);
    }

    if (((int)(s->wish0.ll >> 34) & 1) && ((int)(s->wish2.ll >> 34) & 1)) {
        _ACTCharStatus_Set(self, 25, 0.0f, 0);
    }
    if (((int)(s->wish0.ll >> 35) & 1) && ((int)(s->wish2.ll >> 35) & 1)) {
        _ACTCharStatus_Set(self, 26, 0.0f, 0);
    }

    if ((unsigned int)s->actMode < 4) {
        if (s->actMode != 0) {
            _ACTCharStatus_Set(self, 27, 0.0f, 0);
        }
    }

    if (((char *)girlGObj) != 0 && ((int)(GOBJ_ACT(((char *)girlGObj))->flags18.ll >> 40) & 1)) {
        _ACTCharStatus_Set(self, 15, 0.0f, 0);
    }

    gobj = isysGObjSearchFromObjKindID_begin(20);
    while (gobj != 0) {
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }

    switch (ACTGame_GetCurrentCallStatus(self)) {
    case 1:
    case 2: {
        float orient[4];
        float target[4];
        float *tgt;
        int limit;
        int connect;

        if (self == boyGObj && s->actMode == 1 &&
            (((unsigned long long)(&motionKind[*(
                                       int *)((char *)((IntFloat *)((char *)self + 0x15C))->i +
                                              0x4A0)])
                  ->f_190 >>
              7) &
             1)) {
            limit = 100;
            if ((int)(s->flags20.ll >> 24) & 3) {
                tgt = target;
                ScpCallCameraGetTarget(tgt);
                _OrientXZGV(orient, tgt, test_CURRENTROOT(boyGObj));
            } else if (((char *)girlGObj) != 0) {
                tgt = test_CURRENTROOT(girlGObj);
                _OrientXZGV(orient, tgt, test_CURRENTROOT(boyGObj));
            } else {
                GetOtherStageGirlOrient(orient, test_CURRENTROOT(self));
                orient[1] = 0.0f;
                limit = 45;
            }
            if (((int)(s->flags20.ll >> 23) & 1) && !((int)(s->wish1.ll >> 2) & 1)) {
                if (limit < _AbsRotyGV(orient, test_CURRENTORIENT(self))) {
                    SetMotionDirection(self, orient);
                    ResetMotionProgramInterpInfo(self, 35);
                }
            }
        }
        brainAddLevelGirlDetail(1, 20.0f);
        brainSetSpMode();
        if (hand_able_connect()) {
            /* Boy first: the inline'(char *)s first parameter binding is the
               boyGObj load (listing row 932), and the ROM'(char *)s `and` takes
               the boy'(char *)s bit as its first operand. */
            if (ACTGame_CheckHandMotion((char *)boyGObj, ((char *)girlGObj))) {
                connect = 1;
            } else {
                connect = 0;
            }
            if (GOBJ_ACT(((char *)girlGObj))->actMode == 74) {
                connect = 1;
            }
            if (connect && (s->padNow & 8)) {
                iosOmSendMail(girlGObj, 63, boyGObj);
            }
        }
        break;
    }
    default:
        if (ACTGame_FLAG_TETSUNAGI() && GOBJ_ACT(((char *)girlGObj))->actMode != 81) {
            brainAddLevelGirl(3.0f);
        }
        break;
    }

    if ((int)(s->flags18.ll >> 58) & 1) {
        if (ACTGame_FLAG_TETSUNAGI() && hand_able_connect() == 0) {
            ACTSendMailCorrect(self, 62);
        }
    }

    third = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    half = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;

    if ((s->padTrg & 0xF0) != 0) {
        (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
    }

    if (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) != 0) {
        if (0.5f < s->stickMag) {
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) =
                !*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4);
            (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = third;
        }
    } else {
        if (!(0.5f < s->stickMag)) {
            *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4) =
                !*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC4);
        }
    }

    if (0.5f < s->stickMag) {
        switch (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8)) {
        case 0:
            if (0.5f < s->stickDz) {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 1;
                (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = half;
            }
            break;
        case 1:
            if (!(0.5f < s->stickDz)) {
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xC8) = 0;
                (*(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xCC))--;
                *(int *)(((char *)GOBJ_ACT(self)->enemy) + 0xD4) = half;
            }
            break;
        case -1:
            if (0.5f < s->stickDz) {
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

    if ((&motionKind[*(int *)((char *)((IntFloat *)((char *)self + 0x15C))->i + 0x4A0)])->f_190 &
        1) {
        s->msgBlockTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    }

    ACTGame_LwsEffectProcess(self);
    actGame_SendMailToBirds(self);
    ACTGame_SetMotionPlaySpeedRatio_Exec(self);
}

inline void GetGirlPositionAtThisStage(float *a0)
{
    int buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(a0, stage_no, id, buf);
}

inline void GetOtherStageGirlOrient(float *a0, float *a1)
{
    float pos[4];
    GetGirlPositionAtThisStage(pos);
    _OrientGV(a0, pos, a1);
}

void ACTLookTargetSystem_Exec(GObj *self)
{
    char *s = (char *)((int *)self)[89];

    /* GNU nested function: the listing names it GetTarget.374 and passes
       ACTLookTargetSystem_Exec's frame as the static chain, from which it
       reads `self` and `s`. */
    int GetTarget(int kind, float *pos, int *pmode)
    {
        float dir[4];
        float p[4];
        char *target = 0;
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
            target = *(char **)(s + 0x88);
            break;
        case 10:
            target = *(char **)(s + 0x78);
            break;
        case 5:
            target = *(char **)(s + 0x7C);
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
            GetRootPosition(pos, *(char **)(s + 0x74));
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
                target = *(char **)(s + 0x80);
            } else {
                target = (char *)boyGObj;
            }
            break;
        case 9:
            target = *(char **)(s + 0x84);
            break;
        case 7:
            target = (char *)boyGObj;
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(char **)(s + 0x80);
            }
            break;
        case 3:
            target = (char *)boyGObj;
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
            if (target == (char *)boyGObj) {
                /* the listing writes these two statements out at act-game.c
                   4202-4203 instead of calling GetSkeltonPosition, so the
                   node comes off `target` and the skeleton off the global. */
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

inline void ACTGame_SendSoundMail(GObj *a0, int mail, GObj *from, int a3, int a4)
{
    switch (mail) {
    case 0x1A0:
        if (a4 != 0 && GOBJ_ACT(a0)->soundWait > 0) {
            break;
        }
        iosOmSendMail(a0, 0x1A0, from);
        if (a3 == 0) {
            break;
        }
        {
            Act *act = GOBJ_ACT(a0);
            act->soundMot = a3;
            *(unsigned long long *)((char *)act + 0x138) =
                (*(unsigned long long *)((char *)act + 0x138) & ~1ULL) | (a4 & 1);
        }
        break;

    case 0x1A1:
        iosOmSendMail(a0, 0x1A1, from);
        {
            Act *act = GOBJ_ACT(a0);
            act->soundMot = a3;
        }
        break;
    }
}

void ACTItemWatchMotion(GObj *self)
{
    MotionRec *rec = &motionKind[GOBJ_SUB(self)->ctrl.motion];
    Act *sub = GOBJ_ACT(self);
    int mode = rec->u_188.w >> 19;
    int frame = rec->u_188.b;

    /* Nested inline (dev lines 4456-4464): the "take the pending item"
       request, expanded at the four motion arms below. */
    inline void ItemHold(void)
    {
        if (sub->heldItem.i != 0) {
            return;
        }
        if ((sub->heldItem.i = sub->nextItem.i) == 0) {
            return;
        }
        HoldItem(sub->heldItem.i, self);
    }

    /* Nested inline (dev lines 4474-4476): drop whatever is held, read
       through the slots' pointer member, as the head block below compares
       them against the other actor's pair. */
    inline void ItemRelease(void)
    {
        if (sub->heldItem.p == 0) {
            return;
        }
        ReleaseItem(sub->heldItem.p);
        sub->nextItem.p = sub->heldItem.p = 0;
    }

    /* A real GNU nested function: ROM passes the parent's frame in $2
       (STATIC_CHAIN_REGNUM) and the body reads `(char *)sub` at 0($2) and `self`
       at 4($2) through it. */
    void ACTItemThrow(void)
    {
        float v[4];
        int kind;

        if (sub->heldItem.i == 0) {
            return;
        }
        sceVu0ScaleVector(v, test_CURRENTORIENT(self),
                          _ACTGame_GetParamF(9) + _ACTGame_GetParamF(9));
        kind = GetItemKind(sub->heldItem.i);
        if (kind == 1 || kind == 6) {
            debug_StdPrintfDummy("BOMB!!\n");
            v[0] *= 0.5f;
            v[1] -= 25.0f;
            v[2] *= 0.5f;
        }
        ThrowItem(sub->heldItem.i, v);
        sub->nextItem.i = sub->heldItem.i = 0;
    }

    mode &= 7;

    if (self == (girlGObj) && boyGObj != 0) {
        if (sub->nextItem.p != 0) {
            Act *o = GOBJ_ACT(boyGObj);
            if (sub->nextItem.p == o->nextItem.p || sub->nextItem.p == o->heldItem.p) {
                sub->nextItem.p = 0;
            }
        }
        if (sub->heldItem.p != 0) {
            Act *o = GOBJ_ACT(boyGObj);
            if (sub->heldItem.p == o->nextItem.p || sub->heldItem.p == o->heldItem.p) {
                sub->heldItem.p = 0;
            }
        }
    }

    switch (mode) {
    case 2:
        if ((float)frame < GOBJ_SUB(self)->ctrl.animFrame) {
            ItemHold();
        } else if (sub->heldItem.i != 0) {
            float pos[4];
            GetRootPosition(pos, sub->heldItem.i);
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

    if (self == boyGObj && itemWatchOff == 0) {
        *(int *)((char *)sub + 0x154) = sub->heldItem.i;
        SetBoyInfo((void *)sub->weapon, (void *)sub->heldItem.p);
    }
    if (self == (girlGObj)) {
        *(int *)((char *)sub + 0x154) = sub->heldItem.i;
        if (mode != 0) {
            int item = sub->heldItem.i;
            int drop = 0;
            if (item != 0) {
                drop = *(int *)(item + 0x16C) == 0;
            }
            /* two word tests: as member tests gcc folds them into one doubleword load */
            if (*(int *)((char *)sub + 0x180) == 0 && *(int *)((char *)sub + 0x184) == 0) {
                drop = 1;
            }
            if (drop) {
                *(int *)((char *)sub + 0x154) = sub->heldItem.i = sub->nextItem.i = 0;
                ACTSendMailCorrect(self, 0x7E);
            }
        }
    }
}

inline void ACTItemForceDrop(GObj *a0)
{
    Act *s = GOBJ_ACT(a0);
    int item = s->heldItem.i;
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
                  (0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 100 / 60,
                  (0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 45 / 60, 1, 0.05f, 0.25f);
}

void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7)
{
    HandModeCmd *hmc = 0;

    /* updateHMC is a nested function in the ROM: RequestChangeHandMode
       passes it a static chain in $2 (STATIC_CHAIN_REGNUM) which it spills
       to 0(sp), and reads self/mode/pri/flag/p5/p6/p7 and hmc out of the
       parent frame through it.  The listing names it updateHMC.415. */
    void updateHMC(void)
    {
        hmc->f_0 = flag;
        hmc->f_4 = pri;
        switch (mode) {
        case 0:
            GOBJ_SUB(self)->root.hand0Mode = hmc->f_0;
            GOBJ_SUB(self)->root.hand0Obj = p5;
            GOBJ_SUB(self)->root.hand0Node = p6;
            if (p7 != 0) {
                GOBJ_SUB(self)->root.hand0Pos[0] = p7[0];
                GOBJ_SUB(self)->root.hand0Pos[1] = p7[1];
                GOBJ_SUB(self)->root.hand0Pos[2] = p7[2];
            }
            break;
        case 1:
            GOBJ_SUB(self)->root.hand1Mode = hmc->f_0;
            GOBJ_SUB(self)->root.hand1Obj = p5;
            GOBJ_SUB(self)->root.hand1Node = p6;
            if (p7 != 0) {
                GOBJ_SUB(self)->root.hand1Pos[0] = p7[0];
                GOBJ_SUB(self)->root.hand1Pos[1] = p7[1];
                GOBJ_SUB(self)->root.hand1Pos[2] = p7[2];
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
        debug_assert("src/act-game.c", 4727);
        __assert("src/act-game.c", 4727, "0");
        break;
    }
    if (pri < 3) {
        if (pri > 0) {
            if (flag == 0) {
                if (hmc->f_4 != pri) {
                    return;
                }
            }
        }
    }
    if (hmc->f_4 == 0 || hmc->f_0 == 0) {
        updateHMC();
    } else if (pri >= hmc->f_4) {
        updateHMC();
    }
}

inline void _ACTSetEnemyDisappearSpeed(GObj *a0, float f)
{
    GOBJ_WORK(a0)->disappearSpeed = f;
}

inline int ACTChkAttackIgnore_BOY(GObj *a0, GObj *actor)
{
    Act *s = GOBJ_ACT(a0);
    if (s->actMode == 0x35 ||
        (((ActWork *)s->work)->timer394 != 0 && scpBoyControlReadDisable != 0) ||
        ((int)(s->flags18.ll >> 35) & 1) == 0) {
        return 1;
    }
    return 0;
}

inline int ACTChkAttackIgnore_GIRL(GObj *a0, GObj *actor)
{
    Act *s = GOBJ_ACT(a0);
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

inline int ACTChkAttackIgnore_ENEMY(GObj *a0, GObj *actor)
{
    Act *s = GOBJ_ACT(a0);

    switch (s->actMode) {
    case 0x67:
        if ((60 - systemStatus[0] * 10) / systemStatus[1] / 2 < s->modeFrame) {
            return 1;
        }
        break;

    case 6:
        if (((int)(s->flags18.ll >> 57) & 1) && stage_no != 0x56 && stage_no != 3 &&
            stage_no != 0x2E) {
            return 1;
        }
        break;
    }
    return 0;
}
