#include "girl_act.h"
#include "debug.h"
#include "pad.h"
#include "obj_manager.h"
#include "act-way.h"
#include "way_sys.h"
#include "brain.h"
#include "gflag.h"
#include "Primitive.h"
#include "box.h"
#include "matrixDrive.h"
#include "motionOrientManager.h"
#include "quaternion.h"
#include <stdlib.h>
#include "geometryManager.h"
#include "typedef.h"
#include "script.h"
#include <libvu0.h>
#include "wireLetter.h"
#include "GifPacket.h"
#include "isys.h"
#include "debug_exception.h"
#include <string.h>
#include "generator.h"
#include "boyact.h"
#include "lws_kyomi.h"
#include "act.h"
#include "gobj.h"
#include "enemy_act.h"
#include "torch.h"
#include <stdio.h>
#include "act-game.h"
#include "commonact.h"
#include "gv.h"
#include "main.h"
#include "fieldCollision.h"
#include <assert.h>
#include "camera-editor.h"
#include "motionManager2.h"
#include "act-env.h"
#include "item.h"
#include "wireLetter.h"
#include "include_asm.h"

static void _girlBrainHide_MakeHidePoint(float *p, float dist);
static int isEnterHideadv(void);

typedef struct GirlStand { /* field names derived */
    sceVu0FVECTOR prev;    /* 0x00 last frame's root position */
    sceVu0FVECTOR cur;     /* 0x10 this frame's root position */
    float moveDist;        /* 0x20 how far the root moved this frame */
    char pad24[12];
    sceVu0FVECTOR orient;    /* 0x30 the girl's facing */
    sceVu0FVECTOR toBoy;     /* 0x40 the direction from the girl to the boy */
    float handDist;          /* 0x50 HandMgr_GetDistHand: girl's hand node to the boy's */
    float handHeight;        /* 0x54 the hands' height gap */
    unsigned char still;     /* 0x58 moveDist under 2 ("gv") */
    unsigned char turned;    /* 0x59 facing 61 degrees or more off toBoy ("mo") */
    unsigned char far100;    /* 0x5A handDist over 100 */
    unsigned char far125;    /* 0x5B handDist over 125 ("hd") */
    unsigned char far135;    /* 0x5C handDist over 135 */
    unsigned char near90;    /* 0x5D handDist under 90 ("hd2") */
    unsigned char heightGap; /* 0x5E handHeight over 15 */
} GirlStand;                 /* derived name */

union GAIF { /* field names derived */
    int i;
    float f;
}; /* derived name */

static void GetEyeDirection(char *dir, GObj *obj)
{
    int node = GetSkeltonFocusNode(obj, 0x23);
    if (obj->kind == 4) {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = -1.0f;
        *(int *)(dir + 0x8) = 0;
    } else {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = 1.0f;
        *(int *)(dir + 0x8) = 0;
    }
    *(int *)(dir + 0xC) = 0;
    sceVu0ApplyMatrix(dir, (char *)(GOBJ_SUB(obj)->nodeMtx + (node << 6)), dir);
}

void funcGirlHandDisconnect(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy("--disconnect--\n");
}

/* The three climb headers (omori/include/g50climb.h, g100climb.h,
   g200climb.h) textually included here: each defines the hand-off's
   after-routine and act-routine `inline`, which the compiler emits at the
   end of the file in girl_act.h's order, and the mot-routine plainly,
   emitted in place.  Their strings come out here, in this order. */
INCLUDE_ASM_LIT(afterGirlHand50);

INCLUDE_ASM_LIT(actGirlHand50);

void motGirlHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motGirlHand50\n");
    while (1) {
        iosOmSendMail(boyGObj, 85, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 514 || !(GOBJ_SUB(self)->ctrl.motion < 521)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 86, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    if ((((int)(sub->flags18.ll >> 39)) & 1) == 0) {
        iosOmSendMail(boyGObj, 0x10, isysCurrentGObj);
        ACTSendMailCorrect((void *)self, 7);
    }
    iosOmSendMail(boyGObj, 87, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 85, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 67);
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(actGirlHand100);

void motGirlHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motGirlHand100\n");
    while (1) {
        iosOmSendMail(boyGObj, 0x5A, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 0x202 || !(GOBJ_SUB(self)->ctrl.motion < 0x209)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 0x5B, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(boyGObj, 0x5C, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 0x5C, sub->env.motOriReq);
    while (GOBJ_SUB(self)->ctrl.motion < 0x202 || !(GOBJ_SUB(self)->ctrl.motion < 0x209)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 0x5D, isysCurrentGObj);
        if (sub->readyFlags & 8)
            break;
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 0x43);
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(actGirlHand200);

void motGirlHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int n;

    debug_StdPrintfDummy("enter motGirlHand200\n");
    n = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;
    while (1) {
        if (n <= 0)
            goto expired;
        n--;
        iosOmSendMail(boyGObj, 0x5F, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    goto held;
expired:
    ACTSendMailCorrect((void *)self, 0x63);
    debug_StdPrintfDummy("%s sync error\n",
                         (void *)self == (void *)((int *)boyGObj) ? "boy" : "girl");
held:
    while (GOBJ_SUB(self)->ctrl.motion < 0x202 || !(GOBJ_SUB(self)->ctrl.motion < 0x209)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 0x60, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(boyGObj, 0x61, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 0x5D, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        iosOmSendMail(boyGObj, 0x62, isysCurrentGObj);
        if (sub->readyFlags & 8)
            break;
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 0x43);
        _ACTWait(1);
    }
}

/* actGirlHand and the attract brain pass the girl and a target, which it does not read */
static void GirlBrainClearTarget(void *self, void *target)
{
    brainClsTargetLevel(&brainGirl);
}

/* The hide/others/listB/listD object lists: 0x30 per entry, 100 entries per
   list, the four lists 0x12D0 apart inside GirlBrainWork (others 0xC90,
   listB 0x1F60, hide 0x3230, listD 0x4500).  The `long long` at 0x08 makes
   the record 8-byte aligned. */
typedef struct { /* field names derived */
    void *obj;   /* 0x00 */
    int pad4;
    long long pad8;
    float pos[4]; /* 0x10 */
    float dist;   /* 0x20 */
    int flags;    /* 0x24 */
    int pad28[2];
} GirlListEnt; /* derived name */

typedef struct { /* field names derived */
    int num;     /* 0x00 */
    char pad4[12];
    GirlListEnt ent[100]; /* 0x10 */
} GirlList;               /* derived name */

typedef struct GirlBrainWork { /* field names derived */
    unsigned char listBNear;   /* 0x00 a listB entry lies within 300 */
    unsigned char listDFound;  /* 0x01 the listD list is not empty */
    char pad2[3214];
    GirlList others;  /* 0x0C90 */
    GirlList listB;   /* 0x1F60 */
    GirlList hide;    /* 0x3230 */
    GirlList listD;   /* 0x4500 */
    void *target;     /* 0x57D0 the brain's current target gobj             */
    void *lastTarget; /* 0x57D4 the target the last DecideMode pass saw      */
    char pad57D8[4];
    int curMode;           /* 0x57DC the mode the brain last switched to */
    float runawayGoal[4];  /* 0x57E0 the runaway goal */
    float hidePoint[4];    /* 0x57F0 last accepted hide point */
    float runawayFrom[4];  /* 0x5800 where the last runaway leg started */
    float girlRoot[4];     /* 0x5810 GetRootPosition of the girl, where the runaway search starts */
    float girlPos[4];      /* 0x5820 the girl's own position, GetRootProjectionPosOfGObj */
    float boyRoot[4];      /* 0x5830 GetRootPosition of the boy */
    float boyPos[4];       /* 0x5840 the boy's GetRootProjectionPosOfGObj */
    char pad5850[16];      /* 0x5850, no reader in this build */
    WVTObj hideWay;        /* 0x5860, the way the girl tries to the hide point */
    unsigned char warn;    /* 0x58E0 a brain state asks the main loop to checkWarning */
    unsigned char pad58E1; /* 0x58E1 cleared each frame, never read */
    unsigned char modeChanged; /* 0x58E2 set on the frame the mode changes */
    unsigned char lookHold;    /* 0x58E3 3 s after flags18 bit 62 while she faced the boy */
    int markerPulse;           /* 0x58E4 the runaway goal marker's pulse */
    int runMode;               /* 0x58E8 */
    int wait;
    int timer;
    int limit;
    int modeFrames;    /* 0x58F8 frames since the last mode change */
    int status31Timer; /* 0x58FC frames the attract state keeps char status 31 set */
    int unseenFrames;  /* 0x5900 frames no hide-list object has been in view */
    int hideAdvWait;   /* 0x5904 frames before the hide state may advance */
    int pad5908[2];    /* 0x5908, to the 0x5910 girlBrainMain_Init clears */
} GirlBrainWork;       /* derived name */

/* The head of the TU's .data (the brain work record brain_val and the hand
   manager handmgr follow, defined after the last of these): the
   danger-environment initial value, the brain mode table (the mode's routine
   and its flag byte), the object kinds the others list gathers (-1 ends it)
   and their debug names, the run-mode rows ChangeRunMode indexes, the three
   attract parameter sets, the debug names of the move states, the three
   escape angles and the debug names of the attract states.  Each is defined
   beside its reader: the first three here, the rest further down. */
typedef struct { /* field names derived */
    int kind;
    GObj *obj; /* the danger object, typed like the object globals */
    void *save;
    int count;
} GirlDangerEnv; /* derived name */

typedef struct { /* field names derived */
    void (*proc)(GObj *self);
} GirlBrainMode; /* derived name */

typedef struct { /* field names derived */
    void *obj;   /* 0x00 the object the girl walks to */
    int pad4[3];
    sceVu0FVECTOR pos;      /* 0x10 */
    int kind;               /* 0x20 copied into the actor's 0x44 when the state ends */
    int mail;               /* 0x24 the mail the state sends when it ends */
    float goalDist;         /* 0x28 the way goal distance the girl arrives within */
    float goalHeight;       /* 0x2C the way goal height she arrives within */
    unsigned char fixedPos; /* 0x30 pos stays as set, not re-read from obj each frame */
    char pad31[15];
    sceVu0FVECTOR dir;      /* 0x40 */
    unsigned char goalTurn; /* 0x50 turn to dir on arrival */
    char pad51[3];
    float slowDist; /* 0x54 the walk slows to half within this goal distance */
    char pad58[8];
} GirlAttractParam; /* derived name */

inline void subGirlBrain_Idle(GObj *volatile self);
void subGirlBrain_Attract(GObj *volatile self);
void subGirlBrain_Escape(GObj *volatile self);
void subGirlBrain_Hide(GObj *volatile self);
inline void subGirlBrain_Hesitate(GObj *volatile self);
inline void subGirlBrain_Becarry(GObj *volatile self);
inline void subGirlBrain_Busy(GObj *volatile self);
void subGirlBrain_Pulledup(GObj *volatile self);
inline void subGirlBrain_DangerEnv(GObj *volatile self);
void subGirlBrain_HideAdvance(GObj *volatile self);

static GirlDangerEnv dangerEnvDefault = {0}; /* derived name */

static GirlBrainMode girlBrainModeTable[10] = {
    /* derived name */
    {subGirlBrain_Idle},        {subGirlBrain_Attract},  {subGirlBrain_Escape},
    {subGirlBrain_Hide},        {subGirlBrain_Hesitate}, {subGirlBrain_Becarry},
    {subGirlBrain_Busy},        {subGirlBrain_Pulledup}, {subGirlBrain_DangerEnv},
    {subGirlBrain_HideAdvance},
}; /* derived name */

static int othersKindList[3] = {4, 61, -1}; /* derived name */

/* The TU's .bss: sort_list's index/distance pairs and its copy of the sorted
   positions, CorrectList's compaction scratch and the runaway candidate list
   (ten positions each), subGirlBrain_Escape's debug string buffer,
   subGirlCollision's direction request (priority, direction, the vector at
   +0x10) and the current danger environment (subGirlBrainMain copies
   dangerEnvDefault into it and the Danger_* routines read its object). */
typedef struct { /* field names derived */
    int idx;
    float dist;
} GirlSortEnt; /* derived name */

static GirlSortEnt sortList[100]; /* derived name */

static float sortPos[100][4]; /* derived name */

static float correctListWork[10][4]; /* derived name */

static float runawayPointList[10][4]; /* derived name */

static char escapeDebugString[512]; /* derived name */

typedef struct {       /* field names derived */
    int prio;          /* 0x00 */
    int dir;           /* 0x04 */
    sceVu0FVECTOR vec; /* 0x10 */
} GoalTurnReq;         /* derived name */

static GoalTurnReq goalTurnReq; /* derived name */

static GirlDangerEnv dangerEnv; /* derived name */

/* Defined before the girl_brain_main.c.inc run; subGirlBrain_Pulledup and
   subGirlCollision expand it.  The first parameter is unused. */
static inline void ATGoalTurnSet(void *actor, int prio, int dir, float *v) /* derived name */
{
    if (prio >= goalTurnReq.prio) {
        goalTurnReq.prio = prio;
        goalTurnReq.dir = dir;
        goalTurnReq.vec[0] = v[0];
        goalTurnReq.vec[1] = v[1];
        goalTurnReq.vec[2] = v[2];
    }
}

/* The second static inline of the pair: subGirlCollision expands it once.  It
   reads back the turn request ATGoalTurnSet writes and answers it with the
   turn mail for the request's priority. */
static inline void ATGoalTurnSendMail(GObj *self) /* derived name */
{
    Act *act = GOBJ_ACT(self);
    int mail = -1;
    int slow[2] = {215, 226};
    int fast[2] = {216, 227};
    int idx = 0;

    switch (goalTurnReq.prio) {
    case 2:
    case 3:
        idx = 1;
        break;
    }
    switch (goalTurnReq.dir) {
    case 1:
        mail = slow[idx];
        break;
    case 2:
        mail = fast[idx];
        break;
    }
    if (mail > 0) {
        act->env.turnDir.f[0] = goalTurnReq.vec[0];
        act->env.turnDir.f[1] = goalTurnReq.vec[1];
        act->env.turnDir.f[2] = goalTurnReq.vec[2];
        ACTSendMailCorrect(self, mail);
    }
}

/* The wire-string marker (colour, a MatrixDrive transform of the position,
   DispWireString, colour reset), built only under DEBUG, as
   girlBrainDebugPrint is. */
static inline void girlDispWire(int r, int g, int b, float *pos, char *str) /* derived name */
{
#ifdef DEBUG
    float mtx[16];

    ChangeColorWireString(r, g, b);
    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(mtx, ((float *)((float *)matrixptr)) + 32);
    mtx[3] = mtx[7] = mtx[11] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
    sceVu0MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), mtx);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(str);
    MatrixDrive_PopMatrix();
    MatrixDrive_PopMatrix();
    DefaultColorWireString();
#endif
}

/* the marker colour for a hide point; the caller supplies the marker text */
static inline void girlDispHidePoint(float *pos, int c, char *str) /* derived name */
{
    int r = 0;
    int g = 0;
    int b = 0;

    switch (c) {
    case 'R':
        r = 255;
        break;
    case 'B':
        b = 255;
        break;
    case 'W':
        r = 255;
        g = 255;
        b = 255;
        break;
    case 'Y':
        g = 255;
        b = 255;
        break;
    }
    girlDispWire(r, g, b, pos, str);
}

static void SetTurnSpeedInEscape(GObj *self)
{
    if (GOBJ_ACT(self)->actMode == 10) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 1.5f, 5);
    }
}

static inline int girlListIsOnBoy(void *gobj) /* derived name */
{
    if (*(int *)((char *)gobj + 0xC) != 4) {
        return 1;
    }
    return EnemyBrainStatus_Boy(gobj);
}

static inline int girlListIsAlive(void *gobj) /* derived name */
{
    return (int)(GOBJ_ACT(gobj)->flags18.ll >> 32) & 1;
}

/* the flag-masked record copy the three sub-lists share */
static inline int girlListPick(GirlListEnt *src, GirlListEnt *dst, int n,
                               int mask) /* derived name */
{
    int cnt = 0;
    int i;

    for (i = 0; i < n; i++) {
        if (src[i].flags & mask) {
            dst[cnt] = src[i];
            cnt++;
        }
    }
    return cnt;
}

INCLUDE_ASM(sort_list_78);

INCLUDE_ASM(girlBrainMain_MakeOthersList);

/* The group names, defined here after the list builder. */
static char *groupRelationName[4] = {"FALSE", "OTHERGROUP", "SAMEGROUP",
                                     "DIRECT"}; /* derived name */

/* A static inline in September (no out-of-line copy): true when an entry of
   the hide list stands between `from` and `to`. */
static inline unsigned char girlBrainHideCheckIntercept(float *from, float *to, char *list, int n)
{
    float d[4];
    float m[16];
    float v[4];
    int i;
    float dist;
    int dy;

    sceVu0SubVector(d, from, to);
    d[1] = 0.0f;
    GetMatrixDirectionToZ(m, d);
    dist = FSqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    for (i = 0; i < n; i++) {
        dy = *(float *)(list + i * 0x30 + 0x14) - from[1];
        if (abs(dy) > 200) {
            continue;
        }
        sceVu0SubVector(v, list + i * 0x30 + 0x10, to);
        v[1] = 0.0f;
        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, m, v);

        if (0.0f < v[2]) {
            if (v[2] < dist) {
                if (v[0] * v[0] + v[1] * v[1] < 10000.0f) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* a static inline */
static inline void dispWayMarker(float *p) /* derived name */
{
    float buf[4];
    sceVu0ScaleVector(buf, p, -1.0f);
    debug_Marker(buf, 0xFF, 0, 0, 70.0f, 0.0f);
}

/* A static inline, inlined at two sites: true when the candidate hide point
   sits above the girl's floor by more than 100 units. */
static inline unsigned char isHidePointTooHigh(float *p) /* derived name */
{
    GirlBrainWork *b;
    float y;

    if (stage_no == 8 || stage_no == 22) {
        b = &brain_val;
        y = b->girlPos[1] + 100.0f;
        if (y < p[1] || y < b->boyPos[1]) {
            return 1;
        }
    }
    return 0;
}

/* One call site.  `r = 0;` is a statement after the struct copy, not an
   initialiser. */
static inline int girlBrainHide_TryWay(float *pt, WVTObj *way, float *goal,
                                       float *hit) /* derived name */
{
    float start[4];
    int r = 0;
    void *girl = boyGObj;
    void *self = girlGObj;
    Act *sub = GOBJ_ACT(self);

    *way = sub->way;
    if (GetWay_begin(pt, way, goal)) {
        r = 1;
        start[0] = pt[0];
        start[1] = pt[1];
        start[2] = pt[2];
        start[1] -= 50.0f;
        goal[1] = goal[1] - 30.0f;
        way->reached = 0;
        if (ACTCheckCollis_WAY(10.0f, goal, start, girl, hit) == 0) {
            way->reached = 1;
            DeleteGuideWay(way);
            r = 3;
        } else if (way->flag3C == 0) {
            r = 2;
        }
    }
    return r;
}

INCLUDE_ASM(girlBrainMain_CheckWarningMode);

/* the pad record: the button word at +0 */

/* the brain target pass, inlined into girlBrainMain_DecideMode and into
   subGirlBrainMain */
static inline void *girlBrainGetTarget(void) /* derived name */
{
    Brain *b = &brainGirl;
    void *obj = 0;

    brainGetTarget(b);
    if (b->idx != -1) {
        obj = (void *)b->tgt[b->idx].gobj;
    }
    return obj;
}

/* The girl brain's TTY trace of its escape target, built only when DEBUG is
   defined; the retail build leaves the helper without a body.
   subGirlBrain_Escape's four calls are commented at that function. */
static __inline__ void girlBrainDebugPrint(void) /* derived name */
{
#ifdef DEBUG
    float *t = brain_val.girlRoot;

    scePrintf("girl brain target %f %f %f\n", t[0], t[1], t[2]);
#endif
}

static inline float girlBrainGetTargetLevel(void) /* derived name */
{
    if (brainGirl.idx == -1) {
        return 0.0f;
    }
    return brainGirl.targetLevel;
}

/* the kind of the held target, 0 while none is held; the actor parameter is
   not read */
static inline int girlBrainGetTargetType(void *g) /* derived name */
{
    Brain *b = &brainGirl;

    if (b->idx == -1) {
        return 0;
    }
    return (unsigned short)b->targetType;
}

/* the walk ratio that goes with a target kind */
static inline float girlBrainGetTypeRatio(int type) /* derived name */
{
    float r;

    switch (type) {
    case 2:
        r = 0.5f;
        break;
    case 3:
        r = 1.0f;
        break;
    case 1:
    default:
        r = 0.0f;
        break;
    }
    return r;
}

INCLUDE_ASM(girlBrainMain_DecideMode);

static void girlBrainMain_PositionUpdate(void)
{
    GetRootPosition(brain_val.girlRoot, (void *)girlGObj);
    GetRootPosition(brain_val.boyRoot, boyGObj);
    GetRootProjectionPosOfGObj(brain_val.girlPos, (void *)girlGObj);
    GetRootProjectionPosOfGObj(brain_val.boyPos, boyGObj);
}

static void girlBrainMain_Init(void)
{
    memset(&brain_val, 0, sizeof(brain_val));
}

/* the run-mode rows ChangeRunMode indexes */
static int runModeTable[4][4] = {
    /* derived name */
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {2, 1, 1, 0},
    {3, 2, 1, 1},
}; /* derived name */

/* param-escape-run as the bytes of its [t][mode] grid: girl_act.h's
   EscapeRange rows read t * 16 + mode * 8 bytes in */
extern char paramEscapeRun[];
/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* declared in girl_act.h: the girl's look timer and its state, a tentative
   definition */
int GirlInfo[2];

/* A file-scope static helper, inlined in Danger_Box, its nested
 * GetSafePosition and subGirlBrainMain: whether the boy is pushing a
 * truck-type box (his action mode is 49 and the box he holds is box kind
 * 7). */
static inline unsigned char isBoyPushBoxTruck(void) /* derived name */
{
    Act *sub;
    GObj *box;

    if (((int *)boyGObj) != 0 && (sub = GOBJ_ACT(((int *)boyGObj)))->actMode == 49 &&
        (box = sub->box) != 0 && IsThisBoxTruck(box) == 7) {
        return 1;
    }
    return 0;
}

/* The actor entry parameter is volatile: the actor scheduler writes the
   caller's home slot while this thread is parked in _ACTWait. */
INCLUDE_ASM(ChangeRunMode_135);

INCLUDE_ASM(subGirlBrainMain);

/* a file-scope static helper, inlined in subGirlBrain_HideAdvance's move arm
 * and in subGirlBrain_Pulledup */
static inline void girlBrainSetWalkRatio(GObj *g, float ratio) /* derived name */
{
    Act *s = GOBJ_ACT(g);
    float walk = 0.5f;

    if (walk < ratio && ACTWay_IsMustWalkFromWay(g)) {
        s->stick.mag = walk;
    } else {
        s->stick.mag = ratio;
    }
}

void subGirlBrain_Pulledup(GObj *volatile self)
{
    float self_pos[4];
    float boy_pos[4];
    float ofs[4];
    float base[4];
    float top[4];
    float well[4];
    float cur[4];
    float sk[4];
    float oz[4];
    Act *sub = GOBJ_ACT(self);
    int hit;
    float d;
    float dy;
    float lim;
    int ry;

    GetRootProjectionPosOfGObj(self_pos, (void *)self);
    GetRootProjectionPosOfGObj(boy_pos, boyGObj);
    *(int *)((char *)GOBJ_ACT(self)->work + 0x374) = 0;
    sceVu0ScaleVector(ofs, test_CURRENTORIENT((boyGObj)), 60.0f);
    sceVu0AddVector(base, boy_pos, ofs);
    base[1] = base[1] - 50.0f;
    top[0] = base[0];
    top[2] = base[2];
    top[1] = base[1] + 1000.0f;
    if (ACTCheckCollis_WELL(base, top, ((int *)boyGObj), well, 0.0f)) {
        boy_pos[0] = well[0];
        boy_pos[1] = well[1];
        boy_pos[2] = well[2];
        if (floorGObj_ACTCheckCollis_WELL != 0 &&
            *(int *)((char *)floorGObj_ACTCheckCollis_WELL + 0xC) == 0x11) {
            GOBJ_WORK(self)->floorObj = floorGObj_ACTCheckCollis_WELL;
        }
        boy_pos[1] = boy_pos[1] - 10.0f;
    }
    if (GOBJ_ACT(((int *)boyGObj))->actMode == 85) {
        boy_pos[0] = GOBJ_ACT(((int *)boyGObj))->env.ditchPos[0];
        boy_pos[1] = GOBJ_ACT(((int *)boyGObj))->env.ditchPos[1];
        boy_pos[2] = GOBJ_ACT(((int *)boyGObj))->env.ditchPos[2];
    }
    if (!ACTWayMove_BeginDetail((void *)self, self_pos, boy_pos, 0, 0, 0)) {
        while (1) {
            _ACTWait(1);
        }
    }
    for (;;) {
        cur[0] = test_CURRENTROOT((void *)self)[0];
        cur[1] = test_CURRENTROOT((void *)self)[1];
        cur[2] = test_CURRENTROOT((void *)self)[2];
        hit = ACTWayMove_NextDetail((void *)self, sub->dir, boy_pos, 0);
        debug_NMarker(boy_pos, 0xFF, 0, 0, 100.0f);
        if (!hit) {
            sub->stick.mag = 0;
        } else {
            sub->dir[0] = sub->wayNodeX;
            sub->dir[1] = sub->wayNodeY;
            sub->dir[2] = sub->wayNodeZ;
            girlBrainSetWalkRatio((void *)self, 1.0f);
        }
        d = _DistxzGV(boy_pos, cur);
        dy = boy_pos[1] - cur[1];
        dy = (dy < 0.0f) ? -dy : dy;
        lim = (GOBJ_ACT(((int *)boyGObj))->actMode == 85) ? 200.0f : 100.0f;
        if (d < 30.0f && dy < 200.0f) {
            sub->stick.mag = 0;
            GetSkeltonOrient(sk, (void *)self, 0x2C);
            _OrientXZGV(oz, test_CURRENTROOT((boyGObj)), test_CURRENTROOT((void *)self));
            ry = _RotyGV(sk, oz);
            if (0x15 <= ((ry < 0) ? -ry : ry)) {
                if (0 < ry) {
                    ATGoalTurnSet((void *)self, 3, 2, oz);
                } else {
                    ATGoalTurnSet((void *)self, 3, 1, oz);
                }
            } else {
                sub->flags18.ll |= 0x2000000000000;
            }
        } else if (d < lim) {
            sub->stick.mag =
                (sub->stick.mag < 0.0f) ? 0.0f : ((0.5f < sub->stick.mag) ? 0.5f : sub->stick.mag);
        }
        _ACTCharStatus_Set((void *)self, 26, -1.0f, 0);
        GOBJ_WORK(self)->boyDist = _DistGV(test_CURRENTROOT((void *)self), boy_pos);
        _ACTWait(1);
    }
}

#include "girl_brain_attract.c.inc"

INCLUDE_ASM(_girlBrainHide_MakeHidePoint);

static void girlBrainHide_GoalTurn(float *dir, unsigned char sendMail)
{
    float mo[4];
    float eye[4];
    GObj *girl;
    ActWork *p;
    int r;

    girl = girlGObj;
    GetRootMotionOrient(mo, girl);
    r = _RotyGV(mo, dir);
    r = (r < 0) ? -r : r;
    if (r >= 0x2E) {
        p = GOBJ_WORK(girl);
        p->hideDirX = dir[0];
        p->hideDirY = dir[1];
        p->hideDirZ = dir[2];
        GetEyeDirection((char *)eye, girl);
        if (_RotyGV(eye, dir) > 0) {
            debug_StdPrintfDummy("turnL mail\n");
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xDC);
            } else {
                ACTSendMailCorrect(girl, 0xDE);
            }
        } else {
            debug_StdPrintfDummy("turnR mail\n");
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xDB);
            } else {
                ACTSendMailCorrect(girl, 0xDD);
            }
        }
    }
}

/* A static inline: hands the girl's sub a move direction at the stick ratio
   `run` (subGirlBrain_Hide passes the full 1.0f). */
static inline void girlBrainSetMoveDir(float *d, float run) /* derived name */
{
    Act *s;

    s = GOBJ_ACT(girlGObj);
    s->stick.mag = run;
    s->dir[0] = d[0];
    s->dir[1] = d[1];
    s->dir[2] = d[2];
}

void subGirlBrain_Hide(GObj *volatile self)
{
    float hp[4];
    float cand[4];
    int cnt = 0;
    float rad = 80.0f;
    int near;
    /* the girl object handed in by the actor entry, read from the volatile
       parameter once */
    GObj *g;

    /* isHideRecheck, a GNU nested function: it writes the enclosing `rad`
       through the static chain. */
    int isHideRecheck(float *from, float *to, float *root)
    {
        float v0[4];
        float v1[4];
        float v2[4];
        int i;
        int r;

        sceVu0SubVector(v0, from, root);
        sceVu0SubVector(v1, to, root);
        for (i = 0; i < brain_val.listB.num; i++) {
            sceVu0SubVector(v2, brain_val.listB.ent[i].pos, root);
            r = _RotyGV(v0, v2);
            if ((r < 0 ? -r : r) < 45) {
                rad = 80.0f;
                return 1;
            }
        }
        r = _RotyGV(v0, v1);
        if (!((r < 0 ? -r : r) < 46)) {
            return 1;
        }
        if (_DistxzSqGV(from, root) < _DistxzSqGV(to, root) &&
            !(_DistxzSqGV(from, to) < 25600.0f)) {
            return 1;
        }
        return 0;
    }

    _ACTWait(1);
    hp[0] = brain_val.hidePoint[0];
    hp[1] = brain_val.hidePoint[1];
    hp[2] = brain_val.hidePoint[2];
    while (1) {
        if (cnt++ % ((60 - systemStatus[0] * 10) / systemStatus[1] * 2) == 0 &&
            girlBrainMain_CheckWarningMode(0) != 3) {
            brain_val.warn = 1;
        }
        _girlBrainHide_MakeHidePoint(cand, rad);
        if (isHideRecheck(hp, cand, test_CURRENTROOT((boyGObj)))) {
            rad = _DistxzGV(test_CURRENTROOT((boyGObj)), test_CURRENTROOT((void *)self));
            rad = (rad < 200.0f) ? 200.0f : ((800.0f < rad) ? 800.0f : rad);
            _girlBrainHide_MakeHidePoint(hp, rad);
            cand[0] = hp[0];
            cand[1] = hp[1];
            cand[2] = hp[2];
        }
        if (isHidePointTooHigh(cand) ||
            girlBrainHideCheckIntercept(brain_val.girlPos, cand, (char *)brain_val.hide.ent,
                                        brain_val.hide.num)) {
            brain_val.warn = 1;
        }
        near = _DistxzSqGV(cand, brain_val.girlPos) < 3600.0f;
        if (near) {
            hp[0] = cand[0];
            hp[1] = cand[1];
            hp[2] = cand[2];
        }
        if (_DistxzSqGV(hp, brain_val.girlPos) < 10000.0f || near) {
            g = self;
            GOBJ_ACT(girlGObj)->stick.mag = 0;
            _ACTCharStatus_Set(g, 7, -1.0f, 0);
            if (_DistxzSqGV(hp, brain_val.girlPos) < 6400.0f || near) {
                float dir[4];

                _OrientXZGV(dir, brain_val.boyPos, brain_val.girlPos);
                girlBrainHide_GoalTurn(dir, 1);
            }
        } else {
            float dir[4];

            _OrientXZGV(dir, cand, brain_val.girlPos);
            g = self;
            girlBrainSetMoveDir(dir, 1.0f);
            _ACTCharStatus_Set(g, 6, -1.0f, 0);
        }
        _ACTWait(1);
    }
}

/* A static inline, inlined three times: true when the straight segment from
   `from` to `to` clears both the wall and the wall-field collision. */
static inline int isNoWallBetween(float *from, float *to) /* derived name */
{
    ClipWork work;

    work.radius = 10.0f;
    sceVu0CopyVector(work.pt[0], from);
    sceVu0CopyVector(work.pt[1], to);
    ClipWall(&work);
    if (work.wall.elem == 0) {
        ClipWallField(&work);
        if (work.wall.elem == 0) {
            return 1;
        }
    }
    return 0;
}

/* A static inline: true when `b` is within 100 units vertically and 100
   units in the plane of `a`. */
static inline unsigned char isNearPoint(float *a, float *b) /* derived name */
{
    if ((a[1] - b[1] < 0.0f ? -(a[1] - b[1]) : a[1] - b[1]) < 100.0f) {
        if (_DistSqGV(a, b) < 10000.0f) {
            return 1;
        }
    }
    return 0;
}

/* A static inline, inlined twice inside girlBrainRunawaySearchPoint: true
   when no listB entry lies closer to `p` than the girl does, and no listB
   entry lies closer to `p` than it lies to the girl. */
static inline unsigned char isRunawayPointClear(float *p, float *girl) /* derived name */
{
    int i;
    float d;

    d = _DistSqGV(p, girl);
    for (i = 0; i < brain_val.listB.num; i++) {
        if (_DistSqGV(p, brain_val.listB.ent[i].pos) < d) {
            return 0;
        }
    }
    for (i = 0; i < brain_val.listB.num; i++) {
        float dg = _DistSqGV(girl, brain_val.listB.ent[i].pos);
        float dp = _DistSqGV(p, brain_val.listB.ent[i].pos);

        if (dp < dg) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM(CorrectList_208);

INCLUDE_ASM(girlBrainRunawaySearchPoint);

INCLUDE_ASM(girlBrainRunawayMoveByWay);

/* A static inline: points `v` at the first listB entry within 300 units of
   `p` whose bearing from `dir` is under 45 degrees. */
static inline void girlBrainEscapeFaceCheck(float *p, float *dir, Vec4u *v) /* derived name */
{
    int i;

    memset(v, 0, 16);
    v->f[3] = 1.0f;
    for (i = 0; i < brain_val.listB.num; i++) {
        if (_DistSqGV(p, brain_val.listB.ent[i].pos) < 90000.0f) {
            sceVu0SubVector(v->f, brain_val.listB.ent[i].pos, p);
            if ((_RotGV(dir, v->f) < 0 ? -_RotGV(dir, v->f) : _RotGV(dir, v->f)) < 45) {
                break;
            }
        }
    }
}

/* girlBrainDebugPrint in subGirlBrain_Escape: called in arm 1 after
   `mode = 2` and after `mode = 3`, and in cases 1 and 2 after
   girlBrainRunawayMoveByWay. */

/* The move-state names subGirlBrain_Escape prints, defined here before it. */
static char *moveStateName[5] = {"IDLE", "MOVE START", "MOVE LOOP", "END",
                                 "WAIT"}; /* derived name */

INCLUDE_ASM(subGirlBrain_Escape);

void ClipTwinVector(float *out, float *from, float *to, float max)
{
    float d;
    float t;

    d = _DistGV(from, to);
    if (max < d) {
        t = (d - max) / d;
        _InterGV(out, from, to, t, 1.0f - t);
    } else {
        out[0] = to[0];
        out[1] = to[1];
        out[2] = to[2];
    }
}

/* `inline`: the four Danger_* GetSafePosition bodies below expand it and its
   out-of-line copy closes the TU's deferred run. */
static void Danger_Bomb(GObj *self);
static void Danger_Gondola(GObj *self);
static void Danger_Box(GObj *self);
static void Danger_Rotobject(GObj *self);

INCLUDE_ASM(GetSafePosition_233);

INCLUDE_ASM(Danger_Bomb);

INCLUDE_ASM(GetSafePosition_240);

INCLUDE_ASM(Danger_Gondola);

/* the three escape angles Danger_Box's safe-position search tries */
static int dangerEscapeAngle[3] = {0, -90, 90}; /* derived name */

INCLUDE_ASM(GetSafePosition_247);

INCLUDE_ASM(Danger_Box);

void subGirlBrain_HideAdvance(GObj *volatile self)
{
    float self_pos[4];
    float boy_pos[4];
    Act *sub = GOBJ_ACT(self);
    unsigned char hit;

    GetRootProjectionPosOfGObj(self_pos, (void *)self);
    GetRootProjectionPosOfGObj(boy_pos, boyGObj);
    ACTWayMove_BeginDetail((void *)self, self_pos, boy_pos, 0, 0, 0);
    for (;;) {
        brain_val.hideAdvWait = (60 - systemStatus[0] * 10) / systemStatus[1];
        GetRootProjectionPosOfGObj(boy_pos, boyGObj);
        hit = ACTWayMove_NextDetail((void *)self, sub->dir, boy_pos, 0);
        debug_NMarker(boy_pos, 0xFF, 0, 0, 100.0f);
        if (!hit ||
            (sub->wayGoalDist < 100.0f &&
             (sub->wayGoalHeight < 0.0f ? -sub->wayGoalHeight : sub->wayGoalHeight) < 100.0f)) {
            sub->stick.mag = 0;
            _ACTWait(1);
            continue;
        }
        {
            /* the actor-entry home is `volatile` (the scheduler rewrites the GObj
             * slot between waits), so the arm reads it once at its top and
             * works from the captured pointer */
            void *g = (void *)self;

            sub->dir[0] = sub->wayNodeX;
            sub->dir[1] = sub->wayNodeY;
            sub->dir[2] = sub->wayNodeZ;
            girlBrainSetWalkRatio(g, 1.0f);
        }
        _ACTWait(1);
    }
}

static int isEnterHideadv_EnemyLocation(float *bpos, float *gpos)
{
    float o1[4];
    float o2[4];
    int i;
    float d;

    bpos[0] = test_CURRENTROOT((boyGObj))[0];
    bpos[1] = test_CURRENTROOT((boyGObj))[1];
    bpos[2] = test_CURRENTROOT((boyGObj))[2];
    gpos[0] = test_CURRENTROOT((void *)girlGObj)[0];
    gpos[1] = test_CURRENTROOT((void *)girlGObj)[1];
    gpos[2] = test_CURRENTROOT((void *)girlGObj)[2];
    _OrientXZGV(o1, bpos, gpos);
    for (i = 0; i < brain_val.hide.num; i++) {
        if (*(int *)((char *)brain_val.hide.ent[i].obj + 0xC) == 4) {
            d = _DistGV(gpos, brain_val.hide.ent[i].pos);
            if (!(1500.0f < d)) {
                if (_DistSqGV(bpos, brain_val.hide.ent[i].pos) < (d + 100.0f) * (d + 100.0f)) {
                    return 0;
                }
                if (d < 150.0f) {
                    return 0;
                }
                _OrientXZGV(o2, brain_val.hide.ent[i].pos, gpos);
                if (_AbsRotyGV(o1, o2) < 45) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

static int isEnterHideadv(void)
{
    float buf[8];
    int rv = 0;
    float diff;
    if (((int *)boyGObj) == 0) {
        goto ret0;
    }
    if ((void *)girlGObj == 0) {
        return 0;
    }
    GetRootProjectionPosOfGObj(buf, boyGObj);
    GetRootProjectionPosOfGObj(buf + 4, girlGObj);
    diff = buf[1] - buf[5];
    if (diff < 0.0f) {
        if (-diff > 200.0f) {
            goto set;
        }
        goto test;
    }
    if (diff > 200.0f) {
    set:
        rv = 1;
    }
test:
    if (rv == 0) {
        goto ret0;
    }
    if (_DistxzSqGV(buf, buf + 4) < 22500.0f) {
        return 1;
    }
    if (_DistxzSqGV(buf, buf + 4) < 250000.0f) {
        if (isEnterHideadv_EnemyLocation(buf, buf + 4) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}

static unsigned char wayTestBegin = 1; /* derived name */

static unsigned char wayTestMoving = 0; /* derived name */

INCLUDE_ASM(WayTest);

/* The attract-state names, defined here after WayTest. */
static char *wayTestStateName[9] = {
    "IDLE",    "SEARCHWAY", "LOSTTWAY", "APPROACH", "GOAL",
    "ATTRACT", "LOOKONLY",  "ATTRLOOK", "FINISH"}; /* derived name */

/* girl_act.o's .data global after the attract-state names: the brain's work
   record, all zero, explicitly initialised so that it stays in .data. */
GirlBrainWork brain_val = {0};

/* girl_act.o's .sdata globals (declared in girl_act.h) */
int hyde_test = 0;

int padtimer_stand = 0;

int padtimer_walk = 0;

int padtimer_run = 0;

/* the motion-def row of an actor's current motion (boyact.c's CHAINROW) */
#define MOTDIRROW(self) (GOBJ_SUB(self)->ctrl.motion + motionKind) /* derived name */

/* The girl's control thread.  A block of compiled-out debug code sits in
   it; the strings it printed ("src/girl_act.c", "NOTARGET",
   "[%s] %4d %4d %4d", "delete wg 2\n") stay in .rodata between this
   function's "girl no!!\n" and its jump table. */
INCLUDE_ASM(subGirlControl);

extern int fptodp(float v);

void subGirlCollision(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float ori[4];
    float dir[4];
    float eye[4];
    float sk[4];
    float oz[4];
    int cnt = 0;
    int cnt2 = 0;
    float ang;
    float rot;
    float dirAng;
    float sideAng;
    int hold;
    int step;
    int flag;
    int ry;
    int rz;
    MotionDef *rec;
    const ActModeRec *attr;
    GObj *p;

    while (sub->motReq == 0) {
        _ACTWait(1);
    }
    if (GetDifferenceFromLowerField((void *)self, 0x2C) > 200.0f) {
        ACTSendMailCorrect((void *)self, 7);
    }
    for (;;) {
        flag = 0;
        ACTGame_CommonLoop((void *)self);
        brainLevelProcess(&brainGirl);
        ACTLookTargetSystem_Exec((void *)self);
        ACTParaStatus_Exec((void *)self);
        if (sub->stick.mag != 0.0f) {
            switch ((unsigned int)sub->actMode) {
            case 1:
                ang = _ACTGame_GetParamF(33);
                if (ang < 60.0f) {
                    ang = 60.0f;
                }
                break;
            case 2:
                ang = _ACTGame_GetParamF(34);
                if (*(int *)((char *)GOBJ_ACT(self)->work + 0x830) == 10 &&
                    sub->modeFrame < (60 - systemStatus[0] * 10) / systemStatus[1] / 3) {
                    if (ang < 60.0f) {
                        ang = 60.0f;
                    }
                }
                break;
            case 3:
                ang = _ACTGame_GetParamF(35);
                if (*(int *)((char *)GOBJ_ACT(self)->work + 0x830) == 10 &&
                    sub->modeFrame < (60 - systemStatus[0] * 10) / systemStatus[1] / 3) {
                    if (ang < 60.0f) {
                        ang = 60.0f;
                    }
                }
                break;
            default:
                ang = 105.0f;
                break;
            }
            dir[0] = sub->dir[0];
            dir[1] = sub->dir[1];
            dir[2] = sub->dir[2];
            GetRootMotionOrient(ori, self);
            rot = (float)_RotyGV(ori, dir);
            dir[1] = ori[1] = 0.0f;
            sceVu0Normalize(dir, dir);
            sceVu0Normalize(ori, ori);
            if (ang < ((rot < 0.0f) ? -rot : rot)) {
                sub->env.turnDir.f[0] = dir[0];
                sub->env.turnDir.f[1] = dir[1];
                sub->env.turnDir.f[2] = dir[2];
                GetEyeDirection((char *)eye, self);
                rot = (float)_RotyGV(eye, dir);
                rec = motionKind + GOBJ_SUB(self)->ctrl.motion;
                if ((rec->flags.word >> 4) & 1) {
                    padtimer_run = 0;
                    padtimer_walk = 0;
                }
                if (rot > 0.0f) {
                    ACTSendMailCorrect((void *)self, 216);
                } else {
                    ACTSendMailCorrect((void *)self, 215);
                }
            } else {
                GetSkeltonOrient(sk, (void *)self, 1);
                if (debug_font_flag & 1) {
                    debug_Printf(10, 100, 0x0FFFFFFF, "[%d]\n",
                                 _AbsRotyGV((char *)sub + 0x110, sk));
                }
                if (_AbsRotyGV((char *)sub + 0x110, sk) < 60) {
                    ACTSendMailCorrect((void *)self, 224);
                }
                debug_Arrow(100.0f, test_CURRENTROOT((void *)self), sk, 0, 0xFF, 0);
            }
        } else if (sub->flags18.ll & 0x300000000000000) {
            if (!ACTGame_FLAG_TETSUNAGI()) {
                dirAng = ((int)(sub->flags18.ll >> 56) & 1) ? 90.0f : 60.0f;
                sideAng = ((int)(sub->flags18.ll >> 56) & 1) ? 150.0f : 130.0f;
                step = ((int)(sub->flags18.ll >> 56) & 1) ? 60 : 2;
                hold = ((int)(sub->flags18.ll >> 57) & 1) && cnt2 > 0;
                GetSkeltonOrient(sk, (void *)self, 35);
                GetSkeltonOrient(eye, (void *)self, 44);
                _OrientXZGV(oz, GOBJ_SUB(self)->root.lookPos, test_CURRENTROOT((void *)self));
                ry = _AbsRotyGV(eye, sk);
                rz = _AbsRotyGV(eye, oz);
                if (dirAng < ry && sideAng < rz) {
                    flag = 1;
                }
                if (step * ((60 - systemStatus[0] * 10) / systemStatus[1]) / 60 < cnt && !hold) {
                    if ((int)(sub->flags18.ll >> 54) & 1) {
                        ATGoalTurnSet((void *)self, 1, 1, oz);
                    } else {
                        ATGoalTurnSet((void *)self, 1, 2, oz);
                    }
                }
            }
        }
        cnt = flag ? cnt + 1 : 0;
        if (sub->actMode == 10) {
            cnt2 = (60 - systemStatus[0] * 10) / systemStatus[1] * 4;
        }
        if (cnt2) {
            cnt2--;
        }
        ACTGame_SaveActorInformation(self);
        if (((int *)boyGObj) != 0 && (void *)girlGObj != 0) {
            if (!ACTGame_CheckHandMotion(boyGObj, girlGObj)) {
                ACTSendMailCorrect((void *)self, 59);
                debug_StdPrintfDummy("mot error\n");
            }
            if (!(_DistSqGV(test_CURRENTROOT((boyGObj)), test_CURRENTROOT((void *)girlGObj)) <
                  250000.0f)) {
                if (GOBJ_SUB(((int *)boyGObj))->root.hand1.mode == 5) {
                    debug_StdPrintfDummy("hand connect error\n");
                }
                ACTGame_DisconnectHand();
                debug_StdPrintfDummy("dist fatal error, [%f]\n",
                                     fptodp(_DistGV(test_CURRENTROOT((boyGObj)),
                                                    test_CURRENTROOT((void *)girlGObj))));
                ACTSendMailCorrect((void *)self, 59);
            }
        }
        switch ((unsigned int)sub->actMode) {
        case 0x2C: {
            sceVu0FVECTOR home = {814.0f, 1827.0f, 865.0f, 1.0f};
            sceVu0FVECTOR gate = {608.0f, 1600.0f, -775.0f, 1.0f};

            if (!gflagChk(95)) {
                _OrientXZGV(sub->dir, gate, test_CURRENTROOT((void *)self));
            } else if (test_CURRENTROOT((void *)self)[2] > 350.0f) {
                _OrientXZGV(sub->dir, home, test_CURRENTROOT((void *)self));
            } else {
                sub->dir[0] = 0.0f;
                sub->dir[1] = 0.0f;
                sub->dir[2] = -1.0f;
            }
            SetMotionDirection((void *)self, (float *)((char *)sub + 0x110));
            sub->stick.mag = 1.0f;
            ACTSendMailCorrect((void *)self, 205);
            break;
        }
        case 1:
            ACTSendMailCorrect((void *)self, 183);
            break;
        case 2:
        case 3:
            break;
        }
        p = GOBJ_SUB(self)->parent.obj;
        if (p != 0 && p->kind == 17) {
            if (GetBoxMode(p) == 2) {
                ACTSendMailCorrect((void *)self, 245);
            }
        }
        ATGoalTurnSendMail((void *)self);
        attr = &actModeTbl[sub->actMode];
        if (attr->softIk) {
            GOBJ_SUB(self)->root.ikRate0 = 0.3f;
        } else {
            GOBJ_SUB(self)->root.ikRate0 = GOBJ_WORK(self)->defIkRate0;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM_LIT(afterGirlHand);

/* this TU's uses of GetHeightOfFieldPlaneDifference do not fit the
   prototype in motionManager2.h */

/* the hand manager's record, all zero and explicitly initialised so that it
   stays in .data */
GirlStand handmgr = {0};

INCLUDE_ASM(HandMgr_GetDistHand_289);

INCLUDE_ASM(HandMgr_Update_297);

INCLUDE_ASM(HandMgr_Judge_301);

INCLUDE_ASM(HandMgr_Print_305);

INCLUDE_ASM(HandMgr_Speed_309);

INCLUDE_ASM(GetBoyMode_313);

INCLUDE_ASM(actGirlHand);

INCLUDE_ASM(actGirlPulledReady);

INCLUDE_ASM(actGirlPulledGo);

INCLUDE_ASM(actGirlDitch3mReady);

INCLUDE_ASM_LIT(actGirlDitch3mExec);

INCLUDE_ASM_LIT(actGirlStand);

INCLUDE_ASM_LIT(actGirlWalk);

INCLUDE_ASM_LIT(actGirlRun);

INCLUDE_ASM_LIT(actGirlJump);

INCLUDE_ASM_LIT(actGirlAttack);

INCLUDE_ASM(actGirlReadyMove);

INCLUDE_ASM(actGirlRescueDst);

/* the status-range test inside actGirlSupportGBLoop's loop */
static inline unsigned char isGirlSupportGBStatus(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(((int *)boyGObj))->actMode;

    if (st < 0x6B) {
        if (0x68 <= st) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM(actGirlSupportBGBegin);

int girlcalled;

INCLUDE_ASM(actGirlStart);

INCLUDE_ASM(GirlAct_BoyAndMeCollisionMail);

static inline unsigned char isGirlEscortStatus(void) /* derived name */
{
    Act *s = GOBJ_ACT(girlGObj);
    int mode = s->actMode;
    const ActModeRec *attr = &actModeTbl[mode];
    if (attr->escort && mode != 0x6F && ((int)(s->flags20.ll >> 46) & 1)) {
        return 1;
    }
    return 0;
}

static inline const EscortPoint *searchEscortPoint(int area, int point) /* derived name */
{
    const EscortPoint *p;
    int i;
    for (i = 0; i < 98; i++) {
        p = &autoEscortData[i];
        if (p->area == area && p->point == point) {
            return p;
        }
    }
    return 0;
}

INCLUDE_ASM(IsGirlStatusEscortEnable);

inline int isMustCheckCylinder(void *a, void *b)
{
    if ((a == (void *)((int *)boyGObj) && b == (void *)girlGObj) ||
        (a == (void *)girlGObj && b == (void *)((int *)boyGObj))) {
        if (GOBJ_ACT(girlGObj)->actMode == 0x4E) {
            return 1;
        }
    }
    return 0;
}

static inline void dispEscortSphere(void *pos, float r, unsigned char in) /* derived name */
{
    Col4 col;

    if (debug_disp_escort_ball) {
        MatrixDrive_PushMatrix();
        /* the wire sphere colour: a GNU constructor expression, which gcc keeps
           as an anonymous .rodata constant and copies here */
        col = (Col4){{0, 0x10, 0x20, 0x80}};
        if (in) {
            col.c[0] = 0xFF;
        }
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(r, &col, 16, 8);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

INCLUDE_ASM(func_00175098);

INCLUDE_ASM(func_001752D0);

/* the *(sub+0x688) ACT parameter block, viewed as a struct whose stores are
   member stores */
typedef struct { /* field names derived */
    char pad0[944];
    int turnMailWait; /* 0x3B0 : ActWork's turnMailWait, set by "cannot reach" */
    char pad3B4[364];
    float hintPosX; /* 0x520 : hint-point target position */
    float hintPosY;
    float hintPosZ;
} ActPara; /* derived name */

INCLUDE_ASM(FindGirlPullupFloorBoxGObj);

INCLUDE_ASM(actGirlSupportGBBegin);

INCLUDE_ASM(actGirlSupportGBLoop);

INCLUDE_ASM(actGirlSupportGBEnd);

INCLUDE_ASM(actGirlHangG3M);

INCLUDE_ASM(actGirlDitch3mExec);

INCLUDE_ASM(actGirlStand);

INCLUDE_ASM(actGirlWalk);

INCLUDE_ASM(actGirlRun);

INCLUDE_ASM(actGirlHang);

INCLUDE_ASM(actGirlBHang);

INCLUDE_ASM(actGirlAttack);

INCLUDE_ASM(actGirlBecall);

INCLUDE_ASM(actGirlBehanged);

INCLUDE_ASM(actGirlAttractAction);

INCLUDE_ASM(actGirlHand50);

INCLUDE_ASM(afterGirlHand50);

INCLUDE_ASM(actGirlHand100);

INCLUDE_ASM(afterGirlHand100);

INCLUDE_ASM(actGirlHand200);

INCLUDE_ASM(afterGirlHand200);

INCLUDE_ASM(NotNeedBackHand);

INCLUDE_ASM(SetGirlDangerGObj);

INCLUDE_ASM(ClearGirlDangerGObj);

INCLUDE_ASM(subGirlBrain_Idle);

INCLUDE_ASM(subGirlBrain_Hesitate);

INCLUDE_ASM(subGirlBrain_Becarry);

INCLUDE_ASM(subGirlBrain_Busy);

INCLUDE_ASM(subGirlBrain_DangerEnv);

INCLUDE_ASM(enemy_list_compare);

INCLUDE_ASM(ACTCheckCollis_SAFE);

INCLUDE_ASM(afterGirlHand);

INCLUDE_ASM(afterGirlPulledGo);

INCLUDE_ASM(actGirlJump);

INCLUDE_ASM(afterGirlSupportBGBegin);
