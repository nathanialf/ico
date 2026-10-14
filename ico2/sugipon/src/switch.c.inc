#include "include_asm.h"

/* switch.c: the floor and wall levers and the switches; box.c includes this
   file. */

void switchOnSE(GObj *self);

INCLUDE_ASM(switchOnSE);

INCLUDE_ASM(switchReleaseSE);

INCLUDE_ASM(GetFloorLeverGlobalHoldPoint);

/* the zeroed template both lever inits copy into a new geometry block */
static LeverGeoWork leverGeoInit = {0}; /* derived name */

INCLUDE_ASM_LIT(InitFloorLeverGeo);

INCLUDE_ASM(FloorLeverTriStateGeo);

/* the two frame-rate divisors, the pair box.c's own fall code reads */

/* The floor lever's per-frame function.  The frame divisor (60 -
   systemStatus[0] * 10) / systemStatus[1] is written twice, once for the
   limit test and once for the equality test; the parentize probe is the
   inlined initParentize above. */
INCLUDE_ASM(FloorLeverGeo);

INCLUDE_ASM(FloorLeverDL);

INCLUDE_ASM(GetWallLeverGlobalHoldPoint);

/* the wall lever's counterpart of FloorLeverGeo: the same parentize probe
   and the same frame divisor written twice, no trigger callback, and a mail
   sent every frame that reports the lever's rest state (the inlined
   IsWallLeverStatus above) */
INCLUDE_ASM(WallLeverGeo);

INCLUDE_ASM(WallLeverDL);

/* the poll loop the four functions below share */
static inline int checkReadySwitchKind(int kind) /* derived name */
{
    GObj *o;

    for (o = isysGObjSearchFromObjKindID_begin(kind); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        LeverGeoWork *p = GOBJ_SUB(o)->work;

        if (p->linked == 0) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM(CheckReadyAllSwitches);
