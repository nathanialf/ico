#include "common.h"
#include "ico/types.h"

/* clipCollisionManager.h prototype: the inline tail's emission order */
void *RequestClipCollision(int *a0);
extern int D_0063B754;
extern void actClipCollisionCore(volatile unsigned int self);
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
extern void _ACTWait(int a0);
extern int CreateGObjByFuncSet();

typedef struct ClipColWork {
    int result; /* 0x00 */
    char _p04[0xC];
    float p0[4]; /* 0x10 */
    float p1[4]; /* 0x20 */
    char _p30[0x68];
    /* the two clip results the callback fills in: _clipF stores the floor
       record pointer at +0xA4 and _Clip dereferences +0x98 as the wall
       record (lw 0x4C/0x48 off it), so both are pointers, not flags. */
    void *hitWall; /* 0x98 */
    char _p9C[0x8];
    void *hitFloor; /* 0xA4 */
    char _pA8[0x28];
    char *gobj;           /* 0xD0 */
    void (*func)(void *); /* 0xD4 */
} ClipColWork;

extern int D_0028F4C0[];
extern char D_0061F1D0[];
extern void debug_StdPrintfDummy();
extern float GetPointDistance(void *a0, void *a1);
extern void CopyVector(void *dst, void *src);
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);

/* `self` is volatile because the actor entry's argument has an addressable
   home on the stack (ROM: `sw $a0, 0($sp)` then `lw $v0, 0($sp)`) — the thread
   this runs on is resumed by _ACTWait below, so the entry argument is re-read
   from its home rather than kept in a register across the yield. */
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
    if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < n) {
        debug_StdPrintfDummy(D_0061F1D0);
        w->result = 1;
        return;
    }
    while (1) {
        clung = 0;
        if (w->gobj != 0) {
            clung = *(int *)(*(char **)(w->gobj + 0x15C) + 0x74);
        }
        CopyVector(a, w->p0);
        CopyVector(b, w->p1);
        _InterVectorXYZ(w->p0, b, a, (float)i * step);
        _InterVectorXYZ(w->p1, b, a, (float)(i + 1) * step);
        if (clung != 0) {
            *(int *)(*(char **)(w->gobj + 0x15C) + 0x74) = 0;
        }
        w->func(w->p0);
        if (clung != 0) {
            *(int *)(*(char **)(w->gobj + 0x15C) + 0x74) = 1;
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

/* listing line 72: the manager thread's idle body, handed to
   CreateGObjByFuncSet; a static inline forced out of line by its address */
static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}

int CreateClipCollisionManagerGObj(void)
{
    int v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    D_0063B754 = v;
    return v;
}
