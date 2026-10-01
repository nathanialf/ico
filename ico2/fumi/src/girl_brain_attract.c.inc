/* girl_brain_attract.c.inc -- the girl brain's "attract" state, #included as source into one
 * girl_act.o.  The PAL listing (baserom/pal/SRCFILE.TXT) attributes these bodies to
 * fumi/src/girl_brain_attract.c.inc and links them into girl_act.o; the census in
 * docs/pal_source_tree.json records the include.  Its includer in the 2002 tree is
 * girl_brain_main.c.inc, which is not split out yet (see docs/HEADERS.md), so the include
 * sits at the same point of girl_act.c that girl_brain_main.c.inc's text occupies today.
 * INCLUDE_ASM paths name the INCLUDER's asm directory because splat splits by the
 * translation unit, not by the included file. */

int ATGoalTurnMail(void *actor, float *dir, int node);
/* kept local: void (void *, int, void *, void *) here, int (char *, int, void *, void *) in mail-add-data.h */
extern void ActSendMail_WithAdditionalData(void *gop, int msg, void *sender, void *data);

static void *attractMailData; /* derived name */

/* girl_brain_attract.c.inc:9-20 in the listing, expanded twice in
   subGirlBrain_Attract: turn toward the target, and when already facing it
   send the attract mail with the target attached.  The result (whether a turn
   was started) is dropped by both callers; it keeps the mail out of tail
   position, and integrate.c does not inline a body carrying a sibling call. */
static inline int girlAttractTurnMailL(void *actor, void *obj, float *from, float *to)
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (ATGoalTurnMail(actor, dir, 0x2C)) {
        return 1;
    }
    attractMailData = obj;
    ActSendMail_WithAdditionalData(actor, 0x156, actor, &attractMailData);
    return 0;
}

/* girl_brain_attract.c.inc:33-41: the same turn toward the boy, then the
   plain mail. */
static inline int girlAttractTurnMailR(void *actor, float *from, float *to)
{
    float dir[4];

    _OrientXZGV(dir, from, to);
    if (!ATGoalTurnMail(actor, dir, 0x2C)) {
        ACTSendMailCorrect(actor, 0x158);
        return 0;
    }
    return 1;
}

/* kept local: agrees with act-game.h, which this TU does not include */
extern void GetSkeltonOrient(float *out, void *obj, int node);

int ATGoalTurnMail(void *actor, float *dir, int node)
{
    float o1[4];
    float v[4];
    float o2[4];
    int r1;
    int m;
    int r2;
    int d;
    int ret;

    ret = 0;
    v[0] = dir[0];
    v[1] = dir[1];
    v[2] = dir[2];
    GetSkeltonOrient(o1, actor, 0x2C);
    r1 = _RotyGV(o1, v);
    m = (r1 < 0) ? -r1 : r1;
    if (m >= 0x15) {
        GetSkeltonOrient(o2, actor, node);
        r2 = _RotyGV(o2, v);
        if (m >= 0x5A) {
            goto use_r2;
        }
        if (r1 * r2 < 0) {
            goto set_r1;
        }
    use_r2:
        d = r2;
        goto have_d;
    set_r1:
        d = r1;
    have_d:
        if (d > 0) {
            ATGoalTurnSet(actor, 2, 2, v);
        } else {
            ATGoalTurnSet(actor, 2, 1, v);
        }
        ret = 1;
    }
    return ret;
}

/* kept local: agrees with commonact.h, which this TU does not include */
extern float *test_CURRENTROOT(void *a0);

int checkWaterfallResult(float *out)
{
    union {
        float f[4];
        int i[4];
    } t;

    float pa[4];
    float pb[4];
    int r1;
    int r0;
    int ret;

    r1 = -1;
    r0 = -1;
    ret = 0;
    GetRootProjectionPosOfGObj(pa, boyGObj);
    GetRootProjectionPosOfGObj(pb, girlGObj);
    if (1600.0f < pb[1] && pb[1] < 2300.0f) {
        if (pb[2] < -150.0f) {
            r1 = 0;
        } else if (850.0f < pb[2]) {
            r1 = 2;
        } else {
            r1 = 1;
        }
    }
    if (1600.0f < pa[1] && pa[1] < 2300.0f) {
        if (pa[2] < -150.0f) {
            r0 = 0;
        } else if (850.0f < pa[2]) {
            r0 = 2;
        } else {
            r0 = 1;
        }
    }
    if (r0 == -1) {
        return 0;
    }
    if (r1 == -1) {
        return 0;
    }
    if (r1 == 1) {
        return 1;
    }
    if (r0 == 1) {
        if (*(void **)((char *)GOBJ_SUB(boyGObj)) != 0 &&
            *(int *)((char *)*(void **)((char *)GOBJ_SUB(boyGObj)) + 0xC) == 17) {
            t.f[0] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[0];
            t.f[1] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[1];
            t.f[2] = (test_CURRENTROOT(*(void **)((char *)GOBJ_SUB(boyGObj))))[2];
        } else {
            return 1;
        }
    }
    if (r1 == 0 && r0 != 0) {
        ret = 1;
        if (r0 == 1 && t.f[2] < -50.0f) {
            out[0] = pa[0];
            out[1] = 1800.0f;
            out[2] = -170.0f;
            ret = 2;
        }
    }
    if (r1 == 2 && r0 != r1) {
        ret = 1;
        if (r0 == 1 && 750.0f < t.f[2] && 650.0f < t.f[0] && t.f[0] < 950.0f) {
            out[0] = pa[0];
            out[1] = 1900.0f;
            out[2] = 870.0f;
            ret = 2;
        }
    }
    return ret;
}

/* kept local: brain.h has no row for the target timer; the ROM passes the target object. */
extern int brainDecTargetTimer(void *gobj);
/* kept local: agrees with act-game.h, which this TU does not include */
extern void _GetRootObjectOrient(void *a0, char *a1);

/* One 0x50-byte record per act status, indexed by the actor's status at
   0x34 (act.c reads the same table).  The flags word at 0x4C is a bitfield:
   the ROM keeps 0x4C as the load displacement at all three sites here, which
   only a bitfield reference produces.  The field names are ours. */
typedef struct {
    struct {
        int f0;
        int f4;
        int f8;
    } ent[6];

    int f48;

    unsigned int _b0 : 3;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int _b5 : 27;
} GirlStatusAttr;

extern char actModeTbl[];

/* The record Act.f_680 points at, as far as this file uses it: the sofa
   position the attract state hands over (copied from the actor's 0x5B0) and
   the facing _GetRootObjectOrient fills for it.  The ROM's schedule proves
   these are field references (in-struct MEMs), not casts off an int. */
typedef struct {
    char _000[0x230];
    sceVu0FVECTOR pos; /* 0x230 */
    sceVu0FVECTOR dir; /* 0x240 */
} GirlSofaWork;

/* the three attract parameter sets */
static GirlAttractParam attractObjParam = {0, {0}, {0}, 0, 338, 100.0f, 100.0f}; /* derived name */

static GirlAttractParam attractSofaParam = {0, {0}, {0}, 68, 267, 50.0f, 100.0f,
                                            1, {0}, {0}, 0,  {0}, 200.0f}; /* derived name */

static GirlAttractParam attractBoyParam = {0, {0}, {0}, 0, 338, 100.0f, 70.0f}; /* derived name */

/* The actor entry parameter is volatile: the actor scheduler writes the
 * caller's home slot while this thread is parked in _ACTWait. */
void subGirlBrain_Attract(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float mypos[4];
    float last[4];
    GirlAttractParam tgt;
    int cnt;
    void *cur = brain_val.lastTarget;
    int type = 0;
    int kind;
    int param = 0;
    int dbg = 0; /* local debug switch, see the rate block below */
    int fr = (60 - systemStatus[0] * 10) / systemStatus[1];
    int fr3 = fr + (60 - systemStatus[0] * 10) / systemStatus[1] * 2;
    int turnCnt = 0;
    int hintCnt = 0;

    /* girl_brain_attract.c.inc:257-259 and 261-271 in the listing: two
       nested helpers.  Their references to cnt, sub and cur are what give
       those three their frame slots at 0x90/0x94/0x98, between the target
       record and the vectors declared after them, and the kind test reads
       cur through the static chain (`move $a1,$sp; lw 0x98($a1)`). */
    __inline__ void setMode(int mode)
    {
        cnt = 0;
        sub->f_350 = mode;
    }
    __inline__ int getKind(void)
    {
        if (cur == (void *)boyGObj && GOBJ_ACT(boyGObj)->unk34 == 45) {
            return 0;
        } else if (*(int *)((char *)cur + 0xC) == 16) {
            return 1;
        } else if (GOBJ_ACT(boyGObj)->unk34 == 49 &&
                   *(int *)GOBJ_SUB(girlGObj) == (int)GOBJ_ACT(boyGObj)->box) {
            return 2;
        }
        return 3;
    }
    float root[4];

restart:
    setMode(0);
    if (cur == 0) {
        debug_assert(__FILE__, 279);
        __assert(__FILE__, 279, "0");
    }
    kind = getKind();
    switch (kind) {
    case 0:
        type = 1;
        param = GOBJ_ACT(boyGObj)->f_61C;
        break;
    case 1:
        type = 1;
        param = (int)cur;
        break;
    case 2:
        type = 2;
        param = 0;
        break;
    case 3:
        type = 0;
        param = 0;
        break;
    }
    switch (type) {
    case 0:
        tgt = attractObjParam;
        tgt.obj = cur;
        GetRootProjectionPosOfGObj(tgt.pos, cur);
        break;
    case 1:
        tgt = attractSofaParam;
        tgt.obj = cur;
        GetSofaPosition(girlGObj, (char *)param);
        tgt.pos[0] = sub->f_5B0;
        tgt.pos[1] = sub->f_5B4;
        tgt.pos[2] = sub->f_5B8;
        ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->pos[0] = sub->f_5B0;
        ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->pos[1] = sub->f_5B4;
        ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->pos[2] = sub->f_5B8;
        _GetRootObjectOrient(((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->dir, param);
        tgt.dir[0] = ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->dir[0];
        tgt.dir[1] = ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->dir[1];
        tgt.dir[2] = ((GirlSofaWork *)GOBJ_ACT(a0)->f_680)->dir[2];
        tgt.f_50 = 1;
        break;
    case 2:
        tgt = attractBoyParam;
        tgt.obj = boyGObj;
        GetRootProjectionPosOfGObj(tgt.pos, boyGObj);
        break;
    }
    for (;;) {
        int noTurn = 1;
        int waterHit = 0;
        int hint = 0;
        int escape = 0;
        int far = 0;
        int type2;
        float margin;
        float ratio;

        root[0] = test_CURRENTROOT((void *)a0)[0];
        root[1] = test_CURRENTROOT((void *)a0)[1];
        root[2] = test_CURRENTROOT((void *)a0)[2];
        if (tgt.obj != 0 && *(int *)((char *)tgt.obj + 0xC) == 32 &&
            !(_DistSqGV(root, test_CURRENTROOT(tgt.obj)) < 90000.0f)) {
            far = 1;
        }
        if (!ACTGame_FLAG_TETSUNAGI()) {
            sub->flags20.ll |= 0x2000000000ULL;
        }
        if (type == 0 && tgt.obj == (void *)boyGObj && GOBJ_WORK(a0)->f_380 != 0) {
            noTurn = 0;
        }
        if (*(int *)GOBJ_SUB(a0) != 0 && *(int *)(*(int *)GOBJ_SUB(a0) + 0xC) == 17 &&
            boyGObj != 0 && type == 0 && tgt.obj == (void *)boyGObj &&
            root[1] < test_CURRENTROOT(boyGObj)[1] &&
            _DistSqGV(test_CURRENTROOT((void *)a0), test_CURRENTROOT(boyGObj)) <
                _ACTGame_GetParamF(30) * _ACTGame_GetParamF(30)) {
            hint = 1;
            escape = 1;
        }
        if ((int)(sub->flags20.ll >> 38) & 1) {
            hint = 1;
        }
        if (0 < brain_val.f_590C) {
            _ACTCharStatus_Set((void *)a0, 31, -1.0f, 0);
        }
        if (kind != getKind()) {
            goto restart;
        }
        type2 = girlBrainGetTargetType((void *)a0);
        GetRootProjectionPosOfGObj(mypos, (void *)a0);
        if (tgt.f_30 == 0) {
            int onSofa = 0;
            float dir[4];
            float ofs[4];

            if (tgt.obj == (void *)boyGObj && GOBJ_ACT(tgt.obj)->unk34 == 28) {
                onSofa = 1;
                dir[0] = test_CURRENTORIENT(boyGObj)[0];
                dir[1] = test_CURRENTORIENT(boyGObj)[1];
                dir[2] = test_CURRENTORIENT(boyGObj)[2];
            }
            if (onSofa) {
                sceVu0ScaleVector(ofs, dir, 50.0f);
                GetSkeltonPosition(tgt.pos, boyGObj, 22);
                sceVu0AddVector(tgt.pos, tgt.pos, ofs);
                tgt.pos[1] = tgt.pos[1] - 10.0f;
            } else {
                GetRootProjectionPosOfGObj(tgt.pos, tgt.obj);
            }
            if ((int)(GOBJ_ACT(boyGObj)->flags20.ll >> 43) & 1) {
                float wp[4];

                switch (checkWaterfallResult(wp)) {
                case 1:
                    tgt.pos[0] = mypos[0];
                    tgt.pos[1] = mypos[1];
                    tgt.pos[2] = mypos[2];
                    if (tgt.obj != 0) {
                        GirlBrainClearTarget((void *)a0, &tgt);
                    }
                    break;
                case 2:
                    tgt.pos[0] = wp[0];
                    tgt.pos[1] = wp[1];
                    tgt.pos[2] = wp[2];
                    waterHit = 1;
                    break;
                }
            }
        }
        dispWayMarker(tgt.pos);
        if (tgt.obj != 0) {
            if (brainDecTargetTimer(tgt.obj)) {
                GirlBrainClearTarget((void *)a0, &tgt);
            }
        }
        if (boyGObj != 0 && GOBJ_ACT(boyGObj)->unk34 == 49) {
            if (tgt.obj == (void *)boyGObj || tgt.obj == GOBJ_ACT(boyGObj)->box) {
                GirlBrainClearTarget((void *)a0, &tgt);
            }
        }
        if (sub->unk34 == 81) {
            if (tgt.obj == (void *)boyGObj) {
                GirlBrainClearTarget((void *)a0, &tgt);
            }
        }
        if (sub->f_350 == 3) {
            if (girlBrainGetTypeRatio(type2) == 0.0f) {
                setMode(0);
            }
        }
        {
            float level = girlBrainGetTargetLevel();
            float speed = _ACTGame_GetParamF(29) + level * (1.0f - _ACTGame_GetParamF(29));
            float clamped;

            clamped = (speed < _ACTGame_GetParamF(29)) ? _ACTGame_GetParamF(29)
                                                       : ((1.0f < speed) ? 1.0f : speed);
            ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, clamped, 1);
        }
        {
            float rate = girlBrainGetTargetLevel() * 4.0f;
            float lo = _ACTGame_GetParamF(27);
            float hi = _ACTGame_GetParamF(28);
            float v = lo + rate * (hi - lo);

            v = (v < lo) ? lo : ((hi < v) ? hi : v);
            /* A second speed, computed and clamped like the one above and
               applied only with the debug switch set.  What the bytes pin:
               the ROM keeps this clamp's compares with nothing reading v
               (listing rows 497-503, rows 504-507 code-free), and gcse's
               table size (the spill slots at 0x104..0x11C) counts the
               switched-off arm.  What they cannot pin: the switch's name or
               the arm's exact call. */
            if (dbg) {
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, v, 1);
            }
        }
        if (((int)(sub->flags18.ll >> 62) & 1) && type == 0 && tgt.obj == (void *)boyGObj) {
            if (sub->f_350 == 7) {
                if (!(_DistSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) <
                      10000.0f)) {
                    setMode(1);
                }
            }
        }
        switch (sub->f_350) {
        case 0:
            _ACTLookTarget_Set((void *)a0, 0, 0, 6, 1);
            sub->f_34C = 0.0f;
            setMode(6);
            break;
        case 1: {
            int p = ACTWayMove_BeginDetail((void *)a0, mypos, tgt.pos, tgt.obj, 0, 0);

            if (tgt.f_30 != 0) {
                sub->wayState.bits.wayDetail = 1;
            }
            if (p != 0) {
                setMode(3);
                last[0] = tgt.pos[0];
                last[1] = tgt.pos[1];
                last[2] = tgt.pos[2];
                turnCnt = 0;
                hintCnt = 0;
            } else {
                setMode(2);
            }
            break;
        }
        case 3: {
            int p = ACTWayMove_NextDetail((void *)a0, (char *)sub + 0x120, tgt.pos, 0,
                                          tgt.obj != 0 && IsTopHint(tgt.obj));

            if (GOBJ_ACT(a0)->unk34 == 45) {
                if (type == 1) {
                    setMode(4);
                    break;
                }
            } else if (type == 1) {
                if (tgt.obj != (void *)boyGObj && GOBJ_WORK(a0)->f_3A4 != 0) {
                    setMode(8);
                    sub->f_34C = 0.0f;
                    break;
                }
                if (type == 1 && ((int)(sub->flags20.ll >> 12) & 1) &&
                    _DistSqGV(test_CURRENTROOT((void *)a0), tgt.pos) < 40000.0f) {
                    setMode(2);
                    break;
                }
            }
            if (p == 0) {
                setMode(2);
            } else if ((int)((unsigned long long)sub->f_3F0 >> 17) & 1) {
                setMode(2);
            } else if (hint) {
                setMode(2);
            } else {
                if (!noTurn) {
                    margin = 100.0f;
                } else if (sub->unk34 == 3 && (double)girlBrainGetTypeRatio(type2) > 0.8) {
                    margin = 100.0f;
                } else {
                    margin = 0.0f;
                }
                sub->dir[0] = sub->f_3E0;
                sub->dir[1] = sub->f_3E4;
                sub->dir[2] = sub->f_3E8;
                if (waterHit) {
                    if (sub->f_3F8 < 50.0f && sub->f_3FC < tgt.f_2C) {
                        setMode(4);
                        sub->f_34C = 0.0f;
                    } else if (sub->f_3F8 < 300.0f) {
                        girlBrainSetWalkRatio((void *)a0, 0.5f);
                    } else {
                        ratio = far ? 1.0f : girlBrainGetTypeRatio(type2);
                        girlBrainSetWalkRatio((void *)a0, ratio);
                    }
                } else {
                    if (sub->f_3F8 < tgt.f_28 + margin &&
                        ((sub->f_3FC < 0.0f) ? -sub->f_3FC : sub->f_3FC) < tgt.f_2C) {
                        if (tgt.f_50) {
                            if (ATGoalTurnMail((void *)a0, tgt.dir, 0x23)) {
                                noTurn = 0;
                            }
                        }
                        if (noTurn) {
                            setMode(4);
                        } else {
                            sub->f_34C = 0.0f;
                        }
                    } else {
                        ratio = far ? 1.0f : girlBrainGetTypeRatio(type2);
                        girlBrainSetWalkRatio((void *)a0, ratio);
                        if (sub->f_3F8 < tgt.f_54) {
                            sub->f_34C = (0.5f < sub->f_34C) ? 0.5f : sub->f_34C;
                        }
                    }
                }
            }
            if (!(_DistSqGV(last, tgt.pos) < 90000.0f)) {
                if (_DistSqGV(mypos, tgt.pos) > _DistSqGV(mypos, last)) {
                    brainSubLevelGop(tgt.obj, 0.5f);
                }
                last[0] = tgt.pos[0];
                last[1] = tgt.pos[1];
                last[2] = tgt.pos[2];
            }
            if (tgt.obj != (void *)boyGObj && !(tgt.obj != 0 && IsTopHint(tgt.obj)) &&
                !ACTGameViewSimple_Check((void *)a0, tgt.obj)) {
                switch (sub->unk34) {
                case 2:
                    turnCnt = turnCnt + 1;
                    break;
                case 3:
                    turnCnt = turnCnt + 2;
                    break;
                }
                if ((60 - systemStatus[0] * 10) / systemStatus[1] * 15 < turnCnt) {
                    setMode(2);
                }
            }
            if (tgt.obj != 0 && IsTopHint(tgt.obj) &&
                ((int)((unsigned long long)sub->f_3F0 >> 18) & 1)) {
                hintCnt = hintCnt + ((GirlStatusAttr *)actModeTbl)[GOBJ_ACT(a0)->unk34].b4;
                if ((60 - systemStatus[0] * 10) / systemStatus[1] * 4 < hintCnt) {
                    sub->f_34C = 0.0f;
                }
                if ((60 - systemStatus[0] * 10) / systemStatus[1] * 5 < hintCnt) {
                    setMode(2);
                }
            }
            break;
        }
        case 6:
            if (fr < cnt || brain_val.f_58F3 != 0) {
                if (girlBrainGetTypeRatio(type2) != 0.0f) {
                    setMode(1);
                }
            }
            /* fallthrough */
        case 2:
        case 7:
            if (cnt++ < fr3 + ((tgt.obj != 0 && IsTopHint(tgt.obj))
                                   ? (60 - systemStatus[0] * 10) / systemStatus[1] * 2
                                   : 0)) {
                sub->f_34C = 0;
                _ACTLookTarget_Set((void *)a0, tgt.obj, 0, 2, 1);
                if (tgt.obj != 0 && IsTopHint(tgt.obj) && sub->f_350 == 2 && girlControlMode == 0) {
                    girlAttractTurnMailL((void *)a0, tgt.obj, tgt.pos, mypos);
                    if (((GirlStatusAttr *)actModeTbl)[GOBJ_ACT(a0)->unk34].b3) {
                        cnt = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
                    }
                }
                if (tgt.obj == (void *)boyGObj && sub->f_350 == 2 && escape == 0 &&
                    GOBJ_WORK(a0)->f_3B0 == 0 && girlControlMode == 0 &&
                    brain_val.targetFlag != 0) {
                    girlAttractTurnMailR((void *)a0, tgt.pos, mypos);
                    if (sub->unk34 == 77) {
                        cnt = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
                    }
                }
            } else {
                _ACTLookTarget_Set((void *)a0, 0, 0, 6, 1);
                setMode(8);
            }
            if (((int)(sub->flags18.ll >> 63) & 1) || (*(int *)((char *)sub + 0x20) & 1)) {
                sub->flags20.ll |= 2;
            }
            break;
        case 4:
            if (tgt.kind == 0 && (tgt.obj == 0 || !IsTopHint(tgt.obj))) {
                setMode(7);
            } else {
                setMode(5);
            }
            break;
        case 5:
            if (cnt++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 200 / 60 +
                            ((tgt.obj != 0 && IsTopHint(tgt.obj))
                                 ? (60 - systemStatus[0] * 10) / systemStatus[1] * 2
                                 : 0)) {
                sub->f_34C = 0.0f;
                if (tgt.obj != 0 && IsTopHint(tgt.obj) && girlControlMode == 0) {
                    girlAttractTurnMailL((void *)a0, tgt.obj, tgt.pos, mypos);
                    if (((GirlStatusAttr *)actModeTbl)[GOBJ_ACT(a0)->unk34].b3) {
                        cnt = (60 - systemStatus[0] * 10) / systemStatus[1] * 10;
                    }
                } else {
                    sub->f_44 = tgt.kind;
                    ACTSendMailCorrect((void *)a0, tgt.mail);
                }
            } else {
                setMode(8);
            }
            break;
        case 8:
            cnt = cnt + 1;
            if (cnt == 2) {
                GirlBrainClearTarget((void *)a0, &tgt);
            }
            if ((60 - systemStatus[0] * 10) / systemStatus[1] < cnt) {
                setMode(0);
            }
            break;
        }
        _ACTWait(1);
    }
}
