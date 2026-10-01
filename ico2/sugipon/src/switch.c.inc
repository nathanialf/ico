/* switch.c: the floor and wall levers and the switches; box.c includes this
   file. */

void switchOnSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x3F);
}

void switchReleaseSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x40);
}

inline void SetSwitchTriggerFunc(GObj *a0, int (*a1)(GObj *, int))
{
    ((LeverGeoWork *)GOBJ_SUB(a0)->work)->trigger = a1;
}

inline int InitSwitchGeo(void)
{
    return 0;
}

inline void SwitchGeo(void) {}

inline void SwitchDL(void) {}

void GetFloorLeverGlobalHoldPoint(void *dst, GObj *a1)
{
    LeverGeoWork *p = GOBJ_SUB(a1)->work;
    GetRootMatrix(MatrixDrive_GetMatrix(), a1);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix()[3]);
}

inline void SetFloorLeverWithNodePoint(GObj *a0, GObj *a1, int a2)
{
    float buf[4];
    float pos[4];
    LeverGeoWork *q = GOBJ_SUB(a0)->work;
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, (char *)GOBJ_SUB(a1)->nodeMtx + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnYAngleXZ(&q->shake, &q->angle, buf[0], -buf[1], buf[2] * 0.0f);
}

inline int CanFloorLeverPull(char *a0)
{
    return ((LeverGeoWork *)GOBJ_SUB(a0)->work)->state == 0;
}

inline void initParentize(GObj *a0)
{
    ClipBuf buf;
    GetRootPosition(buf.pt[0], a0);
    CopyVector(buf.pt[1], buf.pt[0]);
    buf.pt[0][1] -= 10.0f;
    buf.pt[1][1] += 200.0f;
    ClipFloor(&buf);
    if (buf.floor.n != 0) {
        LinkParentOfDObj(a0, &buf.floor.o);
    }
}

/* the zeroed template both lever inits copy into a new geometry block */
static LeverGeoWork leverGeoInit = {0}; /* derived name */

inline LeverGeoWork *InitFloorLeverGeo(char *a0, SObjSimpleSetting *a1)
{
    /* "src/switch.c" is this file's name in the game's source tree */
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 141);
    *g = leverGeoInit;
    if (a1->obj != 0) {
        g->linked = 1;
    } else {
        g->linked = 0;
    }
    g->base = CSVSYSTEM_InitDObj(accessary[GOBJ_SUB(a0)->accessary].model, a1);
    g->handle = CSVSYSTEM_InitDObj(accessary[GOBJ_SUB(a0)->accessary].model2, a1);
    return g;
}

inline void SetSwitchState(char *a0, int a1)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;
    int cur = p->state;
    unsigned char ne = cur != a1;
    if (ne) {
        switchOnSE(a0);
        p->state = a1;
    } else {
        p->state = a1;
    }
}

void FloorLeverTriStateGeo(GObj *a0)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;

    if (p->state != -1 && p->state != 1) {
        if (p->trigger != 0) {
            p->trigger(GOBJ_SUB(a0)->parent.obj, 0);
        }
    } else {
        if (p->trigger != 0) {
            p->trigger(GOBJ_SUB(a0)->parent.obj, p->state);
        }
    }
    UpdateRootMatrix(a0);
}

/* the two frame-rate divisors, the pair box.c's own fall code reads */

/* The floor lever's per-frame function.  The frame divisor (60 -
   systemStatus[0] * 10) / systemStatus[1] is written twice, once for the
   limit test and once for the equality test; the parentize probe is the
   inlined initParentize above. */
void FloorLeverGeo(GObj *a0)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;

    if (p->linked == 0) {
        if (p->linkWait++ >= 3) {
            initParentize(a0);
            p->linked = 1;
        }
    }
    if (p->state != 0) {
        p->timer = p->timer + 1;
        if (p->timer <= (60 - systemStatus[0] * 10) / systemStatus[1]) {
            p->shake = (short)(random_signed() * 128.0f);
            if (p->timer == (60 - systemStatus[0] * 10) / systemStatus[1]) {
                switchReleaseSE(a0);
            }
            if (p->trigger != 0) {
                p->trigger(GOBJ_SUB(a0)->parent.obj, p->state);
            }
        } else if (p->angle != 0) {
            p->shake = 0;
            p->angle = (short)((float)p->angle * 0.2f);
        } else {
            float q[4];

            SetIdentityQuaternion(q);
            RotQuaternionX(q, 0x4000);
            GetRootMatrix(MatrixDrive_GetMatrix(), a0);
            SetParticleEffect(0, MatrixDrive_GetMatrix()[3], q);
            p->state = 0;
            p->timer = 0;
            if (p->trigger != 0) {
                p->trigger(GOBJ_SUB(a0)->parent.obj, 0);
            }
        }
    } else {
        if (__builtin_abs(p->angle) < 0x5DD) {
            if (__builtin_abs(p->shake) < 0x5DD) {
                goto end;
            }
        }
        p->state = 1;
        p->timer = 0;
        switchOnSE(a0);
        ObjAction_MailCenter(a0, -1);
    }
end:
    UpdateRootMatrix(a0);
}

inline int GetFloorLeverAngle(char *a0)
{
    return ((LeverGeoWork *)GOBJ_SUB(a0)->work)->angle;
}

void FloorLeverDL(GObj *a0)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;

    p2o_DispVU1(a0);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_RotMatrixX(p->shake);
    CopyMatrix(*(void **)(p->handle + 0xC), MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(p->handle);
    MatrixDrive_PopMatrix();
}

void GetWallLeverGlobalHoldPoint(void *dst, void *lev)
{
    LeverGeoWork *p = GOBJ_SUB(lev)->work;

    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_TransMatrix(-50.0f, 0.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix()[3]);
}

inline void SetWallLeverWithNodePoint(GObj *a0, GObj *a1, int a2)
{
    float buf[4];
    float pos[4];
    LeverGeoWork *q = GOBJ_SUB(a0)->work;
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, (char *)GOBJ_SUB(a1)->nodeMtx + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnXAngleYZ(&q->shake, &q->angle, buf[0], buf[1], buf[2] * 0.0f);
    q->timer = 0;
}

inline int CanWallLeverPull(char *a0)
{
    return ((LeverGeoWork *)GOBJ_SUB(a0)->work)->state == 0;
}

inline LeverGeoWork *InitWallLeverGeo(char *a0, SObjSimpleSetting *a1)
{
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 300);
    *g = leverGeoInit;
    if (a1->obj != 0) {
        g->linked = 1;
    } else {
        g->linked = 0;
    }
    g->base = CSVSYSTEM_InitDObj(accessary[GOBJ_SUB(a0)->accessary].model, a1);
    g->handle = CSVSYSTEM_InitDObj(accessary[GOBJ_SUB(a0)->accessary].model2, a1);
    return g;
}

inline int GetWallLeverAngle(char *a0)
{
    return ((LeverGeoWork *)GOBJ_SUB(a0)->work)->angle;
}

inline int IsWallLeverStatus(char *a0)
{
    short *p = (short *)(char *)GOBJ_SUB(a0)->work;
    int ret = 0;
    if (__builtin_abs(p[1]) < 0xBB9) {
        if (__builtin_abs(p[0]) < 0xBB9) {
            goto end;
        }
    }
    ret = 1;
end:
    return ret;
}

/* the wall lever's counterpart of FloorLeverGeo: the same parentize probe
   and the same frame divisor written twice, no trigger callback, and a mail
   sent every frame that reports the lever's rest state (the inlined
   IsWallLeverStatus above) */
void WallLeverGeo(GObj *a0)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;

    if (p->linked == 0) {
        if (p->linkWait++ >= 3) {
            initParentize(a0);
            p->linked = 1;
        }
    }
    if (p->state != 0) {
        p->timer = p->timer + 1;
        if (p->timer <= (60 - systemStatus[0] * 10) / systemStatus[1]) {
            p->shake = (short)(random_signed() * 128.0f);
            if (p->timer == (60 - systemStatus[0] * 10) / systemStatus[1]) {
                switchReleaseSE(a0);
            }
        } else if (p->angle != 0) {
            p->shake = 0;
            p->angle = (short)((float)p->angle * 0.2f);
        } else {
            float q[4];

            SetIdentityQuaternion(q);
            RotQuaternionX(q, 0x4000);
            GetRootMatrix(MatrixDrive_GetMatrix(), a0);
            SetParticleEffect(0, MatrixDrive_GetMatrix()[3], q);
            p->state = 0;

            p->timer = 0;
        }
    } else {
        if (__builtin_abs(p->angle) < 0x3E9) {
            if (__builtin_abs(p->shake) < 0x3E9) {
                goto end;
            }
        }
        p->state = 1;
        p->timer = 0;
        switchOnSE(a0);
        ObjAction_MailCenter(a0, -1);
    }
end:
    if (IsWallLeverStatus(a0)) {
        ObjAction_MailCenter(a0, 0);
    } else {
        ObjAction_MailCenter(a0, 1);
    }
    UpdateRootMatrix(a0);
}

void WallLeverDL(GObj *a0)
{
    LeverGeoWork *p = GOBJ_SUB(a0)->work;
    char *d;
    p2o_DispVU1(a0);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    MatrixDrive_RotMatrixZ(p->angle);
    MatrixDrive_RotMatrixX(p->shake);
    d = p->handle;
    CopyMatrix(*(char **)(d + 0xC), MatrixDrive_GetMatrix());
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
