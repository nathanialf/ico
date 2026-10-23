#include "include_asm.h"

/* switch.c: the floor and wall levers and the switches; box.c includes this
   file. */

void switchOnSE(GObj *self);

INCLUDE_ASM(switchOnSE);

INCLUDE_ASM(switchReleaseSE);

void GetFloorLeverGlobalHoldPoint(void *dst, GObj *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;
    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix()[3]);
}

/* the zeroed template both lever inits copy into a new geometry block */
static LeverGeoWork leverGeoInit = {0}; /* derived name */

INCLUDE_ASM_LIT(InitFloorLeverGeo);

void FloorLeverTriStateGeo(GObj *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;

    if (p->state != -1 && p->state != 1) {
        if (p->trigger != 0) {
            p->trigger(GOBJ_SUB(lev)->parent.obj, 0);
        }
    } else {
        if (p->trigger != 0) {
            p->trigger(GOBJ_SUB(lev)->parent.obj, p->state);
        }
    }
    UpdateRootMatrix(lev);
}

/* the two frame-rate divisors, the pair box.c's own fall code reads */

/* The floor lever's per-frame function.  The frame divisor (60 -
   systemStatus[0] * 10) / systemStatus[1] is written twice, once for the
   limit test and once for the equality test; the parentize probe is the
   inlined initParentize above. */
INCLUDE_ASM(FloorLeverGeo);

void FloorLeverDL(GObj *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;

    p2o_DispVU1(lev);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_RotMatrixX(p->shake);
    CopyMatrix((void *)p->handle->nodeMtx, MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(p->handle);
    MatrixDrive_PopMatrix();
}

void GetWallLeverGlobalHoldPoint(void *dst, GObj *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;

    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_TransMatrix(-50.0f, 0.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix()[3]);
}

/* the wall lever's counterpart of FloorLeverGeo: the same parentize probe
   and the same frame divisor written twice, no trigger callback, and a mail
   sent every frame that reports the lever's rest state (the inlined
   IsWallLeverStatus above) */
INCLUDE_ASM(WallLeverGeo);

void WallLeverDL(GObj *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;
    Sub15C *d;
    p2o_DispVU1(lev);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_RotMatrixX(p->shake);
    d = p->handle;
    CopyMatrix((void *)d->nodeMtx, MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(p->handle);
    MatrixDrive_PopMatrix();
}

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

int CheckReadyAllSwitches(void)
{
    if (checkReadySwitchKind(22) == 0) {
        return 0;
    }
    if (checkReadySwitchKind(23) == 0) {
        return 0;
    }
    if (checkReadySwitchKind(24) == 0) {
        return 0;
    }
    return checkReadySwitchKind(25);
}
