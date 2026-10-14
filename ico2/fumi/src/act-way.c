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

INCLUDE_ASM(DetourCheck);

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

INCLUDE_ASM(checkPositionIllegal);

inline unsigned char WayMove_CheckCollis(float *p0, float *p1, void *actor, void *posout);

/* a helper inlined into ACTWayMove_BeginDetail and ACTWayMove_NextDetail */

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
    w = GetWay_begin(from, way, goal);
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
