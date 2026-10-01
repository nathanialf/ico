/* kept local with ios.h's declaration: box.c, which includes this file, keeps
   its own view of ios_partition_seki and so does not include ios.h */

/* switch.c -- lever / switch module; #included into box.c (one box.o, listing SRCFILE.TXT). */

void switchOnSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x3F);
}

void switchReleaseSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x40);
}

inline void SetSwitchTriggerFunc(char *a0, void *a1)
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
    CopyVector(dst, MatrixDrive_GetMatrix() + 0x30);
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

/* the zeroed template both lever inits copy into a new geometry block (the
   head of box.o's .data, VMA 0x4E5AA0, 32 bytes); the name is ours */
static LeverGeoWork leverGeoInit = {0};

/* The per-model box record table at VMA 0x2A79B8, 0x28 bytes a record: the
   two DObj ids the levers here and initWheels in box.c pass to
   CSVSYSTEM_InitDObj, and the three wheel floats initWheels copies out.
   RECONSTRUCTION: declared as an array of records because initWheels' first
   wheel float is an ARRAY_REF in the ROM (base register first in the address
   add, addu v0,a0,v0), which a subscript through a cast pointer does not give. */
typedef struct {       /* field names derived */
    int dobj0;         /* 0x00 */
    int dobj1;         /* 0x04 */
    int sub;           /* 0x08, the sub-box model InitBoxGeo creates */
    float wheelHeight; /* 0x0C, the wheels' height InitBoxGeo's wheels sit at */
    float wheelFront;  /* 0x10, the front axle's Z */
    float wheelRear;   /* 0x14, the rear axle's Z */
    float pos[3];      /* 0x18, the sub-box's offset */
    float rotY;        /* 0x24, the sub-box's facing in degrees */
} BoxModelRec;

extern BoxModelRec D_002A79B8[];

inline LeverGeoWork *InitFloorLeverGeo(char *a0, char *a1)
{
    /* "src/switch.c" is this file's __FILE__ in the retail build (the listing
       names it sugipon/src/switch.c, included by src/box.c); __FILE__ here
       would spell the repository's .c.inc name. */
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 141);
    *g = leverGeoInit;
    if (*(int *)(a1 + 0x30) != 0) {
        g->linked = 1;
    } else {
        g->linked = 0;
    }
    g->base = CSVSYSTEM_InitDObj(D_002A79B8[GOBJ_SUB(a0)->accessary].dobj0, a1);
    g->handle = CSVSYSTEM_InitDObj(D_002A79B8[GOBJ_SUB(a0)->accessary].dobj1, a1);
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
            p->trigger(**(int **)(((char *)a0) + 0x15C), 0);
        }
    } else {
        if (p->trigger != 0) {
            p->trigger(**(int **)(((char *)a0) + 0x15C), p->state);
        }
    }
    UpdateRootMatrix(a0);
}

/* kept local: this TU's uses of SetIdentityQuaternion, RotQuaternionX,
   SetParticleEffect and ObjAction_MailCenter do not fit the prototypes in the
   headers that declare them */

/* the two frame-rate divisors, the pair box.c's own fall code reads */

/* switch.c:179-225 in the listing.  The frame divisor (60 - systemStatus[0] *
   10) / systemStatus[1] is written twice, once for the limit test and once for
   the equality test, which is what the ROM's two divisions are; the parentize
   probe at switch.c:122-133 is the inlined initParentize above, and the
   quaternion the particle effect is given shares its frame slot with that
   probe's work buffer, so it is declared in the block that uses it. */
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
                p->trigger(**(int **)(((char *)a0) + 0x15C), p->state);
            }
        } else if (p->angle != 0) {
            p->shake = 0;
            p->angle = (short)((float)p->angle * 0.2f);
        } else {
            float q[4];

            SetIdentityQuaternion(q);
            RotQuaternionX(q, 0x4000);
            GetRootMatrix(MatrixDrive_GetMatrix(), a0);
            SetParticleEffect(0, (char *)MatrixDrive_GetMatrix() + 0x30, q);
            p->state = 0;
            p->timer = 0;
            if (p->trigger != 0) {
                p->trigger(**(int **)(((char *)a0) + 0x15C), 0);
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
    CopyVector(dst, (char *)MatrixDrive_GetMatrix() + 0x30);
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

inline LeverGeoWork *InitWallLeverGeo(char *a0, char *a1)
{
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 300);
    *g = leverGeoInit;
    if (*(int *)(a1 + 0x30) != 0) {
        g->linked = 1;
    } else {
        g->linked = 0;
    }
    g->base = CSVSYSTEM_InitDObj(D_002A79B8[GOBJ_SUB(a0)->accessary].dobj0, a1);
    g->handle = CSVSYSTEM_InitDObj(D_002A79B8[GOBJ_SUB(a0)->accessary].dobj1, a1);
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

/* switch.c:331-380 in the listing, the wall lever's twin of FloorLeverGeo: the
   same parentize probe and the same frame divisor written twice, no trigger
   callback, and a mail sent every frame that reports the lever's rest state
   (the inlined IsWallLeverStatus above, switch.c:319-328). */
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
            SetParticleEffect(0, (char *)MatrixDrive_GetMatrix() + 0x30, q);
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

/* switch.c:414-421 in the listing: the poll loop is inlined at all four call
   sites below, so it is a static inline helper here; it has no symbol of its
   own in the ROM and no census row, and the name is descriptive. */
static inline int checkReadySwitchKind(int kind)
{
    char *o;

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
