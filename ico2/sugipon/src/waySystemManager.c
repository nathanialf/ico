#include "GobjProc.h"
#include "way_sys.h"

/* the manager object */
static GObj *waySystemManagerGObj = 0; /* derived name */

/* void * (void *, int) here, void (int, int) in act.h */
extern void *actCreateSubThreadGOppArg(void *entry, int arg);
/* as in act.h, which this file does not include */
extern void _ACTWait(int frames);

#include "waySystemManager.h"
#include "include_asm.h"

static void actWaySystemCore(volatile unsigned int self);
static void thStart(void);

GObj *CreateWaySystemManagerGObj(void)
{
    GObj *v = CreateGObjByFuncSet(0, 0, 0, 0, thStart, 0, 0);
    waySystemManagerGObj = v;
    return v;
}

INCLUDE_ASM(RequestGetWayBegin);

INCLUDE_ASM(actWaySystemCore);

INCLUDE_ASM(thStart);

INCLUDE_ASM(func_001F2388);

INCLUDE_ASM(func_001F2390);
