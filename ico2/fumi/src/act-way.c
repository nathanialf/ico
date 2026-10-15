#include "main.h"
#include "camera-editor.h"
#include "motionManager2.h"
#include "act-game.h"
#include "act-way.h"
#include "act.h"
#include "gobj_process.h"
#include "way_sys.h"
#include "waySystemManager.h"
#include <libvu0.h>
#include "debug.h"
#include "girl_act.h"
#include "box.h"
#include "commonact.h"
#include "gv.h"
#include "motionOrientManager.h"
#include "include_asm.h"

/* the two-word playback-rate pair the wait counters are scaled by */

/* the three detour angles DetourCheck sweeps, in degrees, zero-terminated */
static int detourAngle[4] = {75, -75, 0, 0}; /* derived name */

static void DetourCheck(GObj *self, float *out)
{
    float orient[4];
    float cur[4];
    float o2[4];
    float tmp[4];
    float dir[4];
    Act *act = GOBJ_ACT(self);
    int i;
    int wait = 0;
    int ok = 0;

    if (debug_girl_detour_flag == 0) {
        return;
    }
    GetSkeltonOrient(orient, self, 0x2C);
    if (*(int *)((char *)GOBJ_ACT(self)->work + 0x810) != 0) {
        out[0] = *(float *)((char *)GOBJ_ACT(self)->work + 0x820);
        out[1] = *(float *)((char *)GOBJ_ACT(self)->work + 0x824);
        out[2] = *(float *)((char *)GOBJ_ACT(self)->work + 0x828);
        *(int *)((char *)GOBJ_ACT(self)->work + 0x810) -= 1;
        return;
    }
    /* two identical case bodies */
    switch (act->actMode) {
    case 2:
        ok = 1;
        wait = (60 - systemStatus[0] * 10) / systemStatus[1] * 40 / 60;
        break;
    case 3:
        ok = 1;
        wait = (60 - systemStatus[0] * 10) / systemStatus[1] * 40 / 60;
        break;
    }
    /* the four tests are one statement */
    if (ok == 0 || act->stick.mag == 0.0f || (GOBJ_SUB(self)->ctrl.flags & 2) == 0 ||
        ((*(unsigned long long *)((char *)GOBJ_ACT(self)->work + 0x408) >> 33) & 1) == 0) {
        return;
    }
    cur[0] = test_CURRENTROOT(self)[0];
    cur[1] = test_CURRENTROOT(self)[1];
    cur[2] = test_CURRENTROOT(self)[2];
    GetSkeltonOrient(o2, self, 0x2C);
    for (i = 0; detourAngle[i] != 0; i++) {
        dir[0] = o2[0];
        dir[1] = o2[1];
        dir[2] = o2[2];
        _ApplyRyGV(dir, (float)detourAngle[i] * 3.1415927f / 180.0f);
        sceVu0ScaleVector(tmp, dir, 100.0f);
        sceVu0AddVector(tmp, cur, tmp);
        if (ACTCheckCollis_WAY(10.0f, cur, tmp, 0, 0) == 0) {
            *(float *)((char *)GOBJ_ACT(self)->work + 0x820) = dir[0];
            *(float *)((char *)GOBJ_ACT(self)->work + 0x824) = dir[1];
            *(float *)((char *)GOBJ_ACT(self)->work + 0x828) = dir[2];
            *(int *)((char *)GOBJ_ACT(self)->work + 0x810) = wait;
            return;
        }
    }
}

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

INCLUDE_ASM(checkPositionIllegal);

/* three helpers inlined into ACTWayMove_BeginDetail and
   ACTWayMove_NextDetail */

/* the pull-up floor box's saved enable word and the box itself, held across
   the way search */
static int pullupBoxEnable; /* derived name */

static void *pullupBox; /* derived name */

static inline void SuspendGirlPullupFloorBox(void) /* derived name */
{
    pullupBox = FindGirlPullupFloorBoxGObj();
    pullupBoxEnable = pullupBox != 0 ? GOBJ_SUB(pullupBox)->disp : 0;
    if (pullupBoxEnable != 0) {
        GOBJ_SUB(pullupBox)->disp = 0;
    }
}

static inline void ResumeGirlPullupFloorBox(void) /* derived name */
{
    if (pullupBoxEnable != 0) {
        GOBJ_SUB(pullupBox)->disp = 1;
    }
}

static inline WayPoint *RequestWayBegin(char *self, float *goal, float *from, WVTObj *way,
                                        unsigned char sub) /* derived name */
{
    ActWork *req;
    WayRequest *ws;
    WayPoint *w;

    if (sub) {
        req = GOBJ_WORK(self);
        ws = &req->wayReq;
        if (ws->proc != 0) {
            isysGObjProcRemove(ws->proc);
            ws->proc = 0;
        }
        ws->from[0] = from[0];
        ws->from[1] = from[1];
        ws->from[2] = from[2];
        req->wayReq.way = *way;
        ws->goal[0] = goal[0];
        ws->goal[1] = goal[1];
        ws->goal[2] = goal[2];
        ws->proc = RequestGetWayBegin(ws);
        while (ws->done == 0) {
            _ACTWait(1);
        }
        w = ws->result;
        *way = ws->way;
        return w;
    }
    if (self == (char *)girlGObj) {
        SuspendGirlPullupFloorBox();
    }
    w = GetWay_begin(from, way, goal);
    if (self == (char *)girlGObj) {
        ResumeGirlPullupFloorBox();
    }
    return w;
}

INCLUDE_ASM(ACTWayMove_BeginDetail);

/* the 0x20-byte way-step record the actor keeps at act + 0x3E0: the step
   direction, the 64-bit way state word and the two distances to the goal */
typedef struct {     /* field names derived */
    float dir[4];    /* 0x00 */
    long long state; /* 0x10 */
    float dist;      /* 0x18 */
    float dy;        /* 0x1C */
} WayStep;           /* derived name */

/* the two templates act-way.o keeps in .data: the cleared way-walker record
   (its waypoint id starts at -1) and the cleared way-step record (its two
   distances start at the largest float) */
static WVTObj wayWorkClear = {{0}, {0}, {0}, 0,   0,   0, 0,
                              0,   {0}, 0,   {0}, {0}, 0, -1}; /* derived name */

static WayStep wayStepClear = {
    {0.0f, 0.0f, 0.0f, 0.0f}, 0, 3.4028235e38f, 3.4028235e38f}; /* derived name */

/* this TU's uses of the gv distance helpers do not fit the void returns gv.h
   carries, and its GetRootProjectionPosOfGObj / IsThisBoxTruck call forms do
   not fit motionManager2.h and box.h */

INCLUDE_ASM(ACTWayMove_NextDetail);

INCLUDE_ASM(ACTWayExec_Position);

INCLUDE_ASM(ACTWay_IsMustWalkFromWay);

INCLUDE_ASM(ACTWay_SetBeginPositionIllegal);
