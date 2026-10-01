#include "GobjProc.h"
#include "way_sys.h"

/* the manager object */
static GObj *waySystemManagerGObj = 0; /* derived name */

/* void * (void *, int) here, void (int, int) in act.h */
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
/* as in act.h, which this file does not include */
extern void _ACTWait(int frames);

#include "waySystemManager.h"

static void actWaySystemCore(volatile unsigned int self);
static void thStart(void);

static inline void actWaySystemCore(volatile unsigned int self)
{
    int *s = (int *)((int *)self)[0x20 / 4];
    int v;
    v = _FUNC_GetWay_begin(((char *)s + 0x10), ((char *)s + 0x20), (int)((char *)s + 0xA0), 1);
    s[0x4 / 4] = v;
    s[0] = 1;
    s[0xB0 / 4] = 0;
}

inline void *RequestGetWayBegin(int *req)
{
    void *t = actCreateSubThreadGOppArg(actWaySystemCore, 21);
    *(int **)((char *)t + 0x20) = req;
    req[0] = 0;
    return t;
}

static inline void thStart(void)
{
    for (;;) {
        _ACTWait(1);
    }
}

GObj *CreateWaySystemManagerGObj(void)
{
    GObj *v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    waySystemManagerGObj = v;
    return v;
}
