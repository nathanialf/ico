#include "include_asm.h"

/* motMan_rootUpdate.c.inc: the motion manager's root update, the wall, floor and water passes; motionManager.c includes this file. */
/* _wallHitReaction's helper */
static inline int getWallSlideDirection(void *dir, void *hit, void *wall) /* derived name */
{
    Vec16 t;

    if (_InnerProduct(hit, wall) < -0.99f) {
        return 0;
    }

    CopyVector(&t, hit);
    t.f[3] = 0.0f;
    GetProjectionOfPlane(dir, &t, wall);
    ((Vec16 *)dir)->f[3] = 0.0f;
    _NormalizeVector(dir, dir);

    return 1;
}

static void _wallHitReaction(ClipWork *w, void *pos, void *last, int noSlide);

INCLUDE_ASM(_wallHitReaction);

/* rootUpdateStepSolution's three helpers; the caller passes the position,
 * the last position, the radius and the fuchi mode */
static inline void clipStepWallAndReact(struct MotRoot *cur, float *last, float rad,
                                        WallCfg *col) /* derived name */
{
    ClipWork w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur->clipFrom);
    }
    CopyVector(w.pt[1], cur->pos);
    w.radius = rad * skelScale;
    w.filter = *col;
    ClipWallE(&w);
    if (w.wall.elem != 0) {
        _wallHitReaction(&w, cur->pos, last, 1);
    }
}

static inline int clipFuchiWallAndReact(struct MotRoot *cur, float *last, int mode,
                                        float rad) /* derived name */
{
    ClipWork w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur->clipFrom);
    }
    CopyVector(w.pt[1], cur->pos);
    w.radius = rad * skelScale;
    ClipWallFuchiHangWalkStop(&w);
    if (w.wall.elem != 0) {
        int attr = GetWallAttribute(&w);

        switch (mode) {
        default:
            return 0;
        case 1:
            if ((attr & 0x20000000) != 0) {
                _wallHitReaction(&w, cur->pos, last, 0);
                return 1;
            }
            break;
        case 2:
            if ((attr & 0x10000000) != 0) {
                _wallHitReaction(&w, cur->pos, last, 0);
                return 1;
            }
            break;
        }
    }
    return 0;
}

static inline int clipFieldWallAndReset(struct MotRoot *cur, float *last) /* derived name */
{
    ClipWork w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur->clipFrom);
    }
    CopyVector(w.pt[1], cur->pos);
    w.filter = InitialColInfo;
    ClipWallField(&w);
    if (w.wall.elem != 0 && CompareAttribute(w.attr, 0x10000) != 0) {
        _wallHitReaction(&w, cur->pos, last, 0);
        return 1;
    }
    return 0;
}

static void _wallCollisionPreProcess(ClipWork *w, void *p, void *q, float dy);

INCLUDE_ASM(_wallCollisionPreProcess);

static inline int wallCollisionAndFloorFit(float *pos, float *last, float dy) /* derived name */
{
    ClipWork w;
    Vec16 t;

    _wallCollisionPreProcess(&w, pos, last, dy);
    if (w.wall.elem != 0) {
        _wallHitReaction(&w, pos, last, 0);
        return 1;
    } else if (w.floor.elem != 0) {
        CopyVector(&t, w.pt[2]);
        t.f[1] = t.f[1] - dy;
        CopyVector(pos, &t);
        CopyVector(last, &t);
        return 1;
    }
    return 0;
}

/* dy is the caller's constant */
static inline void wallCollisionAndReact(float dy) /* derived name */
{
    ClipWork w;
    struct MotRoot *g = skelRoot;
    float *last = g->last;

    _wallCollisionPreProcess(&w, g->pos, last, dy);
    if (w.wall.elem != 0) {
        _wallHitReaction(&w, g->pos, last, 0);
    }
}

/* The wave-force twin of _wallCollisionPreProcess: the same work-block head,
 * then ClipWallWaveForce and the horizontal push it reports.  rootUpdateSwim
 * uses it. */
static inline void waveForceReaction(struct MotRoot *cur, float *last, float dy) /* derived name */
{
    ClipWork w;
    float d;
    float k;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur->clipFrom);
    }
    CopyVector(w.pt[1], cur->pos);
    w.filter = skelRoot->filter;
    w.pt[0][1] = w.pt[0][1] + dy;
    w.pt[1][1] = w.pt[1][1] + dy;
    w.radius = skelRoot->radius + 200.0f;
    CopyVector(w.pt[1], &w);
    ClipWallWaveForce(&w);
    if (w.wall.elem != 0) {
        d = GetDistanceFromPlane(&w.normal, &w);
        d = d + w.radius;
        if (d > 0.0f) {
            k = 1.0f / (d + 50.0f);
            /* the wall normal read through Vec16, as motionOrientManager.c
             * writes vector components */
            cur->pos[0] = cur->pos[0] + ((Vec16 *)&w.normal)->f[0] * 100.0f * k;
            cur->pos[2] = cur->pos[2] + ((Vec16 *)&w.normal)->f[2] * 100.0f * k;
            skelMotCtrl->flags |= 0x2000;
        }
    }
}

/* getFieldCollision's two helpers */
static inline void setPoolHeightOfFloor(ClipWork *w) /* derived name */
{
    /* &w->floor is the floor's owning object: ico2/sugipon/src/box.c reads the
     * same word of the same work block as `char **`. */
    GObj *obj = w->floor.o.obj;

    skelMotCtrl->pool = obj;
    skelMotCtrl->waterY = GetPoolGlobalHeight(obj);
    skelMotCtrl->waterDepth = w->pt[2][1] - skelMotCtrl->waterY;
}

static inline void checkPoolFloor(ClipWork *w) /* derived name */
{
    int attr = GetFloorAttribute(w);

    if (CompareAttribute(attr, 0x50) != 0) {
        if (w->pt[2][1] - skelRoot->pos[1] < skelRoot->projHeight) {
            setPoolHeightOfFloor(w);
        }
    }
}

INCLUDE_ASM(getFieldCollision);

/* setIKAndAdjustRootHeight's two helpers */

/* "PLANE<EUC-JP riMItto desu> %f <EUC-JP abunai node rakka sasemasu>\n":
 * the plane limit was exceeded, so the actor is dropped. */

/* Builds the plane the root height is measured against out of the floor plane
 * the motion block carries, and reports whether the floor was steep enough to
 * need one. */
static inline int makeRootFitPlane(float *pl, struct MotRoot *o) /* derived name */
{
    float *fl = o->plane.f;
    Vec16 pos;
    Vec16 n;
    int ret = 0;

    CopyVector(pl, fl);
    if (-0.3f < fl[1]) {
        CopyVector(&pos, o->pos);
        pos.f[1] = GetYProjectionOfPlane(fl, o->pos);

        pl[1] = 0.0f;
        _NormalizeVector(&n, pl);
        _ScaleVectorXYZ(pl, &n, _Sqrt(0.90999997f));
        pl[1] = -0.3f;

        pl[0] = 0.0f;
        pl[1] = -1.0f;
        pl[2] = 0.0f;
        pl[3] = -_InnerProduct(pl, &pos);
        ret = 1;
    }
    return ret;
}

/* Drops a probe from v onto the floor and returns how far the root has to move
 * to sit on it. */
static inline float getFloorDropAt(float *v, float *pl, float *o) /* derived name */
{
    ClipWork w;
    float d;

    CopyVector(&w, v);
    CopyVector(w.pt[1], v);
    w.pt[0][1] = w.pt[0][1] - 100.0f;
    w.pt[1][1] = w.pt[1][1] + 500.0f;
    ClipFloor(&w);
    if (w.floor.elem != 0) {
        d = -(w.pt[2][1] - v[1]);
    } else {
        d = 3.40282347e+38f;
    }

    if (w.floor.elem != 0) {
        float t = GetYProjectionOfPlane(w.normal.f, o) - GetYProjectionOfPlane(pl, o);

        if (45.0f < (t < 0.0f ? -t : t)) {
            d = GetYDistanceFromPlane(pl, v);
        }
    } else {
        d = GetYDistanceFromPlane(pl, v);
    }
    return d;
}

INCLUDE_ASM(setIKAndAdjustRootHeight);

/* shared by rootUpdateFly and rootUpdateEnemyFly */
static inline int getFlyFieldCollision(ClipWork *w) /* derived name */
{
    float y;

    y = skelMotDef->landFrame;
    if (y < -0.5f) {
        return 0;
    }
    w->radius = 0.0f;
    CopyVector(w, skelRoot->pos);
    w->pt[0][1] = skelRoot->clipFrom[1];
    CopyVector(w->pt[1], skelRoot->pos);
    w->pt[1][1] = w->pt[1][1] + 10000.0f;
    ClipFloor(w);
    return CheckFieldContact(w, (GObj *)skelGObj, skelRoot->pos, skelRoot->projHeight);
}

/* landingFieldAction's helper */
static inline void adjustRootByLandingPlane(Vec16 *plane, float rate) /* derived name */
{
    Vec16 push;
    Vec16 half;
    Vec16 pl;
    float d;

    CopyVector(&pl, plane);
    pl.f[3] = 0.0f;
    d = plane_distance(skelRoot->move, &pl);
    if (d < 0.0f) {
        _ScaleVector(&push, &pl, d);
        push.f[3] = 0.0f;
        _SubVector(&half, skelRoot->move, &push);
        half.f[3] = 0.0f;
        half.f[1] = 0.0f;
        _ScaleVectorXYZ(&half, &half, rate);
        _SubVectorXYZ(skelRoot->last, skelRoot->pos, &half);
    }
}

INCLUDE_ASM(landingFieldAction);

/* shared by rootUpdateFly and rootUpdateEnemyFly */
static inline void markPoolContact(ClipWork *w) /* derived name */
{
    skelMotCtrl->flags |= 0x400;
    setPoolHeightOfFloor(w);
}

static void floorFitting(int kind)
{
    Vec16 plane;
    Vec16 dir;
    float mtx[16];
    short ang;

    if (kind == 0x11 || kind == 0x14) {
        plane = skelRoot->plane;
        GetMatrixFromQuaternion(mtx, skelRoot->quat);
        _ApplyMatrix(&dir, mtx, ZUnitVector);
        plane.f[3] = 0.0f;
        floorSlope[1] = GetYDistanceFromPlane(plane.f, dir.f);
        floorSlope[2] = 1.0f;
        _NormalizeVector(floorSlope, floorSlope);
        ang = GetTableArcTan2(floorSlope[1], floorSlope[2]);
        RotQuaternionX(skelRoot->quat, ang);
        skelRoot->lifting = 0;
    }
}

/* rootUpdateXZ's helper */
static inline int getFloorAttributeUnderNode(void) /* derived name */
{
    ClipWork w;
    int node;

    memset(&w, 0, 0xC0);
    node = GetSkeltonFocusNode((GObj *)skelGObj, 51);
    _AddVectorXYZ(&w, skelRoot->pos, nodePos2 + node * 16);
    CopyVector(w.pt[1], &w);
    w.pt[0][1] = w.pt[0][1] - 50.0f;
    w.pt[1][1] = w.pt[1][1] + 50.0f;
    ClipFloor(&w);
    if (w.floor.elem != 0) {
        return GetFloorAttribute(&w);
    }
    return -1;
}

/* the wall pass after a horizontal move, used three times by rootUpdateXZ;
 * rootUpdateXZ_MotPos writes it out */
#define WALL_COLLISION_AND_WAVE_FORCE() /* derived name */                                         \
    if (wallCollisionAndFloorFit(skelRoot->pos, skelRoot->last, skelRoot->projHeight + -30.0f) ==  \
        0) {                                                                                       \
        if (skelMotCtrl->wallReact != 0) {                                                         \
            wallCollisionAndFloorFit(skelRoot->pos, skelRoot->last, 5.0f);                         \
        }                                                                                          \
    }                                                                                              \
    if (skelMotCtrl->wallReact != 0) {                                                             \
        waveForceReaction(skelRoot, skelRoot->last, 0.0f);                                         \
    }

INCLUDE_ASM(rootUpdateXZ);

INCLUDE_ASM(rootUpdateXZ_MotPos);

static int adjustSideWall(ClipWork *w, int nearTest, Vec16 *wallPlane)
{
    WallCfg cfg = {w->wall.o, w->wall.elem};
    Vec16 pl0;
    Vec16 pl1;
    float pts[16];
    Vec16 push;
    float d;
    float t;

    GetPureVerticalPlane(&pl0, &pl1, pts, &cfg, 0);
    d = (GetDistanceFromPlane(&pl0, w->pt[2]) < 0.0f ? -GetDistanceFromPlane(&pl0, w->pt[2])
                                                     : GetDistanceFromPlane(&pl0, w->pt[2])) -
        30.0f;
    if (nearTest != 0) {
        if ((d < 0.0f ? -d : d) < 30.0f) {
            return 1;
        }
    }
    t = sceVu0InnerProduct(wallPlane, &pl1);
    if ((t < 0.0f ? -t : t) < 0.8f) {
        CopyVector(&push, &pl1);
        push.f[3] = 0.0f;
        sceVu0ScaleVectorXYZ(&push, &push, GetDistanceFromPlane(&pl1, skelRoot->pos) - 30.0f);
        SubVectorXYZ(skelRoot->pos, skelRoot->pos, &push);
    }
    return 0;
}

static int checkSideWall(float *probe, float *mtx, ClipWork *p, ClipWork *base, Vec16 *wallPlane)
{
    int flag;
    int mag;
    int mask;

    p->radius = 0.0f;
    CopyVector(p, base);
    sceVu0ApplyMatrix(p->pt[1], mtx, probe);
    ClipWall(p);

    if (p->wall.elem != 0) {
        goto disp_one;
    }
    if (skelRoot->fuchiMode != 0) {
        ClipWallFuchiHangWalkStop(p);
        if (p->wall.elem != 0) {
            flag = 0;
            mag = GetWallAttribute(p);
            switch (skelRoot->fuchiMode) {
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
                return adjustSideWall(p, 0, wallPlane);
            }
        }
    }
    CopyVector(p, (void *)p->pt[1]);
    CopyVector((void *)p->pt[1], base->pt[1]);
    ClipWall(p);
    if (p->wall.elem != 0) {
    disp_one:
        return adjustSideWall(p, 1, wallPlane);
    }
    return 0;
}

static void forceFallDown(void)
{
    iosOmSendMail((GObj *)skelGObj, 24, (void *)skelGObj);
    CopyVector(skelRoot->last, skelRoot->pos);
}

INCLUDE_ASM(forceReset);

static void checkWallUpperWall(void)
{
    float (*v)[4];
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    {
        register float *p = skelRoot->pos;
        MatrixDrive_TransMatrix(p[0], p[1] - rootMove[1], p[2]);
    }
    MultiMatrixByQuaternion(skelRoot->quat);
    checkUpperWallState();
    MatrixDrive_PopMatrix();
}

/* rootUpdateHang's helper */
static inline void dropWhenFloorTooFar(void) /* derived name */
{
    ClipWork w;

    if (0.0f <= plane_distance(skelRoot->pos, &skelRoot->plane)) {
        return;
    }
    CopyVector(&w, skelRoot->pos);
    CopyVector(w.pt[1], &w);
    w.pt[1][1] = w.pt[1][1] + 50.0f;
    ClipFloor(&w);
    if (w.floor.elem != 0) {
        if ((GetFloorAttribute(&w) & 0x800000) == 0 && w.pt[2][1] - w.pt[0][1] < 50.0f) {
            forceFallDown();
        }
    }
}

INCLUDE_ASM(calcWallFittingGeometry);

static ObjNode rootUpdateHang(int kind, int hand1Pt, int hand0Pt)
{
    Vec16 mv;
    float mtx[16];
    Vec16 pl;
    Vec16 pl2;
    ClipWork w;
    float mtx2[16];
    Vec16 pos;
    int hit;

    GetMatrixFromQuaternion(mtx, skelRoot->quat);
    sceVu0ApplyMatrix(&mv, mtx, rootStep);
    AddVectorXYZ(skelRoot->pos, skelRoot->pos, &mv);
    skelRoot->height = rootMove[1];
    hit = 0;
    CopyVector(&pos, skelRoot->pos);
    pos.f[1] = pos.f[1] - (rootMove[1] - 30.0f);
    MatrixDrive_PushMatrix();
    GetMatrixFromQuaternionPos((void *)MatrixDrive_GetMatrix(), skelRoot->quat, &pos);
    MatrixDrive_TransMatrix(0.0f, 0.0f, -rootMove[2] - 10.0f);
    CopyMatrix(mtx2, (void *)MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    sceVu0ApplyMatrix(&w, mtx2, hangBack);
    sceVu0ApplyMatrix(w.pt[1], mtx2, hangFront);
    w.radius = 0.0f;

    /* the work records, in a block of their own */
    {
        int n;
        int attr;

        if (skelMotCtrl->updateModeChanged == 0) {
            ClipWall(&w);
            if (w.wall.elem != 0) {
                WallCfg rec = {w.wall.o, w.wall.elem};

                n = GetPureVerticalPlaneOfCurrentPosition(&skelRoot->plane, &pl, 0, &rec, 0,
                                                          skelRoot->pos);
                if (-0.25f < skelRoot->plane.f[1]) {
                    /* EUC-JP: "the wall angle is steep, so fall" */
                    debug_StdPrintfDummy("壁の角度が急なので落下\n");
                    forceFallDown();
                    goto out;
                }
                CopyVector(&pl2, &pl);
                if (skelRoot->wall.o.obj == rec.o.obj && skelRoot->wall.o.node == rec.o.node &&
                    skelRoot->wall.elem == rec.elem) {
                    hit = skelRoot->wallCount == n;
                }
                skelRoot->wall = rec;
                skelRoot->wallCount = n;
                skelMotCtrl->wallAttr = attr = GetWallAttribute(&w);
                if (attr == 768) {
                    forceFallDown();
                    /* EUC-JP: "fall by the wall attribute" */
                    debug_StdPrintfDummy("壁属性により落下\n");
                    goto out;
                }
            } else {
                /* EUC-JP: "no wall, so fall" */
                debug_StdPrintfDummy("壁がなくて落下\n");
                forceFallDown();
                goto out;
            }
        } else {
            skelMotCtrl->updateModeChanged = 0;
            GetPureVerticalPlane(&skelRoot->plane, &pl, 0, &skelRoot->wall, 0);
            hit = 1;
            CopyVector(&pl2, &pl);
        }

        {
            Vec16 v;
            Vec16 sc;
            ClipWork sw1;
            ClipWork sw2;
            Vec16 dv;
            int r1;
            int r2;
            float d;
            float dd;

            pl2.f[3] = 0.0f;
            CopyVector(&v, skelRoot->pos);
            v.f[1] = v.f[1] - rootMove[1];
            d = GetDistanceFromPlane(&skelRoot->plane, &v);
            if (hit == 0) {
                if (d < 0.0f ? 30.0f < -d : 30.0f < d) {
                    /* EUC-JP: "no hold point on the wall, so fall (step: %f)" */
                    debug_StdPrintfDummy("壁のつかまり先がなくて落下 (段差:%f)\n", fptodp(d));
                    forceFallDown();
                    goto out;
                }
            }
            dd = -d;
            sceVu0ScaleVector(&sc, &skelRoot->plane, dd);
            AddVectorXYZ(&v, &v, &sc);
            d = GetDistanceFromPlane(&pl, &v);
            sceVu0ScaleVector(&sc, &pl, -d - rootMove[2]);
            AddVectorXYZ(&v, &v, &sc);
            CopyVector(skelRoot->pos, &v);
            CopyVector(skelRoot->footPos, skelRoot->pos);
            skelRoot->pos[1] = skelRoot->pos[1] + rootMove[1];

            r1 = checkSideWall(hangLeft, mtx2, &sw1, &w, &pl2);
            r2 = checkSideWall(hangRight, mtx2, &sw2, &w, &pl2);
            if (r1 == -1 || r2 == -1) {
                /* EUC-JP: "hit a forced-fall wall, so fall" */
                debug_StdPrintfDummy("強制落下の壁に当たったので落下\n");
                forceFallDown();
                goto out;
            }
            if (r1 != 0 && r2 != 0) {
                sceVu0SubVector(&dv, sw2.pt[2], sw1.pt[2]);
                sceVu0OuterProduct(skelMotCtrl->dir, &dv, YUnitVector);
                skelMotCtrl->dir[1] = 0.0f;
                sceVu0Normalize(skelMotCtrl->dir, skelMotCtrl->dir);
            } else {
                CopyVector(skelMotCtrl->dir, &pl2);
                skelMotCtrl->dir[0] = -skelMotCtrl->dir[0];
                skelMotCtrl->dir[2] = -skelMotCtrl->dir[2];
            }
        }
    }

    checkWallUpperWall();
    dropWhenFloorTooFar();
    wallCollisionAndFloorFit(skelRoot->pos, skelRoot->last, 0.0f);

out:
    CopyVector(skelRoot->trans, ZeroPoint);
    if (kind == 15) {
        calcWallFittingGeometry();
    }
    SubVectorXYZ(skelRoot->move, skelRoot->pos, skelRoot->last);
    CopyVector(skelRoot->last, skelRoot->pos);
    CopyVector(skelRoot->delta, rootDelta);
    skelRoot->standNode = -1;
    return skelRoot->wall.o;
}

INCLUDE_ASM(rootUpdateSwim);

/* shared by rootUpdateStepSolution and rootUpdateY */
static inline void clipWallAhead(ClipWork *w) /* derived name */
{
    float mtx[16];

    GetMatrixFromQuaternionPos(mtx, skelRoot->quat, skelRoot->pos);
    sceVu0ApplyMatrix(w, mtx, clipWallBack);
    sceVu0ApplyMatrix(w->pt[1], mtx, clipWallFront);
    w->radius = 0.0f;
    ClipWall(w);
}

/* avoidSideAdjustWall's two helpers */
static inline int clipSideWallAndHit(ClipWork *w) /* derived name */
{
    int hit = 1;

    ClipWallAdjustPos(w);

    return w->wall.elem != 0 ? hit : 0;
}

static inline void pushRootAlongSideWall(ClipWork *w) /* derived name */
{
    Vec16 t;

    _ScaleVectorXYZ(&t, &w->normal, 40.0f);
    _AddVectorXYZ(&t, (w->pt[2]), &t);
    _SubVectorXYZ(&t, &t, skelRoot->pos);
    _ScaleVectorXYZ(&t, &t, 0.07f);
    _AddVectorXYZ(skelRoot->pos, skelRoot->pos, &t);
}

static int avoidSideAdjustWall(void)
{
    float mtx[16];
    /* a 0xD0-byte block, cleared to the clip request's 0xC0 */
    char w[208];

    memset(w, 0, 0xC0);
    GetMatrixFromQuaternionPos(mtx, skelRoot->quat, skelRoot->pos);
    _ApplyMatrix(w, mtx, avoidLeft);
    _ApplyMatrix(w + 0x10, mtx, avoidRight);
    if (clipSideWallAndHit(w) == 0) {
        _ApplyMatrix(w, mtx, avoidRight);
        _ApplyMatrix(w + 0x10, mtx, avoidLeft);
        if (clipSideWallAndHit(w) == 0) {
            return 0;
        }
    }
    pushRootAlongSideWall(w);
    return 1;
}

INCLUDE_ASM(rootUpdateStepSolution);

static ObjNode rootUpdateTrueMotion(int kind)
{
    float mtx[16];
    Vec16 v;
    int noMove = kind;

    GetMatrixFromQuaternion(mtx, skelRoot->quat);
    if (noMove == 0) {
        sceVu0ApplyMatrix(&v, mtx, rootMove);
        v.f[1] = v.f[1] + skelNode->pos[1];
        v.f[0] = v.f[2] = 0.0f;
        CopyVector(skelRoot->trans, &v);
    } else {
        CopyVector(skelRoot->trans, ZeroPoint);
    }
    skelRoot->standNode = -1;
    skelRoot->height = 0.0f;
    CopyVector(skelRoot->delta, rootDelta);
    return InitialObjPointer;
}

static ObjNode rootUpdateDirectPlayForStream(void)
{
    float *p;

    SetIdentityQuaternion(skelRoot->quat);
    RotQuaternionY(skelRoot->quat, -32768);
    CopyVector(skelRoot->pos, rootMove);
    p = skelRoot->pos;
    p[0] = -p[0];
    p[2] = -p[2];
    CopyVector(skelRoot->last, skelRoot->pos);
    CopyVector(skelRoot->move, ZeroVector);
    CopyVector(skelRoot->trans, ZeroVector);
    skelRoot->standNode = -1;
    skelRoot->height = 0.0f;
    AdjustMotionHeightToNearestField((GObj *)skelGObj);
    CopyVector(skelRoot->delta, rootDelta);
    return InitialObjPointer;
}

INCLUDE_ASM(rootUpdateDirectPlay);

INCLUDE_ASM(keepVerticalZWithQ_267);

INCLUDE_ASM(rootUpdateNodeFix);

static ObjNode rootUpdateY(void)
{
    Vec16 mv;
    Vec16 mv2;
    float mtx[16];
    float plane[4];
    float vp[4];
    Vec16 corner[4];
    Vec16 center;
    Vec16 pos;
    Vec16 push;
    ClipWork w;
    ClipWork cw;
    float d;
    int i;

    GetMatrixFromQuaternion(mtx, skelRoot->quat);
    sceVu0ApplyMatrix(&mv, mtx, rootMove);
    sceVu0ApplyMatrix(&mv2, mtx, rootStep);

    CopyVector(skelRoot->move, &mv2);
    sceVu0AddVector(skelRoot->pos, skelRoot->pos, skelRoot->move);
    CopyVector(skelRoot->footPos, skelRoot->pos);

    GetPureVerticalPlane(0, vp, (float *)corner, &skelRoot->wall, 0);
    CopyVector(plane, vp);
    plane[3] = 0.0f;

    memset(&center, 0, 16);
    center.f[3] = 1.0f;
    for (i = 0; i < 4; i++) {
        AddVectorXYZ(&center, &center, &corner[i]);
    }
    sceVu0ScaleVector(&center, &center, 0.25f);
    skelRoot->pos[0] = center.f[0];
    skelRoot->pos[2] = center.f[2];
    skelRoot->pos[0] = skelRoot->pos[0] + mv.f[0];
    skelRoot->pos[2] = skelRoot->pos[2] + mv.f[2];

    CopyVector(&pos, skelRoot->pos);
    pos.f[1] = pos.f[1] - rootMove[1];
    d = GetDistanceFromPlane(vp, &pos);
    sceVu0ScaleVector(&push, vp, -d - rootMove[2]);
    AddVectorXYZ(&pos, &pos, &push);
    pos.f[3] = 1.0f;
    CopyVector(skelRoot->pos, &pos);
    skelRoot->pos[1] = skelRoot->pos[1] + rootMove[1];
    sceVu0ScaleVectorXYZ(skelMotCtrl->dir, plane, -1.0f);

    if (skelRoot->stairStep != 0) {
        float t = skelRoot->pos[1] - mv.f[1];
        float e;

        t = t - (float)((int)(t / 50.0f) * 50);
        if (t < 0.0f) {
            t = t + 50.0f;
        }
        if (t > 25.0f) {
            e = 50.0f - t;
            skelRoot->pos[1] = skelRoot->pos[1] + e;
        } else {
            skelRoot->pos[1] = skelRoot->pos[1] - t;
        }
    }

    getFieldCollision(&w);
    CopyVector(&skelRoot->plane, &w.normal);
    clipWallAhead(&cw);
    if (cw.wall.elem != 0) {
        WallCfg rec = {cw.wall.o, cw.wall.elem};

        skelRoot->aheadWall = rec;
    }

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(skelRoot->pos[0], skelRoot->pos[1] + 100.0f, skelRoot->pos[2]);
    MultiMatrixByQuaternion(skelRoot->quat);
    checkWallState(2);
    MatrixDrive_PopMatrix();

    CopyVector(skelRoot->last, skelRoot->pos);
    CopyVector(skelRoot->delta, rootDelta);
    CopyVector(skelRoot->trans, ZeroVector);
    skelRoot->standNode = -1;
    return skelRoot->wall.o;
}

/* the parameter is unused */
static ObjNode rootUpdateY_Rope(int actPt)
{
    Vec16 v;
    Vec16 cur;
    float save;

    CopyVector(skelRoot->footPos, skelRoot->pos);
    if (skelRoot->ropeState != 0) {
        int node = GetSkeltonFocusNode((GObj *)skelGObj, 22);

        v.f[0] = skelRoot->pos[0];
        v.f[1] = skelRoot->pos[1];
        v.f[2] = skelRoot->pos[2];
        _SubVector(skelRoot->pos, skelRoot->holdPoint, nodePos2 + node * 16);
        if (skelRoot->ropeState < 0) {
            _InterGV(skelRoot->pos, v.f, skelRoot->pos, 1.0f, 2.0f);
        }
    }
    save = skelRoot->radius;
    CopyVector(&cur, skelRoot->pos);
    CopyVector(&v, skelRoot->last);
    skelRoot->radius = 60.0f;
    wallCollisionAndFloorFit(cur.f, v.f, 5.0f);
    skelRoot->radius = save;
    skelMotCtrl->fallHeight = 0.0f;
    skelRoot->height = 0.0f;
    SubVectorXYZ(skelRoot->move, skelRoot->pos, skelRoot->last);
    CopyVector(skelRoot->trans, ZeroPoint);
    CopyVector(skelRoot->footPos, skelRoot->pos);
    AddVectorXYZ(skelRoot->footPos, skelRoot->footPos, skelRoot->delta);
    CopyVector(skelRoot->last, skelRoot->pos);
    skelRoot->standNode = -1;
    return InitialObjPointer;
}

INCLUDE_ASM(rootUpdateFly);

INCLUDE_ASM(rootUpdateEnemyFly);
