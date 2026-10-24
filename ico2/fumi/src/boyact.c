#include "typedef.h"
#include "boyact.h"
#include "debug.h"
#include "gamesys.h"
#include "sceneManager.h"
#include "gobj.h"
#include "obj_manager.h"
#include "girl_act.h"
#include "brain.h"
#include "gflag.h"
#include "layout_action.h"
#include "frameDependSequence.h"
#include "torch.h"
#include <string.h>
#include "geometryManager.h"
#include "chain.h"
#include "act-game.h"
#include "motionOrientManager.h"
#include "motionFileManager.h"
#include "matrixDrive.h"
#include "debug_exception.h"
#include "layout_texture.h"
#include "motionManager.h"
#include "main.h"
#include "enemy_act.h"
#include <libvu0.h>
#include "cage.h"
#include "isys.h"
#include "way_sys.h"
#include "fuzio.h"
#include "pad.h"
#include "weapon.h"
#include "StageAnimation.h"
#include "attackhit.h"
#include "mail-add-data.h"
#include "camera-editor.h"
#include "quaternion.h"
#include "script.h"
#include "commonact.h"
#include "act.h"
#include "gv.h"
#include <assert.h>
#include "poly-flat.h"
#include "fieldCollision.h"
#include "motionManager2.h"
#include "box.h"

typedef struct { /* field names derived */
    int a, b, c;
} S12; /* derived name */

/* One word of the boy's actor parameter block at gobj->x15C: the motion code
   writes these slots as float and the evaluator reads them as int, so the word
   itself is a union. */
typedef union BoyVal { /* field names derived */
    int i;
    float f;
} BoyVal; /* derived name */

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* the motion-def row of an actor's current motion */
#define CHAINROW(self) (GOBJ_SUB(self)->ctrl.motion + motionKind) /* derived name */

#ifdef VERSION_NTSC
static void findChainInJump(void *self)
{
    float p[4];
    float q[4];
    float w[4];
    float sk[4];
    float rt[4];
    float lp[4];
    float lv[4];
    float mtx[16];
    float hp0[4];
    float hp1[4];
    float cp[4];
    float ce[4];
    float pos[4];
    float hx[4];
    float cp2[4];
    float ce2[4];
    Act *sub;
    void *g;
    void *cage;
    float r;
    float r2;
    float ang;
    int rside = 0;
    int lside = 0;

    sub = GOBJ_ACT(self);
    r = ((CHAINROW(self)->flags.word >> 6) & 1) ? 300.0f : 100.0f;
    r2 = ((CHAINROW(self)->flags.word >> 6) & 1) ? 90.0f : 120.0f;

    for (g = isysGObjSearchFromObjKindID_begin(0x15); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (*(int *)((char *)g + 0x16C) != 0) {
            GetRootPosition(p, g);
            q[0] = p[0];
            q[1] = p[1];
            q[2] = p[2];
            q[1] += GetChainLength(g) + 50.0f;
            if (_DistxzSqGV(test_CURRENTROOT(self), p) < r * r &&
                p[1] < test_CURRENTROOT(self)[1] && test_CURRENTROOT(self)[1] < q[1]) {
                _OrientXZGV(rt, p, test_CURRENTROOT(self));
                ang = (float)_RotyGV(rt, test_CURRENTORIENT(self));
                if ((ang < 0.0f ? -ang : ang) < r2) {
                    if (sub->actMode == 4) {
                        if (0.0f < ang) {
                            rside = 1;
                        } else {
                            lside = 1;
                        }
                    }
                }
                GetSkeltonPosition(sk, self, 18);
                w[0] = 0.0f;
                w[1] = sk[1] - p[1];
                w[2] = 0.0f;
                break;
            }
        }
    }

    rt[0] = test_CURRENTROOT(self)[0];
    rt[1] = test_CURRENTROOT(self)[1];
    rt[2] = test_CURRENTROOT(self)[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(self));
    lp[0] = p[0];
    lp[1] = p[1];
    lp[2] = p[2];
    sceVu0SubVector(lv, (float *)lp, (float *)rt);
    lv[3] = 0.0f;
    sceVu0ApplyMatrix(lv, mtx, lv);

    if (((CHAINROW(self)->flags2.word >> 3) & 1) == 0 && (rside != 0 || lside != 0) &&
        (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
        RequestChangeHandMode(self, 0, 2, 1, g, 0, w);
        RequestChangeHandMode(self, 1, 2, 1, g, 0, w);
    } else {
        RequestChangeHandMode(self, 0, 2, 0, 0, 0, 0);
        RequestChangeHandMode(self, 1, 2, 0, 0, 0, 0);
    }

    if ((rside != 0 || lside != 0) &&
        motionKind[GOBJ_SUB(self)->ctrl.motion].flags2.bits.chainIkRate) {
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x45C))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x464))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x468))->f = 0.8f;
    }

    if (rside != 0 || lside != 0) {
        _ACTCharStatus_Set(self, 16, -1.0f, (int)g);
    }

    if (rside != 0) {
        GetSkeltonPosition(hp0, self, 22);
        if ((lv[0] < 0.0f ? -lv[0] : lv[0]) < 60.0f && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 100.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (lside != 0) {
        GetSkeltonPosition(hp1, self, 6);
        if ((lv[0] < 0.0f ? -lv[0] : lv[0]) < 60.0f && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 100.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (g != 0 && sub->actMode == 65) {
        GetSkeltonPosition(hp0, self, 6);
        GetChainNearestNodePosition(hp1, g, hp0);
        if ((hp0[1] - hp1[1] < 0.0f ? -(hp0[1] - hp1[1]) : (hp0[1] - hp1[1])) < 5.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (sub->actMode == 65) {
        void *o;

        cage = 0;
        pos[0] = test_CURRENTROOT(self)[0];
        pos[1] = test_CURRENTROOT(self)[1];
        pos[2] = test_CURRENTROOT(self)[2];
        for (o = isysGObjSearchFromObjKindID_begin(43); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)((char *)o + 0x16C) != 0) {
                if (GetCageChainPoint(cp, ce, o) != 0) {
                    if (_DistxzSqGV(test_CURRENTROOT(self), cp) < 4.9e+03f && ce[1] > pos[1]) {
                        cage = o;
                        break;
                    }
                }
            }
        }
        if (cage != 0) {
            GetRootPositionHandExtra(self, hx);
            GetCageChainPoint(cp2, ce2, cage);
            if (cp2[1] + 150.0f < hx[1]) {
                ACTSendMailCorrect(self, 161);
                ACTSendMailCorrect(self, 160);
            }
        }
    }
}
#else
static void findChainInJump(void *self)
{
    float p[4];
    float q[4];
    float w[4];
    float sk[4];
    float rt[4];
    float lp[4];
    float lv[4];
    float mtx[16];
    float hp0[4];
    float hp1[4];
    float cp[4];
    float ce[4];
    float pos[4];
    float hx[4];
    float cp2[4];
    float ce2[4];
    Act *sub;
    void *g;
    void *cage;
    float r;
    float r2;
    float ang;
    int rside = 0;
    int lside = 0;

    sub = GOBJ_ACT(self);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    r = ((CHAINROW(self)->flags2.word >> 9) & 1) ? 300.0f : 100.0f;
    r2 = ((CHAINROW(self)->flags2.word >> 9) & 1) ? 90.0f : 120.0f;
#else
#ifdef VERSION_AUG6
    r = ((CHAINROW(self)->flags.word >> 6) & 1) ? 300.0f : 100.0f;
    r2 = ((CHAINROW(self)->flags.word >> 6) & 1) ? 90.0f : 120.0f;
#else
#ifdef VERSION_JUN26
    r = CHAINROW(self)->flags.bits.chainHang ? 300.0f : 100.0f;
    r2 = CHAINROW(self)->flags.bits.chainHang ? 90.0f : 120.0f;
#else
    r = ((CHAINROW(self)->flags2.word >> 8) & 1) ? 300.0f : 100.0f;
    r2 = ((CHAINROW(self)->flags2.word >> 8) & 1) ? 90.0f : 120.0f;
#endif
#endif
#endif

    for (g = isysGObjSearchFromObjKindID_begin(0x15); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (*(int *)((char *)g + 0x16C) != 0) {
            GetRootPosition(p, g);
            q[0] = p[0];
            q[1] = p[1];
            q[2] = p[2];
            q[1] += GetChainLength(g) + 50.0f;
            if (_DistxzSqGV(test_CURRENTROOT(self), p) < r * r &&
                p[1] < test_CURRENTROOT(self)[1] && test_CURRENTROOT(self)[1] < q[1]) {
                _OrientXZGV(rt, p, test_CURRENTROOT(self));
                ang = (float)_RotyGV(rt, test_CURRENTORIENT(self));
                if ((ang < 0.0f ? -ang : ang) < r2) {
                    if (sub->actMode == 4) {
                        if (0.0f < ang) {
                            rside = 1;
                        } else {
                            lside = 1;
                        }
                    }
                }
                GetSkeltonPosition(sk, self, 18);
                w[0] = 0.0f;
                w[1] = sk[1] - p[1];
                w[2] = 0.0f;
                break;
            }
        }
    }

    rt[0] = test_CURRENTROOT(self)[0];
    rt[1] = test_CURRENTROOT(self)[1];
    rt[2] = test_CURRENTROOT(self)[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(self));
    lp[0] = p[0];
    lp[1] = p[1];
    lp[2] = p[2];
    sceVu0SubVector(lv, (float *)lp, (float *)rt);
    lv[3] = 0.0f;
    sceVu0ApplyMatrix(lv, mtx, lv);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    if (((CHAINROW(self)->flags2.word >> 7) & 1) == 0 && (rside != 0 || lside != 0) &&
        (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
#else
#ifdef VERSION_AUG6
    if (((CHAINROW(self)->flags2.word >> 3) & 1) == 0 && (rside != 0 || lside != 0) &&
        (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
#else
#ifdef VERSION_JUN26
    if ((rside != 0 || lside != 0) && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
#else
    if (((CHAINROW(self)->flags2.word >> 6) & 1) == 0 && (rside != 0 || lside != 0) &&
        (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
#endif
#endif
#endif
        RequestChangeHandMode(self, 0, 2, 1, g, 0, w);
        RequestChangeHandMode(self, 1, 2, 1, g, 0, w);
    } else {
        RequestChangeHandMode(self, 0, 2, 0, 0, 0, 0);
        RequestChangeHandMode(self, 1, 2, 0, 0, 0, 0);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    if ((rside != 0 || lside != 0) &&
        motionKind[GOBJ_SUB(self)->ctrl.motion].flags2.bits.chainIkRate) {
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x45C))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x464))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x468))->f = 0.8f;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    if ((rside != 0 || lside != 0) &&
        motionKind[GOBJ_SUB(self)->ctrl.motion].flags.bits.chainIkRate) {
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x44C))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x454))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x458))->f = 0.8f;
#else
    if ((rside != 0 || lside != 0) &&
        motionKind[GOBJ_SUB(self)->ctrl.motion].flags2.bits.chainIkRate) {
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x44C))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x454))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x458))->f = 0.8f;
#endif
#else
    if ((rside != 0 || lside != 0) && ((CHAINROW(self)->flags2.word >> 5) & 1) != 0) {
        float sp = (systemStatus[0] == 1) ? 0.5f : 0.8f;

        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x45C))->f = sp;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x464))->f = sp;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x468))->f = sp;
#endif
#endif
    }

    if (rside != 0 || lside != 0) {
#ifdef VERSION_AUG6
        _ACTCharStatus_Set(self, 16, -1.0f, (int)g);
#else
#ifdef VERSION_JUN26
        _ACTCharStatus_Set(self, 14, -1.0f, (int)g);
#else
        _ACTCharStatus_Set(self, 18, -1.0f, (int)g);
#endif
#endif
    }

    if (rside != 0) {
        GetSkeltonPosition(hp0, self, 22);
        if ((lv[0] < 0.0f ? -lv[0] : lv[0]) < 60.0f && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 100.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (lside != 0) {
        GetSkeltonPosition(hp1, self, 6);
        if ((lv[0] < 0.0f ? -lv[0] : lv[0]) < 60.0f && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 100.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (g != 0 && sub->actMode == 65) {
        GetSkeltonPosition(hp0, self, 6);
        GetChainNearestNodePosition(hp1, g, hp0);
        if ((hp0[1] - hp1[1] < 0.0f ? -(hp0[1] - hp1[1]) : (hp0[1] - hp1[1])) < 5.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (sub->actMode == 65) {
        void *o;

        cage = 0;
        pos[0] = test_CURRENTROOT(self)[0];
        pos[1] = test_CURRENTROOT(self)[1];
        pos[2] = test_CURRENTROOT(self)[2];
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        for (o = isysGObjSearchFromObjKindID_begin(42); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)((char *)o + 0x16C) != 0) {
                GetCageChainPoint(cp, ce, o);
                if (_DistxzSqGV(test_CURRENTROOT(self), cp) < 4.9e+03f && ce[1] > pos[1]) {
                    cage = o;
                    break;
#else
        for (o = isysGObjSearchFromObjKindID_begin(43); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)((char *)o + 0x16C) != 0) {
                GetCageChainPoint(cp, ce, o);
                if (_DistxzSqGV(test_CURRENTROOT(self), cp) < 4.9e+03f && ce[1] > pos[1]) {
                    cage = o;
                    break;
#endif
#else
        for (o = isysGObjSearchFromObjKindID_begin(0x2C); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)((char *)o + 0x16C) != 0) {
                if (GetCageChainPoint(cp, ce, o) != 0) {
                    if (_DistxzSqGV(test_CURRENTROOT(self), cp) < 4.9e+03f && ce[1] > pos[1]) {
                        cage = o;
                        break;
                    }
#endif
                }
            }
        }
        if (cage != 0) {
            GetRootPositionHandExtra(self, hx);
            GetCageChainPoint(cp2, ce2, cage);
            if (cp2[1] + 150.0f < hx[1]) {
#ifdef VERSION_AUG6
                ACTSendMailCorrect(self, 159);
                ACTSendMailCorrect(self, 158);
#else
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 156);
                ACTSendMailCorrect(self, 155);
#else
                ACTSendMailCorrect(self, 0xAE);
                ACTSendMailCorrect(self, 0xAD);
#endif
#endif
            }
        }
    }
}
#endif

/* dir: subBoyCollision passes the motion direction (sub + 0x120); this body
   never reads it */
#ifndef VERSION_JUN26
static int CorrectOrient_RopeCliff(float *out, void *gobj, float *dir)
{
    float pos[4];
    float rpos[4];
    float orient[4];
    float climb[4];
    Act *sub = GOBJ_ACT(gobj);
    void *p;
    int r;
    int a;
    int b;
    float dy;

    switch (sub->actMode) {
    case 3:
        r = 0x78;
        break;
    case 2:
        r = 0x5A;
        break;
    default:
        return 0;
    }
    GetRootProjectionPosOfGObj(pos, gobj);
    p = isysGObjSearchFromObjKindID_begin(21);
    while (p != 0) {
        if (*(int *)((char *)p + 0x16C) != 0) {
            GetRootPosition(rpos, p);
            if (_DistxzSqGV(pos, rpos) < (float)(r * r)) {
                dy = pos[1] - rpos[1];
                if ((dy < 0.0f ? -dy : dy) < 70.0f) {
                    _OrientXZGV(orient, rpos, pos);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
                    a = _AbsRotyGV(sub->dir, orient);
                    GetChainClimbOrient(climb, p);
                    b = _AbsRotyGV(sub->dir, climb);
#else
                    a = _AbsRotyGV((char *)sub + 0x120, orient);
                    GetChainClimbOrient(climb, p);
                    b = _AbsRotyGV((char *)sub + 0x120, climb);
#endif
                    if (a < 0x4B && b < 0x4B) {
                        out[0] = orient[0];
                        out[1] = orient[1];
                        out[2] = orient[2];
                        return 1;
                    }
                }
            }
        }
        p = isysGObjSearchFromObjKindID_next(p);
    }
    return 0;
}
#endif

/* The three climb headers (omori/include/b50climb.h, b100climb.h,
   b200climb.h) textually included here, as girl_act.c does with its own
   three: each defines the hand-off's after-routine and act-routine `inline`,
   which the compiler emits at the end of the file in boyact.h's order, and
   the mot-routine plainly, emitted in place.  Their strings come out here,
   in this order, at the head of the TU's .rodata. */
inline void afterBoyHand50(GObj *volatile self)
{
    debug_StdPrintfDummy("boy after func\n");
    if (girlGObj != 0) {
#ifdef VERSION_NTSC
        iosOmSendMail(girlGObj, 89, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
        iosOmSendMail(girlGObj, 88, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
        iosOmSendMail(girlGObj, 87, isysCurrentGObj);
#else
        iosOmSendMail(girlGObj, 0x60, isysCurrentGObj);
#endif
#endif
#endif
    }
}

inline void actBoyHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand50\n");
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    sub->actMode = 79;
#else
#ifdef VERSION_JUN26
    sub->actMode = 78;
#else
    sub->actMode = 0x52;
#endif
#endif
    sub->after = (void *)afterBoyHand50;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error flg get\n");
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 89);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 88);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 87);
#else
        ACTSendMailCorrect(self, 0x60);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

void motBoyHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motBoyHand50\n");
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 85, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 84, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 83, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x5C, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 86, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 85, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 84, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x5D, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(45);
    sub->after = 0;
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 67);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 66);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 65);
#else
        ACTSendMailCorrect(self, 0x47);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

/* the shared "face the girl" prologue the b100climb.h / b200climb.h climb
   motions open with */
static inline void faceGirlFlat(void) /* derived name */
{
    float dir[4];
    void *boy = boyGObj;

    sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
    dir[1] = 0.0f;
    sceVu0Normalize(dir, dir);
    SetMotionDirection(boy, dir);
}

inline void afterBoyHand100(GObj *volatile self)
{
    debug_StdPrintfDummy("boy after func\n");
    if (girlGObj != 0) {
#ifdef VERSION_NTSC
        iosOmSendMail(girlGObj, 94, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
        iosOmSendMail(girlGObj, 93, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
        iosOmSendMail(girlGObj, 92, isysCurrentGObj);
#else
        iosOmSendMail(girlGObj, 0x65, isysCurrentGObj);
#endif
#endif
#endif
    }
}

inline void actBoyHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand100\n");
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    sub->actMode = 80;
#else
#ifdef VERSION_JUN26
    sub->actMode = 79;
#else
    sub->actMode = 0x53;
#endif
#endif
    sub->after = (void *)afterBoyHand100;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 94);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 93);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 92);
#else
        ACTSendMailCorrect(self, 0x65);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

void motBoyHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int n;

    debug_StdPrintfDummy("enter motBoyHand100\n");
    faceGirlFlat();
    n = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (girlGObj != 0) {
#ifdef VERSION_NTSC
                iosOmSendMail(girlGObj, 90, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
                iosOmSendMail(girlGObj, 89, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
                iosOmSendMail(girlGObj, 88, isysCurrentGObj);
#else
                iosOmSendMail(girlGObj, 0x61, isysCurrentGObj);
#endif
#endif
#endif
            }
            if ((sub->readyFlags & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 94);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 93);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 92);
#else
    ACTSendMailCorrect(self, 0x65);
#endif
#endif
#endif
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_NTSC
    sub->motReq = SetMotionRequest((void *)self, 92, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 145, sub->env.motOriReq);
#else
#ifdef VERSION_AUG6
    sub->motReq = SetMotionRequest((void *)self, 91, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 143, sub->env.motOriReq);
#else
#ifdef VERSION_JUN26
    sub->motReq = SetMotionRequest((void *)self, 88, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 139, sub->env.motOriReq);
#else
    sub->motReq = SetMotionRequest((void *)self, 0x65, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 0xA4, sub->env.motOriReq);
#endif
#endif
#endif
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 91, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 90, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 89, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x62, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    sub->motReq = SetMotionRequest((void *)self, 92, sub->env.motOriReq);
#else
#ifdef VERSION_AUG6
    sub->motReq = SetMotionRequest((void *)self, 91, sub->env.motOriReq);
#else
#ifdef VERSION_JUN26
    sub->motReq = SetMotionRequest((void *)self, 88, sub->env.motOriReq);
#else
    sub->motReq = SetMotionRequest((void *)self, 0x65, sub->env.motOriReq);
#endif
#endif
#endif
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 93, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 92, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 91, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x64, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 67);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 66);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 65);
#else
        ACTSendMailCorrect(self, 0x47);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

inline void afterBoyHand200(GObj *volatile self)
{
    debug_StdPrintfDummy("boy after func\n");
    if (girlGObj != 0) {
#ifdef VERSION_NTSC
        iosOmSendMail(girlGObj, 99, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
        iosOmSendMail(girlGObj, 98, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
        iosOmSendMail(girlGObj, 97, isysCurrentGObj);
#else
        iosOmSendMail(girlGObj, 0x6A, isysCurrentGObj);
#endif
#endif
#endif
    }
}

inline void actBoyHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand200\n");
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    sub->actMode = 81;
#else
#ifdef VERSION_JUN26
    sub->actMode = 80;
#else
    sub->actMode = 0x54;
#endif
#endif
    sub->after = (void *)afterBoyHand200;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 99);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 98);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 97);
#else
        ACTSendMailCorrect(self, 0x6A);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

void motBoyHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int n;

    debug_StdPrintfDummy("enter motBoyHand200\n");
    faceGirlFlat();
    n = (60 - systemStatus[0] * 10) / systemStatus[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (girlGObj != 0) {
#ifdef VERSION_NTSC
                iosOmSendMail(girlGObj, 95, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
                iosOmSendMail(girlGObj, 94, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
                iosOmSendMail(girlGObj, 93, isysCurrentGObj);
#else
                iosOmSendMail(girlGObj, 0x66, isysCurrentGObj);
#endif
#endif
#endif
            }
            if ((sub->readyFlags & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 99);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 98);
#else
#ifdef VERSION_JUN26
    ACTSendMailCorrect(self, 97);
#else
    ACTSendMailCorrect(self, 0x6A);
#endif
#endif
#endif
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
#ifdef VERSION_NTSC
    sub->motReq = SetMotionRequest((void *)self, 93, sub->env.motOriReq);
#else
#ifdef VERSION_AUG6
    sub->motReq = SetMotionRequest((void *)self, 92, sub->env.motOriReq);
#else
#ifdef VERSION_JUN26
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
#else
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
#endif
#endif
#endif
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    sub->motReq = SetMotionRequest((void *)self, 93, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 145, sub->env.motOriReq);
#else
#ifdef VERSION_AUG6
    sub->motReq = SetMotionRequest((void *)self, 92, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 143, sub->env.motOriReq);
#else
#ifdef VERSION_JUN26
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 139, sub->env.motOriReq);
#else
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 0xA4, sub->env.motOriReq);
#endif
#endif
#endif
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 96, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 95, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 94, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x67, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
#ifdef VERSION_NTSC
    sub->motReq = SetMotionRequest((void *)self, 93, sub->env.motOriReq);
#else
#ifdef VERSION_AUG6
    sub->motReq = SetMotionRequest((void *)self, 92, sub->env.motOriReq);
#else
#ifdef VERSION_JUN26
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
#else
    sub->motReq = SetMotionRequest((void *)self, 0x66, sub->env.motOriReq);
#endif
#endif
#endif
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_NTSC
            iosOmSendMail(girlGObj, 98, isysCurrentGObj);
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 97, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 96, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 0x69, isysCurrentGObj);
#endif
#endif
#endif
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 67);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 66);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 65);
#else
        ACTSendMailCorrect(self, 0x47);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* Each of the two height tests is one source line applying ABSF twice to the
   same height difference, so each re-evaluates the pair of test_CURRENTROOT
   calls.  The second test's body is empty in retail. */
#define BOYGIRL_DY()                                                                               \
    (test_CURRENTROOT(boyGObj)[1] - test_CURRENTROOT(girlGObj)[1]) /* derived name */
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))                          /* derived name */

#ifdef VERSION_NTSC
void handoff_heroin(void) /* derived name */
{
    void *boy = boyGObj;

    if (girlGObj != 0) {
        if (GOBJ_SUB(girlGObj)->root.hand0.mode == 6) {
            if (actModeTbl[GOBJ_ACT(boy)->actMode].pullUp) {
            } else {
                iosOmSendMail(girlGObj, 59, isysCurrentGObj);
            }
            ACTSendMailCorrect(boy, 234);
        } else if (_DistxzGV(test_CURRENTROOT(boy), test_CURRENTROOT(girlGObj)) < 100.0f &&
                   ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {
            GetHeightOfFieldPlaneDifference(boyGObj, girlGObj);
        }
    }
    if (girlGObj != 0 && GOBJ_SUB(girlGObj)->root.hand0.mode != 6) {
        if (_DistxzGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 100.0f &&
            ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {}
    }
}

static sceVu0FVECTOR pinchBoyPos; /* derived name */

static sceVu0FVECTOR pinchCameraPos; /* derived name */

static sceVu0FVECTOR pinchBoyPosLate; /* derived name */
#else
void handoff_heroin(void)
{
    void *boy = boyGObj;

    if (girlGObj != 0) {
        if (GOBJ_SUB(girlGObj)->root.hand0.mode == 6) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 57, isysCurrentGObj);
            ACTSendMailCorrect(boy, 226);
#else
            iosOmSendMail(girlGObj, 58, isysCurrentGObj);
            ACTSendMailCorrect(boy, 231);
#endif
#else
            if (actModeTbl[GOBJ_ACT(boy)->actMode].bit7) {
            } else {
                iosOmSendMail(girlGObj, 0x3E, isysCurrentGObj);
            }
            ACTSendMailCorrect(boy, 0xFA);
#endif
        } else if (_DistxzGV(test_CURRENTROOT(boy), test_CURRENTROOT(girlGObj)) < 100.0f &&
                   ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {
            GetHeightOfFieldPlaneDifference(boyGObj, girlGObj);
        }
    }
    if (girlGObj != 0 && GOBJ_SUB(girlGObj)->root.hand0.mode != 6) {
        if (_DistxzGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 100.0f &&
            ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {}
    }
}

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifndef VERSION_JUN26
static sceVu0FVECTOR pinchBoyPos; /* derived name */

static sceVu0FVECTOR pinchCameraPos; /* derived name */

static sceVu0FVECTOR pinchBoyPosLate; /* derived name */
#endif
#else
static float pinchBoyPos[4]; /* derived name */

static float pinchCameraPos[4]; /* derived name */

static float pinchBoyPosLate[4]; /* derived name */
#endif
#endif

typedef struct { /* field names derived */
    int a;
    int b;
} CharPos; /* derived name */

/* the wall hit actBoyStart hands the boy and the girl with mail 0x36: the
   ClipWall work record's wall pair and the wall it hit */
static WallCfg sofaWallHit; /* derived name */

#ifdef VERSION_JUN26
/* the attribute wall hit, three words in a VU0 int vector: the object's .bss
   is 16-byte aligned in this build (it opens at 0x6F5160, 8 bytes past
   act-parallel-control's run) */
static sceVu0IVECTOR attrWallHit; /* derived name */
#else
static int attrWallHit[3]; /* derived name */
#endif

static long long boyInfo[12]; /* derived name */

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
static void CheckCollisionAttr(void *self)
{
    Sub15C *stage = GOBJ_SUB(self);
    int i;
    int flag = 1;
    int esc = 0;

#ifdef VERSION_JUN26
    if (_ACTGame_GetParamF(1) < stage->ctrl.groundHeight) {
#else
    if (_ACTGame_GetParamF(2) < stage->ctrl.groundHeight) {
#endif
        return;
    }
    if (GOBJ_ACT(self)->actMode == 22) {
        return;
    }
    if (gameover_flag != 0) {
        return;
    }
    for (i = 1; i < 16; i++) {
        if (CheckFloorAttribute(self, i)) {
            int *w = (int *)boyInfo;

            flag = 0;
            if (w[4] < 0) {
                w[4] = i;
                return;
            }
            if (w[4] != i) {
                if (ACTGame_FLAG_TETSUNAGI()) {
                    esc = 1;
                } else if (girlGObj != 0) {
                    if (IsGirlStatusEscortEnable(stage_no, i)) {
                        esc = 1;
                    }
                }
                if (esc) {
                    boyInfo[1] |= 0x800000000LL;
#ifdef VERSION_JUN26
                    RequestStageChange(i, boyGObj, girlGObj, 1.0f, 16.0f);
                } else {
                    RequestStageChange(i, boyGObj, 0, 1.0f, 16.0f);
#else
                    RequestStageChange(i, boyGObj, girlGObj, 1.0f, 8.0f);
                } else {
                    RequestStageChange(i, boyGObj, 0, 1.0f, 8.0f);
#endif
                }
            }
        }
    }
    if (flag) {
        ((int *)boyInfo)[4] = 0xFF;
    }
}

typedef struct { /* field names derived */
    int id;      /* 0x00 */
    float f04;
    float f08;
    unsigned char b0C; /* 0x0C */
    unsigned char b0D;
    unsigned char b0E;
    unsigned char b0F;
    float f10; /* 0x10 */
    char pad14[0x20 - 0x14];
    sceVu0FVECTOR f20; /* 0x20 */
    sceVu0FVECTOR f30; /* 0x30 */
} BgaEntry;            /* derived name */
#else
static void CheckCollisionAttr(void *self)
{
    Sub15C *stage = GOBJ_SUB(self);
    int i;
    int flag = 1;
    int esc = 0;

    if (_ACTGame_GetParamF(2) < stage->ctrl.groundHeight) {
        return;
    }
    if (GOBJ_ACT(self)->actMode == 0x16) {
        return;
    }
    if (gameover_flag != 0) {
        return;
    }
    if (scpBoyControlReadDisable != 0) {
        return;
    }
    for (i = 1; i < 16; i++) {
        if (CheckFloorAttribute(self, i)) {
            int *w = (int *)boyInfo;

            flag = 0;
            if (w[4] < 0) {
                w[4] = i;
                return;
            }
            if (w[4] != i) {
                if (ACTGame_FLAG_TETSUNAGI()) {
                    esc = 1;
                } else if (girlGObj != 0) {
                    if (IsGirlStatusEscortEnable(stage_no, i)) {
                        esc = 1;
                    }
                }
                if (esc) {
                    boyInfo[1] |= 0x800000000LL;
                    RequestStageChange(i, boyGObj, girlGObj, 1.0f, 8.0f);
                } else {
                    RequestStageChange(i, boyGObj, 0, 1.0f, 8.0f);
                }
                itemWatchOff = 1;
            }
        }
    }
    if (flag) {
        ((int *)boyInfo)[4] = 0xFF;
    }
}

typedef struct { /* field names derived */
    int id;      /* 0x00 */
    float f04;
    float f08;
    unsigned char b0C; /* 0x0C */
    unsigned char b0D;
    unsigned char b0E;
    unsigned char b0F;
    float f10; /* 0x10 */
    char pad14[0x20 - 0x14];
    float f20[4]; /* 0x20 */
    float f30[4]; /* 0x30 */
} BgaEntry;       /* derived name */
#endif

typedef struct { /* field names derived */
    long long w[12];
} BoyWork; /* derived name */

#ifdef VERSION_NTSC
typedef struct { /* field names derived */
    int w[6];
} BoyKidnapWork; /* derived name */

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0}}; /* derived name */

static BgaEntry boyBgaTable[] = {
    /* derived name */
    {416, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {417, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {421, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {422, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
typedef struct { /* field names derived */
    int w[6];
} BoyKidnapWork; /* derived name */

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0}}; /* derived name */

#ifdef VERSION_JUN26
static BgaEntry boyBgaTable[] = {
    /* derived name */
    {380, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {381, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {385, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {386, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */
#else
static BgaEntry boyBgaTable[] = {
    /* derived name */
    {415, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {416, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {420, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {421, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */
#endif
#else
typedef struct { /* field names derived */
    int w[8];
} BoyKidnapWork; /* derived name */

/* the private insert-camera record, 16-aligned as the programmer's other
   vector records (act-game.c Vec4S, way_sys.c WayClipWork) */
typedef struct {           /* field names derived */
    float pos[4];          /* 0x00, where the camera starts */
    float tgt[4];          /* 0x10, where it moves to */
    struct GObj *track;    /* 0x20, the object the return leg follows, or 0 for pos */
    int inFrames;          /* 0x24, frames of the move to tgt */
    int outFrames;         /* 0x28, frames of the return */
    float inRate;          /* 0x2C, the move's interpolation step */
    float blend;           /* 0x30, InsertCamera_SetDetail's blend */
    unsigned char control; /* 0x34, PrivInsCamChk_Control's answer */
    unsigned char pad35[3];
    int cnt;                               /* 0x38 */
    int on;                                /* 0x3C */
    float cur[4];                          /* 0x40 */
} __attribute__((aligned(16))) PrivInsCam; /* derived name */

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0, 0, 0, 0, 0, -1, -1}}; /* derived name */

static BgaEntry boyBgaTable[] = {
/* derived name */
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    {476, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {477, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {481, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {482, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */

#else
    {480, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {481, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {485, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {486, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */
#endif

/* PrivInsCam's initial value: subBoyCollision copies it whole into
   privInsCam. */
static PrivInsCam privInsCamDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, 0, 0, 0, 0.5f, 0.2f}; /* derived name */
#endif

#endif

/* boyact.o's two .data globals, the last two quadwords of its .data:
   test_rope_velo, which no code names, and add_rope_vec, the boy's orient
   snapshot SaveBoyOrientForScript writes. */
float test_rope_velo[4] = {0.0f, 0.0f, 0.0f, 0.0f};

float add_rope_vec[4] = {0.0f, 0.0f, 0.0f, 0.0f};

static void BoyBgaManager(void *self, int id, void *dst)
{
    /* UpdateGeo is a GNU nested function: it reads `self` out of
       BoyBgaManager's frame through the static chain. */
    void UpdateGeo(BgaEntry * p)
    {
        float dir[4];
        float tmp[4];
        void *obj;

        if (p->b0F != 0) {
            dir[0] = test_CURRENTORIENT(self)[0];
            dir[1] = test_CURRENTORIENT(self)[1];
            dir[2] = test_CURRENTORIENT(self)[2];
        } else {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
            obj = isysGObjSearchFromObjKindID_begin(46);
#else
#ifdef VERSION_JUN26
            obj = isysGObjSearchFromObjKindID_begin(45);
#else
            obj = isysGObjSearchFromObjKindID_begin(47);
#endif
#endif
            _OrientXZGV(dir, test_CURRENTROOT(obj), test_CURRENTROOT(self));
        }
        sceVu0ScaleVector(dir, dir, p->f10);
        ActGame_GetOrientQ(p->f30, dir, 0);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f08);
        sceVu0AddVector(p->f20, test_CURRENTROOT(self), tmp);
        sceVu0ScaleVector(tmp, test_CURRENTORIENT(self), p->f04);
        _ApplyRyGV(tmp, 1.5707964f);
        sceVu0AddVector(p->f20, p->f20, tmp);
        p->f20[1] += (float)p->b0D;
    }
    BgaEntry *p;
    int i;
    int v;
    int r;

    for (i = 0; 0 <= boyBgaTable[i].id; i++) {
        if (boyBgaTable[i].id == id) {
            p = &boyBgaTable[i];
            goto found;
        }
    }
    debug_assert(__FILE__, LN(1731, 1724, 1724, 1543, 1493, 1292));
    __assert(__FILE__, LN(1731, 1724, 1724, 1543, 1493, 1292), "0");
    p = 0;
found:
    v = *(int *)dst;
    if (v < 0) {
        return;
    }
    if (p->b0C != 0) {
        UpdateGeo(p);
        goto reload;
    }
    if (v == 0) {
        UpdateGeo(p);
    reload:
        v = *(int *)dst;
    }
    r = (int)stage_PlayBgAnimation(p->id, (float)v, p->f20, p->f30);
    if (p->b0E == 0) {
        *(int *)dst = r;
    } else if (0 <= r) {
        *(int *)dst = r;
    }
}

static unsigned char girlLookStarted; /* derived name */

static unsigned char girlLookInScreen; /* derived name */

static unsigned char weaponLookStarted; /* derived name */

static unsigned char weaponLookInScreen; /* derived name */

static unsigned char girlEscortedInStage; /* derived name */

static unsigned char ableBoyControl; /* derived name */

static unsigned char startWithGirl; /* derived name */

static unsigned char startWaitCancel; /* derived name */

static unsigned char startOnSofa; /* derived name */

static unsigned char sitLayoutDone; /* derived name */

static int sitCount; /* derived name */

static void *beliftGirl; /* derived name */

#ifdef VERSION_NTSC
static void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (startWithGirl != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
        SetDirectRootPositionNoFitting(self, buf);
    }
    if (gflagChk(348)) {
        gflagOff(348);
        return;
    }
    if (GetStageStartInfo(self, 0, 0, &w1, &w2, &w3) == 0) {
        return;
    }
    if (startOnSofa != 0) {
        return;
    }
    if (startWaitCancel != 0) {
        return;
    }
    _ACTWait(3);
    GetStageStartInfo(self, 0, 0, &w1, &w2, &w3);
    _ACTWait(w1);
    scpPlayStart(self);
    scpPlayMotReq(self, 7);
    _ACTWait(w2);
    scpPlayEnd(self);
    _ACTWait(w3);
}
#else
static void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (startWithGirl != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
#ifdef VERSION_JUN26
        SetDirectRootPosition(self, buf);
    }
    if (gflagChk(332)) {
        gflagOff(332);
#else
        SetDirectRootPositionNoFitting(self, buf);
    }
#ifdef VERSION_AUG6
    if (gflagChk(347)) {
        gflagOff(347);
#else
    if (gflagChk(381)) {
        gflagOff(381);
#endif
#endif
        return;
    }
    if (GetStageStartInfo(self, 0, 0, &w1, &w2, &w3) == 0) {
        return;
    }
    if (startOnSofa != 0) {
        return;
    }
    if (startWaitCancel != 0) {
        return;
    }
    _ACTWait(3);
    GetStageStartInfo(self, 0, 0, &w1, &w2, &w3);
    _ACTWait(w1);
    scpPlayStart(self);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    scpPlayMotReq(self, 7);
#else
    scpPlayMotReq(self, 8);
#endif
    _ACTWait(w2);
    scpPlayEnd(self);
    _ACTWait(w3);
}
#endif

extern int fptodp(float v);

static int GetChainSlope(void)
{
    float a;
    float b;
    float c;
    float ratio;
    GObj *g = boyGObj;
    int up;
    int down;

    GetChainPendulum((void *)GOBJ_ACT(g)->chain, &a, &b, &c);
    if (b < 5.0f) {
        return 0;
    }
    ratio = (float)*motionTable[GOBJ_SUB(g)->ctrl.motion] / (c * 0.5f);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_NTSC) || defined(VERSION_AUG6)
    ACTGame_SetMotionPlaySpeedRatio_Reserve(g, ratio, 7);
#else
#ifdef VERSION_JUN26
    ACTGame_SetMotionPlaySpeedRatio_Reserve(g, ratio, 7);
#else
    ACTGame_SetMotionPlaySpeedRatio_Reserve(
        g, ratio * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 30.0f, 7);
#endif
#endif
    if (debug_font_flag & 1) {
        debug_Printf(10, 140, 0x0FFFFFFF, "speed = %f (%f)\n", fptodp(ratio), fptodp(c));
    }
    if (debug_font_flag & 1) {
        debug_Printf(10, 150, 0x0FFFFFFF, "%f / %f\n", fptodp(GOBJ_SUB(g)->ctrl.animFrame),
                     fptodp((float)*motionTable[GOBJ_SUB(g)->ctrl.motion]));
    }
    if ((b < 0.0f ? -b : b) < 30.0f) {
        up = 1;
        down = 2;
    } else {
        up = 3;
        down = 4;
    }
    if (a < 0.0f) {
        return up;
    }
    return down;
}

#ifdef VERSION_JUN26
int test_rope_slope = 0;

float add_rope_val = 0.0f;
#else
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int InsertCameraWorkingFlag;

#ifndef VERSION_AUG6
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int FixViewInGameCameraFlag;
#endif
#endif

/* An inline-only static that snapshots the boy's orient where the script
   side reads it, inlined into subBoyControl and subBoyCollision. */
static inline void SaveBoyOrientForScript(void) /* derived name */
{
    void *boy = boyGObj;

    add_rope_vec[0] = test_CURRENTORIENT(boy)[0];
    add_rope_vec[1] = test_CURRENTORIENT(boy)[1];
    add_rope_vec[2] = test_CURRENTORIENT(boy)[2];
}

/* the stick's angle from a direction, which CorrectStickInfo and
   subBoyControl inline */
static inline int correctStick(void *dir, IosPadStick *stick) /* derived name */
{
    float buf[4];

    ConvertStickToAbsCoord(buf, stick);
    return _RotyGV(buf, dir);
#if !defined(VERSION_NTSC) && !defined(VERSION_JUN26)
}

/* the private-camera gate */
static __inline__ unsigned char boyPrivInsCamInScreen(void) /* derived name */
{
    float scr[4];

    if (PrivInsCamChk_Control() == 0) {
        return 0;
    }
    if (0.0f < IsPointIsInScreen(scr, test_CURRENTROOT(boyGObj))) {
        return 1;
    }
    return 0;
#endif
}

/* the stick snap the boy's walk control applies when the camera-relative
   wish and the stick agree closely enough */
static __inline__ int snapStickToCamera(float *stick, float *wish, float *sabs,
                                        float *cam) /* derived name */
{
    int rc;
    int rs;
    int d;

    rc = _RotyGV(cam, wish);
    rs = _RotyGV(stick, sabs);
    if (sabs[0] == 0.0f && sabs[1] == 0.0f && sabs[2] == 0.0f) {
        return 0;
    }
    if (!((rc < 0 ? -rc : rc) < 20)) {
        return 0;
    }
    if ((rs < 0 ? -rs : rs) < 46) {
        return 0;
    }
    d = ((rs < 0 ? -rs : rs) > 90) ? 2 : 4;
    if (rs < 0) {
        d = -d;
    }
    if ((rs < 0 ? -rs : rs) < (d < 0 ? -d : d)) {
        d = rs;
    }
    stick[0] = sabs[0];
    stick[1] = sabs[1];
    stick[2] = sabs[2];
    _ApplyRyGV(stick, (float)d * 3.1415927f / 180.0f);
    return d;
}

#ifndef VERSION_JUN26
int test_rope_slope = 0;

float add_rope_val = 0.0f;
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
void subBoyControl(GObj *volatile self)
{
    float stick[4];
    float wish[4];
    float sabs[4];
    float dir[4];
    int c0;
    int c1;
    int c2;
    Act *s = GOBJ_ACT(self);
    void *g;
#ifndef VERSION_JUN26
    int n;
    int sw;
#endif
    int slow;
    float d;
    float dist;
    int dbg = 0; /* local debug switch, see the test after the stick loop */

    memset(stick, 0, 16);
    c0 = 0;
    c1 = 0;
    c2 = 0;
    memset(wish, 0, 16);
#ifndef VERSION_JUN26
    n = 0;
#endif
    iosPadConnect(&s->pad, 0, 0, &iosPadConfCustom);
    boyPad = &s->pad;
    E3_StageStartBoy((void *)self);
    layoutActPushStartNew = 0;
    while (1) {
#ifdef VERSION_JUN26
        for (;;) {
            if (((int)(s->flags18.ll >> 42) & 1) == 0) {
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        if (InsertCameraWorkingFlag) {
#else
        if (FixViewInGameCameraFlag) {
            n = 3;
        }
        if (InsertCameraWorkingFlag) {
            n = 3;
        }
        if ((int)(s->flags20.ll >> 18) & 1) {
#endif
            n = 3;
        }
        sw = 0;
        if (n) {
            n--;
            sw = 1;
        }
        for (;;) {
            if (((int)(s->flags18.ll >> 43) & 1) == 0) {
#endif
                goto noStick;
            }
            if (scpBoyControlReadDisable == 0 && GOBJ_WORK(self)->pinchFrames == 0) {
                iosPadRead(&s->pad);
                if (s->pad.dev->error == 1) {
                    layoutActPushStartNew = 1;
                } else {
                    layoutActPushStartNew = 0;
                }
                /* the option word's low byte */
                iosPadGetStick(&s->pad, &s->stick, 0, 2, 2, (unsigned char)debug_stick_simulate);
                if (debug_stick_input) {
                    if (debug_font_flag & 1) {
                        debug_Printf(10, 170, 0x0FFFFFFF, "L = %f\n", fptodp(s->stick.mag));
                    }
                }
                ableBoyControl = 1;
            } else {
                s->pad.rel = 0;
                s->stick.x = s->stick.y = 127;
                s->pad.trg = 0;
                s->pad.now = 0;
                s->stick.mag = 0.0f;
                ableBoyControl = 0;
            }
            _GetMotionDirection(dir, (void *)self);
            correctStick(dir, &s->stick);
            if (s->pad.trg & 1) {
                BridgeBox();
            }
            g = isysGObjSearchFromObjLayoutID(2);
            if (s->wayMode == 1) {
                float tgt[4];
                float pos[4];

                GetRootPosition(tgt, g);
                GetRootPosition(pos, (void *)self);
                if (GetWay_begin(tgt, &s->way, pos) == 0) {
                    s->wayMode = 0;
                } else {
                    s->wayMode = 2;
                }
                break;
            }
            if (s->wayMode == 2) {
                switch (s->way.reached) {
                case 0: {
                    float root[4];

                    GetRootPosition(root, (void *)self);
                    GetWay_next(&s->way, root);
                    sceVu0CopyVector(stick, s->way.nrm);
                    s->stick.mag = 1.0f;
                    break;
                }
                case 1: {
                    float p0[4];
                    float p1[4];
                    ClipWork work;

                    GetRootPosition(p0, (void *)self);
                    GetRootPosition(p1, g);
                    work.radius = 10.0f;
                    sceVu0CopyVector(work.pt[0], p0);
                    sceVu0CopyVector(work.pt[1], p1);
                    ClipWall(&work);
                    if (work.wall.elem != 0) {
                        s->wayMode = 1;
                    }
                    dist = fzMagnitude2fv(p1, p0);
                    p1[0] = p1[0] - p0[0];
                    p1[1] = 0.0f;
                    p1[2] = p1[2] - p0[2];
                    sceVu0Normalize(stick, p1);
                    if (dist < 120.0f) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        ACTSendMailCorrect(self, 177);
#else
                        ACTSendMailCorrect(self, 180);
#endif
#else
                        ACTSendMailCorrect(self, 183);
#endif
                        s->wayMode = 0;
                    } else if (dist < 850.0f) {
                        s->stick.mag = (dist - 100.0f) / 750.0f;
                    } else {
                        s->stick.mag = 1.0f;
                    }
                    break;
                }
                }
                break;
            }
            if (0.1f < s->stick.mag) {
                float cam[4];

                sabs[0] = stick[0];
                sabs[1] = stick[1];
                sabs[2] = stick[2];
                ConvertStickToAbsCoord(stick, &s->stick);
                cam[0] = (float)(s->stick.x - 128);
                cam[1] = 0.0f;
                cam[2] = (float)(s->stick.y - 128);
#ifdef VERSION_JUN26
                snapStickToCamera(stick, wish, sabs, cam);
#else
                if (sw == 0) {
                    snapStickToCamera(stick, wish, sabs, cam);
                }
#endif
                wish[0] = cam[0];
                wish[1] = cam[1];
                wish[2] = cam[2];
                {
                    float ori[4];

                    GetRootMotionOrient(ori, (void *)self);
                    s->stick.angle = _RotyGV(stick, ori);
                }
            } else {
                s->stick.angle = 0;
                s->stick.mag = 0.0f;
            }
            if ((void *)self == CurrentTargetGObj) {
                break;
            }
            _ACTWait(1);
        }
        /* a local debug switch, off: the cursor_control idiom of way_tool.c,
           moving the current target object; the August TRFILE (2052-2056)
           and the PAL listing (2323-2327) have five code-less lines after
           the loop's brace, this block's length; the text is derived */
        if (dbg) {
            if ((void *)self == CurrentTargetGObj && (s->pad.trg & 1)) {
                ACTDebugMove(self, 1);
            }
        }
        s->dir[0] = stick[0];
        s->dir[1] = stick[1];
        s->dir[2] = stick[2];
    noStick:
#ifndef VERSION_JUN26
        GOBJ_WORK(self)->stickMag = s->stick.mag;
#endif
        {
            static int slowWalkTimer = 0; /* derived name */

            slow = 0;
            if (s->actMode == 1) {
#ifdef VERSION_JUN26
                if (GOBJ_SUB(self)->ctrl.motion == 0 || GOBJ_SUB(self)->ctrl.motion == 1 ||
                    GOBJ_SUB(self)->ctrl.motion == 2) {
#else
                if (GOBJ_SUB(self)->ctrl.motion == 0 || GOBJ_SUB(self)->ctrl.motion == 1) {
#endif
                    if (0.5f < s->stick.mag) {
                        slowWalkTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 5;
                    }
                }
            }
            if (0 < slowWalkTimer) {
                slowWalkTimer--;
                slow = 1;
            }
        }
        if (slow && 0.5f < s->stick.mag) {
            s->stick.mag = 0.5f;
        }
        c0++;
        if (0.1f < s->stick.mag) {
            c0 = 0;
        }
        if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) {
            c1++;
        } else {
            c1 = 0;
        }
        if (0.1f < s->stick.mag &&
            !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)))) {
            c2++;
        } else {
            c2 = 0;
        }
        _ACTCommonMailTest(self, c0, c1, c2);
        switch (s->actMode) {
        case 1:
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 177);
            break;
        case 2:
            ACTSendMailCorrect(self, 163);
            break;
        case 3:
            ACTSendMailCorrect(self, 168);
#else
            ACTSendMailCorrect(self, 180);
            break;
        case 2:
            ACTSendMailCorrect(self, 166);
            break;
        case 3:
            ACTSendMailCorrect(self, 171);
#endif
#else
            ACTSendMailCorrect(self, 183);
            break;
        case 2:
            ACTSendMailCorrect(self, 168);
            break;
        case 3:
            ACTSendMailCorrect(self, 173);
#endif
            break;
        case 29:
            if (s->pad.trg & 0x40) {
                if (100.0f < GetDifferenceFromLowerField(self, 44)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 267);
                } else {
                    ACTSendMailCorrect(self, 202);
#else
                    ACTSendMailCorrect(self, 275);
                } else {
                    ACTSendMailCorrect(self, 207);
#endif
#else
                    ACTSendMailCorrect(self, 278);
                } else {
                    ACTSendMailCorrect(self, 210);
#endif
                }
            }
            if ((0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) ||
                (s->pad.trg & 0x10)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 177);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 180);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 183);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 26:
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                GOBJ_WORK(self)->fallDir[0] = s->dir[0];
                GOBJ_WORK(self)->fallDir[1] = s->dir[1];
                GOBJ_WORK(self)->fallDir[2] = s->dir[2];
                ACTSendMailCorrect(self, 282);
#else
                sceVu0ScaleVector(GOBJ_WORK(self)->fallDir, (char *)GOBJ_ACT(self)->work + 0x7E0,
                                  -1.0f);
                ACTSendMailCorrect(self, 291);
#endif
#else
                sceVu0ScaleVector(GOBJ_WORK(self)->fallDir, (char *)GOBJ_ACT(self)->work + 0x800,
                                  -1.0f);
                ACTSendMailCorrect(self, 294);
#endif
            }
            break;
        case 27: {
            int back = 0;

            if (0.1f < s->stick.mag) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                int r = _RotyGV(stick, GOBJ_WORK(self)->hangOrient);
#else
                int r = _RotyGV(stick, (float *)((char *)GOBJ_ACT(self)->work + 0x430));
#endif

                r = r < 0 ? -r : r;
                back = r >= 136;
                if (back && GetMotionFrameFlag1((void *)self)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 276);
#else
                    ACTSendMailCorrect(self, 285);
#endif
#else
                    ACTSendMailCorrect(self, 288);
#endif
                }
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 275);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 202);
            }
            if (back || (s->pad.trg & 0x10)) {
                ACTSendMailCorrect(self, 177);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 267);
#else
                ACTSendMailCorrect(self, 284);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 207);
            }
            if (back || (s->pad.trg & 0x10)) {
                ACTSendMailCorrect(self, 180);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 275);
#endif
#else
                ACTSendMailCorrect(self, 287);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 210);
            }
            if (back || (s->pad.trg & 0x10)) {
                ACTSendMailCorrect(self, 183);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 278);
#endif
            break;
        }
        case 28:
            if (s->pad.trg & 0x40) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 207);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 210);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 30:
            if (s->pad.trg & 0x40) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
            } else if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 177);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 207);
            } else if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 180);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 210);
            } else if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 183);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 31:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 33:
            if (s->pad.trg & 0x40) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
#else
                ACTSendMailCorrect(self, 207);
#endif
#else
                ACTSendMailCorrect(self, 210);
#endif
            }
            break;
        case 40:
            if ((s->pad.trg & 0x10) || s->stick.y - 128 < -100) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 274);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 202);
#else
                ACTSendMailCorrect(self, 283);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 207);
#endif
#else
                ACTSendMailCorrect(self, 286);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 210);
#endif
            }
            break;
        case 34:
            if (s->pad.trg & 0x40) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
            } else if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 273);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 207);
            } else if ((s->pad.trg & 0x10) ||
                       (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91)) {
                ACTSendMailCorrect(self, 282);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 210);
            } else if ((s->pad.trg & 0x10) ||
                       (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91)) {
                ACTSendMailCorrect(self, 285);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 35:
            if (s->pad.trg & 0x40) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
            }
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 171);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
#else
                ACTSendMailCorrect(self, 207);
            }
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 174);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 308);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 309);
#endif
#else
                ACTSendMailCorrect(self, 210);
            }
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 176);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 312);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 313);
#endif
            }
            break;
        case 52: {
            int near = 1;
            int front = 1;
            float gpos[4];
            float tpos[4];
            float ori[4];
            float vec[4];
            void *obj = s->env.pullParent;

            if (obj != 0 && girlGObj != 0) {
                gpos[0] = test_CURRENTROOT(girlGObj)[0];
                gpos[1] = test_CURRENTROOT(girlGObj)[1];
                gpos[2] = test_CURRENTROOT(girlGObj)[2];
                GetRootPosition(tpos, obj);
                ori[0] = test_CURRENTORIENT((void *)self)[0];
                ori[1] = test_CURRENTORIENT((void *)self)[1];
                ori[2] = test_CURRENTORIENT((void *)self)[2];
                _OrientXZGV(vec, gpos, tpos);
                if (_DistSqGV(tpos, gpos) < 250000.0f &&
                    CheckFloorAttribute(girlGObj, 0xA000000) != 0) {
                    if (0.0f < sceVu0InnerProduct(ori, vec)) {
                        near = 0;
                    } else {
                        front = 0;
                    }
                }
            }
            if (s->pad.now & 0x20) {
                if (near && 0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 119);
#else
                    ACTSendMailCorrect(self, 120);
#endif
#else
                    ACTSendMailCorrect(self, 121);
#endif
                    break;
                }
                if (front && 0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 118);
                    break;
                }
                ACTSendMailCorrect(self, 301);
                break;
            }
            ACTSendMailCorrect(self, 301);
            ACTSendMailCorrect(self, 177);
#else
                    ACTSendMailCorrect(self, 119);
                    break;
                }
                ACTSendMailCorrect(self, 310);
                break;
            }
            ACTSendMailCorrect(self, 310);
            ACTSendMailCorrect(self, 180);
#endif
#else
                    ACTSendMailCorrect(self, 120);
                    break;
                }
                ACTSendMailCorrect(self, 314);
                break;
            }
            ACTSendMailCorrect(self, 314);
            ACTSendMailCorrect(self, 183);
#endif
            break;
        }
        case 53:
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 90 / 60 > s->modeFrame) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 124);
                break;
            }
            ACTSendMailCorrect(self, 301);
            ACTSendMailCorrect(self, 177);
#else
                ACTSendMailCorrect(self, 125);
                break;
            }
            ACTSendMailCorrect(self, 310);
            ACTSendMailCorrect(self, 180);
#endif
#else
                ACTSendMailCorrect(self, 126);
                break;
            }
            ACTSendMailCorrect(self, 314);
            ACTSendMailCorrect(self, 183);
#endif
            break;
        case 54:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 124);
                    if (s->pad.now & 8) {
                        ACTSendMailCorrect(self, 60);
                    }
                } else {
                    ACTSendMailCorrect(self, 301);
                }
            } else {
                ACTSendMailCorrect(self, 177);
#else
                    ACTSendMailCorrect(self, 125);
                    if (s->pad.now & 8) {
                        ACTSendMailCorrect(self, 61);
                    }
                } else {
                    ACTSendMailCorrect(self, 310);
                }
            } else {
                ACTSendMailCorrect(self, 180);
#endif
#else
                    ACTSendMailCorrect(self, 126);
                    if (s->pad.now & 8) {
                        ACTSendMailCorrect(self, 62);
                    }
                } else {
                    ACTSendMailCorrect(self, 314);
                }
            } else {
                ACTSendMailCorrect(self, 183);
#endif
            }
            break;
        case 32:
        case 38: {
            /* the actor, read at the head of this arm; the DEBUG build's report
               reads it */
            GObj *obj = self;

            if (((int)(*(unsigned long long *)((char *)GOBJ_ACT(self)->enemy + 0x298) >> 1) & 1) &&
                !(s->stick.y - 128 < 101)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 296);
            } else if ((*(int *)((char *)GOBJ_ACT(self)->enemy + 0x298) & 1) &&
                       s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 295);
            } else {
                ACTSendMailCorrect(self, 301);
            }
            if (s->pad.trg & 8) {
                ACTSendMailCorrect(self, 60);
#else
                ACTSendMailCorrect(self, 305);
            } else if ((*(int *)((char *)GOBJ_ACT(self)->enemy + 0x298) & 1) &&
                       s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 304);
            } else {
                ACTSendMailCorrect(self, 310);
            }
            if (s->pad.trg & 8) {
                ACTSendMailCorrect(self, 61);
#endif
#else
                ACTSendMailCorrect(self, 309);
            } else if ((*(int *)((char *)GOBJ_ACT(self)->enemy + 0x298) & 1) &&
                       s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 308);
            } else {
                ACTSendMailCorrect(self, 314);
            }
            if (s->pad.trg & 8) {
                ACTSendMailCorrect(self, 62);
#endif
            }
#ifdef DEBUG
            scePrintf("boy %08x stick %d\n", obj, s->stick.y - 128);
#endif
            break;
        }
        case 43:
            if (0.95f < s->stick.mag) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 198);
                break;
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 203);
                break;
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 206);
                break;
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 44:
            if (0.95f < s->stick.mag) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 197);
                break;
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 202);
                break;
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 205);
                break;
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 49:
            if (s->pad.now & 0x20) {
                switch (s->pushDir) {
                case 1:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        ACTSendMailCorrect(self, 297);
                    } else {
                        ACTSendMailCorrect(self, 301);
#else
                        ACTSendMailCorrect(self, 306);
                    } else {
                        ACTSendMailCorrect(self, 310);
#endif
#else
                        ACTSendMailCorrect(self, 310);
                    } else {
                        ACTSendMailCorrect(self, 314);
#endif
                    }
                    break;
                case -1:
                    if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        ACTSendMailCorrect(self, 298);
                    } else {
                        ACTSendMailCorrect(self, 301);
#else
                        ACTSendMailCorrect(self, 307);
                    } else {
                        ACTSendMailCorrect(self, 310);
#endif
#else
                        ACTSendMailCorrect(self, 311);
                    } else {
                        ACTSendMailCorrect(self, 314);
#endif
                    }
                    break;
                default:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                        ACTSendMailCorrect(self, 297);
                    } else if (0.1f < s->stick.mag &&
                               !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 298);
                    } else {
                        ACTSendMailCorrect(self, 301);
#else
                        ACTSendMailCorrect(self, 306);
                    } else if (0.1f < s->stick.mag &&
                               !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 307);
                    } else {
                        ACTSendMailCorrect(self, 310);
#endif
#else
                        ACTSendMailCorrect(self, 310);
                    } else if (0.1f < s->stick.mag &&
                               !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 311);
                    } else {
                        ACTSendMailCorrect(self, 314);
#endif
                    }
                    break;
                }
            } else {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 301);
                ACTSendMailCorrect(self, 177);
#else
                ACTSendMailCorrect(self, 310);
                ACTSendMailCorrect(self, 180);
#endif
#else
                ACTSendMailCorrect(self, 314);
                ACTSendMailCorrect(self, 183);
#endif
            }
            break;
        case 51:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
#ifdef VERSION_JUN26
                    ACTSendMailCorrect(self, 297);
                } else if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 298);
                } else {
                    ACTSendMailCorrect(self, 301);
                }
            } else {
                ACTSendMailCorrect(self, 177);
            }
            break;
        case 113:
            if (s->pad.trg & 0x20) {
                ACTSendMailCorrect(self, 178);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                    ACTSendMailCorrect(self, 306);
                } else if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 307);
                } else {
                    ACTSendMailCorrect(self, 310);
                }
            } else {
                ACTSendMailCorrect(self, 180);
#else
                    ACTSendMailCorrect(self, 310);
                } else if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 311);
                } else {
                    ACTSendMailCorrect(self, 314);
                }
            } else {
                ACTSendMailCorrect(self, 183);
#endif
            }
            break;
        case 114:
            if (s->pad.trg & 0x20) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 181);
#else
                ACTSendMailCorrect(self, 184);
#endif
#endif
                break;
            }
            if (0.1f < s->stick.mag &&
                !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)))) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 168);
#else
                ACTSendMailCorrect(self, 171);
#endif
#else
                ACTSendMailCorrect(self, 173);
#endif
                break;
            }
            if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 163);
                break;
            }
            ACTSendMailCorrect(self, 301);
#else
                ACTSendMailCorrect(self, 166);
                break;
            }
            ACTSendMailCorrect(self, 310);
#endif
#else
                ACTSendMailCorrect(self, 168);
                break;
            }
            ACTSendMailCorrect(self, 314);
#endif
            break;
        case 58:
            switch (GetChainSlope()) {
            case 0:
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 148);
                break;
            case 1:
                ACTSendMailCorrect(self, 134);
                break;
            case 2:
                ACTSendMailCorrect(self, 135);
                break;
            case 3:
                ACTSendMailCorrect(self, 136);
                break;
            case 4:
                ACTSendMailCorrect(self, 137);
                break;
            }
            if (GOBJ_SUB(self)->ctrl.motion == 142) {
#else
#ifdef VERSION_AUG6
                ACTSendMailCorrect(self, 150);
                break;
            case 1:
                ACTSendMailCorrect(self, 136);
                break;
            case 2:
                ACTSendMailCorrect(self, 137);
                break;
            case 3:
                ACTSendMailCorrect(self, 138);
                break;
            case 4:
                ACTSendMailCorrect(self, 139);
#else
                ACTSendMailCorrect(self, 152);
                break;
            case 1:
                ACTSendMailCorrect(self, 138);
                break;
            case 2:
                ACTSendMailCorrect(self, 139);
                break;
            case 3:
                ACTSendMailCorrect(self, 140);
                break;
            case 4:
                ACTSendMailCorrect(self, 141);
#endif
                break;
            }
            if (GOBJ_SUB(self)->ctrl.motion == 133) {
#endif
                d = 1.0f;
            } else if (s->pad.now & 0x20) {
                d = 1.0f;
            } else {
                d = 0.0f;
            }
            SaveBoyOrientForScript();
            add_rope_val = d;
            if (s->pad.now & 0x20) {
                IncreasePdlChain(s->chain);
            } else {
                DecreasePdlChain(s->chain);
            }
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 177);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 297);
            }
#endif
            break;
        case 60:
            if (!(s->stick.y - 128 < 101)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 202);
            }
            if (s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 143);
            }
            if (s->pad.now & 0x20) {
                ACTSendMailCorrect(self, 144);
#else
                ACTSendMailCorrect(self, 207);
            }
            if (s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 145);
            }
            if (s->pad.now & 0x20) {
                ACTSendMailCorrect(self, 146);
#endif
#else
                ACTSendMailCorrect(self, 210);
            }
            if (s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 147);
            }
            if (s->pad.now & 0x20) {
                ACTSendMailCorrect(self, 148);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 210);
#endif
            }
            break;
        case 20:
        case 21:
            if (girlGObj != 0) {
#ifdef VERSION_JUN26
                iosOmSendMail(girlGObj, 57, isysCurrentGObj);
            }
            break;
        case 104:
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                iosOmSendMail(girlGObj, 58, isysCurrentGObj);
#else
                iosOmSendMail(girlGObj, 59, isysCurrentGObj);
#endif
            }
            break;
        case 105:
#endif
            if (s->pad.now & 8) {
                break;
            }
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 177);
            break;
        case 101:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 332);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 202);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            ACTSendMailCorrect(self, 180);
#else
            ACTSendMailCorrect(self, 183);
#endif
            break;
        case 102:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 348);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 207);
#else
                ACTSendMailCorrect(self, 352);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 210);
#endif
#endif
            }
            break;
        case 45:
            if (0.1f < s->stick.mag) {
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 108);
                ACTSendMailCorrect(self, 107);
            }
            if (s->pad.now & 8) {
                ACTSendMailCorrect(self, 107);
                brainAddLevelGirl(10.0f);
            }
            if (s->modeFrame == 0 && ((int)(s->flags18.ll >> 36) & 1)) {
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 109);
                ACTSendMailCorrect(self, 108);
            }
            if (s->pad.now & 8) {
                ACTSendMailCorrect(self, 108);
#else
                ACTSendMailCorrect(self, 110);
                ACTSendMailCorrect(self, 109);
            }
            if (s->pad.now & 8) {
                ACTSendMailCorrect(self, 109);
#endif
                brainAddLevelGirl(10.0f);
            }
            if (s->modeFrame == 0 && ((int)(s->flags18.ll >> 37) & 1)) {
#endif
                brainAddLevelGirl(1000.0f);
            }
            break;
        case 23:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 297);
#else
                ACTSendMailCorrect(self, 306);
#endif
#else
                ACTSendMailCorrect(self, 310);
#endif
                break;
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 298);
#else
                ACTSendMailCorrect(self, 307);
#endif
#else
                ACTSendMailCorrect(self, 311);
#endif
                break;
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 299);
#else
                ACTSendMailCorrect(self, 308);
#endif
#else
                ACTSendMailCorrect(self, 312);
#endif
                break;
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 300);
            }
            break;
        case 111:
            if (0.1f < s->stick.mag &&
                !(0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 75) < 151)) {
                ACTSendMailCorrect(self, 240);
            }
            break;
        case 90:
            if (GOBJ_ACT(self)->enemy->floorAttrOff != 0) {
                ACTSendMailCorrect(self, 319);
                break;
            }
            ACTSendMailCorrect(self, 301);
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 309);
#else
                ACTSendMailCorrect(self, 313);
#endif
            }
            break;
        case 112:
            if (0.1f < s->stick.mag &&
                !(0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 75) < 151)) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 247);
#else
                ACTSendMailCorrect(self, 250);
#endif
            }
            break;
        case 91:
            if (GOBJ_ACT(self)->enemy->floorAttrOff != 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                ACTSendMailCorrect(self, 335);
                break;
            }
            ACTSendMailCorrect(self, 310);
#else
                ACTSendMailCorrect(self, 339);
                break;
            }
            ACTSendMailCorrect(self, 314);
#endif
#endif
            break;
        }
        _ACTWait(1);
    }
}

#ifndef VERSION_AUG6
/* subBoyControl's countdown, set to a fifth of a second of frames */
static int boyControlWait = 0; /* derived name */
#endif
#else
void subBoyControl(GObj *volatile self)
{
    float stick[4];
    float wish[4];
    float sabs[4];
    float dir[4];
    int c0;
    int c1;
    int c2;
    Act *s = GOBJ_ACT(self);
    void *g;
    int n;
    int sw;
    int slow;
    float d;
    float dist;
    int dbg = 0; /* local debug switch, see the test after the stick loop */

    memset(stick, 0, 16);
    c0 = 0;
    c1 = 0;
    c2 = 0;
    memset(wish, 0, 16);
    n = 0;
    iosPadConnect(&s->pad, 0, 0, &iosPadConfCustom);
    boyPad = &s->pad;
    E3_StageStartBoy((void *)self);
    layoutActPushStartNew = 0;
    while (1) {
        if (FixViewInGameCameraFlag) {
            n = 3;
        }
        if (InsertCameraWorkingFlag) {
            n = 3;
        }
        if ((int)(s->flags20.ll >> 31) & 1) {
            n = 3;
        }
        sw = 0;
        if (n) {
            n--;
            sw = 1;
        }
        for (;;) {
            if (((int)(s->flags18.ll >> 48) & 1) == 0) {
                goto noStick;
            }
            s->flags18.ll &= ~0x800000000;
            if (scpBoyControlReadDisable == 0 && GOBJ_WORK(self)->pinchFrames == 0 &&
                (PrivInsCamChk() == 0 || boyPrivInsCamInScreen())) {
                iosPadRead(&s->pad);
                if (GOBJ_WORK(self)->ditchTimer != 0) {
                    s->pad.now &= ~8;
                }
                s->flags18.ll |= 0x800000000;
                if ((int)(s->pad.dev->flags >> 16) & 1) {
                    layoutActPushStartNew = 1;
                } else {
                    layoutActPushStartNew = 0;
                }
                /* the option word's low byte */
                iosPadGetStick(&s->pad, &s->stick, 0, 2, 2, (unsigned char)debug_stick_simulate);
                if (debug_stick_input) {
                    if (debug_font_flag & 1) {
                        debug_Printf(10, 170, 0x0FFFFFFF, "L = %f\n", fptodp(s->stick.mag));
                    }
                }
                ableBoyControl = 1;
            } else {
                s->pad.rel = 0;
                s->stick.x = s->stick.y = 127;
                s->pad.trg = 0;
                s->pad.now = 0;
                s->stick.mag = 0.0f;
                ableBoyControl = 0;
            }
            _GetMotionDirection(dir, (void *)self);
            correctStick(dir, &s->stick);
            if (s->pad.trg & 1) {
                BridgeBox();
            }
            g = isysGObjSearchFromObjLayoutID(2);
            if (s->wayMode == 1) {
                float tgt[4];
                float pos[4];

                GetRootPosition(tgt, g);
                GetRootPosition(pos, (void *)self);
                if (GetWay_begin(tgt, &s->way, pos) == 0) {
                    s->wayMode = 0;
                } else {
                    s->wayMode = 2;
                }
                break;
            }
            if (s->wayMode == 2) {
                switch (s->way.reached) {
                case 0: {
                    float root[4];

                    GetRootPosition(root, (void *)self);
                    GetWay_next(&s->way, root);
                    sceVu0CopyVector(stick, s->way.nrm);
                    s->stick.mag = 1.0f;
                    break;
                }
                case 1: {
                    float p0[4];
                    float p1[4];
                    ClipWork work;

                    GetRootPosition(p0, (void *)self);
                    GetRootPosition(p1, g);
                    work.radius = 10.0f;
                    sceVu0CopyVector(work.pt[0], p0);
                    sceVu0CopyVector(work.pt[1], p1);
                    ClipWall(&work);
                    if (work.wall.elem != 0) {
                        s->wayMode = 1;
                    }
                    dist = fzMagnitude2fv(p1, p0);
                    p1[0] = p1[0] - p0[0];
                    p1[1] = 0.0f;
                    p1[2] = p1[2] - p0[2];
                    sceVu0Normalize(stick, p1);
                    if (dist < 120.0f) {
                        ACTSendMailCorrect(self, 0xC7);
                        s->wayMode = 0;
                    } else if (dist < 850.0f) {
                        s->stick.mag = (dist - 100.0f) / 750.0f;
                    } else {
                        s->stick.mag = 1.0f;
                    }
                    break;
                }
                }
                break;
            }
            if (0.1f < s->stick.mag) {
                float cam[4];

                sabs[0] = stick[0];
                sabs[1] = stick[1];
                sabs[2] = stick[2];
                ConvertStickToAbsCoord(stick, &s->stick);
                cam[0] = (float)(s->stick.x - 128);
                cam[1] = 0.0f;
                cam[2] = (float)(s->stick.y - 128);
                if (sw == 0) {
                    snapStickToCamera(stick, wish, sabs, cam);
                }
                wish[0] = cam[0];
                wish[1] = cam[1];
                wish[2] = cam[2];
                {
                    float ori[4];

                    GetRootMotionOrient(ori, (void *)self);
                    s->stick.angle = _RotyGV(stick, ori);
                }
            } else {
                s->stick.angle = 0;
                s->stick.mag = 0.0f;
            }
            if ((void *)self == CurrentTargetGObj) {
                break;
            }
            _ACTWait(1);
        }
        /* a local debug switch, off: the cursor_control idiom of way_tool.c,
           moving the current target object */
        if (dbg) {
            if ((void *)self == CurrentTargetGObj && (s->pad.trg & 1)) {
                if (s->actMode != 1) {
                    ACTSendMailCorrect(self, 258);
                }
                ACTDebugMove(self, 1);
            }
        }
        s->dir[0] = stick[0];
        s->dir[1] = stick[1];
        s->dir[2] = stick[2];
    noStick:
        GOBJ_WORK(self)->stickMag = s->stick.mag;
        {
            static int slowWalkTimer = 0; /* derived name */

            slow = 0;
            if (s->actMode == 1) {
                if (GOBJ_SUB(self)->ctrl.motion == 0 || GOBJ_SUB(self)->ctrl.motion == 1) {
                    if (0.5f < s->stick.mag) {
                        slowWalkTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 5;
                    }
                }
            }
            if (0 < slowWalkTimer) {
                slowWalkTimer--;
                slow = 1;
            }
        }
        if (slow && 0.5f < s->stick.mag) {
            s->stick.mag = 0.5f;
        }
        c0++;
        if (0.1f < s->stick.mag) {
            c0 = 0;
        }
        if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) {
            c1++;
        } else {
            c1 = 0;
        }
        if (0.1f < s->stick.mag &&
            !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)))) {
            c2++;
        } else {
            c2 = 0;
        }
        _ACTCommonMailTest(self, c0, c1, c2);
        switch (s->actMode) {
        case 1:
            ACTSendMailCorrect(self, 0xC7);
            break;
        case 2:
            ACTSendMailCorrect(self, 0xB5);
            break;
        case 3:
            ACTSendMailCorrect(self, 0xBA);
            break;
        case 41:
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 0x149);
            }
            break;
        case 29:
            if (s->pad.trg & 0x40) {
                if (100.0f < GetDifferenceFromLowerField(self, 44)) {
                    ACTSendMailCorrect(self, 0x127);
                } else {
                    ACTSendMailCorrect(self, 0xE2);
                }
            }
            if (s->pad.now & 0x10) {
                ACTSendMailCorrect(self, 0xC7);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 26:
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                sceVu0ScaleVector(GOBJ_WORK(self)->fallDir, (char *)GOBJ_ACT(self)->work + 0x8C0,
                                  -1.0f);
#else
                sceVu0ScaleVector(GOBJ_WORK(self)->fallDir, (char *)GOBJ_ACT(self)->work + 0x8D0,
                                  -1.0f);
#endif
                ACTSendMailCorrect(self, 0x139);
            }
            break;
        case 27:
            if (0.1f < s->stick.mag &&
                _AbsRotyGV(stick, (char *)GOBJ_ACT(self)->work + 0x470) >= 136 &&
                GetMotionFrameFlag1((void *)self)) {
                ACTSendMailCorrect(self, 0x131);
            }
            if ((s->pad.now & 0x10) && GetMotionFrameFlag1((void *)self)) {
                ACTSendMailCorrect(self, 0x131);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 0x130);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            }
            if (s->pad.now & 0x10) {
                ACTSendMailCorrect(self, 0xC7);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x127);
            break;
        case 28:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 30:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            } else if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 0xC7);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 31:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 33:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            }
            break;
        case 40:
            if ((s->pad.trg & 0x10) || s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 0x12F);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            }
            break;
        case 34:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            } else if (s->pad.now & 0x10) {
                ACTSendMailCorrect(self, 0x12E);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 35:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0xE2);
            }
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 0xBD);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            break;
        case 52: {
            int near = 1;
            int front = 1;
            float gpos[4];
            float tpos[4];
            float ori[4];
            float vec[4];
            void *obj = s->env.pullParent;

            if (obj != 0 && girlGObj != 0) {
                gpos[0] = test_CURRENTROOT(girlGObj)[0];
                gpos[1] = test_CURRENTROOT(girlGObj)[1];
                gpos[2] = test_CURRENTROOT(girlGObj)[2];
                GetRootPosition(tpos, obj);
                ori[0] = test_CURRENTORIENT((void *)self)[0];
                ori[1] = test_CURRENTORIENT((void *)self)[1];
                ori[2] = test_CURRENTORIENT((void *)self)[2];
                _OrientXZGV(vec, gpos, tpos);
                if (_DistSqGV(tpos, gpos) < 250000.0f &&
                    CheckFloorAttribute(girlGObj, 0xA000000) != 0) {
                    if (0.0f < sceVu0InnerProduct(ori, vec)) {
                        near = 0;
                    } else {
                        front = 0;
                    }
                }
            }
            if (s->pad.now & 0x20) {
                if (near && 0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                    ACTSendMailCorrect(self, 0x81);
                    break;
                }
                if (front && 0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 0x80);
                    break;
                }
                ACTSendMailCorrect(self, 0x150);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            ACTSendMailCorrect(self, 0xC7);
            break;
        }
        case 53:
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 90 / 60 > s->modeFrame) {
                ACTSendMailCorrect(self, 0x86);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            ACTSendMailCorrect(self, 0xC7);
            break;
        case 54:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag) {
                    ACTSendMailCorrect(self, 0x86);
                    if (s->pad.now & 8) {
                        ACTSendMailCorrect(self, 0x42);
                    }
                } else {
                    ACTSendMailCorrect(self, 0x150);
                }
            } else {
                ACTSendMailCorrect(self, 0xC7);
            }
            break;
        case 32:
        case 38: {
            /* the actor, read at the head of this arm; the DEBUG build's report
               reads it */
            GObj *obj = self;

            if (((int)(*(unsigned long long *)((char *)GOBJ_ACT(self)->enemy + 0x298) >> 1) & 1) &&
                !(s->stick.y - 128 < 101)) {
                ACTSendMailCorrect(self, 0x14B);
            } else if ((*(int *)((char *)GOBJ_ACT(self)->enemy + 0x298) & 1) &&
                       s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 0x14A);
            } else {
                ACTSendMailCorrect(self, 0x150);
            }
            if ((optionControlType == 1 ? s->pad.trg : s->pad.now) & 8) {
                ACTSendMailCorrect(self, 0x42);
            }
#ifdef DEBUG
            scePrintf("boy %08x stick %d\n", obj, s->stick.y - 128);
#endif
            break;
        }
        case 43:
            if (0.95f < s->stick.mag) {
                ACTSendMailCorrect(self, 0xDE);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 44:
            if (0.95f < s->stick.mag) {
                ACTSendMailCorrect(self, 0xDD);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 49:
            if (s->pad.now & 0x20) {
                switch (s->pushDir) {
                case 1:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                        ACTSendMailCorrect(self, 0x14C);
                    } else {
                        ACTSendMailCorrect(self, 0x150);
                    }
                    break;
                case -1:
                    if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 0x14D);
                    } else {
                        ACTSendMailCorrect(self, 0x150);
                    }
                    break;
                default:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                        ACTSendMailCorrect(self, 0x14C);
                    } else if (0.1f < s->stick.mag &&
                               !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 0x14D);
                    } else {
                        ACTSendMailCorrect(self, 0x150);
                    }
                    break;
                }
            } else {
                ACTSendMailCorrect(self, 0x150);
                ACTSendMailCorrect(self, 0xC7);
            }
            break;
        case 51:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                    ACTSendMailCorrect(self, 0x14C);
                } else if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 0x14D);
                } else {
                    ACTSendMailCorrect(self, 0x150);
                }
            } else {
                ACTSendMailCorrect(self, 0xC7);
            }
            break;
        case 118:
            if (s->pad.trg & 0x20) {
                ACTSendMailCorrect(self, 0xC8);
                break;
            }
            if (0.1f < s->stick.mag &&
                !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)))) {
                ACTSendMailCorrect(self, 0xBA);
                break;
            }
            if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) {
                ACTSendMailCorrect(self, 0xB5);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        case 58:
            switch (GetChainSlope()) {
            case 0:
                ACTSendMailCorrect(self, 0xA3);
                if (GOBJ_SUB(self)->ctrl.motion == 137 && GOBJ_SUB(self)->ctrl.animFrame < 50.0f) {
                    ACTSendMailCorrect(self, 0xA4);
                }
                break;
            case 1:
                ACTSendMailCorrect(self, 0x94);
                break;
            case 2:
                ACTSendMailCorrect(self, 0x95);
                break;
            case 3:
                ACTSendMailCorrect(self, 0x96);
                break;
            case 4:
                ACTSendMailCorrect(self, 0x97);
                break;
            }
            if (GOBJ_SUB(self)->ctrl.motion == 135) {
                d = 1.0f;
            } else if (s->pad.now & 0x20) {
                d = 1.0f;
            } else {
                d = 0.0f;
            }
            SaveBoyOrientForScript();
            add_rope_val = d;
            if (s->pad.now & 0x20) {
                IncreasePdlChain(s->chain);
            } else {
                DecreasePdlChain(s->chain);
            }
            if (s->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 0xBE);
                ACTSendMailCorrect(self, 0xC4);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0x13C);
            }
            break;
        case 60:
            if (!(s->stick.y - 128 < 101)) {
                ACTSendMailCorrect(self, 0x13C);
            }
            if (s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 0x9E);
            }
            if (s->pad.now & 0x20) {
                ACTSendMailCorrect(self, 0x9F);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0x13C);
            }
            break;
        case 20:
        case 21:
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x3E, isysCurrentGObj);
            }
            break;
        case 109:
            if (s->pad.now & 8) {
                break;
            }
            ACTSendMailCorrect(self, 0xC7);
            break;
        case 105:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 0x17C);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 0xE2);
            }
            break;
        case 45:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 0x75);
                ACTSendMailCorrect(self, 0x74);
            }
            if (s->pad.now & 8) {
                ACTSendMailCorrect(self, 0x74);
                brainAddLevelGirl(10.0f);
            }
            if (s->modeFrame == 0 && ((int)(s->flags18.ll >> 41) & 1)) {
                brainAddLevelGirl(1000.0f);
            }
            break;
        case 23:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 0x14C);
                break;
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 0x14D);
                break;
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 0x14E);
                break;
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 0x14F);
            }
            break;
        case 94:
            if (GOBJ_ACT(self)->enemy->floorAttrOff != 0) {
                ACTSendMailCorrect(self, 0x16F);
                break;
            }
            ACTSendMailCorrect(self, 0x150);
            break;
        }
        _ACTWait(1);
    }
}
#endif

typedef struct {                      /* field names derived */
    int boyID;                        /* 0x00 */
    int girlID;                       /* 0x04 */
    unsigned long long layoutID : 32; /* 0x08 */
    /* the one-bit flags are declared no wider than short; torch is a
       short */
    unsigned char bit32 : 1;
    unsigned char fire : 1;
    unsigned short torch : 1;
    unsigned char escort : 1;
    char pad10[16];          /* 0x10 */
    void *weapon;            /* 0x20 */
    void *nextWeapon;        /* 0x24 */
    char pad28[0x30 - 0x28]; /* 0x28 */
    float f30;               /* 0x30 */
    float f34;
    float f38;
    char pad3C[4];
    float f40; /* 0x40 */
    float f44;
    float f48;
    char pad4C[4];
    CharPos f50; /* 0x50 */
} BoyInfo;       /* derived name */

#define BOYINFO (*(BoyInfo *)boyInfo) /* derived name */
/* BoyInfo's +0x50 record as the ef-stage return reads it: a flag byte and the
   camera target id at +4 (BoyInfoUpdate_StageChange copies it whole as f50). */
#define BOYEFSTAGE ((unsigned char *)boyInfo + 0x50) /* derived name */

static void InitSwapWeapon(void *self)
{
    Act *sub = GOBJ_ACT(self);
    GObj *info;
    char *p;
    GenGeo *row;

    if (BOYINFO.boyID != 0) {
        BOYINFO.weapon = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
    } else {
        BOYINFO.weapon = 0;
    }
    info = sub->env.swapWeapon;
    BOYINFO.nextWeapon = info;
    p = (char *)gamesysObjInfoGet(info->kind, info->labelId);
    if (p != 0) {
        BOYINFO.f30 = *(float *)(p + 0x10);
        BOYINFO.f34 = *(float *)(p + 0x14);
        BOYINFO.f38 = *(float *)(p + 0x18);
        BOYINFO.f40 = *(float *)(p + 0x20);
        BOYINFO.f44 = *(float *)(p + 0x24);
        BOYINFO.f48 = *(float *)(p + 0x28);
    } else {
        row = &objLayout[info->labelId];
        BOYINFO.f30 = -row->pos[0];
        BOYINFO.f34 = -row->pos[1];
        BOYINFO.f38 = -row->pos[2];
#ifdef VERSION_JUN26
        BOYINFO.f40 = row->rot[0];
        BOYINFO.f44 = row->rot[1];
        BOYINFO.f48 = row->rot[2];
#else
        BOYINFO.f40 = row->rot[0] * 3.1415927f / 180.0f;
        BOYINFO.f44 = row->rot[1] * 3.1415927f / 180.0f;
        BOYINFO.f48 = row->rot[2] * 3.1415927f / 180.0f;
#endif
    }
}

static void PutWeapon(void)
{
    char *p = (char *)boyInfo;
#ifdef VERSION_JUN26
    struct MotRoot *root;

    if (*(void **)(p + 0x20) != 0) {
        root = &GOBJ_SUB(*(void **)(p + 0x20))->root;
        InitMotionGeoInfo(
            root, *(float *)(p + 0x30), *(float *)(p + 0x34), *(float *)(p + 0x38), 0.0f,
            -((int)(_GetDirection(test_CURRENTORIENT(boyGObj)) / 3.1415927f * 180.0f) * 3.1415927f /
              180.0f),
            0.0f);
#else

    if (*(void **)(p + 0x20) != 0) {
        InitMotionGeoInfo(&GOBJ_SUB(*(void **)(p + 0x20))->root, *(float *)(p + 0x30),
                          *(float *)(p + 0x34), *(float *)(p + 0x38), -*(float *)(p + 0x40),
                          -*(float *)(p + 0x44), -*(float *)(p + 0x48));
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
        if (CheckWeaponKind(*(void **)(p + 0x20)) == 9) {
            SetWeaponOffsetMode(*(void **)(p + 0x20), 1);
        }
#endif
#endif
        UpdateRootMatrix(*(void **)(p + 0x20));
    }
}

/* a static helper inlined into SetBoyWeaponGObj and afterBoyTakeWeapon */
static inline int SwapBoyWeapon(void *oldW, void *newW, void *boy) /* derived name */
{
    Act *sub = GOBJ_ACT(boy);

    if (oldW == newW) {
        return 0;
    }
    if (newW == 0) {
#ifdef VERSION_AUG6
        debug_assert(__FILE__, LN(1731, 1724, 1724, 1543, 2695, 1731));
#else
#ifdef VERSION_JUN26
        debug_assert(__FILE__, LN(1731, 1724, 1724, 1543, 1493, 2475));
#else
        debug_assert(__FILE__, LN(3007, 3000, 3000, 2757, 3007, 3007));
#endif
#endif
        __assert(__FILE__, LN(3007, 3000, 3000, 2757, 2695, 2475), "next");
        return 0;
    }
#ifdef VERSION_JUN26
    PickupWeapon(newW, boy, 22);
#else
    PickupWeapon(newW, boy, 0x16);
#endif
    ((int *)boyInfo)[0] = *(int *)((char *)newW + 0x8);
#if defined(VERSION_NTSC) || defined(VERSION_JUN26)
    sub->weapon = newW;
#else
#ifdef VERSION_AUG6
    *(void **)((char *)sub + 0x130) = newW;
#else
    *(void **)((char *)sub + 0x150) = newW;
    SetWeaponOffsetMode(newW, 0);
#endif
#endif

    if (oldW == 0) {
        return 1;
    }
    ReleaseWeapon(oldW);
    PutWeapon();
    gamesysObjInfoPosSetStage(oldW, 0, 0, stage_no);
    debug_StdPrintfDummy("%d -> %d\n", *(int *)((char *)oldW + 0x8), *(int *)((char *)newW + 0x8));
    return 1;
}

#ifndef VERSION_JUN26
/* returns float * here, int * in camera-root.h */
extern float *GetCurrentCameraSet2(void);

#ifdef VERSION_NTSC
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);
#endif

#ifdef VERSION_AUG6
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames);
#endif

static void OtherStageGirlPinchCamera_After(float t)
{
    float buf[4];

    pinchBoyPos[0] = test_CURRENTROOT(boyGObj)[0];
    pinchBoyPos[1] = test_CURRENTROOT(boyGObj)[1];
    pinchBoyPos[2] = test_CURRENTROOT(boyGObj)[2];
    if (_ACTGame_GetParamF(0xE) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f <=
        t) {
        pinchBoyPosLate[0] = test_CURRENTROOT(boyGObj)[0];
        pinchBoyPosLate[1] = test_CURRENTROOT(boyGObj)[1];
        pinchBoyPosLate[2] = test_CURRENTROOT(boyGObj)[2];
#ifdef VERSION_AUG6
        GetOtherStageGirlOrient(buf);
#else
        GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
#endif
        sceVu0ScaleVector(buf, buf, 500.0f);
        sceVu0AddVector(pinchCameraPos, GetCurrentCameraSet2(), buf);
    } else {
#ifdef VERSION_NTSC
        _InterGV(pinchBoyPosLate, pinchBoyPosLate, pinchCameraPos, 1.0f, 8.0f);
        InsertCamera_SetNoraml(GetCurrentCameraSet2(), pinchBoyPosLate, 5, 1);
#else
#ifdef VERSION_AUG6
        _InterGV(pinchBoyPosLate, pinchBoyPosLate, pinchCameraPos, 1.0f, 8.0f);
        InsertCamera_SetNoraml(GetCurrentCameraSet2(), pinchBoyPosLate, 5);
#else
        PrivInsCamSet(test_CURRENTROOT(boyGObj), pinchCameraPos, boyGObj,
                      (60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60,
                      (60 - systemStatus[0] * 10) / systemStatus[1] * 45 / 60, 0.05f, 0.25f, 0);
        GOBJ_WORK(boyGObj)->pinchFrames = 0;
#endif
#endif
    }
}

#ifdef VERSION_NTSC
void ACTDispLwsBoyStonize_InQueenStage(void *self)
{
    BoyBgaManager(self, 416, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
    BoyBgaManager(self, 417, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
    BoyBgaManager(self, 421, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
    BoyBgaManager(self, 421, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
    BoyBgaManager(self, 422, (char *)GOBJ_ACT(self)->enemy + 0x2A8);
}

static int characterPacket[6]; /* derived name */
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
#else
#ifdef VERSION_AUG6
static int characterPacket[6]; /* derived name */
#else
void ACTDispLwsBoyStonize_InQueenStage(void *self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    BoyBgaManager(self, 476, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
    BoyBgaManager(self, 477, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
    BoyBgaManager(self, 481, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
    BoyBgaManager(self, 481, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
    BoyBgaManager(self, 482, (char *)GOBJ_ACT(self)->enemy + 0x2A8);
#else
    BoyBgaManager(self, 0x1E0, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
    BoyBgaManager(self, 0x1E1, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
    BoyBgaManager(self, 0x1E5, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
    BoyBgaManager(self, 0x1E5, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
    BoyBgaManager(self, 0x1E6, (char *)GOBJ_ACT(self)->enemy + 0x2A8);
#endif
}

static int characterPacket[8]; /* derived name */

static PrivInsCam privInsCam; /* derived name */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetDetail(float *pos, float *tgt, int frames, int cutType, int zoom,
                                   int cutBack, float blend);

static void PrivInsCamProcess(void)
{
    float p[4];

    switch (privInsCam.on) {
    case 1:
        privInsCam.cur[0] = privInsCam.pos[0];
        privInsCam.cur[1] = privInsCam.pos[1];
        privInsCam.cur[2] = privInsCam.pos[2];
        privInsCam.cnt = privInsCam.inFrames;
        privInsCam.on = 2;
        break;
    case 2:
        _InterGV(privInsCam.cur, privInsCam.tgt, privInsCam.cur, 1.0f, privInsCam.inRate);
        InsertCamera_SetDetail(GetCurrentCameraSet2(), privInsCam.cur, 5, 1, 2, 0,
                               privInsCam.blend);
        if (--privInsCam.cnt <= 0) {
            privInsCam.on = 3;
        }
        break;
    case 3:
        privInsCam.tgt[0] = privInsCam.cur[0];
        privInsCam.tgt[1] = privInsCam.cur[1];
        privInsCam.tgt[2] = privInsCam.cur[2];
        privInsCam.cnt = privInsCam.outFrames;
        privInsCam.on = 4;
        break;
    case 4:
        if (privInsCam.track != 0) {
            p[0] = test_CURRENTROOT(privInsCam.track)[0];
            p[1] = test_CURRENTROOT(privInsCam.track)[1];
            p[2] = test_CURRENTROOT(privInsCam.track)[2];
        } else {
            p[0] = privInsCam.pos[0];
            p[1] = privInsCam.pos[1];
            p[2] = privInsCam.pos[2];
        }
        _InterGV(privInsCam.cur, p, privInsCam.tgt, (float)privInsCam.cnt,
                 (float)(privInsCam.outFrames - privInsCam.cnt));
        InsertCamera_SetDetail(GetCurrentCameraSet2(), privInsCam.cur, 2, 1, 0, 0,
                               privInsCam.blend);
        if (--privInsCam.cnt <= 0) {
            privInsCam.on = 0;
        }
        break;
    }
}
#endif
#endif

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri);
#endif

/* the object kinds the proximity scan below walks, terminated by -1 */
typedef struct { /* field names derived */
    int id[4];
} ObjKindList; /* derived name */

#ifdef VERSION_NTSC
static const ObjKindList collisionKinds = {{4, 46, 61, -1}}; /* derived name */
#else
#ifdef VERSION_AUG6
static const ObjKindList collisionKinds = {{4, 46, 60, -1}}; /* derived name */
#else
#ifdef VERSION_JUN26
static const ObjKindList collisionKinds = {{4, 45, 59, -1}}; /* derived name */

/* returns float * here, int * in camera-root.h */
extern float *GetCurrentCameraSet2(void);

/* the character packet, 24 bytes (Boy_Init copies three doublewords); the
   object's .bss ends after it at 0x6F51F8 */
static int characterPacket[6]; /* derived name */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri);
#else
static const ObjKindList collisionKinds = {{4, 47, 62, -1}}; /* derived name */

/* reset the private insert camera to its initial value; only
   subBoyCollision calls it */
static inline void PrivInsCamInit(void) /* derived name */
{
    privInsCam = privInsCamDefault;
}
#endif
#endif
#endif

/* the nearest object of a kind in front of the actor, which ACTSearchGObj,
   subBoyCollision and actBoyAttack inline */
static inline void searchGObj(void *self, int kind, int maxDeg, int *out_id, float *out_vec,
                              float thresh) /* derived name */
{
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(kind);
    best = maxDeg;
    *out_id = 0;
    for (; node != 0; node = isysGObjSearchFromObjKindID_next(node)) {
        if (*(int *)((char *)node + 0x16C) != 0) {
            float *r1 = test_CURRENTROOT(self);
            if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                int sign;
                int dist;
                float *r4 = test_CURRENTROOT(node);
                sceVu0SubVector(buf, r4, test_CURRENTROOT(self));
                sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                if (sign < 0) {
                    dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                } else {
                    dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(self));
                }
                if (dist < best) {
                    best = dist;
                    out_vec[0] = buf[0];
                    out_vec[1] = buf[1];
                    out_vec[2] = buf[2];
                    *out_id = (int)node;
                }
            }
        }
    }
}

#ifndef VERSION_JUN26
/* the DEBUG build's report of subBoyCollision's camera state, built only
   under DEBUG */
static __inline__ void boyCamDebugDisp(int camOn, int looking) /* derived name */
{
#ifdef DEBUG
    scePrintf("boy camera on %d looking %d\n", camOn, looking);
#endif
}
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
void subBoyCollision(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int camOn;
    int looking;
    int hang;
    int hangBit;
    int dbg = 0; /* local debug switch, see the test after the helper's SetRootPosition */

    while ((int)sub->motReq == 0) {
        _ACTWait(1);
    }
    if (200.0f < GetDifferenceFromLowerField(self, 0x2C)) {
        ACTSendMailCorrect(self, 7);
    }
    while (1) {
        float vec[4];

        camOn = 0;
        if (0 < GOBJ_WORK(self)->pinchFrames) {
            _ACTCharStatus_Set((void *)self, 29, -1.0f, 0);
            OtherStageGirlPinchCamera_After((float)GOBJ_WORK(self)->pinchFrames);
            GOBJ_WORK(self)->pinchFrames -= 1;
        }
        findChainInJump((void *)self);
        CheckCollisionAttr((void *)self);
        ACTGame_CommonLoop((void *)self);
#ifdef VERSION_AUG6
        BoyBgaManager(self, 415, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
        BoyBgaManager(self, 416, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
        BoyBgaManager(self, 420, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
        BoyBgaManager(self, 420, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
        BoyBgaManager(self, 421, (char *)GOBJ_ACT(self)->enemy + 0x2A8);
#endif

        hangBit = ((int)(sub->flags18.ll >> 45) & 1);
        hang = 1;
#ifdef VERSION_AUG6
        if (((int)(sub->flags20.ll >> 4) & 1) == 0) {
#else
        if (((int)(sub->flags20.ll >> 7) & 1) == 0) {
#endif
            hang = hangBit;
        }
        if (hang == 0) {
            if (sub->stick.mag != 0.0f &&
                CorrectOrient_RopeCliff(vec, (void *)self, sub->dir) != 0) {
                sub->dir[0] = vec[0];
                sub->dir[1] = vec[1];
                sub->dir[2] = vec[2];
            }
            if (0.1f < sub->stick.mag && sub->actMode != 111) {
                SetMotionDirectionSmooze(self, sub->dir,
                                         (float)motionKind[GOBJ_SUB(self)->ctrl.motion].dirFrames);
            }
        }
        CommonAttackCenter((void *)self);
        ACTGame_SaveActorInformation(self);
        if (ACTGame_CheckItemMotion(self) == 0) {
            afterCommonItem(self);
        }
        if (*(unsigned int *)((char *)sub + 0x30) < 4 && sub->actMode != 0) {
            if (sub->pad.trg & 0x20) {
                int hit;

                searchGObj((void *)self, 19, 45, &hit, vec, 100.0f);
            }
        }
        switch (sub->actMode) {
        case 28:
            if (((int)(sub->wish1.ll >> 3) & 1) && ((int)(sub->wish3.ll >> 3) & 1)) {
#ifdef VERSION_AUG6
                ACTSendMailCorrect(self, 180);
#else
                ACTSendMailCorrect(self, 183);
#endif
            }
            break;
        case 38:
#ifndef VERSION_AUG6
            if (sub->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 297);
            }
#endif
            break;
        case 57:
            SaveBoyOrientForScript();
            add_rope_val = 0.0f;
#ifdef VERSION_AUG6
            if (sub->pad.now & 0x20) {
                ACTSendMailCorrect(self, 149);
                ACTSendMailCorrect(self, 208);
            } else {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 304);
                } else if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 305);
                    if (isBottomOfChain(sub->chain)) {
                        ACTSendMailCorrect(self, 144);
#else
            if (sub->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 297);
            }
            if (sub->pad.now & 0x20) {
                ACTSendMailCorrect(self, 151);
                ACTSendMailCorrect(self, 211);
            } else {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 308);
                } else if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 309);
                    if (isBottomOfChain(sub->chain)) {
                        ACTSendMailCorrect(self, 146);
#endif
                    }
                } else if (GOBJ_SUB(self)->ctrl.motion == 116) {
                    float bodyori[4];
                    int cor;
                    int ry;

                    GetCorrectOrientOfChain(vec, (void *)self);
                    SetMotionDirection((void *)self, vec);
                    if (GetChainDirCorrectVal((void *)sub->chain, &cor) != 0) {
                        if (sub->stick.x - 0x80 < -100) {
#ifdef VERSION_AUG6
                            ACTSendMailCorrect(self, 147);
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ACTSendMailCorrect(self, 148);
#else
                            ACTSendMailCorrect(self, 149);
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ACTSendMailCorrect(self, 150);
#endif
                        }
                    } else {
                        if (sub->stick.x - 0x80 < -100) {
                            ry = 5;
                        } else {
                            ry = 0;
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ry = -5;
                        }
                        bodyori[0] = test_CURRENTORIENT((void *)self)[0];
                        bodyori[1] = test_CURRENTORIENT((void *)self)[1];
                        bodyori[2] = test_CURRENTORIENT((void *)self)[2];
                        _ApplyRyGV(bodyori, (float)ry * 3.1415927f / 180.0f);
                        SetMotionDirection((void *)self, bodyori);
                    }
                }
#ifdef VERSION_AUG6
                ACTSendMailCorrect(self, 310);
#else
                ACTSendMailCorrect(self, 314);
#endif
            }
            break;
        case 66:
#ifdef VERSION_AUG6
            if (((int)(sub->flags20.ll >> 1) & 1) == 0) {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 304);
                }
                if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 305);
#else
            if (((int)(sub->flags20.ll >> 2) & 1) == 0) {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 308);
                }
                if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 309);
#endif
                }
            }
            if (GOBJ_SUB(self)->ctrl.motion == 116) {
                if (sub->stick.x - 0x80 < -100) {
#ifdef VERSION_AUG6
                    ACTSendMailCorrect(self, 147);
                }
                if (100 < sub->stick.x - 0x80) {
                    ACTSendMailCorrect(self, 148);
                }
            }
            ACTSendMailCorrect(self, 310);
            break;
        case 55:
#else
                    ACTSendMailCorrect(self, 149);
                }
                if (100 < sub->stick.x - 0x80) {
                    ACTSendMailCorrect(self, 150);
                }
            }
            ACTSendMailCorrect(self, 314);
            if (sub->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 297);
            }
            break;
        case 55:
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->curMot != 85 &&
                GOBJ_ACT(girlGObj)->curMot != 92 &&
                (60 - systemStatus[0] * 10) / systemStatus[1] < sub->modeFrame) {
                if (((int)(sub->wish0.ll >> 46) & 1) == 0 ||
                    ((int)(sub->wish2.ll >> 46) & 1) == 0) {
                    ACTSendMailCorrect(self, 233);
                } else {
                    ACTSendMailCorrect(self, 234);
                }
            }
#endif
            /* falls through into the next arm */
        case 68:
            if (((int)(sub->wish0.ll >> 45) & 1) && ((int)(sub->wish2.ll >> 45) & 1)) {
                if (girlGObj != 0) {
#ifdef VERSION_AUG6
                    iosOmSendMail(girlGObj, 58, isysCurrentGObj);
                }
                ACTSendMailCorrect(self, 231);
            } else if (NotNeedBackHand() ||
                       (GOBJ_ACT(girlGObj)->intrMot != 84 && GOBJ_ACT(girlGObj)->intrMot != 91 &&
                        (60 - systemStatus[0] * 10) / systemStatus[1] * 2 < sub->modeFrame)) {
                if (((int)(sub->wish0.ll >> 46) & 1) && ((int)(sub->wish2.ll >> 46) & 1)) {
                    ACTSendMailCorrect(self, 231);
                } else {
                    ACTSendMailCorrect(self, 230);
#else
                    iosOmSendMail(girlGObj, 59, isysCurrentGObj);
                }
                ACTSendMailCorrect(self, 234);
            } else if (NotNeedBackHand() ||
                       (GOBJ_ACT(girlGObj)->intrMot != 85 && GOBJ_ACT(girlGObj)->intrMot != 92 &&
                        (60 - systemStatus[0] * 10) / systemStatus[1] * 2 < sub->modeFrame)) {
                if (((int)(sub->wish0.ll >> 46) & 1) && ((int)(sub->wish2.ll >> 46) & 1)) {
                    ACTSendMailCorrect(self, 234);
                } else {
                    ACTSendMailCorrect(self, 233);
#endif
                }
            }
            break;
        /* the table runs from 1, with this arm empty */
        case 1:
            break;
        }
        {
            int work[4];
            int scr[4];
            int tgt[4];
            int ofs[4];
            int cpos[4];

            if (((int)(sub->wish0.ll >> 44) & 1) == 0 || ((int)(sub->wish2.ll >> 44) & 1) == 0) {
                girlLookStarted = 0;
                girlLookInScreen = 0;
            }
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 69) {
                sceVu0ScaleVector(vec, test_CURRENTORIENT((void *)self), 200.0f);
                vec[1] = 0.0f;
                sceVu0AddVector(vec, test_CURRENTROOT((void *)self), vec);
                _ACTLookTarget_Set((void *)self, 0, vec, 1, 1);
            }
            if (((int)(sub->wish0.ll >> 44) & 1) && ((int)(sub->wish2.ll >> 44) & 1)) {
#ifndef VERSION_AUG6
                int see = 0;
                int onGirl = 0;
#endif

                if (girlLookStarted == 0) {
                    girlLookStarted = 1;
                    if (girlGObj != 0) {
#ifdef VERSION_AUG6
                        girlLookInScreen =
                            (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(girlGObj))) ? 1 : 0;
#else
                        girlLookInScreen =
                            (0.0f < IsPointIsInScreen(scr, test_CURRENTROOT(girlGObj))) ? 1 : 0;
#endif
                    }
                }
                if (girlGObj != 0) {
#ifdef VERSION_AUG6
                    float d = _DistGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));

                    if (d < _ACTGame_GetParamF(3)) {
#else
                    ((float *)work)[0] = test_CURRENTROOT(girlGObj)[0];
                    ((float *)work)[1] = test_CURRENTROOT(girlGObj)[1];
                    ((float *)work)[2] = test_CURRENTROOT(girlGObj)[2];
                    see = 1;
                    onGirl = 1;
                } else if ((stage_no == 84 || stage_no == 3 || stage_no == 46) &&
                           ((int)(sub->flags20.ll >> 13) & 1)) {
                    see = 1;
                    onGirl = 0;
                    ScpCallCameraGetTarget((float *)work);
                }
                if (see) {
                    float d = _DistGV(test_CURRENTROOT((void *)self), (float *)work);

                    if (d < _ACTGame_GetParamF(3) && onGirl) {
#endif
                        _ACTParaStatus_Set((void *)self, 21);
                        _ACTCharStatus_Set((void *)self, 30, -1.0f, 0);
                    } else if (d < _ACTGame_GetParamF(4)) {
                        _ACTParaStatus_Set((void *)self, 20);
                        _ACTCharStatus_Set((void *)self, 32, -1.0f, 0);
                    } else {
                        _ACTParaStatus_Set((void *)self, 19);
                        _ACTCharStatus_Set((void *)self, 31, -1.0f, 0);
                    }
                } else {
                    _ACTParaStatus_Set((void *)self, 19);
                    _ACTCharStatus_Set((void *)self, 31, -1.0f, 0);
                }
                looking = girlGObj != 0;
                if (looking) {
                    _ACTLookTarget_Set((void *)self, girlGObj, 0, 4, 2);
#ifdef VERSION_AUG6
                    if (girlLookInScreen == 0 && ((int)(sub->flags20.ll >> 9) & 1)) {
                        if ((int)(sub->flags20.ll >> 10) & 1) {
#else
                    if (girlLookInScreen == 0 && ((int)(sub->flags20.ll >> 12) & 1)) {
                        if ((int)(sub->flags20.ll >> 13) & 1) {
#endif
                            void *lo = isysGObjSearchFromObjLayoutID(4);

                            if (lo != 0) {
#ifdef VERSION_AUG6
                                ScpCallCameraGetTarget((float *)scr);
                                SetRootPosition(lo, scr);
#else
                                ScpCallCameraGetTarget((float *)tgt);
                                SetRootPosition(lo, tgt);
#endif
                                Camctrl_SetTarget(self, lo, 1);
                            }
                        } else {
                            Camctrl_SetTarget(self, girlGObj, 1);
                        }
                    }
                }
            }
            {
                int i;
                float near = 3.40282347e+38f; /* FLT_MAX */

                *(ObjKindList *)work = collisionKinds;
                for (i = 0; work[i] != -1; i++) {
                    void *g;

                    for (g = isysGObjSearchFromObjKindID_begin(work[i]); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
                        if ((int)(GOBJ_ACT(g)->flags18.ll >> 32) & 1) {
                            float d = _DistGV(test_CURRENTROOT((void *)self), test_CURRENTROOT(g));

                            if (work[i] == 46) {
                                if (*(int *)((char *)g + 0x16C) == 0) {
                                    continue;
                                }
                                d = 1.0f;
                            }
                            if (d < near) {
                                near = d;
                            }
                        }
                    }
                }
                if (ACTGame_NoWeapon((void *)self) == 0) {
                    if (near < 1000.0f) {
                        _ACTParaStatus_Set((void *)self, 2);
                    }
                    if (near < 300.0f) {
                        _ACTParaStatus_Set((void *)self, 3);
                    }
                }
                if (near < 1000.0f) {
                    _ACTCharStatus_Set((void *)self, 15, near, 0);
                }
            }
            if (_ACTParaStatus_Check((void *)self, 0x3) ||
                _ACTParaStatus_Check((void *)self, 0x2)) {
                if (_ACTParaStatus_Check((void *)self, 20)) {
                    _ACTParaStatus_Set((void *)self, 23);
                }
                if (_ACTParaStatus_Check((void *)self, 19)) {
                    _ACTParaStatus_Set((void *)self, 22);
                }
            }
            if (ACTGame_NoWeapon((void *)self)) {
                _ACTParaStatus_Set((void *)self, 4);
            }
            ACTParaStatus_Exec((void *)self);
            {
                /* the weapon search, defined here and inlined into the test
               below */
                inline void *searchWeapon(void) /* derived name */
                {
                    void *g;

                    for (g = isysGObjSearchFromObjKindID_begin(0xE); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
                        if (CheckWeaponKind(g) == 5) {
                            return g;
                        }
                    }
                    return 0;
                }
                void *w;

                if (girlGObj == 0 && (w = searchWeapon()) != 0) {
                    if ((sub->pad.now & 0x8) == 0) {
                        weaponLookInScreen = 0;
                        weaponLookStarted = 0;
                    } else {
                        if (weaponLookStarted == 0) {
                            weaponLookInScreen =
                                (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(w))) ? 1 : 0;
                        }
                        weaponLookStarted = 1;
#ifdef VERSION_AUG6
                        if ((sub->flags20.ll & 0x600) == 0x200) {
#else
                        if ((sub->flags20.ll & 0x3000) == 0x1000) {
#endif
                            Camctrl_SetTarget(self, w, 1);
                            camOn = 1;
                        }
                    }
                }
            }
            if (camOn == 0 && girlGObj == 0) {
                void *lo = isysGObjSearchFromObjLayoutID(4);

                /* In retail camOn and looking are dead from here on; the DEBUG
               build's camera report at the end of this block reads them. */
                if (lo == 0) {
                    camOn = 1;
                    looking = 0;
                }
                if ((sub->pad.now & 0x8) && lo != 0) {
#ifdef VERSION_AUG6
                    GetOtherStageGirlOrient((float *)ofs);
#endif
                    ((float *)tgt)[0] = test_CURRENTROOT(boyGObj)[0];
                    ((float *)tgt)[1] = test_CURRENTROOT(boyGObj)[1];
                    ((float *)tgt)[2] = test_CURRENTROOT(boyGObj)[2];
                    ((float *)scr)[0] = ((float *)GetCurrentCameraSet2())[0];
                    ((float *)scr)[1] = ((float *)GetCurrentCameraSet2())[1];
                    ((float *)scr)[2] = ((float *)GetCurrentCameraSet2())[2];
#ifndef VERSION_AUG6
                    GetOtherStageGirlOrient((float *)ofs, (float *)scr);
#endif
                    sceVu0ScaleVector(ofs, ofs, _DistGV((float *)scr, (float *)tgt));
                    sceVu0AddVector(work, scr, ofs);
                    SetRootPosition(lo, work);
                    /* a local debug switch, off (see dbg in the declarations):
                       mark the helper position just set */
                    if (dbg) {
                        debug_NMarker((float *)work, 255, 0, 0, 100.0f);
                    }
#ifdef VERSION_AUG6
                    if ((int)(sub->flags20.ll >> 9) & 1) {
                        if ((int)(sub->flags20.ll >> 10) & 1) {
#else
                    if ((int)(sub->flags20.ll >> 12) & 1) {
                        if ((int)(sub->flags20.ll >> 13) & 1) {
#endif
                            lo = isysGObjSearchFromObjLayoutID(4);
                            if (lo != 0) {
                                ScpCallCameraGetTarget((float *)cpos);
                                SetRootPosition(lo, cpos);
                                Camctrl_SetTarget(self, lo, 1);
                            }
                        } else {
                            Camctrl_SetTarget(self, lo, 1);
                        }
                    }
                }
                boyCamDebugDisp(camOn, looking);
            }
        }
        ACTLookTargetSystem_Exec((void *)self);
        if (boyGObj != 0 && girlGObj != 0 && GOBJ_ACT(boyGObj)->actMode == 45 &&
            GOBJ_ACT(girlGObj)->actMode == GOBJ_ACT(boyGObj)->actMode) {
            if (0x3C < sitCount++) {
                if (sitLayoutDone == 0) {
                    lt_switch_layout(25);
                    sitLayoutDone = 1;
                }
            }
        } else {
            sitLayoutDone = 0;
            sitCount = 0;
        }
        if ((_ACTCharStatus_Check((void *)self, 31) || _ACTCharStatus_Check((void *)self, 32)) &&
            girlGObj != 0) {
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 57, isysCurrentGObj);
#else
            iosOmSendMail(girlGObj, 58, isysCurrentGObj);
#endif
        }
        sub->flags18.ll = (sub->flags18.ll & ~0x2000000000LL) |
                          ((unsigned long long)(ACTGame_FLAG_TETSUNAGI() & 1) << 37);
        _ACTWait(1);
    }
}
#else
void subBoyCollision(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int camOn;
#ifdef VERSION_JUN26
    int hang;
    int hangBit;
    int dbg = 0; /* local debug switch, see the test after the helper's SetRootPosition */
#else
    int looking;
    int hang;
    int hangBit;
    int hold;
    int dbg = 0; /* local debug switch, see the test after the helper's SetRootPosition */

    PrivInsCamInit();
#endif

    while ((int)sub->motReq == 0) {
        _ACTWait(1);
    }
#ifdef VERSION_JUN26
    if (200.0f < GetDifferenceFromLowerField(self, 44)) {
        ACTSendMailCorrect(self, 7);
#else
    if (200.0f < GetDifferenceFromLowerField(self, 0x2C)) {
        ACTSendMailCorrect(self, 0x7);
#endif
    }
    while (1) {
        float vec[4];

        camOn = 0;
        if (0 < GOBJ_WORK(self)->pinchFrames) {
#ifdef VERSION_JUN26
            _ACTCharStatus_Set((void *)self, 27, -1.0f, 0);
            GOBJ_WORK(self)->pinchFrames -= 1;
        }
#else
            GOBJ_WORK(self)->pinchFrames -= 1;
            _ACTCharStatus_Set((void *)self, 0x20, -1.0f, 0);
            OtherStageGirlPinchCamera_After((float)GOBJ_WORK(self)->pinchFrames);
        }
        PrivInsCamProcess();
#endif
        findChainInJump((void *)self);
        CheckCollisionAttr((void *)self);
        ACTGame_CommonLoop((void *)self);
#ifdef VERSION_JUN26
        BoyBgaManager(self, 380, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
        BoyBgaManager(self, 381, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
        BoyBgaManager(self, 385, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
        BoyBgaManager(self, 385, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
        BoyBgaManager(self, 386, (char *)GOBJ_ACT(self)->enemy + 0x2A8);

        hangBit = ((int)(sub->flags18.ll >> 44) & 1);
        hang = 1;
        if (((int)(sub->flags20.ll >> 2) & 1) == 0) {
#else

        hangBit = ((int)(sub->flags18.ll >> 50) & 1);
        hang = 1;
        if (((int)(sub->flags20.ll >> 18) & 1) == 0) {
#endif
            hang = hangBit;
        }
        if (hang == 0) {
#ifdef VERSION_JUN26
            if (0.1f < sub->stick.mag && sub->actMode != 110) {
                SetMotionDirectionSmooze(self, sub->dir,
                                         (float)motionKind[GOBJ_SUB(self)->ctrl.motion].dirFrames);
#else
            if (sub->stick.mag != 0.0f &&
                CorrectOrient_RopeCliff(vec, (void *)self, sub->dir) != 0) {
                sub->dir[0] = vec[0];
                sub->dir[1] = vec[1];
                sub->dir[2] = vec[2];
            }
            if (0.1f < sub->stick.mag && sub->actMode != 0x73) {
                SetMotionDirectionSmooze(self, sub->dir,
                                         (float)(((void *)self == girlGObj && girlControlMode != 0)
                                                     ? CHAINROW(self)->girlDirFrames
                                                     : CHAINROW(self)->dirFrames));
#endif
            }
        }
        CommonAttackCenter((void *)self);
        ACTGame_SaveActorInformation(self);
#ifdef VERSION_JUN26
        if (ACTGame_CheckItemMotion(self) == 0) {
            afterCommonItem(self);
        }
        if (*(unsigned int *)((char *)sub + 0x30) < 4 && sub->actMode != 0) {
#else
        if (*(unsigned int *)((char *)sub + 0x34) < 4 && sub->actMode != 0) {
#endif
            if (sub->pad.trg & 0x20) {
                int hit;

#ifdef VERSION_JUN26
                searchGObj((void *)self, 19, 45, &hit, vec, 100.0f);
#else
                searchGObj((void *)self, 0x13, 0x2D, &hit, vec, 100.0f);
#endif
            }
        }
        switch (sub->actMode) {
#ifdef VERSION_JUN26
        case 28:
            if (((int)(sub->wish1.ll >> 1) & 1) && ((int)(sub->wish2.ll >> 33) & 1)) {
                ACTSendMailCorrect(self, 177);
            }
            break;
        case 57:
            SaveBoyOrientForScript();
            add_rope_val = 0.0f;
            if (sub->pad.now & 0x20) {
                ACTSendMailCorrect(self, 147);
                ACTSendMailCorrect(self, 203);
            } else {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 295);
                } else if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 296);
                    if (isBottomOfChain(sub->chain)) {
                        ACTSendMailCorrect(self, 142);
                    }
                } else if (GOBJ_SUB(self)->ctrl.motion == 125) {
#else
        case 0x1C:
            if (((int)(sub->wish1.ll >> 10) & 1) && ((int)(sub->wish3.ll >> 10) & 1)) {
                ACTSendMailCorrect(self, 0xC7);
            }
            break;
        case 0x20:
        case 0x26:
            if (sub->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0x13C);
            }
            break;
        case 0x39:
            SaveBoyOrientForScript();
            add_rope_val = 0.0f;
            if (sub->pad.trg & 0x10) {
                ACTSendMailCorrect(self, 0xC3);
            }
            if (sub->pad.trg & 0x40) {
                GOBJ_WORK(self)->ropeClimbHeight = test_CURRENTROOT((void *)sub->chain)[1] +
                                                   GetChainLength((void *)sub->chain) -
                                                   test_CURRENTROOT((void *)self)[1];
                ActSendMail_WithAdditionalData((void *)self, 0x13C, (void *)self,
                                               &GOBJ_WORK(self)->ropeClimbHeight);
            }
            if (sub->pad.now & 0x20) {
                ACTSendMailCorrect(self, 0xA2);
                ACTSendMailCorrect(self, 0xE3);
            } else {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 0x14A);
                } else if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 0x14B);
                    if (isBottomOfChain(sub->chain)) {
                        ACTSendMailCorrect(self, 0x9D);
                    }
                } else if (GOBJ_SUB(self)->ctrl.motion == 0x76) {
#endif
                    float bodyori[4];
                    int cor;
                    int ry;

                    GetCorrectOrientOfChain(vec, (void *)self);
                    SetMotionDirection((void *)self, vec);
                    if (GetChainDirCorrectVal((void *)sub->chain, &cor) != 0) {
                        if (sub->stick.x - 0x80 < -100) {
#ifdef VERSION_JUN26
                            ACTSendMailCorrect(self, 145);
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ACTSendMailCorrect(self, 146);
#else
                            ACTSendMailCorrect(self, 0xA0);
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ACTSendMailCorrect(self, 0xA1);
#endif
                        }
                    } else {
                        if (sub->stick.x - 0x80 < -100) {
                            ry = 5;
                        } else {
                            ry = 0;
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ry = -5;
                        }
                        bodyori[0] = test_CURRENTORIENT((void *)self)[0];
                        bodyori[1] = test_CURRENTORIENT((void *)self)[1];
                        bodyori[2] = test_CURRENTORIENT((void *)self)[2];
                        _ApplyRyGV(bodyori, (float)ry * 3.1415927f / 180.0f);
                        SetMotionDirection((void *)self, bodyori);
                    }
                }
#ifdef VERSION_JUN26
                ACTSendMailCorrect(self, 301);
            }
            break;
        case 66:
            if (((int)(sub->flags18.ll >> 63) & 1) == 0) {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 295);
                }
                if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 296);
                }
            }
            if (GOBJ_SUB(self)->ctrl.motion == 125) {
                int ry;

                if (sub->stick.x - 0x80 < -100) {
                    ry = 5;
                } else {
                    ry = 0;
                }
                if (100 < sub->stick.x - 0x80) {
                    ry = -5;
                }
                vec[0] = test_CURRENTORIENT((void *)self)[0];
                vec[1] = test_CURRENTORIENT((void *)self)[1];
                vec[2] = test_CURRENTORIENT((void *)self)[2];
                _ApplyRyGV(vec, (float)ry * 3.1415927f / 180.0f);
                SetMotionDirection((void *)self, vec);
            }
            ACTSendMailCorrect(self, 301);
            break;
        /* an empty arm: without a seventh label gcc writes a compare tree, and
           the demo has a 67-slot table from 1; an empty arm's slot holds the
           switch exit like every default slot, so the table does not show its
           value (38 and 39 give the same object): 38 is the USA's label */
        case 38:
            break;
        case 55:
        case 67:
            if (((int)(sub->wish0.ll >> 45) & 1) && ((int)(sub->wish2.ll >> 13) & 1)) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 57, isysCurrentGObj);
                }
                ACTSendMailCorrect(self, 226);
            } else if (NotNeedBackHand() ||
                       (GOBJ_ACT(girlGObj)->intrMot != 81 && GOBJ_ACT(girlGObj)->intrMot != 88 &&
                        (60 - systemStatus[0] * 10) / systemStatus[1] * 2 < sub->modeFrame)) {
                if (((int)(sub->wish0.ll >> 46) & 1) && ((int)(sub->wish2.ll >> 14) & 1)) {
                    ACTSendMailCorrect(self, 226);
                } else {
                    ACTSendMailCorrect(self, 225);
#else
                ACTSendMailCorrect(self, 0x150);
            }
            break;
        case 0x42:
            if (((int)(sub->flags20.ll >> 11) & 1) == 0) {
                if (sub->stick.y - 0x80 < -100) {
                    ACTSendMailCorrect(self, 0x14A);
                }
                if (100 < sub->stick.y - 0x80) {
                    ACTSendMailCorrect(self, 0x14B);
                }
            }
            if (GOBJ_SUB(self)->ctrl.motion == 0x76) {
                if (sub->stick.x - 0x80 < -100) {
                    ACTSendMailCorrect(self, 0xA0);
                }
                if (100 < sub->stick.x - 0x80) {
                    ACTSendMailCorrect(self, 0xA1);
                }
            }
            ACTSendMailCorrect(self, 0x150);
            if (sub->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 0x13C);
            }
            break;
        case 0x37:
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->curMot != 0x5E &&
                GOBJ_ACT(girlGObj)->curMot != 0x65 &&
                (60 - systemStatus[0] * 10) / systemStatus[1] < sub->modeFrame) {
                if (((int)(sub->wish0.ll >> 49) & 1) == 0 ||
                    ((int)(sub->wish2.ll >> 49) & 1) == 0) {
                    ACTSendMailCorrect(self, 0xF9);
                } else {
                    ACTSendMailCorrect(self, 0xFA);
                }
            }
            /* falls through into the next arm */
        case 0x44:
            if (((int)(sub->wish0.ll >> 48) & 1) && ((int)(sub->wish2.ll >> 48) & 1)) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x3E, isysCurrentGObj);
                }
                ACTSendMailCorrect(self, 0xFA);
            } else if (NotNeedBackHand() ||
                       (GOBJ_ACT(girlGObj)->intrMot != 0x5E &&
                        GOBJ_ACT(girlGObj)->intrMot != 0x65 &&
                        (60 - systemStatus[0] * 10) / systemStatus[1] * 2 < sub->modeFrame)) {
                if (((int)(sub->wish0.ll >> 49) & 1) && ((int)(sub->wish2.ll >> 49) & 1)) {
                    ACTSendMailCorrect(self, 0xFA);
                } else {
                    ACTSendMailCorrect(self, 0xF9);
#endif
                }
            }
            break;
            /* the table runs from 1, with this arm empty */
#ifdef VERSION_JUN26
        case 1:
#else
        case 0x1:
#endif
            break;
        }
        {
#ifdef VERSION_JUN26
            float front[4];
            int work[4];
            int scr[4];
            int tgt[4];
            int ofs[4];

            if (((int)(sub->wish0.ll >> 44) & 1) == 0 || ((int)(sub->wish2.ll >> 12) & 1) == 0) {
#else
            int tgt2[4];
            int scr2[4];
            int work[4];
            int cam[4];
            int broot[4];
            int ofs[4];
            int cpos[4];

            looking = 0;
            if (((int)(sub->wish0.ll >> 46) & 1) == 0 || ((int)(sub->wish2.ll >> 46) & 1) == 0) {
#endif
                girlLookStarted = 0;
                girlLookInScreen = 0;
            }
#ifdef VERSION_JUN26
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 68) {
                sceVu0ScaleVector(front, test_CURRENTORIENT((void *)self), 200.0f);
                front[1] = 0.0f;
                sceVu0AddVector(front, test_CURRENTROOT((void *)self), front);
                _ACTLookTarget_Set((void *)self, 0, front, 1, 1);
            }
            if (((int)(sub->wish0.ll >> 44) & 1) && ((int)(sub->wish2.ll >> 12) & 1)) {
#else
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 0x45) {
                sceVu0ScaleVector(vec, test_CURRENTORIENT((void *)self), 200.0f);
                vec[1] = 0.0f;
                sceVu0AddVector(vec, test_CURRENTROOT((void *)self), vec);
                _ACTLookTarget_Set((void *)self, 0, vec, 1, 1);
            }
            if (((int)(sub->wish0.ll >> 46) & 1) && ((int)(sub->wish2.ll >> 46) & 1)) {
                int see = 0;
                int onGirl = 0;

#endif
                if (girlLookStarted == 0) {
                    girlLookStarted = 1;
                    if (girlGObj != 0) {
#ifdef VERSION_JUN26
                        girlLookInScreen =
                            (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(girlGObj))) ? 1 : 0;
#else
                        girlLookInScreen =
                            (0.0f < IsPointIsInScreen(scr2, test_CURRENTROOT(girlGObj))) ? 1 : 0;
#endif
                    }
                }
                if (girlGObj != 0) {
#ifdef VERSION_JUN26
                    float d = _DistGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));

                    if (d < _ACTGame_GetParamF(2)) {
                        _ACTParaStatus_Set((void *)self, 24);
                        _ACTCharStatus_Set((void *)self, 28, -1.0f, 0);
                    } else if (d < _ACTGame_GetParamF(3)) {
                        _ACTParaStatus_Set((void *)self, 23);
                        _ACTCharStatus_Set((void *)self, 30, -1.0f, 0);
                    } else {
                        _ACTParaStatus_Set((void *)self, 22);
                        _ACTCharStatus_Set((void *)self, 29, -1.0f, 0);
                    }
                } else {
                    _ACTParaStatus_Set((void *)self, 22);
                    _ACTCharStatus_Set((void *)self, 29, -1.0f, 0);
                }
                if (girlGObj != 0) {
                    _ACTLookTarget_Set((void *)self, girlGObj, 0, 4, 2);
                    if (girlLookInScreen == 0) {
#else
                    ((float *)tgt2)[0] = test_CURRENTROOT(girlGObj)[0];
                    ((float *)tgt2)[1] = test_CURRENTROOT(girlGObj)[1];
                    ((float *)tgt2)[2] = test_CURRENTROOT(girlGObj)[2];
                    see = 1;
                    onGirl = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                } else if ((stage_no == 84 || stage_no == 3 || stage_no == 46) &&
                           ((int)(sub->flags20.ll >> 24) & 3)) {
#else
                } else if ((stage_no == 0x56 || stage_no == 0x3 || stage_no == 0x2E) &&
                           ((int)(sub->flags20.ll >> 24) & 3)) {
#endif
                    see = 1;
                    onGirl = 0;
                    ScpCallCameraGetTarget((float *)tgt2);
                }
                if (see) {
                    float d = _DistGV(test_CURRENTROOT((void *)self), (float *)tgt2);

                    if (d < _ACTGame_GetParamF(3) && onGirl) {
                        _ACTParaStatus_Set((void *)self, 0x15);
                        _ACTCharStatus_Set((void *)self, 0x21, -1.0f, 0);
                    } else if (d < _ACTGame_GetParamF(4)) {
                        _ACTParaStatus_Set((void *)self, 0x14);
                        _ACTCharStatus_Set((void *)self, 0x23, -1.0f, 0);
                        _ACTParaStatus_Set((void *)self, 0x13);
                        _ACTCharStatus_Set((void *)self, 0x22, -1.0f, 0);
                    } else {
                        _ACTParaStatus_Set((void *)self, 0x13);
                        _ACTCharStatus_Set((void *)self, 0x22, -1.0f, 0);
                    }
                } else {
                    _ACTParaStatus_Set((void *)self, 0x13);
                    _ACTCharStatus_Set((void *)self, 0x22, -1.0f, 0);
                }
                hold = sub->pad.now & 0x8;
                looking = hold != 0;
            }
            if (girlGObj != 0 && (looking || ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 26) & 1))) {
                _ACTLookTarget_Set((void *)self, girlGObj, 0, 4, 2);
                if (girlLookInScreen == 0 && ((int)(sub->flags20.ll >> 23) & 1)) {
                    if (((int)(sub->flags20.ll >> 24) & 3) != 0) {
                        void *lo = isysGObjSearchFromObjLayoutID(0x4);

                        if (lo != 0) {
                            ScpCallCameraGetTarget((float *)work);
                            SetRootPosition(lo, work);
                            Camctrl_SetTarget(self, lo, 1);
                        }
                    } else {
#endif
                        Camctrl_SetTarget(self, girlGObj, 1);
                    }
                }
            }
            {
                int i;
                float near = 3.40282347e+38f; /* FLT_MAX */

                *(ObjKindList *)work = collisionKinds;
                for (i = 0; work[i] != -1; i++) {
                    void *g;

                    for (g = isysGObjSearchFromObjKindID_begin(work[i]); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
                        if ((int)(GOBJ_ACT(g)->flags18.ll >> 32) & 1) {
                            float d = _DistGV(test_CURRENTROOT((void *)self), test_CURRENTROOT(g));

#ifndef VERSION_JUN26
                            if (work[i] == 47) {
                                if (*(int *)((char *)g + 0x16C) == 0) {
                                    continue;
                                }
                                d = 1.0f;
                            }
#endif
                            if (d < near) {
                                near = d;
                            }
                        }
                    }
                }
                if (ACTGame_NoWeapon((void *)self) == 0) {
                    if (near < 1000.0f) {
#ifdef VERSION_JUN26
                        _ACTParaStatus_Set((void *)self, 2);
                    }
                    if (near < 300.0f) {
                        _ACTParaStatus_Set((void *)self, 3);
#else
                        _ACTParaStatus_Set((void *)self, 0x2);
                    }
                    if (near < 300.0f) {
                        _ACTParaStatus_Set((void *)self, 0x3);
#endif
                    }
                }
                if (near < 1000.0f) {
#ifdef VERSION_JUN26
                    _ACTCharStatus_Set((void *)self, 13, near, 0);
                }
            }
            if (_ACTParaStatus_Check((void *)self, 3) || _ACTParaStatus_Check((void *)self, 2)) {
                if (_ACTParaStatus_Check((void *)self, 23)) {
                    _ACTParaStatus_Set((void *)self, 26);
                }
                if (_ACTParaStatus_Check((void *)self, 22)) {
                    _ACTParaStatus_Set((void *)self, 25);
#else
                    _ACTCharStatus_Set((void *)self, 0x11, near, 0);
                }
            }
            if (_ACTParaStatus_Check((void *)self, 0x3) ||
                _ACTParaStatus_Check((void *)self, 0x2)) {
                if (_ACTParaStatus_Check((void *)self, 0x14)) {
                    _ACTParaStatus_Set((void *)self, 0x17);
                }
                if (_ACTParaStatus_Check((void *)self, 0x13)) {
                    _ACTParaStatus_Set((void *)self, 0x16);
#endif
                }
            }
            if (ACTGame_NoWeapon((void *)self)) {
#ifdef VERSION_JUN26
                _ACTParaStatus_Set((void *)self, 4);
#else
                _ACTParaStatus_Set((void *)self, 0x4);
#endif
            }
            ACTParaStatus_Exec((void *)self);
            {
                /* the weapon search, defined here and inlined into the test
                   below */
                inline void *searchWeapon(void) /* derived name */
                {
                    void *g;

#ifdef VERSION_JUN26
                    for (g = isysGObjSearchFromObjKindID_begin(14); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
#else
                    for (g = isysGObjSearchFromObjKindID_begin(0xE); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
#endif
                        if (CheckWeaponKind(g) == 5) {
                            return g;
                        }
                    }
                    return 0;
                }
                void *w;

                if (girlGObj == 0 && (w = searchWeapon()) != 0) {
                    if ((sub->pad.now & 0x8) == 0) {
                        weaponLookInScreen = 0;
                        weaponLookStarted = 0;
                    } else {
#ifndef VERSION_JUN26
                        int mode;
                        int ok;
#endif

                        if (weaponLookStarted == 0) {
                            weaponLookInScreen =
                                (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(w))) ? 1 : 0;
                        }
                        weaponLookStarted = 1;
#ifdef VERSION_JUN26
                        Camctrl_SetTarget(self, w, 1);
                        camOn = 1;
#else
                        mode = (int)(sub->flags20.ll >> 24) & 3;
                        ok = mode == 0;
                        if (stage_no == 0x25 && mode == 2) {
                            ok = 1;
                        }
                        if (((int)(sub->flags20.ll >> 23) & 1) && ok) {
                            Camctrl_SetTarget(self, w, 1);
                            camOn = 1;
                            if (stage_no == 0x25) {
                                ((float *)cam)[0] = test_CURRENTROOT(w)[0];
                                ((float *)cam)[1] = test_CURRENTROOT(w)[1];
                                ((float *)cam)[2] = test_CURRENTROOT(w)[2];
                                ScpCallCameraSetTarget(-((float *)cam)[0], -((float *)cam)[1],
                                                       -((float *)cam)[2]);
                                sub->flags20.ll = (sub->flags20.ll & ~0x3000000) | 0x2000000;
                            }
                        }
#endif
                    }
                }
            }
            if (camOn == 0 && girlGObj == 0) {
#ifdef VERSION_JUN26
                void *lo = isysGObjSearchFromObjLayoutID(4);

                if ((sub->pad.now & 0x8) && lo != 0) {
                    GetOtherStageGirlOrient((float *)ofs);
                    ((float *)tgt)[0] = test_CURRENTROOT(boyGObj)[0];
                    ((float *)tgt)[1] = test_CURRENTROOT(boyGObj)[1];
                    ((float *)tgt)[2] = test_CURRENTROOT(boyGObj)[2];
                    ((float *)scr)[0] = ((float *)GetCurrentCameraSet2())[0];
                    ((float *)scr)[1] = ((float *)GetCurrentCameraSet2())[1];
                    ((float *)scr)[2] = ((float *)GetCurrentCameraSet2())[2];
                    sceVu0ScaleVector(ofs, ofs, _DistGV((float *)scr, (float *)tgt));
                    sceVu0AddVector(work, scr, ofs);
#else
                void *lo = isysGObjSearchFromObjLayoutID(0x4);

                /* In retail camOn and looking are dead from here on; the DEBUG
                   build's camera report at the end of this block reads
                   them. */
                if (lo == 0) {
                    camOn = 1;
                    looking = 0;
                }
                if ((sub->pad.now & 0x8) && lo != 0) {
                    ((float *)broot)[0] = test_CURRENTROOT(boyGObj)[0];
                    ((float *)broot)[1] = test_CURRENTROOT(boyGObj)[1];
                    ((float *)broot)[2] = test_CURRENTROOT(boyGObj)[2];
                    ((float *)cam)[0] = ((float *)GetCurrentCameraSet2())[0];
                    ((float *)cam)[1] = ((float *)GetCurrentCameraSet2())[1];
                    ((float *)cam)[2] = ((float *)GetCurrentCameraSet2())[2];
                    GetOtherStageGirlOrient((float *)ofs, (float *)cam);
                    sceVu0ScaleVector(ofs, ofs, _DistGV((float *)cam, (float *)broot));
                    sceVu0AddVector(work, cam, ofs);
#endif
                    SetRootPosition(lo, work);
                    /* a local debug switch, off (see dbg in the declarations): mark
                       the helper position just set */
                    if (dbg) {
#ifdef VERSION_JUN26
                        debug_NMarker((float *)work, 255, 0, 0, 100.0f);
                    }
                    Camctrl_SetTarget(self, lo, 1);
#else
                        debug_NMarker((float *)work, 0xFF, 0, 0, 100.0f);
                    }
                    if ((int)(sub->flags20.ll >> 23) & 1) {
                        if (((int)(sub->flags20.ll >> 24) & 3) != 0) {
                            lo = isysGObjSearchFromObjLayoutID(0x4);
                            if (lo != 0) {
                                ScpCallCameraGetTarget((float *)cpos);
                                SetRootPosition(lo, cpos);
                                Camctrl_SetTarget(self, lo, 1);
                            }
                        } else {
                            Camctrl_SetTarget(self, lo, 1);
                        }
                    }
                }
                boyCamDebugDisp(camOn, looking);
            }
            ACTLookTargetSystem_Exec((void *)self);
            if (boyGObj != 0 && girlGObj != 0 && GOBJ_ACT(boyGObj)->actMode == 0x2D &&
                GOBJ_ACT(girlGObj)->actMode == GOBJ_ACT(boyGObj)->actMode) {
                if (0x3C < sitCount++) {
                    if (sitLayoutDone == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
                        lt_switch_layout(25);
#else
                        lt_switch_layout(0x1C);
#endif
                        sitLayoutDone = 1;
                    }
                }
            } else {
                sitLayoutDone = 0;
                sitCount = 0;
            }
            if ((_ACTCharStatus_Check((void *)self, 0x22) ||
                 _ACTCharStatus_Check((void *)self, 0x23)) &&
                girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x3D, isysCurrentGObj);
            }
            sub->flags18.ll = (sub->flags18.ll & ~0x20000000000LL) |
                              ((unsigned long long)(ACTGame_FLAG_TETSUNAGI() & 1) << 41);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
            if (((CHAINROW(self)->flags.word >> 19) & 1) && ACTGame_FLAG_TETSUNAGI() == 0) {
#else
            if (((CHAINROW(self)->flags.word >> 13) & 1) && ACTGame_FLAG_TETSUNAGI() == 0) {
#endif
                ACTSendMailCorrect(self, 0x1AA);
            }
            if ((int)(sub->flags18.ll >> 38) & 1) {
                int life = GOBJ_WORK(self)->bit38Frames;

                if (life < 60) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 0xB4, isysCurrentGObj);
                    }
                } else if (life < 70) {
                    brainAddLevelGirl(20.0f);
                } else {
                    brainAddLevelGirl(10.0f);
#endif
                }
            }
        }
#ifdef VERSION_JUN26
        ACTLookTargetSystem_Exec((void *)self);
        if (boyGObj != 0 && girlGObj != 0 && GOBJ_ACT(boyGObj)->actMode == 45 &&
            GOBJ_ACT(girlGObj)->actMode == GOBJ_ACT(boyGObj)->actMode) {
            if (60 < sitCount++) {
                if (sitLayoutDone == 0) {
                    lt_switch_layout(25);
                    sitLayoutDone = 1;
                }
            }
        } else {
            sitLayoutDone = 0;
            sitCount = 0;
        }
        if ((_ACTCharStatus_Check((void *)self, 29) || _ACTCharStatus_Check((void *)self, 30)) &&
            girlGObj != 0) {
            iosOmSendMail(girlGObj, 56, isysCurrentGObj);
        }
        sub->flags18.ll = (sub->flags18.ll & ~0x1000000000LL) |
                          ((unsigned long long)(ACTGame_FLAG_TETSUNAGI() & 1) << 36);
#endif
        _ACTWait(1);
    }
}
#endif

inline void afterBoySwim(GObj *volatile self);

/* the record Act+0x680 points at, with the fields actBoyBelift and actBoySwim
   touch: the lift level and the lifted object, then the floating-box flag, the
   box GObj and the grip point, a four-float vector sceVu0ApplyMatrix takes
   whole (its w set to 1 before the apply) */
typedef struct { /* field names derived */
    char pad0[204];
    int liftLevel; /* 0xCC, the lift level actBoyBelift sets to 10 and clamps */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    char padD0[340];
    void *liftObj; /* 0x224, the object the boy lifts (actBoyBelift stores the girl) */
    char pad228[152];
#else
    char padD0[348];
    void *liftObj; /* 0x22C, the object the boy lifts (actBoyBelift stores the girl) */
    char pad230[144];
#endif
    int holdBox; /* 0x2C0, set while the boy holds a floating box */
    GObj *box;   /* 0x2C4 */
    char pad2C8[8];
    float grip[4]; /* 0x2D0 */
} BoyExt;          /* derived name */

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x670)) /* derived name */
#else
#ifdef VERSION_JUN26
#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x650)) /* derived name */
#else
#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x680)) /* derived name */
#endif
#endif

/* GObj's 0x15C slot read through a union (typedef.h: an int handle the
   engine casts to a pointer) */
typedef union { /* field names derived */
    char *sub;
} GObjSubSlot; /* derived name */

#define GOBJ_SUBSLOT(o) (((GObjSubSlot *)((char *)(o) + 0x15C))->sub) /* derived name */

void actBoySwim(GObj *volatile self)
{
    float pos[4];
    Act *sub = GOBJ_ACT(self);
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    int padReq = 0;
#endif

    BOY_EXT(self)->holdBox = 0;
    sub->after = (void *)afterBoySwim;
    while (1) {
        GObj *box = BOY_EXT(self)->box;

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        if (sub->curMot == 0xAD) {
            sub->flags20.ll |= 0x800000000ULL;
        }
#endif
        if (BOY_EXT(self)->holdBox) {
            RequestChangeHandMode(self, 0, 3, 1, box, 0, BOY_EXT(self)->grip);
            BOY_EXT(self)->grip[3] = 1.0f;
            sceVu0ApplyMatrix(pos, *(void **)(GOBJ_SUBSLOT(box) + 0xC), BOY_EXT(self)->grip);
            debug_NMarker(pos, 0xFF, 0, 0, 100.0f);
            MoveFloatingBox(box, self,
                            (float *)(*(char **)(GOBJ_SUBSLOT(self) + 0xC) +
                                      GetSkeltonFocusNode(self, 0x13) * 0x40 + 0x30),
                            BOY_EXT(self)->grip, 30.0f);
            if (!(_DistSqGV(test_CURRENTROOT((void *)self), pos) < 4e+04f)) {
                BOY_EXT(self)->holdBox = 0;
            }
#ifdef VERSION_JUN26
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->a = (int)box;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->b = -1;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->c = 0;
        } else {
            RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
            ((Sub15C *)GOBJ_SUBSLOT(self))->root.filter = InitialColInfo;
        }
        _ACTWait(1);
    }
}

inline void actBoyStand(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyStand\n");
    sub->actMode = 1;
    while (1) {
#else
#ifdef VERSION_AUG6
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->a = (int)box;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->b = -1;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1B0))->c = 0;
        } else {
            RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
#else
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->a = (int)box;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->b = -1;
            ((S12 *)(GOBJ_SUBSLOT(self) + 0x1C0))->c = 0;
#ifdef VERSION_NTSC
        } else {
            RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
#else
            if (!padReq) {
                iosPadActRequest(boyPad, 6);
                padReq = 1;
            }
            if ((int)(sub->flags20.ll >> 35) & 1) {
                if (*(int *)(GOBJ_SUBSLOT(self) + 0x4CC) || *(int *)(GOBJ_SUBSLOT(self) + 0x4C8)) {
                    iosPadActRequest(boyPad, 7);
                }
            }
        } else {
            RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
            padReq = 0;
#endif
#endif
            ((Sub15C *)GOBJ_SUBSLOT(self))->root.filter = InitialColInfo;
        }
#endif
        _ACTWait(1);
    }
}

void actBoyWalk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, boyGObj, 2);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            GetSkeltonPosition(gp, girlGObj, 18);
#else
            GetSkeltonPosition(gp, girlGObj, 0x12);
#endif
            d = _DistGV((float *)gp, (float *)bp);
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 < sub->modeFrame &&
                80.0f < d) {
                d = (d - 80.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.9 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

void actBoyRun(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, boyGObj, 2);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            GetSkeltonPosition(gp, girlGObj, 18);
#else
            GetSkeltonPosition(gp, girlGObj, 0x12);
#endif
            d = _DistGV((float *)gp, (float *)bp);
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 < sub->modeFrame &&
                90.0f < d) {
                d = (d - 90.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.7 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)self, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
/* the nearest enemy in front of the actor, which ACTSearchEnemy and
   actBoyAttack inline */
static inline void searchEnemy(void *self, int *out_id, float *out_vec) /* derived name */
{
    searchGObj(self, (*(int *)((char *)self + 0xC) ^ 1) ? 1 : 4, 0x5A, out_id, out_vec, 300.0f);
}
#endif

inline void actBoyFall(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyFall\n");
    sub->actMode = 5;
    while (1) {
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
void actBoyAttack(GObj *volatile self)
{
    char *sub = (char *)GOBJ_ACT(self);
    int mot = *(int *)((char *)sub + 0x10);
    float vec[4];

    *(unsigned long long *)(sub + 0x20) |= 0x80000;
    *(int *)((char *)sub + 0x440) = mot;
    debug_StdPrintfDummy("attack sub id [%d]\n", mot);
    debug_StdPrintfDummy("enter actBoyAttack\n");
    _ACTWait(2);
    searchEnemy((void *)self, (int *)((char *)sub + 0x178), vec);
    while (1) {
        if (*(int *)((char *)sub + 0x178)) {
            if (ACTGame_NoWeapon(self)) {
                SetMotionDirectionWithLimit((void *)self, vec, 5.0f, 45.0f);
            } else {
                SetMotionDirectionWithLimit((void *)self, vec, 10.0f, 90.0f);
            }
        }
        ACTSendMailCorrect(self, 183);
        BoyAttackCenter(self);
        _ACTWait(1);
    }
}
#else
/* the nearest enemy in front of the actor, which ACTSearchEnemy and
   actBoyAttack inline */
static inline void searchEnemy(void *self, int *out_id, float *out_vec) /* derived name */
{
    searchGObj(self, (*(int *)((char *)self + 0xC) ^ 1) ? 1 : 4, 0x5A, out_id, out_vec, 300.0f);
}

void actBoyAttack(GObj *volatile self)
{
    char *sub = (char *)GOBJ_ACT(self);
    int mot = *(int *)((char *)sub + 0x10);
    float vec[4];

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    *(int *)((char *)sub + 0x440) = mot;
#else
    *(unsigned long long *)(sub + 0x20) |= 0x100000000ULL;
    *(int *)((char *)sub + 0x450) = mot;
#endif
    debug_StdPrintfDummy("attack sub id [%d]\n", mot);
    debug_StdPrintfDummy("enter actBoyAttack\n");
    _ACTWait(2);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    searchEnemy((void *)self, (int *)((char *)sub + 0x168), vec);
    while (1) {
        if (*(int *)((char *)sub + 0x168)) {
#else
    searchEnemy((void *)self, (int *)((char *)sub + 0x188), vec);
    while (1) {
        if (*(int *)((char *)sub + 0x188)) {
#endif
            if (ACTGame_NoWeapon(self)) {
                SetMotionDirectionWithLimit((void *)self, vec, 5.0f, 45.0f);
            } else {
                SetMotionDirectionWithLimit((void *)self, vec, 10.0f, 90.0f);
            }
        }
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 180);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 177);
#else
        ACTSendMailCorrect(self, 0xC7);
#endif
#endif
        BoyAttackCenter(self);
        _ACTWait(1);
    }
}
#endif

void actBoyTakeWeaponReady(GObj *volatile self)
{
    float w[4];
    float p[4];
    float dir[4];
    GObj *obj;
    int first = 1;
    int n = 0;

    obj = GOBJ_ACT(self)->env.swapWeapon;
    w[0] = test_CURRENTROOT(obj)[0];
    w[1] = test_CURRENTROOT(obj)[1];
    w[2] = test_CURRENTROOT(obj)[2];
    while (1) {
        p[0] = test_CURRENTROOT((void *)self)[0];
        p[1] = test_CURRENTROOT((void *)self)[1];
        p[2] = test_CURRENTROOT((void *)self)[2];
        _OrientXZGV(dir, w, p);
        if (first) {
            SetMotionDirection((void *)self, dir);
            first = 0;
        } else if (_AbsRotyGV(test_CURRENTORIENT((void *)self), dir) < 0x1E) {
            _ACTMotDirSmzDirect((void *)self, dir);
        } else {
#ifdef VERSION_NTSC
            ACTSendMailCorrect(self, 188);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 188);
#else
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 185);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 185);
#else
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 182);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 182);
#else
            ACTSendMailCorrect(self, 0xCC);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 0xCC);
#endif
#endif
#endif
        }
        _ACTWait(1);
    }
}

/* sub->0x14 is the actor's "after" callback slot: actBoyTakeWeapon arms it with
   afterBoyTakeWeapon and calls it through the slot once the motion frame passes
   the swap point, so it is written and read as a function pointer. */
typedef void (*BoyAfterFunc)(GObj *volatile a0);

#ifdef VERSION_NTSC
void actBoyTakeWeapon(GObj *volatile self)
{
    float p[4];
    float dir[4];
    Act *sub = GOBJ_ACT(self);
    int picked = 0;
    int put = 0;

    InitSwapWeapon((void *)self);
    *(BoyAfterFunc *)((char *)sub + 0x14) = afterBoyTakeWeapon;
    p[0] = test_CURRENTROOT(BOYINFO.nextWeapon)[0];
    p[1] = test_CURRENTROOT(BOYINFO.nextWeapon)[1];
    p[2] = test_CURRENTROOT(BOYINFO.nextWeapon)[2];
    _OrientXZGV(dir, p, test_CURRENTROOT((void *)self));
    SetMotionDirection((void *)self, dir);
    while (1) {
        if (GOBJ_SUB(self)->ctrl.motion == 226) {
            if (15.0f < GOBJ_SUB(self)->ctrl.animFrame && GOBJ_SUB(self)->ctrl.animFrame < 48.0f &&
                !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)self, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(self)->ctrl.animFrame && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
                    ExecuteSEPackage(BOYINFO.weapon, 76);
                }
                PutWeapon();
                put = 1;
            }
            if (48.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        } else {
            if (16.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        }
        ACTSendMailCorrect(self, 183);
        _ACTWait(1);
    }
}

static int pullup_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, s->env.cliffOrient) &&
        _DistxzGV(s->env.cliffStepPos, test_CURRENTROOT(girlGObj)) < 100.0f &&
        ((unsigned int)(GOBJ_ACT(girlGObj)->flags18.ll >> 49) & 1) &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 450.0f))) {
        return 1;
    }
    return 0;
}

#define BOY_WALL(o) ((char *)GOBJ_ACT(o)->work) /* derived name */
#define BOY_GIRL_DY()                                                                              \
    (test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1]) /* derived name */

inline void actBoyCliffHesitate(GObj *volatile self)
{
    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.b.wall);
    GetOrientOfWall(BOY_WALL(self) + 0x800, GOBJ_WORK(self)->intrReq.b.wall.elem,
                    &GOBJ_WORK(self)->intrReq.b.wall.o);
    while (1) {
        if (girlGObj != 0) {
            brainSetSpMode();
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 58, isysCurrentGObj);
            }
        }
        ACTSendMailCorrect(self, 279);
        _ACTWait(1);
    }
}

/* the pull-up go mail, inlined into actBoyPullupReady */
static inline void ACTSendMail_PULLUP_GO(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);

    switch (sub->env.cliffSel) {
    case 100:
        ACTSendMailCorrect(g, 70);
        sub->orientMot = 97;
        break;
    case 200:
        ACTSendMailCorrect(g, 70);
        sub->orientMot = 99;
        break;
    case 300:
        ACTSendMailCorrect(g, 70);
        sub->orientMot = 101;
        break;
    }
}

/* the pull-up start mail, inlined into actBoyPullupGo */
static inline void ACTSendMail_PULLUP_START(void) /* derived name */
{
    Act *sub = GOBJ_ACT(boyGObj);

    switch (sub->env.cliffSel) {
    case 100:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 77, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 92;
        break;
    case 200:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 77, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 93;
        break;
    case 300:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 77, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 94;
        break;
    }
}
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
void actBoyTakeWeapon(GObj *volatile self)
{
    float p[4];
    float dir[4];
    Act *sub = GOBJ_ACT(self);
    int picked = 0;
    int put = 0;

    InitSwapWeapon((void *)self);
    *(BoyAfterFunc *)((char *)sub + 0x14) = afterBoyTakeWeapon;
    p[0] = test_CURRENTROOT(BOYINFO.nextWeapon)[0];
    p[1] = test_CURRENTROOT(BOYINFO.nextWeapon)[1];
    p[2] = test_CURRENTROOT(BOYINFO.nextWeapon)[2];
    _OrientXZGV(dir, p, test_CURRENTROOT((void *)self));
    SetMotionDirection((void *)self, dir);
    while (1) {
#ifdef VERSION_JUN26
        if (GOBJ_SUB(self)->ctrl.motion == 236) {
#else
        if (GOBJ_SUB(self)->ctrl.motion == 226) {
#endif
            if (15.0f < GOBJ_SUB(self)->ctrl.animFrame && GOBJ_SUB(self)->ctrl.animFrame < 48.0f &&
                !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)self, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(self)->ctrl.animFrame && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
#ifdef VERSION_JUN26
                    ExecuteSEPackage(BOYINFO.weapon, 68);
#else
                    ExecuteSEPackage(BOYINFO.weapon, 76);
#endif
                }
                PutWeapon();
                put = 1;
            }
            if (48.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        } else {
            if (16.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        }
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 177);
#else
        ACTSendMailCorrect(self, 180);
#endif
        _ACTWait(1);
    }
}

#ifdef VERSION_JUN26
/* the girl is in place for the pull-up: on the cliff's side, near its step
   and in the climb status (flags18 bit 47); inlined at the pull-up test */
static inline unsigned char pullup_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, s->env.cliffOrient) &&
        _DistxzGV(s->env.cliffStepPos, test_CURRENTROOT(girlGObj)) < 100.0f &&
        ((unsigned int)(GOBJ_ACT(girlGObj)->flags18.ll >> 47) & 1)) {
        return 1;
    }
    return 0;
}
#else
#define BOY_WALL(o) ((char *)GOBJ_ACT(o)->work) /* derived name */
#define BOY_GIRL_DY()                                                                              \
    (test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1]) /* derived name */

inline void actBoyCliffHesitate(GObj *volatile self)
{
    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.b.wall);
    GetOrientOfWall(BOY_WALL(self) + 0x7E0, GOBJ_WORK(self)->intrReq.b.wall.elem,
                    &GOBJ_WORK(self)->intrReq.b.wall.o);
    while (1) {
        if (girlGObj != 0) {
            brainSetSpMode();
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 57, isysCurrentGObj);
            }
        }
        ACTSendMailCorrect(self, 276);
        _ACTWait(1);
    }
}
#endif
#else
void actBoyTakeWeapon(GObj *volatile self)
{
    float p[4];
    float dir[4];
    Act *sub = GOBJ_ACT(self);
    int picked = 0;
    int put = 0;

    InitSwapWeapon((void *)self);
    *(BoyAfterFunc *)((char *)sub + 0x14) = afterBoyTakeWeapon;
    p[0] = test_CURRENTROOT(BOYINFO.nextWeapon)[0];
    p[1] = test_CURRENTROOT(BOYINFO.nextWeapon)[1];
    p[2] = test_CURRENTROOT(BOYINFO.nextWeapon)[2];
    _OrientXZGV(dir, p, test_CURRENTROOT((void *)self));
    SetMotionDirection((void *)self, dir);
    while (1) {
        if (GOBJ_SUB(self)->ctrl.motion == 0xE6) {
            if (15.0f < GOBJ_SUB(self)->ctrl.animFrame && GOBJ_SUB(self)->ctrl.animFrame < 48.0f &&
                !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)self, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(self)->ctrl.animFrame && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
                    ExecuteSEPackage(BOYINFO.weapon, 0x50);
                }
                PutWeapon();
                put = 1;
            }
            if (48.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        } else {
            if (16.0f < GOBJ_SUB(self)->ctrl.animFrame) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(self);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        }
        ACTSendMailCorrect(self, 0xC7);
        _ACTWait(1);
    }
}

#define BOY_WALL(o) ((char *)GOBJ_ACT(o)->work) /* derived name */

void actBoyCliffHesitate(GObj *volatile self)
{
    int hit = 0;

    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.b.wall);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    GetOrientOfWall(BOY_WALL(self) + 0x8C0, GOBJ_WORK(self)->intrReq.b.wall.elem,
                    &GOBJ_WORK(self)->intrReq.b.wall.o);
#else
    GetOrientOfWall(BOY_WALL(self) + 0x8D0, GOBJ_WORK(self)->intrReq.b.wall.elem,
                    &GOBJ_WORK(self)->intrReq.b.wall.o);
#endif
    if (CompareAttribute(((FcWallEnt *)GOBJ_WORK(self)->intrReq.b.wall.elem)->attr, 0x400)) {
        hit = 1;
        GOBJ_WORK(self)->cliffReq.b = GOBJ_WORK(self)->intrReq.b;
    }
    while (1) {
        if (hit) {
            ACTSendMailCorrect(self, 0x8C);
        }
        if (girlGObj != 0) {
            brainSetSpMode();
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x3D, isysCurrentGObj);
            }
        }
        ACTSendMailCorrect(self, 0x128);
        _ACTWait(1);
    }
}
#endif
#endif

#ifdef VERSION_JUN26
/* the pull-up go mail, inlined into actBoyPullupReady */
static inline void ACTSendMail_PULLUP_GO(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);

    switch (sub->env.cliffSel) {
    case 100:
        ACTSendMailCorrect(g, 68);
        sub->orientMot = 93;
        break;
    case 200:
        ACTSendMailCorrect(g, 68);
        sub->orientMot = 95;
        break;
    case 300:
        ACTSendMailCorrect(g, 68);
        sub->orientMot = 97;
        break;
    }
}

void actBoyPullupReady(GObj *volatile self)
{
    float mv[4];
    Act *sub = GOBJ_ACT(self);

    sceVu0ScaleVector(mv, sub->env.cliffOrient, -30.0f);
    sceVu0AddVector(mv, sub->env.cliffStepPos, mv);
    StartCorrectPosition(self, mv, 0, 0, 20.0f);
    while (IsCorrectPosition(self)) {
        ContinueCorrectPosition(self);
        _ACTWait(1);
    }
    while (1) {
        _ACTCharStatus_Set(self, 24, -1.0f, 0);
        if ((sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 67);
        } else if (pullup_check_heroin_position()) {
            if (PAIR_IsStatus_GIRL_PULL() == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 73, isysCurrentGObj);
                }
            } else if (IsCorrectPosition(girlGObj) == 0) {
                ACTSendMail_PULLUP_GO();
            }
        }
        _ACTWait(1);
    }
}

/* the pull-up start mail, inlined into actBoyPullupGo */
static inline void ACTSendMail_PULLUP_START(void) /* derived name */
{
    Act *sub = GOBJ_ACT(boyGObj);

    switch (sub->env.cliffSel) {
    case 100:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 75, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 88;
        break;
    case 200:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 75, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 89;
        break;
    case 300:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 75, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 90;
        break;
    }
}
#else
#ifdef VERSION_AUG6
/* the pull-up go mail, inlined into actBoyPullupReady */
static inline void ACTSendMail_PULLUP_GO(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);

    switch (sub->env.cliffSel) {
    case 100:
        ACTSendMailCorrect(g, 69);
        sub->orientMot = 96;
        break;
    case 200:
        ACTSendMailCorrect(g, 69);
        sub->orientMot = 98;
        break;
    case 300:
        ACTSendMailCorrect(g, 69);
        sub->orientMot = 100;
        break;
    }
}
#else
inline void actBoyCall(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyCall\n");
    sub->actMode = 9;
    _ACTWait(2);
    if (girlGObj != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        iosOmSendMail(girlGObj, 61, isysCurrentGObj);
#else
        iosOmSendMail(girlGObj, 0x41, isysCurrentGObj);
#endif
    }
    while (1) {
        if ((sub->pad.now & 8) == 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
            ACTSendMailCorrect(self, 183);
#else
            ACTSendMailCorrect(self, 0xC7);
#endif
        }
        _ACTWait(1);
    }
}
#endif

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
/* the pull-up start mail, inlined into actBoyPullupGo */
static inline void ACTSendMail_PULLUP_START(void) /* derived name */
{
    Act *sub = GOBJ_ACT(boyGObj);

    switch (sub->env.cliffSel) {
    case 100:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 76, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 91;
        break;
    case 200:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 76, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 92;
        break;
    case 300:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 76, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 93;
        break;
    }
}
#else
inline void actBoyItem(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 183);
        _ACTWait(1);
    }
}
#endif

#ifdef VERSION_AUG6
static int pullup_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, s->env.cliffOrient) &&
        _DistxzGV(s->env.cliffStepPos, test_CURRENTROOT(girlGObj)) < 100.0f &&
        ((unsigned int)(GOBJ_ACT(girlGObj)->flags18.ll >> 48) & 1) &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 450.0f))) {
        return 1;
    }
    return 0;
}
#else
inline void actBoyItemAfter(GObj *volatile self)
{
    float dir[4];

    debug_StdPrintfDummy("enter actBoyItemAfter\n");
    while (1) {
        sceVu0ScaleVector(dir, test_CURRENTORIENT(self), 15.0f);
        ACTSendMailCorrect(self, 183);
        _ACTWait(1);
    }
}
#endif

static int ditch_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
#ifdef VERSION_AUG6
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4B0)) &&
        _DistxzGV((char *)s + 0x500, test_CURRENTROOT(girlGObj)) < 31.0f &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 450.0f))) {
#else
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4B0)) &&
        _DistxzGV((char *)s + 0x500, test_CURRENTROOT(girlGObj)) < 31.0f &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 200.0f))) {
#endif
        return 1;
    }
    return 0;
}

void actBoyPullupReady(GObj *volatile self)
{
    float mv[4];

    /* the helper is defined here and inlined at the pull-up test */
    inline unsigned char isGirlWithinPullupHeight(void) /* derived name */
    {
        float boy[4];
        float girl[4];

        GetRootProjectionPosOfGObj(boy, boyGObj);
        GetRootProjectionPosOfGObj(girl, girlGObj);
        if (GOBJ_ACT(girlGObj)->actMode == 38 ||
            (boy[1] - girl[1] < 0.0f ? -(boy[1] - girl[1]) : boy[1] - girl[1]) < 50.0f) {
            return 1;
        }
        return 0;
    }
    Act *sub = GOBJ_ACT(self);

    sceVu0ScaleVector(mv, sub->env.cliffOrient, -30.0f);
    sceVu0AddVector(mv, sub->env.cliffStepPos, mv);
    StartCorrectPosition(self, mv, 0, 0, 20.0f);
    while (IsCorrectPosition(self)) {
        ContinueCorrectPosition(self);
        _ACTWait(1);
    }
    while (1) {
        _ACTCharStatus_Set(self, 26, -1.0f, 0);
        if ((sub->pad.now & 8) == 0 || isGirlWithinPullupHeight()) {
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 68);
#else
            ACTSendMailCorrect(self, 69);
#endif
        } else if (pullup_check_heroin_position()) {
            if (PAIR_IsStatus_GIRL_PULL() == 0) {
                if (girlGObj != 0) {
#ifdef VERSION_AUG6
                    iosOmSendMail(girlGObj, 74, isysCurrentGObj);
#else
                    iosOmSendMail(girlGObj, 75, isysCurrentGObj);
#endif
                }
            } else if (IsCorrectPosition(girlGObj) == 0) {
                ACTSendMail_PULLUP_GO();
            }
        }
        _ACTWait(1);
    }
}
#else
#define BOY_GIRL_DY()                                                                              \
    (test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1]) /* derived name */

static void ACTSendMail_PULLUP_GO(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);

    switch (sub->env.cliffSel) {
    case 0x64:
        ACTSendMailCorrect(g, 0x4A);
        sub->orientMot = 0x6B;
        break;
    case 0xC8:
        ACTSendMailCorrect(g, 0x4A);
        sub->orientMot = 0x6D;
        break;
    case 0x12C:
        if (GOBJ_ACT(girlGObj)->actMode != 0x50) {
            break;
        }
        if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()))) {
            ACTSendMailCorrect(g, 0x4A);
            sub->orientMot = 0x6F;
        } else if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x52, isysCurrentGObj);
        }
        break;
    }
}

/* the pull-up start mail, inlined into actBoyPullupGo */
static inline void ACTSendMail_PULLUP_START(void) /* derived name */
{
    Act *sub = GOBJ_ACT(boyGObj);

    switch (sub->env.cliffSel) {
    case 0x64:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x65;
        break;
    case 0xC8:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x66;
        break;
    case 0x12C:
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
        }
        GOBJ_ACT(girlGObj)->orientMot = 0x67;
        break;
    }
}

static int pullup_check_heroin_position(void)
{
    float buf[4];
    float p1[4];
    float p2[4];
    GObj *g = boyGObj;
    Act *s = GOBJ_ACT(g);

    if (girlControlMode != 0 && s->env.cliffSel == 300) {
        switch (GOBJ_ACT(girlGObj)->actMode) {
        case 4:
            GetSkeltonPosition(p1, girlGObj, 0x16);
            GetSkeltonPosition(p2, boyGObj, 6);
            if (_DistSqGV(p1, p2) < 3600.0f) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x59, isysCurrentGObj);
                }
            }
            return 0;
        case 0x51:
            ACTSendMailCorrect(boyGObj, 0x58);
            return 0;
        default:
            return 0;
        }
    }
    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, s->env.cliffOrient) &&
        _DistxzGV(s->env.cliffStepPos, test_CURRENTROOT(girlGObj)) < 100.0f &&
        ((unsigned int)(GOBJ_ACT(girlGObj)->flags18.ll >> 54) & 1) &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 450.0f))) {
        return 1;
    }
    return 0;
}

static int ditch_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4C0)) &&
        _DistxzGV((char *)s + 0x510, test_CURRENTROOT(girlGObj)) < 31.0f &&
        (girlGObj == 0 || boyGObj == 0 ||
         !(test_CURRENTROOT(girlGObj)[1] > test_CURRENTROOT(boyGObj)[1] + 200.0f))) {
        return 1;
    }
    return 0;
}

void actBoyPullupReady(GObj *volatile self)
{
    float mv[4];

    /* the helper is defined here and inlined at the pull-up test */
    inline unsigned char isGirlWithinPullupHeight(void) /* derived name */
    {
        float boy[4];
        float girl[4];

        GetRootProjectionPosOfGObj(boy, boyGObj);
        GetRootProjectionPosOfGObj(girl, girlGObj);
        if (GOBJ_ACT(girlGObj)->actMode == 0x26 ||
            (boy[1] - girl[1] < 0.0f ? -(boy[1] - girl[1]) : boy[1] - girl[1]) < 50.0f) {
            return 1;
        }
        return 0;
    }
    Act *sub = GOBJ_ACT(self);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    ACTAdjustPlane(self, BOY_WALL(self) + 0x8B0);
#else
    ACTAdjustPlane(self, BOY_WALL(self) + 0x8C0);
#endif
    while (1) {
        if (GOBJ_WORK(self)->boxSideSet && motionKind[GOBJ_SUB(self)->ctrl.motion].playMode != 1) {
            _MoveGV(mv, test_CURRENTROOT(self), GOBJ_WORK(self)->boxSidePos, 3.0f);
            SetRootPosition(self, mv);
        }
        _ACTCharStatus_Set(self, 0x1C, -1.0f, 0);
        if ((sub->pad.now & 8) == 0 || isGirlWithinPullupHeight()) {
            ACTSendMailCorrect(self, 0x49);
        } else if (pullup_check_heroin_position()) {
            if (PAIR_IsStatus_GIRL_PULL() == 0) {
                if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()) &&
                      GOBJ_WORK(girlGObj)->jumpTimer)) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 0x4F, isysCurrentGObj);
                    }
                }
            } else if (IsCorrectPosition(girlGObj) == 0) {
                ACTSendMail_PULLUP_GO();
            }
        }
        _ACTWait(1);
    }
}
#endif
#endif

/* the boy is hauling the girl up: moving while the stick is pushed between
   0.1 and 0.99 of its range, or further with button 0x20 held */
#define BOY_PULLUP_MOVING(sub) /* derived name */                                                  \
    (0.1f < (sub)->stick.mag && ((sub)->stick.mag < 0.99f || ((sub)->pad.now & 0x20)))

#ifdef VERSION_JUN26
void actBoyPullupGo(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    ACTSendMail_PULLUP_START();
    while (1) {
        if ((sub->pad.trg & 8) || PAIR_IsStatus_GIRL_PULL() == 0) {
            ACTSendMailCorrect(self, 69);
        } else {
            if (0.1f < sub->stick.mag && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 70);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 71);
            } else {
                ACTSendMailCorrect(self, 72);
            }
        }
        _ACTWait(1);
    }
}

inline void actBoyHang(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHang\n");
    sub->actMode = 28;
    _ACTWait(0);
}

inline void actBoyCliffHesitate(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
            brainSetSpMode();
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 56, isysCurrentGObj);
            }
        }
        ACTSendMailCorrect(self, 268);
        _ACTWait(1);
    }
}

inline void actBoyCall(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyCall\n");
    sub->actMode = 9;
    _ACTWait(2);
    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 59, isysCurrentGObj);
    }
    while (1) {
        if ((sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 177);
        }
        _ACTWait(1);
    }
}

inline void actBoyItem(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actBoyItemAfter(GObj *volatile self)
{
    float dir[4];

    debug_StdPrintfDummy("enter actBoyItemAfter\n");
    while (1) {
        sceVu0ScaleVector(dir, test_CURRENTORIENT(self), 15.0f);
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

extern void InsertCamera_Set(float *pos, float *tgt, int frames);

void actBoyBelift(GObj *volatile self)
{
    /* the quaternion is reached through a union, the form actEnemyKidnapEnd
       (enemy_act.c) gives the same memset-and-w=1 idiom */
    union { /* field names derived */
        float f[4];
    } q;

    float cam[4];
    float boypos[4];
    float p[4];
    float girlpos[4];
    float dir[4];
    float ofs[4];
    float hit[4];
    GObj *girl = GOBJ_ACT(self)->intrArg;
    float ratio;
    int mode;
    int lv;
    float dist;

    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    ratio = 1.0f;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        ratio = 0.2f;
    }
    mode = GOBJ_ACT(girl)->enemy->liftKind == 3 ? 0 : 2;
    BOY_EXT(self)->liftObj = girl;
    beliftGirl = girl;
    BOY_EXT(self)->liftLevel = 10;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        RotQuaternionX(q.f, 0x4000);
    }
    SetMotionNodeFixModeParameter((void *)self, girl, mode, 0x16, q.f, 0.0f, 0.0f, 0.0f, ratio);
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    _ACTWait(1);
    while (1) {
        if (GOBJ_ACT(girl)->enemy->liftKind == 3 && (unsigned int)GOBJ_ACT(girl)->actMode == 93) {
            lv = BOY_EXT(self)->liftLevel;
            lv = lv < 0 ? 0 : (10.0f < lv ? 10.0f : lv);
            lv = lv * 0.5f;
            dist = lv * 100.0f + 500.0f;
            GetSkeltonPosition(boypos, boyGObj, 35);
            GetSkeltonPosition(girlpos, girl, 35);
            _OrientXZGV(dir, girlpos, boypos);
            sceVu0ScaleVector(ofs, dir, -dist);
            sceVu0AddVector(p, ofs, boypos);
            if (_DistSqGV(p, cam) < 2500.0f) {
                _InterGV(p, cam, p, 1.0f, 1.0f);
            } else {
                _MoveGV(p, cam, p, 50.0f);
            }
            if (ACTCheckCollis_WF(50.0f, girlpos, p, 0, hit)) {
                p[0] = hit[0];
                p[1] = hit[1];
                p[2] = hit[2];
            }
            cam[0] = p[0];
            cam[1] = p[1];
            cam[2] = p[2];
            GetSkeltonPosition(girlpos, boyGObj, 44);
            sceVu0ScaleVector(p, p, -1.0f);
            sceVu0ScaleVector(girlpos, girlpos, -1.0f);
            InsertCamera_Set(p, girlpos, (60 - systemStatus[0] * 10) / systemStatus[1] / 6);
        }
        switch ((unsigned int)GOBJ_ACT(girl)->actMode) {
        case 93:
        case 94:
            break;
        default:
            ACTSendMailCorrect(self, 202);
            debug_StdPrintfDummy("enemy error body slam[%s]\n",
                                 actModeTbl[(unsigned int)GOBJ_ACT(girl)->actMode].name);
            break;
        }
        _ACTWait(1);
    }
}

void actBoyRescueReady(GObj *volatile self)
{
    GObj *g = GOBJ_ACT(self)->enemy->rescueObj;
    float p[4];
    float q[4];
    float step[4];
    float dir[4];
    float tmp[4];
    float np[4];
    int cnt = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    int rest;

    p[0] = test_CURRENTROOT((void *)self)[0];
    p[1] = test_CURRENTROOT((void *)self)[1];
    p[2] = test_CURRENTROOT((void *)self)[2];
    q[0] = test_CURRENTROOT(g)[0];
    q[1] = test_CURRENTROOT(g)[1];
    q[2] = test_CURRENTROOT(g)[2];
    _OrientXZGV(dir, q, p);
    sceVu0ScaleVector(tmp, dir, -60.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueBoyPos, q, tmp);
    sceVu0ScaleVector(tmp, dir, 0.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueGirlPos, q, tmp);
    GOBJ_ACT(self)->enemy->rescueGirlPos[1] += 50.0f;
    SetMotionDirection((void *)self, dir);
    sceVu0SubVector(step, GOBJ_ACT(self)->enemy->rescueBoyPos, (float *)p);
    sceVu0ScaleVector(step, step, 1.0f / (float)cnt);
    rest = cnt;
    while (1) {
        if (0 < rest) {
            sceVu0AddVector(np, test_CURRENTROOT((void *)self), step);
            np[1] = test_CURRENTROOT((void *)self)[1];
            SetDirectRootPosition((void *)self, np);
        }
        rest--;
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1 ||
            (GOBJ_SUB(self)->ctrl.ctrlFlags & 0x16) || GOBJ_SUB(self)->ctrl.frameEnd != 0) {
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 308, isysCurrentGObj);
            }
        }
        _ACTWait(1);
    }
}

/* the girl is in place for the ditch hand-up: on the ditch's side and within
   60 of its point; inlined at the test */
static inline unsigned char ditch_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(boyGObj);

    sceVu0SubVector(buf, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4B0)) &&
        _DistxzGV((char *)s + 0x500, test_CURRENTROOT(girlGObj)) < 60.0f) {
        return 1;
    }
    return 0;
}

void actBoyDitch3mReady(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int a;
    int b;

    _ACTWait(1);
    while (1) {
        a = 1;
        switch ((unsigned int)GOBJ_ACT(girlGObj)->actMode) {
        case 4:
        case 86: {
            float p[4];
            float q[4];

            p[0] = test_CURRENTROOT(boyGObj)[0];
            p[1] = test_CURRENTROOT(boyGObj)[1];
            p[2] = test_CURRENTROOT(boyGObj)[2];
            q[0] = test_CURRENTROOT(girlGObj)[0];
            q[1] = test_CURRENTROOT(girlGObj)[1];
            q[2] = test_CURRENTROOT(girlGObj)[2];
            if (_DistxzSqGV(p, q) < 250000.0f) {
                if (p[1] + 300.0f < q[1]) {
                } else {
                    a = 0;
                }
            }
            break;
        }
        }

        if (a != 0 && (sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 344);
        } else {
            if (ditch_check_heroin_position() != 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 346, isysCurrentGObj);
                }
            }
            if (IsCorrectPosition(girlGObj) == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 347, isysCurrentGObj);
                }
            }
            if (GOBJ_ACT(girlGObj)->actMode == 4) {
                float dy;

                b = 0;
                dy = test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1];
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 10000.0f &&
                    ABSF(BOYGIRL_DY()) < 100.0f) {
                    b = 1;
                }
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 78400.0f &&
                    ABSF(BOYGIRL_DY()) < 200.0f && 50.0f < dy && dy < 200.0f) {
                    b = 1;
                }
                if (b != 0) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 349, isysCurrentGObj);
                    }
                    ACTSendMailCorrect(self, 345);
                }
            }
        }
        _ACTWait(1);
    }
}

/* camera-root.c's insert camera, three arguments in this build (camera-root.h, which this TU
   does not include, declares it too; the USA build's takes four) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames);

void SetStatusBoy_OtherStageGirlPinch(void)
{
    float buf[4];
    float pos[4];
    float tgt[4];
    float tmp[4];
    float head[4];
    float hit[4];
    GObj *g = boyGObj;
    ActWork *w;
    float t;
    int frames;

    t = (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    GetOtherStageGirlOrient(buf);
    w = GOBJ_WORK(g);
    frames = (int)t;
    w->pinchFrames = frames;
    w->pinchPosX = buf[0];
    w->pinchPosY = buf[1];
    w->pinchPosZ = buf[2];
    GetSkeltonPosition(head, g, 35);
    sceVu0ScaleVector(tmp, buf, -100.0f);
    sceVu0AddVector(pos, head, tmp);
    if (ACTCheckCollis_W(10.0f, head, pos, 0, hit, 0)) {
        pos[0] = head[0];
        pos[1] = head[1] - 50.0f;
        pos[2] = head[2];
    }
    sceVu0ScaleVector(tmp, buf, 300.0f);
    sceVu0AddVector(tgt, head, tmp);
    InsertCamera_SetNoraml(pos, tgt, frames);
}
#else
#ifdef VERSION_NTSC
void actBoyPullupGo(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    ACTSendMail_PULLUP_START();
    while (1) {
        if (PAIR_IsStatus_GIRL_PULL() == 0) {
            ACTSendMailCorrect(self, 71);
        } else {
            if (0.1f < sub->stick.mag && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 72);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 73);
            } else {
                ACTSendMailCorrect(self, 74);
            }
        }
        _ACTWait(1);
    }
}

extern void InsertCamera_Set(float *pos, float *tgt, int frames);

void actBoyBelift(GObj *volatile self)
{
    /* the quaternion is reached through a union, the form actEnemyKidnapEnd
       (enemy_act.c) gives the same memset-and-w=1 idiom */
    union { /* field names derived */
        float f[4];
    } q;

    float cam[4];
    float boypos[4];
    float p[4];
    float girlpos[4];
    float dir[4];
    float ofs[4];
    float hit[4];
    GObj *girl = GOBJ_ACT(self)->intrArg;
    float ratio;
    int mode;
    int lv;
    float dist;

    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    ratio = 1.0f;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        ratio = 0.2f;
    }
    mode = GOBJ_ACT(girl)->enemy->liftKind == 3 ? 0 : 2;
    BOY_EXT(self)->liftObj = girl;
    beliftGirl = girl;
    BOY_EXT(self)->liftLevel = 10;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        RotQuaternionX(q.f, 0x4000);
    }
    SetMotionNodeFixModeParameter((void *)self, girl, mode, 0x16, q.f, 0.0f, 0.0f, 0.0f, ratio);
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    _ACTWait(1);
    while (1) {
        if (GOBJ_ACT(girl)->enemy->liftKind == 3 && (unsigned int)GOBJ_ACT(girl)->actMode == 94) {
            lv = BOY_EXT(self)->liftLevel;
            lv = lv < 0 ? 0 : (10.0f < lv ? 10.0f : lv);
            lv = lv * 0.5f;
            dist = lv * 100.0f + 500.0f;
            GetSkeltonPosition(boypos, boyGObj, 35);
            GetSkeltonPosition(girlpos, girl, 35);
            _OrientXZGV(dir, girlpos, boypos);
            sceVu0ScaleVector(ofs, dir, -dist);
            sceVu0AddVector(p, ofs, boypos);
            if (_DistSqGV(p, cam) < 2500.0f) {
                _InterGV(p, cam, p, 1.0f, 1.0f);
            } else {
                _MoveGV(p, cam, p, 50.0f);
            }
            if (ACTCheckCollis_WF(50.0f, girlpos, p, 0, hit)) {
                p[0] = hit[0];
                p[1] = hit[1];
                p[2] = hit[2];
            }
            cam[0] = p[0];
            cam[1] = p[1];
            cam[2] = p[2];
            GetSkeltonPosition(girlpos, boyGObj, 44);
            sceVu0ScaleVector(p, p, -1.0f);
            sceVu0ScaleVector(girlpos, girlpos, -1.0f);
            InsertCamera_Set(p, girlpos, (60 - systemStatus[0] * 10) / systemStatus[1] / 6);
        }
        switch ((unsigned int)GOBJ_ACT(girl)->actMode) {
        case 94:
        case 95:
            break;
        default:
            ACTSendMailCorrect(self, 210);
            debug_StdPrintfDummy("enemy error body slam[%s]\n",
                                 actModeTbl[(unsigned int)GOBJ_ACT(girl)->actMode].name);
            break;
        }
        _ACTWait(1);
    }
}
#else
void actBoyPullupGo(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    ACTSendMail_PULLUP_START();
    while (1) {
        if (PAIR_IsStatus_GIRL_PULL() == 0) {
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 70);
        } else {
            if (0.1f < sub->stick.mag && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 71);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 72);
            } else {
                ACTSendMailCorrect(self, 73);
#else
            ACTSendMailCorrect(self, 0x4B);
        } else {
            if (0.1f < sub->stick.mag && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 0x4C);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(self, 0x4D);
            } else {
                ACTSendMailCorrect(self, 0x4E);
#endif
            }
        }
        _ACTWait(1);
    }
}

extern void InsertCamera_Set(float *pos, float *tgt, int frames);

#ifdef VERSION_AUG6
inline void actBoyCall(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyCall\n");
    sub->actMode = 9;
    _ACTWait(2);
    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 60, isysCurrentGObj);
    }
    while (1) {
        if ((sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 180);
        }
        _ACTWait(1);
    }
}

inline void actBoyItem(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 180);
        _ACTWait(1);
    }
}

inline void actBoyItemAfter(GObj *volatile self)
{
    float dir[4];

    debug_StdPrintfDummy("enter actBoyItemAfter\n");
    while (1) {
        sceVu0ScaleVector(dir, test_CURRENTORIENT(self), 15.0f);
        ACTSendMailCorrect(self, 180);
        _ACTWait(1);
    }
}
#endif

void actBoyBelift(GObj *volatile self)
{
    /* the quaternion is reached through a union, the form actEnemyKidnapEnd
       (enemy_act.c) gives the same memset-and-w=1 idiom */
    union { /* field names derived */
        float f[4];
    } q;

    float cam[4];
    float boypos[4];
    float p[4];
    float girlpos[4];
    float dir[4];
    float ofs[4];
    float hit[4];
    GObj *girl = GOBJ_ACT(self)->intrArg;
    float ratio;
    int mode;
    int lv;
    float dist;

    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    ratio = 1.0f;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        ratio = 0.2f;
    }
    mode = GOBJ_ACT(girl)->enemy->liftKind == 3 ? 0 : 2;
    BOY_EXT(self)->liftObj = girl;
    beliftGirl = girl;
    BOY_EXT(self)->liftLevel = 10;
    if (GOBJ_ACT(girl)->enemy->liftKind == 3) {
        RotQuaternionX(q.f, 0x4000);
    }
    SetMotionNodeFixModeParameter((void *)self, girl, mode, 0x16, q.f, 0.0f, 0.0f, 0.0f, ratio);
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    _ACTWait(1);
    while (1) {
#ifdef VERSION_AUG6
        if (GOBJ_ACT(girl)->enemy->liftKind == 3 && (unsigned int)GOBJ_ACT(girl)->actMode == 94) {
#else
        if (GOBJ_ACT(girl)->enemy->liftKind == 3 && (unsigned int)GOBJ_ACT(girl)->actMode == 0x61) {
#endif
            lv = BOY_EXT(self)->liftLevel;
            lv = lv < 0 ? 0 : (10.0f < lv ? 10.0f : lv);
            lv = lv * 0.5f;
            dist = lv * 100.0f + 500.0f;
#ifdef VERSION_AUG6
            GetSkeltonPosition(boypos, boyGObj, 35);
            GetSkeltonPosition(girlpos, girl, 35);
#else
            GetSkeltonPosition(boypos, boyGObj, 0x23);
            GetSkeltonPosition(girlpos, girl, 0x23);
#endif
            _OrientXZGV(dir, girlpos, boypos);
            sceVu0ScaleVector(ofs, dir, -dist);
            sceVu0AddVector(p, ofs, boypos);
            if (_DistSqGV(p, cam) < 2500.0f) {
                _InterGV(p, cam, p, 1.0f, 1.0f);
            } else {
                _MoveGV(p, cam, p, 50.0f);
            }
            if (ACTCheckCollis_WF(50.0f, girlpos, p, 0, hit)) {
                p[0] = hit[0];
                p[1] = hit[1];
                p[2] = hit[2];
            }
            cam[0] = p[0];
            cam[1] = p[1];
            cam[2] = p[2];
#ifdef VERSION_AUG6
            GetSkeltonPosition(girlpos, boyGObj, 44);
#else
            GetSkeltonPosition(girlpos, boyGObj, 0x2C);
#endif
            sceVu0ScaleVector(p, p, -1.0f);
            sceVu0ScaleVector(girlpos, girlpos, -1.0f);
            InsertCamera_Set(p, girlpos, (60 - systemStatus[0] * 10) / systemStatus[1] / 6);
        }
        switch ((unsigned int)GOBJ_ACT(girl)->actMode) {
#ifdef VERSION_AUG6
        case 94:
        case 95:
            break;
        default:
            ACTSendMailCorrect(self, 207);
#else
        case 0x61:
        case 0x62:
            break;
        default:
            ACTSendMailCorrect(self, 0xE2);
#endif
            debug_StdPrintfDummy("enemy error body slam[%s]\n",
                                 actModeTbl[(unsigned int)GOBJ_ACT(girl)->actMode].name);
            break;
        }
        _ACTWait(1);
    }
}
#endif

/* The walk order the boy is executing: sub->0x30 points at the request record
   the caller filled in, and actBoyReadyMove works on a private copy of it. */
typedef struct { /* field names derived */
    float pos[4];
    float dir[4];
    float range;
    int frames;
    int fix;
    int _2C;
} __attribute__((aligned(16))) BoyMoveOrder; /* derived name */

#ifdef VERSION_NTSC
inline void actBoyReadyMove(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    BoyMoveOrder ord = *(BoyMoveOrder *)((char *)GOBJ_ACT(self)->intrData);

    while (1) {
        _ACTMotDirSmzDirect((void *)self, ord.dir);
        if (ord.fix) {
            sub->wish3.ll |= 0x1000;
            sub->wish3.ll |= 0x2;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(self, 250);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)self), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(self, 250);
        }
        _ACTWait(1);
    }
}

void actBoyRescueReady(GObj *volatile self)
{
    GObj *g = GOBJ_ACT(self)->enemy->rescueObj;
    float p[4];
    float q[4];
    float step[4];
    float dir[4];
    float tmp[4];
    float np[4];

    union { /* field names derived */
        float f[4];
        long long ll[2];
    } pts[2];

    int cnt = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    int rest, hp, r;
    int n1, n2;
    char *hold;
    int u = 0;
    int gm = GOBJ_SUB(girlGObj)->ctrl.motion;
    int t;

    p[0] = test_CURRENTROOT((void *)self)[0];
    p[1] = test_CURRENTROOT((void *)self)[1];
    p[2] = test_CURRENTROOT((void *)self)[2];
    q[0] = test_CURRENTROOT(g)[0];
    q[1] = test_CURRENTROOT(g)[1];
    q[2] = test_CURRENTROOT(g)[2];
    _OrientXZGV(dir, q, p);
    sceVu0ScaleVector(tmp, dir, -60.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueBoyPos, q, tmp);
    sceVu0ScaleVector(tmp, dir, 0.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueGirlPos, q, tmp);
    GOBJ_ACT(self)->enemy->rescueGirlPos[1] += 50.0f;
    SetMotionDirection((void *)self, dir);
    sceVu0SubVector(step, GOBJ_ACT(self)->enemy->rescueBoyPos, (float *)p);
    sceVu0ScaleVector(step, step, 1.0f / (float)cnt);
    t = 1;
    rest = cnt;
    while (1) {
        if (0 < rest) {
            sceVu0AddVector(np, test_CURRENTROOT((void *)self), step);
            np[1] = test_CURRENTROOT((void *)self)[1];
            SetDirectRootPositionNoFitting((void *)self, np);
        }
        rest--;
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1 ||
            (GOBJ_SUB(self)->ctrl.ctrlFlags & 0x16) || GOBJ_SUB(self)->ctrl.frameEnd != 0) {
            hold = (char *)GOBJ_ACT(girlGObj)->carrier;
            hp = GOBJ_ACT(hold)->modeFrame;
            r = 0;
            /* n1 takes systemStatus[0] and is not read on this path */
            n1 = systemStatus[0];
            ACTGame_ConnectHand();
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 <= hp) {
                r = hp * ((60 - systemStatus[0] * 10) / systemStatus[1] * 3) /
                    ((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
            }
            /* the quotient is not read */
            if (0 <= r) {
                r = (60 - systemStatus[0] * 10) / systemStatus[1];
            }
            if (gameover_flag == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 321, isysCurrentGObj);
                }
            }
            n1 = GetSkeltonFocusNode(girlGObj, 0x16);
            n2 = GetSkeltonFocusNode(boyGObj, 6);
            pts[0].f[0] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x30);
            pts[0].f[1] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x34);
            pts[0].f[2] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x38);
            pts[1].f[0] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x30);
            pts[1].f[1] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x34);
            pts[1].f[2] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x38);
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, pts[0].f, 0.05f);
            u = t++;
        }
        if (gm == 626) {
            if ((u / 30) & 1) {
                ACTSendMailCorrect(self, 324);
            } else {
                ACTSendMailCorrect(self, 323);
            }
        } else {
            if ((u / 15) & 1) {
                ACTSendMailCorrect(self, 324);
            } else {
                ACTSendMailCorrect(self, 323);
            }
        }
        _ACTWait(1);
    }
}

void actBoyDitch3mReady(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float p[4];
    float q[4];
    int a;
    int b;

    _ACTWait(1);
    ResetMotionProgramInterpInfo(self, 35);
    ResetMotionProgramInterpInfo(self, 1);

    while (1) {
        a = 1;
        b = 0;
        switch ((unsigned int)GOBJ_ACT(girlGObj)->actMode) {
        case 4:
        case 87:
            p[0] = test_CURRENTROOT(boyGObj)[0];
            p[1] = test_CURRENTROOT(boyGObj)[1];
            p[2] = test_CURRENTROOT(boyGObj)[2];
            q[0] = test_CURRENTROOT(girlGObj)[0];
            q[1] = test_CURRENTROOT(girlGObj)[1];
            q[2] = test_CURRENTROOT(girlGObj)[2];
            if (_DistxzSqGV(p, q) < 250000.0f) {
                if (p[1] + 300.0f < q[1]) {
                } else {
                    a = 0;
                }
            }
            break;
        case 28:
        case 29:
            b = 1;
            break;
        }

        /* two branches with one body */
        if (a != 0 && (sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 364);
        } else if (b != 0) {
            ACTSendMailCorrect(self, 364);
        } else {
            if (ditch_check_heroin_position() != 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 366, isysCurrentGObj);
                }
            }
            if (IsCorrectPosition(girlGObj) == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 367, isysCurrentGObj);
                }
            }
            if (GOBJ_ACT(girlGObj)->actMode == 4) {
                float dy;

                b = 0;
                dy = test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1];
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 10000.0f &&
                    ABSF(BOYGIRL_DY()) < 100.0f) {
                    b = 1;
                }
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 78400.0f &&
                    ABSF(BOYGIRL_DY()) < 200.0f && 50.0f < dy && dy < 200.0f) {
                    b = 1;
                }
                if (sub->env.ditchCarry != 0) {
                    b = 0;
                }
                if (b != 0) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 369, isysCurrentGObj);
                    }
                    ACTSendMailCorrect(self, 365);
                }
            }
        }
        _ACTWait(1);
    }
}
#else
#ifdef VERSION_AUG6
inline void actBoyReadyMove(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    BoyMoveOrder ord = *(BoyMoveOrder *)((char *)GOBJ_ACT(self)->intrData);

    while (1) {
        _ACTMotDirSmzDirect((void *)self, ord.dir);
        if (ord.fix) {
            sub->wish3.ll |= 0x1000;
            sub->wish3.ll |= 0x2;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(self, 247);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)self), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(self, 247);
        }
        _ACTWait(1);
    }
}
#else
void actBoyReadyMove(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    BoyMoveOrder ord = *(BoyMoveOrder *)((char *)GOBJ_ACT(self)->intrData);

    while (1) {
        if ((((void *)self == girlGObj && girlControlMode != 0)
                 ? (GOBJ_SUB(self)->ctrl.motion + motionKind)->girlDirFrames
                 : (GOBJ_SUB(self)->ctrl.motion + motionKind)->dirFrames) == 0) {
            SetMotionDirectionSmooze(self, ord.dir, 10.0f);
        } else {
            _ACTMotDirSmzDirect((void *)self, ord.dir);
        }
        if (ord.fix) {
            sub->wish3.ll |= 0x80000;
            sub->wish3.ll |= 0x40;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(self, 0x10A);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)self), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(self, 0x10A);
        }
        if (0.1f < sub->stick.mag && 100 < _AbsRotyGV(ord.dir, (char *)sub + 0x120)) {
            ACTSendMailCorrect(self, 0x10A);
        }
        _ACTWait(1);
    }
}
#endif

void actBoyRescueReady(GObj *volatile self)
{
    GObj *g = GOBJ_ACT(self)->enemy->rescueObj;
    float p[4];
    float q[4];
    float step[4];
    float dir[4];
    float tmp[4];
    float np[4];

    union { /* field names derived */
        float f[4];
        long long ll[2];
    } pts[2];

    int cnt = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
    int rest, hp, r;
    int n1, n2;
    char *hold;
    int u = 0;
    int gm = GOBJ_SUB(girlGObj)->ctrl.motion;
    int t;

    p[0] = test_CURRENTROOT((void *)self)[0];
    p[1] = test_CURRENTROOT((void *)self)[1];
    p[2] = test_CURRENTROOT((void *)self)[2];
    q[0] = test_CURRENTROOT(g)[0];
    q[1] = test_CURRENTROOT(g)[1];
    q[2] = test_CURRENTROOT(g)[2];
    _OrientXZGV(dir, q, p);
    sceVu0ScaleVector(tmp, dir, -60.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueBoyPos, q, tmp);
    sceVu0ScaleVector(tmp, dir, 0.0f);
    sceVu0AddVector(GOBJ_ACT(self)->enemy->rescueGirlPos, q, tmp);
    GOBJ_ACT(self)->enemy->rescueGirlPos[1] += 50.0f;
    SetMotionDirection((void *)self, dir);
    sceVu0SubVector(step, GOBJ_ACT(self)->enemy->rescueBoyPos, (float *)p);
    sceVu0ScaleVector(step, step, 1.0f / (float)cnt);
    t = 1;
    rest = cnt;
    while (1) {
        if (0 < rest) {
            sceVu0AddVector(np, test_CURRENTROOT((void *)self), step);
            np[1] = test_CURRENTROOT((void *)self)[1];
            SetDirectRootPositionNoFitting((void *)self, np);
        }
        rest--;
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1 ||
            (GOBJ_SUB(self)->ctrl.ctrlFlags & 0x16) || GOBJ_SUB(self)->ctrl.frameEnd != 0) {
            hold = (char *)GOBJ_ACT(girlGObj)->carrier;
            hp = GOBJ_ACT(hold)->modeFrame;
            r = 0;
            /* n1 takes systemStatus[0] and is not read on this path */
            n1 = systemStatus[0];
            ACTGame_ConnectHand();
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 100 / 60 <= hp) {
                r = hp * ((60 - systemStatus[0] * 10) / systemStatus[1] * 3) /
                    ((60 - systemStatus[0] * 10) / systemStatus[1] * 10);
            }
            /* the quotient is not read */
            if (0 <= r) {
                r = (60 - systemStatus[0] * 10) / systemStatus[1];
            }
            if (gameover_flag == 0) {
                if (girlGObj != 0) {
#ifdef VERSION_AUG6
                    iosOmSendMail(girlGObj, 317, isysCurrentGObj);
#else
                    iosOmSendMail(girlGObj, 0x15D, isysCurrentGObj);
#endif
                }
            }
            n1 = GetSkeltonFocusNode(girlGObj, 0x16);
            n2 = GetSkeltonFocusNode(boyGObj, 6);
            pts[0].f[0] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x30);
            pts[0].f[1] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x34);
            pts[0].f[2] = *(float *)((char *)GOBJ_SUB(girlGObj)->nodeMtx + n1 * 0x40 + 0x38);
            pts[1].f[0] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x30);
            pts[1].f[1] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x34);
            pts[1].f[2] = *(float *)((char *)GOBJ_SUB(boyGObj)->nodeMtx + n2 * 0x40 + 0x38);
            SetDirectRootPositionNoFittingWithNodePoint((void *)self, 6, pts[0].f, 0.05f);
            u = t++;
        }
#ifdef VERSION_AUG6
        if (gm == 628) {
            if ((u / 30) & 1) {
                ACTSendMailCorrect(self, 320);
            } else {
                ACTSendMailCorrect(self, 319);
#else
        if (gm == 641) {
            if ((u / 30) & 1) {
                ACTSendMailCorrect(self, 0x160);
            } else {
                ACTSendMailCorrect(self, 0x15F);
#endif
            }
        } else {
            if ((u / 15) & 1) {
#ifdef VERSION_AUG6
                ACTSendMailCorrect(self, 320);
            } else {
                ACTSendMailCorrect(self, 319);
#else
                ACTSendMailCorrect(self, 0x160);
            } else {
                ACTSendMailCorrect(self, 0x15F);
#endif
            }
        }
        _ACTWait(1);
    }
}

void actBoyDitch3mReady(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    float p[4];
    float q[4];
#ifndef VERSION_AUG6
    int c = 0;
#endif
    int a;
    int b;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    ACTAdjustPlane(self, BOY_WALL(self) + 0x8B0);
#else
#ifndef VERSION_AUG6
    ACTAdjustPlane(self, BOY_WALL(self) + 0x8C0);
#endif
#endif
    _ACTWait(1);
    ResetMotionProgramInterpInfo(self, 35);
    ResetMotionProgramInterpInfo(self, 1);

    while (1) {
        a = 1;
        b = 0;
        switch ((unsigned int)GOBJ_ACT(girlGObj)->actMode) {
        case 4:
#ifdef VERSION_AUG6
        case 87:
#else
        case 90:
#endif
            p[0] = test_CURRENTROOT(boyGObj)[0];
            p[1] = test_CURRENTROOT(boyGObj)[1];
            p[2] = test_CURRENTROOT(boyGObj)[2];
            q[0] = test_CURRENTROOT(girlGObj)[0];
            q[1] = test_CURRENTROOT(girlGObj)[1];
            q[2] = test_CURRENTROOT(girlGObj)[2];
            if (_DistxzSqGV(p, q) < 250000.0f) {
                if (p[1] + 300.0f < q[1]) {
                } else {
                    a = 0;
                }
            }
            break;
        case 28:
        case 29:
            b = 1;
            break;
        }

#ifdef VERSION_AUG6
        /* two branches with one body */
        if (a != 0 && (sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 360);
        } else if (b != 0) {
            ACTSendMailCorrect(self, 360);
        } else {
            if (ditch_check_heroin_position() != 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 362, isysCurrentGObj);
                }
            }
            if (IsCorrectPosition(girlGObj) == 0) {
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 363, isysCurrentGObj);
                }
            }
            if (GOBJ_ACT(girlGObj)->actMode == 4) {
#else
        if (GOBJ_ACT(girlGObj)->actMode != 4 &&
            _DistSqGV(test_CURRENTROOT(boyGObj), (char *)sub + 0x510) < 90000.0f &&
            _DistSqGV(test_CURRENTROOT(girlGObj), (char *)sub + 0x510) < 90000.0f) {
            c = 1;
        }

        if (c != 0) {
            if (GOBJ_ACT(girlGObj)->actMode == 4) {
                GOBJ_WORK(self)->ditchTimer = (60 - systemStatus[0] * 10) / systemStatus[1] / 3;
            }
            _ACTParaStatus_Set((void *)self, 40);
            _ACTCharStatus_Set((void *)self, 29, -1.0f, 0);
            GOBJ_WORK(self)->parallelInterp = 30.0f;
            ACTSendMailCorrect(self, 0x187);
        }

        /* two branches with one body */
        if (a != 0 && (sub->pad.now & 8) == 0) {
            ACTSendMailCorrect(self, 0x189);
            if (c != 0) {
                ACTSendMailCorrect(self, 0x18A);
            }
        } else if (b != 0) {
            ACTSendMailCorrect(self, 0x189);
            if (c != 0) {
                ACTSendMailCorrect(self, 0x18A);
            }
        } else {
            if (girlControlMode == 0) {
                if (ditch_check_heroin_position() != 0) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 0x18C, isysCurrentGObj);
                    }
                }
                if (IsCorrectPosition(girlGObj) == 0) {
                    if (girlGObj != 0) {
                        iosOmSendMail(girlGObj, 0x18D, isysCurrentGObj);
                    }
                }
            }
            if (GOBJ_ACT(girlGObj)->actMode == 4 && c == 0) {
#endif
                float dy;

                b = 0;
                dy = test_CURRENTROOT(girlGObj)[1] - test_CURRENTROOT(boyGObj)[1];
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 10000.0f &&
                    ABSF(BOYGIRL_DY()) < 100.0f) {
                    b = 1;
                }
                if (_DistxzSqGV(test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj)) < 78400.0f &&
                    ABSF(BOYGIRL_DY()) < 200.0f && 50.0f < dy && dy < 200.0f) {
                    b = 1;
                }
#ifndef VERSION_AUG6
                GetSkeltonPosition(p, girlGObj, 22);
                GetSkeltonPosition(q, boyGObj, 6);
                if (_DistSqGV(p, q) < 3600.0f) {
                    b = 1;
                }
#endif
                if (sub->env.ditchCarry != 0) {
                    b = 0;
                }
                if (b != 0) {
                    if (girlGObj != 0) {
#ifdef VERSION_AUG6
                        iosOmSendMail(girlGObj, 365, isysCurrentGObj);
                    }
                    ACTSendMailCorrect(self, 361);
                }
            }
#else
                        iosOmSendMail(girlGObj, 0x18F, isysCurrentGObj);
                    }
                    ACTSendMailCorrect(self, 0x18B);
                }
            }
        }
        _ACTWait(1);
    }
}

void actBoyRescueGirlBhang(GObj *volatile self)
{
    float tgt[4];
    float mv[4];
    float boy[4];
    float girl[4];
    Act *sub = GOBJ_ACT(self);
    int mode;
    int connect = 1;

    *(void **)((char *)sub + 0x18) = (void *)afterBoyRescueGirlBhang;
    while (1) {
        mode = 0;
        switch (GOBJ_ACT(girlGObj)->actMode) {
        case 0x1C:
            mode = 1;
            break;
        case 0x1D:
            mode = 2;
            if ((60 - systemStatus[0] * 10) / systemStatus[1] / 2 < sub->modeFrame) {
                if (connect) {
                    ACTGame_ConnectHand();
                    connect = 0;
                }
            }
            break;
        }
        if (mode != 0) {
            if (sub->modeFrame < 0xA) {
                boy[0] = test_CURRENTROOT(boyGObj)[0];
                boy[1] = test_CURRENTROOT(boyGObj)[1];
                boy[2] = test_CURRENTROOT(boyGObj)[2];
                girl[0] = test_CURRENTROOT(girlGObj)[0];
                girl[1] = test_CURRENTROOT(girlGObj)[1];
                girl[2] = test_CURRENTROOT(girlGObj)[2];
                tgt[0] = girl[0];
                tgt[2] = girl[2];
                tgt[1] = boy[1];
                _MoveGV(mv, boy, tgt, 5.0f);
                SetRootPosition((void *)self, mv);
            }
        }
        if (motionKind[GOBJ_SUB(self)->ctrl.motion].playMode == 1) {
            if (mode == 1) {
                ACTSendMailCorrect(self, 0x15B);
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x51, isysCurrentGObj);
                }
                GOBJ_ACT(girlGObj)->orientMot = 0x66;
            }
            if (mode == 2) {
                ACTSendMailCorrect(self, 0x15B);
                if (girlGObj != 0) {
                    iosOmSendMail(girlGObj, 0x40, isysCurrentGObj);
                }
            }
        }
        if (mode == 0) {
            ACTSendMailCorrect(self, 0xC7);
#endif
        }
        _ACTWait(1);
    }
}
#endif
#endif

inline int RequestStageChangeKidnapEnd(int stage, int targetId)
{
    int rv = 0;
    if (boyGObj != 0) {
#ifdef VERSION_JUN26
        rv = RequestStageChangeSimple(stage, 16.0f, 16.0f, 0, 0, 0) & 0xFF;
#else
        rv = RequestStageChangeSimple(stage, 0.25f, 4.0f, 0, 0, 0) & 0xFF;
#endif
        if (rv != 0) {
            Vec16 buf = {{-1000000.0f, 0.0f, 0.0f}};

            BOYEFSTAGE[0] = 1;
            *(int *)(BOYEFSTAGE + 4) = targetId;
            ACTGame_StageChangeGObjDirect(boyGObj, stage, &buf, 0);
        }
    }
    return rv;
}

#ifndef VERSION_JUN26
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void InsertCamera_SetNoraml(float *pos, float *tgt, int frames, int cutType);
#endif

void SetStatusBoy_OtherStageGirlPinch(void)
{
    float buf[4];
    float cam[4];
    float pos[4];
    GObj *g = boyGObj;
    ActWork *w;
    float a;
    float b;
    float t;
    int frames;

    a = _ACTGame_GetParamF(0xD);
    b = _ACTGame_GetParamF(0xE);
    t = a * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f +
        b * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
#ifdef VERSION_AUG6
    ExecuteSEPackage(0, 122);
    GetOtherStageGirlOrient(buf);
#else
#ifdef VERSION_NTSC
    ExecuteSEPackage(0, 122);
#else
    ExecuteSEPackage(0, 0x7F);
#endif
    GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
#endif
    w = GOBJ_WORK(g);
    frames = (int)t;
    w->pinchFrames = frames;
    w->pinchPosX = buf[0];
    w->pinchPosY = buf[1];
    w->pinchPosZ = buf[2];
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    pos[0] = test_CURRENTROOT(boyGObj)[0];
    pos[1] = test_CURRENTROOT(boyGObj)[1];
    pos[2] = test_CURRENTROOT(boyGObj)[2];
#ifdef VERSION_AUG6
    InsertCamera_SetNoraml(cam, pos, frames);
#else
    InsertCamera_SetNoraml(cam, pos, frames, 0);
#endif
}

void *gopp_subBoyControl;
#endif

#ifdef VERSION_NTSC
void actBoyStart(GObj *self)
{
    char *work;
    void *g;

    girlEscortedInStage = BOYINFO.escort;
    BOYINFO.escort = 0;

    ((int *)boyInfo)[4] = -1;

    ableBoyControl = 0;
    startWithGirl = 0;
    startWaitCancel = 0;
    startOnSofa = 0;
    sitLayoutDone = 0;

    sitCount = 0;
    debug_StdPrintfDummy("actBoyStart:%p\n", self);

    work = (char *)actInitialize(self);
    *(void **)(work + 0x67C) = attrWallHit;

    GetRootPosition(work + 0x100, (void *)self);

    actInitialize_ext_charcter(self);
    actInitialize_only_charcter((char *)self);
    actInitialize_geo(self);

    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(31) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
    ACTGame_LwsEffectInit(self);

    *(int *)(work + 0x170) = 0;
    *(int *)(work + 0x174) = 0;

    gopp_subBoyControl = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init((int **)self);

    _ACTWait(1);

    CurrentTargetGObj = (void *)self;

    *(float *)(work + 0x1D0) = _ACTGame_GetParamF(17);
    *(int *)(work + 0x44) = 0;

    if (BOYINFO.boyID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
        if (g != 0) {
            PickupWeapon(g, (void *)self, 0x16);
            *(void **)(work + 0x140) = g;
            if (BOYINFO.torch) {
                LightTorchOnOfWeaponWithNoSE(g);
            }
        } else {
            BOYINFO.boyID = 0;
        }
    }

    if (BOYINFO.girlID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.girlID);
        if (g != 0) {
            ACTSendMailCorrect(self, 53);
            *(void **)(work + 0x174) = *(void **)(work + 0x144) = g;
        } else {
            BOYINFO.girlID = 0;
        }
        startWithGirl = 1;
    }

    if (BOYINFO.layoutID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.layoutID);
        if (g != 0) {
            Vec16 p0 = {{0.0f, 0.0f, -50.0f, 1.0f}};
            Vec16 p1 = {{0.0f, 0.0f, 50.0f, 1.0f}};
            ClipWork cw;

            CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(g)->nodeMtx);
            MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
            sceVu0ApplyMatrix(cw.pt[0], MatrixDrive_GetMatrix(), &p0);
            sceVu0ApplyMatrix(cw.pt[1], MatrixDrive_GetMatrix(), &p1);
            cw.radius = 0.0f;
            ClipWall(&cw);
            if (cw.wall.elem == 0) {
                /* "!!! cannot find the sofa's wall !!!" */
                debug_StdPrintfDummy("！！！ソファの壁を見付けることができません！！！\n");
            } else {
                startOnSofa = 1;
                sitLayoutDone = 1;
                sofaWallHit.o = cw.wall.o;
                sofaWallHit.elem = cw.wall.elem;
                scpBoyControlReadDisable = 0;
                ActSendMail_WithAdditionalData((void *)self, 54, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 54, girlGObj, &sofaWallHit);
                }
            }
        } else {
            BOYINFO.layoutID = 0;
        }
    }

    startWaitCancel = 0;

    *(void **)(work + 0xC0) = &actIntrList[67];

    actCreateSubThread(subBoyBrainMain, 20);
    gopp_subBoyControl = (void *)actCreateSubThread(subBoyControl, 21);
    actCreateSubThread(subBoyCollision, 21);
    actCreateSubThread(subCommonIdle, 21);

    *(void **)(work + 0xC4) = &actIntrList[72];
    ACTSendMailCorrect(self, 183);

    _ACTWait(1);

    if (BOYINFO.fire && girlGObj != 0) {
        iosOmSendMail(girlGObj, 60, self);
        debug_StdPrintfDummy("hand connect start\n");
    }
    _ACTWait(0);
}
#else
void actBoyStart(GObj *self)
{
    char *work;
    void *g;

    girlEscortedInStage = BOYINFO.escort;
    BOYINFO.escort = 0;

    ((int *)boyInfo)[4] = -1;

    ableBoyControl = 0;
    startWithGirl = 0;
    startWaitCancel = 0;
    startOnSofa = 0;
    sitLayoutDone = 0;

    sitCount = 0;
    debug_StdPrintfDummy("actBoyStart:%p\n", self);

    work = (char *)actInitialize(self);
#ifdef VERSION_AUG6
    *(void **)(work + 0x67C) = attrWallHit;

    GetRootPosition(work + 0xF0, (void *)self);
#else
#ifdef VERSION_JUN26
    *(void **)(work + 0x65C) = attrWallHit;

    GetRootPosition(work + 0xF0, (void *)self);
#else
    *(void **)(work + 0x68C) = attrWallHit;

    GetRootPosition(work + 0x110, (void *)self);
#endif
#endif

    actInitialize_ext_charcter(self);
    actInitialize_only_charcter((char *)self);
    actInitialize_geo(self);

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(27) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
#else
    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(31) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
#endif
    ACTGame_LwsEffectInit(self);

    *(int *)(work + 0x160) = 0;
    *(int *)(work + 0x164) = 0;
#else
    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(0x21) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
    ACTGame_LwsEffectInit(self);

    *(int *)(work + 0x180) = 0;
    *(int *)(work + 0x184) = 0;
#endif

    gopp_subBoyControl = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init((int **)self);

    _ACTWait(1);

    CurrentTargetGObj = (void *)self;

#ifdef VERSION_AUG6
    *(float *)(work + 0x1D0) = _ACTGame_GetParamF(17);
    *(int *)(work + 0x44) = 0;
#else
#ifdef VERSION_JUN26
    *(float *)(work + 0x1D0) = _ACTGame_GetParamF(14);
    *(int *)(work + 0x44) = 0;
#else
    *(float *)(work + 0x1E0) = _ACTGame_GetParamF(0x13);
    *(int *)(work + 0x48) = 0;
#endif
#endif

    if (BOYINFO.boyID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
        if (g != 0) {
#ifdef VERSION_JUN26
            PickupWeapon(g, (void *)self, 22);
            *(void **)(work + 0x130) = g;
            if (BOYINFO.torch) {
                LightTorchOnOfWeapon(g);
#else
            PickupWeapon(g, (void *)self, 0x16);
#ifdef VERSION_AUG6
            *(void **)(work + 0x130) = g;
#else
            *(void **)(work + 0x150) = g;
#endif
            if (BOYINFO.torch) {
                LightTorchOnOfWeaponWithNoSE(g);
#endif
            }
        } else {
            BOYINFO.boyID = 0;
        }
    }

#ifdef VERSION_JUN26
    /* the demo hands the boy the stick at layout 2702 when he comes in empty-handed */
    if (*(void **)(work + 0x130) == 0) {
        GObj *stick = isysGObjSearchFromObjLayoutID(2702);

        if (stick != 0) {
            Act *sub = GOBJ_ACT(self);

            PickupWeapon(stick, (void *)self, 22);
            sub->weapon = stick;
            BOYINFO.boyID = stick->labelId;
        }
    }
#endif
    if (BOYINFO.girlID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.girlID);
        if (g != 0) {
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 52);
            *(void **)(work + 0x164) = *(void **)(work + 0x134) = g;
#else
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 51);
            *(void **)(work + 0x164) = *(void **)(work + 0x134) = g;
#else
            ACTSendMailCorrect(self, 0x35);
            *(void **)(work + 0x184) = *(void **)(work + 0x154) = g;
#endif
#endif
        } else {
            BOYINFO.girlID = 0;
        }
        startWithGirl = 1;
    }

    if (BOYINFO.layoutID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.layoutID);
        if (g != 0) {
            Vec16 p0 = {{0.0f, 0.0f, -50.0f, 1.0f}};
            Vec16 p1 = {{0.0f, 0.0f, 50.0f, 1.0f}};
            ClipWork cw;

            CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(g)->nodeMtx);
            MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
            sceVu0ApplyMatrix(cw.pt[0], MatrixDrive_GetMatrix(), &p0);
            sceVu0ApplyMatrix(cw.pt[1], MatrixDrive_GetMatrix(), &p1);
            cw.radius = 0.0f;
            ClipWall(&cw);
            if (cw.wall.elem == 0) {
                /* "!!! cannot find the sofa's wall !!!" */
                debug_StdPrintfDummy("！！！ソファの壁を見付けることができません！！！\n");
            } else {
                startOnSofa = 1;
                sitLayoutDone = 1;
                sofaWallHit.o = cw.wall.o;
                sofaWallHit.elem = cw.wall.elem;
#ifdef VERSION_JUN26
                ActSendMail_WithAdditionalData((void *)self, 52, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 52, girlGObj, &sofaWallHit);
#else
                scpBoyControlReadDisable = 0;
#ifdef VERSION_AUG6
                ActSendMail_WithAdditionalData((void *)self, 53, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 53, girlGObj, &sofaWallHit);
#else
                ActSendMail_WithAdditionalData((void *)self, 0x36, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 0x36, girlGObj, &sofaWallHit);
#endif
#endif
                }
            }
        } else {
            BOYINFO.layoutID = 0;
        }
    }

    startWaitCancel = 0;

#ifdef VERSION_AUG6
    *(void **)(work + 0xB0) = &actIntrList[67];
#else
#ifdef VERSION_JUN26
    *(void **)(work + 0xB0) = &actIntrList[65];
#else
    *(void **)(work + 0xD0) = &actIntrList[74];
#endif
#endif

    actCreateSubThread(subBoyBrainMain, 20);
    gopp_subBoyControl = (void *)actCreateSubThread(subBoyControl, 21);
    actCreateSubThread(subBoyCollision, 21);
    actCreateSubThread(subCommonIdle, 21);
#ifdef VERSION_JUN26
    scpBoyControlReadDisable = 0;

    *(void **)(work + 0xB4) = &actIntrList[70];
    ACTSendMailCorrect(self, 177);
#else

#ifdef VERSION_AUG6
    *(void **)(work + 0xB4) = &actIntrList[72];
    ACTSendMailCorrect(self, 180);
#else
    *(void **)(work + 0xD4) = &actIntrList[79];
    ACTSendMailCorrect(self, 0xC7);
#endif
#endif

    _ACTWait(1);

    if (BOYINFO.fire && girlGObj != 0) {
#ifdef VERSION_AUG6
        iosOmSendMail(girlGObj, 59, self);
#else
#ifdef VERSION_JUN26
        iosOmSendMail(girlGObj, 58, self);
#else
        iosOmSendMail(girlGObj, 0x3F, self);
#endif
#endif
        debug_StdPrintfDummy("hand connect start\n");
    }
    _ACTWait(0);
}
#endif

#ifdef VERSION_JUN26
/* The walk order the boy is executing: sub->0x30 points at the request record
   the caller filled in, and actBoyReadyMove works on a private copy of it. */
typedef struct { /* field names derived */
    float pos[4];
    float dir[4];
    float range;
    int frames;
    int fix;
    int _2C;
} __attribute__((aligned(16))) BoyMoveOrder; /* derived name */

inline void actBoyReadyMove(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    BoyMoveOrder ord = *(BoyMoveOrder *)((char *)GOBJ_ACT(self)->intrData);

    while (1) {
        _ACTMotDirSmzDirect((void *)self, ord.dir);
        if (ord.fix) {
            sub->wish2.ll |= 0x20000000000LL;
            sub->wish2.ll |= 0x80000000LL;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(self, 240);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)self), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(self, 240);
        }
        _ACTWait(1);
    }
}

void *gopp_subBoyControl;

static inline unsigned char IsBoyStatus_SupportGB(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(girlGObj)->actMode;
    if (st < 103) {
        if (st >= 100) {
            return 1;
        }
    }
    return 0;
}

inline void afterBoySwim(GObj *volatile self)
{
    RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
    GOBJ_SUB(self)->root.filter = InitialColInfo;
    debug_StdPrintfDummy("after");
}

static int boyActUnusedWord = -1; /* derived name */
#endif

inline int CorrectStickInfo(void *dir, IosPadStick *stick)
{
    return correctStick(dir, stick);
}

inline void *GetBoyWeaponGObj(void)
{
    GObj *g = boyGObj;
    if (g != 0) {
        return (void *)GOBJ_ACT(g)->weapon;
    }
    return 0;
}

#ifdef VERSION_JUN26
inline void actBoyBHang(GObj *volatile self)
{
    _ACTWait(0);
}
#else
#ifdef VERSION_NTSC
inline void actBoyStand(GObj *volatile self)
{
    MotionDef *row = GOBJ_SUB(self)->ctrl.motion + motionKind;

    if ((row->flags.word >> 11) & 1) {
        ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.a.wall);
    }
    while (1) {
        _ACTWait(1);
    }
}
#else
inline void actBoyStand(GObj *volatile self)
{
    MotionDef *row = GOBJ_SUB(self)->ctrl.motion + motionKind;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    if (row->flags.word & 1) {
#else
#ifdef VERSION_AUG6
    if ((row->flags.word >> 11) & 1) {
#else
    if ((row->flags.word >> 8) & 1) {
#endif
#endif
        ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.a.wall);
    }
    while (1) {
        _ACTWait(1);
    }
}
#endif

inline void actBoyHang(GObj *volatile self)
{
    char *g = (char *)self;
    ACTAdjustPlane(self, &GOBJ_WORK(g)->intrReq.a.wall);
    _ACTWait(0);
}

inline void actBoyBHang(GObj *volatile self)
{
    char *g = (char *)self;
    ACTAdjustPlane(self, &GOBJ_WORK(g)->intrReq.a.wall);
    _ACTWait(0);
}
#endif

#ifdef VERSION_NTSC
inline void actBoyHangBefore(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.b.wall);
    GOBJ_WORK(self)->hangOrient[0] = sub->env.cliffOrient[0];
    GOBJ_WORK(self)->hangOrient[1] = sub->env.cliffOrient[1];
    GOBJ_WORK(self)->hangOrient[2] = sub->env.cliffOrient[2];
    GOBJ_WORK(self)->cliffReq = sub->env.motOriReq.b;
    while (1) {
        ACTSendMailCorrect(self, 279);
        _ACTWait(1);
    }
}
#else
inline void actBoyHangBefore(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifndef VERSION_JUN26
    ACTAdjustPlane(self, &GOBJ_WORK(self)->intrReq.b.wall);
#endif
    GOBJ_WORK(self)->hangOrient[0] = sub->env.cliffOrient[0];
    GOBJ_WORK(self)->hangOrient[1] = sub->env.cliffOrient[1];
    GOBJ_WORK(self)->hangOrient[2] = sub->env.cliffOrient[2];
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    GOBJ_WORK(self)->cliffReq = sub->env.motOriReq.b;
    while (1) {
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 268);
#else
        ACTSendMailCorrect(self, 276);
#endif
#else
    GOBJ_WORK(self)->cliffReq.a = sub->env.motOriReq.b;
    while (1) {
        ACTSendMailCorrect(self, 0x128);
#endif
        _ACTWait(1);
    }
}
#endif

inline void actBoyBeslam(GObj *volatile self)
{
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    char *p = (char *)GOBJ_SUB(self) + 0x120;
#else
    char *p = (char *)GOBJ_SUB(self) + 0x130;
#endif

    sceVu0ScaleVector(p, test_CURRENTORIENT(beliftGirl), 30.0f);
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 295);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 292);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 283);
#else
        ACTSendMailCorrect(self, 0x13A);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

inline void actBoyRescueSrc(GObj *volatile self)
{
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 183);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 180);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 177);
#else
        ACTSendMailCorrect(self, 0xC7);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
inline void actBoySupportGBBegin(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 353, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 351);
        _ACTWait(1);
    }
}

static inline unsigned char IsBoyStatus_SupportGB(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(girlGObj)->actMode;
    if (st < 104) {
        if (st >= 101) {
            return 1;
        }
    }
    return 0;
}
#else
inline void actBoySupportGBBegin(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 333, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 331);
        _ACTWait(1);
    }
#else
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 349, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 347);
#else
            iosOmSendMail(girlGObj, 0x17D, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 0x17B);
#endif
        _ACTWait(1);
    }
}

static inline unsigned char IsBoyStatus_SupportGB(void) /* derived name */
{
    unsigned int st = (unsigned int)GOBJ_ACT(girlGObj)->actMode;
#ifdef VERSION_AUG6
    if (st < 104) {
        if (st >= 101) {
#else
    if (st < 0x6B) {
        if (st >= 0x68) {
#endif
            return 1;
        }
    }
    return 0;
#endif
}
#endif

inline void actBoySupportGBLoop(GObj *volatile self)
{
    while (1) {
        if (!IsBoyStatus_SupportGB()) {
#ifdef VERSION_NTSC
            ACTSendMailCorrect(self, 210);
#else
#ifdef VERSION_AUG6
            ACTSendMailCorrect(self, 207);
#else
#ifdef VERSION_JUN26
            ACTSendMailCorrect(self, 202);
#else
            ACTSendMailCorrect(self, 0xE2);
#endif
#endif
#endif
        }
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
inline void actBoySupportGBEnd(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 355, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 183);
        _ACTWait(1);
    }
}
#else
inline void actBoySupportGBEnd(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
#ifdef VERSION_AUG6
            iosOmSendMail(girlGObj, 351, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 180);
#else
#ifdef VERSION_JUN26
            iosOmSendMail(girlGObj, 335, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 177);
#else
            iosOmSendMail(girlGObj, 0x17F, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 0xC7);
#endif
#endif
        _ACTWait(1);
    }
}
#endif

inline void actBoySupportBGBegin(GObj *volatile self)
{
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 359);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 355);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 339);
#else
        ACTSendMailCorrect(self, 0x183);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

inline void actBoyDitch3mExec(GObj *volatile self)
{
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 370);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 366);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 350);
#else
        ACTSendMailCorrect(self, 0x190);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

#ifdef VERSION_NTSC
inline void actBoyHangG3M(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (0.1f < sub->stick.mag || (sub->pad.now & 0x10)) {
            ACTSendMailCorrect(self, 372);
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 375, isysCurrentGObj);
            }
        }
        _ACTWait(1);
    }
}
#else
inline void actBoyHangG3M(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

#ifdef VERSION_AUG6
    while (1) {
        if (0.1f < sub->stick.mag || (sub->pad.now & 0x10)) {
            ACTSendMailCorrect(self, 368);
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 371, isysCurrentGObj);
#else
#ifdef VERSION_JUN26
    while (1) {
        if (sub->pad.trg & 8) {
            ACTSendMailCorrect(self, 351);
            ACTGame_DisconnectHand();
        } else if (0.1f < sub->stick.mag) {
            ACTSendMailCorrect(self, 352);
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 355, isysCurrentGObj);
#else
    *(void **)((char *)sub + 0x18) = (void *)afterBoyHangG3M;
    while (1) {
        if (0.1f < sub->stick.mag || (sub->pad.now & 0x10)) {
            ACTSendMailCorrect(self, 0x192);
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 0x195, isysCurrentGObj);
#endif
#endif
            }
        }
        _ACTWait(1);
    }
}
#endif

inline unsigned char IsAbleBoyControl(void)
{
    return ableBoyControl;
}

inline void ACTSearchEnemy(void *self, int *out_id, float *out_vec)
{
    searchEnemy(self, out_id, out_vec);
}

inline void DeleteBoyWeapon(void)
{
    union { /* field names derived */
        float f[4];
        long long ll[2];
    } buf;

    Act *sub;

    if (boyGObj != 0) {
        sub = GOBJ_ACT(boyGObj);
        if ((void *)sub->weapon != 0) {
            ReleaseWeapon((void *)sub->weapon);
            memset(&buf, 0, 0x10);
            buf.f[0] = 10000000.0f;
#ifdef VERSION_JUN26
            SetDirectRootPosition((void *)sub->weapon, buf.f);
#else
            SetDirectRootPositionNoFitting((void *)sub->weapon, buf.f);
#endif
            gamesysObjInfoPosSetStage(sub->weapon, 0, 0, stage_no);
            *(int *)((char *)sub->weapon + 0x16C) = 0;
        }
        characterPacket[2] = 0;
        ((int *)boyInfo)[0] = 0;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        sub->weapon = 0;
#else
        *(void **)((char *)sub + 0x150) = 0;
#endif
    }
}

#ifdef VERSION_NTSC
inline int isLiftBoyEnable(void)
{
    unsigned int st = (unsigned int)GOBJ_ACT(boyGObj)->actMode;
    if (st >= 93) {
        return 1;
    }
    if (st < 91) {
        return 1;
    }
    return 0;
}
#else
inline int isLiftBoyEnable(void)
{
    unsigned int st = (unsigned int)GOBJ_ACT(boyGObj)->actMode;
#ifdef VERSION_AUG6
    if (st >= 93) {
        return 1;
    }
    if (st < 91) {
#else
#ifdef VERSION_JUN26
    if (st >= 92) {
        return 1;
    }
    if (st < 90) {
#else
    if (st >= 0x60) {
        return 1;
    }
    if (st < 0x5E) {
#endif
#endif
        return 1;
    }
    return 0;
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
}

inline void SetKidnapInfo(int enemyLabel, int targetLabel)
{
    characterPacket[5] = enemyLabel;
    characterPacket[6] = targetLabel;
}

inline void GetKidnapInfo(int *enemyLabel, int *targetLabel)
{
    *enemyLabel = characterPacket[5];
    *targetLabel = characterPacket[6];
}

inline void PrivInsCamSet(float *pos, float *tgt, GObj *track, int inFrames, int outFrames,
                          float inRate, float blend, unsigned char control)
{
    privInsCam.pos[0] = pos[0];
    privInsCam.pos[1] = pos[1];
    privInsCam.pos[2] = pos[2];
    privInsCam.tgt[0] = tgt[0];
    privInsCam.tgt[1] = tgt[1];
    privInsCam.tgt[2] = tgt[2];
    privInsCam.track = track;
    privInsCam.inFrames = inFrames;
    privInsCam.outFrames = outFrames;
    privInsCam.inRate = inRate;
    privInsCam.blend = blend;
    privInsCam.control = control;
    privInsCam.on = 1;
#endif
}
#endif

inline int IsBoyStatus_EnemyMustWait(void)
{
    Act *sub;
    unsigned int st;

    if (boyGObj == 0) {
#ifdef VERSION_AUG6
        debug_assert(__FILE__, LN(1731, 1724, 1724, 1543, 5123, 1731));
        __assert(__FILE__, LN(1731, 1724, 1724, 1543, 5123, 1731), "0");
#else
#ifdef VERSION_JUN26
        debug_assert(__FILE__, LN(1731, 1724, 1724, 1543, 1493, 4630));
        __assert(__FILE__, LN(1731, 1724, 1724, 1543, 1493, 4630), "0");
#else
#ifdef VERSION_NTSC
        debug_assert(__FILE__, LN(5211, 5211, 5211, 5211, 5211, 5211));
#else
        debug_assert(__FILE__, LN(5795, 5779, 5779, 5795, 5795, 5795));
#endif
        __assert(__FILE__, LN(5795, 5779, 5779, 5211, 5795, 5795), "0");
#endif
#endif
        return 0;
    }
    sub = GOBJ_ACT(boyGObj);
    st = (unsigned int)sub->actMode;
    if (st >= 0x13) {
        if (st >= 0x16) {
            if (st < 0x18) {
                return 1;
            }
        } else if (sub->enemy->stoneLevel != 0) {
            return 1;
        }
    }
    if (st == 0x15 || 0 < ((ActWork *)sub->work)->downTimer) {
        return 1;
    }
    return 0;
}

inline int IsGirlEscortedInNextStage(void)
{
    return (int)((unsigned char)((unsigned long long)boyInfo[1] >> 35)) & 1;
}

inline unsigned char IsGirlEscortedInCurrentStage(void)
{
    return girlEscortedInStage;
}

inline int GetSaveSofaLayoutID(void)
{
    int *a = (int *)boyGObj;
    int *b = (int *)girlGObj;
    int *pa, *pb, *r;
    int v;
    if (a == 0)
        goto err;
    if (b == 0)
        goto err;
    pa = (int *)a[0x164 / 4];
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    v = pa[0x30 / 4];
#else
    v = pa[0x34 / 4];
#endif
    if (v != 0x2D)
        goto err;
    pb = (int *)b[0x164 / 4];
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (pb[0x30 / 4] != v)
        goto err;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    r = (int *)pa[0x140 / 4];
#else
    r = (int *)pa[0x150 / 4];
#endif
#else
    if (pb[0x34 / 4] != v)
        goto err;
    r = (int *)pa[0x160 / 4];
#endif
    return r[2];
err:
    return -1;
}

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifndef VERSION_JUN26
inline void OnGirlEscortFlag(void)
{
    boyInfo[1] |= 0x800000000LL;
}
#endif
#else
inline void OnGirlEscortFlag(void)
{
    boyInfo[1] |= 0x800000000LL;
}

inline void SetBoyWeaponGObj(void *w)
{
    if (boyGObj != 0 && w != 0) {
        SwapBoyWeapon(0, w, boyGObj);
    }
}

#ifndef VERSION_NTSC
inline int IsBoyStatus_NotDanger(void)
{
    unsigned int st = (unsigned int)GOBJ_ACT(boyGObj)->actMode;
    if (st < 0x17) {
        if (st >= 0x14) {
            return 1;
        }
    }
    return 0 < GOBJ_WORK(boyGObj)->downTimer;
}
#endif
#endif

inline int GetEfStageCameraTargetID(void)
{
    if (BOYEFSTAGE[0]) {
        return *(int *)(BOYEFSTAGE + 4);
    }
    return 0;
}

inline int IsBackFromEfStage(void)
{
    return BOYEFSTAGE[0];
}

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
inline int PrivInsCamChk(void)
{
    return privInsCam.on != 0;
}

inline unsigned char PrivInsCamChk_Control(void)
{
    return privInsCam.control;
}
#endif

inline int *GetbufpCharacterPacket(void)
{
    return characterPacket;
}

#ifdef VERSION_NTSC
inline int GetsizeCharacterPacket(void)
{
    return 24;
}

inline void MakeCharacterPacket(void)
{
    char *pkt = (char *)characterPacket;
    Act *sub;
    char *g;

    *(BoyKidnapWork *)characterPacket = characterPacketDefault;
    if (boyGObj != 0) {
        sub = GOBJ_ACT(boyGObj);
        if (sub->weapon != 0) {
            *(int *)(pkt + 0x8) = sub->weapon->labelId;
        }
        if (sub->curItem != 0) {
            *(int *)(pkt + 0xC) = sub->curItem->labelId;
        }
        if (sub->actMode == 45) {
            *(int *)(pkt + 0x10) = *(int *)(sub->flags150.sofa + 0x8);
        }
        g = (char *)girlGObj;
        if (g != 0 && GOBJ_ACT(g)->actMode == 45) {
            *(int *)(pkt + 0x14) |= 1;
        }
        BoyInfoUpdate_StageChange();
        *(int *)(pkt + 0x14) =
            (*(int *)(pkt + 0x14) & ~0x10000) |
            (((int)((unsigned char)((unsigned long long)boyInfo[1] >> 34)) & 1) << 16);
        *(unsigned char *)(pkt + 0x15) =
            (int)((unsigned char)((unsigned long long)boyInfo[1] >> 33)) & 1;
        *(CharPos *)pkt = BOYINFO.f50;
    }
}
#else
inline int GetsizeCharacterPacket(void)
{
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    return 24;
#else
    return 32;
#endif
}

inline void MakeCharacterPacket(void)
{
    char *pkt = (char *)characterPacket;
    Act *sub;
    char *g;

    *(BoyKidnapWork *)characterPacket = characterPacketDefault;
    if (boyGObj != 0) {
        sub = GOBJ_ACT(boyGObj);
        if (sub->weapon != 0) {
            *(int *)(pkt + 0x8) = sub->weapon->labelId;
        }
        if (sub->curItem != 0) {
            *(int *)(pkt + 0xC) = sub->curItem->labelId;
        }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        if (sub->actMode == 45) {
            *(int *)(pkt + 0x10) = *(int *)(sub->flags150.sofa + 0x8);
        }
        g = (char *)girlGObj;
        if (g != 0 && GOBJ_ACT(g)->actMode == 45) {
            *(int *)(pkt + 0x14) |= 1;
        }
        BoyInfoUpdate_StageChange();
        *(int *)(pkt + 0x14) =
            (*(int *)(pkt + 0x14) & ~0x10000) |
            (((int)((unsigned char)((unsigned long long)boyInfo[1] >> 34)) & 1) << 16);
        *(unsigned char *)(pkt + 0x15) =
            (int)((unsigned char)((unsigned long long)boyInfo[1] >> 33)) & 1;
#else
        if (sub->actMode == 0x2D) {
            *(int *)(pkt + 0x10) = *(int *)(sub->sofa + 0x8);
        }
        g = (char *)girlGObj;
        if (g != 0 && GOBJ_ACT(g)->actMode == 0x2D) {
            *(int *)(pkt + 0x1C) |= 1;
        }
        BoyInfoUpdate_StageChange();
        *(int *)(pkt + 0x1C) =
            (*(int *)(pkt + 0x1C) & ~0x10000) |
            (((int)((unsigned char)((unsigned long long)boyInfo[1] >> 34)) & 1) << 16);
        *(unsigned char *)(pkt + 0x1D) =
            (int)((unsigned char)((unsigned long long)boyInfo[1] >> 33)) & 1;
#endif
        *(CharPos *)pkt = BOYINFO.f50;
    }
}
#endif

inline void BoyInfoUpdate_StageChange(void)
{
    GObj *g = boyGObj;
    Act *sub = GOBJ_ACT(g);
    GObj *w;
    int x;

    BOYINFO.torch = 0;
    w = sub->weapon;
    if (w != 0) {
        x = ACTGame_isWeaponEnableCatchfire(w);
        if (x != 0) {
            if (IsTorchLightOn((GObj *)x)) {
                BOYINFO.torch = 1;
            }
        }
    }
    BOYINFO.fire = 0;
    if (ACTGame_FLAG_TETSUNAGI()) {
        BOYINFO.fire = 1;
    }
}

#if defined(VERSION_NTSC) || defined(VERSION_JUN26)
typedef struct {          /* field names derived */
    CharPos pos;          /* 0x00 */
    int boyID;            /* 0x08 */
    int girlID;           /* 0x0C */
    int f10;              /* 0x10 */
    unsigned int b1C : 8; /* 0x14 */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x16 */
} CharacterPacket;         /* derived name */
#else
#ifdef VERSION_AUG6
inline int ACTChkAttackIgnore_BOY(GObj *self)
{
    Act *s = GOBJ_ACT(self);
    if (s->actMode == 53 ||
        (((ActWork *)s->work)->leverTimer != 0 && scpBoyControlReadDisable != 0)) {
        return 1;
    }
    return 0;
}

typedef struct {          /* field names derived */
    CharPos pos;          /* 0x00 */
    int boyID;            /* 0x08 */
    int girlID;           /* 0x0C */
    int f10;              /* 0x10 */
    unsigned int b1C : 8; /* 0x14 */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x16 */
} CharacterPacket;         /* derived name */
#else
typedef struct { /* field names derived */
    CharPos pos; /* 0x00 */
    int boyID;   /* 0x08 */
    int girlID;  /* 0x0C */
    int f10;     /* 0x10 */
    int f14;
    int f18;
    unsigned int b1C : 8; /* 0x1C */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x1E */
} CharacterPacket;         /* derived name */
#endif
#endif

inline void ReadCharacterPacket(void)
{
    CharacterPacket *p = (CharacterPacket *)characterPacket;

    BOYINFO.boyID = p->boyID;
    BOYINFO.girlID = p->girlID;
    BOYINFO.layoutID = p->f10;
    BOYINFO.bit32 = p->b1C;
    BOYINFO.fire = p->b1D;
    BOYINFO.torch = p->h1E;
    BOYINFO.f50 = p->pos;
}

inline void ACTSearchGObj(void *self, int kind, int maxDeg, int *out_id, float *out_vec,
                          float thresh)
{
    searchGObj(self, kind, maxDeg, out_id, out_vec, thresh);
}

#ifndef VERSION_JUN26
inline void afterBoySwim(GObj *volatile self)
{
    RequestChangeHandMode(self, 0, 3, 0, 0, 0, 0);
    GOBJ_SUB(self)->root.filter = InitialColInfo;
    debug_StdPrintfDummy("after");
}

static int boyActUnusedWord = -1; /* derived name */
#endif

inline void actBoyJump(GObj *volatile self)
{
    while (1) {
#ifdef VERSION_NTSC
        ACTSendMailCorrect(self, 176);
#else
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 174);
#else
#ifdef VERSION_JUN26
        ACTSendMailCorrect(self, 171);
#else
        ACTSendMailCorrect(self, 0xBD);
#endif
#endif
#endif
        _ACTWait(1);
    }
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void afterBoyTakeWeapon(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SwapBoyWeapon(BOYINFO.weapon, BOYINFO.nextWeapon, (void *)self);
    sub->weapon = BOYINFO.nextWeapon;
}

inline void afterCommonItem(GObj *volatile self) {}
#else
inline void afterBoyTakeWeapon(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SwapBoyWeapon(BOYINFO.weapon, BOYINFO.nextWeapon, (void *)self);
    *(void **)((char *)sub + 0x150) = BOYINFO.nextWeapon;
}

inline void afterBoyHangG3M(int x)
{
    volatile int local = x;
}

inline void afterBoyRescueGirlBhang(GObj *volatile self)
{
    ACTGame_DisconnectHand();
}
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline void subBoyBrainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        _ACTWait(1);
    }
}
#else
inline void subBoyBrainMain(int arg)
{
    volatile int local = arg;
    while (1) {
        _ACTWait(1);
    }
}
#endif

inline void SetBoyInfo(GObj *weapon, GObj *item)
{
    int n;
    int i;
    if (weapon != 0) {
        ((int *)boyInfo)[0] = weapon->labelId;
    } else {
        ((int *)boyInfo)[0] = 0;
    }
    i = 0;
    n = 1;
    if ((int)item != i) {
        ((int *)boyInfo)[n] = item->labelId;
    } else {
        ((int *)boyInfo)[n] = i;
    }
}

#ifdef VERSION_NTSC
inline void GetBoyRootPositionForCamera(float *out, GObj *gobj)
{
    float buf[4];
    GObj *g = boyGObj;
    Act *sub;

    sub = GOBJ_ACT(g);
    GetRootPosition(buf, g);
    if (_DistSqGV(buf, &sub->camRootX) < 40000.0f) {
        out[0] = sub->camRootX;
        out[1] = sub->camRootY;
        out[2] = sub->camRootZ;
    } else {
        GetRootPosition(&sub->camRootX, g);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}
#else
inline void GetBoyRootPositionForCamera(float *out, GObj *gobj)
{
    float buf[4];
    GObj *g = boyGObj;
    Act *sub;

    sub = GOBJ_ACT(g);
    GetRootPosition(buf, g);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (_DistSqGV(buf, &sub->camRootX) < 40000.0f) {
#else
    if (_DistSqGV(buf, (char *)sub + 0x110) < 40000.0f) {
#endif
        out[0] = sub->camRootX;
        out[1] = sub->camRootY;
        out[2] = sub->camRootZ;
    } else {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        GetRootPosition(&sub->camRootX, g);
#else
        GetRootPosition((char *)sub + 0x110, g);
#endif
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}
#endif

inline void Boy_Init(void)
{
    *(BoyWork *)boyInfo = boyInfoDefault;
    *(BoyKidnapWork *)characterPacket = characterPacketDefault;
}
