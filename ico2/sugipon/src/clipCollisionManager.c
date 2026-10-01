#include "clipCollisionManager.h"
#include "GobjProc.h"
#include "debug.h"
#include "matrixDrive.h"
#include "Matrix.h"
#include "main.h"

/* the manager object CreateClipCollisionManagerGObj made */
static int clipCollisionManagerGObj = 0; /* derived name */

/* void * (void *, int) here, void (int, int) in act.h */
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
/* as in act.h, which this file does not include */
extern void _ACTWait(int a0);

typedef struct ClipColWork { /* field names derived */
    int result;              /* 0x00 */
    char _p04[12];
    float p0[4]; /* 0x10 */
    float p1[4]; /* 0x20 */
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
void actClipCollisionCore(volatile unsigned int self)
{
    ClipColWork *w = *(ClipColWork **)(self + 0x20);
    float a[4];
    float b[4];
    float step;
    int n;
    int i;
    int clung;

    n = (int)(GetPointDistance(w->p0, w->p1) * 0.01f) + 1;
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
        CopyVector(a, w->p0);
        CopyVector(b, w->p1);
        _InterVectorXYZ(w->p0, b, a, (float)i * step);
        _InterVectorXYZ(w->p1, b, a, (float)(i + 1) * step);
        if (clung != 0) {
            GOBJ_SUB(w->gobj)->disp = 0;
        }
        w->func(w->p0);
        if (clung != 0) {
            GOBJ_SUB(w->gobj)->disp = 1;
        }
        CopyVector(w->p0, a);
        CopyVector(w->p1, b);
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
    void *t = actCreateSubThreadGOppArg(actClipCollisionCore, 0x15);
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

int CreateClipCollisionManagerGObj(void)
{
    int v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    clipCollisionManagerGObj = v;
    return v;
}
