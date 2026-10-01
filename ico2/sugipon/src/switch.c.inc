/* kept local with ios.h's declaration: box.c, which includes this file, keeps
   its own view of ios_partition_seki and so does not include ios.h */
/* kept local: agrees with ios.h, which this TU does not include (ios_partition_seki differs) */
extern int ios_partition_sugipon;

/* switch.c -- lever / switch module; #included into box.c (one box.o, listing SRCFILE.TXT). */

void switchOnSE(int a0)
{
    ExecuteSEPackage(a0, 0x3F);
}

void switchReleaseSE(int a0)
{
    ExecuteSEPackage(a0, 0x40);
}

inline void SetSwitchTriggerFunc(char *a0, void *a1)
{
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x1C) = a1;
}

inline int InitSwitchGeo(void)
{
    return 0;
}

inline void SwitchGeo(void) {}

inline void SwitchDL(void) {}

/* kept local: agrees with matrixDrive.h, which this TU does not include (MatrixDrive_GetTurnXAngleYZ, MatrixDrive_GetTurnYAngleXZ differ) */
extern void MatrixDrive_TransMatrix(float x, float y, float z);
/* kept local for the same reason.  The void return is ROM bytes: a
   value-returning call sets $2, local-alloc marks that unused $2 live at the
   call insn, and the quantity born in the next insn is pushed off $2, which
   is where dispWheels' last CopyMatrix reads its wheel pointer. */
/* kept local: agrees with matrixDrive.h, which this TU does not include (MatrixDrive_GetTurnXAngleYZ, MatrixDrive_GetTurnYAngleXZ differ) */
extern void MatrixDrive_RotMatrixX(short a0);

void GetFloorLeverGlobalHoldPoint(void *dst, char *a1)
{
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    GetRootMatrix(MatrixDrive_GetMatrix(), a1);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix() + 0x30);
}

/* kept local: void (void *, void *) here, void (void *, char *) in geometryManager.h */
extern void GetRootPosition(void *dst, void *obj);
/* kept local: void (void *, void *) here, void (float *, float *) in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *a0, void *a1);
/* kept local: void (void *, void *, float, float, float) here, void (short *, short *, float, float, float) in matrixDrive.h */
extern void MatrixDrive_GetTurnYAngleXZ(void *a0, void *a1, float x, float y, float z);
/* kept local: void (void *, void *, float, float, float) here, void (short *, short *, float, float, float) in matrixDrive.h */
extern void MatrixDrive_GetTurnXAngleYZ(void *a0, void *a1, float x, float y, float z);

inline void SetFloorLeverWithNodePoint(char *a0, char *a1, int a2)
{
    float buf[4];
    float pos[4];
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, *(char **)(*(char **)(a1 + 0x15C) + 0xC) + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnYAngleXZ(q, q + 2, buf[0], -buf[1], buf[2] * 0.0f);
}

inline int CanFloorLeverPull(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}

/* kept local: void (void *) here, int (void *) in fieldCollision.h */
extern void ClipFloor(void *a0);

inline void initParentize(char *a0)
{
    char buf[0xC0];
    GetRootPosition(buf, a0);
    CopyVector(buf + 0x10, buf);
    *(float *)(buf + 4) -= 10.0f;
    *(float *)(buf + 0x14) += 200.0f;
    ClipFloor(buf);
    if (*(int *)(buf + 0x94) != 0) {
        LinkParentOfDObj(a0, buf + 0x8C);
    }
}

/* the zeroed template both lever inits copy into a new geometry block (the
   head of box.o's .data, VMA 0x4E5AA0, 32 bytes); the name is ours */
static LeverGeoWork leverGeoInit = {{0}};

/* The per-model box record table at VMA 0x2A79B8, 0x28 bytes a record: the
   two DObj ids the levers here and initWheels in box.c pass to
   CSVSYSTEM_InitDObj, and the three wheel floats initWheels copies out.
   RECONSTRUCTION: declared as an array of records because initWheels' first
   wheel float is an ARRAY_REF in the ROM (base register first in the address
   add, addu v0,a0,v0), which a subscript through a cast pointer does not give. */
typedef struct {
    int dobj0;    /* 0x00 */
    int dobj1;    /* 0x04 */
    int sub;      /* 0x08, the sub-box model InitBoxGeo creates */
    float f0C;    /* 0x0C */
    float f10;    /* 0x10 */
    float f14;    /* 0x14 */
    float pos[3]; /* 0x18, the sub-box's offset */
    float rotY;   /* 0x24, the sub-box's facing in degrees */
} BoxModelRec;

extern BoxModelRec D_002A79B8[];

inline LeverGeoWork *InitFloorLeverGeo(char *a0, char *a1)
{
    /* "src/switch.c" is this file's __FILE__ in the retail build (the listing
       names it sugipon/src/switch.c, included by src/box.c); __FILE__ here
       would spell the repository's .c.inc name. */
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 0x8D);
    *g = leverGeoInit;
    if (*(int *)(a1 + 0x30) != 0) {
        g->w[5] = 1;
    } else {
        g->w[5] = 0;
    }
    g->w[3] = CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(a0 + 0x15C) + 0x844)].dobj0, a1);
    g->w[4] = CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(a0 + 0x15C) + 0x844)].dobj1, a1);
    return g;
}

inline void SetSwitchState(char *a0, int a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int cur = *(int *)(p + 4);
    unsigned char ne = cur != a1;
    if (ne) {
        switchOnSE((int)a0);
        *(int *)(p + 4) = a1;
    } else {
        *(int *)(p + 4) = a1;
    }
}

void FloorLeverTriStateGeo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(int *)(p + 4) != -1 && *(int *)(p + 4) != 1) {
        if (*(int *)(p + 0x1C) != 0) {
            (*(void (**)(int, int))(p + 0x1C))(**(int **)(a0 + 0x15C), 0);
        }
    } else {
        if (*(int *)(p + 0x1C) != 0) {
            (*(void (**)(int, int))(p + 0x1C))(**(int **)(a0 + 0x15C), *(int *)(p + 4));
        }
    }
    UpdateRootMatrix(a0);
}

/* kept local: this TU's uses of SetIdentityQuaternion, RotQuaternionX,
   SetParticleEffect and ObjAction_MailCenter do not fit the prototypes in the
   headers that declare them */
/* kept local: agrees with quaternion.h, which this TU does not include (GetInverseQuaternion, GetMatrixFromQuaternion differ) */
extern void SetIdentityQuaternion(void *q);
/* kept local: agrees with quaternion.h, which this TU does not include (GetInverseQuaternion, GetMatrixFromQuaternion differ) */
extern void RotQuaternionX(void *q, int angle);
/* kept local: void (int, void *, void *) here, int (int, void *, void *) in particleEffect.h */
extern void SetParticleEffect(int kind, void *mat, void *q);
/* the two frame-rate divisors, the pair box.c's own fall code reads */
/* kept local: agrees with main.h, which this TU does not include (boyGObj, girlGObj differ) */
extern int systemStatus[];

/* switch.c:179-225 in the listing.  The frame divisor (60 - systemStatus[0] *
   10) / systemStatus[1] is written twice, once for the limit test and once for
   the equality test, which is what the ROM's two divisions are; the parentize
   probe at switch.c:122-133 is the inlined initParentize above, and the
   quaternion the particle effect is given shares its frame slot with that
   probe's work buffer, so it is declared in the block that uses it. */
void FloorLeverGeo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(int *)(p + 0x14) == 0) {
        if ((*(int *)(p + 0x18))++ >= 3) {
            initParentize(a0);
            *(int *)(p + 0x14) = 1;
        }
    }
    if (*(int *)(p + 4) != 0) {
        *(int *)(p + 8) = *(int *)(p + 8) + 1;
        if (*(int *)(p + 8) <= (60 - systemStatus[0] * 10) / systemStatus[1]) {
            *(short *)p = (short)(random_signed() * 128.0f);
            if (*(int *)(p + 8) == (60 - systemStatus[0] * 10) / systemStatus[1]) {
                switchReleaseSE((int)a0);
            }
            if (*(int *)(p + 0x1C) != 0) {
                (*(void (**)(int, int))(p + 0x1C))(**(int **)(a0 + 0x15C), *(int *)(p + 4));
            }
        } else if (*(short *)(p + 2) != 0) {
            *(short *)p = 0;
            *(short *)(p + 2) = (short)((float)*(short *)(p + 2) * 0.2f);
        } else {
            float q[4];

            SetIdentityQuaternion(q);
            RotQuaternionX(q, 0x4000);
            GetRootMatrix(MatrixDrive_GetMatrix(), a0);
            SetParticleEffect(0, (char *)MatrixDrive_GetMatrix() + 0x30, q);
            *(int *)(p + 4) = 0;
            *(int *)(p + 8) = 0;
            if (*(int *)(p + 0x1C) != 0) {
                (*(void (**)(int, int))(p + 0x1C))(**(int **)(a0 + 0x15C), 0);
            }
        }
    } else {
        if (__builtin_abs(*(short *)(p + 2)) < 0x5DD) {
            if (__builtin_abs(*(short *)p) < 0x5DD) {
                goto end;
            }
        }
        *(int *)(p + 4) = 1;
        *(int *)(p + 8) = 0;
        switchOnSE((int)a0);
        ObjAction_MailCenter(a0, -1);
    }
end:
    UpdateRootMatrix(a0);
}

inline int GetFloorLeverAngle(char *a0)
{
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}

void FloorLeverDL(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    p2o_DispVU1(a0);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_RotMatrixX(*(short *)p);
    CopyMatrix(*(void **)(*(char **)(p + 0x10) + 0xC), MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(*(void **)(p + 0x10));
    MatrixDrive_PopMatrix();
}

void GetWallLeverGlobalHoldPoint(void *dst, void *lev)
{
    char *p = *(char **)(*(char **)((char *)lev + 0x15C) + 0x830);

    GetRootMatrix(MatrixDrive_GetMatrix(), lev);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_TransMatrix(-50.0f, 0.0f, 0.0f);
    CopyVector(dst, (char *)MatrixDrive_GetMatrix() + 0x30);
}

inline void SetWallLeverWithNodePoint(char *a0, char *a1, int a2)
{
    float buf[4];
    float pos[4];
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int idx = GetSkeltonFocusNode(a1, a2);
    void *m;
    GetRootPosition(pos, a0);
    sceVu0SubVector(buf, *(char **)(*(char **)(a1 + 0x15C) + 0xC) + (idx << 6) + 0x30, pos);
    *(int *)&buf[3] = 0;
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    m = MatrixDrive_GetMatrix();
    MatrixDrive_SetTransposeMatrix(m, MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix(buf, MatrixDrive_GetMatrix(), buf);
    MatrixDrive_GetTurnXAngleYZ(q, q + 2, buf[0], buf[1], buf[2] * 0.0f);
    *(int *)(q + 8) = 0;
}

inline int CanWallLeverPull(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 4) == 0;
}

inline LeverGeoWork *InitWallLeverGeo(char *a0, char *a1)
{
    LeverGeoWork *g =
        (LeverGeoWork *)iosMallocDebug(ios_partition_sugipon, 0x20, "src/switch.c", 0x12C);
    *g = leverGeoInit;
    if (*(int *)(a1 + 0x30) != 0) {
        g->w[5] = 1;
    } else {
        g->w[5] = 0;
    }
    g->w[3] = CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(a0 + 0x15C) + 0x844)].dobj0, a1);
    g->w[4] = CSVSYSTEM_InitDObj(D_002A79B8[*(int *)(*(char **)(a0 + 0x15C) + 0x844)].dobj1, a1);
    return g;
}

inline int GetWallLeverAngle(char *a0)
{
    return *(short *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 2);
}

inline int IsWallLeverStatus(char *a0)
{
    short *p = (short *)*(char **)(*(char **)(a0 + 0x15C) + 0x830);
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
void WallLeverGeo(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(int *)(p + 0x14) == 0) {
        if ((*(int *)(p + 0x18))++ >= 3) {
            initParentize(a0);
            *(int *)(p + 0x14) = 1;
        }
    }
    if (*(int *)(p + 4) != 0) {
        *(int *)(p + 8) = *(int *)(p + 8) + 1;
        if (*(int *)(p + 8) <= (60 - systemStatus[0] * 10) / systemStatus[1]) {
            *(short *)p = (short)(random_signed() * 128.0f);
            if (*(int *)(p + 8) == (60 - systemStatus[0] * 10) / systemStatus[1]) {
                switchReleaseSE((int)a0);
            }
        } else if (*(short *)(p + 2) != 0) {
            *(short *)p = 0;
            *(short *)(p + 2) = (short)((float)*(short *)(p + 2) * 0.2f);
        } else {
            float q[4];

            SetIdentityQuaternion(q);
            RotQuaternionX(q, 0x4000);
            GetRootMatrix(MatrixDrive_GetMatrix(), a0);
            SetParticleEffect(0, (char *)MatrixDrive_GetMatrix() + 0x30, q);
            *(int *)(p + 4) = 0;

            *(int *)(p + 8) = 0;
        }
    } else {
        if (__builtin_abs(*(short *)(p + 2)) < 0x3E9) {
            if (__builtin_abs(*(short *)p) < 0x3E9) {
                goto end;
            }
        }
        *(int *)(p + 4) = 1;
        *(int *)(p + 8) = 0;
        switchOnSE((int)a0);
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

void WallLeverDL(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    char *d;
    p2o_DispVU1(a0);
    MatrixDrive_PushMatrix();
    GetRootMatrix(MatrixDrive_GetMatrix(), a0);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_RotMatrixX(*(short *)(p + 0));
    d = *(char **)(p + 0x10);
    CopyMatrix(*(char **)(d + 0xC), MatrixDrive_GetMatrix());
    p2o_DispVU1DObj(*(int *)(p + 0x10));
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
        char *p = *(char **)(*(char **)(o + 0x15C) + 0x830);

        if (*(int *)(p + 0x14) == 0) {
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
