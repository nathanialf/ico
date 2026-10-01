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
/* kept local: this TU's uses of these do not fit the prototypes in
 * fieldCollision.h / math.h. */
extern void GetWallGlobalInfo(int a0, void *v, int a2, char *node);
extern float atan2f(float y, float x);
/* kept local: this TU's uses of ZeroPoint do not fit the prototype in matrixDrive.h */
extern char ZeroPoint[];
/* kept local: this TU does not include fieldCollision.h (its prototypes
   conflict here) and reads the pair as its own MotShift */
extern MotShift InitialObjPointer;
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *elem, void *base, void *v, float a, float b);
extern void _wallHitReaction(char *w, void *p, void *q, int flag);
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
/* kept local: this TU's uses of MultiQuaternion do not fit the prototype in quaternion.h */
extern void MultiQuaternion(void *p0, void *p1, void *p2);
extern void ClipWallAdjustPos(void *a0);
extern void ClipWallE(void *a0);
extern void CopyQuaternion(void *a0, void *a1);
extern void GetRootQuaternion(void *q, void *obj);
/* the two ints the demo timer keeps: the elapsed count and its divisor. */
/* kept local: main.c's global; this TU does not include main.h */
extern int systemStatus[];
extern int GetPureVerticalPlaneOfCurrentPosition(void *plane0, void *plane1, float *ptsIn, int *cfg,
                                                 int flip, char *self);
extern void sceVu0OuterProduct(void *dst, void *a, void *b);
extern WallCfg InitialColInfo;
/* kept local, as ico2/sugipon/src/box.c declares them: fieldCollision.h is
 * not included here. */
extern void GetLowerPlaneCollision(void *work, void *pos);
extern int GetWaterReaction(void *w, int *hit, void *plane, void *pos, void *vel, float low,
                            float mid, float high, float k, float acc);
/* kept local: void like this TU's other clip entries (the result is never read). */
extern void ClipWallWaveForce(void *a0);

/* 12-byte plane record copied out of the motion work block. */
typedef struct {
    int b[3];
} FieldBlk12;

extern int ClipWallEField(void *a0);
/* kept local: this TU's uses of these do not fit the prototypes in
 * fieldCollision.h / geometryManager.h. */
extern float GetDistanceFromPlane(void *plane, void *pos);
extern float GetProjectionOfPlane(void *out, void *plane, void *pos);
/* motionManager2's debug draws read the three words of a WallCfg through
 * their first argument. */
extern void DebugDisp1Collision(void *hit);
extern void DebugDisp1CollisionWithColor(void *hit, void *colour);

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * _wallHitReaction (rows 31-41, above its def line 51), so it carries no
 * symbol in MAIN.MAP. */
static inline int getWallSlideDirection(void *dir, void *hit, void *wall)
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

void _wallHitReaction(char *w, void *pos, void *last, int noSlide)
{
    Vec16 mv;
    Vec16 nrm;
    Vec16 pen;
    Vec16 pl;
    Vec16 slide;
    float d;

    SubVectorXYZ(&mv, w + 0x10, w + 0x20);
    SubVectorXYZ(pos, pos, &mv);
    GetOrientOfWall(&nrm, *(void **)(w + 0x88), w + 0x80);
    *(int *)(skelMotCtrl + 0x14) = *(int *)(skelMotCtrl + 0x14) | 2;

    CopyVector(&pl, &nrm);
    pl.f[3] = -sceVu0InnerProduct(pos, &nrm);
    d = GetDistanceFromPlane(&pl, last);
    sceVu0ScaleVector(&pen, &nrm, d);
    sceVu0SubVector(last, last, &pen);

    d = GetDistanceFromPlane(w + 0xA0, w + 0x10);
    sceVu0ScaleVector(&pen, &nrm, d);
    sceVu0SubVector(&slide, &mv, &pen);

    if (noSlide == 0) {
        ClipBuf cw = {{0}, *(float *)(w + 0x70)};

        CopyVector(&cw, pos);
        _AddVectorXYZ((int)&cw + 0x10, (int)pos, &slide);

        *(WallObj *)((char *)&cw + 0x74) = *(WallObj *)(w + 0x80);
        *(void **)((char *)&cw + 0x7C) = *(void **)(w + 0x88);
        if (*(int *)(skelRoot + 0x320) != 0) {
            ClipWallEField(&cw);
        } else {
            ClipWallE(&cw);
        }
        if (debug_wallhitcoldisp != 0) {
            /* An initialised record whose address is taken: gcc fills a
               temporary a member at a time and copies it whole, the two
               copies the listing puts on this one row. */
            WallCfg disp = {((WallCfg *)(w + 0x80))->o, ((WallCfg *)(w + 0x80))->n};

            DebugDisp1Collision(&disp);
        }
        if (*(int *)((char *)&cw + 0x88) != 0) {
            Vec16 prj;

            GetProjectionOfPlane(&prj, (char *)&cw + 0xA0, (char *)&cw + 0x10);
            d = GetDistanceFromPlane(w + 0xA0, &prj);
            if (d < 0.0f) {
                Vec16 dir;

                if (getWallSlideDirection(&dir, w + 0xA0, (char *)&cw + 0xA0) != 0) {
                    Vec16 step;

                    _SubVectorXYZ(&step, (char *)&cw + 0x10, (char *)&cw + 0x20);
                    GetProjectionOfPlane(&step, &dir, &step);
                    _AddVectorXYZ((int)pos, (int)&cw + 0x20, &step);
                } else {
                    ClipBuf cw2;
                    Vec16 push;

                    memset(&cw2, 0, 0xC0);
                    _NormalizeVector(&push, &slide);
                    _ScaleVectorXYZ(&push, &push, 100.0f);
                    CopyVector(&cw2, pos);
                    _AddVectorXYZ((int)&cw2 + 0x10, (int)pos, &push);
                    ClipWall(&cw2);
                    _AddVectorXYZ((int)pos, (int)pos, &slide);
                    if (debug_wallhitcoldisp != 0) {
                        DrawCollisionRay(&cw2);
                    }
                    if (*(int *)((char *)&cw2 + 0x88) != 0) {
                        Vec16 hp;

                        *(float *)((char *)&cw2 + 0xAC) =
                            *(float *)((char *)&cw2 + 0xAC) - (*(float *)(w + 0x70) + 1.0f);
                        if (GetProjectionOfPlane(&hp, (char *)&cw2 + 0xA0, pos) < 0.0f) {
                            CopyVector(pos, &hp);
                            if (debug_wallhitcoldisp != 0) {
                                WallCfg disp = {((WallCfg *)((char *)&cw2 + 0x80))->o,
                                                ((WallCfg *)((char *)&cw2 + 0x80))->n};

                                DebugDisp1CollisionWithColor(&disp, wallHitColor);
                            }
                        }
                    }
                }
            } else {
                CopyVector(pos, &prj);
            }
            if (debug_wallhitcoldisp != 0) {
                WallCfg disp = {((WallCfg *)((char *)&cw + 0x80))->o,
                                ((WallCfg *)((char *)&cw + 0x80))->n};

                DebugDisp1CollisionWithColor(&disp, wallHitColor2);
            }
        } else {
            _AddVectorXYZ((int)pos, (int)pos, &slide);
        }
    } else {
        _AddVectorXYZ((int)pos, (int)pos, &slide);
    }
}

/* RECONSTRUCTED NAMES: the PAL listing shows these three bodies only inlined
 * into rootUpdateStepSolution (rows 163-205, 213-241 and 247-258, between
 * _wallHitReaction and _wallCollisionPreProcess), so none of them carries a
 * symbol in MAIN.MAP.  The caller passes the position, the last position, the
 * radius and the fuchi mode: rows 163 and 213 hold their copies, as row 306
 * holds wallCollisionAndFloorFit's. */
static inline void clipStepWallAndReact(char *cur, char *last, float rad, WallCfg *col)
{
    ClipBuf w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur + 0x160);
    }
    CopyVector((char *)&w + 0x10, cur);
    w.rad = rad * skelScale;
    w.filter = *col;
    ClipWallE(&w);
    if (*(int *)((char *)&w + 0x88) != 0) {
        _wallHitReaction((char *)&w, cur, last, 1);
    }
}

static inline int clipFuchiWallAndReact(char *cur, char *last, int mode, float rad)
{
    ClipBuf w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur + 0x160);
    }
    CopyVector((char *)&w + 0x10, cur);
    w.rad = rad * skelScale;
    ClipWallFuchiHangWalkStop(&w);
    if (*(int *)((char *)&w + 0x88) != 0) {
        int attr = GetWallAttribute(&w);

        switch (mode) {
        default:
            return 0;
        case 1:
            if ((attr & 0x20000000) != 0) {
                _wallHitReaction((char *)&w, cur, last, 0);
                return 1;
            }
            break;
        case 2:
            if ((attr & 0x10000000) != 0) {
                _wallHitReaction((char *)&w, cur, last, 0);
                return 1;
            }
            break;
        }
    }
    return 0;
}

static inline int clipFieldWallAndReset(char *cur, char *last)
{
    ClipBuf w;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur + 0x160);
    }
    CopyVector((char *)&w + 0x10, cur);
    w.filter = InitialColInfo;
    ClipWallField(&w);
    if (*(int *)((char *)&w + 0x88) != 0 &&
        CompareAttribute(*(int *)((char *)&w + 0x98), 0x10000) != 0) {
        _wallHitReaction((char *)&w, cur, last, 0);
        return 1;
    }
    return 0;
}

void _wallCollisionPreProcess(char *w, void *p, void *q, float dy)
{
    Vec16 save;
    float r;

    if (debug_col_old_proc != 0) {
        CopyVector(w, q);
    } else {
        CopyVector(w, skelRoot + 0x160);
    }
    CopyVector(w + 0x10, p);
    *(FieldBlk12 *)(w + 0x74) = *(FieldBlk12 *)(skelRoot + 0x120);
    *(float *)(w + 4) = *(float *)(w + 4) + dy;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + dy;
    if (*(int *)(skelRoot + 0x320) != 0) {
        r = *(float *)(skelRoot + 0x338);
        if (r < 20.0f) {
            *(float *)(w + 0x70) = skelScale * 20.0f;
        } else {
            *(float *)(w + 0x70) = r * skelScale;
        }
        ClipWallField(w);
    } else {
        *(float *)(w + 0x70) = *(float *)(skelRoot + 0x338) * skelScale;
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
        _wallHitReaction((char *)&w, cur, last, 0);
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
    char *g = skelRoot;
    char *last = g + 0x150;

    _wallCollisionPreProcess((char *)&w, g, last, dy);
    if (*(int *)((char *)&w + 0x88) != 0) {
        _wallHitReaction((char *)&w, g, last, 0);
    }
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateSwim (rows 342-363, between wallCollisionAndReact's 331-335 and
 * upperFieldCheck's 370), so it carries no symbol in MAIN.MAP.  It is the
 * wave-force twin of _wallCollisionPreProcess: the same work-block head, then
 * ClipWallWaveForce and the horizontal push it reports.  Row 342 holds the
 * copy of dy, the caller's constant. */
static inline void waveForceReaction(char *cur, char *last, float dy)
{
    ClipBuf w;
    float d;
    float k;

    if (debug_col_old_proc != 0) {
        CopyVector(&w, last);
    } else {
        CopyVector(&w, cur + 0x160);
    }
    CopyVector((char *)&w + 0x10, cur);
    *(FieldBlk12 *)((char *)&w + 0x74) = *(FieldBlk12 *)(skelRoot + 0x120);
    *(float *)((char *)&w + 4) = *(float *)((char *)&w + 4) + dy;
    *(float *)((char *)&w + 0x14) = *(float *)((char *)&w + 0x14) + dy;
    w.rad = *(float *)(skelRoot + 0x338) + 200.0f;
    CopyVector((char *)&w + 0x10, &w);
    ClipWallWaveForce(&w);
    if (*(int *)((char *)&w + 0x88) != 0) {
        d = GetDistanceFromPlane((char *)&w + 0xA0, &w);
        d = d + w.rad;
        if (d > 0.0f) {
            k = 1.0f / (d + 50.0f);
            /* the wall normal read through Vec16, as sugipon's motionOrientManager
             * writes vector components: the ROM schedules the flag store after the
             * second normal load, which only a union access orders. */
            *(float *)cur = *(float *)cur + ((Vec16 *)((char *)&w + 0xA0))->f[0] * 100.0f * k;
            *(float *)(cur + 8) =
                *(float *)(cur + 8) + ((Vec16 *)((char *)&w + 0xA0))->f[2] * 100.0f * k;
            *(int *)(skelMotCtrl + 0x14) |= 0x2000;
        }
    }
}

inline int upperFieldCheck(char *a0, float f)
{
    char buf[0xC0];
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

    *(char **)(skelMotCtrl + 0x1D8) = obj;
    *(float *)(skelMotCtrl + 0x1D0) = GetPoolGlobalHeight(obj);
    *(float *)(skelMotCtrl + 0x1D4) = *(float *)(w + 0x24) - *(float *)(skelMotCtrl + 0x1D0);
}

static inline void checkPoolFloor(char *w)
{
    int attr = GetFloorAttribute(w);

    if (CompareAttribute(attr, 0x50) != 0) {
        if (*(float *)(w + 0x24) - *(float *)(skelRoot + 4) < *(float *)(skelRoot + 0x1D0)) {
            setPoolHeightOfFloor(w);
        }
    }
}

int getFieldCollision(char *w)
{
    float d;

    CopyVector(w, skelRoot);
    CopyVector(w + 0x10, w);
    *(float *)(w + 4) = *(float *)(w + 4) - 50.0f;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 50000.0f;
    if (*(int *)(skelRoot + 0x120) != 0) {
        *(FieldBlk12 *)(w + 0x74) = *(FieldBlk12 *)(skelRoot + 0x120);
        ClipFloorE(w);
    } else {
        ClipFloor(w);
    }
    if (*(int *)(w + 0x94) != 0) {
        checkPoolFloor(w);
        d = GetYDistanceFromPlane(skelRoot + 0x130, w + 0x20);
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
    char w[0xC0];
    float d;

    CopyVector(w, v);
    CopyVector(w + 0x10, v);
    *(float *)(w + 4) = *(float *)(w + 4) - 100.0f;
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 500.0f;
    ClipFloor(w);
    if (*(int *)(w + 0x94) != 0) {
        d = -(*(float *)(w + 0x24) - *(float *)(v + 4));
    } else {
        d = 3.40282347e+38f;
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

    if (*(int *)(skelRoot + 0x364) < 0) {
        return;
    }
    steep = makeRootFitPlane((char *)&pl, skelRoot);
    h = GetYProjectionOfPlane((int)&pl, (int)skelRoot) + *(float *)(mv + 4) -
        *(float *)(skelRoot + 4);
    /* Disabled in retail: the root height report.  What the bytes pin: its
       text in .rodata after _checkCliffAndWall's messages and before this
       function's PLANE message (row 571), with no instruction; rows 559-561
       after the height (558) are empty.  What they cannot: the row, the
       condition that disabled it and its two arguments. */
    if (0) {
        debug_StdPrintfDummy("regular height: %f (%f)\n", fptodp(h),
                             fptodp(*(float *)(skelRoot + 4)));
    }
    if (steep != 0) {
        if ((h < 0.0f ? -h : h) < 35.0f) {
            *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + h;
            *(float *)(skelRoot + 0x154) = *(float *)(skelRoot + 0x154) + h;
            return;
        }
        *(int *)(skelMotCtrl + 0x14) = *(int *)(skelMotCtrl + 0x14) | 4;
        *(float *)(skelRoot + 0x154) = *(float *)(skelRoot + 4);
        /* retail links debug_StdPrintfDummy in place of the listing's printf. */
        /* EUC-JP: "PLANE limit %f, it is steep so it is dropped" */
        debug_StdPrintfDummy("PLANEリミットです %f 急なので落下させます\n", fptodp(h));

        return;
    }
    if (*(int *)(skelMotCtrl + 0x68) == 0x14) {
        *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + h;
        *(float *)(skelRoot + 0x154) = *(float *)(skelRoot + 0x154) + h;
        return;
    }
    if (*(float *)(skelNode + 0x14) * skelScale < (h < 0.0f ? -h : h)) {
        *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + h;
        *(float *)(skelRoot + 0x154) = *(float *)(skelRoot + 0x154) + h;
        return;
    }

    makeRootFitPlane((char *)&pl, skelRoot);

    AddVectorXYZ(&p0, nodePos2 + *(int *)(skelRoot + 0x364) * 0x10, mv);

    AddVectorXYZ(&p1, nodePos2 + *(int *)(skelRoot + 0x364) * 0x10, skelRoot);

    p1.f[1] = p1.f[1] - p0.f[1];

    d0 = getFloorDropAt((char *)&p1, (char *)&pl, skelRoot);

    dy = d0;
    switch (*(int *)(skelNode + *(int *)(skelRoot + 0x364) * 0x40 + 4)) {
    case 0x30:
        node = GetSkeltonFocusNode((char *)skelGObj, 0x34);
        break;
    case 0x34:
        node = GetSkeltonFocusNode((char *)skelGObj, 0x30);
        break;
    default:
        node = -1;
        break;
    }
    if (node != -1) {
        Vec16 p3;

        AddVectorXYZ(&p2, nodePos2 + node * 0x10, skelRoot);

        p2.f[1] = p1.f[1];
        CopyVector(&p3, &p2);
        p3.f[1] = p3.f[1] - d0;

        d1 = getFloorDropAt((char *)&p3, (char *)&pl, skelRoot);

        if (d1 < 0.0f) {
            dy = d0 + d1;
        }

        if (*(int *)(skelMotCtrl + 0x1BC) == 0 || (*(int *)(skelMotCtrl + 0x188) & 0xF00000) == 0) {
            Vec16 pl2;

            pl2 = pl;
            pl2.f[3] = 0.0f;

            t = GetYDistanceFromPlane(&pl2, skelRoot + 0x90);

            if (!(5.0f < (t < 0.0f ? -t : t))) {
                if (debug_mot_slope_interp == 0) {
                    if (10.0f < (dy < 0.0f ? -dy : dy)) {
                        if (dy < 0.0f) {
                            dy = -10.0f;
                        } else {
                            dy = 10.0f;
                        }
                    }
                } else {
                    dy = dy * ((float)debug_mot_slope_interp * 0.1f);
                }
            }
        }
        if (*(int *)(skelRoot + 0x200) != 0) {
            *(int *)(skelRoot + 0x204) = 1;
            if (*(int *)(skelNode + *(int *)(skelRoot + 0x364) * 0x40 + 4) == 0x30) {
                if (0.0f < d1) {
                    ((MotGeoTurn *)skelRoot)->lift[0] = 0.0f;
                    ((MotGeoTurn *)skelRoot)->lift[1] = -d1;
                } else {
                    ((MotGeoTurn *)skelRoot)->lift[0] = d1;
                    ((MotGeoTurn *)skelRoot)->lift[1] = 0.0f;
                }
            } else {
                if (0.0f < d1) {
                    ((MotGeoTurn *)skelRoot)->lift[0] = -d1;
                    ((MotGeoTurn *)skelRoot)->lift[1] = 0.0f;
                } else {
                    ((MotGeoTurn *)skelRoot)->lift[0] = 0.0f;
                    ((MotGeoTurn *)skelRoot)->lift[1] = d1;
                }
            }
            if (((MotGeoTurn *)skelRoot)->lift[0] <
                -(*(float *)(skelNode + 0x14) * skelScale * 0.5f)) {
                ((MotGeoTurn *)skelRoot)->lift[0] =
                    -(*(float *)(skelNode + 0x14) * skelScale * 0.5f);
            }
            if (((MotGeoTurn *)skelRoot)->lift[1] <
                -(*(float *)(skelNode + 0x14) * skelScale * 0.5f)) {
                ((MotGeoTurn *)skelRoot)->lift[1] =
                    -(*(float *)(skelNode + 0x14) * skelScale * 0.5f);
            }
        }
    }
    *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) - dy;
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateFly and rootUpdateEnemyFly (rows 736-756, which sit between
 * setIKAndAdjustRootHeight's def line 548 and landingFieldAction's 809), so it
 * carries no symbol in MAIN.MAP. */
static inline int getFlyFieldCollision(char *w)
{
    float y;

    y = *(float *)(skelMotDef + 0x120);
    if (y < -0.5f) {
        return 0;
    }
    *(int *)(w + 0x70) = 0;
    CopyVector(w, skelRoot);
    *(float *)(w + 4) = *(float *)(skelRoot + 0x164);
    CopyVector(w + 0x10, skelRoot);
    *(float *)(w + 0x14) = *(float *)(w + 0x14) + 10000.0f;
    ClipFloor(w);
    return CheckFieldContact(w, (char *)skelGObj, (float *)skelRoot, *(float *)(skelRoot + 0x1D0));
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * landingFieldAction (rows 787-801, above its def line 809), so it carries no
 * symbol in MAIN.MAP.  Row 787 is the declaration line, which is where the
 * caller's `w + 0xA0` address arithmetic is attributed. */
static inline void adjustRootByLandingPlane(char *plane, float rate)
{
    Vec16 push;
    Vec16 half;
    Vec16 pl;
    float d;

    CopyVector(&pl, plane);
    pl.f[3] = 0.0f;
    d = plane_distance(skelRoot + 0x90, &pl);
    if (d < 0.0f) {
        _ScaleVector(&push, &pl, d);
        push.f[3] = 0.0f;
        _SubVector(&half, skelRoot + 0x90, &push);
        half.f[3] = 0.0f;
        half.f[1] = 0.0f;
        _ScaleVectorXYZ(&half, &half, rate);
        _SubVectorXYZ(skelRoot + 0x150, skelRoot, &half);
    }
}

void landingFieldAction(char *w)
{
    float h;

    *(float *)(skelRoot + 4) = *(float *)(w + 0x24) - *(float *)(skelRoot + 0x1D0);
    adjustRootByLandingPlane(w + 0xA0, 0.5f);
    h = *(float *)(skelRoot + 0x1B4);
    CopyVector(skelRoot + 0x130, w + 0xA0);
    *(float *)(skelMotCtrl + 0xEC) = GetYProjectionOfPlane((int)(w + 0xA0), (int)skelRoot) - h;
    CopyVector(skelRoot + 0x1B0, skelRoot);
    *(float *)(skelRoot + 0x1B4) = *(float *)(w + 0x24);
    *(int *)(skelMotCtrl + 0x14) |= 8;
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateFly and rootUpdateEnemyFly (row 832 followed by
 * setPoolHeightOfFloor's rows 381-383), between landingFieldAction's def line
 * 809 and floorFitting's 861, so it carries no symbol in MAIN.MAP. */
static inline void markPoolContact(char *w)
{
    *(int *)(skelMotCtrl + 0x14) |= 0x400;
    setPoolHeightOfFloor(w);
}

void floorFitting(int kind)
{
    Vec16 plane;
    Vec16 dir;
    float mtx[16];
    short ang;

    if (kind == 0x11 || kind == 0x14) {
        plane = *(Vec16 *)(skelRoot + 0x130);
        GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
        _ApplyMatrix(&dir, (int)mtx, ZUnitVector);
        plane.f[3] = 0.0f;
        floorSlope[1] = GetYDistanceFromPlane(&plane, &dir);
        floorSlope[2] = 1.0f;
        _NormalizeVector(floorSlope, floorSlope);
        ang = GetTableArcTan2(floorSlope[1], floorSlope[2]);
        RotQuaternionX(skelRoot + 0x30, ang);
        *(int *)(skelRoot + 0x204) = 0;
    }
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateXZ (rows 889-899, between floorFitting's def line 861 and
 * rootUpdateXZ's 905), so it carries no symbol in MAIN.MAP. */
static inline int getFloorAttributeUnderNode(void)
{
    ClipBuf w;
    int node;

    memset(&w, 0, 0xC0);
    node = GetSkeltonFocusNode((char *)skelGObj, 51);
    _AddVectorXYZ((int)&w, (int)skelRoot, nodePos2 + node * 0x10);
    CopyVector((char *)&w + 0x10, &w);
    *(float *)((char *)&w + 4) = *(float *)((char *)&w + 4) - 50.0f;
    *(float *)((char *)&w + 0x14) = *(float *)((char *)&w + 0x14) + 50.0f;
    ClipFloor(&w);
    if (*(int *)((char *)&w + 0x94) != 0) {
        return GetFloorAttribute(&w);
    }
    return -1;
}

extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0SubVector(void *dst, void *a, void *b);

/* The wall pass after a horizontal move: the listing gives the two
 * wallCollisionAndFloorFit expansions, both 0xD8 tests and the
 * waveForceReaction expansion ONE row at each of rootUpdateXZ's three uses
 * (1037, 1120, 1133), where rootUpdateXZ_MotPos's written-out copy has three. */
#define WALL_COLLISION_AND_WAVE_FORCE()                                                            \
    if (wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150,                                       \
                                 *(float *)(skelRoot + 0x1D0) + -30.0f) == 0) {                    \
        if (*(int *)(skelMotCtrl + 0xD8) != 0) {                                                   \
            wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150, 5.0f);                            \
        }                                                                                          \
    }                                                                                              \
    if (*(int *)(skelMotCtrl + 0xD8) != 0) {                                                       \
        waveForceReaction(skelRoot, skelRoot + 0x150, 0.0f);                                       \
    }

MotShift rootUpdateXZ(int kind, int no)
{
    Vec16 mv;
    Vec16 step;
    MotShift ret = {0, -1};
    float mtx[16];

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)rootMove);
    sceVu0ApplyMatrix((int *)&step, (int)mtx, skelRoot + 0x170);
    AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0x10);
    AddVectorXYZ(skelRoot + 0x150, skelRoot + 0x150, skelRoot + 0x10);

    if (no != -1) {
        Vec16 focus;

        *(int *)(skelRoot + 0x364) = no;
        CopyVector(&focus, nodePos + no * 0x10);
        switch (*(int *)(skelNode + no * 0x40 + 4)) {
        case 47:
            *(int *)(skelRoot + 0x364) = GetSkeltonFocusNode((char *)skelGObj, 48);
            break;
        case 51:
            *(int *)(skelRoot + 0x364) = GetSkeltonFocusNode((char *)skelGObj, 52);
            break;
        }
        if (*(int *)(skelRoot + 0x180) == no) {
            Vec16 dir;
            float keep = 1.0f;
            float give = 0.0f;

            /* The slope work is a block of its own: the ROM frees pos, fall
             * and n (sp+0xB0..0xE0) before the wall pass reuses that space,
             * which needs their block to close with the slope test as its
             * last statement; dir (sp+0x80, read below) sits one level out. */
            {
                Vec16 nodePos, pl, pos, fall, n;
                float rate, d;

                MatrixDrive_PushMatrix();
                sceVu0UnitMatrix(MatrixDrive_GetMatrix());
                MultiMatrixByQuaternion(skelRoot + 0x30);
                sceVu0ApplyMatrix((int *)&nodePos, MatrixDrive_GetMatrix(), skelRoot + 0x1A0);
                SubVectorXYZ(&dir, &nodePos, &focus);
                MatrixDrive_PopMatrix();
                CopyVector(&pl, skelRoot + 0x130);
                pl.f[3] = 0.0f;
                if (*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                    (*(int *)(skelMotCtrl + 0x188) & 0xF00000) != 0) {
                    memset(&fall, 0, 16);
                    fall.f[1] = 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) *
                                0.5f *
                                (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
                    pos = fall;
                    rate = 0.0f;
                    d = GetDistanceFromPlane(&pl, &pos);
                    sceVu0ScaleVector(&n, &pl, -d);
                    sceVu0SubVector(&fall, &n, &pos);
                    AddVectorXYZ(skelRoot + 0x90, skelRoot + 0x90, &fall);
                    if (*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                        (*(int *)(skelMotCtrl + 0x188) & 0x100000) != 0) {
                        rate = 0.5f;
                    }
                    if (*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                        (*(int *)(skelMotCtrl + 0x188) & 0x200000) != 0) {
                        rate = 0.7f;
                    }
                    if (*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                        (*(int *)(skelMotCtrl + 0x188) & 0x400000) != 0) {
                        rate = 0.8f;
                    }
                    if (*(int *)(skelMotCtrl + 0x1BC) != 0 &&
                        (*(int *)(skelMotCtrl + 0x188) & 0x800000) != 0) {
                        rate = 0.95f;
                    }
                    keep = 1.0f - rate;
                    give = rate;
                    *(int *)(skelMotCtrl + 0x1B4) = *(int *)(skelMotCtrl + 0x188);
                }
            }
            sceVu0ScaleVector(&dir, &dir, keep);
            sceVu0ScaleVector(skelRoot + 0x90, skelRoot + 0x90, give);
            AddVectorXYZ(skelRoot + 0x90, skelRoot + 0x90, &dir);
            {
                Vec16 t;

                CopyVector(&t, skelRoot + 0x90);
                t.f[1] = 0.0f;
                AddVectorXYZ(skelRoot, skelRoot, &t);
            }
        } else {
            AddVectorXYZ(skelRoot, skelRoot, &step);
            CopyVector(skelRoot + 0x90, &step);
        }
        WALL_COLLISION_AND_WAVE_FORCE();
        /* The ROM keeps this work block (sp+0xB0) out of reach of the else
         * arm, whose own block is fresh at sp+0x1B0: the block closes after
         * setIKAndAdjustRootHeight and before the arm's next statement. */
        {
            ClipBuf w;
            int attr;

            if (getFieldCollision((char *)&w) != 0) {
                CopyVector(skelRoot + 0x130, (char *)&w + 0xA0);
                *(int *)(skelMotCtrl + 0x188) = attr = GetFloorAttribute(&w);
                if (*(int *)(skelRoot + 0x180) == -1) {
                    *(int *)(skelMotCtrl + 0xEC) = 0;
                    adjustRootByLandingPlane(
                        skelRoot + 0x130,
                        (*(int *)(skelMotCtrl + 0x1BC) != 0 && (attr & 0xF00000) != 0) ? 0.5f
                                                                                       : 1.0f);
                }
                ret = *(MotShift *)((char *)&w + 0x8C);
            } else {
                *(int *)(skelMotCtrl + 0x14) |= 4;
            }
            setIKAndAdjustRootHeight((char *)&mv);
        }
        checkCliffAndWallStateOfLastPlane();
        MatrixDrive_PushMatrix();
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MultiMatrixByQuaternion(skelRoot + 0x30);
        CopyVector((void *)(MatrixDrive_GetMatrix() + 0x30), ZeroPoint);
        sceVu0TransposeMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
        sceVu0ApplyMatrix((int *)(skelRoot + 0x1A0), MatrixDrive_GetMatrix(), (char *)&focus);
        MatrixDrive_PopMatrix();
        *(float *)(skelRoot + 0xC0) = GetYDistanceFromPlane(skelRoot + 0x130, skelRoot);
        {
            Vec16 sum;
            float proj, gap;

            AddVectorXYZ(&sum, nodePos2 + no * 0x10, skelRoot);
            sceVu0CopyVector(skelRoot + 0x1B0, &sum);
            *(float *)(skelRoot + 0x1BC) = 1.0f;
            proj = GetYProjectionOfPlane((int)(skelRoot + 0x130), (int)&sum);
            gap = proj - *(float *)(skelRoot + 0x1B4);
            if ((gap < 0.0f ? -gap : gap) < *(float *)(skelNode + 0x14) * skelScale) {
                *(float *)(skelRoot + 0x1B4) = proj;
            }
        }
        CopyVector(skelRoot + 0x190, &focus);
    } else {
        ClipBuf w;

        if (*(int *)(skelRoot + 0x30C) != 0) {
            *(float *)(skelRoot + 0x94) +=
                60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
                (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) *
                (systemStatus[0] != 0 ? 0.7f : 1.0f);
            AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0x90);
            WALL_COLLISION_AND_WAVE_FORCE();
        } else {
            if (*(int *)(skelRoot + 0x180) != no) {
                CopyVector(skelRoot + 0x90, &step);
            }
            *(float *)(skelRoot + 0x94) = 0.0f;
            AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0x90);
            WALL_COLLISION_AND_WAVE_FORCE();
            if (*(int *)(skelRoot + 0x310) != 0) {
                if (getFieldCollision((char *)&w) != 0) {
                    CopyVector(skelRoot + 0x130, (char *)&w + 0xA0);
                    ret = *(MotShift *)((char *)&w + 0x8C);
                    setIKAndAdjustRootHeight((char *)&mv);
                } else {
                    *(int *)(skelMotCtrl + 0x14) |= 4;
                }
            } else {
                *(float *)(skelRoot + 4) = mv.f[1] + *(float *)(skelRoot + 0x1B4);
            }
        }
        checkCliffAndWallStateAtJump();
        switch (getFlyFieldCollision((char *)&w)) {
        case 1:
            landingFieldAction((char *)&w);
            break;
        case 2:
            markPoolContact((char *)&w);
            break;
        default:
            /* Disabled in retail: the unknown-reaction report ("whoever sees
               this message, report it to Sugiyama at once").  What the bytes
               pin: its text in .rodata after setIKAndAdjustRootHeight's PLANE
               message and before rootUpdateXZ_MotPos's, with no instruction;
               rows 1159-1167, after case 2 (1158), are empty.  What they
               cannot: the arm's form and the condition that disabled it. */
            if (0) {
                debug_StdPrintfDummy(
                    "このメッセージを見た人は直ちにすぎやまに報告してくれー:NOWALLHITPROC\n");
            }
            break;
        }
    }
    if (*(int *)(skelMotCtrl + 0x100) != 0) {
        if (*(float *)(skelMotCtrl + 0x138) < 20.0f && -10.0f < *(float *)(skelMotCtrl + 0x130)) {
            *(unsigned int *)(skelMotCtrl + 0x14) &= ~4;
        }
    }
    if (kind == 20) {
        int attr = getFloorAttributeUnderNode();

        if (attr != -1) {
            *(int *)(skelMotCtrl + 0x188) = attr;
        }
    }
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x150, skelRoot);
    *(int *)(skelRoot + 0x180) = no;
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0xD0, rootDelta);
    return ret;
}

MotShift rootUpdateXZ_MotPos(int kind, int no)
{
    MotShift ret = {0, -1};
    ClipBuf w;
    Vec16 mv;
    Vec16 step;
    float mtx[16];
    float lim;
    int r;

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)rootMove);
    sceVu0ApplyMatrix((int *)&step, (int)mtx, rootStep);
    AddVectorXYZ(skelRoot, skelRoot, &step);

    if (no != -1) {
        CopyVector(skelRoot + 0xD0, rootDelta);
    } else {
        if (*(int *)(skelMotCtrl + 0x58) != 0) {
            if (systemStatus[0] == 1) {
                AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0x90);
            }
        }
        if (*(int *)(skelMotCtrl + 0x30) == 21) {
            lim = -(60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 10.0f);
            if (*(float *)(skelRoot + 0xD4) < lim) {
                *(float *)(skelRoot + 0xD4) = lim;
                /* retail links debug_StdPrintfDummy in place of the listing's printf. */
                debug_StdPrintfDummy("inertia cancel.\n");
            }
        }
        AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0xD0);
    }

    if (wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150,
                                 *(float *)(skelRoot + 0x1D0) + -30.0f) == 0) {
        if (*(int *)(skelMotCtrl + 0xD8) != 0) {
            wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150, 5.0f);
        }
    }

    if (*(int *)(skelMotCtrl + 0xD4) != 0) {
        if (no != -1 || *(int *)(skelRoot + 0x310) != 0) {
            if (getFieldCollision((char *)&w) != 0) {
                CopyVector(skelRoot + 0x130, (char *)&w + 0xA0);
                *(float *)(skelRoot + 4) = *(float *)((char *)&w + 0x24) + mv.f[1];
                if (no != -1 || *(int *)(skelMotCtrl + 0x30) == 75 ||
                    *(int *)(skelMotCtrl + 0x30) == 599 || *(int *)(skelMotCtrl + 0x30) == 58) {
                    *(int *)(skelMotCtrl + 0x188) = GetFloorAttribute((char *)&w);
                    ret = *(MotShift *)((char *)&w + 0x8C);
                } else {
                    *(int *)(skelMotCtrl + 0x188) = 0;
                }
            } else {
                *(int *)(skelMotCtrl + 0x14) = *(int *)(skelMotCtrl + 0x14) | 4;
            }
        } else {
            getFieldCollision((char *)&w);
        }
        r = getFlyFieldCollision((char *)&w);
        switch (r) {
        case 1:
            if (*(float *)(skelMotDef + 0x120) > *(float *)(skelMotCtrl + 0x3C)) {
                *(float *)(skelRoot + 4) = *(float *)((char *)&w + 0x24) + mv.f[1];
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
    *(float *)(skelRoot + 0xC0) = rootMove[1];
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0x150, skelRoot);
    *(int *)(skelRoot + 0x180) = no;
    return ret;
}

/* kept local: this TU's uses of GetDistanceFromPlane do not fit the prototype
 * in fieldCollision.h */
extern float GetDistanceFromPlane(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);

int adjustSideWall(char *w, int a1, int a2)
{
    WallCfg cfg = {((WallCfg *)(w + 0x80))->o, ((WallCfg *)(w + 0x80))->n};
    Vec16 pl0;
    Vec16 pl1;
    float pts[16];
    Vec16 push;
    float d;
    float t;

    GetPureVerticalPlane(&pl0, &pl1, pts, (int *)&cfg, 0);
    d = (GetDistanceFromPlane(&pl0, w + 0x20) < 0.0f ? -GetDistanceFromPlane(&pl0, w + 0x20)
                                                     : GetDistanceFromPlane(&pl0, w + 0x20)) -
        30.0f;
    if (a1 != 0) {
        if ((d < 0.0f ? -d : d) < 30.0f) {
            return 1;
        }
    }
    t = sceVu0InnerProduct((void *)a2, &pl1);
    if ((t < 0.0f ? -t : t) < 0.8f) {
        CopyVector(&push, &pl1);
        push.f[3] = 0.0f;
        sceVu0ScaleVectorXYZ(&push, &push, GetDistanceFromPlane(&pl1, skelRoot) - 30.0f);
        SubVectorXYZ(skelRoot, skelRoot, &push);
    }
    return 0;
}

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
    if (*(int *)(skelRoot + 0x324) != 0) {
        ClipWallFuchiHangWalkStop((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = GetWallAttribute((void *)p);
            switch (*(int *)(skelRoot + 0x324)) {
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
    _ApplyMatrix(buf, a1, sideWallProbe);
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
    iosOmSendMail(skelGObj, 0x18, skelGObj);
    CopyVector(skelRoot + 0x150, skelRoot);
}

void forceReset(void)
{
    iosOmSendMail(skelGObj, 0x103, skelGObj);
    CopyVector((char *)skelRoot + 0x150, (char *)skelRoot);
}

void checkWallUpperWall(void)
{
    int v;
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    {
        register float *p = (float *)skelRoot;
        MatrixDrive_TransMatrix(p[0], p[1] - rootMove[1], p[2]);
    }
    MultiMatrixByQuaternion((char *)skelRoot + 0x30);
    checkUpperWallState();
    MatrixDrive_PopMatrix();
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateHang (rows 1553-1573, between checkWallUpperWall's 1536 and
 * calcWallFittingGeometry's 1581), so it carries no symbol in MAIN.MAP. */
static inline void dropWhenFloorTooFar(void)
{
    ClipBuf w;

    if (0.0f <= plane_distance(skelRoot, skelRoot + 0x130)) {
        return;
    }
    CopyVector(&w, skelRoot);
    CopyVector((char *)&w + 0x10, &w);
    *(float *)((char *)&w + 0x14) = *(float *)((char *)&w + 0x14) + 50.0f;
    ClipFloor(&w);
    if (*(int *)((char *)&w + 0x94) != 0) {
        if ((GetFloorAttribute(&w) & 0x800000) == 0 &&
            *(float *)((char *)&w + 0x24) - *(float *)((char *)&w + 4) < 50.0f) {
            forceFallDown();
        }
    }
}

void calcWallFittingGeometry(void)
{
    Vec16 v;
    float mtx[16];
    Vec16 base;
    Vec16 rot;
    short ang;

    GetWallGlobalInfo(0, &v, *(int *)(skelRoot + 0xE8),
                      *(char **)(*(char **)(*(char **)(skelRoot + 0xE0) + 0x15C) + 0xC) +
                          *(int *)(skelRoot + 0xE4) * 0x40);
    MatrixDrive_SetTransposeMatrix(mtx, MatrixDrive_GetMatrix());
    _ApplyMatrix(&v, (int)mtx, (char *)&v);
    v.f[0] = 0.0f;
    _NormalizeVector(&v, &v);
    ang = (short)(atan2f(v.f[1], -v.f[2]) * 10430.378f);
    RotQuaternionX(skelRoot + 0x30, ang);
    MatrixDrive_PushMatrix();
    _ApplyMatrix(&base, MatrixDrive_GetMatrix(), (char *)rootMove);
    MatrixDrive_RotMatrixX(ang);
    _ApplyMatrix(&rot, MatrixDrive_GetMatrix(), (char *)rootMove);
    _SubVector(skelRoot + 0x10, &rot, &base);
    *(int *)(skelRoot + 0x1C) = 0;
    MatrixDrive_PopMatrix();
    *(int *)(skelRoot + 0xC0) = 0;
}

MotShift rootUpdateHang(int kind, int a1, int a2)
{
    Vec16 mv;
    Vec16 up;
    float mtx[16];
    Vec16 pl;
    Vec16 pl2;
    ClipBuf w;
    float mtx2[16];
    Vec16 pos;
    int hit;

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&up, (int)mtx, (char *)rootMove);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)rootStep);
    AddVectorXYZ(skelRoot, skelRoot, &mv);
    *(float *)(skelRoot + 0xC0) = rootMove[1];
    hit = 0;
    CopyVector(&pos, skelRoot);
    pos.f[1] = pos.f[1] - (rootMove[1] - 30.0f);
    MatrixDrive_PushMatrix();
    GetMatrixFromQuaternionPos((void *)MatrixDrive_GetMatrix(), skelRoot + 0x30, &pos);
    MatrixDrive_TransMatrix(0.0f, 0.0f, -rootMove[2] - 10.0f);
    CopyMatrix(mtx2, (void *)MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    sceVu0ApplyMatrix((int *)&w, (int)mtx2, (char *)hangBack);
    sceVu0ApplyMatrix((int *)((char *)&w + 0x10), (int)mtx2, (char *)hangFront);
    w.rad = 0.0f;

    /* The frame pins two block levels around the work records (not their
       text): a block local whose address a statement of its own block takes
       is released only when the enclosing block ends, and the ROM gives
       sp+0x190..0x350 back to both inlined helpers below. */
    {
        int n;
        int attr;

        if (*(int *)(skelMotCtrl + 0x64) == 0) {
            ClipWall(&w);
            if (*(int *)((char *)&w + 0x88) != 0) {
                WallCfg rec = {((WallCfg *)((char *)&w + 0x80))->o,
                               ((WallCfg *)((char *)&w + 0x80))->n};

                n = GetPureVerticalPlaneOfCurrentPosition(skelRoot + 0x130, &pl, 0, (int *)&rec, 0,
                                                          skelRoot);
                if (-0.25f < *(float *)(skelRoot + 0x134)) {
                    /* EUC-JP: "the wall angle is steep, so fall" */
                    debug_StdPrintfDummy("壁の角度が急なので落下\n");
                    forceFallDown();
                    goto out;
                }
                CopyVector(&pl2, &pl);
                if (*(int *)(skelRoot + 0xE0) == rec.o.obj &&
                    *(int *)(skelRoot + 0xE4) == rec.o.node && *(int *)(skelRoot + 0xE8) == rec.n) {
                    hit = *(int *)(skelRoot + 0xEC) == n;
                }
                *(WallCfg *)(skelRoot + 0xE0) = rec;
                *(int *)(skelRoot + 0xEC) = n;
                *(int *)(skelMotCtrl + 0x17C) = *(int *)(skelMotCtrl + 0x184) = attr =
                    GetWallAttribute(&w);
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
            *(int *)(skelMotCtrl + 0x64) = 0;
            GetPureVerticalPlane(skelRoot + 0x130, &pl, 0, (int *)(skelRoot + 0xE0), 0);
            hit = 1;
            CopyVector(&pl2, &pl);
        }

        {
            Vec16 v;
            Vec16 sc;
            ClipBuf sw1;
            ClipBuf sw2;
            Vec16 dv;
            int r1;
            int r2;
            float d;
            float dd;

            pl2.f[3] = 0.0f;
            CopyVector(&v, skelRoot);
            v.f[1] = v.f[1] - rootMove[1];
            d = GetDistanceFromPlane(skelRoot + 0x130, &v);
            if (hit == 0) {
                if (d < 0.0f ? 30.0f < -d : 30.0f < d) {
                    /* EUC-JP: "no hold point on the wall, so fall (step: %f)" */
                    debug_StdPrintfDummy("壁のつかまり先がなくて落下 (段差:%f)\n", fptodp(d));
                    forceFallDown();
                    goto out;
                }
            }
            dd = -d;
            sceVu0ScaleVector(&sc, skelRoot + 0x130, dd);
            AddVectorXYZ(&v, &v, &sc);
            d = GetDistanceFromPlane(&pl, &v);
            sceVu0ScaleVector(&sc, &pl, -d - rootMove[2]);
            AddVectorXYZ(&v, &v, &sc);
            CopyVector(skelRoot, &v);
            CopyVector(skelRoot + 0x1B0, skelRoot);
            *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + rootMove[1];

            r1 = checkSideWall((int)hangLeft, (int)mtx2, (int)&sw1, (int)&w, (int)&pl2);
            r2 = checkSideWall((int)hangRight, (int)mtx2, (int)&sw2, (int)&w, (int)&pl2);
            if (r1 == -1 || r2 == -1) {
                /* EUC-JP: "hit a forced-fall wall, so fall" */
                debug_StdPrintfDummy("強制落下の壁に当たったので落下\n");
                forceFallDown();
                goto out;
            }
            if (r1 != 0 && r2 != 0) {
                sceVu0SubVector(&dv, (char *)&sw2 + 0x20, (char *)&sw1 + 0x20);
                sceVu0OuterProduct(skelMotCtrl + 0xB0, &dv, YUnitVector);
                *(int *)(skelMotCtrl + 0xB4) = 0;
                sceVu0Normalize(skelMotCtrl + 0xB0, skelMotCtrl + 0xB0);
            } else {
                CopyVector(skelMotCtrl + 0xB0, &pl2);
                *(float *)(skelMotCtrl + 0xB0) = -*(float *)(skelMotCtrl + 0xB0);
                *(float *)(skelMotCtrl + 0xB8) = -*(float *)(skelMotCtrl + 0xB8);
            }
        }
    }

    checkWallUpperWall();
    dropWhenFloorTooFar();
    wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150, 0.0f);

out:
    CopyVector(skelRoot + 0x10, ZeroPoint);
    if (kind == 15) {
        calcWallFittingGeometry();
    }
    SubVectorXYZ(skelRoot + 0x60, skelRoot, &up);
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0xD0, rootDelta);
    *(int *)(skelRoot + 0x180) = -1;
    return *(MotShift *)(skelRoot + 0xE0);
}

MotShift rootUpdateSwim(void)
{
    ClipBuf w;
    Vec16 v;
    MotShift shift = {0, -1};
    float mtx[16];
    int node;

    node = GetSkeltonFocusNode((char *)skelGObj, 34);
    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&v, (int)mtx, rootStep);
    v.f[0] = v.f[0] * 0.2f;
    v.f[1] = v.f[1] * 0.2f;
    v.f[2] = v.f[2] * 0.2f;
    sceVu0AddVector(skelRoot + 0x90, skelRoot + 0x90, &v);
    GetLowerPlaneCollision(&w, skelRoot);
    if (GetWaterReaction(0, 0, &w, skelRoot, skelRoot + 0x90, *(float *)(skelRoot + 4) - 80.0f,
                         *(float *)(skelRoot + 4) + *(float *)(nodePos + node * 0x10 + 4),
                         *(float *)(skelRoot + 4) + 80.0f, 0.9f,
                         60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * -0.1f *
                             (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]))) !=
        0) {
        /* listing row 1884 holds only the load of this constant; the
         * subtractions are on the rows that use it. */
        float depth = 10.0f;

        if (*(float *)((char *)&w + 0x24) - depth < *(float *)(skelRoot + 4)) {
            *(float *)(skelRoot + 4) = *(float *)((char *)&w + 0x24) - depth;
            *(float *)(skelRoot + 0x154) = *(float *)((char *)&w + 0x24) - depth;
        }
        setPoolHeightOfFloor((char *)&w);
    } else {
        *(int *)(skelMotCtrl + 0x14) |= 0x800;
        /* retail links debug_StdPrintfDummy in place of the listing's printf. */
        /* EUC-JP: "there is no DWATER water bottom below.  If this message keeps coming, it has not left the swim state" */
        debug_StdPrintfDummy(
            "下にDWATERの水底がないです。このメッセージが連続で\n出てるなら、泳ぎから遷移していない状態です\n\n");
    }
    if (*(int *)((char *)&w + 0x94) != 0) {
        *(int *)(skelMotCtrl + 0x188) = GetFloorAttribute(&w);
        CopyVector(skelRoot + 0x130, (char *)&w + 0xA0);
    }
    wallCollisionAndFloorFit(skelRoot, skelRoot + 0x150, 0.0f);
    if (*(int *)(skelMotCtrl + 0xD8) != 0) {
        waveForceReaction(skelRoot, skelRoot + 0x150, 0.0f);
    }
    checkCliffAndWallStateAtJump();
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x1B0, skelRoot);
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0xD0, rootDelta);
    *(int *)(skelRoot + 0xC0) = 0;
    *(int *)(skelRoot + 0x180) = -1;
    return shift;
}

/* RECONSTRUCTED NAME: the PAL listing shows this body only inlined into
 * rootUpdateStepSolution and rootUpdateY (rows 1936-1942, between
 * rootUpdateSwim and avoidSideAdjustWall), so it carries no symbol in
 * MAIN.MAP. */
static inline void clipWallAhead(ClipBuf *w)
{
    float mtx[16];

    GetMatrixFromQuaternionPos(mtx, skelRoot + 0x30, skelRoot);
    sceVu0ApplyMatrix((int *)w, (int)mtx, (char *)clipWallBack);
    sceVu0ApplyMatrix((int *)((char *)w + 0x10), (int)mtx, (char *)clipWallFront);
    w->rad = 0.0f;
    ClipWall(w);
}

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
    _SubVectorXYZ(&t, &t, skelRoot);
    _ScaleVectorXYZ(&t, &t, 0.07f);
    _AddVectorXYZ((int)skelRoot, (int)skelRoot, &t);
}

int avoidSideAdjustWall(void)
{
    float mtx[16];
    char w[0xD0];

    memset(w, 0, 0xC0);
    GetMatrixFromQuaternionPos(mtx, skelRoot + 0x30, skelRoot);
    _ApplyMatrix(w, (int)mtx, avoidLeft);
    _ApplyMatrix(w + 0x10, (int)mtx, avoidRight);
    if (clipSideWallAndHit(w) == 0) {
        _ApplyMatrix(w, (int)mtx, avoidRight);
        _ApplyMatrix(w + 0x10, (int)mtx, avoidLeft);
        if (clipSideWallAndHit(w) == 0) {
            return 0;
        }
    }
    pushRootAlongSideWall(w);
    return 1;
}

MotShift rootUpdateStepSolution(int kind)
{
    Vec16 mv;
    Vec16 up;
    /* every arm of the switch below reassigns it, but the ROM copies the
       initial record (listing row 2025) all the same. */
    WallCfg cfg = {{0, -1}, 0};
    float mtx[16];
    Vec16 d1;
    Vec16 d2;
    float pl[4];
    float pl2[4];
    Vec16 corner[4];
    Vec16 avg;
    Vec16 pos;
    Vec16 adj;
    ClipBuf w;
    float dir;
    float d;
    int node;
    int i;

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)rootStep);
    sceVu0ApplyMatrix((int *)&up, (int)mtx, (char *)rootMove);
    if (stepFocusNode != -1) {
        node = GetSkeltonFocusNode((char *)skelGObj, stepFocusNode);
        _SubVectorXYZ(&d2, *(char **)(*(char **)(skelGObj + 0x15C) + 0xC) + node * 0x40 + 0x30,
                      *(char **)(*(char **)(skelGObj + 0x15C) + 0xC) + 0x30);
        _SubVectorXYZ(&d1, nodePos2 + node * 0x10, &d2);
        _SubVectorXYZ(skelRoot, skelRoot, &d1);
    } else {
        AddVectorXYZ(skelRoot, skelRoot, &mv);
    }
    *(float *)(skelRoot + 0xC0) = rootMove[1];

    switch (kind) {
    case 9:
        cfg = *(WallCfg *)(skelRoot + 0xF0);
        dir = 1.0f;
        GetPureVerticalPlane(skelRoot + 0x130, pl, (float *)corner, (int *)&cfg, 0);
        break;
    case 13:
        cfg = *(WallCfg *)(skelRoot + 0xF0);
        dir = 1.0f;
        GetPureVerticalPlane(skelRoot + 0x130, pl, (float *)corner, (int *)&cfg, 1);
        break;
    case 7:
    case 16:
    default:
        cfg = *(WallCfg *)(skelRoot + 0xE0);
        dir = -1.0f;
        GetPureVerticalPlane(skelRoot + 0x130, pl, (float *)corner, (int *)&cfg, 0);
        break;
    case 8:
        cfg = *(WallCfg *)(skelRoot + 0xE0);
        dir = -1.0f;
        GetPureVerticalPlane(skelRoot + 0x130, pl, (float *)corner, (int *)&cfg, 1);
        break;
    }

    CopyVector(pl2, pl);
    pl2[3] = 0.0f;
    if (*(int *)(skelRoot + 0x32C) != 0) {
        memset(&avg, 0, 16);
        avg.f[3] = 1.0f;
        for (i = 0; i < 4; i++) {
            AddVectorXYZ(&avg, &avg, &corner[i]);
        }
        sceVu0ScaleVector(&avg, &avg, 0.25f);
        *(float *)(skelRoot + 0) =
            *(float *)(skelRoot + 0) + (avg.f[0] - *(float *)(skelRoot + 0)) * 0.2f;
        *(float *)(skelRoot + 8) =
            *(float *)(skelRoot + 8) + (avg.f[2] - *(float *)(skelRoot + 8)) * 0.2f;
    }

    CopyVector(&pos, skelRoot);
    pos.f[1] = pos.f[1] - rootMove[1];
    d = GetDistanceFromPlane(skelRoot + 0x130, &pos);
    sceVu0ScaleVector(&adj, skelRoot + 0x130, -d);
    AddVectorXYZ(&pos, &pos, &adj);
    d = GetDistanceFromPlane(pl, &pos);
    sceVu0ScaleVector(&adj, pl, -d + rootMove[2] * dir);
    AddVectorXYZ(&pos, &pos, &adj);
    CopyVector(skelRoot, &pos);
    *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + rootMove[1];
    sceVu0ScaleVectorXYZ(skelMotCtrl + 0xB0, pl2, dir);

    CopyVector(&w, skelRoot);
    CopyVector((char *)&w + 0x10, &w);
    *(float *)((char *)&w + 0x14) =
        *(float *)((char *)&w + 0x14) + (*(float *)(skelRoot + 0x1D0) + 10.0f);
    ClipFloor(&w);
    if (*(int *)((char *)&w + 0x94) != 0) {
        *(int *)(skelMotCtrl + 0x188) = GetFloorAttribute(&w) & 0xF0;
    }

    if (*(int *)(skelRoot + 0x324) != 0) {
        avoidSideAdjustWall();
    }

    if (kind >= 7 && (kind < 9 || kind == 16)) {
        if (*(int *)(skelMotCtrl + 0xD8) != 0) {
            if (*(int *)(skelMotDef + 0x130) == 0) {
                clipStepWallAndReact(skelRoot, skelRoot + 0x150, *(float *)(skelRoot + 0x338),
                                     &cfg);
            }
            if (upperFieldCheck(skelRoot, -50.0f) != 0) {
                forceFallDown();
            }
        }
        checkWallUpperWall();
        if (*(int *)(skelMotCtrl + 0x30) == 85) {
            MatrixDrive_PushMatrix();
            _UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrix(*(float *)(skelRoot + 0),
                                    GetYProjectionOfPlane((int)(skelRoot + 0x130), (int)skelRoot),
                                    *(float *)(skelRoot + 8));
            MultiMatrixByQuaternion(skelRoot + 0x30);
            checkCliffState(1);
            MatrixDrive_PopMatrix();
        }
    } else {
        clipStepWallAndReact(skelRoot, skelRoot + 0x150, *(float *)(skelRoot + 0x338), &cfg);
    }

    if (clipFuchiWallAndReact(skelRoot, skelRoot + 0x150, *(int *)(skelRoot + 0x324),
                              *(float *)(skelRoot + 0x338)) != 0) {
        /* EUC-JP: "hit an extension wall" */
        debug_StdPrintfDummy("拡張壁に当たった\n");
    }
    if (*(int *)(skelRoot + 0x320) != 0) {
        if (clipFieldWallAndReset(skelRoot, skelRoot + 0x150) != 0) {
            forceReset();
        }
    }

    CopyVector(skelRoot + 0x10, ZeroPoint);
    switch (kind) {
    case 16:
        calcWallFittingGeometry();
        /* falls through: the ROM runs the kind-7/8 wall probe after it. */
    case 7:
    case 8: {
        ClipBuf cw;

        clipWallAhead(&cw);
        {
            WallCfg rec = {((WallCfg *)((char *)&cw + 0x80))->o,
                           ((WallCfg *)((char *)&cw + 0x80))->n};
            Vec16 wp;

            if (*(int *)((char *)&cw + 0x88) != 0) {
                *(WallCfg *)(skelRoot + 0x100) = rec;
                GetPureVerticalPlane(&wp, 0, 0, (int *)&rec, 0);
                *(float *)(skelMotCtrl + 0x178) = GetDistanceFromPlane(&wp, skelRoot) - rootMove[1];
            }
        }
    } break;
    case 9:
        dropWhenFloorTooFar();
        break;
    }

    SubVectorXYZ(skelRoot + 0x60, skelRoot, &up);
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x90, ZeroVector);
    CopyVector(skelRoot + 0x1B0, skelRoot);
    *(float *)(skelRoot + 0x1B4) = *(float *)(skelRoot + 0x1B4) - rootMove[1];
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0xD0, rootDelta);
    *(int *)(skelRoot + 0x180) = -1;
    *(WallCfg *)(skelRoot + 0xE0) = cfg;
    return *(MotShift *)&cfg;
}

MotShift rootUpdateTrueMotion(int a0)
{
    float mtx[16];
    Vec16 v;
    int noMove = a0;

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    if (noMove == 0) {
        sceVu0ApplyMatrix((int *)&v, (int)mtx, (char *)rootMove);
        v.f[1] = v.f[1] + *(float *)(skelNode + 0x14);
        v.f[0] = v.f[2] = 0.0f;
        CopyVector(skelRoot + 0x10, &v);
    } else {
        CopyVector(skelRoot + 0x10, ZeroPoint);
    }
    *(int *)(skelRoot + 0x180) = -1;
    *(int *)(skelRoot + 0xC0) = 0;
    CopyVector(skelRoot + 0xD0, rootDelta);
    return InitialObjPointer;
}

MotShift rootUpdateDirectPlayForStream(void)
{
    float *p;
    int *q;

    SetIdentityQuaternion(skelRoot + 0x30);
    RotQuaternionY(skelRoot + 0x30, -32768);
    CopyVector(skelRoot, rootMove);
    p = (float *)skelRoot;
    p[0] = -p[0];
    p[2] = -p[2];
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0x90, ZeroVector);
    CopyVector(skelRoot + 0x10, ZeroVector);
    q = (int *)skelRoot;
    q[0x60] = -1;
    q[0x30] = 0;
    AdjustMotionHeightToNearestField((char *)skelGObj);
    CopyVector(skelRoot + 0xD0, rootDelta);
    return InitialObjPointer;
}

MotShift rootUpdateDirectPlay(int a0)
{
    int kind = a0;
    float *p;
    int *q;
    float s;

    SetIdentityQuaternion(skelRoot + 0x30);
    RotQuaternionY(skelRoot + 0x30, -32768);
    CopyVector(skelRoot, rootMove);
    p = (float *)skelRoot;
    p[0] = p[0] - *(float *)(skelMotDef + 0x124);
    p[1] = p[1] - *(float *)(skelMotDef + 0x128);
    p[2] = p[2] + *(float *)(skelMotDef + 0x12C);
    if (kind == 14) {
        s = 1.0f / skelScale;
        p[0] = p[0] * -s;
        p[1] = p[1] * s;
        p[2] = p[2] * -s;
    } else {
        p[0] = -p[0];
        p[2] = -p[2];
    }
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0x90, ZeroVector);
    CopyVector(skelRoot + 0x10, ZeroVector);
    q = (int *)skelRoot;
    q[0x60] = -1;
    q[0x30] = 0;
    AdjustMotionHeightToNearestField((char *)skelGObj);
    CopyVector(skelRoot + 0xD0, rootDelta);
    return InitialObjPointer;
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
        SetIdentityQuaternion(skelRoot + 0x30);
        RotQuaternionY(skelRoot + 0x30, -GetTableArcTan2(v.f[0], -v.f[2]));
        MultiQuaternion(skelRoot + 0x30, skelRoot + 0x30, skelRoot + 0x390);
        CopyMatrix((void *)MatrixDrive_GetMatrix(),
                   *(char **)(*(char **)(*(char **)(skelRoot + 0x384) + 0x15C) + 0xC) +
                       *(int *)(skelRoot + 0x388) * 0x40);
        MatrixDrive_TransMatrixV(skelRoot + 0x3A0);
        UnitRotation(MatrixDrive_GetMatrix());
        MultiMatrixByQuaternion((char *)skelRoot + 0x30);
        MatrixDrive_TransMatrix(rootMove[0], rootMove[1], rootMove[2]);
        CopyVector(skelRoot, (char *)MatrixDrive_GetMatrix() + 0x30);
    }

    Vec16 rq;
    Vec16 va;
    Vec16 vb;

    CopyQuaternion(&rq, *(char **)(*(char **)(*(char **)(skelRoot + 0x384) + 0x15C) + 0x10) +
                            *(int *)(skelRoot + 0x388) * 0x10);
    switch (*(unsigned int *)(skelRoot + 0x3B4)) {
    default:
    case 0:
        MultiQuaternion(skelRoot + 0x30, &rq, skelRoot + 0x390);
        CopyMatrix((void *)MatrixDrive_GetMatrix(),
                   *(char **)(*(char **)(*(char **)(skelRoot + 0x384) + 0x15C) + 0xC) +
                       *(int *)(skelRoot + 0x388) * 0x40);
        MultiMatrixByQuaternion((char *)skelRoot + 0x390);
        MatrixDrive_TransMatrixV(skelRoot + 0x3A0);
        MatrixDrive_TransMatrix(rootMove[0], rootMove[1], rootMove[2]);
        CopyVector(skelRoot, (char *)MatrixDrive_GetMatrix() + 0x30);
        break;
    case 1:
        break;
    case 3:
        GetRootQuaternion(&rq, *(char **)(skelRoot + 0x384));
        MultiQuaternion(&rq, &rq, *(char **)(*(char **)(skelRoot + 0x384) + 0x15C) + 0xE0);
        /* fall through */
    case 2:
        keepVerticalZWithQ(&rq);
        break;
    }
    _ScaleVector(&va, skelRoot + 0x150, 1.0f - *(float *)(skelRoot + 0x3B0));
    _ScaleVector(&vb, skelRoot, *(float *)(skelRoot + 0x3B0));
    _AddVector(skelRoot, &va, &vb);
    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0x1B0, skelRoot);
    CopyVector(skelRoot + 0x90, ZeroVector);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0xD0, rootDelta);
    *(int *)(skelRoot + 0x180) = -1;
    *(int *)(skelRoot + 0xC0) = 0;
    *(int *)(skelMotCtrl + 0x188) = 0;
    return InitialObjPointer;
}

MotShift rootUpdateY(void)
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
    ClipBuf w;
    ClipBuf cw;
    float d;
    int i;

    GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
    sceVu0ApplyMatrix((int *)&mv, (int)mtx, (char *)rootMove);
    sceVu0ApplyMatrix((int *)&mv2, (int)mtx, (char *)rootStep);

    CopyVector(skelRoot + 0x90, &mv2);
    sceVu0AddVector(skelRoot, skelRoot, skelRoot + 0x90);
    CopyVector(skelRoot + 0x1B0, skelRoot);

    GetPureVerticalPlane(0, vp, (float *)corner, (int *)(skelRoot + 0xE0), 0);
    CopyVector(plane, vp);
    plane[3] = 0.0f;

    memset(&center, 0, 16);
    center.f[3] = 1.0f;
    for (i = 0; i < 4; i++) {
        AddVectorXYZ(&center, &center, &corner[i]);
    }
    sceVu0ScaleVector(&center, &center, 0.25f);
    *(float *)(skelRoot + 0) = center.f[0];
    *(float *)(skelRoot + 8) = center.f[2];
    *(float *)(skelRoot + 0) = *(float *)(skelRoot + 0) + mv.f[0];
    *(float *)(skelRoot + 8) = *(float *)(skelRoot + 8) + mv.f[2];

    CopyVector(&pos, skelRoot);
    pos.f[1] = pos.f[1] - rootMove[1];
    d = GetDistanceFromPlane(vp, &pos);
    sceVu0ScaleVector(&push, vp, -d - rootMove[2]);
    AddVectorXYZ(&pos, &pos, &push);
    pos.f[3] = 1.0f;
    CopyVector(skelRoot, &pos);
    *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + rootMove[1];
    sceVu0ScaleVectorXYZ(skelMotCtrl + 0xB0, plane, -1.0f);

    if (*(int *)(skelRoot + 0x314) != 0) {
        float t = *(float *)(skelRoot + 4) - mv.f[1];
        float e;

        t = t - (float)((int)(t / 50.0f) * 50);
        if (t < 0.0f) {
            t = t + 50.0f;
        }
        if (t > 25.0f) {
            e = 50.0f - t;
            *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) + e;
        } else {
            *(float *)(skelRoot + 4) = *(float *)(skelRoot + 4) - t;
        }
    }

    getFieldCollision((char *)&w);
    CopyVector(skelRoot + 0x130, (char *)&w + 0xA0);
    clipWallAhead(&cw);
    if (*(int *)((char *)&cw + 0x88) != 0) {
        WallCfg rec = {((WallCfg *)((char *)&cw + 0x80))->o, ((WallCfg *)((char *)&cw + 0x80))->n};

        *(WallCfg *)(skelRoot + 0x100) = rec;
    }

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(*(float *)(skelRoot + 0), *(float *)(skelRoot + 4) + 100.0f,
                            *(float *)(skelRoot + 8));
    MultiMatrixByQuaternion(skelRoot + 0x30);
    checkWallState(2);
    MatrixDrive_PopMatrix();

    CopyVector(skelRoot + 0x150, skelRoot);
    CopyVector(skelRoot + 0xD0, rootDelta);
    CopyVector(skelRoot + 0x10, ZeroVector);
    *(int *)(skelRoot + 0x180) = -1;
    return *(MotShift *)(skelRoot + 0xE0);
}

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

    CopyVector(skelRoot + 0x1B0, skelRoot);
    mode = *(int *)(skelRoot + 0x380);
    if (mode >= 2) {
        GetMatrixFromQuaternion(mtx, skelRoot + 0x30);
        sceVu0ApplyMatrix((int *)&dir, (int)mtx, (char *)rootMove);
        sceVu0AddVector(&pos, skelRoot + 0x370, &dir);
        *(float *)skelRoot = pos.f[0];
        *(float *)(skelRoot + 8) = pos.f[2];
    } else if (mode != 0) {
        int node = GetSkeltonFocusNode((char *)skelGObj, 22);

        v.f[0] = *(float *)skelRoot;
        v.f[1] = *(float *)(skelRoot + 4);
        v.f[2] = *(float *)(skelRoot + 8);
        _SubVector(skelRoot, skelRoot + 0x370, nodePos2 + node * 0x10);
        if (*(int *)(skelRoot + 0x380) < 0) {
            _InterGV(skelRoot, &v, skelRoot, ropeInterRate, 1.0f);
        }
    }
    save = *(float *)(skelRoot + 0x338);
    CopyVector(&cur, skelRoot);
    CopyVector(&v, skelRoot + 0x150);
    *(float *)(skelRoot + 0x338) = 60.0f;
    wallCollisionAndFloorFit((char *)&cur, (char *)&v, 5.0f);
    *(float *)(skelRoot + 0x338) = save;
    /* 0xEC is the float landingFieldAction and rootUpdateFly write. */
    *(float *)(skelMotCtrl + 0xEC) = 0.0f;
    *(int *)(skelRoot + 0xC0) = 0;
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0x1B0, skelRoot);
    CopyVector(skelRoot + 0x150, skelRoot);
    *(int *)(skelRoot + 0x180) = -1;
    return InitialObjPointer;
}

MotShift rootUpdateFly(void)
{
    MotShift shift = {0, -1};
    char w[0xC0];
    int contact;
    float h;
    float d;

    *(int *)(skelMotCtrl + 0x188) = 0;
    contact = getFlyFieldCollision(w);
    switch (contact) {
    case 1:
        *(int *)(skelMotCtrl + 0x14) |= 8;
        h = *(float *)(skelRoot + 0x1B4);
        CopyVector(skelRoot + 0x130, w + 0xA0);
        d = GetYProjectionOfPlane((int)(w + 0xA0), (int)skelRoot);
        d = d - h;
        *(float *)(skelMotCtrl + 0xEC) = d;
        break;
    case 2:
        markPoolContact(w);
        break;
    }
    wallCollisionAndReact(*(float *)(skelNode + 0x14));
    *(int *)(skelRoot + 0xC0) = 0;
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0x90, ZeroVector);
    CopyVector(skelRoot + 0x150, skelRoot);
    *(int *)(skelRoot + 0x180) = -1;
    return shift;
}

MotShift rootUpdateEnemyFly(void)
{
    MotShift shift = {0, -1};
    char w[0xC0];
    int contact;

    AddVectorXYZ(skelRoot, skelRoot, skelRoot + 0x90);
    if (*(int *)((int)GOBJ_SUB(skelGObj) + 0x654) == 0) {
        wallCollisionAndReact(0.0f);
        contact = getFlyFieldCollision(w);
        switch (contact) {
        case 1:
            CopyVector(skelRoot + 0x1B0, skelRoot);
            *(float *)(skelMotCtrl + 0xEC) = 0.0f;
            CopyVector(skelRoot + 0x130, w + 0xA0);
            *(int *)(skelMotCtrl + 0x14) |= 8;
            break;
        case 2:
            markPoolContact(w);
            break;
        }
    }
    *(int *)(skelRoot + 0xC0) = 0;
    SubVectorXYZ(skelRoot + 0x90, skelRoot, skelRoot + 0x150);
    CopyVector(skelRoot + 0x10, ZeroPoint);
    CopyVector(skelRoot + 0x150, skelRoot);
    *(int *)(skelRoot + 0x180) = -1;
    return shift;
}
