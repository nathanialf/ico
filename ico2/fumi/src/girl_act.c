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
inline void afterGirlHand50(GObj *volatile self)
{
    debug_StdPrintfDummy("girl after func\n");
    iosOmSendMail(boyGObj, 87, isysCurrentGObj);
    ACTGame_DisconnectHand();
}

inline void actGirlHand50(GObj *volatile self)
{
    float dir[4];
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlHand50\n");
    sceVu0ScaleVector(dir, (float *)((char *)sub + 0x4A0), -1.0f);
    SetMotionDirection((void *)self, dir);
    SetDirectRootPosition((void *)self, (float *)((char *)sub + 0x560));
    sub->readyFlags = 0;
    sub->after = (void *)afterGirlHand50;
    do {
        _ACTWait(1);
    } while ((sub->readyFlags & 0x10) == 0);
    debug_StdPrintfDummy("girl error flg get\n");
    for (;;) {
        ACTSendMailCorrect((void *)self, 87);
        _ACTWait(1);
    }
}

void motGirlHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motGirlHand50\n");
    while (1) {
        iosOmSendMail(boyGObj, 83, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 521 || !(GOBJ_SUB(self)->ctrl.motion < 527)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 84, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    if ((((int)(sub->flags18.ll >> 38)) & 1) == 0) {
        iosOmSendMail(boyGObj, 16, isysCurrentGObj);
        ACTSendMailCorrect((void *)self, 7);
    }
    iosOmSendMail(boyGObj, 85, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 81, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 65);
        _ACTWait(1);
    }
}

inline void afterGirlHand100(GObj *volatile self)
{
    debug_StdPrintfDummy("girl after func\n");
    iosOmSendMail(boyGObj, 92, isysCurrentGObj);
    ACTGame_DisconnectHand();
}

inline void actGirlHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlHand100\n");
    sub->actMode = 79;
    sub->after = (void *)afterGirlHand100;
    sub->readyFlags = 0;
    do {
        _ACTWait(1);
    } while ((sub->readyFlags & 0x10) == 0);
    debug_StdPrintfDummy("girl error flg get\n");
    for (;;) {
        ACTSendMailCorrect((void *)self, 92);
        _ACTWait(1);
    }
}

void motGirlHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motGirlHand100\n");
    while (1) {
        iosOmSendMail(boyGObj, 88, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 521 || !(GOBJ_SUB(self)->ctrl.motion < 527)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 89, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(boyGObj, 90, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 88, sub->env.motOriReq);
    while (GOBJ_SUB(self)->ctrl.motion < 521 || !(GOBJ_SUB(self)->ctrl.motion < 527)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 91, isysCurrentGObj);
        if (sub->readyFlags & 8)
            break;
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 65);
        _ACTWait(1);
    }
}

inline void afterGirlHand200(GObj *volatile self)
{
    debug_StdPrintfDummy("girl after func\n");
    iosOmSendMail(boyGObj, 97, isysCurrentGObj);
    ACTGame_DisconnectHand();
}

inline void actGirlHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlHand200\n");
    sub->actMode = 80;
    sub->after = (void *)afterGirlHand200;
    sub->readyFlags = 0;
    do {
        _ACTWait(1);
    } while ((sub->readyFlags & 0x10) == 0);
    debug_StdPrintfDummy("girl error flg get\n");
    for (;;) {
        ACTSendMailCorrect((void *)self, 97);
        _ACTWait(1);
    }
}

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
        iosOmSendMail(boyGObj, 93, isysCurrentGObj);
        if (sub->readyFlags & 1)
            break;
        _ACTWait(1);
    }
    goto held;
expired:
    ACTSendMailCorrect((void *)self, 97);
    debug_StdPrintfDummy("%s sync error\n",
                         (void *)self == (void *)((int *)boyGObj) ? "boy" : "girl");
held:
    while (GOBJ_SUB(self)->ctrl.motion < 521 || !(GOBJ_SUB(self)->ctrl.motion < 527)) {
        sub->motReq = SetMotionRequest((void *)self, 1, sub->env.motOriReq);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(boyGObj, 94, isysCurrentGObj);
        if (sub->readyFlags & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(boyGObj, 95, isysCurrentGObj);
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        iosOmSendMail(boyGObj, 96, isysCurrentGObj);
        if (sub->readyFlags & 8)
            break;
        _ACTWait(1);
    }
    sub->after = 0;
    for (;;) {
        ACTSendMailCorrect((void *)self, 65);
        _ACTWait(1);
    }
}

/* actGirlHand and the attract brain pass the girl and a target, which it does not read */
static void GirlBrainClearTarget(void *self, void *target)
{
    brainClsTargetLevel(&brainGirl);
}

inline void SetGirlDangerGObj(GObj *self)
{
    GObj *g = girlGObj;
    if (g != 0) {
        GOBJ_WORK(g)->dangerObj = self;
    }
}

inline void ClearGirlDangerGObj(void)
{
    char *g = (char *)girlGObj;
    if (g != 0) {
        GOBJ_WORK(g)->dangerObj = 0;
    }
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
    int curMode;               /* 0x57DC the mode the brain last switched to */
    sceVu0FVECTOR runawayGoal; /* 0x57E0 the runaway goal (subGirlBrain_Escape) */
    sceVu0FVECTOR hidePoint;   /* 0x57F0 last accepted hide point (subGirlBrain_Hide) */
    sceVu0FVECTOR runawayFrom; /* 0x5800 where the last runaway leg started */
    sceVu0FVECTOR girlRoot;    /* 0x5810 GetRootPosition of the girl */
    sceVu0FVECTOR girlPos;     /* 0x5820 the girl's own position, GetRootProjectionPosOfGObj */
    sceVu0FVECTOR boyRoot;     /* 0x5830 GetRootPosition of the boy */
    sceVu0FVECTOR boyPos;      /* 0x5840 the boy's GetRootProjectionPosOfGObj */
    WayPoint *lastWay;         /* 0x5850, the way point GetWay_next last returned */
    char pad5854[12];
    WVTObj hideWay;            /* 0x5860, the way the girl tries to the hide point */
    unsigned char warn;        /* 0x58E0 a brain state asks the main loop to checkWarning */
    unsigned char pad58E1;     /* 0x58E1 cleared each frame, never read */
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
    int pad5908
        [2];     /* 0x5908, to the 0x5910 girlBrainMain_Init clears (its memset of 22800 bytes) */
} GirlBrainWork; /* derived name; 16-aligned (the vectors): brain_val sits at 0x26B2D0, 12 bytes

                    after wayTestStateName */

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
    void *obj;   /* 0x00 the object the girl walks to */
    int pad4[3];
    sceVu0FVECTOR pos;      /* 0x10 */
    int kind;               /* 0x20 copied into the actor's 0x44 when the state ends */
    int mail;               /* 0x24 the mail the state sends when it ends */
    float goalDist;         /* 0x28 the way goal distance the girl arrives within */
    float goalHeight;       /* 0x2C the way goal height she arrives within */
    unsigned char fixedPos; /* 0x30 pos stays as set, not re-read from obj each frame */
    char pad31[15];
} GirlAttractParam; /* derived name; 0x40 bytes in this build: no arrival direction,

                       goal turn or slow-down distance */

inline void subGirlBrain_Idle(GObj *volatile self);
void subGirlBrain_Attract(GObj *volatile self);
void subGirlBrain_Escape(GObj *volatile self);
void subGirlBrain_Hide(GObj *volatile self);
inline void subGirlBrain_Hesitate(GObj *volatile self);
inline void subGirlBrain_Becarry(GObj *volatile self);
inline void subGirlBrain_Busy(GObj *volatile self);
void subGirlBrain_Pulledup(GObj *volatile self);
inline void subGirlBrain_DangerEnv(GObj *volatile self);

static GirlDangerEnv dangerEnvDefault = {0}; /* derived name */

/* the brain of each girl mode, by mode number; this build has nine modes
   (no hide-advance brain), and the tenth slot is zero */
static void (*girlBrainModeTable[10])(GObj *self) = {
    /* derived name */
    subGirlBrain_Idle, subGirlBrain_Attract,  subGirlBrain_Escape,
    subGirlBrain_Hide, subGirlBrain_Hesitate, subGirlBrain_Becarry,
    subGirlBrain_Busy, subGirlBrain_Pulledup, subGirlBrain_DangerEnv,
}; /* derived name */

static int othersKindList[3] = {4, 59, -1}; /* derived name */

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

inline void ACTGame_GirlBeforeFunc(GObj *self)
{
    Act *s;

    s = GOBJ_ACT(self);
    goalTurnReq.prio = 0;
    goalTurnReq.dir = 0;
    if (s->actMode != 68) {
        s->flags20.ll &= ~0x10ULL;
    }
}

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
    /* this build's mail numbers */
    int slow[2] = {207, 218};
    int fast[2] = {208, 219};
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

static inline int enemy_list_compare(int p, int q)
{
    float diff = *(float *)(p + 0x20) - *(float *)(q + 0x20);
    return (int)diff;
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

static void girlBrainMain_MakeOthersList(void)
{
    /* a GNU nested function */
    void sort_list(float *list, int n)
    {
        GirlSortEnt t;
        int i;
        int j;

        for (i = 0; i < n; i++) {
            sortList[i].idx = i;
            sortList[i].dist = _DistSqGV(list + i * 4, brain_val.girlRoot);
        }
        for (i = 0; i < n; i++) {
            for (j = n - 1; i < j; j--) {
                if (sortList[j].dist < sortList[j - 1].dist) {
                    t = sortList[j];
                    sortList[j] = sortList[j - 1];
                    sortList[j - 1] = t;
                }
            }
        }
        for (i = 0; i < n; i++) {
            float *d = sortPos[i];

            d[0] = list[i * 4 + 0];
            d[1] = list[i * 4 + 1];
            d[2] = list[i * 4 + 2];
        }
        for (i = 0; i < n; i++) {
            float *e = sortPos[sortList[i].idx];

            list[i * 4 + 0] = e[0];
            list[i * 4 + 1] = e[1];
            list[i * 4 + 2] = e[2];
        }
    }
    float d;
    int seen;
    int i;
    int j;
    int k;

    brain_val.hide.num = brain_val.listB.num = 0;
    for (i = 0; othersKindList[i] != -1; i++) {
        void *o;

        for (o = isysGObjSearchFromObjKindID_begin(othersKindList[i]); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (girlListIsAlive(o) && girlListIsOnBoy(o)) {
                if (!(brain_val.hide.num < 100)) {
                    /* "too many enemies", EUC-JP */
                    debug_StdPrintfDummy(
                        "\305\250\244\316\277\364\244\254\302\277\244\271\244\256\244\336\244\271");
                    debug_assert("src/girl_brain_main.c.inc", 438);
                    __assert("src/girl_brain_main.c.inc", 438, "0");
                }
                GetRootPosition(brain_val.hide.ent[brain_val.hide.num].pos, o);
                brain_val.hide.num++;
            }
        }
    }
    sort_list(brain_val.listB.ent[0].pos, brain_val.listB.num);
    sort_list(brain_val.hide.ent[0].pos, brain_val.hide.num);
    brain_val.others.num = 0;
    for (i = 0; othersKindList[i] != -1; i++) {
        void *o;

        for (o = isysGObjSearchFromObjKindID_begin(othersKindList[i]); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (girlListIsAlive(o)) {
                int n = brain_val.others.num;

                brain_val.others.ent[n].obj = o;
                GetRootProjectionPosOfGObj(brain_val.others.ent[n].pos, o);
                brain_val.others.ent[n].dist =
                    _DistGV(brain_val.others.ent[n].pos, brain_val.girlPos);
                brain_val.others.ent[n].flags = 1;
                if (girlListIsOnBoy(o)) {
                    brain_val.others.ent[n].flags |= 2;
                }
                brain_val.others.num++;
            }
        }
    }
    qsort(brain_val.others.ent, brain_val.others.num, sizeof(GirlListEnt), enemy_list_compare);
    brain_val.listB.num =
        girlListPick(brain_val.others.ent, brain_val.listB.ent, brain_val.others.num, 0xC);
    brain_val.hide.num =
        girlListPick(brain_val.others.ent, brain_val.hide.ent, brain_val.others.num, 0xF);
    brain_val.listD.num =
        girlListPick(brain_val.others.ent, brain_val.listD.ent, brain_val.others.num, 0xE);
    brain_val.listBNear = 0;
    if (brain_val.listB.num != 0 && brain_val.listB.ent[0].dist < 300.0f) {
        brain_val.listBNear = 1;
    }
    brain_val.listDFound = 0;
    if (brain_val.listD.num != 0) {
        brain_val.listDFound = 1;
    }
    /* a marker at each hide point, coloured by the others entry's flags;
       only its drawing is compiled out (see girlDispWire), so the loop stays
       and counts down empty */
    for (k = 0; k < brain_val.hide.num; k++) {
        int c = brain_val.others.ent[k].flags & 2 ? 'B' : 'W';

        if (brain_val.others.ent[k].flags & 4) {
            c = 'Y';
        }
        if (brain_val.others.ent[k].flags & 8) {
            c = 'R';
        }
        girlDispHidePoint(brain_val.hide.ent[k].pos, c, "III");
    }
    seen = 0;
    for (i = 0; i < brain_val.hide.num; i++) {
        if (ACTGameView_Check(girlGObj, brain_val.hide.ent[i].obj) != 0) {
            seen = 1;
            break;
        }
    }
    if (seen != 0) {
        brain_val.unseenFrames = 0;
    } else {
        brain_val.unseenFrames++;
    }
}

/* The group names, defined here after the list builder. */
static char *groupRelationName[4] = {"FALSE", "OTHERGROUP", "SAMEGROUP",
                                     "DIRECT"}; /* derived name */

/* A static inline (no out-of-line copy): true when an entry of
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
    float *t = brain_val.runawayFrom;

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

INCLUDE_ASM(ChangeRunMode_135_girl_act);

INCLUDE_ASM(func_001640B0);

inline void subGirlBrain_Idle(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_ACT(g)->stick.mag = 0;
    _ACTWait(0);
}

inline void subGirlBrain_Becarry(GObj *volatile self)
{
    char *g = (char *)self;
    GOBJ_ACT(g)->stick.mag = 0;
    _ACTWait(0);
}

inline void subGirlBrain_Busy(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    GirlBrainWork *w = &brain_val;
    int i = 0;

    sub->stick.mag = 0;
    while (1) {
        if (w->others.num) {
            _ACTCharStatus_Set((void *)self, 0, -1.0f, (int)w->others.ent[0].obj);
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1] < i &&
             ACTGameView_Check(self, boyGObj)) ||
            (60 - systemStatus[0] * 10) / systemStatus[1] * 2 < i) {
            w->warn = 1;
        }
        i++;
        _ACTWait(1);
    }
}

INCLUDE_ASM(subGirlBrain_Pulledup);

INCLUDE_ASM(subGirlBrain_Attract);

static void _girlBrainHide_MakeHidePoint(float *p, float dist)
{
    float v[4];
    ClipWork work;
    int i;
    float total;
    float w;

    if (brain_val.hide.num == 0) {
        return;
    }
    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;
    total = p[0];
    for (i = 0; i < brain_val.hide.num; i++) {
        sceVu0SubVector(v, brain_val.boyPos, brain_val.hide.ent[i].pos);
        v[1] = 0.0f;
        sceVu0Normalize(v, v);
        w = brain_val.hide.ent[i].dist;
        if (w < 1.0f) {
            w = 1.0f;
        }
        w = 1.0f / w;
        total += w;
        sceVu0ScaleVector(v, v, w);
        sceVu0AddVector(p, p, v);
    }
    if (total != 0.0f) {
        sceVu0ScaleVector(p, p, dist / total);
    } else {
        debug_assert("src/girl_brain_main.c.inc", 1732);
        __assert("src/girl_brain_main.c.inc", 1732, "0");
    }
    sceVu0Normalize(p, p);
    sceVu0ScaleVector(p, p, dist);
    sceVu0AddVector(p, brain_val.boyPos, p);
    p[1] = brain_val.boyRoot[1];
    work.radius = 50.0f;
    sceVu0CopyVector(work.pt[0], brain_val.boyRoot);
    sceVu0CopyVector(work.pt[1], p);
    ClipWall(&work);
    work.pt[0][0] = work.pt[2][0];
    work.pt[0][2] = work.pt[2][2];
    work.pt[1][0] = work.pt[2][0];
    work.pt[1][2] = work.pt[2][2];
    work.pt[0][1] = work.pt[2][1] - 200.0f;
    work.pt[1][1] = work.pt[2][1] + 200.0f;
    ClipFloor(&work);
    p[0] = work.pt[2][0];
    p[2] = work.pt[2][2];
    p[1] = work.pt[2][1] - 10.0f;
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
void subGirlBrainMain(GObj *volatile self);

/* a file-scope static helper (the PAL build inlines it in
 * subGirlBrain_Pulledup) */
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

#include "girl_brain_attract.c.inc"

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
                ACTSendMailCorrect(girl, 212);
            } else {
                ACTSendMailCorrect(girl, 214);
            }
        } else {
            debug_StdPrintfDummy("turnR mail\n");
            if (sendMail) {
                ACTSendMailCorrect(girl, 211);
            } else {
                ACTSendMailCorrect(girl, 213);
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
        if (girlBrainHideCheckIntercept(brain_val.girlPos, cand, (char *)brain_val.hide.ent,
                                        brain_val.hide.num)) {
            brain_val.warn = 1;
        }
        if (_DistxzSqGV(hp, brain_val.girlPos) < 10000.0f) {
            g = self;
            GOBJ_ACT(girlGObj)->stick.mag = 0;
            _ACTCharStatus_Set(g, 5, -1.0f, 0);
            if (_DistxzSqGV(hp, brain_val.girlPos) < 6400.0f) {
                float dir[4];

                _OrientXZGV(dir, brain_val.boyPos, brain_val.girlPos);
                girlBrainHide_GoalTurn(dir, 1);
            }
        } else {
            float dir[4];

            _OrientXZGV(dir, cand, brain_val.girlPos);
            g = self;
            girlBrainSetMoveDir(dir, 1.0f);
            _ACTCharStatus_Set(g, 4, -1.0f, 0);
        }
        _ACTWait(1);
    }
}

inline void subGirlBrain_Hesitate(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    int i = 1;

    for (;;) {
        s->stick.mag = 0.0f;
        if (i % ((60 - systemStatus[0] * 10) / systemStatus[1] / 2) == 0) {
            brain_val.warn = 1;
        }
        i++;
        _ACTWait(1);
    }
}

INCLUDE_ASM(CorrectList_208_girl_act);

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

INCLUDE_ASM(func_001679B8);

/* `inline`: the four Danger_* GetSafePosition bodies below expand it and its
   out-of-line copy closes the TU's deferred run. */
inline int ACTCheckCollis_SAFE(float height, float *p0, float *p1, void *actor, float *posout,
                               int radius)
{
    ClipWork work;
    float tmp[4];
    int flag;
    int rv;

    rv = 1;
    flag = actor ? GOBJ_SUB(actor)->disp : 0;

    work.radius = (float)radius;
    work.pt[0][0] = p0[0];
    work.pt[0][1] = p0[1];
    work.pt[0][2] = p0[2];
    work.pt[1][0] = p1[0];
    work.pt[1][2] = p1[2];
    work.pt[1][1] = p0[1];

    tmp[0] = p1[0];
    tmp[1] = p0[1];
    tmp[2] = p1[2];

    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 0;
    }
    ClipWall(&work);
    if (work.wall.elem == 0) {
        ClipWallField(&work);
        if (work.wall.elem == 0)
            goto no_wall;
    }
    tmp[0] = work.pt[2][0];
    tmp[1] = work.pt[2][1];
    tmp[2] = work.pt[2][2];
no_wall:
    work.pt[0][0] = tmp[0];
    work.pt[0][1] = tmp[1];
    work.pt[0][2] = tmp[2];
    work.pt[1][0] = tmp[0];
    work.pt[1][2] = tmp[2];
    work.pt[1][1] = tmp[1] + height;
    ClipFloor(&work);
    if (work.floor.elem == 0) {
        rv = 0;
    } else {
        work.pt[2][1] -= 10.0f;
    }
    if (posout != 0) {
        posout[0] = work.pt[2][0];
        posout[1] = work.pt[2][1];
        posout[2] = work.pt[2][2];
    }
    if (flag != 0) {
        GOBJ_SUB(actor)->disp = 1;
    }
    return rv;
}

static void Danger_Bomb(GObj *self);
static void Danger_Gondola(GObj *self);
static void Danger_Box(GObj *self);

inline void subGirlBrain_DangerEnv(GObj *volatile self)
{
    switch (dangerEnv.kind) {
    case 1:
        Danger_Bomb((void *)self);
        break;
    case 2:
        Danger_Gondola((void *)self);
        break;
    case 3:
        Danger_Box((void *)self);
        break;
    }
    _ACTWait(0);
}

INCLUDE_ASM(Danger_Bomb);

INCLUDE_ASM(func_00167EE0);

INCLUDE_ASM(Danger_Gondola);

INCLUDE_ASM(func_00168480);

/* the escape angles Danger_Box's safe-position search tries: two words in .data in this build */
INCLUDE_ASM(dangerEscapeAngle);

INCLUDE_ASM(Danger_Box);

/* WayTest's two flags: the demo's .sdata has them after subGirlBrain_Escape's
   string and before func_00168C30's (0x679EE3, 0x679EE4), so they stand here. */
static unsigned char wayTestBegin = 1; /* derived name */

static unsigned char wayTestMoving = 0; /* derived name */

INCLUDE_ASM(func_00168C30);

INCLUDE_ASM_LIT(func_00168C30);

/* The attract-state names, defined after func_00168C30 (WayTest): the demo's
   .rodata and .sdata hold their strings after that function's constants. */
static char *wayTestStateName[9] = {
    "IDLE",    "SEARCHWAY", "LOSTTWAY", "APPROACH", "GOAL",
    "ATTRACT", "LOOKONLY",  "ATTRLOOK", "FINISH"}; /* derived name */

INCLUDE_ASM(func_00168EA8);

INCLUDE_ASM_LIT(func_00168EA8);

INCLUDE_ASM(func_00169630);

INCLUDE_ASM(HandMgr_GetDistHand_289_girl_act);

INCLUDE_ASM(HandMgr_Update_297_girl_act);

INCLUDE_ASM(HandMgr_Judge_301_girl_act);

INCLUDE_ASM(HandMgr_Print_305_girl_act);

INCLUDE_ASM(func_0016A458);

INCLUDE_ASM(func_0016A638);

/* girl_act.o's .data global after the attract-state names: the brain's work
   record, all zero, explicitly initialised so that it stays in .data. */
GirlBrainWork brain_val = {0};

/* girl_act.o's .sdata globals (declared in girl_act.h) */
int hyde_test = 0;

int padtimer_stand = 0;

int padtimer_walk = 0;

int padtimer_run = 0;

INCLUDE_ASM_LIT(func_00169630);

/* the motion-def row of an actor's current motion (boyact.c's CHAINROW) */
#define MOTDIRROW(self) (GOBJ_SUB(self)->ctrl.motion + motionKind) /* derived name */

/* The girl's control thread.  A block of compiled-out debug code sits in
   it; the strings it printed ("src/girl_act.c", "NOTARGET",
   "[%s] %4d %4d %4d", "delete wg 2\n") stay in .rodata between this
   function's "girl no!!\n" and its jump table. */
void subGirlControl(GObj *volatile self);
extern int fptodp(float v);
void subGirlCollision(GObj *volatile self);

/* this TU's uses of GetHeightOfFieldPlaneDifference do not fit the
   prototype in motionManager2.h */

inline int NotNeedBackHand(void)
{
    GObj *g = girlGObj;
    Act *w = GOBJ_ACT(g);

    if ((((int)(w->flags18.ll >> 35)) & 1) == 0) {
        return 1;
    }
    if (w->actMode == 68 && handmgr.near90 != 0 && handmgr.still == 0) {
        return 1;
    }
    return 0;
}

inline void afterGirlHand(unsigned int self)
{
    volatile unsigned int local = self;
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy("after func\n");
    iosPadActStop(7);
}

/* the hand manager's record, all zero and explicitly initialised so that it
   stays in .data */
GirlStand handmgr = {0};

INCLUDE_ASM_LIT(HandMgr_Print_305_girl_act);

INCLUDE_ASM_LIT(func_0016A638);

INCLUDE_ASM(actGirlHand);

void actGirlPulledReady(GObj *volatile self)
{
    float boy[4];
    float dir[4];
    float pos[4];
    float dst[4];
    float d;
    float v;

    GetRootPosition(pos, (void *)self);
    PAIR_GetPosition_BOY(boy, dir);
    sceVu0ScaleVector(dst, dir, 30.0f);
    sceVu0AddVector(dst, boy, dst);
    dst[1] = test_CURRENTROOT((void *)self)[1];
    sceVu0ScaleVector(dir, dir, -1.0f);
    d = _DistxzGV(pos, dst) * 0.5f;
    v = (d < 1.0f) ? 1.0f : ((d > 20.0f) ? 20.0f : d);
    StartCorrectPosition((void *)self, dst, dir, 1, v);
    while (IsCorrectPosition((void *)self)) {
        ContinueCorrectPosition((void *)self);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)self, 74);
        }
        _ACTWait(1);
    }
}

inline void afterGirlPulledGo(void *self)
{
    void *volatile q = self;
    int *p = (int *)GOBJ_SUB(q);
    *(int *)((char *)p + 0x620) = 0;
}

void actGirlPulledGo(GObj *volatile self)
{
    float q[4];
    Act *s;
    int m;

    s = GOBJ_ACT(self);
    s->after = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    *(MotOriReq *)&GOBJ_SUB(self)->root.wall = s->env.motOriReq;
    *(int *)(*(char **)((char *)self + 0x15C) + 0x620) = 1;
    *(char **)((char *)s + 0x18) = (char *)afterGirlPulledGo;
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(girlGObj, boyGObj, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)self, 76);
            ACTSendMailCorrect((void *)self, 77);
        } else {
            m = GOBJ_ACT(((int *)boyGObj))->actMode;
            if (m == 2 || m == 3) {
                ACTSendMailCorrect((void *)self, 78);
                ACTSendMailCorrect((void *)self, 79);
            }
            ACTSendMailCorrect((void *)self, 80);
        }
        _ACTWait(1);
    }
}

void actGirlDitch3mReady(GObj *volatile self)
{
    float gpos[4];
    float now[4];
    float bpos[4];

    GetRootPosition(now, (void *)self);
    PAIR_GetPosition_BOY_DITCH(bpos, gpos);
    bpos[1] = test_CURRENTROOT((void *)self)[1];
    sceVu0ScaleVector(gpos, gpos, -1.0f);
    StartCorrectPosition((void *)self, bpos, gpos, 1, 20.0f);
    while (IsCorrectPosition((void *)self)) {
        debug_NMarker(bpos, 0, 0, 0xFF, 100.0f);
        ContinueCorrectPosition((void *)self);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)self, 348);
        }
        _ACTWait(1);
    }
}

inline void actGirlDitch3mExec(GObj *volatile self)
{
    ACTGame_ConnectHand();
    debug_StdPrintfDummy("ditch3m hand connect\n");
    for (;;) {
        ACTSendMailCorrect((void *)self, 353);
        _ACTWait(1);
    }
}

inline void actGirlHangG3M(GObj *volatile self)
{
    for (;;) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)self, 354);
        }
        _ACTWait(1);
    }
}

inline void actGirlStand(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlStand\n");
    sub->actMode = 1;
    _ACTWait(0);
}

inline void actGirlWalk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlWalk\n");
    sub->actMode = 2;
    _ACTWait(0);
}

inline void actGirlRun(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlRun\n");
    sub->actMode = 3;
    _ACTWait(0);
}

inline void actGirlJump(GObj *volatile self)
{
    char *g = (char *)self;
    Act *s = GOBJ_ACT(g);
    debug_StdPrintfDummy("enter actGirlJump\n");
    s->actMode = 4;
    _ACTWait(0);
}

inline void actGirlBecall(GObj *volatile self)
{
    int i;

    for (i = 0; i < (60 - systemStatus[0] * 10) / systemStatus[1] * 2; i++) {
        _ACTLookTarget_Set((void *)self, boyGObj, 0, 5, 1);
        _ACTWait(1);
    }
    ACTSendMailCorrect((void *)self, 228);
    _ACTWait(0);
}

inline void actGirlAttractAction(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect((void *)self, 305);
        _ACTWait(1);
    }
}

inline void actGirlBehanged(GObj *volatile self)
{
    float q[4];

    for (;;) {
        memset(q, 0, 0x10);
        q[3] = 1.0f;
        RotQuaternionY(q, 0);
        SetMotionNodeFixModeParameter(girlGObj, boyGObj, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
        _ACTWait(1);
    }
}

inline void actGirlAttack(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actGirlAttack\n");
    sub->actMode = 15;
    _ACTWait(0);
}

inline void actGirlHang(GObj *volatile self)
{
    Act *s = GOBJ_ACT(self);
    /* rope-hang detected from the actor's interrupt words */
    int hang = 0;

    if (*(int *)((char *)s + 0x448) == 86) {
        hang = *(int *)((char *)s + 0x444) == 4;
    }
    for (;;) {
        if (hang) {
            ACTSendMailCorrect((void *)self, 177);
        }
        _ACTWait(1);
    }
}

inline void actGirlBHang(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect((void *)self, 301);
        _ACTWait(1);
    }
}

void actGirlReadyMove(GObj *volatile self)
{
    float dst[4];
    float dir[4];

    dst[0] = GOBJ_ACT(self)->enemy->readyPosX;
    dst[1] = GOBJ_ACT(self)->enemy->readyPosY;
    dst[2] = GOBJ_ACT(self)->enemy->readyPosZ;
    dir[0] = GOBJ_ACT(self)->enemy->readyDirX;
    dir[1] = GOBJ_ACT(self)->enemy->readyDirY;
    dir[2] = GOBJ_ACT(self)->enemy->readyDirZ;
    dst[1] = test_CURRENTROOT((void *)self)[1];
    StartCorrectPosition((void *)self, dst, dir, 1, 40.0f);
    while (IsCorrectPosition((void *)self)) {
        debug_Arrow(100.0f, test_CURRENTROOT((void *)self), dir, 0xFF, 0, 0xFF);
        ContinueCorrectPosition((void *)self);
        _ACTWait(1);
    }
    while (1) {
        ACTSendMailCorrect((void *)self, 242);
        _ACTWait(1);
    }
}

void actGirlRescueDst(GObj *volatile self)
{
    float dir[4];
    float q[4];
    float pos[4];
    float p1[4];
    float p2[4];
    float dst[4];
    Act *s;
    EnemyBattleWork *w;
    int n;

    s = GOBJ_ACT(self);
    memset(q, 0, 16);
    n = ((60 - systemStatus[0] * 10) / systemStatus[1]) / 3;
    s->after = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    ACTGameCollisionOn((void *)self);
    gflagOff(342);
    pos[0] = test_CURRENTROOT((void *)self)[0];
    pos[1] = test_CURRENTROOT((void *)self)[1];
    pos[2] = test_CURRENTROOT((void *)self)[2];
    pos[1] = GOBJ_ACT(((int *)boyGObj))->enemy->rescueGirlPos[1];
    SetDirectRootPosition((void *)self, pos);
    w = GOBJ_ACT(((int *)boyGObj))->enemy;
    _OrientXZGV(q, w->rescueBoyPos, w->rescueGirlPos);
    sceVu0SubVector(dir, GOBJ_ACT(((int *)boyGObj))->enemy->rescueGirlPos,
                    test_CURRENTROOT((void *)self));
    sceVu0ScaleVector(dir, dir, 1.0f / (float)n);
    SetMotionDirection((void *)self, q);
    while (1) {
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) / 2 < s->modeFrame) {
            GetSkeltonPosition(p1, (boyGObj), 6);
            GetSkeltonPosition(p2, (void *)girlGObj, 22);
            if (!(_DistSqGV(p1, p2) < 400.0f)) {
                iosOmSendMail(boyGObj, 224, isysCurrentGObj);
            }
            ACTSendMailCorrect((void *)self, 176);
        }
        if (n > 0) {
            sceVu0AddVector(dst, test_CURRENTROOT((void *)self), dir);
            dst[1] = test_CURRENTROOT((void *)self)[1];
            SetDirectRootPosition((void *)self, dst);
        }
        iosOmSendMail(boyGObj, 309, isysCurrentGObj);
        n--;
        ACTSendMailCorrect((void *)self, 177);
        _ACTWait(1);
    }
}

inline void actGirlSupportGBBegin(GObj *volatile self)
{
    float girl[4];
    float boy[4];
    float dst[4];

    for (;;) {
        girl[0] = test_CURRENTROOT((void *)girlGObj)[0];
        girl[1] = test_CURRENTROOT((void *)girlGObj)[1];
        girl[2] = test_CURRENTROOT((void *)girlGObj)[2];
        boy[0] = test_CURRENTROOT((boyGObj))[0];
        boy[1] = test_CURRENTROOT((boyGObj))[1];
        boy[2] = test_CURRENTROOT((boyGObj))[2];
        boy[1] = girl[1];
        _MoveGV(dst, girl, boy, 20.0f);
        SetDirectRootPosition((void *)self, dst);
        ACTSendMailCorrect((void *)self, 334);
        _ACTWait(1);
    }
}

/* the status-range test inside actGirlSupportGBLoop's loop */
static inline unsigned char isGirlSupportGBStatus(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(((int *)boyGObj))->actMode;

    if (st < 103) {
        if (100 <= st) {
            return 1;
        }
    }
    return 0;
}

inline void actGirlSupportGBLoop(GObj *volatile self)
{
    for (;;) {
        if (!isGirlSupportGBStatus()) {
            ACTSendMailCorrect((void *)self, 336);
        }
        _ACTWait(1);
    }
}

inline void actGirlSupportGBEnd(GObj *volatile self)
{
    for (;;) {
        ACTSendMailCorrect((void *)self, 177);
        _ACTWait(1);
    }
}

inline void afterGirlSupportBGBegin(unsigned int self)
{
    volatile unsigned int local = self;
    ACTGame_DisconnectHand();
}

void actGirlSupportBGBegin(GObj *volatile self)
{
    float v1[4];
    float v2[4];
    float dst[4];
    float q[4];
    Act *s;
    int i;

    i = 0;
    s = GOBJ_ACT(self);
    v1[0] = test_CURRENTROOT((boyGObj))[0];
    v1[1] = test_CURRENTROOT((boyGObj))[1];
    v1[2] = test_CURRENTROOT((boyGObj))[2];
    v2[0] = test_CURRENTROOT((void *)girlGObj)[0];
    v2[1] = test_CURRENTROOT((void *)girlGObj)[1];
    v2[2] = test_CURRENTROOT((void *)girlGObj)[2];
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(girlGObj, boyGObj, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    s->after = (void *)afterGirlSupportBGBegin;
    ACTGame_ConnectHand();
    while (1) {
        if (i++ < 6) {
            _InterGV(dst, v1, v2, (float)i, (float)(5 - i));
        }
        ACTSendMailCorrect((void *)self, 340);
        _ACTWait(1);
    }
}

int girlcalled;

INCLUDE_ASM(actGirlStart);

void GirlAct_BoyAndMeCollisionMail(void *self)
{
    float vec[4];
    float boyPos[4];
    float myPos[4];
    float ang;

    ACTSendMailCorrect(self, 243);

    if (((int *)((int *)boyGObj)[0x59])[0xC] == 1) {
        return;
    }
    GetRootPosition(boyPos, boyGObj);
    GetRootPosition(myPos, self);

    sceVu0SubVector(vec, boyPos, myPos);
    sceVu0Normalize(vec, vec);

    ang = _RotyGV(vec, test_CURRENTORIENT(self));

    if ((ang < 0.0f ? -ang : ang) < 45.0f) {
        ACTSendMailCorrect(self, 244);
        return;
    } else if ((ang < 0.0f ? -ang : ang) > 135.0f) {
        ACTSendMailCorrect(self, 245);
        return;
    } else if (ang > 45.0f) {
        ACTSendMailCorrect(self, 246);
        return;
    } else {
        ACTSendMailCorrect(self, 247);
    }
}

static inline unsigned char isGirlEscortStatus(void) /* derived name */
{
    Act *s = GOBJ_ACT(girlGObj);
    int mode = s->actMode;
    const ActModeRec *attr = &actModeTbl[mode];
    if (attr->escort && brain_val.curMode == 1) {
        return 1;
    }
    return 0;
}

static inline const EscortPoint *searchEscortPoint(int area, int point) /* derived name */
{
    const EscortPoint *p;
    int i;
    for (i = 0; i < 88; i++) {
        p = &autoEscortData[i];
        if (p->area == area && p->point == point) {
            return p;
        }
    }
    return 0;
}

int IsGirlStatusEscortEnable(int area, int point)
{
    float v[4];
    const EscortPoint *p;
    float d;

    if (((int *)boyGObj) != 0 && (void *)girlGObj != 0 && isGirlEscortStatus()) {
        p = searchEscortPoint(area, point);
        if (p != 0) {
            v[0] = -p->pos[0];
            v[1] = -p->pos[1];
            v[2] = -p->pos[2];
            d = _DistGV(v, test_CURRENTROOT((void *)girlGObj));
            if (d < p->range) {
                GOBJ_WORK(girlGObj)->escortOffset = p->range * p->rate;
                return 1;
            }
        } else {
            if (_DistSqGV(test_CURRENTROOT((boyGObj)), test_CURRENTROOT((void *)girlGObj)) <
                _ACTGame_GetParamF(4) * _ACTGame_GetParamF(4)) {
                return 1;
            }
        }
    }
    return 0;
}

inline int isMustCheckCylinder(void *a, void *b)
{
    if ((a == (void *)((int *)boyGObj) && b == (void *)girlGObj) ||
        (a == (void *)girlGObj && b == (void *)((int *)boyGObj))) {
        if (GOBJ_ACT(girlGObj)->actMode == 77) {
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

void DebugDispAutoEscort(void)
{
    Vec4 pos = {{3.40282347e+38f, 0.0f, 0.0f, 1.0f}}; /* FLT_MAX: no girl yet */
    Vec4 v;
    const EscortPoint *p;
    int i;
    int in;

    if (debug_disp_escort_ball == 0) {
        return;
    }
    if ((void *)girlGObj != 0 && isGirlEscortStatus()) {
        pos.f[0] = test_CURRENTROOT((void *)girlGObj)[0];
        pos.f[1] = test_CURRENTROOT((void *)girlGObj)[1];
        pos.f[2] = test_CURRENTROOT((void *)girlGObj)[2];
    }
    for (i = 1; i < 16; i++) {
        p = searchEscortPoint(stage_no, i);
        if (p != 0) {
            v.f[0] = -p->pos[0];
            v.f[1] = -p->pos[1];
            v.f[2] = -p->pos[2];
            in = _DistSqGV(&v, &pos) < p->range * p->range;
            dispEscortSphere(&v, p->range, in);
        }
    }
}

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

static inline void afterGirlHintPoint(GObj *volatile self)
{
    RequestChangeHandMode(self, 1, 4, 0, 0, 0, 0);
}
