#include "clipCollisionManager.h"
#include "GobjProc.h"
#include "debug.h"
#include "matrixDrive.h"
#include "Matrix.h"
#include "main.h"
#include "act.h"

/* the manager object CreateClipCollisionManagerGObj made */
static GObj *clipCollisionManagerGObj = 0; /* derived name */

typedef struct ClipColWork { /* field names derived */
    int result;              /* 0x00 */
    char _p04[12];
    float from[4]; /* 0x10, the segment start */
    float to[4];   /* 0x20, the segment end */
    char _p30[104];
    /* the two clip results the callback fills in: _clipF stores the floor
       record at +0xA4 and _Clip reads the wall record at +0x98 */
    void *hitWall; /* 0x98 */
    char _p9C[8];
    void *hitFloor; /* 0xA4 */
    char _pA8[40];
    char *gobj;           /* 0xD0 */
    void (*func)(void *); /* 0xD4 */
} ClipColWork;            /* derived name */

/* `self` is volatile: the thread yields in _ACTWait below, and the entry
   argument is read back from its stack home after each resume. */
static void actClipCollisionCore(volatile unsigned int self)
{
    ClipColWork *w = *(ClipColWork **)(self + 0x20);
    float a[4];
    float b[4];
    float step;
    int n;
    int i;
    int clung;

    n = (int)(GetPointDistance(w->from, w->to) * 0.01f) + 1;
    step = 1.0f / (float)n;
    i = 0;
    w->hitFloor = 0;
    w->hitWall = 0;
    if ((60 - systemStatus[0] * 10) / systemStatus[1] * 5 < n) {
        /* an enemy in flight cast a RAY that costs too many frames, so it was
           dropped */
        debug_StdPrintfDummy(
            "飛び中の敵があまりにフレーム数のかかるRAYを飛ばしたので無効にしました.\n");
        w->result = 1;
        return;
    }
    while (1) {
        clung = 0;
        if (w->gobj != 0) {
            clung = GOBJ_SUB(w->gobj)->disp;
        }
        CopyVector(a, w->from);
        CopyVector(b, w->to);
        _InterVectorXYZ(w->from, b, a, (float)i * step);
        _InterVectorXYZ(w->to, b, a, (float)(i + 1) * step);
        if (clung != 0) {
            GOBJ_SUB(w->gobj)->disp = 0;
        }
        w->func(w->from);
        if (clung != 0) {
            GOBJ_SUB(w->gobj)->disp = 1;
        }
        CopyVector(w->from, a);
        CopyVector(w->to, b);
        if (w->hitFloor != 0 || w->hitWall != 0) {
            break;
        }
        i++;
        if (i >= n) {
            break;
        }
        _ACTWait(1);
    }
    w->result = 1;
}

inline void *RequestClipCollision(int *a0)
{
    void *t = actCreateSubThreadGOppArg(actClipCollisionCore, 21);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}

/* the manager thread's idle body, handed to CreateGObjByFuncSet;
   waySystemManager.c has its own thStart */
static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}

GObj *CreateClipCollisionManagerGObj(void)
{
    GObj *v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    clipCollisionManagerGObj = v;
    return v;
}
