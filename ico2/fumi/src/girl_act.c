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

INCLUDE_ASM(motGirlHand50);

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
    int curMode;    /* 0x57DC the mode the brain last switched to */
    int targetFlag; /* 0x57E0 bit 16 of the winning BrainTarget's b18 word */
    char pad57E4[12];
    float runawayGoal[4];  /* 0x57F0 the runaway goal */
    float hidePoint[4];    /* 0x5800 last accepted hide point */
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
    int *flag = &brain_val.targetFlag;
    Brain *b = &brainGirl;
    void *obj = 0;

    brainGetTarget(b);
    *flag = 0;
    if (b->idx != -1) {
        obj = (void *)b->tgt[b->idx].gobj;
        *flag = *(unsigned short *)&b->tgt[b->idx].detail & 1;
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

INCLUDE_ASM(subGirlBrain_Pulledup);

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

/* A static inline: hands the girl's sub a move direction at the full run
   ratio.  `run` is declared ahead of the two loads, as this TU's
   girlBrainSetWalkRatio declares its own run/walk ratios. */
static inline void girlBrainSetMoveDir(float *d) /* derived name */
{
    float run = 1.0f;
    Act *s;

    s = GOBJ_ACT(girlGObj);
    s->stick.mag = run;
    s->dir[0] = d[0];
    s->dir[1] = d[1];
    s->dir[2] = d[2];
}

INCLUDE_ASM(isHideRecheck_189);

INCLUDE_ASM(subGirlBrain_Hide);

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

INCLUDE_ASM(subGirlBrain_HideAdvance);

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

INCLUDE_ASM(subGirlCollision);

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
