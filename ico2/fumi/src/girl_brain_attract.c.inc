/* girl_brain_attract.c.inc: the girl brain's "attract" state, #included as
 * source into girl_act.c.  Its includer in the 2002 tree is
 * girl_brain_main.c.inc, which is not split out, so the include sits at the
 * point of girl_act.c that girl_brain_main.c.inc's text occupies. */

/* The demo's attract state has no goal turn: no ATGoalTurnMail and no turn-mail
   helpers (the August build adds them). */

/* The record Act.enemy points at, as far as this file uses it: the sofa
   position the attract state hands over (copied from the actor's 0x580) and
   the facing _GetRootObjectOrient fills for it. */
typedef struct { /* field names derived */
    char pad0[560];
    sceVu0FVECTOR pos; /* 0x230 */
    sceVu0FVECTOR dir; /* 0x240 */
} GirlSofaWork;        /* derived name */

/* the three attract parameter sets */
static GirlAttractParam attractObjParam = {0, {0}, {0}, 0, 303, 100.0f, 100.0f}; /* derived name */

static GirlAttractParam attractSofaParam = {0,   {0},   {0},    59,
                                            241, 50.0f, 100.0f, 1}; /* derived name */

static GirlAttractParam attractBoyParam = {0, {0}, {0}, 0, 303, 100.0f, 70.0f}; /* derived name */

/* The actor entry parameter is volatile: the actor scheduler writes the
 * caller's home slot while this thread is parked in _ACTWait. */
void subGirlBrain_Attract(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float mypos[4];
    float last[4];
    GirlAttractParam tgt;
    int cnt;
    void *cur = brain_val.lastTarget;
    int type = 0;
    int kind;
    GObj *param = 0;
    int dbg = 0; /* local debug switch, see the rate block below */
    int fr = (60 - systemStatus[0] * 10) / systemStatus[1];
    int fr3 = fr + (60 - systemStatus[0] * 10) / systemStatus[1] * 2;

    /* two nested helpers, which read cnt, sub and cur through the static chain */
    __inline__ void setMode(int mode) /* derived name */
    {
        cnt = 0;
        sub->wayMode = mode;
    }
    __inline__ int getKind(void) /* derived name */
    {
        if (cur == (void *)boyGObj && GOBJ_ACT(boyGObj)->actMode == 45) {
            return 0;
        } else if (*(int *)((char *)cur + 0xC) == 16) {
            return 1;
        } else if (GOBJ_ACT(boyGObj)->actMode == 49 &&
                   *(int *)GOBJ_SUB(girlGObj) == (int)GOBJ_ACT(boyGObj)->box) {
            return 2;
        }
        return 3;
    }

restart:
    setMode(0);
    if (cur == 0) {
        debug_assert(__FILE__, 98);
        __assert(__FILE__, 98, "0");
    }
    kind = getKind();
    switch (kind) {
    case 0:
        type = 1;
        param = GOBJ_ACT(boyGObj)->env.sofaObj.obj;
        break;
    case 1:
        type = 1;
        param = cur;
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
        GetSofaPosition(girlGObj, param);
        tgt.pos[0] = sub->env.sofaPos[0];
        tgt.pos[1] = sub->env.sofaPos[1];
        tgt.pos[2] = sub->env.sofaPos[2];
        ((GirlSofaWork *)GOBJ_ACT(self)->enemy)->pos[0] = sub->env.sofaPos[0];
        ((GirlSofaWork *)GOBJ_ACT(self)->enemy)->pos[1] = sub->env.sofaPos[1];
        ((GirlSofaWork *)GOBJ_ACT(self)->enemy)->pos[2] = sub->env.sofaPos[2];
        _GetRootObjectOrient(((GirlSofaWork *)GOBJ_ACT(self)->enemy)->dir, param);
        break;
    case 2:
        tgt = attractBoyParam;
        tgt.obj = boyGObj;
        GetRootProjectionPosOfGObj(tgt.pos, boyGObj);
        break;
    }
    for (;;) {
        int type2;
        float margin;
        float ratio;

        if (0 < brain_val.status31Timer) {
            _ACTCharStatus_Set((void *)self, 26, -1.0f, 0);
        }
        if (kind != getKind()) {
            goto restart;
        }
        type2 = girlBrainGetTargetType((void *)self);
        GetRootProjectionPosOfGObj(mypos, (void *)self);
        if (tgt.fixedPos == 0) {
            GetRootProjectionPosOfGObj(tgt.pos, tgt.obj);
        }
        dispWayMarker(tgt.pos);
        if (tgt.obj != 0) {
            if (brainDecTargetTimer(tgt.obj)) {
                GirlBrainClearTarget((void *)self, &tgt);
            }
        }
        if (boyGObj != 0 && GOBJ_ACT(boyGObj)->actMode == 49) {
            if (tgt.obj == (void *)boyGObj || tgt.obj == GOBJ_ACT(boyGObj)->box) {
                GirlBrainClearTarget((void *)self, &tgt);
            }
        }
        if (sub->actMode == 77) {
            if (tgt.obj == (void *)boyGObj) {
                GirlBrainClearTarget((void *)self, &tgt);
            }
        }
        if (sub->wayMode == 3) {
            if (girlBrainGetTypeRatio(type2) == 0.0f) {
                setMode(0);
            }
        }
        {
            float level = girlBrainGetTargetLevel();
            float speed = _ACTGame_GetParamF(24) + level * (1.0f - _ACTGame_GetParamF(24));
            float clamped;

            clamped = (speed < _ACTGame_GetParamF(24)) ? _ACTGame_GetParamF(24)
                                                       : ((1.0f < speed) ? 1.0f : speed);
            ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, clamped, 1);
        }
        {
            float rate = girlBrainGetTargetLevel() * 4.0f;
            float lo = _ACTGame_GetParamF(22);
            float hi = _ACTGame_GetParamF(23);
            float v = lo + rate * (hi - lo);

            v = (v < lo) ? lo : ((hi < v) ? hi : v);
            /* a second speed, computed and clamped like the one above and applied only
               with the debug switch set */
            if (dbg) {
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, v, 1);
            }
        }
        if (((int)(sub->flags18.ll >> 51) & 1) && type == 0 && tgt.obj == (void *)boyGObj) {
            if (sub->wayMode == 7) {
                if (!(_DistSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) <
                      10000.0f)) {
                    setMode(1);
                }
            }
        }
        switch (sub->wayMode) {
        case 0:
            _ACTLookTarget_Set((void *)self, 0, 0, 6, 1);
            sub->stick.mag = 0.0f;
            setMode(6);
            break;
        case 1: {
            int p = ACTWayMove_BeginDetail((void *)self, mypos, tgt.pos, tgt.obj, 0);

            if (tgt.fixedPos != 0) {
                sub->wayState.flags |= 0x1000000000000LL;
            }
            if (p == 0) {
                setMode(2);
            } else {
                setMode(3);
                last[0] = tgt.pos[0];
                last[1] = tgt.pos[1];
                last[2] = tgt.pos[2];
            }
            break;
        }
        case 3: {
            int p = ACTWayMove_NextDetail((void *)self, sub->dir, tgt.pos);

            if (GOBJ_ACT(self)->actMode == 45) {
                if (type == 1) {
                    setMode(4);
                    break;
                }
            }
            if (p == 0) {
                setMode(2);
            } else if ((int)((unsigned long long)sub->wayFlags >> 16) & 1) {
                setMode(2);
            } else {
                if (sub->actMode == 3 && (double)girlBrainGetTypeRatio(type2) > 0.8) {
                    margin = 100.0f;
                } else {
                    margin = 0.0f;
                }
                sub->dir[0] = sub->wayNodeX;
                sub->dir[1] = sub->wayNodeY;
                sub->dir[2] = sub->wayNodeZ;
                if (sub->wayGoalDist < tgt.goalDist + margin &&
                    sub->wayGoalHeight < tgt.goalHeight) {
                    setMode(4);
                } else {
                    ratio = girlBrainGetTypeRatio(type2);
                    girlBrainSetWalkRatio((void *)self, ratio);
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
            break;
        }
        case 6:
            if (fr < cnt || brain_val.lookHold != 0) {
                if (girlBrainGetTypeRatio(type2) != 0.0f) {
                    setMode(1);
                }
            }
            /* fallthrough */
        case 2:
        case 7:
            if (cnt++ < fr3) {
                sub->stick.mag = 0;
                _ACTLookTarget_Set((void *)self, tgt.obj, 0, 2, 1);
            } else {
                _ACTLookTarget_Set((void *)self, 0, 0, 6, 1);
                setMode(8);
            }
            if ((sub->flags18.ll & (1ULL << 53)) || (sub->flags18.ll & (1ULL << 52))) {
                sub->flags18.ll |= 1ULL << 54;
            }
            break;
        case 4:
            if (tgt.kind == 0) {
                setMode(7);
            } else {
                setMode(5);
            }
            break;
        case 5:
            if (cnt++ < (60 - systemStatus[0] * 10) / systemStatus[1] * 200 / 60) {
                sub->stick.mag = 0.0f;
                sub->orientMot = tgt.kind;
                ACTSendMailCorrect((void *)self, tgt.mail);
            } else {
                setMode(8);
            }
            break;
        case 8:
            cnt = cnt + 1;
            if (cnt == 2) {
                GirlBrainClearTarget((void *)self, &tgt);
            }
            if ((60 - systemStatus[0] * 10) / systemStatus[1] < cnt) {
                setMode(0);
            }
            break;
        }
        _ACTWait(1);
    }
}
