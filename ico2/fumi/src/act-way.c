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

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];
static int checkPositionIllegal(GObj *self, float *pos);

/* PAL's way-search helpers (the girl's pull-up floor box suspended around
   the search, kept in two .sbss words, and the request they served) have no
   copy here: this build's .sbss has no such words, and no C function of the
   TU calls the request helper. */

INCLUDE_ASM(func_001EFA40);

INCLUDE_ASM(ACTWayMove_BeginDetail);

/* the 0x20-byte way-step record the actor keeps at act + 0x3E0: the step
   direction, the 64-bit way state word and the two distances to the goal */
typedef struct {     /* field names derived */
    float dir[4];    /* 0x00 */
    long long state; /* 0x10 */
    float dist;      /* 0x18 */
    float dy;        /* 0x1C */
} WayStep;           /* derived name */

/* the one template act-way.o keeps in .data in this build: the cleared
   way-step record (its two distances start at the largest float) */
static WayStep wayStepClear = {
    {0.0f, 0.0f, 0.0f, 0.0f}, 0, 3.4028235e38f, 3.4028235e38f}; /* derived name */

/* this TU's uses of the gv distance helpers do not fit the void returns gv.h
   carries, and its GetRootProjectionPosOfGObj / IsThisBoxTruck call forms do
   not fit motionManager2.h and box.h */

int ACTWayMove_NextDetail(GObj *self, float *node, float *goal, unsigned char d, unsigned char e);

INCLUDE_ASM(ACTWayExec_Position);

INCLUDE_ASM(WayMove_CheckCollis);
