/* switch.c -- lever / switch module; #included into box.c (one box.o, listing SRCFILE.TXT). */

#include "common.h"

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

/* kept local: this TU's uses of MatrixDrive_TransMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrix(float x, float y, float z);

void GetFloorLeverGlobalHoldPoint(void *dst, char *a1)
{
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    GetRootMatrix(MatrixDrive_GetMatrix(), a1);
    MatrixDrive_RotMatrixZ(*(short *)(p + 2));
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    CopyVector(dst, MatrixDrive_GetMatrix() + 0x30);
}

/* kept local: this TU's uses of GetRootPosition do not fit the prototype in geometryManager.h */
extern void GetRootPosition(void *dst, void *obj);
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *a0, void *a1);
/* kept local: this TU's uses of MatrixDrive_GetTurnYAngleXZ do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_GetTurnYAngleXZ(void *a0, void *a1, float x, float y, float z);
/* kept local: this TU's uses of MatrixDrive_GetTurnXAngleYZ do not fit the prototype in matrixDrive.h */
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

/* kept local: this TU's uses of ClipFloor do not fit the prototype in fieldCollision.h */
extern void ClipFloor(void *a0);

inline void initParentize(char *a0)
{
    char buf[0xC0] __attribute__((aligned(16)));
    GetRootPosition(buf, a0);
    CopyVector(buf + 0x10, buf);
    *(float *)(buf + 4) -= 10.0f;
    *(float *)(buf + 0x14) += 200.0f;
    ClipFloor(buf);
    if (*(int *)(buf + 0x94) != 0) {
        LinkParentOfDObj(a0, buf + 0x8C);
    }
}

extern LeverGeoWork D_004E5AA0;
extern char D_0061EF10[];
extern int D_0063A438;
extern char D_002A79B8[];

inline LeverGeoWork *InitFloorLeverGeo(char *a0, char *a1)
{
    LeverGeoWork *g = (LeverGeoWork *)iosMallocDebug(D_0063A438, 0x20, D_0061EF10, 0x8D);
    *g = D_004E5AA0;
    if (*(int *)(a1 + 0x30) != 0) {
        g->w[5] = 1;
    } else {
        g->w[5] = 0;
    }
    g->w[3] = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28), a1);
    g->w[4] = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28 + 4), a1);
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
extern void SetIdentityQuaternion(void *q);
extern void RotQuaternionX(void *q, int angle);
extern void SetParticleEffect(int kind, void *mat, void *q);
extern void ObjAction_MailCenter(void *obj, int mail);
/* the two frame-rate divisors, the pair box.c's own fall code reads */
extern int D_0028F4C0[];

/* switch.c:179-225 in the listing.  The frame divisor (60 - D_0028F4C0[0] *
   10) / D_0028F4C0[1] is written twice, once for the limit test and once for
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
        if (*(int *)(p + 8) <= (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) {
            *(short *)p = (short)(random_signed() * 128.0f);
            if (*(int *)(p + 8) == (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) {
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
    LeverGeoWork *g = (LeverGeoWork *)iosMallocDebug(D_0063A438, 0x20, D_0061EF10, 0x12C);
    *g = D_004E5AA0;
    if (*(int *)(a1 + 0x30) != 0) {
        g->w[5] = 1;
    } else {
        g->w[5] = 0;
    }
    g->w[3] = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28), a1);
    g->w[4] = CSVSYSTEM_InitDObj(
        *(int *)(D_002A79B8 + *(int *)(*(char **)(a0 + 0x15C) + 0x844) * 0x28 + 4), a1);
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
        if (*(int *)(p + 8) <= (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) {
            *(short *)p = (short)(random_signed() * 128.0f);
            if (*(int *)(p + 8) == (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) {
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
