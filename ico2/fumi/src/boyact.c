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
    r = CHAINROW(self)->flags.bits.chainHang ? 300.0f : 100.0f;
    r2 = CHAINROW(self)->flags.bits.chainHang ? 90.0f : 120.0f;

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

    if ((rside != 0 || lside != 0) && (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
        RequestChangeHandMode(self, 0, 2, 1, g, 0, w);
        RequestChangeHandMode(self, 1, 2, 1, g, 0, w);
    } else {
        RequestChangeHandMode(self, 0, 2, 0, 0, 0, 0);
        RequestChangeHandMode(self, 1, 2, 0, 0, 0, 0);
    }

    if ((rside != 0 || lside != 0) &&
        motionKind[GOBJ_SUB(self)->ctrl.motion].flags.bits.chainIkRate) {
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x44C))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x454))->f = 0.8f;
        ((BoyVal *)((char *)GOBJ_SUB(self) + 0x458))->f = 0.8f;
    }

    if (rside != 0 || lside != 0) {
        _ACTCharStatus_Set(self, 14, -1.0f, (int)g);
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
        for (o = isysGObjSearchFromObjKindID_begin(42); o != 0;
             o = isysGObjSearchFromObjKindID_next(o)) {
            if (*(int *)((char *)o + 0x16C) != 0) {
                GetCageChainPoint(cp, ce, o);
                if (_DistxzSqGV(test_CURRENTROOT(self), cp) < 4.9e+03f && ce[1] > pos[1]) {
                    cage = o;
                    break;
                }
            }
        }
        if (cage != 0) {
            GetRootPositionHandExtra(self, hx);
            GetCageChainPoint(cp2, ce2, cage);
            if (cp2[1] + 150.0f < hx[1]) {
                ACTSendMailCorrect(self, 156);
                ACTSendMailCorrect(self, 155);
            }
        }
    }
}

/* dir: subBoyCollision passes the motion direction (sub + 0x120); this body
   never reads it */
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
        iosOmSendMail(girlGObj, 87, isysCurrentGObj);
    }
}

inline void actBoyHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand50\n");
    sub->actMode = 78;
    sub->after = (void *)afterBoyHand50;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error flg get\n");
    while (1) {
        ACTSendMailCorrect(self, 87);
        _ACTWait(1);
    }
}

void motBoyHand50(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter motBoyHand50\n");
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 83, isysCurrentGObj);
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
            iosOmSendMail(girlGObj, 84, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(45);
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 65);
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
        iosOmSendMail(girlGObj, 92, isysCurrentGObj);
    }
}

inline void actBoyHand100(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand100\n");
    sub->actMode = 79;
    sub->after = (void *)afterBoyHand100;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
        ACTSendMailCorrect(self, 92);
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
                iosOmSendMail(girlGObj, 88, isysCurrentGObj);
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
    ACTSendMailCorrect(self, 92);
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->motReq = SetMotionRequest((void *)self, 88, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 139, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 89, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 88, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 91, isysCurrentGObj);
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 65);
        _ACTWait(1);
    }
}

inline void afterBoyHand200(GObj *volatile self)
{
    debug_StdPrintfDummy("boy after func\n");
    if (girlGObj != 0) {
        iosOmSendMail(girlGObj, 97, isysCurrentGObj);
    }
}

inline void actBoyHand200(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyHand200\n");
    sub->actMode = 80;
    sub->after = (void *)afterBoyHand200;
    sub->readyFlags = 0;
    while ((sub->readyFlags & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
        ACTSendMailCorrect(self, 97);
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
                iosOmSendMail(girlGObj, 93, isysCurrentGObj);
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
    ACTSendMailCorrect(self, 97);
    debug_StdPrintfDummy("%s sync error\n", (void *)self == boyGObj ? "boy" : "girl");
done:
    while (GOBJ_SUB(self)->ctrl.motion < 0 || 2 <= GOBJ_SUB(self)->ctrl.motion) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
    sub->motReq = SetMotionRequest((void *)self, 139, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 94, isysCurrentGObj);
        }
        if (sub->readyFlags & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->motReq = SetMotionRequest((void *)self, 89, sub->env.motOriReq);
    while ((*(int *)((char *)sub->motReq + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 96, isysCurrentGObj);
        }
        if (sub->readyFlags & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->after = 0;
    while (1) {
        ACTSendMailCorrect(self, 65);
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

void handoff_heroin(void) /* derived name */
{
    void *boy = boyGObj;

    if (girlGObj != 0) {
        if (GOBJ_SUB(girlGObj)->root.hand0.mode == 6) {
            iosOmSendMail(girlGObj, 57, isysCurrentGObj);
            ACTSendMailCorrect(boy, 226);
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

typedef struct { /* field names derived */
    int a;
    int b;
} CharPos; /* derived name */

/* the wall hit actBoyStart hands the boy and the girl with mail 0x36: the
   ClipWall work record's wall pair and the wall it hit */
static WallCfg sofaWallHit; /* derived name */

/* the attribute wall hit, three words in a VU0 int vector: the object's .bss
   is 16-byte aligned in this build (it opens at 0x6F5160, 8 bytes past
   act-parallel-control's run) */
static sceVu0IVECTOR attrWallHit; /* derived name */

static long long boyInfo[12]; /* derived name */

static void CheckCollisionAttr(void *self)
{
    Sub15C *stage = GOBJ_SUB(self);
    int i;
    int flag = 1;
    int esc = 0;

    if (_ACTGame_GetParamF(1) < stage->ctrl.groundHeight) {
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
                    RequestStageChange(i, boyGObj, girlGObj, 1.0f, 16.0f);
                } else {
                    RequestStageChange(i, boyGObj, 0, 1.0f, 16.0f);
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

typedef struct { /* field names derived */
    long long w[12];
} BoyWork; /* derived name */

typedef struct { /* field names derived */
    int w[6];
} BoyKidnapWork; /* derived name */

static BoyWork boyInfoDefault = {{0, 0, 0xFFFFFFFF}}; /* derived name */

static BoyKidnapWork characterPacketDefault = {{0}}; /* derived name */

static BgaEntry boyBgaTable[] = {
    /* derived name */
    {380, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {381, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {385, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {386, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
}; /* derived name */

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
            obj = isysGObjSearchFromObjKindID_begin(45);
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
    debug_assert(__FILE__, 1292);
    __assert(__FILE__, 1292, "0");
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

static void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (startWithGirl != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
        SetDirectRootPosition(self, buf);
    }
    if (gflagChk(332)) {
        gflagOff(332);
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
    ACTGame_SetMotionPlaySpeedRatio_Reserve(g, ratio, 7);
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

int test_rope_slope = 0;

float add_rope_val = 0.0f;

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int InsertCameraWorkingFlag;
/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differ) */
extern int FixViewInGameCameraFlag;

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
    int slow;
    float d;
    float dist;
    int dbg = 0; /* local debug switch, see the test after the stick loop */

    memset(stick, 0, 16);
    c0 = 0;
    c1 = 0;
    c2 = 0;
    memset(wish, 0, 16);
    iosPadConnect(&s->pad, 0, 0, &iosPadConfCustom);
    boyPad = &s->pad;
    E3_StageStartBoy((void *)self);
    layoutActPushStartNew = 0;
    while (1) {
        for (;;) {
            if (((int)(s->flags18.ll >> 42) & 1) == 0) {
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
                        ACTSendMailCorrect(self, 177);
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
                snapStickToCamera(stick, wish, sabs, cam);
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
        {
            static int slowWalkTimer = 0; /* derived name */

            slow = 0;
            if (s->actMode == 1) {
                if (GOBJ_SUB(self)->ctrl.motion == 0 || GOBJ_SUB(self)->ctrl.motion == 1 ||
                    GOBJ_SUB(self)->ctrl.motion == 2) {
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
            ACTSendMailCorrect(self, 177);
            break;
        case 2:
            ACTSendMailCorrect(self, 163);
            break;
        case 3:
            ACTSendMailCorrect(self, 168);
            break;
        case 29:
            if (s->pad.trg & 0x40) {
                if (100.0f < GetDifferenceFromLowerField(self, 44)) {
                    ACTSendMailCorrect(self, 267);
                } else {
                    ACTSendMailCorrect(self, 202);
                }
            }
            if ((0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) ||
                (s->pad.trg & 0x10)) {
                ACTSendMailCorrect(self, 177);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 26:
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                GOBJ_WORK(self)->fallDir[0] = s->dir[0];
                GOBJ_WORK(self)->fallDir[1] = s->dir[1];
                GOBJ_WORK(self)->fallDir[2] = s->dir[2];
                ACTSendMailCorrect(self, 282);
            }
            break;
        case 27: {
            int back = 0;

            if (0.1f < s->stick.mag) {
                int r = _RotyGV(stick, GOBJ_WORK(self)->hangOrient);

                r = r < 0 ? -r : r;
                back = r >= 136;
                if (back && GetMotionFrameFlag1((void *)self)) {
                    ACTSendMailCorrect(self, 276);
                }
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
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
            break;
        }
        case 28:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 202);
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 30:
            if (s->pad.trg & 0x40) {
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
            break;
        case 31:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
                ACTSendMailCorrect(self, 300);
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 33:
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 202);
            }
            break;
        case 40:
            if ((s->pad.trg & 0x10) || s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 274);
            }
            if (s->pad.trg & 0x40) {
                ACTSendMailCorrect(self, 202);
            }
            break;
        case 34:
            if (s->pad.trg & 0x40) {
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
            break;
        case 35:
            if (s->pad.trg & 0x40) {
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
                    ACTSendMailCorrect(self, 119);
                    break;
                }
                if (front && 0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                    ACTSendMailCorrect(self, 118);
                    break;
                }
                ACTSendMailCorrect(self, 301);
                break;
            }
            ACTSendMailCorrect(self, 301);
            ACTSendMailCorrect(self, 177);
            break;
        }
        case 53:
            if ((60 - systemStatus[0] * 10) / systemStatus[1] * 90 / 60 > s->modeFrame) {
                ACTSendMailCorrect(self, 124);
                break;
            }
            ACTSendMailCorrect(self, 301);
            ACTSendMailCorrect(self, 177);
            break;
        case 54:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag) {
                    ACTSendMailCorrect(self, 124);
                    if (s->pad.now & 8) {
                        ACTSendMailCorrect(self, 60);
                    }
                } else {
                    ACTSendMailCorrect(self, 301);
                }
            } else {
                ACTSendMailCorrect(self, 177);
            }
            break;
        case 32:
        case 38: {
            /* the actor, read at the head of this arm; the DEBUG build's report
               reads it */
            GObj *obj = self;

            if (((int)(*(unsigned long long *)((char *)GOBJ_ACT(self)->enemy + 0x298) >> 1) & 1) &&
                !(s->stick.y - 128 < 101)) {
                ACTSendMailCorrect(self, 296);
            } else if ((*(int *)((char *)GOBJ_ACT(self)->enemy + 0x298) & 1) &&
                       s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 295);
            } else {
                ACTSendMailCorrect(self, 301);
            }
            if (s->pad.trg & 8) {
                ACTSendMailCorrect(self, 60);
            }
#ifdef DEBUG
            scePrintf("boy %08x stick %d\n", obj, s->stick.y - 128);
#endif
            break;
        }
        case 43:
            if (0.95f < s->stick.mag) {
                ACTSendMailCorrect(self, 198);
                break;
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 44:
            if (0.95f < s->stick.mag) {
                ACTSendMailCorrect(self, 197);
                break;
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 49:
            if (s->pad.now & 0x20) {
                switch (s->pushDir) {
                case 1:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                        ACTSendMailCorrect(self, 297);
                    } else {
                        ACTSendMailCorrect(self, 301);
                    }
                    break;
                case -1:
                    if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 298);
                    } else {
                        ACTSendMailCorrect(self, 301);
                    }
                    break;
                default:
                    if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
                        ACTSendMailCorrect(self, 297);
                    } else if (0.1f < s->stick.mag &&
                               !((unsigned int)(s->stick.angle + 89) < 179)) {
                        ACTSendMailCorrect(self, 298);
                    } else {
                        ACTSendMailCorrect(self, 301);
                    }
                    break;
                }
            } else {
                ACTSendMailCorrect(self, 301);
                ACTSendMailCorrect(self, 177);
            }
            break;
        case 51:
            if (s->pad.now & 0x20) {
                if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 90) < 181) {
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
                break;
            }
            if (0.1f < s->stick.mag &&
                !(0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20)))) {
                ACTSendMailCorrect(self, 168);
                break;
            }
            if (0.1f < s->stick.mag && (s->stick.mag < 0.99f || (s->pad.now & 0x20))) {
                ACTSendMailCorrect(self, 163);
                break;
            }
            ACTSendMailCorrect(self, 301);
            break;
        case 58:
            switch (GetChainSlope()) {
            case 0:
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
            break;
        case 60:
            if (!(s->stick.y - 128 < 101)) {
                ACTSendMailCorrect(self, 202);
            }
            if (s->stick.y - 128 < -100) {
                ACTSendMailCorrect(self, 143);
            }
            if (s->pad.now & 0x20) {
                ACTSendMailCorrect(self, 144);
            }
            break;
        case 20:
        case 21:
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 57, isysCurrentGObj);
            }
            break;
        case 104:
            if (s->pad.now & 8) {
                break;
            }
            ACTSendMailCorrect(self, 177);
            break;
        case 101:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 332);
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 202);
            }
            break;
        case 45:
            if (0.1f < s->stick.mag) {
                ACTSendMailCorrect(self, 108);
                ACTSendMailCorrect(self, 107);
            }
            if (s->pad.now & 8) {
                ACTSendMailCorrect(self, 107);
                brainAddLevelGirl(10.0f);
            }
            if (s->modeFrame == 0 && ((int)(s->flags18.ll >> 36) & 1)) {
                brainAddLevelGirl(1000.0f);
            }
            break;
        case 23:
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle + 45) < 91) {
                ACTSendMailCorrect(self, 297);
                break;
            }
            if (0.1f < s->stick.mag && !((unsigned int)(s->stick.angle + 134) < 269)) {
                ACTSendMailCorrect(self, 298);
                break;
            }
            if (0.1f < s->stick.mag && (unsigned int)(s->stick.angle - 46) < 89) {
                ACTSendMailCorrect(self, 299);
                break;
            }
            if (0.1f < s->stick.mag && !(s->stick.angle < -134) && s->stick.angle < -45) {
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
            break;
        }
        _ACTWait(1);
    }
}

/* subBoyControl's countdown, set to a fifth of a second of frames */
static int boyControlWait = 0; /* derived name */

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
        BOYINFO.f40 = row->rot[0];
        BOYINFO.f44 = row->rot[1];
        BOYINFO.f48 = row->rot[2];
    }
}

static void PutWeapon(void)
{
    char *p = (char *)boyInfo;
    struct MotRoot *root;

    if (*(void **)(p + 0x20) != 0) {
        root = &GOBJ_SUB(*(void **)(p + 0x20))->root;
        InitMotionGeoInfo(
            root, *(float *)(p + 0x30), *(float *)(p + 0x34), *(float *)(p + 0x38), 0.0f,
            -((int)(_GetDirection(test_CURRENTORIENT(boyGObj)) / 3.1415927f * 180.0f) * 3.1415927f /
              180.0f),
            0.0f);
        UpdateRootMatrix(*(void **)(p + 0x20));
    }
}

/* a static helper inlined into afterBoyTakeWeapon */
static inline int SwapBoyWeapon(void *oldW, void *newW, void *boy) /* derived name */
{
    Act *sub = GOBJ_ACT(boy);

    if (oldW == newW) {
        return 0;
    }
    if (newW == 0) {
        debug_assert(__FILE__, 2475);
        __assert(__FILE__, 2475, "next");
        return 0;
    }
    PickupWeapon(newW, boy, 22);
    ((int *)boyInfo)[0] = *(int *)((char *)newW + 0x8);
    sub->weapon = newW;

    if (oldW == 0) {
        return 1;
    }
    ReleaseWeapon(oldW);
    PutWeapon();
    gamesysObjInfoPosSetStage(oldW, 0, 0, stage_no);
    debug_StdPrintfDummy("%d -> %d\n", *(int *)((char *)oldW + 0x8), *(int *)((char *)newW + 0x8));
    return 1;
}

/* the object kinds the proximity scan below walks, terminated by -1 */
typedef struct { /* field names derived */
    int id[4];
} ObjKindList; /* derived name */

static const ObjKindList collisionKinds = {{4, 45, 59, -1}}; /* derived name */

/* returns float * here, int * in camera-root.h */
extern float *GetCurrentCameraSet2(void);

/* the character packet, 24 bytes (Boy_Init copies three doublewords); the
   object's .bss ends after it at 0x6F51F8 */
static int characterPacket[6]; /* derived name */

/* as in camera-root.h, which this TU does not include (GetCurrentCameraSet2 differs) */
extern void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri);

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

void subBoyCollision(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    int camOn;
    int hang;
    int hangBit;
    int dbg = 0; /* local debug switch, see the test after the helper's SetRootPosition */

    while ((int)sub->motReq == 0) {
        _ACTWait(1);
    }
    if (200.0f < GetDifferenceFromLowerField(self, 44)) {
        ACTSendMailCorrect(self, 7);
    }
    while (1) {
        float vec[4];

        camOn = 0;
        if (0 < GOBJ_WORK(self)->pinchFrames) {
            _ACTCharStatus_Set((void *)self, 27, -1.0f, 0);
            GOBJ_WORK(self)->pinchFrames -= 1;
        }
        findChainInJump((void *)self);
        CheckCollisionAttr((void *)self);
        ACTGame_CommonLoop((void *)self);
        BoyBgaManager(self, 380, (char *)GOBJ_ACT(self)->enemy + 0x2A0);
        BoyBgaManager(self, 381, (char *)GOBJ_ACT(self)->enemy + 0x2A4);
        BoyBgaManager(self, 385, (char *)GOBJ_ACT(self)->enemy + 0x2B0);
        BoyBgaManager(self, 385, (char *)GOBJ_ACT(self)->enemy + 0x2AC);
        BoyBgaManager(self, 386, (char *)GOBJ_ACT(self)->enemy + 0x2A8);

        hangBit = ((int)(sub->flags18.ll >> 44) & 1);
        hang = 1;
        if (((int)(sub->flags20.ll >> 2) & 1) == 0) {
            hang = hangBit;
        }
        if (hang == 0) {
            if (0.1f < sub->stick.mag && sub->actMode != 110) {
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
                    float bodyori[4];
                    int cor;
                    int ry;

                    GetCorrectOrientOfChain(vec, (void *)self);
                    SetMotionDirection((void *)self, vec);
                    if (GetChainDirCorrectVal((void *)sub->chain, &cor) != 0) {
                        if (sub->stick.x - 0x80 < -100) {
                            ACTSendMailCorrect(self, 145);
                        }
                        if (100 < sub->stick.x - 0x80) {
                            ACTSendMailCorrect(self, 146);
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
                }
            }
            break;
        /* the table runs from 1, with this arm empty */
        case 1:
            break;
        }
        {
            float front[4];
            int work[4];
            int scr[4];
            int tgt[4];
            int ofs[4];

            if (((int)(sub->wish0.ll >> 44) & 1) == 0 || ((int)(sub->wish2.ll >> 12) & 1) == 0) {
                girlLookStarted = 0;
                girlLookInScreen = 0;
            }
            if (girlGObj != 0 && GOBJ_ACT(girlGObj)->actMode == 68) {
                sceVu0ScaleVector(front, test_CURRENTORIENT((void *)self), 200.0f);
                front[1] = 0.0f;
                sceVu0AddVector(front, test_CURRENTROOT((void *)self), front);
                _ACTLookTarget_Set((void *)self, 0, front, 1, 1);
            }
            if (((int)(sub->wish0.ll >> 44) & 1) && ((int)(sub->wish2.ll >> 12) & 1)) {
                if (girlLookStarted == 0) {
                    girlLookStarted = 1;
                    if (girlGObj != 0) {
                        girlLookInScreen =
                            (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(girlGObj))) ? 1 : 0;
                    }
                }
                if (girlGObj != 0) {
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
                    _ACTCharStatus_Set((void *)self, 13, near, 0);
                }
            }
            if (_ACTParaStatus_Check((void *)self, 3) || _ACTParaStatus_Check((void *)self, 2)) {
                if (_ACTParaStatus_Check((void *)self, 23)) {
                    _ACTParaStatus_Set((void *)self, 26);
                }
                if (_ACTParaStatus_Check((void *)self, 22)) {
                    _ACTParaStatus_Set((void *)self, 25);
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

                    for (g = isysGObjSearchFromObjKindID_begin(14); g != 0;
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
                        Camctrl_SetTarget(self, w, 1);
                        camOn = 1;
                    }
                }
            }
            if (camOn == 0 && girlGObj == 0) {
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
                    SetRootPosition(lo, work);
                    /* a local debug switch, off (see dbg in the declarations):
                       mark the helper position just set */
                    if (dbg) {
                        debug_NMarker((float *)work, 255, 0, 0, 100.0f);
                    }
                    Camctrl_SetTarget(self, lo, 1);
                }
            }
        }
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
        _ACTWait(1);
    }
}

inline void afterBoySwim(GObj *volatile self);

/* the record Act+0x650 points at, with the fields actBoyBelift and actBoySwim
   touch: the lift level and the lifted object, then the floating-box flag, the
   box GObj and the grip point, a four-float vector sceVu0ApplyMatrix takes
   whole (its w set to 1 before the apply) */
typedef struct { /* field names derived */
    char pad0[204];
    int liftLevel; /* 0xCC, the lift level actBoyBelift sets to 10 and clamps */
    char padD0[340];
    void *liftObj; /* 0x224, the object the boy lifts (actBoyBelift stores the girl) */
    char pad228[152];
    int holdBox; /* 0x2C0, set while the boy holds a floating box */
    GObj *box;   /* 0x2C4 */
    char pad2C8[8];
    float grip[4]; /* 0x2D0 */
} BoyExt;          /* derived name */

#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x650)) /* derived name */

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

    BOY_EXT(self)->holdBox = 0;
    sub->after = (void *)afterBoySwim;
    while (1) {
        GObj *box = BOY_EXT(self)->box;

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
            GetSkeltonPosition(gp, girlGObj, 18);
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
            GetSkeltonPosition(gp, girlGObj, 18);
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

inline void actBoyFall(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    debug_StdPrintfDummy("enter actBoyFall\n");
    sub->actMode = 5;
    while (1) {
        _ACTWait(1);
    }
}

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

    *(int *)((char *)sub + 0x440) = mot;
    debug_StdPrintfDummy("attack sub id [%d]\n", mot);
    debug_StdPrintfDummy("enter actBoyAttack\n");
    _ACTWait(2);
    searchEnemy((void *)self, (int *)((char *)sub + 0x168), vec);
    while (1) {
        if (*(int *)((char *)sub + 0x168)) {
            if (ACTGame_NoWeapon(self)) {
                SetMotionDirectionWithLimit((void *)self, vec, 5.0f, 45.0f);
            } else {
                SetMotionDirectionWithLimit((void *)self, vec, 10.0f, 90.0f);
            }
        }
        ACTSendMailCorrect(self, 177);
        BoyAttackCenter(self);
        _ACTWait(1);
    }
}

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
            ACTSendMailCorrect(self, 182);
        }
        if ((60 - systemStatus[0] * 10) / systemStatus[1] * 2 < n++) {
            ACTSendMailCorrect(self, 182);
        }
        _ACTWait(1);
    }
}

/* sub->0x14 is the actor's "after" callback slot: actBoyTakeWeapon arms it with
   afterBoyTakeWeapon and calls it through the slot once the motion frame passes
   the swap point, so it is written and read as a function pointer. */
typedef void (*BoyAfterFunc)(GObj *volatile a0);

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
        if (GOBJ_SUB(self)->ctrl.motion == 236) {
            if (15.0f < GOBJ_SUB(self)->ctrl.animFrame && GOBJ_SUB(self)->ctrl.animFrame < 48.0f &&
                !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)self, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(self)->ctrl.animFrame && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
                    ExecuteSEPackage(BOYINFO.weapon, 68);
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
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

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

/* the boy is hauling the girl up: moving while the stick is pushed between
   0.1 and 0.99 of its range, or further with button 0x20 held */
#define BOY_PULLUP_MOVING(sub) /* derived name */                                                  \
    (0.1f < (sub)->stick.mag && ((sub)->stick.mag < 0.99f || ((sub)->pad.now & 0x20)))

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

inline int RequestStageChangeKidnapEnd(int stage, int targetId)
{
    int rv = 0;
    if (boyGObj != 0) {
        rv = RequestStageChangeSimple(stage, 16.0f, 16.0f, 0, 0, 0) & 0xFF;
        if (rv != 0) {
            Vec16 buf = {{-1000000.0f, 0.0f, 0.0f}};

            BOYEFSTAGE[0] = 1;
            *(int *)(BOYEFSTAGE + 4) = targetId;
            ACTGame_StageChangeGObjDirect(boyGObj, stage, &buf, 0);
        }
    }
    return rv;
}

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
    *(void **)(work + 0x65C) = attrWallHit;

    GetRootPosition(work + 0xF0, (void *)self);

    actInitialize_ext_charcter(self);
    actInitialize_only_charcter((char *)self);
    actInitialize_geo(self);

    GOBJ_ACT(self)->enemy->sofaWakeTime =
        (int)(_ACTGame_GetParamF(27) * (float)((60 - systemStatus[0] * 10) / systemStatus[1]) /
              60.0f);
    ACTGame_LwsEffectInit(self);

    *(int *)(work + 0x160) = 0;
    *(int *)(work + 0x164) = 0;

    gopp_subBoyControl = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init((int **)self);

    _ACTWait(1);

    CurrentTargetGObj = (void *)self;

    *(float *)(work + 0x1D0) = _ACTGame_GetParamF(14);
    *(int *)(work + 0x44) = 0;

    if (BOYINFO.boyID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
        if (g != 0) {
            PickupWeapon(g, (void *)self, 22);
            *(void **)(work + 0x130) = g;
            if (BOYINFO.torch) {
                LightTorchOnOfWeapon(g);
            }
        } else {
            BOYINFO.boyID = 0;
        }
    }

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

    if (BOYINFO.girlID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.girlID);
        if (g != 0) {
            ACTSendMailCorrect(self, 51);
            *(void **)(work + 0x164) = *(void **)(work + 0x134) = g;
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
                ActSendMail_WithAdditionalData((void *)self, 52, (void *)self, &sofaWallHit);
                if (BOYINFO.bit32 && girlGObj != 0) {
                    ActSendMail_WithAdditionalData(girlGObj, 52, girlGObj, &sofaWallHit);
                }
            }
        } else {
            BOYINFO.layoutID = 0;
        }
    }

    startWaitCancel = 0;

    *(void **)(work + 0xB0) = &actIntrList[65];

    actCreateSubThread(subBoyBrainMain, 20);
    gopp_subBoyControl = (void *)actCreateSubThread(subBoyControl, 21);
    actCreateSubThread(subBoyCollision, 21);
    actCreateSubThread(subCommonIdle, 21);
    scpBoyControlReadDisable = 0;

    *(void **)(work + 0xB4) = &actIntrList[70];
    ACTSendMailCorrect(self, 177);

    _ACTWait(1);

    if (BOYINFO.fire && girlGObj != 0) {
        iosOmSendMail(girlGObj, 58, self);
        debug_StdPrintfDummy("hand connect start\n");
    }
    _ACTWait(0);
}

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

inline void actBoyBHang(GObj *volatile self)
{
    _ACTWait(0);
}

inline void actBoyHangBefore(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    GOBJ_WORK(self)->hangOrient[0] = sub->env.cliffOrient[0];
    GOBJ_WORK(self)->hangOrient[1] = sub->env.cliffOrient[1];
    GOBJ_WORK(self)->hangOrient[2] = sub->env.cliffOrient[2];
    GOBJ_WORK(self)->cliffReq = sub->env.motOriReq.b;
    while (1) {
        ACTSendMailCorrect(self, 268);
        _ACTWait(1);
    }
}

inline void actBoyBeslam(GObj *volatile self)
{
    char *p = (char *)GOBJ_SUB(self) + 0x120;

    sceVu0ScaleVector(p, test_CURRENTORIENT(beliftGirl), 30.0f);
    while (1) {
        ACTSendMailCorrect(self, 283);
        _ACTWait(1);
    }
}

inline void actBoyRescueSrc(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actBoySupportGBBegin(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 333, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 331);
        _ACTWait(1);
    }
}

inline void actBoySupportGBLoop(GObj *volatile self)
{
    while (1) {
        if (!IsBoyStatus_SupportGB()) {
            ACTSendMailCorrect(self, 202);
        }
        _ACTWait(1);
    }
}

inline void actBoySupportGBEnd(GObj *volatile self)
{
    while (1) {
        if (girlGObj != 0) {
            iosOmSendMail(girlGObj, 335, isysCurrentGObj);
        }
        ACTSendMailCorrect(self, 177);
        _ACTWait(1);
    }
}

inline void actBoySupportBGBegin(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 339);
        _ACTWait(1);
    }
}

inline void actBoyDitch3mExec(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 350);
        _ACTWait(1);
    }
}

inline void actBoyHangG3M(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        if (sub->pad.trg & 8) {
            ACTSendMailCorrect(self, 351);
            ACTGame_DisconnectHand();
        } else if (0.1f < sub->stick.mag) {
            ACTSendMailCorrect(self, 352);
            if (girlGObj != 0) {
                iosOmSendMail(girlGObj, 355, isysCurrentGObj);
            }
        }
        _ACTWait(1);
    }
}

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
            SetDirectRootPosition((void *)sub->weapon, buf.f);
            gamesysObjInfoPosSetStage(sub->weapon, 0, 0, stage_no);
            *(int *)((char *)sub->weapon + 0x16C) = 0;
        }
        characterPacket[2] = 0;
        ((int *)boyInfo)[0] = 0;
        sub->weapon = 0;
    }
}

inline int isLiftBoyEnable(void)
{
    unsigned int st = (unsigned int)GOBJ_ACT(boyGObj)->actMode;
    if (st >= 92) {
        return 1;
    }
    if (st < 90) {
        return 1;
    }
    return 0;
}

inline int IsBoyStatus_EnemyMustWait(void)
{
    Act *sub;
    unsigned int st;

    if (boyGObj == 0) {
        debug_assert(__FILE__, 4630);
        __assert(__FILE__, 4630, "0");
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
    v = pa[0x30 / 4];
    if (v != 0x2D)
        goto err;
    pb = (int *)b[0x164 / 4];
    if (pb[0x30 / 4] != v)
        goto err;
    r = (int *)pa[0x140 / 4];
    return r[2];
err:
    return -1;
}

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

inline int *GetbufpCharacterPacket(void)
{
    return characterPacket;
}

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

typedef struct {          /* field names derived */
    CharPos pos;          /* 0x00 */
    int boyID;            /* 0x08 */
    int girlID;           /* 0x0C */
    int f10;              /* 0x10 */
    unsigned int b1C : 8; /* 0x14 */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x16 */
} CharacterPacket;         /* derived name */

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

inline void actBoyJump(GObj *volatile self)
{
    while (1) {
        ACTSendMailCorrect(self, 171);
        _ACTWait(1);
    }
}

inline void afterBoyTakeWeapon(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    SwapBoyWeapon(BOYINFO.weapon, BOYINFO.nextWeapon, (void *)self);
    sub->weapon = BOYINFO.nextWeapon;
}

inline void afterCommonItem(GObj *volatile self) {}

inline void subBoyBrainMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    while (1) {
        _ACTWait(1);
    }
}

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

inline void Boy_Init(void)
{
    *(BoyWork *)boyInfo = boyInfoDefault;
    *(BoyKidnapWork *)characterPacket = characterPacketDefault;
}
