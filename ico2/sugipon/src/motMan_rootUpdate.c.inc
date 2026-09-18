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
extern char D_00720200[];
/* the two ints the demo timer keeps: the elapsed count and its divisor. */
extern int D_0028F4C0[];
extern char D_0061FE80[];

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
static inline int wallCollisionAndFloorFit(char *cur, char *last, float dy)
{
    ClipBuf w;
    Vec16 t;

    _wallCollisionPreProcess((char *)&w, cur, last, dy);
    if (*(int *)((char *)&w + 0x88) != 0) {
        _wallHitReaction(&w, cur, last, 0);
        return 1;
    } else if (*(int *)((char *)&w + 0x94) != 0) {
        CopyVector(&t, (char *)&w + 0x20);
        t.f[1] = t.f[1] - dy;
        CopyVector(cur, &t);
        CopyVector(last, &t);
        return 1;
    }
    return 0;
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

/* RECONSTRUCTED NAMES for two helpers the PAL listing shows only inlined into
 * setIKAndAdjustRootHeight (rows 439-483 and 492-517, both above its def line
 * 548), so neither carries a symbol in MAIN.MAP. */

/* kept local: this TU's uses of these do not fit the prototypes in
 * Matrix.h / debug.h. */
extern float _InnerProduct(void *a, void *b);
/* "PLANE<EUC-JP riMItto desu> %f <EUC-JP abunai node rakka sasemasu>\n":
 * the plane limit was exceeded, so the actor is dropped. */
extern char D_0061FE08[];
extern int D_0063B21C;
/* declared as an array so the load is %hi/%lo and not gp-relative. */
extern float D_0063B928[];

/* Builds the plane the root height is measured against out of the floor plane
 * the motion block carries, and reports whether the floor was steep enough to
 * need one. */
static inline int makeRootFitPlane(char *pl, char *o)
{
    char *fl = o + 0x130;
    Vec16 pos;
    Vec16 n;
    int ret = 0;

    CopyVector(pl, fl);
    if (-0.3f < *(float *)(fl + 4)) {
        CopyVector(&pos, o);
        pos.f[1] = GetYProjectionOfPlane((int)fl, (int)o);

        *(float *)(pl + 4) = 0.0f;
        _NormalizeVector(&n, pl);
        _ScaleVectorXYZ(pl, &n, _Sqrt(0.90999997f));
        *(float *)(pl + 4) = -0.3f;

        *(float *)(pl + 0) = 0.0f;
        *(float *)(pl + 4) = -1.0f;
        *(float *)(pl + 8) = 0.0f;
        *(float *)(pl + 0xC) = -_InnerProduct(pl, &pos);
        ret = 1;
    }
    return ret;
}

/* Drops a probe from v onto the floor and returns how far the root has to move
 * to sit on it. */
static inline float getFloorDropAt(char *v, char *pl, char *o)
{
    char w[0xC0] __attribute__((aligned(16)));
    float d;

    CopyVector(w, v);
    CopyVector(w + 0x10, v);
    *(float *)(w + 4) = *(float *)(w + 4) - 100.0f;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 500.0f;
    ClipFloor(w);
    if (*(int *)(w + 0x94) != 0) {
        d = -(*(float *)(w + 0x24) - *(float *)(v + 4));
    } else {
        d = D_0063B928[0];
    }

    if (*(int *)(w + 0x94) != 0) {
        float t =
            GetYProjectionOfPlane((int)(w + 0xA0), (int)o) - GetYProjectionOfPlane((int)pl, (int)o);

        if (45.0f < (t < 0.0f ? -t : t)) {
            d = GetYDistanceFromPlane(pl, v);
        }
    } else {
        d = GetYDistanceFromPlane(pl, v);
    }
    return d;
}

static void setIKAndAdjustRootHeight(char *mv)
{
    Vec16 p0;
    Vec16 p1;
    Vec16 p2;
    Vec16 pl;
    float d0;
    float d1;
    float dy;
    float h;
    float t;
    int steep;
    int node;

    if (*(int *)(D_0063C490 + 0x364) < 0) {
        return;
    }
    steep = makeRootFitPlane((char *)&pl, D_0063C490);
    h = GetYProjectionOfPlane((int)&pl, (int)D_0063C490) + *(float *)(mv + 4) -
        *(float *)(D_0063C490 + 4);
    if (steep != 0) {
        if ((h < 0.0f ? -h : h) < 35.0f) {
            *(float *)(D_0063C490 + 4) = *(float *)(D_0063C490 + 4) + h;
            *(float *)(D_0063C490 + 0x154) = *(float *)(D_0063C490 + 0x154) + h;
            return;
        }
        *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 4;
        *(float *)(D_0063C490 + 0x154) = *(float *)(D_0063C490 + 4);
        /* retail links debug_StdPrintfDummy in place of the listing's printf. */
        debug_StdPrintfDummy(D_0061FE08, fptodp(h));

        return;
    }
    if (*(int *)(D_0063C494 + 0x68) == 0x14) {
        *(float *)(D_0063C490 + 4) = *(float *)(D_0063C490 + 4) + h;
        *(float *)(D_0063C490 + 0x154) = *(float *)(D_0063C490 + 0x154) + h;
        return;
    }
    if (*(float *)(D_0063B938 + 0x14) * D_0063B900 < (h < 0.0f ? -h : h)) {
        *(float *)(D_0063C490 + 4) = *(float *)(D_0063C490 + 4) + h;
        *(float *)(D_0063C490 + 0x154) = *(float *)(D_0063C490 + 0x154) + h;
        return;
    }

    makeRootFitPlane((char *)&pl, D_0063C490);

    AddVectorXYZ(&p0, D_0063C488 + *(int *)(D_0063C490 + 0x364) * 0x10, mv);

    AddVectorXYZ(&p1, D_0063C488 + *(int *)(D_0063C490 + 0x364) * 0x10, D_0063C490);

    p1.f[1] = p1.f[1] - p0.f[1];

    d0 = getFloorDropAt((char *)&p1, (char *)&pl, D_0063C490);

    dy = d0;
    switch (*(int *)(D_0063B938 + *(int *)(D_0063C490 + 0x364) * 0x40 + 4)) {
    case 0x30:
        node = GetSkeltonFocusNode((char *)D_0063B93C, 0x34);
        break;
    case 0x34:
        node = GetSkeltonFocusNode((char *)D_0063B93C, 0x30);
        break;
    default:
        node = -1;
        break;
    }
    if (node != -1) {
        Vec16 p3;

        AddVectorXYZ(&p2, D_0063C488 + node * 0x10, D_0063C490);

        p2.f[1] = p1.f[1];
        CopyVector(&p3, &p2);
        p3.f[1] = p3.f[1] - d0;

        d1 = getFloorDropAt((char *)&p3, (char *)&pl, D_0063C490);

        if (d1 < 0.0f) {
            dy = d0 + d1;
        }

        if (*(int *)(D_0063C494 + 0x1BC) == 0 || (*(int *)(D_0063C494 + 0x188) & 0xF00000) == 0) {
            Vec16 pl2;

            pl2 = pl;
            pl2.f[3] = 0.0f;

            t = GetYDistanceFromPlane(&pl2, D_0063C490 + 0x90);

            if (!(5.0f < (t < 0.0f ? -t : t))) {
                if (D_0063B21C == 0) {
                    if (10.0f < (dy < 0.0f ? -dy : dy)) {
                        if (dy < 0.0f) {
                            dy = -10.0f;
                        } else {
                            dy = 10.0f;
                        }
                    }
                } else {
                    dy = dy * ((float)D_0063B21C * 0.1f);
                }
            }
        }
        if (*(int *)(D_0063C490 + 0x200) != 0) {
            *(int *)(D_0063C490 + 0x204) = 1;
            if (*(int *)(D_0063B938 + *(int *)(D_0063C490 + 0x364) * 0x40 + 4) == 0x30) {
                if (0.0f < d1) {
                    *(float *)(D_0063C490 + 0x208) = 0.0f;
                    *(float *)(D_0063C490 + 0x20C) = -d1;
                } else {
                    *(float *)(D_0063C490 + 0x208) = d1;
                    *(float *)(D_0063C490 + 0x20C) = 0.0f;
                }
            } else {
                if (0.0f < d1) {
                    *(float *)(D_0063C490 + 0x208) = -d1;
                    *(float *)(D_0063C490 + 0x20C) = 0.0f;
                } else {
                    *(float *)(D_0063C490 + 0x208) = 0.0f;
                    *(float *)(D_0063C490 + 0x20C) = d1;
                }
            }
            if (*(float *)(D_0063C490 + 0x208) <
                -(*(float *)(D_0063B938 + 0x14) * D_0063B900 * 0.5f)) {
                *(float *)(D_0063C490 + 0x208) =
                    -(*(float *)(D_0063B938 + 0x14) * D_0063B900 * 0.5f);
            }
            if (*(float *)(D_0063C490 + 0x20C) <
                -(*(float *)(D_0063B938 + 0x14) * D_0063B900 * 0.5f)) {
                *(float *)(D_0063C490 + 0x20C) =
                    -(*(float *)(D_0063B938 + 0x14) * D_0063B900 * 0.5f);
            }
        }
    }
    *(float *)(D_0063C490 + 4) = *(float *)(D_0063C490 + 4) - dy;
}

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

MotShift rootUpdateXZ_MotPos(int kind, int no)
{
    MotShift ret;
    ClipBuf w;
    Vec16 mv;
    Vec16 step;
    float mtx[16];
    float lim;
    int r;

    ret = D_0063B930[0];
    GetMatrixFromQuaternion(mtx, D_0063C490 + 0x30);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)D_007201F0);
    sceVu0ApplyMatrix((int *)&step, (int)mtx, D_00720200);
    AddVectorXYZ(D_0063C490, D_0063C490, &step);

    if (no != -1) {
        CopyVector(D_0063C490 + 0xD0, D_00720210);
    } else {
        if (*(int *)(D_0063C494 + 0x58) != 0) {
            if (D_0028F4C0[0] == 1) {
                AddVectorXYZ(D_0063C490, D_0063C490, D_0063C490 + 0x90);
            }
        }
        if (*(int *)(D_0063C494 + 0x30) == 21) {
            lim = -(60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10.0f);
            if (*(float *)(D_0063C490 + 0xD4) < lim) {
                *(float *)(D_0063C490 + 0xD4) = lim;
                /* retail links debug_StdPrintfDummy in place of the listing's printf. */
                debug_StdPrintfDummy(D_0061FE80);
            }
        }
        AddVectorXYZ(D_0063C490, D_0063C490, D_0063C490 + 0xD0);
    }

    if (wallCollisionAndFloorFit(D_0063C490, D_0063C490 + 0x150,
                                 *(float *)(D_0063C490 + 0x1D0) + -30.0f) == 0) {
        if (*(int *)(D_0063C494 + 0xD8) != 0) {
            wallCollisionAndFloorFit(D_0063C490, D_0063C490 + 0x150, 5.0f);
        }
    }

    if (*(int *)(D_0063C494 + 0xD4) != 0) {
        if (no != -1 || *(int *)(D_0063C490 + 0x310) != 0) {
            if (getFieldCollision((char *)&w) != 0) {
                CopyVector(D_0063C490 + 0x130, (char *)&w + 0xA0);
                *(float *)(D_0063C490 + 4) = *(float *)((char *)&w + 0x24) + mv.f[1];
                if (no != -1 || *(int *)(D_0063C494 + 0x30) == 75 ||
                    *(int *)(D_0063C494 + 0x30) == 599 || *(int *)(D_0063C494 + 0x30) == 58) {
                    *(int *)(D_0063C494 + 0x188) = GetFloorAttribute((char *)&w);
                    ret = *(MotShift *)((char *)&w + 0x8C);
                } else {
                    *(int *)(D_0063C494 + 0x188) = 0;
                }
            } else {
                *(int *)(D_0063C494 + 0x14) = *(int *)(D_0063C494 + 0x14) | 4;
            }
        } else {
            getFieldCollision((char *)&w);
        }
        r = getFlyFieldCollision((char *)&w);
        switch (r) {
        case 1:
            if (*(float *)(D_0063C4A8 + 0x120) > *(float *)(D_0063C494 + 0x3C)) {
                *(float *)(D_0063C490 + 4) = *(float *)((char *)&w + 0x24) + mv.f[1];
            } else {
                landingFieldAction((char *)&w);
            }
            break;
        case 2:
            markPoolContact((char *)&w);
            break;
        }
    }

    checkCliffAndWallStateAtJump();
    floorFitting(kind);
    *(float *)(D_0063C490 + 0xC0) = D_007201F0[1];
    SubVectorXYZ(D_0063C490 + 0x90, D_0063C490, D_0063C490 + 0x150);
    CopyVector(D_0063C490 + 0x10, ZeroPoint);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
    *(int *)(D_0063C490 + 0x180) = no;
    return ret;
}

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
