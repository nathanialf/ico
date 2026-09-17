/* motMan_rootUpdate.c.inc -- #included by motionManager.c into one motionManager.o (PAL listing SRCFILE.TXT). */
/* kept local: this TU's uses of these do not fit the prototypes in
 * fieldCollision.h / pool.h. */
extern int ClipFloorE(void *a0);
extern int GetFloorAttribute(void *a0);
extern int CompareAttribute(unsigned int a, unsigned int b);
extern float GetPoolGlobalHeight(char *obj);
/* kept local: this TU's uses of GetTableArcTan2 do not fit the prototype in tableSin.h */
extern short GetTableArcTan2(float f12, float f13);
extern void RotQuaternionX(void *q, short ang);
extern float D_004ECA70[];
/* kept local: this TU's uses of these do not fit the prototypes in
 * fieldCollision.h / math.h. */
extern void GetWallGlobalInfo(int a0, void *v, int a2, char *node);
extern float atan2f(float y, float x);
/* kept local: this TU's uses of ZeroPoint do not fit the prototype in matrixDrive.h */
extern char ZeroPoint[];
extern float D_007201F0[];
extern char D_00720210[];
extern MotShift D_0063A810;
extern MotShift D_0063B930[];
extern float D_0063B940;
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *elem, void *base, void *v, float a, float b);
extern void _wallHitReaction(void *w, void *p, void *q, int flag);
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
/* kept local: this TU's uses of MultiQuaternion do not fit the prototype in quaternion.h */
extern void MultiQuaternion(void *p0, void *p1, void *p2);
extern void ClipWallAdjustPos(void *a0);
extern void ClipWallE(void *a0);
extern int D_0063B230;
extern char D_004ECAF0[];
extern char D_004ECB00[];
extern void CopyQuaternion(void *a0, void *a1);
extern void GetRootQuaternion(void *q, void *obj);

/* 12-byte plane record copied out of the motion work block. */
typedef struct {
    int b[3];
} FieldBlk12;

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", _wallHitReaction);

void _wallCollisionPreProcess(char *w, void *p, void *q, float dy)
{
    Vec16 save;
    float r;

    if (D_0063B230 != 0) {
        CopyVector(w, q);
    } else {
        CopyVector(w, D_0063C490 + 0x160);
    }
    CopyVector(w + 0x10, p);
    *(FieldBlk12 *)(w + 0x74) = *(FieldBlk12 *)(D_0063C490 + 0x120);
    *(float *)(w + 4) = *(float *)(w + 4) + dy;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + dy;
    if (*(int *)(D_0063C490 + 0x320) != 0) {
        r = *(float *)(D_0063C490 + 0x338);
        if (r < 20.0f) {
            *(float *)(w + 0x70) = D_0063B900 * 20.0f;
        } else {
            *(float *)(w + 0x70) = r * D_0063B900;
        }
        ClipWallField(w);
    } else {
        *(float *)(w + 0x70) = *(float *)(D_0063C490 + 0x338) * D_0063B900;
        CopyVector(&save, w + 0x10);
        if (*(int *)(w + 0x74) != 0) {
            ClipWallE(w);
        } else {
            ClipWall(w);
        }
        CopyVector(w + 0x10, w + 0x20);
        ClipFloor(w);
        CopyVector(w + 0x10, &save);
    }
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into its
 * callers (rows 306-320, above wallCollisionAndReact's 331), so it carries no
 * symbol in MAIN.MAP. */
static inline void wallCollisionAndFloorFit(char *cur, char *last, float dy)
{
    ClipBuf w;
    Vec16 t;

    _wallCollisionPreProcess((char *)&w, cur, last, dy);
    if (*(int *)((char *)&w + 0x88) != 0) {
        _wallHitReaction(&w, cur, last, 0);
    } else if (*(int *)((char *)&w + 0x94) != 0) {
        CopyVector(&t, (char *)&w + 0x20);
        t.f[1] = t.f[1] - dy;
        CopyVector(cur, &t);
        CopyVector(last, &t);
    }
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into its
 * callers (rows 331-335), so it carries no symbol in MAIN.MAP.  Row 331 is
 * where the two work-block locals are attributed, and dy is a parameter: row
 * 331 carries the caller's constant. */
static inline void wallCollisionAndReact(float dy)
{
    ClipBuf w;
    char *g = D_0063C490;
    char *last = g + 0x150;

    _wallCollisionPreProcess((char *)&w, g, last, dy);
    if (*(int *)((char *)&w + 0x88) != 0) {
        _wallHitReaction(&w, g, last, 0);
    }
}

inline int upperFieldCheck(char *a0, float f)
{
    char buf[0xC0] __attribute__((aligned(16)));
    CopyVector((void *)buf, a0);
    CopyVector((void *)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ClipFloor(buf);
    return *(int *)(buf + 0x94);
}

/* RECONSTRUCTED NAMES: the PAL listing shows these two bodies only inlined
 * into getFieldCollision (rows 381-383 and 389-394, both above its def line
 * 407), so neither carries a symbol in MAIN.MAP. */
static inline void setPoolHeightOfFloor(char *w)
{
    /* w+0x8C is the floor's owning object: ico2/sugipon/src/box.c reads the
     * same word of the same work block as `char **`. */
    char *obj = *(char **)(w + 0x8C);

    *(char **)(D_0063C494 + 0x1D8) = obj;
    *(float *)(D_0063C494 + 0x1D0) = GetPoolGlobalHeight(obj);
    *(float *)(D_0063C494 + 0x1D4) = *(float *)(w + 0x24) - *(float *)(D_0063C494 + 0x1D0);
}

static inline void checkPoolFloor(char *w)
{
    int attr = GetFloorAttribute(w);

    if (CompareAttribute(attr, 0x50) != 0) {
        if (*(float *)(w + 0x24) - *(float *)(D_0063C490 + 4) < *(float *)(D_0063C490 + 0x1D0)) {
            setPoolHeightOfFloor(w);
        }
    }
}

int getFieldCollision(char *w)
{
    float d;

    CopyVector(w, D_0063C490);
    CopyVector(w + 0x10, w);
    *(float *)(w + 4) = *(float *)(w + 4) - 50.0f;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 50000.0f;
    if (*(int *)(D_0063C490 + 0x120) != 0) {
        *(FieldBlk12 *)(w + 0x74) = *(FieldBlk12 *)(D_0063C490 + 0x120);
        ClipFloorE(w);
    } else {
        ClipFloor(w);
    }
    if (*(int *)(w + 0x94) != 0) {
        checkPoolFloor(w);
        d = GetYDistanceFromPlane(D_0063C490 + 0x130, w + 0x20);
        if (d <= 35.0f) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", setIKAndAdjustRootHeight);

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateFly and rootUpdateEnemyFly (rows 736-756, which sit between
 * setIKAndAdjustRootHeight's def line 548 and landingFieldAction's 809), so it
 * carries no symbol in MAIN.MAP. */
static inline int getFlyFieldCollision(char *w)
{
    float y;

    y = *(float *)(D_0063C4A8 + 0x120);
    if (y < -0.5f) {
        return 0;
    }
    *(int *)(w + 0x70) = 0;
    CopyVector(w, D_0063C490);
    *(float *)(w + 4) = *(float *)(D_0063C490 + 0x164);
    CopyVector(w + 0x10, D_0063C490);
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 10000.0f;
    ClipFloor(w);
    return CheckFieldContact(w, (char *)D_0063B93C, (float *)D_0063C490,
                             *(float *)(D_0063C490 + 0x1D0));
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * landingFieldAction (rows 787-801, above its def line 809), so it carries no
 * symbol in MAIN.MAP.  Row 787 is the declaration line, which is where the
 * caller's `w + 0xA0` address arithmetic is attributed. */
static inline void adjustRootByLandingPlane(char *plane)
{
    Vec16 push;
    Vec16 half;
    Vec16 pl;
    float d;

    CopyVector(&pl, plane);
    pl.f[3] = 0.0f;
    d = plane_distance(D_0063C490 + 0x90, &pl);
    if (d < 0.0f) {
        _ScaleVector(&push, &pl, d);
        push.f[3] = 0.0f;
        _SubVector(&half, D_0063C490 + 0x90, &push);
        half.f[3] = 0.0f;
        half.f[1] = 0.0f;
        _ScaleVectorXYZ(&half, &half, 0.5f);
        _SubVectorXYZ(D_0063C490 + 0x150, D_0063C490, &half);
    }
}

void landingFieldAction(char *w)
{
    float h;

    *(float *)(D_0063C490 + 4) = *(float *)(w + 0x24) - *(float *)(D_0063C490 + 0x1D0);
    adjustRootByLandingPlane(w + 0xA0);
    h = *(float *)(D_0063C490 + 0x1B4);
    CopyVector(D_0063C490 + 0x130, w + 0xA0);
    *(float *)(D_0063C494 + 0xEC) = GetYProjectionOfPlane((int)(w + 0xA0), (int)D_0063C490) - h;
    CopyVector(D_0063C490 + 0x1B0, D_0063C490);
    *(float *)(D_0063C490 + 0x1B4) = *(float *)(w + 0x24);
    *(int *)(D_0063C494 + 0x14) |= 8;
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateFly and rootUpdateEnemyFly (row 832 followed by
 * setPoolHeightOfFloor's rows 381-383), between landingFieldAction's def line
 * 809 and floorFitting's 861, so it carries no symbol in MAIN.MAP. */
static inline void markPoolContact(char *w)
{
    *(int *)(D_0063C494 + 0x14) |= 0x400;
    setPoolHeightOfFloor(w);
}

void floorFitting(int kind)
{
    Vec16 plane;
    Vec16 dir;
    float mtx[16];
    short ang;

    if (kind == 0x11 || kind == 0x14) {
        plane = *(Vec16 *)(D_0063C490 + 0x130);
        GetMatrixFromQuaternion(mtx, D_0063C490 + 0x30);
        _ApplyMatrix(&dir, (int)mtx, ZUnitVector);
        plane.f[3] = 0.0f;
        D_004ECA70[1] = GetYDistanceFromPlane(&plane, &dir);
        D_004ECA70[2] = 1.0f;
        _NormalizeVector(D_004ECA70, D_004ECA70);
        ang = GetTableArcTan2(D_004ECA70[1], D_004ECA70[2]);
        RotQuaternionX(D_0063C490 + 0x30, ang);
        *(int *)(D_0063C490 + 0x204) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateXZ);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateXZ_MotPos);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", adjustSideWall);

int checkSideWall(int a0, int a1, int p, int a3, int a4)
{
    char buf[0x10];
    int flag;
    int mag;
    int mask;

    *(int *)(p + 0x70) = 0;
    CopyVector((void *)p, (void *)a3);
    sceVu0ApplyMatrix((int *)(p + 0x10), a1, (char *)a0);
    ClipWall((void *)p);

    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    if (*(int *)(D_0063C490 + 0x324) != 0) {
        ClipWallFuchiHangWalkStop((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = GetWallAttribute((void *)p);
            switch (*(int *)(D_0063C490 + 0x324)) {
            default:
            case 1:
                mask = 0x20000000;
                break;
            case 2:
                mask = 0x10000000;
                break;
            }
            if (mag & mask) {
                flag = 1;
                if (mag & 0x0FFFFFFF) {
                    return -1;
                }
            }
            if (flag != 0) {
                return adjustSideWall(p, 0, a4);
            }
            goto block12;
        }
    }
block12:
    _ApplyMatrix(buf, a1, D_004ECA80);
    CopyVector((void *)p, (void *)(p + 0x10));
    _AddVectorXYZ(p + 0x10, p, buf);
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    CopyVector((void *)p, (void *)(p + 0x10));
    CopyVector((void *)(p + 0x10), (void *)(a3 + 0x10));
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
    disp_one:
        return adjustSideWall(p, 1, a4);
    }
    return 0;
}

void forceFallDown(void)
{
    iosOmSendMail(D_0063B93C, 0x18, D_0063B93C);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
}

void forceReset(void)
{
    iosOmSendMail(D_0063B93C, 0x103, D_0063B93C);
    CopyVector((char *)D_0063C490 + 0x150, (char *)D_0063C490);
}

void checkWallUpperWall(void)
{
    int v;
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    {
        register float *p = (float *)D_0063C490;
        MatrixDrive_TransMatrix(p[0], p[1] - D_007201F4[0], p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    checkUpperWallState();
    MatrixDrive_PopMatrix();
}

void calcWallFittingGeometry(void)
{
    Vec16 v;
    float mtx[16];
    Vec16 base;
    Vec16 rot;
    short ang;

    GetWallGlobalInfo(0, &v, *(int *)(D_0063C490 + 0xE8),
                      *(char **)(*(char **)(*(char **)(D_0063C490 + 0xE0) + 0x15C) + 0xC) +
                          *(int *)(D_0063C490 + 0xE4) * 0x40);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&v, (int)mtx, (char *)&v);
    v.f[0] = 0.0f;
    _NormalizeVector(&v, &v);
    ang = (short)(atan2f(v.f[1], -v.f[2]) * 10430.378f);
    RotQuaternionX(D_0063C490 + 0x30, ang);
    MatrixDrive_PushMatrix();
    _ApplyMatrix(&base, MatrixDrive_GetMatrix(), (char *)D_007201F0);
    MatrixDrive_RotMatrixX(ang);
    _ApplyMatrix(&rot, MatrixDrive_GetMatrix(), (char *)D_007201F0);
    _SubVector(D_0063C490 + 0x10, &rot, &base);
    *(int *)(D_0063C490 + 0x1C) = 0;
    MatrixDrive_PopMatrix();
    *(int *)(D_0063C490 + 0xC0) = 0;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateHang);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateSwim);

/* RECONSTRUCTED NAMES: both bodies appear in the PAL listing only inlined into
 * avoidSideAdjustWall (rows 1950-1952 and 1983-1987, above its def line 1993),
 * so neither carries a symbol in MAIN.MAP. */
static inline int clipSideWallAndHit(char *w)
{
    int hit = 1;

    ClipWallAdjustPos(w);

    return *(int *)(w + 0x88) != 0 ? hit : 0;
}

static inline void pushRootAlongSideWall(char *w)
{
    Vec16 t;

    _ScaleVectorXYZ(&t, w + 0xA0, 40.0f);
    _AddVectorXYZ((int)&t, (int)(w + 0x20), &t);
    _SubVectorXYZ(&t, &t, D_0063C490);
    _ScaleVectorXYZ(&t, &t, 0.07f);
    _AddVectorXYZ((int)D_0063C490, (int)D_0063C490, &t);
}

int avoidSideAdjustWall(void)
{
    float mtx[16];
    char w[0xD0] __attribute__((aligned(16)));

    memset(w, 0, 0xC0);
    GetMatrixFromQuaternionPos(mtx, D_0063C490 + 0x30, D_0063C490);
    _ApplyMatrix(w, (int)mtx, D_004ECAF0);
    _ApplyMatrix(w + 0x10, (int)mtx, D_004ECB00);
    if (clipSideWallAndHit(w) == 0) {
        _ApplyMatrix(w, (int)mtx, D_004ECB00);
        _ApplyMatrix(w + 0x10, (int)mtx, D_004ECAF0);
        if (clipSideWallAndHit(w) == 0) {
            return 0;
        }
    }
    pushRootAlongSideWall(w);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateStepSolution);

MotShift rootUpdateTrueMotion(int a0)
{
    float mtx[16];
    Vec16 v;
    int noMove = a0;

    GetMatrixFromQuaternion(mtx, D_0063C490 + 0x30);
    if (noMove == 0) {
        sceVu0ApplyMatrix((int *)&v, (int)mtx, (char *)D_007201F0);
        v.f[1] = v.f[1] + *(float *)(D_0063B938 + 0x14);
        v.f[0] = v.f[2] = 0.0f;
        CopyVector(D_0063C490 + 0x10, &v);
    } else {
        CopyVector(D_0063C490 + 0x10, ZeroPoint);
    }
    *(int *)(D_0063C490 + 0x180) = -1;
    *(int *)(D_0063C490 + 0xC0) = 0;
    CopyVector(D_0063C490 + 0xD0, D_00720210);
    return D_0063A810;
}

MotShift rootUpdateDirectPlayForStream(void)
{
    float *p;
    int *q;

    SetIdentityQuaternion(D_0063C490 + 0x30);
    RotQuaternionY(D_0063C490 + 0x30, -32768);
    CopyVector(D_0063C490, D_007201F0);
    p = (float *)D_0063C490;
    p[0] = -p[0];
    p[2] = -p[2];
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    CopyVector(D_0063C490 + 0x90, ZeroVector);
    CopyVector(D_0063C490 + 0x10, ZeroVector);
    q = (int *)D_0063C490;
    q[0x60] = -1;
    q[0x30] = 0;
    AdjustMotionHeightToNearestField((char *)D_0063B93C);
    CopyVector(D_0063C490 + 0xD0, D_00720210);
    return D_0063A810;
}

MotShift rootUpdateDirectPlay(int a0)
{
    int kind = a0;
    float *p;
    int *q;
    float s;

    SetIdentityQuaternion(D_0063C490 + 0x30);
    RotQuaternionY(D_0063C490 + 0x30, -32768);
    CopyVector(D_0063C490, D_007201F0);
    p = (float *)D_0063C490;
    p[0] = p[0] - *(float *)(D_0063C4A8 + 0x124);
    p[1] = p[1] - *(float *)(D_0063C4A8 + 0x128);
    p[2] = p[2] + *(float *)(D_0063C4A8 + 0x12C);
    if (kind == 14) {
        s = 1.0f / D_0063B900;
        p[0] = p[0] * -s;
        p[1] = p[1] * s;
        p[2] = p[2] * -s;
    } else {
        p[0] = -p[0];
        p[2] = -p[2];
    }
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    CopyVector(D_0063C490 + 0x90, ZeroVector);
    CopyVector(D_0063C490 + 0x10, ZeroVector);
    q = (int *)D_0063C490;
    q[0x60] = -1;
    q[0x30] = 0;
    AdjustMotionHeightToNearestField((char *)D_0063B93C);
    CopyVector(D_0063C490 + 0xD0, D_00720210);
    return D_0063A810;
}

MotShift rootUpdateNodeFix(void)
{
    /* NESTED FUNCTION: the PAL listing emits it as keepVerticalZWithQ.377
     * immediately before rootUpdateNodeFix and its prologue spills the static
     * chain ($2) at sp+0, so the 2001 source defines it inside this body
     * (listing rows 2374-2400, above the parent's first statement at 2407).
     * The single call site passes the parent frame in $2. */
    void keepVerticalZWithQ(void *q)
    {
        float mtx[16];
        Vec16 v;

        GetMatrixFromQuaternion(mtx, q);
        sceVu0ApplyMatrix((int *)&v, (int)mtx, ZUnitVector);
        v.f[1] = 0.0f;
        sceVu0Normalize(&v, &v);
        SetIdentityQuaternion(D_0063C490 + 0x30);
        RotQuaternionY(D_0063C490 + 0x30, -GetTableArcTan2(v.f[0], -v.f[2]));
        MultiQuaternion(D_0063C490 + 0x30, D_0063C490 + 0x30, D_0063C490 + 0x390);
        CopyMatrix((void *)MatrixDrive_GetMatrix(),
                   *(char **)(*(char **)(*(char **)(D_0063C490 + 0x384) + 0x15C) + 0xC) +
                       *(int *)(D_0063C490 + 0x388) * 0x40);
        MatrixDrive_TransMatrixV(D_0063C490 + 0x3A0);
        UnitRotation(MatrixDrive_GetMatrix());
        MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
        MatrixDrive_TransMatrix(D_007201F0[0], D_007201F0[1], D_007201F0[2]);
        CopyVector(D_0063C490, (char *)MatrixDrive_GetMatrix() + 0x30);
    }

    Vec16 rq;
    Vec16 va;
    Vec16 vb;

    CopyQuaternion(&rq, *(char **)(*(char **)(*(char **)(D_0063C490 + 0x384) + 0x15C) + 0x10) +
                            *(int *)(D_0063C490 + 0x388) * 0x10);
    switch (*(unsigned int *)(D_0063C490 + 0x3B4)) {
    default:
    case 0:
        MultiQuaternion(D_0063C490 + 0x30, &rq, D_0063C490 + 0x390);
        CopyMatrix((void *)MatrixDrive_GetMatrix(),
                   *(char **)(*(char **)(*(char **)(D_0063C490 + 0x384) + 0x15C) + 0xC) +
                       *(int *)(D_0063C490 + 0x388) * 0x40);
        MultiMatrixByQuaternion((char *)D_0063C490 + 0x390);
        MatrixDrive_TransMatrixV(D_0063C490 + 0x3A0);
        MatrixDrive_TransMatrix(D_007201F0[0], D_007201F0[1], D_007201F0[2]);
        CopyVector(D_0063C490, (char *)MatrixDrive_GetMatrix() + 0x30);
        break;
    case 1:
        break;
    case 3:
        GetRootQuaternion(&rq, *(char **)(D_0063C490 + 0x384));
        MultiQuaternion(&rq, &rq, *(char **)(*(char **)(D_0063C490 + 0x384) + 0x15C) + 0xE0);
        /* fall through */
    case 2:
        keepVerticalZWithQ(&rq);
        break;
    }
    _ScaleVector(&va, D_0063C490 + 0x150, 1.0f - *(float *)(D_0063C490 + 0x3B0));
    _ScaleVector(&vb, D_0063C490, *(float *)(D_0063C490 + 0x3B0));
    _AddVector(D_0063C490, &va, &vb);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    CopyVector(D_0063C490 + 0x1B0, D_0063C490);
    CopyVector(D_0063C490 + 0x90, ZeroVector);
    CopyVector(D_0063C490 + 0x10, ZeroPoint);
    CopyVector(D_0063C490 + 0xD0, D_00720210);
    *(int *)(D_0063C490 + 0x180) = -1;
    *(int *)(D_0063C490 + 0xC0) = 0;
    *(int *)(D_0063C494 + 0x188) = 0;
    return D_0063A810;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateY);

/* The parameter is unused: the ROM overwrites $4 with the first load. */
MotShift rootUpdateY_Rope(int a0)
{
    float mtx[16];
    Vec16 dir;
    Vec16 pos;
    Vec16 v;
    Vec16 cur;
    float save;
    int mode;

    CopyVector(D_0063C490 + 0x1B0, D_0063C490);
    mode = *(int *)(D_0063C490 + 0x380);
    if (mode >= 2) {
        GetMatrixFromQuaternion(mtx, D_0063C490 + 0x30);
        sceVu0ApplyMatrix((int *)&dir, (int)mtx, (char *)D_007201F0);
        sceVu0AddVector(&pos, D_0063C490 + 0x370, &dir);
        *(float *)D_0063C490 = pos.f[0];
        *(float *)(D_0063C490 + 8) = pos.f[2];
    } else if (mode != 0) {
        int node = GetSkeltonFocusNode((char *)D_0063B93C, 22);

        v.f[0] = *(float *)D_0063C490;
        v.f[1] = *(float *)(D_0063C490 + 4);
        v.f[2] = *(float *)(D_0063C490 + 8);
        _SubVector(D_0063C490, D_0063C490 + 0x370, D_0063C488 + node * 0x10);
        if (*(int *)(D_0063C490 + 0x380) < 0) {
            _InterGV(D_0063C490, &v, D_0063C490, D_0063B940, 1.0f);
        }
    }
    save = *(float *)(D_0063C490 + 0x338);
    CopyVector(&cur, D_0063C490);
    CopyVector(&v, D_0063C490 + 0x150);
    *(float *)(D_0063C490 + 0x338) = 60.0f;
    wallCollisionAndFloorFit((char *)&cur, (char *)&v, 5.0f);
    *(float *)(D_0063C490 + 0x338) = save;
    /* 0xEC is the float landingFieldAction and rootUpdateFly write. */
    *(float *)(D_0063C494 + 0xEC) = 0.0f;
    *(int *)(D_0063C490 + 0xC0) = 0;
    SubVectorXYZ(D_0063C490 + 0x90, D_0063C490, D_0063C490 + 0x150);
    CopyVector(D_0063C490 + 0x10, ZeroPoint);
    CopyVector(D_0063C490 + 0x1B0, D_0063C490);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    *(int *)(D_0063C490 + 0x180) = -1;
    return D_0063A810;
}

MotShift rootUpdateFly(void)
{
    MotShift shift = D_0063B930[0];
    char w[0xC0] __attribute__((aligned(16)));
    int contact;
    float h;
    float d;

    *(int *)(D_0063C494 + 0x188) = 0;
    contact = getFlyFieldCollision(w);
    switch (contact) {
    case 1:
        *(int *)(D_0063C494 + 0x14) |= 8;
        h = *(float *)(D_0063C490 + 0x1B4);
        CopyVector(D_0063C490 + 0x130, w + 0xA0);
        d = GetYProjectionOfPlane((int)(w + 0xA0), (int)D_0063C490);
        d = d - h;
        *(float *)(D_0063C494 + 0xEC) = d;
        break;
    case 2:
        markPoolContact(w);
        break;
    }
    wallCollisionAndReact(*(float *)(D_0063B938 + 0x14));
    *(int *)(D_0063C490 + 0xC0) = 0;
    SubVectorXYZ(D_0063C490 + 0x90, D_0063C490, D_0063C490 + 0x150);
    CopyVector(D_0063C490 + 0x10, ZeroPoint);
    CopyVector(D_0063C490 + 0x90, ZeroVector);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    *(int *)(D_0063C490 + 0x180) = -1;
    return shift;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/motionManager", rootUpdateEnemyFly);
