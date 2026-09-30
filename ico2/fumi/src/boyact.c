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
#include "frameDependSequence.h"
#include "torch.h"
#include <string.h>
#include "geometryManager.h"
#include "chain.h"
#include "act-game.h"
#include "motionOrientManager.h"

typedef struct {
    int a, b, c;
} S12;

typedef struct {
    char pad[4];
    float f4;
} CCPResult;

/* One word of the boy's actor parameter block at gobj->x15C: the motion code
   writes these slots as float and the evaluator reads them as int, so the word
   itself is a union.  ROM re-loads gobj->x15C before every store through one,
   which only an alias-set-0 union member does. */
typedef union BoyVal {
    int i;
    float f;
} BoyVal;

extern char D_0055FE58[];
extern int D_0028F4C0[];
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern CCPResult *test_CURRENTROOT(void *a0);
extern void *test_CURRENTORIENT(void *a0);
extern float _DistxzSqGV(void *a, void *b);
extern void _OrientXZGV(void *dst, void *a, void *b);
extern int _RotyGV();
extern void GetMatrixDirectionToZ(void *dst, void *orient);
extern void sceVu0SubVector(void *dst, CCPResult *a, CCPResult *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void GetChainNearestNodePosition(float *out, void *g, float *ref);
extern int GetCageChainPoint(float *a, float *b, void *obj);
extern void GetRootPositionHandExtra(void *self, float *out);
extern void ACTSendMailCorrect(int a0, int mail);

/* one 0x194-byte motion row per motion id; 0x182/0x186 are the halfwords
   subBoyCollision hands SetMotionDirectionSmooze (with and without the girl
   held), 0x18C and 0x190 flag words (0x190 the jump-chain flags) */
typedef struct {
    char _000[0x182];
    short f_182;
    char _184[0x2];
    short f_186;
    char _188[0x4];
    unsigned int f_18C;
    unsigned int f_190;
} ChainMotRow;

#define CHAINROW(self)                                                                             \
    ((ChainMotRow *)(*(int *)(*(char **)((char *)(self) + 0x15C) + 0x4A0) * sizeof(ChainMotRow) +  \
                     D_0055FE58))

void findChainInJump(void *self)
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
    char *sub;
    void *g;
    void *cage;
    float r;
    float r2;
    float ang;
    int rside = 0;
    int lside = 0;

    sub = *(char **)((char *)self + 0x164);
    r = ((CHAINROW(self)->f_190 >> 8) & 1) ? 300.0f : 100.0f;
    r2 = ((CHAINROW(self)->f_190 >> 8) & 1) ? 90.0f : 120.0f;

    for (g = isysGObjSearchFromObjKindID_begin(0x15); g != 0;
         g = isysGObjSearchFromObjKindID_next(g)) {
        if (*(int *)((char *)g + 0x16C) != 0) {
            GetRootPosition(p, g);
            q[0] = p[0];
            q[1] = p[1];
            q[2] = p[2];
            q[1] += GetChainLength(g) + 50.0f;
            if (_DistxzSqGV(test_CURRENTROOT(self), p) < r * r &&
                p[1] < test_CURRENTROOT(self)->f4 && test_CURRENTROOT(self)->f4 < q[1]) {
                _OrientXZGV(rt, p, test_CURRENTROOT(self));
                ang = (float)_RotyGV(rt, test_CURRENTORIENT(self));
                if ((ang < 0.0f ? -ang : ang) < r2) {
                    if (*(int *)(sub + 0x34) == 4) {
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

    rt[0] = ((float *)test_CURRENTROOT(self))[0];
    rt[1] = ((float *)test_CURRENTROOT(self))[1];
    rt[2] = ((float *)test_CURRENTROOT(self))[2];
    GetMatrixDirectionToZ(mtx, test_CURRENTORIENT(self));
    lp[0] = p[0];
    lp[1] = p[1];
    lp[2] = p[2];
    sceVu0SubVector(lv, (CCPResult *)lp, (CCPResult *)rt);
    lv[3] = 0.0f;
    sceVu0ApplyMatrix(lv, mtx, lv);

    if (((CHAINROW(self)->f_190 >> 6) & 1) == 0 && (rside != 0 || lside != 0) &&
        (lv[2] < 0.0f ? -lv[2] : lv[2]) < 150.0f) {
        RequestChangeHandMode(self, 0, 2, 1, g, 0, (int)w);
        RequestChangeHandMode(self, 1, 2, 1, g, 0, (int)w);
    } else {
        RequestChangeHandMode(self, 0, 2, 0, 0, 0, 0);
        RequestChangeHandMode(self, 1, 2, 0, 0, 0, 0);
    }

    if ((rside != 0 || lside != 0) && ((CHAINROW(self)->f_190 >> 5) & 1) != 0) {
        float sp = (D_0028F4C0[0] == 1) ? 0.5f : 0.8f;

        ((BoyVal *)(*(char **)((char *)self + 0x15C) + 0x45C))->f = sp;
        ((BoyVal *)(*(char **)((char *)self + 0x15C) + 0x464))->f = sp;
        ((BoyVal *)(*(char **)((char *)self + 0x15C) + 0x468))->f = sp;
    }

    if (rside != 0 || lside != 0) {
        _ACTCharStatus_Set(self, 18, -1.0f, g);
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

    if (g != 0 && *(int *)(sub + 0x34) == 65) {
        GetSkeltonPosition(hp0, self, 6);
        GetChainNearestNodePosition(hp1, g, hp0);
        if ((hp0[1] - hp1[1] < 0.0f ? -(hp0[1] - hp1[1]) : (hp0[1] - hp1[1])) < 5.0f) {
            iosOmSendMail(self, 20, g);
        }
    }

    if (*(int *)(sub + 0x34) == 65) {
        void *o;

        cage = 0;
        pos[0] = ((float *)test_CURRENTROOT(self))[0];
        pos[1] = ((float *)test_CURRENTROOT(self))[1];
        pos[2] = ((float *)test_CURRENTROOT(self))[2];
        for (o = isysGObjSearchFromObjKindID_begin(0x2C); o != 0;
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
                ACTSendMailCorrect((int)self, 0xAE);
                ACTSendMailCorrect((int)self, 0xAD);
            }
        }
    }
}

/* kept local: this TU's uses of GetRootProjectionPosOfGObj do not fit the prototype in motionManager2.h */
extern void GetRootProjectionPosOfGObj(void *out, void *obj);
/* kept local: this TU's uses of _OrientXZGV do not fit the prototype in gv.h */
extern void _OrientXZGV(void *dst, void *a, void *b);
/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *a, void *b);
/* kept local: this TU's uses of _AbsRotyGV do not fit the prototype in gv.h */
extern int _AbsRotyGV(void *a, void *b);

/* dir: subBoyCollision passes the motion direction (sub + 0x120) in $6; this
   body never reads it */
int CorrectOrient_RopeCliff(float *out, void *gobj, float *dir)
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

    switch (sub->unk34) {
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
                    a = _AbsRotyGV((char *)sub + 0x120, orient);
                    GetChainClimbOrient(climb, p);
                    b = _AbsRotyGV((char *)sub + 0x120, climb);
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

/* kept local: this TU's uses of _ACTWait do not fit the prototype in act.h */
extern void _ACTWait(int a0);
/* kept local: this TU's uses of ACTSendMailCorrect do not fit the prototype in commonact.h */
extern void ACTSendMailCorrect(int a0, int mail);
extern void *D_00639EA8;
extern void *D_0063A61C;

/* The three climb headers (omori/include/b50climb.h, b100climb.h,
   b200climb.h in the listing) textually included here, as girl_act.c does
   with its own three: each defines the hand-off's after-routine and
   act-routine `inline`, which the compiler emits at the end of the file in
   boyact.h's order, and the mot-routine plainly, emitted in place.  Their
   strings come out here, in this order, at the head of the TU's .rodata. */
inline void afterBoyHand50(volatile int a0)
{
    debug_StdPrintfDummy("boy after func\n");
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x60, D_0063A61C);
    }
}

inline void actBoyHand50(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actBoyHand50\n");
    sub->unk34 = 0x52;
    *(void **)((char *)sub + 0x14) = (void *)afterBoyHand50;
    sub->f_E0 = 0;
    while ((sub->f_E0 & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error flg get\n");
    while (1) {
        ACTSendMailCorrect(a0, 0x60);
        _ACTWait(1);
    }
}

void motBoyHand50(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter motBoyHand50\n");
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x5C, D_0063A61C);
        }
        if (sub->f_E0 & 1) {
            break;
        }
        _ACTWait(1);
    }
    while (GOBJ_SUB(a0)->f_4A0 < 0 || 2 <= GOBJ_SUB(a0)->f_4A0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x5D, D_0063A61C);
        }
        if (sub->f_E0 & 2) {
            break;
        }
        _ACTWait(1);
    }
    _ACTWait(45);
    sub->f_14 = 0;
    while (1) {
        ACTSendMailCorrect(a0, 0x47);
        _ACTWait(1);
    }
}

extern void *D_00639EA4;
extern char D_0063A6C0[];
extern char D_0063A6C8[];
extern int D_0028F4C0[];
extern CCPResult *test_CURRENTROOT(void *a0);
extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern void sceVu0Normalize(float *dst, float *src);
extern void SetMotionDirection(void *self, float *dir);

/* boyact.c rows 1522-1529 of the listing: the shared "face the girl" prologue
   the b100climb.h / b200climb.h climb motions open with. */
static inline void faceGirlFlat(void)
{
    float dir[4];
    void *boy = D_00639EA4;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8));
    dir[1] = 0.0f;
    sceVu0Normalize(dir, dir);
    SetMotionDirection(boy, dir);
}

inline void afterBoyHand100(volatile int a0)
{
    debug_StdPrintfDummy("boy after func\n");
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x65, D_0063A61C);
    }
}

inline void actBoyHand100(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actBoyHand100\n");
    sub->unk34 = 0x53;
    *(void **)((char *)sub + 0x14) = (void *)afterBoyHand100;
    sub->f_E0 = 0;
    while ((sub->f_E0 & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
        ACTSendMailCorrect(a0, 0x65);
        _ACTWait(1);
    }
}

void motBoyHand100(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int n;

    debug_StdPrintfDummy("enter motBoyHand100\n");
    faceGirlFlat();
    n = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x61, D_0063A61C);
            }
            if ((sub->f_E0 & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
    ACTSendMailCorrect(a0, 0x65);
    debug_StdPrintfDummy("%s sync error\n", (void *)a0 == D_00639EA4 ? D_0063A6C0 : D_0063A6C8);
done:
    while (GOBJ_SUB(a0)->f_4A0 < 0 || 2 <= GOBJ_SUB(a0)->f_4A0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->f_130 = SetMotionRequest((void *)a0, 0x65, *(MotOriReq *)((char *)sub + 0x620));
    sub->f_130 = SetMotionRequest((void *)a0, 0xA4, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)((char *)sub->f_130 + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x62, D_0063A61C);
        }
        if (sub->f_E0 & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->f_130 = SetMotionRequest((void *)a0, 0x65, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)((char *)sub->f_130 + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x64, D_0063A61C);
        }
        if (sub->f_E0 & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->f_14 = 0;
    while (1) {
        ACTSendMailCorrect(a0, 0x47);
        _ACTWait(1);
    }
}

inline void afterBoyHand200(volatile int a0)
{
    debug_StdPrintfDummy("boy after func\n");
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x6A, D_0063A61C);
    }
}

inline void actBoyHand200(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actBoyHand200\n");
    sub->unk34 = 0x54;
    *(void **)((char *)sub + 0x14) = (void *)afterBoyHand200;
    sub->f_E0 = 0;
    while ((sub->f_E0 & 0x10) == 0) {
        _ACTWait(1);
    }
    debug_StdPrintfDummy("boy error\n");
    while (1) {
        ACTSendMailCorrect(a0, 0x6A);
        _ACTWait(1);
    }
}

void motBoyHand200(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    int n;

    debug_StdPrintfDummy("enter motBoyHand200\n");
    faceGirlFlat();
    n = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2;
    while (1) {
        if (0 < n) {
            n--;
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x66, D_0063A61C);
            }
            if ((sub->f_E0 & 1) == 0) {
                goto cont;
            }
            goto done;
        }
        break;
    cont:
        _ACTWait(1);
    }
    ACTSendMailCorrect(a0, 0x6A);
    debug_StdPrintfDummy("%s sync error\n", (void *)a0 == D_00639EA4 ? D_0063A6C0 : D_0063A6C8);
done:
    while (GOBJ_SUB(a0)->f_4A0 < 0 || 2 <= GOBJ_SUB(a0)->f_4A0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    sub->f_130 = SetMotionRequest((void *)a0, 0x66, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)((char *)sub->f_130 + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    sub->f_130 = SetMotionRequest((void *)a0, 0x66, *(MotOriReq *)((char *)sub + 0x620));
    sub->f_130 = SetMotionRequest((void *)a0, 0xA4, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)((char *)sub->f_130 + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x67, D_0063A61C);
        }
        if (sub->f_E0 & 2) {
            break;
        }
        _ACTWait(1);
    }
    sub->f_130 = SetMotionRequest((void *)a0, 0x66, *(MotOriReq *)((char *)sub + 0x620));
    while ((*(int *)((char *)sub->f_130 + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x69, D_0063A61C);
        }
        if (sub->f_E0 & 8) {
            break;
        }
        _ACTWait(1);
    }
    sub->f_14 = 0;
    while (1) {
        ACTSendMailCorrect(a0, 0x47);
        _ACTWait(1);
    }
}

extern void *D_00639EA4;
extern char D_005577D0[];
/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
extern CCPResult *test_CURRENTROOT(void *a0);
/* kept local: this TU's uses of _DistxzGV do not fit the prototype in gv.h */
extern float _DistxzGV(void *a, void *b);
/* kept local: this TU's uses of GetHeightOfFieldPlaneDifference do not fit the prototype in motionManager2.h */
extern float GetHeightOfFieldPlaneDifference(void *boy, void *girl);

/* One 0x50-byte record per act status, indexed by sub->0x34. */

/* boyact.c:1547 and :1562 are one source line each: ABSF applied TWICE to the
   same height difference (a 2001 copy-paste artefact), which is what produces
   the eight re-evaluations of the pair of test_CURRENTROOT calls in each copy.
   The :1562 copy's body is empty in retail (the January-2002 listing shows the
   same shape), so only the calls the condition makes survive there. */
#define BOYGIRL_DY() (test_CURRENTROOT(D_00639EA4)->f4 - test_CURRENTROOT(D_00639EA8)->f4)
#define ABSF(x) ((x) < 0.0f ? -(x) : (x))

void handoff_heroin(void)
{
    void *boy = D_00639EA4;

    if (D_00639EA8 != 0) {
        if (GOBJ_SUB(D_00639EA8)->f_310 == 6) {
            if ((((StatusAttr *)(D_005577D0 + GOBJ_ACT(boy)->unk34 * 0x50))->f_4C >> 7) & 1) {
            } else {
                iosOmSendMail(D_00639EA8, 0x3E, D_0063A61C);
            }
            ACTSendMailCorrect((int)boy, 0xFA);
        } else if (_DistxzGV(test_CURRENTROOT(boy), test_CURRENTROOT(D_00639EA8)) < 100.0f &&
                   ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {
            GetHeightOfFieldPlaneDifference(D_00639EA4, D_00639EA8);
        }
    }
    if (D_00639EA8 != 0 && GOBJ_SUB(D_00639EA8)->f_310 != 6) {
        if (_DistxzGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) < 100.0f &&
            ABSF(ABSF(BOYGIRL_DY())) < 100.0f) {}
    }
}

static float D_006C0A80[4];

static float D_006C0A90[4];

static float D_006C0AA0[4];

typedef struct {
    int a;
    int b;
} CharPos;

/* the wall hit actBoyStart hands the boy and the girl with mail 0x36: the
   ClipWall work record's 0x80 pair and its hit flag at 0x88 */
typedef struct {
    CharPos pos; /* 0x00 */
    int hit;     /* 0x08 */
} BoyWallHit;

static BoyWallHit D_006C0AB0;

static int D_006C0AC0[3];

static long long D_006C0AD0[12];

/* kept local: this TU's uses of CheckFloorAttribute do not fit the prototype in motionManager2.h */
extern int CheckFloorAttribute(void *self, int id);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern void RequestStageChange(int id, void *boy, void *girl, float a, float b);
extern int stage_no;
extern int D_00639EB4;
extern int D_0063AA08;
extern int D_00639EBC;

void CheckCollisionAttr(void *self)
{
    Sub15C *stage = GOBJ_SUB(self);
    int i;
    int flag = 1;
    int esc = 0;

    if (_ACTGame_GetParamF(2) < *(float *)((char *)stage + 0x560)) {
        return;
    }
    if (GOBJ_ACT(self)->unk34 == 0x16) {
        return;
    }
    if (D_00639EB4 != 0) {
        return;
    }
    if (D_0063AA08 != 0) {
        return;
    }
    for (i = 1; i < 16; i++) {
        if (CheckFloorAttribute(self, i)) {
            int *w = (int *)D_006C0AD0;

            flag = 0;
            if (w[4] < 0) {
                w[4] = i;
                return;
            }
            if (w[4] != i) {
                if (ACTGame_FLAG_TETSUNAGI()) {
                    esc = 1;
                } else if (D_00639EA8 != 0) {
                    if (IsGirlStatusEscortEnable(stage_no, i)) {
                        esc = 1;
                    }
                }
                if (esc) {
                    D_006C0AD0[1] |= 0x800000000LL;
                    RequestStageChange(i, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
                } else {
                    RequestStageChange(i, D_00639EA4, 0, 1.0f, 8.0f);
                }
                D_00639EBC = 1;
            }
        }
    }
    if (flag) {
        ((int *)D_006C0AD0)[4] = 0xFF;
    }
}

typedef struct {
    int id; /* 0x00 */
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
} BgaEntry;

typedef struct {
    long long w[12];
} BoyWork;

typedef struct {
    int w[8];
} BoyKidnapWork;

/* the private insert-camera record.  16-aligned as the programmer's other
   vector records (act-game.c Vec4S, way_sys.c WayClipWork): subBoyCollision's
   whole-record copy is the ROM's doubleword ld/sd loop, which needs a record
   alignment of at least 8. */
typedef struct {
    float pos[3]; /* 0x00 */
    float unk0C;
    float tgt[3]; /* 0x10 */
    float unk1C;
    int unk20; /* 0x20 */
    int unk24;
    int unk28;
    float unk2C;
    float unk30;         /* 0x30 */
    unsigned char unk34; /* 0x34 */
    unsigned char pad35[3];
    int cnt;      /* 0x38 */
    int on;       /* 0x3C */
    float cur[4]; /* 0x40 */
} __attribute__((aligned(16))) PrivInsCam;

static BoyWork D_0029C610 = {{0, 0, 0xFFFFFFFF}};

static BoyKidnapWork D_0029C670 = {{0, 0, 0, 0, 0, -1, -1}};

static BgaEntry D_0029C690[] = {
    {480, 0.0f, 7.0f, 1, 70, 1, 1, 1.0f},
    {481, 0.0f, 0.0f, 0, 70, 0, 1, 1.0f},
    {485, 0.0f, 0.0f, 0, 0, 0, 0, -1.0f},
    {486, -10.0f, 23.0f, 1, 70, 1, 1, -1.0f},
    {-1},
};

/* PrivInsCam's initial value: subBoyCollision's line 3175 copies it whole into
   D_006C0B50 (the prologue forms &D_0029C7D0 and &D_0029C7D0 + 0x40 for it). */
static PrivInsCam D_0029C7D0 = {
    {0.0f, 0.0f, 0.0f}, 0.0f, {0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0.5f, 0.2f};

/* 16 zero bytes between the PrivInsCam value and D_0029C830 that no code in
   the ROM names; kept so the run keeps its layout. */
static float D_0029C820[4] = {0.0f, 0.0f, 0.0f, 0.0f};

static float D_0029C830[4] = {0.0f, 0.0f, 0.0f, 0.0f};

/* kept local: this TU's uses of test_CURRENTORIENT do not fit the prototype in commonact.h */
extern void *test_CURRENTORIENT(void *a0);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0AddVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(void *v, float ry);
/* kept local: the declaration in StageAnimation.h changes this TU codegen */
extern float stage_PlayBgAnimation(float frame, int id, void *a, void *b);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern char D_0063A6D0[];

void BoyBgaManager(void *self, int id, void *dst)
{
    /* UpdateGeo is a NESTED function in the ROM: BoyBgaManager passes it the
       static chain in $2 (STATIC_CHAIN_REGNUM) and UpdateGeo reads `self` out
       of the enclosing frame at 0($sp).  The PAL listing names it
       `UpdateGeo.170`, gcc's mangling for a nested function. */
    void UpdateGeo(BgaEntry * p)
    {
        float dir[4];
        float tmp[4];
        void *obj;

        if (p->b0F != 0) {
            dir[0] = ((float *)test_CURRENTORIENT(self))[0];
            dir[1] = ((float *)test_CURRENTORIENT(self))[1];
            dir[2] = ((float *)test_CURRENTORIENT(self))[2];
        } else {
            obj = isysGObjSearchFromObjKindID_begin(47);
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

    for (i = 0; 0 <= D_0029C690[i].id; i++) {
        if (D_0029C690[i].id == id) {
            p = &D_0029C690[i];
            goto found;
        }
    }
    debug_assert(__FILE__, 1731);
    __assert(__FILE__, 1731, D_0063A6D0);
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
    r = (int)stage_PlayBgAnimation((float)v, p->id, p->f20, p->f30);
    if (p->b0E == 0) {
        *(int *)dst = r;
    } else if (0 <= r) {
        *(int *)dst = r;
    }
}

static unsigned char D_0063C1F0;

static unsigned char D_0063C1F1;

static unsigned char D_0063C1F2;

static unsigned char D_0063C1F3;

static unsigned char D_0063C1F4;

static unsigned char D_0063C1F5;

static unsigned char D_0063C1F6;

static unsigned char D_0063C1F7;

static unsigned char D_0063C1F8;

static unsigned char D_0063C1F9;

static int D_0063C1FC;

static void *D_0063C200;

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(void *a0);
/* kept local: this TU's uses of scpPlayMotReq do not fit the prototype in script.h */
extern void scpPlayMotReq(void *a0, int a1);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(void *a0);

void E3_StageStartBoy(void *self)
{
    float buf[4];
    int w1;
    int w2;
    int w3;

    if (D_0063C1F6 != 0) {
        sceVu0ScaleVector(buf, test_CURRENTORIENT(self), 100.0f);
        sceVu0AddVector(buf, buf, test_CURRENTROOT(self));
        SetDirectRootPositionNoFitting(self, buf);
    }
    if (gflagChk(381)) {
        gflagOff(381);
        return;
    }
    if (GetStageStartInfo(self, 0, 0, &w1, &w2, &w3) == 0) {
        return;
    }
    if (D_0063C1F8 != 0) {
        return;
    }
    if (D_0063C1F7 != 0) {
        return;
    }
    _ACTWait(3);
    GetStageStartInfo(self, 0, 0, &w1, &w2, &w3);
    _ACTWait(w1);
    scpPlayStart(self);
    scpPlayMotReq(self, 8);
    _ACTWait(w2);
    scpPlayEnd(self);
    _ACTWait(w3);
}

extern int D_0028F4C0[];
extern int *D_004EB758[];
extern int D_0063B13C;
extern int fptodp(float v);

int GetChainSlope(void)
{
    float a;
    float b;
    float c;
    float ratio;
    char *g = (char *)D_00639EA4;
    int up;
    int down;

    GetChainPendulum(*(void **)(*(char **)(g + 0x164) + 0x190), &a, &b, &c);
    if (b < 5.0f) {
        return 0;
    }
    ratio = (float)*D_004EB758[GOBJ_SUB(g)->f_4A0] / (c * 0.5f);
    ACTGame_SetMotionPlaySpeedRatio_Reserve(
        g, ratio * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 30.0f, 7);
    if (D_0063B13C & 1) {
        debug_Printf(10, 140, 0x0FFFFFFF, "speed = %f (%f)\n", fptodp(ratio), fptodp(c));
    }
    if (D_0063B13C & 1) {
        debug_Printf(10, 150, 0x0FFFFFFF, "%f / %f\n", fptodp(GOBJ_SUB(g)->f_4AC),
                     fptodp((float)*D_004EB758[GOBJ_SUB(g)->f_4A0]));
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

/* kept local: this TU's uses of these do not fit the prototypes in the headers
   the rest of the file reaches. */
extern void ConvertStickToAbsCoord();
extern void GetWay_next(void *way, void *pos);
extern int GetWay_begin(void *a, void *way, void *b);
extern void sceVu0CopyVector(void *dst, void *src);
extern float fzMagnitude2fv(void *a, void *b);
extern float _DistSqGV(void *a, void *b);
extern float sceVu0InnerProduct(void *a, void *b);
extern void ClipWall(void *w);
extern void BridgeBox(void);
extern int PrivInsCamChk(void);
extern unsigned char PrivInsCamChk_Control(void);
extern float IsPointIsInScreen(void *dst, void *pos);
extern int iosPadConnect(void *pad, int a, int b, void *conf);
extern int iosPadRead(void *pad);
extern int iosPadGetStick(void *pad, void *out, int a, int b, int c, int d);
extern void _GetMotionDirection(void *dst, void *g);
extern void _ACTCommonMailTest(int a0, int a, int b, int c);
extern float GetDifferenceFromLowerField(int self, int a1);
extern int GetMotionFrameFlag1(void *self);
extern void ACTDebugMove(int a0, int a1);
extern void IncreasePdlChain(int id);
extern void DecreasePdlChain(int id);

/* the pad configuration record, as fumi's ios/pad.c and src/act.c type it */
typedef struct {
    int w[60];
} PadConf;

extern PadConf iosPadConfCustom;
extern int D_00639EAC;
extern void *D_00639EC0;
extern void *optionControlType;
extern int D_0063ABA0;
extern int D_0063ABA4;
extern int D_0063B1E8;
extern int D_0063B5F4;
extern int D_0063A6E8;
extern float D_0063A6D8;
extern unsigned char D_0063B20C;
extern char D_0063A6E0[];

/* the ClipWall work record as this function uses it: the two segment
   endpoints, the radius at 0x70 and the hit flag at 0x88 (commonact.c's
   RopeWallWork is the same 0xC0-byte record). */
typedef struct {
    char _00[0x70];
    float f70;
    char _74[0x0C];
    CharPos f80;
    int f88;
    char _8C[0x34];
} BoyWallWork;

/* The listing gives this one lines 2066-2072 of boyact.c: an inline-only
   static that snapshots the boy's orient where the script side reads it,
   inlined into subBoyControl and subBoyCollision.  Name is this
   repository's. */
static inline void SaveBoyOrientForScript(void)
{
    void *boy = D_00639EA4;

    D_0029C830[0] = ((float *)test_CURRENTORIENT(boy))[0];
    D_0029C830[1] = ((float *)test_CURRENTORIENT(boy))[1];
    D_0029C830[2] = ((float *)test_CURRENTORIENT(boy))[2];
}

/* INTERIM: CorrectStickInfo is a file-scope `inline` in the original TU
   (rows 1634-1638): the listing expands it into subBoyControl (rows
   1636-1637) and its out-of-line copy sits in the TU's inline tail, where the
   plain definition stays.  This stand-in carries the body inline; fold it
   back when the tail is C. */
static inline int CorrectStickInfo_inl(void *dir, void *stick)
{
    int buf[4];

    ConvertStickToAbsCoord(buf, stick);
    return _RotyGV(buf, dir);
}

/* boyact.c:2082-2092: the private-camera gate. */
static __inline__ unsigned char boyPrivInsCamInScreen(void)
{
    float scr[4];

    if (PrivInsCamChk_Control() == 0) {
        return 0;
    }
    if (0.0f < IsPointIsInScreen(scr, test_CURRENTROOT(D_00639EA4))) {
        return 1;
    }
    return 0;
}

/* boyact.c:1980-2010: the stick snap the boy's walk control applies when the
   camera-relative wish and the stick agree closely enough. */
static __inline__ int snapStickToCamera(float *stick, float *wish, float *sabs, float *cam)
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

void subBoyControl(volatile int a0)
{
    float stick[4];
    float wish[4];
    float sabs[4];
    float dir[4];
    int c0;
    int c1;
    int c2;
    char *s = *(char **)((char *)a0 + 0x164);
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
    iosPadConnect(s + 0x2D8, 0, 0, &iosPadConfCustom);
    D_00639EAC = (int)(s + 0x2D8);
    E3_StageStartBoy((void *)a0);
    D_0063B5F4 = 0;
    while (1) {
        if (D_0063ABA4) {
            n = 3;
        }
        if (D_0063ABA0) {
            n = 3;
        }
        if ((int)(*(unsigned long long *)(s + 0x20) >> 31) & 1) {
            n = 3;
        }
        sw = 0;
        if (n) {
            n--;
            sw = 1;
        }
        for (;;) {
            if (((int)(*(unsigned long long *)(s + 0x18) >> 48) & 1) == 0) {
                goto noStick;
            }
            *(unsigned long long *)(s + 0x18) &= ~0x800000000;
            if (D_0063AA08 == 0 &&
                *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x4B0) == 0 &&
                (PrivInsCamChk() == 0 || boyPrivInsCamInScreen())) {
                iosPadRead(s + 0x2D8);
                if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x3C8) != 0) {
                    *(unsigned int *)(s + 0x2E0) &= ~8;
                }
                *(unsigned long long *)(s + 0x18) |= 0x800000000;
                if ((int)(*(unsigned long long *)(*(char **)(s + 0x2D8) + 0x1C0) >> 16) & 1) {
                    D_0063B5F4 = 1;
                } else {
                    D_0063B5F4 = 0;
                }
                iosPadGetStick(s + 0x2D8, s + 0x338, 0, 2, 2, D_0063B20C);
                if (D_0063B1E8) {
                    if (D_0063B13C & 1) {
                        debug_Printf(10, 170, 0x0FFFFFFF, (int)D_0063A6E0,
                                     fptodp(*(float *)(s + 0x34C)));
                    }
                }
                D_0063C1F5 = 1;
            } else {
                *(int *)(s + 0x2E8) = 0;
                *(int *)(s + 0x338) = *(int *)(s + 0x33C) = 127;
                *(int *)(s + 0x2E4) = 0;
                *(int *)(s + 0x2E0) = 0;
                *(float *)(s + 0x34C) = 0.0f;
                D_0063C1F5 = 0;
            }
            _GetMotionDirection(dir, (void *)a0);
            CorrectStickInfo_inl(dir, s + 0x338);
            if (*(int *)(s + 0x2E4) & 1) {
                BridgeBox();
            }
            g = isysGObjSearchFromObjLayoutID(2);
            if (*(int *)(s + 0x350) == 1) {
                float tgt[4];
                float pos[4];

                GetRootPosition(tgt, g);
                GetRootPosition(pos, (void *)a0);
                if (GetWay_begin(tgt, s + 0x360, pos) == 0) {
                    *(int *)(s + 0x350) = 0;
                } else {
                    *(int *)(s + 0x350) = 2;
                }
                break;
            }
            if (*(int *)(s + 0x350) == 2) {
                switch (*(int *)(s + 0x3A4)) {
                case 0: {
                    float root[4];

                    GetRootPosition(root, (void *)a0);
                    GetWay_next(s + 0x360, root);
                    sceVu0CopyVector(stick, s + 0x3B0);
                    *(float *)(s + 0x34C) = 1.0f;
                    break;
                }
                case 1: {
                    float p0[4];
                    float p1[4];
                    BoyWallWork work;

                    GetRootPosition(p0, (void *)a0);
                    GetRootPosition(p1, g);
                    work.f70 = 10.0f;
                    sceVu0CopyVector(&work, p0);
                    sceVu0CopyVector((char *)&work + 0x10, p1);
                    ClipWall(&work);
                    if (work.f88 != 0) {
                        *(int *)(s + 0x350) = 1;
                    }
                    dist = fzMagnitude2fv(p1, p0);
                    p1[0] = p1[0] - p0[0];
                    p1[1] = 0.0f;
                    p1[2] = p1[2] - p0[2];
                    sceVu0Normalize(stick, p1);
                    if (dist < 120.0f) {
                        ACTSendMailCorrect(a0, 0xC7);
                        *(int *)(s + 0x350) = 0;
                    } else if (dist < 850.0f) {
                        *(float *)(s + 0x34C) = (dist - 100.0f) / 750.0f;
                    } else {
                        *(float *)(s + 0x34C) = 1.0f;
                    }
                    break;
                }
                }
                break;
            }
            if (0.1f < *(float *)(s + 0x34C)) {
                float cam[4];

                sabs[0] = stick[0];
                sabs[1] = stick[1];
                sabs[2] = stick[2];
                ConvertStickToAbsCoord(stick, s + 0x338);
                cam[0] = (float)(*(int *)(s + 0x338) - 128);
                cam[1] = 0.0f;
                cam[2] = (float)(*(int *)(s + 0x33C) - 128);
                if (sw == 0) {
                    snapStickToCamera(stick, wish, sabs, cam);
                }
                wish[0] = cam[0];
                wish[1] = cam[1];
                wish[2] = cam[2];
                {
                    float ori[4];

                    GetRootMotionOrient(ori, (void *)a0);
                    *(int *)(s + 0x340) = _RotyGV(stick, ori);
                }
            } else {
                *(int *)(s + 0x340) = 0;
                *(float *)(s + 0x34C) = 0.0f;
            }
            if ((void *)a0 == D_00639EC0) {
                break;
            }
            _ACTWait(1);
        }
        /* Local debug switch, off.  What the bytes pin: the function reaches
           gcse with 1548..1567 real insns (1537 without this arm): the
           expression table size orders PRE's reaching registers, whose order
           is the order of the spill slots at 0x170..0x18C (s + 0x360 before
           the 0xB0 vector).  cse cannot carry dbg's 0 across the loop labels,
           gcse's constant propagation folds the test and the next jump pass
           deletes the arm.  What they cannot pin: the arm's text, which is
           the January build's live arm at this spot (listing rows 2328-2330),
           way_tool.c's cursor_control idiom. */
        if (dbg) {
            if ((void *)a0 == D_00639EC0 && (*(int *)(s + 0x2E4) & 1)) {
                if (*(int *)(s + 0x34) != 1) {
                    ACTSendMailCorrect(a0, 258);
                }
                ACTDebugMove(a0, 1);
            }
        }
        *(float *)(s + 0x120) = stick[0];
        *(float *)(s + 0x124) = stick[1];
        *(float *)(s + 0x128) = stick[2];
    noStick:
        *(float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x340) =
            *(float *)(s + 0x34C);
        slow = 0;
        if (*(int *)(s + 0x34) == 1) {
            if (GOBJ_SUB(a0)->f_4A0 == 0 || GOBJ_SUB(a0)->f_4A0 == 1) {
                if (0.5f < *(float *)(s + 0x34C)) {
                    D_0063A6E8 = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 5;
                }
            }
        }
        if (0 < D_0063A6E8) {
            D_0063A6E8--;
            slow = 1;
        }
        if (slow && 0.5f < *(float *)(s + 0x34C)) {
            *(float *)(s + 0x34C) = 0.5f;
        }
        c0++;
        if (0.1f < *(float *)(s + 0x34C)) {
            c0 = 0;
        }
        if (0.1f < *(float *)(s + 0x34C) &&
            (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20))) {
            c1++;
        } else {
            c1 = 0;
        }
        if (0.1f < *(float *)(s + 0x34C) &&
            !(0.1f < *(float *)(s + 0x34C) &&
              (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20)))) {
            c2++;
        } else {
            c2 = 0;
        }
        _ACTCommonMailTest(a0, c0, c1, c2);
        switch (*(int *)(s + 0x34)) {
        case 1:
            ACTSendMailCorrect(a0, 0xC7);
            break;
        case 2:
            ACTSendMailCorrect(a0, 0xB5);
            break;
        case 3:
            ACTSendMailCorrect(a0, 0xBA);
            break;
        case 41:
            if (0.1f < *(float *)(s + 0x34C) &&
                !((unsigned int)(*(int *)(s + 0x340) + 134) < 269)) {
                ACTSendMailCorrect(a0, 0x149);
            }
            break;
        case 29:
            if (*(int *)(s + 0x2E4) & 0x40) {
                if (100.0f < GetDifferenceFromLowerField(a0, 44)) {
                    ACTSendMailCorrect(a0, 0x127);
                } else {
                    ACTSendMailCorrect(a0, 0xE2);
                }
            }
            if (*(int *)(s + 0x2E0) & 0x10) {
                ACTSendMailCorrect(a0, 0xC7);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 26:
            if (0.1f < *(float *)(s + 0x34C) &&
                !((unsigned int)(*(int *)(s + 0x340) + 134) < 269)) {
                sceVu0ScaleVector(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x360,
                                  *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8D0,
                                  -1.0f);
                ACTSendMailCorrect(a0, 0x139);
            }
            break;
        case 27:
            if (0.1f < *(float *)(s + 0x34C) &&
                _AbsRotyGV(stick, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x470) >=
                    136 &&
                GetMotionFrameFlag1((void *)a0)) {
                ACTSendMailCorrect(a0, 0x131);
            }
            if ((*(int *)(s + 0x2E0) & 0x10) && GetMotionFrameFlag1((void *)a0)) {
                ACTSendMailCorrect(a0, 0x131);
            }
            if (0.1f < *(float *)(s + 0x34C) &&
                !((unsigned int)(*(int *)(s + 0x340) + 134) < 269)) {
                ACTSendMailCorrect(a0, 0x130);
            }
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            if (*(int *)(s + 0x2E0) & 0x10) {
                ACTSendMailCorrect(a0, 0xC7);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x127);
            break;
        case 28:
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 30:
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            } else if (*(int *)(s + 0x2E4) & 0x10) {
                ACTSendMailCorrect(a0, 0xC7);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 31:
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 33:
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            break;
        case 40:
            if ((*(int *)(s + 0x2E4) & 0x10) || *(int *)(s + 0x33C) - 128 < -100) {
                ACTSendMailCorrect(a0, 0x12F);
            }
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            break;
        case 34:
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            } else if (*(int *)(s + 0x2E0) & 0x10) {
                ACTSendMailCorrect(a0, 0x12E);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 35:
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            if (*(int *)(s + 0x2E4) & 0x10) {
                ACTSendMailCorrect(a0, 0xBD);
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            break;
        case 52: {
            int near = 1;
            int front = 1;
            float gpos[4];
            float tpos[4];
            float ori[4];
            float vec[4];
            void *obj = *(void **)(s + 0x600);

            if (obj != 0 && D_00639EA8 != 0) {
                gpos[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                gpos[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                gpos[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
                GetRootPosition(tpos, obj);
                ori[0] = ((float *)test_CURRENTORIENT((void *)a0))[0];
                ori[1] = ((float *)test_CURRENTORIENT((void *)a0))[1];
                ori[2] = ((float *)test_CURRENTORIENT((void *)a0))[2];
                _OrientXZGV(vec, gpos, tpos);
                if (_DistSqGV(tpos, gpos) < 250000.0f &&
                    CheckFloorAttribute(D_00639EA8, 0xA000000) != 0) {
                    if (0.0f < sceVu0InnerProduct(ori, vec)) {
                        near = 0;
                    } else {
                        front = 0;
                    }
                }
            }
            if (*(int *)(s + 0x2E0) & 0x20) {
                if (near && 0.1f < *(float *)(s + 0x34C) &&
                    (unsigned int)(*(int *)(s + 0x340) + 90) < 181) {
                    ACTSendMailCorrect(a0, 0x81);
                    break;
                }
                if (front && 0.1f < *(float *)(s + 0x34C) &&
                    !((unsigned int)(*(int *)(s + 0x340) + 89) < 179)) {
                    ACTSendMailCorrect(a0, 0x80);
                    break;
                }
                ACTSendMailCorrect(a0, 0x150);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            ACTSendMailCorrect(a0, 0xC7);
            break;
        }
        case 53:
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 90 / 60 > *(int *)(s + 0x4C)) {
                ACTSendMailCorrect(a0, 0x86);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            ACTSendMailCorrect(a0, 0xC7);
            break;
        case 54:
            if (*(int *)(s + 0x2E0) & 0x20) {
                if (0.1f < *(float *)(s + 0x34C)) {
                    ACTSendMailCorrect(a0, 0x86);
                    if (*(int *)(s + 0x2E0) & 8) {
                        ACTSendMailCorrect(a0, 0x42);
                    }
                } else {
                    ACTSendMailCorrect(a0, 0x150);
                }
            } else {
                ACTSendMailCorrect(a0, 0xC7);
            }
            break;
        case 32:
        case 38: {
            /* RECONSTRUCTION: the bytes pin a volatile read of a0 opening
               this arm (listing row 2676, its value unused in the retail
               text) and 39 code-free rows 2689-2727 before the arm's break;
               this local is the form that read takes in fumi's actor code,
               and its reader is the DEBUG build's report in that window.
               The name, type and report are ours. */
            int self = a0;

            if (((int)(*(unsigned long long *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) +
                                               0x298) >>
                       1) &
                 1) &&
                !(*(int *)(s + 0x33C) - 128 < 101)) {
                ACTSendMailCorrect(a0, 0x14B);
            } else if ((*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x298) & 1) &&
                       *(int *)(s + 0x33C) - 128 < -100) {
                ACTSendMailCorrect(a0, 0x14A);
            } else {
                ACTSendMailCorrect(a0, 0x150);
            }
            if ((optionControlType == (void *)1 ? *(int *)(s + 0x2E4) : *(int *)(s + 0x2E0)) & 8) {
                ACTSendMailCorrect(a0, 0x42);
            }
#ifdef DEBUG
            scePrintf("boy %08x stick %d\n", self, *(int *)(s + 0x33C) - 128);
#endif
            break;
        }
        case 43:
            if (0.95f < *(float *)(s + 0x34C)) {
                ACTSendMailCorrect(a0, 0xDE);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 44:
            if (0.95f < *(float *)(s + 0x34C)) {
                ACTSendMailCorrect(a0, 0xDD);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 49:
            if (*(int *)(s + 0x2E0) & 0x20) {
                switch (*(unsigned int *)(s + 0x38)) {
                case 1:
                    if (0.1f < *(float *)(s + 0x34C) &&
                        (unsigned int)(*(int *)(s + 0x340) + 90) < 181) {
                        ACTSendMailCorrect(a0, 0x14C);
                    } else {
                        ACTSendMailCorrect(a0, 0x150);
                    }
                    break;
                case -1:
                    if (0.1f < *(float *)(s + 0x34C) &&
                        !((unsigned int)(*(int *)(s + 0x340) + 89) < 179)) {
                        ACTSendMailCorrect(a0, 0x14D);
                    } else {
                        ACTSendMailCorrect(a0, 0x150);
                    }
                    break;
                default:
                    if (0.1f < *(float *)(s + 0x34C) &&
                        (unsigned int)(*(int *)(s + 0x340) + 90) < 181) {
                        ACTSendMailCorrect(a0, 0x14C);
                    } else if (0.1f < *(float *)(s + 0x34C) &&
                               !((unsigned int)(*(int *)(s + 0x340) + 89) < 179)) {
                        ACTSendMailCorrect(a0, 0x14D);
                    } else {
                        ACTSendMailCorrect(a0, 0x150);
                    }
                    break;
                }
            } else {
                ACTSendMailCorrect(a0, 0x150);
                ACTSendMailCorrect(a0, 0xC7);
            }
            break;
        case 51:
            if (*(int *)(s + 0x2E0) & 0x20) {
                if (0.1f < *(float *)(s + 0x34C) &&
                    (unsigned int)(*(int *)(s + 0x340) + 90) < 181) {
                    ACTSendMailCorrect(a0, 0x14C);
                } else if (0.1f < *(float *)(s + 0x34C) &&
                           !((unsigned int)(*(int *)(s + 0x340) + 89) < 179)) {
                    ACTSendMailCorrect(a0, 0x14D);
                } else {
                    ACTSendMailCorrect(a0, 0x150);
                }
            } else {
                ACTSendMailCorrect(a0, 0xC7);
            }
            break;
        case 118:
            if (*(int *)(s + 0x2E4) & 0x20) {
                ACTSendMailCorrect(a0, 0xC8);
                break;
            }
            if (0.1f < *(float *)(s + 0x34C) &&
                !(0.1f < *(float *)(s + 0x34C) &&
                  (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20)))) {
                ACTSendMailCorrect(a0, 0xBA);
                break;
            }
            if (0.1f < *(float *)(s + 0x34C) &&
                (*(float *)(s + 0x34C) < 0.99f || (*(int *)(s + 0x2E0) & 0x20))) {
                ACTSendMailCorrect(a0, 0xB5);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        case 58:
            switch (GetChainSlope()) {
            case 0:
                ACTSendMailCorrect(a0, 0xA3);
                if (GOBJ_SUB(a0)->f_4A0 == 137 && GOBJ_SUB(a0)->f_4AC < 50.0f) {
                    ACTSendMailCorrect(a0, 0xA4);
                }
                break;
            case 1:
                ACTSendMailCorrect(a0, 0x94);
                break;
            case 2:
                ACTSendMailCorrect(a0, 0x95);
                break;
            case 3:
                ACTSendMailCorrect(a0, 0x96);
                break;
            case 4:
                ACTSendMailCorrect(a0, 0x97);
                break;
            }
            if (GOBJ_SUB(a0)->f_4A0 == 135) {
                d = 1.0f;
            } else if (*(int *)(s + 0x2E0) & 0x20) {
                d = 1.0f;
            } else {
                d = 0.0f;
            }
            SaveBoyOrientForScript();
            D_0063A6D8 = d;
            if (*(int *)(s + 0x2E0) & 0x20) {
                IncreasePdlChain(*(int *)(s + 0x190));
            } else {
                DecreasePdlChain(*(int *)(s + 0x190));
            }
            if (*(int *)(s + 0x2E4) & 0x10) {
                ACTSendMailCorrect(a0, 0xBE);
                ACTSendMailCorrect(a0, 0xC4);
            }
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0x13C);
            }
            break;
        case 60:
            if (!(*(int *)(s + 0x33C) - 128 < 101)) {
                ACTSendMailCorrect(a0, 0x13C);
            }
            if (*(int *)(s + 0x33C) - 128 < -100) {
                ACTSendMailCorrect(a0, 0x9E);
            }
            if (*(int *)(s + 0x2E0) & 0x20) {
                ACTSendMailCorrect(a0, 0x9F);
            }
            if (*(int *)(s + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0x13C);
            }
            break;
        case 20:
        case 21:
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x3E, D_0063A61C);
            }
            break;
        case 109:
            if (*(int *)(s + 0x2E0) & 8) {
                break;
            }
            ACTSendMailCorrect(a0, 0xC7);
            break;
        case 105:
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) + 45) < 91) {
                ACTSendMailCorrect(a0, 0x17C);
            }
            if (0.1f < *(float *)(s + 0x34C) &&
                !((unsigned int)(*(int *)(s + 0x340) + 134) < 269)) {
                ACTSendMailCorrect(a0, 0xE2);
            }
            break;
        case 45:
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) + 45) < 91) {
                ACTSendMailCorrect(a0, 0x75);
                ACTSendMailCorrect(a0, 0x74);
            }
            if (*(int *)(s + 0x2E0) & 8) {
                ACTSendMailCorrect(a0, 0x74);
                brainAddLevelGirl(10.0f);
            }
            if (*(int *)(s + 0x4C) == 0 && ((int)(*(unsigned long long *)(s + 0x18) >> 41) & 1)) {
                brainAddLevelGirl(1000.0f);
            }
            break;
        case 23:
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) + 45) < 91) {
                ACTSendMailCorrect(a0, 0x14C);
                break;
            }
            if (0.1f < *(float *)(s + 0x34C) &&
                !((unsigned int)(*(int *)(s + 0x340) + 134) < 269)) {
                ACTSendMailCorrect(a0, 0x14D);
                break;
            }
            if (0.1f < *(float *)(s + 0x34C) && (unsigned int)(*(int *)(s + 0x340) - 46) < 89) {
                ACTSendMailCorrect(a0, 0x14E);
                break;
            }
            if (0.1f < *(float *)(s + 0x34C) && !(*(int *)(s + 0x340) < -134) &&
                *(int *)(s + 0x340) < -45) {
                ACTSendMailCorrect(a0, 0x14F);
            }
            break;
        case 94:
            if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0xD0) != 0) {
                ACTSendMailCorrect(a0, 0x16F);
                break;
            }
            ACTSendMailCorrect(a0, 0x150);
            break;
        }
        _ACTWait(1);
    }
}

typedef struct {
    int boyID;                        /* 0x00 */
    int girlID;                       /* 0x04 */
    unsigned long long layoutID : 32; /* 0x08 */
    /* The one-bit flags are declared no wider than short: actBoyStart's truth
       tests of torch, bit32 and fire are the ROM's ld/mask/and form, which
       shorten_compare hands to fold's bit-field compare only for a field
       narrower than int, and its escort read truncates to char before the
       mask as a char field's extraction does.  torch is a short because
       ReadCharacterPacket's lhu of its 16-bit packet field survives only a
       conversion to a type of at least 16 bits. */
    unsigned char bit32 : 1;
    unsigned char fire : 1;
    unsigned short torch : 1;
    unsigned char escort : 1;
    char pad10[0x10];        /* 0x10 */
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
} BoyInfo;

#define BOYINFO (*(BoyInfo *)D_006C0AD0)
/* BoyInfo's +0x50 record as the ef-stage return reads it: a flag byte and the
   camera target id at +4 (BoyInfoUpdate_StageChange copies it whole as f50). */
#define BOYEFSTAGE ((unsigned char *)D_006C0AD0 + 0x50)

typedef struct {
    char pad00[0x0C];
    float f0C; /* 0x0C */
    float f10;
    float f14;
    float f18; /* 0x18 */
    float f1C;
    float f20;
    char pad24[0x4C - 0x24];
} WeaponOffsetRow; /* 0x4C */

extern char D_002C2DC8[];

void InitSwapWeapon(void *self)
{
    Act *sub = GOBJ_ACT(self);
    char *info;
    char *p;
    WeaponOffsetRow *row;

    if (BOYINFO.boyID != 0) {
        BOYINFO.weapon = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
    } else {
        BOYINFO.weapon = 0;
    }
    info = *(char **)((char *)sub + 0x608);
    BOYINFO.nextWeapon = info;
    p = (char *)gamesysObjInfoGet(*(int *)(info + 0xC), *(int *)(info + 0x8));
    if (p != 0) {
        BOYINFO.f30 = *(float *)(p + 0x10);
        BOYINFO.f34 = *(float *)(p + 0x14);
        BOYINFO.f38 = *(float *)(p + 0x18);
        BOYINFO.f40 = *(float *)(p + 0x20);
        BOYINFO.f44 = *(float *)(p + 0x24);
        BOYINFO.f48 = *(float *)(p + 0x28);
    } else {
        row = (WeaponOffsetRow *)(*(int *)(info + 0x8) * sizeof(WeaponOffsetRow) + D_002C2DC8);
        BOYINFO.f30 = -row->f18;
        BOYINFO.f34 = -row->f1C;
        BOYINFO.f38 = -row->f20;
        BOYINFO.f40 = row->f0C * 3.1415927f / 180.0f;
        BOYINFO.f44 = row->f10 * 3.1415927f / 180.0f;
        BOYINFO.f48 = row->f14 * 3.1415927f / 180.0f;
    }
}

/* kept local: this TU's uses of InitMotionGeoInfo do not fit the prototype in motionManager2.h */
extern void InitMotionGeoInfo(void *node, float x, float y, float z, float rx, float ry, float rz);
/* kept local: this TU's uses of CheckWeaponKind do not fit the prototype in weapon.h */
extern int CheckWeaponKind(void *w);
/* kept local: this TU's uses of SetWeaponOffsetMode do not fit the prototype in weapon.h */
extern void SetWeaponOffsetMode(void *w, int mode);

void PutWeapon(void)
{
    char *p = (char *)D_006C0AD0;

    if (*(void **)(p + 0x20) != 0) {
        InitMotionGeoInfo(*(char **)(*(char **)(p + 0x20) + 0x15C) + 0xA0, *(float *)(p + 0x30),
                          *(float *)(p + 0x34), *(float *)(p + 0x38), -*(float *)(p + 0x40),
                          -*(float *)(p + 0x44), -*(float *)(p + 0x48));
        if (CheckWeaponKind(*(void **)(p + 0x20)) == 9) {
            SetWeaponOffsetMode(*(void **)(p + 0x20), 1);
        }
        UpdateRootMatrix(*(void **)(p + 0x20));
    }
}

/* kept local: this TU's uses of PickupWeapon do not fit the prototype in weapon.h */
extern void PickupWeapon(void *w, void *boy, int kind);
/* kept local: this TU's uses of ReleaseWeapon do not fit the prototype in weapon.h */
extern void ReleaseWeapon(void *w);
extern char D_0063A6F0[];

/* boyact.c:3002-3021 in the PAL listing: a static helper with no out-of-line
   copy in ROM, inlined into SetBoyWeaponGObj and afterBoyTakeWeapon. */
static inline int SwapBoyWeapon(void *oldW, void *newW, void *boy)
{
    Act *sub = GOBJ_ACT(boy);

    if (oldW == newW) {
        return 0;
    }
    if (newW == 0) {
        debug_assert(__FILE__, 3007);
        __assert(__FILE__, 3007, D_0063A6F0);
        return 0;
    }
    PickupWeapon(newW, boy, 0x16);
    ((int *)D_006C0AD0)[0] = *(int *)((char *)newW + 0x8);
    *(void **)((char *)sub + 0x150) = newW;
    SetWeaponOffsetMode(newW, 0);

    if (oldW == 0) {
        return 1;
    }
    ReleaseWeapon(oldW);
    PutWeapon();
    gamesysObjInfoPosSetStage((int *)oldW, 0, 0, stage_no);
    debug_StdPrintfDummy("%d -> %d\n", *(int *)((char *)oldW + 0x8), *(int *)((char *)newW + 0x8));
    return 1;
}

/* kept local: the declaration in camera-root.h changes this TU codegen */
extern float *GetCurrentCameraSet2(void);

void OtherStageGirlPinchCamera_After(float t)
{
    float buf[4];

    D_006C0A80[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    D_006C0A80[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    D_006C0A80[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    if (_ACTGame_GetParamF(0xE) * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f <= t) {
        D_006C0AA0[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
        D_006C0AA0[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
        D_006C0AA0[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
        GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
        sceVu0ScaleVector(buf, buf, 500.0f);
        sceVu0AddVector(D_006C0A90, GetCurrentCameraSet2(), buf);
    } else {
        /* a2 is the gobj the insert-camera record tracks, not a frame count. */
        PrivInsCamSet((float *)test_CURRENTROOT(D_00639EA4), D_006C0A90, (int)D_00639EA4,
                      (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 100 / 60,
                      (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 45 / 60, 0.05f, 0.25f, 0);
        *(int *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x688) + 0x4B0) = 0;
    }
}

void ACTDispLwsBoyStonize_InQueenStage(void *self)
{
    BoyBgaManager(self, 0x1E0, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A0);
    BoyBgaManager(self, 0x1E1, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A4);
    BoyBgaManager(self, 0x1E5, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2B0);
    BoyBgaManager(self, 0x1E5, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2AC);
    BoyBgaManager(self, 0x1E6, *(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x2A8);
}

static int D_006C0B30[8];

static PrivInsCam D_006C0B50;

/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *dst, void *a, void *b, float t, float u);
/* kept local: this TU's uses of InsertCamera_SetDetail do not fit the prototype in camera-root.h */
extern void InsertCamera_SetDetail(float *cam, float *p, int a2, int a3, int a4, int a5, float f);

void PrivInsCamProcess(void)
{
    float p[4];

    switch (D_006C0B50.on) {
    case 1:
        D_006C0B50.cur[0] = D_006C0B50.pos[0];
        D_006C0B50.cur[1] = D_006C0B50.pos[1];
        D_006C0B50.cur[2] = D_006C0B50.pos[2];
        D_006C0B50.cnt = D_006C0B50.unk24;
        D_006C0B50.on = 2;
        break;
    case 2:
        _InterGV(D_006C0B50.cur, D_006C0B50.tgt, D_006C0B50.cur, 1.0f, D_006C0B50.unk2C);
        InsertCamera_SetDetail(GetCurrentCameraSet2(), D_006C0B50.cur, 5, 1, 2, 0,
                               D_006C0B50.unk30);
        if (--D_006C0B50.cnt <= 0) {
            D_006C0B50.on = 3;
        }
        break;
    case 3:
        D_006C0B50.tgt[0] = D_006C0B50.cur[0];
        D_006C0B50.tgt[1] = D_006C0B50.cur[1];
        D_006C0B50.tgt[2] = D_006C0B50.cur[2];
        D_006C0B50.cnt = D_006C0B50.unk28;
        D_006C0B50.on = 4;
        break;
    case 4:
        if (D_006C0B50.unk20 != 0) {
            p[0] = ((float *)test_CURRENTROOT((void *)D_006C0B50.unk20))[0];
            p[1] = ((float *)test_CURRENTROOT((void *)D_006C0B50.unk20))[1];
            p[2] = ((float *)test_CURRENTROOT((void *)D_006C0B50.unk20))[2];
        } else {
            p[0] = D_006C0B50.pos[0];
            p[1] = D_006C0B50.pos[1];
            p[2] = D_006C0B50.pos[2];
        }
        _InterGV(D_006C0B50.cur, p, D_006C0B50.tgt, (float)D_006C0B50.cnt,
                 (float)(D_006C0B50.unk28 - D_006C0B50.cnt));
        InsertCamera_SetDetail(GetCurrentCameraSet2(), D_006C0B50.cur, 2, 1, 0, 0,
                               D_006C0B50.unk30);
        if (--D_006C0B50.cnt <= 0) {
            D_006C0B50.on = 0;
        }
        break;
    }
}

/* kept local: this TU's uses of _DistGV do not fit the prototype in gv.h */
extern float _DistGV(CCPResult *a, CCPResult *b);
/* kept local: poly-flat.h declares IsPointIsInScreen void, the callers here
   read the float it returns */
extern float IsPointIsInScreen(void *dst, void *pos);
extern void lt_switch_layout(int no);
extern void ACTGame_CommonLoop(void *self);
extern void ACTParaStatus_Exec(void *self);
extern void ACTLookTargetSystem_Exec(void *self);
extern int _ACTParaStatus_Check(void *self, int bit);
extern void CommonAttackCenter(void *self);
extern float GetDifferenceFromLowerField(int self, int a1);
extern int NotNeedBackHand(void);
extern int isBottomOfChain(void *chain);
extern void GetCorrectOrientOfChain(void *buf, void *obj);
/* kept local: this TU's uses of SetMotionDirectionSmooze do not fit the prototype in commonact.h */
extern void SetMotionDirectionSmooze(void *self, float *dir, float t);
extern int ActSendMail_WithAdditionalData(void *gop, int msg, void *sender, void *data);
extern void Camctrl_SetTarget(int self, int obj, int a2);
extern void ScpCallCameraGetTarget(float *dst);
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: this TU's uses of debug_NMarker do not fit the prototype in camera-editor.h */
extern void debug_NMarker(float *pos, int r, int g, int b, float size);
extern void *D_00639EA0;
extern float D_0063A6F8[];
extern float D_0063A6D8;

/* the boy's work record at Act+0x688.  subBoyCollision's stores through it are
   member accesses: the ROM moves its a0 reloads ahead of them (the 0x4B0
   decrement, the 0x33C store), which it may only do past a MEM_IN_STRUCT_P
   store (girl_act.c's ActPara is the girl's view of the same record).
   actBoyDitch3mReady's 0x348 store is the same case: the mail's a0 reload
   goes ahead of it and the store lands in the call's delay slot. */
typedef struct {
    char pad000[0x33C];
    float f33C; /* 0x33C */
    char pad340[0x348 - 0x340];
    float f348; /* 0x348 */
    char pad34C[0x3C0 - 0x34C];
    int f3C0; /* 0x3C0 */
    char pad3C4[0x470 - 0x3C4];
    float f470; /* 0x470 */
    float f474;
    float f478;
    char pad47C[0x480 - 0x47C];
    S12 f480; /* 0x480 */
    char pad48C[0x4B0 - 0x48C];
    int f4B0; /* 0x4B0 */
} HangTarget;

#define HANG_TARGET(o) ((HangTarget *)*(char **)(*(char **)((char *)(o) + 0x164) + 0x688))

/* the object kinds the proximity scan below walks, terminated by -1 */
typedef struct {
    int id[4];
} ObjKindList;

static const ObjKindList collisionKinds = {{4, 47, 62, -1}};

/* The listing gives this one lines 3173-3177 of boyact.c with its whole body
   on 3175 and no out-of-line copy: it was `inline` in the original and only
   subBoyCollision calls it.  The name is this repository's. */
static inline void PrivInsCamInit(void)
{
    D_006C0B50 = D_0029C7D0;
}

/* INTERIM: ACTSearchGObj is a file-scope `inline` in the original TU: the
   listing expands it into subBoyCollision and actBoyAttack (rows 1644-1661)
   and its out-of-line copy sits in the TU's inline tail, where the plain
   definition stays.  This stand-in carries the body both inline; fold it back
   when the tail is C. */
static inline void ACTSearchGObj_inl(void *a0, int a1, int a2, int *out_id, float *out_vec,
                                     float thresh)
{
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(a1);
    best = a2;
    *out_id = 0;
    for (; node != 0; node = isysGObjSearchFromObjKindID_next(node)) {
        if (*(int *)((char *)node + 0x16C) != 0) {
            CCPResult *r1 = test_CURRENTROOT(a0);
            if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                int sign;
                int dist;
                CCPResult *r4 = test_CURRENTROOT(node);
                sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                if (sign < 0) {
                    dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                } else {
                    dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
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

/* The DEBUG build's report of subBoyCollision's camera state, built only under
   DEBUG (name and text ours); its register arguments leave nothing in retail. */
static __inline__ void boyCamDebugDisp(int camOn, int looking)
{
#ifdef DEBUG
    scePrintf("boy camera on %d looking %d\n", camOn, looking);
#endif
}

void subBoyCollision(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);
    int camOn;
    int looking;
    int hang;
    int hangBit;
    int hold;
    int dbg = 0; /* local debug switch, see the test after the helper's SetRootPosition */

    PrivInsCamInit();

    while (*(int *)(sub + 0x130) == 0) {
        _ACTWait(1);
    }
    if (200.0f < GetDifferenceFromLowerField(a0, 0x2C)) {
        ACTSendMailCorrect(a0, 0x7);
    }
    while (1) {
        float vec[4];

        camOn = 0;
        if (0 < HANG_TARGET(a0)->f4B0) {
            HANG_TARGET(a0)->f4B0 -= 1;
            _ACTCharStatus_Set((void *)a0, 0x20, -1.0f, 0);
            OtherStageGirlPinchCamera_After((float)HANG_TARGET(a0)->f4B0);
        }
        PrivInsCamProcess();
        findChainInJump((void *)a0);
        CheckCollisionAttr((void *)a0);
        ACTGame_CommonLoop((void *)a0);

        hangBit = ((int)(*(unsigned long long *)(sub + 0x18) >> 50) & 1);
        hang = 1;
        if (((int)(*(unsigned long long *)(sub + 0x20) >> 18) & 1) == 0) {
            hang = hangBit;
        }
        if (hang == 0) {
            if (*(float *)(sub + 0x34C) != 0.0f &&
                CorrectOrient_RopeCliff(vec, (void *)a0, (float *)(sub + 0x120)) != 0) {
                *(float *)(sub + 0x120) = vec[0];
                *(float *)(sub + 0x124) = vec[1];
                *(float *)(sub + 0x128) = vec[2];
            }
            if (0.1f < *(float *)(sub + 0x34C) && *(int *)(sub + 0x34) != 0x73) {
                SetMotionDirectionSmooze((void *)a0, (float *)(sub + 0x120),
                                         (float)(((void *)a0 == D_00639EA8 && D_00639EA0 != 0)
                                                     ? CHAINROW(a0)->f_182
                                                     : CHAINROW(a0)->f_186));
            }
        }
        CommonAttackCenter((void *)a0);
        ACTGame_SaveActorInformation((void *)a0);
        if (*(unsigned int *)(sub + 0x34) < 4 && *(int *)(sub + 0x34) != 0) {
            if (*(int *)(sub + 0x2E4) & 0x20) {
                int hit;

                ACTSearchGObj_inl((void *)a0, 0x13, 0x2D, &hit, vec, 100.0f);
            }
        }
        switch (*(int *)(sub + 0x34)) {
        case 0x1C:
            if (((int)(*(unsigned long long *)(sub + 0x480) >> 10) & 1) &&
                ((int)(*(unsigned long long *)(sub + 0x490) >> 10) & 1)) {
                ACTSendMailCorrect(a0, 0xC7);
            }
            break;
        case 0x20:
        case 0x26:
            if (*(int *)(sub + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0x13C);
            }
            break;
        case 0x39:
            SaveBoyOrientForScript();
            D_0063A6D8 = 0.0f;
            if (*(int *)(sub + 0x2E4) & 0x10) {
                ACTSendMailCorrect(a0, 0xC3);
            }
            if (*(int *)(sub + 0x2E4) & 0x40) {
                HANG_TARGET(a0)->f33C = ((float *)test_CURRENTROOT(*(void **)(sub + 0x190)))[1] +
                                        GetChainLength(*(void **)(sub + 0x190)) -
                                        ((float *)test_CURRENTROOT((void *)a0))[1];
                ActSendMail_WithAdditionalData((void *)a0, 0x13C, (void *)a0,
                                               &HANG_TARGET(a0)->f33C);
            }
            if (*(int *)(sub + 0x2E0) & 0x20) {
                ACTSendMailCorrect(a0, 0xA2);
                ACTSendMailCorrect(a0, 0xE3);
            } else {
                if (*(int *)(sub + 0x33C) - 0x80 < -100) {
                    ACTSendMailCorrect(a0, 0x14A);
                } else if (100 < *(int *)(sub + 0x33C) - 0x80) {
                    ACTSendMailCorrect(a0, 0x14B);
                    if (isBottomOfChain(*(void **)(sub + 0x190))) {
                        ACTSendMailCorrect(a0, 0x9D);
                    }
                } else if (GOBJ_SUB(a0)->f_4A0 == 0x76) {
                    float bodyori[4];
                    int cor;
                    int ry;

                    GetCorrectOrientOfChain(vec, (void *)a0);
                    SetMotionDirection((void *)a0, vec);
                    if (GetChainDirCorrectVal(*(void **)(sub + 0x190), &cor) != 0) {
                        if (*(int *)(sub + 0x338) - 0x80 < -100) {
                            ACTSendMailCorrect(a0, 0xA0);
                        }
                        if (100 < *(int *)(sub + 0x338) - 0x80) {
                            ACTSendMailCorrect(a0, 0xA1);
                        }
                    } else {
                        if (*(int *)(sub + 0x338) - 0x80 < -100) {
                            ry = 5;
                        } else {
                            ry = 0;
                        }
                        if (100 < *(int *)(sub + 0x338) - 0x80) {
                            ry = -5;
                        }
                        bodyori[0] = ((float *)test_CURRENTORIENT((void *)a0))[0];
                        bodyori[1] = ((float *)test_CURRENTORIENT((void *)a0))[1];
                        bodyori[2] = ((float *)test_CURRENTORIENT((void *)a0))[2];
                        _ApplyRyGV(bodyori, (float)ry * 3.1415927f / 180.0f);
                        SetMotionDirection((void *)a0, bodyori);
                    }
                }
                ACTSendMailCorrect(a0, 0x150);
            }
            break;
        case 0x42:
            if (((int)(*(unsigned long long *)(sub + 0x20) >> 11) & 1) == 0) {
                if (*(int *)(sub + 0x33C) - 0x80 < -100) {
                    ACTSendMailCorrect(a0, 0x14A);
                }
                if (100 < *(int *)(sub + 0x33C) - 0x80) {
                    ACTSendMailCorrect(a0, 0x14B);
                }
            }
            if (GOBJ_SUB(a0)->f_4A0 == 0x76) {
                if (*(int *)(sub + 0x338) - 0x80 < -100) {
                    ACTSendMailCorrect(a0, 0xA0);
                }
                if (100 < *(int *)(sub + 0x338) - 0x80) {
                    ACTSendMailCorrect(a0, 0xA1);
                }
            }
            ACTSendMailCorrect(a0, 0x150);
            if (*(int *)(sub + 0x2E4) & 0x40) {
                ACTSendMailCorrect(a0, 0x13C);
            }
            break;
        case 0x37:
            if (D_00639EA8 != 0 &&
                *(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x40) != 0x5E &&
                *(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x40) != 0x65 &&
                (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] < *(int *)(sub + 0x4C)) {
                if (((int)(*(unsigned long long *)(sub + 0x478) >> 49) & 1) == 0 ||
                    ((int)(*(unsigned long long *)(sub + 0x488) >> 49) & 1) == 0) {
                    ACTSendMailCorrect(a0, 0xF9);
                } else {
                    ACTSendMailCorrect(a0, 0xFA);
                }
            }
            /* falls through into the next arm */
        case 0x44:
            if (((int)(*(unsigned long long *)(sub + 0x478) >> 48) & 1) &&
                ((int)(*(unsigned long long *)(sub + 0x488) >> 48) & 1)) {
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x3E, D_0063A61C);
                }
                ACTSendMailCorrect(a0, 0xFA);
            } else if (NotNeedBackHand() ||
                       (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x3C) != 0x5E &&
                        *(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x3C) != 0x65 &&
                        (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < *(int *)(sub + 0x4C))) {
                if (((int)(*(unsigned long long *)(sub + 0x478) >> 49) & 1) &&
                    ((int)(*(unsigned long long *)(sub + 0x488) >> 49) & 1)) {
                    ACTSendMailCorrect(a0, 0xFA);
                } else {
                    ACTSendMailCorrect(a0, 0xF9);
                }
            }
            break;
        /* the listing's table runs from 1, with this arm empty */
        case 0x1:
            break;
        }
        {
            int tgt2[4];
            int scr2[4];
            int work[4];
            int cam[4];
            int broot[4];
            int ofs[4];
            int cpos[4];

            looking = 0;
            if (((int)(*(unsigned long long *)(sub + 0x478) >> 46) & 1) == 0 ||
                ((int)(*(unsigned long long *)(sub + 0x488) >> 46) & 1) == 0) {
                D_0063C1F0 = 0;
                D_0063C1F1 = 0;
            }
            if (D_00639EA8 != 0 &&
                *(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) == 0x45) {
                sceVu0ScaleVector(vec, test_CURRENTORIENT((void *)a0), 200.0f);
                vec[1] = 0.0f;
                sceVu0AddVector(vec, test_CURRENTROOT((void *)a0), vec);
                _ACTLookTarget_Set((void *)a0, 0, vec, 1, 1);
            }
            if (((int)(*(unsigned long long *)(sub + 0x478) >> 46) & 1) &&
                ((int)(*(unsigned long long *)(sub + 0x488) >> 46) & 1)) {
                int see = 0;
                int onGirl = 0;

                if (D_0063C1F0 == 0) {
                    D_0063C1F0 = 1;
                    if (D_00639EA8 != 0) {
                        D_0063C1F1 =
                            (0.0f < IsPointIsInScreen(scr2, test_CURRENTROOT(D_00639EA8))) ? 1 : 0;
                    }
                }
                if (D_00639EA8 != 0) {
                    ((float *)tgt2)[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                    ((float *)tgt2)[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                    ((float *)tgt2)[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
                    see = 1;
                    onGirl = 1;
                } else if ((stage_no == 0x56 || stage_no == 0x3 || stage_no == 0x2E) &&
                           ((int)(*(unsigned long long *)(sub + 0x20) >> 24) & 3)) {
                    see = 1;
                    onGirl = 0;
                    ScpCallCameraGetTarget((float *)tgt2);
                }
                if (see) {
                    float d = _DistGV(test_CURRENTROOT((void *)a0), (CCPResult *)tgt2);

                    if (d < _ACTGame_GetParamF(3) && onGirl) {
                        _ACTParaStatus_Set((void *)a0, 0x15);
                        _ACTCharStatus_Set((void *)a0, 0x21, -1.0f, 0);
                    } else if (d < _ACTGame_GetParamF(4)) {
                        _ACTParaStatus_Set((void *)a0, 0x14);
                        _ACTCharStatus_Set((void *)a0, 0x23, -1.0f, 0);
                        _ACTParaStatus_Set((void *)a0, 0x13);
                        _ACTCharStatus_Set((void *)a0, 0x22, -1.0f, 0);
                    } else {
                        _ACTParaStatus_Set((void *)a0, 0x13);
                        _ACTCharStatus_Set((void *)a0, 0x22, -1.0f, 0);
                    }
                } else {
                    _ACTParaStatus_Set((void *)a0, 0x13);
                    _ACTCharStatus_Set((void *)a0, 0x22, -1.0f, 0);
                }
                hold = *(int *)(sub + 0x2E0) & 0x8;
                looking = hold != 0;
            }
            if (D_00639EA8 != 0 &&
                (looking ||
                 ((int)(*(unsigned long long *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x20) >>
                        26) &
                  1))) {
                _ACTLookTarget_Set((void *)a0, (int)D_00639EA8, 0, 4, 2);
                if (D_0063C1F1 == 0 && ((int)(*(unsigned long long *)(sub + 0x20) >> 23) & 1)) {
                    if (((int)(*(unsigned long long *)(sub + 0x20) >> 24) & 3) != 0) {
                        void *lo = isysGObjSearchFromObjLayoutID(0x4);

                        if (lo != 0) {
                            ScpCallCameraGetTarget((float *)work);
                            SetRootPosition(lo, work);
                            Camctrl_SetTarget(a0, (int)lo, 1);
                        }
                    } else {
                        Camctrl_SetTarget(a0, (int)D_00639EA8, 1);
                    }
                }
            }
            {
                int i;
                float near = D_0063A6F8[0];

                *(ObjKindList *)work = collisionKinds;
                for (i = 0; work[i] != -1; i++) {
                    void *g;

                    for (g = isysGObjSearchFromObjKindID_begin(work[i]); g != 0;
                         g = isysGObjSearchFromObjKindID_next(g)) {
                        if ((int)(*(unsigned long long *)(*(char **)((char *)g + 0x164) + 0x18) >>
                                  32) &
                            1) {
                            float d = _DistGV(test_CURRENTROOT((void *)a0), test_CURRENTROOT(g));

                            if (work[i] == 47) {
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
                if (ACTGame_NoWeapon((void *)a0) == 0) {
                    if (near < 1000.0f) {
                        _ACTParaStatus_Set((void *)a0, 0x2);
                    }
                    if (near < 300.0f) {
                        _ACTParaStatus_Set((void *)a0, 0x3);
                    }
                }
                if (near < 1000.0f) {
                    _ACTCharStatus_Set((void *)a0, 0x11, near, 0);
                }
            }
            if (_ACTParaStatus_Check((void *)a0, 0x3) || _ACTParaStatus_Check((void *)a0, 0x2)) {
                if (_ACTParaStatus_Check((void *)a0, 0x14)) {
                    _ACTParaStatus_Set((void *)a0, 0x17);
                }
                if (_ACTParaStatus_Check((void *)a0, 0x13)) {
                    _ACTParaStatus_Set((void *)a0, 0x16);
                }
            }
            if (ACTGame_NoWeapon((void *)a0)) {
                _ACTParaStatus_Set((void *)a0, 0x4);
            }
            ACTParaStatus_Exec((void *)a0);
            {
                /* boyact.c:3689-3699 in the listing, inside this function's own
                   span: the weapon search is defined here and inlined into the
                   test below; it has no symbol of its own, so the name is
                   descriptive. */
                inline void *searchWeapon(void)
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

                if (D_00639EA8 == 0 && (w = searchWeapon()) != 0) {
                    if ((*(int *)(sub + 0x2E0) & 0x8) == 0) {
                        D_0063C1F3 = 0;
                        D_0063C1F2 = 0;
                    } else {
                        int mode;
                        int ok;

                        if (D_0063C1F2 == 0) {
                            D_0063C1F3 =
                                (0.0f < IsPointIsInScreen(work, test_CURRENTROOT(w))) ? 1 : 0;
                        }
                        D_0063C1F2 = 1;
                        mode = (int)(*(unsigned long long *)(sub + 0x20) >> 24) & 3;
                        ok = mode == 0;
                        if (stage_no == 0x25 && mode == 2) {
                            ok = 1;
                        }
                        if (((int)(*(unsigned long long *)(sub + 0x20) >> 23) & 1) && ok) {
                            Camctrl_SetTarget(a0, (int)w, 1);
                            camOn = 1;
                            if (stage_no == 0x25) {
                                ((float *)cam)[0] = ((float *)test_CURRENTROOT(w))[0];
                                ((float *)cam)[1] = ((float *)test_CURRENTROOT(w))[1];
                                ((float *)cam)[2] = ((float *)test_CURRENTROOT(w))[2];
                                ScpCallCameraSetTarget(-((float *)cam)[0], -((float *)cam)[1],
                                                       -((float *)cam)[2]);
                                *(unsigned long long *)(sub + 0x20) =
                                    (*(unsigned long long *)(sub + 0x20) & ~0x3000000) | 0x2000000;
                            }
                        }
                    }
                }
            }
            if (camOn == 0 && D_00639EA8 == 0) {
                void *lo = isysGObjSearchFromObjLayoutID(0x4);

                /* RECONSTRUCTION, a deleted-code window (listing row 3748,
                   code-free between the 3747 lookup and the 3749 tests).  What
                   the bytes pin: the ROM issues the lookup's result copy before
                   the 0x2E0 load, which sched1 does only across a block boundary,
                   so a conditional jump on lo alone sits here over a body that
                   flow deletes and that jump.c cannot turn into a store-flag (more
                   than one set); the jump to the next insn then goes in the pass
                   after sched2.  What they cannot pin: the text.  In retail
                   camOn and looking are dead from here on; the DEBUG build's
                   camera report at the end of this block reads them. */
                if (lo == 0) {
                    camOn = 1;
                    looking = 0;
                }
                if ((*(int *)(sub + 0x2E0) & 0x8) && lo != 0) {
                    ((float *)broot)[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
                    ((float *)broot)[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                    ((float *)broot)[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
                    ((float *)cam)[0] = ((float *)GetCurrentCameraSet2())[0];
                    ((float *)cam)[1] = ((float *)GetCurrentCameraSet2())[1];
                    ((float *)cam)[2] = ((float *)GetCurrentCameraSet2())[2];
                    GetOtherStageGirlOrient((float *)ofs, (float *)cam);
                    sceVu0ScaleVector(ofs, ofs, _DistGV((CCPResult *)cam, (CCPResult *)broot));
                    sceVu0AddVector(work, cam, ofs);
                    SetRootPosition(lo, work);
                    /* Local debug switch, off (see dbg in the declarations).
                       What the bytes pin: subBoyCollision reached gcse with 1228
                       to 1231 real insns (the order of the seven spilled frame
                       addresses is pre_delete's hash-bucket walk with 615
                       buckets; the January build's order and its one extra call
                       make it 1231), all of them gone from the final words.  A
                       switch set to 0 outside the loop is that: cse cannot carry
                       the constant across the loop label, gcse's constant
                       propagation folds the test and the next jump pass deletes
                       the guarded call.  What they cannot pin:
                       the text; the marker is actBoySwim's own debug_NMarker
                       call on the helper position just set (rows 3769-3771 are
                       code-free). */
                    if (dbg) {
                        debug_NMarker((float *)work, 0xFF, 0, 0, 100.0f);
                    }
                    if ((int)(*(unsigned long long *)(sub + 0x20) >> 23) & 1) {
                        if (((int)(*(unsigned long long *)(sub + 0x20) >> 24) & 3) != 0) {
                            lo = isysGObjSearchFromObjLayoutID(0x4);
                            if (lo != 0) {
                                ScpCallCameraGetTarget((float *)cpos);
                                SetRootPosition(lo, cpos);
                                Camctrl_SetTarget(a0, (int)lo, 1);
                            }
                        } else {
                            Camctrl_SetTarget(a0, (int)lo, 1);
                        }
                    }
                }
                boyCamDebugDisp(camOn, looking);
            }
            ACTLookTargetSystem_Exec((void *)a0);
            if (D_00639EA4 != 0 && D_00639EA8 != 0 &&
                *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x2D &&
                *(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) ==
                    *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34)) {
                if (0x3C < D_0063C1FC++) {
                    if (D_0063C1F9 == 0) {
                        lt_switch_layout(0x1C);
                        D_0063C1F9 = 1;
                    }
                }
            } else {
                D_0063C1F9 = 0;
                D_0063C1FC = 0;
            }
            if ((_ACTCharStatus_Check((void *)a0, 0x22) ||
                 _ACTCharStatus_Check((void *)a0, 0x23)) &&
                D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x3D, D_0063A61C);
            }
            ((ActStatusWord *)(sub + 0x18))->q =
                (((ActStatusWord *)(sub + 0x18))->q & ~0x20000000000LL) |
                ((unsigned long long)(ACTGame_FLAG_TETSUNAGI() & 1) << 41);
            if (((CHAINROW(a0)->f_18C >> 13) & 1) && ACTGame_FLAG_TETSUNAGI() == 0) {
                ACTSendMailCorrect(a0, 0x1AA);
            }
            if ((int)(*(unsigned long long *)(sub + 0x18) >> 38) & 1) {
                int life = HANG_TARGET(a0)->f3C0;

                if (life < 60) {
                    if (D_00639EA8 != 0) {
                        iosOmSendMail(D_00639EA8, 0xB4, D_0063A61C);
                    }
                } else if (life < 70) {
                    brainAddLevelGirl(20.0f);
                } else {
                    brainAddLevelGirl(10.0f);
                }
            }
        }
        _ACTWait(1);
    }
}

void afterBoySwim(volatile int a0);
extern S12 InitialColInfo;
extern int D_00639EAC;
extern int iosPadActRequest(int port, int id);
extern int GetSkeltonFocusNode(char *a0, int a1);
extern void MoveFloatingBox(void *box, int self, void *m, void *p, float d);
/* kept local: this TU's uses of _DistSqGV do not fit the prototype in gv.h */
extern float _DistSqGV(void *a, void *b);

/* the record Act+0x680 points at, with the fields actBoyBelift and actBoySwim
   touch: the lift level and the lifted object, then the floating-box flag, the
   box GObj and the grip point, a four-float vector sceVu0ApplyMatrix takes
   whole (its w set to 1 before the apply) */
typedef struct {
    char _pad0[0xCC];
    int f_CC; /* 0xCC, the lift level actBoyBelift sets to 10 and clamps */
    char _padD0[0x15C];
    void *f_22C; /* 0x22C, the object the boy lifts (actBoyBelift stores the girl) */
    char _pad230[0x90];
    int f_2C0;   /* 0x2C0 */
    char *f_2C4; /* 0x2C4 */
    char _pad2C8[0x8];
    float f_2D0[4]; /* 0x2D0 */
} BoyExt;

#define BOY_EXT(o) (*(BoyExt **)(*(char **)((char *)(o) + 0x164) + 0x680))

/* RECONSTRUCTION: GObj's 0x15C slot read through a union (typedef.h 98-104: an
   int handle the engine casts to a pointer).  Proof, sched1 dump of this TU
   (-fsched-verbose-5): the ROM's row 3900 order needs the box slot read to
   depend on the float store to the grip point's w while the 0x164 and 0x680
   pointer reads do not, and row 3913 needs each slot read to follow the col-info
   int store before it; under this compiler's TBAA only an alias-set-0 read
   (a union member) conflicts with both the float and the int store.  Only the
   pointer member is attested. */
typedef union {
    char *sub;
} GObjSubSlot;

#define GOBJ_SUBSLOT(o) (((GObjSubSlot *)((char *)(o) + 0x15C))->sub)

void actBoySwim(volatile int a0)
{
    float pos[4];
    char *sub = *(char **)((char *)a0 + 0x164);
    int padReq = 0;

    BOY_EXT(a0)->f_2C0 = 0;
    *(void **)(sub + 0x14) = (void *)afterBoySwim;
    while (1) {
        char *box = BOY_EXT(a0)->f_2C4;

        if (*(int *)(sub + 0x40) == 0xAD) {
            *(unsigned long long *)(sub + 0x20) |= 0x800000000ULL;
        }
        if (BOY_EXT(a0)->f_2C0) {
            RequestChangeHandMode((char *)a0, 0, 3, 1, (int)box, 0, BOY_EXT(a0)->f_2D0);
            BOY_EXT(a0)->f_2D0[3] = 1.0f;
            sceVu0ApplyMatrix(pos, *(void **)(GOBJ_SUBSLOT(box) + 0xC), BOY_EXT(a0)->f_2D0);
            debug_NMarker(pos, 0xFF, 0, 0, 100.0f);
            MoveFloatingBox(box, a0,
                            *(char **)(GOBJ_SUBSLOT(a0) + 0xC) +
                                GetSkeltonFocusNode((char *)a0, 0x13) * 0x40 + 0x30,
                            BOY_EXT(a0)->f_2D0, 30.0f);
            if (!(_DistSqGV(test_CURRENTROOT((void *)a0), pos) < 4e+04f)) {
                BOY_EXT(a0)->f_2C0 = 0;
            }
            ((S12 *)(GOBJ_SUBSLOT(a0) + 0x1C0))->a = (int)box;
            ((S12 *)(GOBJ_SUBSLOT(a0) + 0x1C0))->b = -1;
            ((S12 *)(GOBJ_SUBSLOT(a0) + 0x1C0))->c = 0;
            if (!padReq) {
                iosPadActRequest(D_00639EAC, 6);
                padReq = 1;
            }
            if ((int)(*(unsigned long long *)(sub + 0x20) >> 35) & 1) {
                if (*(int *)(GOBJ_SUBSLOT(a0) + 0x4CC) || *(int *)(GOBJ_SUBSLOT(a0) + 0x4C8)) {
                    iosPadActRequest(D_00639EAC, 7);
                }
            }
        } else {
            RequestChangeHandMode((char *)a0, 0, 3, 0, 0, 0, 0);
            padReq = 0;
            *(S12 *)(GOBJ_SUBSLOT(a0) + 0x1C0) = InitialColInfo;
        }
        _ACTWait(1);
    }
}

void actBoyWalk(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, D_00639EA4, 2);
            GetSkeltonPosition(gp, D_00639EA8, 0x12);
            d = _DistGV((CCPResult *)gp, (CCPResult *)bp);
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 100 / 60 <
                    *(int *)((char *)sub + 0x4C) &&
                80.0f < d) {
                d = (d - 80.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.9 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

void actBoyRun(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    while (1) {
        if (ACTGame_FLAG_TETSUNAGI()) {
            float gp[4];
            float bp[4];
            float d;
            float ratio;

            GetSkeltonPosition(bp, D_00639EA4, 2);
            GetSkeltonPosition(gp, D_00639EA8, 0x12);
            d = _DistGV((CCPResult *)gp, (CCPResult *)bp);
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 100 / 60 <
                    *(int *)((char *)sub + 0x4C) &&
                90.0f < d) {
                d = (d - 90.0f) / 10.0f;
                d = d < 0.0f ? 0.0f : (1.0f < d ? 1.0f : d);
                ratio = 0.7 - d * 0.2;
                ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, ratio, 2);
            }
        }
        _ACTWait(1);
    }
}

inline void actBoyFall(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actBoyFall\n");
    sub->unk34 = 5;
    while (1) {
        _ACTWait(1);
    }
}

extern void BoyAttackCenter(int a0);
/* kept local: this TU's uses of SetMotionDirectionWithLimit do not fit the prototype in motionManager2.h */
extern void SetMotionDirectionWithLimit(void *self, float *dir, float lo, float hi);

/* INTERIM: ACTSearchEnemy is a file-scope `inline` in the original TU (rows
   1671/1674, around ACTSearchGObj's 1644-1661; see ACTSearchGObj_inl above
   subBoyCollision); its out-of-line copy sits in the TU's inline tail, where
   the plain definition stays.  Fold it back when the tail is C. */
static inline void ACTSearchEnemy_inl(void *a0, int *out_id, float *out_vec)
{
    ACTSearchGObj_inl(a0, (*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4, 0x5A, out_id, out_vec, 300.0f);
}

void actBoyAttack(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);
    int mot = *(int *)(sub + 0x10);
    float vec[4];

    *(unsigned long long *)(sub + 0x20) |= 0x100000000ULL;
    *(int *)(sub + 0x450) = mot;
    debug_StdPrintfDummy("attack sub id [%d]\n", mot);
    debug_StdPrintfDummy("enter actBoyAttack\n");
    _ACTWait(2);
    ACTSearchEnemy_inl((void *)a0, (int *)(sub + 0x188), vec);
    while (1) {
        if (*(int *)(sub + 0x188)) {
            if (ACTGame_NoWeapon((char *)a0)) {
                SetMotionDirectionWithLimit((void *)a0, vec, 5.0f, 45.0f);
            } else {
                SetMotionDirectionWithLimit((void *)a0, vec, 10.0f, 90.0f);
            }
        }
        ACTSendMailCorrect(a0, 0xC7);
        BoyAttackCenter(a0);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of SetMotionDirection do not fit the prototype in motionManager2.h */
extern void SetMotionDirection(void *self, float *dir);
/* kept local: this TU's uses of _ACTMotDirSmzDirect do not fit the prototype in commonact.h */
extern void _ACTMotDirSmzDirect(void *self, float *dir);

void actBoyTakeWeaponReady(volatile int a0)
{
    float w[4];
    float p[4];
    float dir[4];
    char *obj;
    int first = 1;
    int n = 0;

    obj = *(char **)(*(char **)((char *)a0 + 0x164) + 0x608);
    w[0] = ((float *)test_CURRENTROOT(obj))[0];
    w[1] = ((float *)test_CURRENTROOT(obj))[1];
    w[2] = ((float *)test_CURRENTROOT(obj))[2];
    while (1) {
        p[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
        p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
        p[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
        _OrientXZGV(dir, w, p);
        if (first) {
            SetMotionDirection((void *)a0, dir);
            first = 0;
        } else if (_AbsRotyGV(test_CURRENTORIENT((void *)a0), dir) < 0x1E) {
            _ACTMotDirSmzDirect((void *)a0, dir);
        } else {
            ACTSendMailCorrect(a0, 0xCC);
        }
        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < n++) {
            ACTSendMailCorrect(a0, 0xCC);
        }
        _ACTWait(1);
    }
}

/* sub->0x14 is the actor's "after" callback slot: actBoyTakeWeapon arms it with
   afterBoyTakeWeapon and calls it through the slot once the motion frame passes
   the swap point, so it is written and read as a function pointer. */
typedef void (*BoyAfterFunc)(volatile int a0);

void actBoyTakeWeapon(volatile int a0)
{
    float p[4];
    float dir[4];
    Act *sub = GOBJ_ACT(a0);
    int picked = 0;
    int put = 0;

    InitSwapWeapon((void *)a0);
    *(BoyAfterFunc *)((char *)sub + 0x14) = afterBoyTakeWeapon;
    p[0] = ((float *)test_CURRENTROOT(BOYINFO.nextWeapon))[0];
    p[1] = ((float *)test_CURRENTROOT(BOYINFO.nextWeapon))[1];
    p[2] = ((float *)test_CURRENTROOT(BOYINFO.nextWeapon))[2];
    _OrientXZGV(dir, p, test_CURRENTROOT((void *)a0));
    SetMotionDirection((void *)a0, dir);
    while (1) {
        if (GOBJ_SUB(a0)->f_4A0 == 0xE6) {
            if (15.0f < GOBJ_SUB(a0)->f_4AC && GOBJ_SUB(a0)->f_4AC < 48.0f && !picked) {
                PickupWeapon(BOYINFO.nextWeapon, (void *)a0, 6);
                picked = 1;
            }
            if (30.0f < GOBJ_SUB(a0)->f_4AC && !put) {
                if (BOYINFO.weapon != 0) {
                    ReleaseWeapon(BOYINFO.weapon);
                    ExecuteSEPackage((int)BOYINFO.weapon, 0x50);
                }
                PutWeapon();
                put = 1;
            }
            if (48.0f < GOBJ_SUB(a0)->f_4AC) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(a0);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        } else {
            if (16.0f < GOBJ_SUB(a0)->f_4AC) {
                if (*(BoyAfterFunc *)((char *)sub + 0x14) != 0) {
                    (*(BoyAfterFunc *)((char *)sub + 0x14))(a0);
                    *(BoyAfterFunc *)((char *)sub + 0x14) = 0;
                }
            }
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of ACTAdjustPlane do not fit the prototype in commonact.h */
extern void ACTAdjustPlane(int a0, void *p);
/* kept local: this TU's uses of GetOrientOfWall do not fit the prototype in fieldCollision.h */
extern void GetOrientOfWall(void *out, void *wall, void *pos);
/* kept local: this TU's uses of CompareAttribute do not fit the prototype in fieldCollision.h */
extern int CompareAttribute(int attr, int mask);

#define BOY_WALL(o) (*(char **)(*(char **)((char *)(o) + 0x164) + 0x688))

void actBoyCliffHesitate(volatile int a0)
{
    int hit = 0;

    ACTAdjustPlane(a0, BOY_WALL(a0) + 0x8C0);
    GetOrientOfWall(BOY_WALL(a0) + 0x8D0, *(void **)(BOY_WALL(a0) + 0x8C8), BOY_WALL(a0) + 0x8C0);
    if (CompareAttribute(*(int *)(*(char **)(BOY_WALL(a0) + 0x8C8) + 0x48), 0x400)) {
        hit = 1;
        *(S12 *)(BOY_WALL(a0) + 0x490) = *(S12 *)(BOY_WALL(a0) + 0x8C0);
    }
    while (1) {
        if (hit) {
            ACTSendMailCorrect(a0, 0x8C);
        }
        if (D_00639EA8 != 0) {
            brainSetSpMode();
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x3D, D_0063A61C);
            }
        }
        ACTSendMailCorrect(a0, 0x128);
        _ACTWait(1);
    }
}

inline void actBoyCall(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    debug_StdPrintfDummy("enter actBoyCall\n");
    sub->unk34 = 9;
    _ACTWait(2);
    if (D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x41, D_0063A61C);
    }
    while (1) {
        if ((*(int *)((char *)sub + 0x2E0) & 8) == 0) {
            ACTSendMailCorrect(a0, 0xC7);
        }
        _ACTWait(1);
    }
}

#define BOY_GIRL_DY()                                                                              \
    (((float *)test_CURRENTROOT(D_00639EA8))[1] - ((float *)test_CURRENTROOT(D_00639EA4))[1])

void ACTSendMail_PULLUP_GO(void)
{
    char *g = (char *)D_00639EA4;
    Act *sub = GOBJ_ACT(g);

    switch (*(int *)((char *)sub + 0x5E4)) {
    case 0x64:
        ACTSendMailCorrect((int)g, 0x4A);
        sub->f_44 = 0x6B;
        break;
    case 0xC8:
        ACTSendMailCorrect((int)g, 0x4A);
        sub->f_44 = 0x6D;
        break;
    case 0x12C:
        if (GOBJ_ACT(D_00639EA8)->unk34 != 0x50) {
            break;
        }
        if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()))) {
            ACTSendMailCorrect((int)g, 0x4A);
            sub->f_44 = 0x6F;
        } else if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x52, D_0063A61C);
        }
        break;
    }
}

/* boyact.c:4386-4398 in the listing: the pull-up start mail, inlined into
   actBoyPullupGo; it has no symbol of its own and no census row, so the name is
   descriptive. */
static inline void ACTSendMail_PULLUP_START(void)
{
    Act *sub = GOBJ_ACT(D_00639EA4);

    switch (*(int *)((char *)sub + 0x5E4)) {
    case 0x64:
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x51, D_0063A61C);
        }
        GOBJ_ACT(D_00639EA8)->f_44 = 0x65;
        break;
    case 0xC8:
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x51, D_0063A61C);
        }
        GOBJ_ACT(D_00639EA8)->f_44 = 0x66;
        break;
    case 0x12C:
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x51, D_0063A61C);
        }
        GOBJ_ACT(D_00639EA8)->f_44 = 0x67;
        break;
    }
}

extern void sceVu0SubVector(void *, CCPResult *, CCPResult *);
extern float sceVu0InnerProduct(void *a, void *b);
/* kept local: this TU's uses of _DistSqGV do not fit the prototype in gv.h */
extern float _DistSqGV(void *a, void *b);

int pullup_check_heroin_position(void)
{
    float buf[4];
    float p1[4];
    float p2[4];
    char *g = (char *)D_00639EA4;
    Act *s = GOBJ_ACT(g);

    if (D_00639EA0 != 0 && *(int *)((char *)s + 0x5E4) == 300) {
        switch (GOBJ_ACT(D_00639EA8)->unk34) {
        case 4:
            GetSkeltonPosition(p1, D_00639EA8, 0x16);
            GetSkeltonPosition(p2, D_00639EA4, 6);
            if (_DistSqGV(p1, p2) < 3600.0f) {
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x59, D_0063A61C);
                }
            }
            return 0;
        case 0x51:
            ACTSendMailCorrect((int)D_00639EA4, 0x58);
            return 0;
        default:
            return 0;
        }
    }
    sceVu0SubVector(buf, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    if (0.0f < sceVu0InnerProduct(buf, (char *)s + 0x4C0) &&
        _DistxzGV((char *)s + 0x500, test_CURRENTROOT(D_00639EA8)) < 100.0f &&
        ((unsigned int)(*(unsigned long long *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x18) >>
                        54) &
         1) &&
        (D_00639EA8 == 0 || D_00639EA4 == 0 ||
         !(test_CURRENTROOT(D_00639EA8)->f4 > test_CURRENTROOT(D_00639EA4)->f4 + 450.0f))) {
        return 1;
    }
    return 0;
}

int ditch_check_heroin_position(void)
{
    float buf[4];
    Act *s = GOBJ_ACT(D_00639EA4);

    sceVu0SubVector(buf, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    if (0.0f < sceVu0InnerProduct(buf, (float *)((char *)s + 0x4C0)) &&
        _DistxzGV((char *)s + 0x510, test_CURRENTROOT(D_00639EA8)) < 31.0f &&
        (D_00639EA8 == 0 || D_00639EA4 == 0 ||
         !(test_CURRENTROOT(D_00639EA8)->f4 > test_CURRENTROOT(D_00639EA4)->f4 + 200.0f))) {
        return 1;
    }
    return 0;
}

extern char D_0055FFA8[];
/* kept local: this TU's uses of _MoveGV do not fit the prototype in gv.h */
extern void _MoveGV(float *dst, float *from, float *to, float d);
extern int IsCorrectPosition(char *a0);

void actBoyPullupReady(volatile int a0)
{
    float mv[4];

    /* boyact.c:4478-4483 in the listing, inside this function's own span: the
       helper is defined here and inlined at the pull-up test; it has no symbol
       of its own, so the name is descriptive. */
    inline unsigned char isGirlWithinPullupHeight(void)
    {
        float boy[4];
        float girl[4];

        GetRootProjectionPosOfGObj(boy, D_00639EA4);
        GetRootProjectionPosOfGObj(girl, D_00639EA8);
        if (GOBJ_ACT(D_00639EA8)->unk34 == 0x26 ||
            (boy[1] - girl[1] < 0.0f ? -(boy[1] - girl[1]) : boy[1] - girl[1]) < 50.0f) {
            return 1;
        }
        return 0;
    }
    Act *sub = GOBJ_ACT(a0);

    ACTAdjustPlane(a0, BOY_WALL(a0) + 0x8C0);
    while (1) {
        if (*(unsigned char *)(BOY_WALL(a0) + 0x4F0) &&
            *(int *)(GOBJ_SUB(a0)->f_4A0 * 0x194 + D_0055FFA8) != 1) {
            _MoveGV(mv, (float *)test_CURRENTROOT((void *)a0), (float *)(BOY_WALL(a0) + 0x500),
                    3.0f);
            SetRootPosition((char *)a0, mv);
        }
        _ACTCharStatus_Set((char *)a0, 0x1C, -1.0f, 0);
        if ((*(int *)((char *)sub + 0x2E0) & 8) == 0 || isGirlWithinPullupHeight()) {
            ACTSendMailCorrect(a0, 0x49);
        } else if (pullup_check_heroin_position()) {
            if (PAIR_IsStatus_GIRL_PULL() == 0) {
                if (!(300.0f < (BOY_GIRL_DY() < 0.0f ? -BOY_GIRL_DY() : BOY_GIRL_DY()) &&
                      *(int *)(BOY_WALL(D_00639EA8) + 0x3B4))) {
                    if (D_00639EA8 != 0) {
                        iosOmSendMail(D_00639EA8, 0x4F, D_0063A61C);
                    }
                }
            } else if (IsCorrectPosition(D_00639EA8) == 0) {
                ACTSendMail_PULLUP_GO();
            }
        }
        _ACTWait(1);
    }
}

/* the boy is hauling the girl up: moving while the grip ratio is between 0.1
   and 0.99 or the hold flag is set */
#define BOY_PULLUP_MOVING(sub)                                                                     \
    (0.1f < *(float *)((char *)(sub) + 0x34C) &&                                                   \
     (*(float *)((char *)(sub) + 0x34C) < 0.99f || (*(int *)((char *)(sub) + 0x2E0) & 0x20)))

void actBoyPullupGo(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    ACTSendMail_PULLUP_START();
    while (1) {
        if (PAIR_IsStatus_GIRL_PULL() == 0) {
            ACTSendMailCorrect(a0, 0x4B);
        } else {
            if (0.1f < *(float *)((char *)sub + 0x34C) && !BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(a0, 0x4C);
            } else if (BOY_PULLUP_MOVING(sub)) {
                ACTSendMailCorrect(a0, 0x4D);
            } else {
                ACTSendMailCorrect(a0, 0x4E);
            }
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of RotQuaternionX do not fit the prototype in quaternion.h */
extern void RotQuaternionX(float *q, short a);
/* kept local: this TU's uses of SetMotionNodeFixModeParameter do not fit the prototype in motionManager2.h */
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);
extern int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout);
extern void InsertCamera_Set(float *pos, float *tgt, int frames);
extern char D_005577F4[];

void actBoyBelift(volatile int a0)
{
    /* RECONSTRUCTION: the quaternion is reached through a union, the form
       actEnemyKidnapEnd (enemy_act.c) gives the same memset-and-w=1 idiom.
       Proof, sched1 dump of this TU: the ROM stores q's w before it loads
       girl->0x164 for line 4603, a true dependence, and under this compiler's
       TBAA only an alias-set-0 access (a union member) makes a float store to
       the stack conflict with that load.  Only the float member is attested. */
    union {
        float f[4];
    } q;

    float cam[4];
    float boypos[4];
    float p[4];
    float girlpos[4];
    float dir[4];
    float ofs[4];
    float hit[4];
    char *girl = *(char **)(*(char **)((char *)a0 + 0x164) + 0x2C);
    float ratio;
    int mode;
    int lv;
    float dist;

    memset(&q, 0, 0x10);
    q.f[3] = 1.0f;
    ratio = 1.0f;
    if (*(int *)(*(int *)(*(int *)(girl + 0x164) + 0x680) + 0x1E4) == 3) {
        ratio = 0.2f;
    }
    mode = *(int *)(*(int *)(*(int *)(girl + 0x164) + 0x680) + 0x1E4) == 3 ? 0 : 2;
    BOY_EXT(a0)->f_22C = girl;
    D_0063C200 = girl;
    BOY_EXT(a0)->f_CC = 10;
    if (*(int *)(*(int *)(*(int *)(girl + 0x164) + 0x680) + 0x1E4) == 3) {
        RotQuaternionX(q.f, 0x4000);
    }
    SetMotionNodeFixModeParameter((void *)a0, girl, mode, 0x16, q.f, 0.0f, 0.0f, 0.0f, ratio);
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    _ACTWait(1);
    while (1) {
        if (*(int *)(*(char **)(*(char **)(girl + 0x164) + 0x680) + 0x1E4) == 3 &&
            *(unsigned int *)(*(char **)(girl + 0x164) + 0x34) == 0x61) {
            lv = BOY_EXT(a0)->f_CC;
            lv = lv < 0 ? 0 : (10.0f < lv ? 10.0f : lv);
            lv = lv * 0.5f;
            dist = lv * 100.0f + 500.0f;
            GetSkeltonPosition(boypos, D_00639EA4, 0x23);
            GetSkeltonPosition(girlpos, girl, 0x23);
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
            GetSkeltonPosition(girlpos, D_00639EA4, 0x2C);
            sceVu0ScaleVector(p, p, -1.0f);
            sceVu0ScaleVector(girlpos, girlpos, -1.0f);
            InsertCamera_Set(p, girlpos, (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 6);
        }
        switch (*(unsigned int *)(*(char **)(girl + 0x164) + 0x34)) {
        case 0x61:
        case 0x62:
            break;
        default:
            ACTSendMailCorrect(a0, 0xE2);
            debug_StdPrintfDummy("enemy error body slam[%s]\n",
                                 D_005577F4 +
                                     *(unsigned int *)(*(char **)(girl + 0x164) + 0x34) * 0x50);
            break;
        }
        _ACTWait(1);
    }
}

extern char D_0055FE58[];

/* The walk order the boy is executing: sub->0x30 points at the request record
   the caller filled in, and actBoyReadyMove works on a private copy of it. */
typedef struct {
    float pos[4];
    float dir[4];
    float range;
    int frames;
    int fix;
    int _2C;
} __attribute__((aligned(16))) BoyMoveOrder;

/* the motion parameter table: one 0x194-byte row per motion id */
typedef struct {
    char _000[0x182];
    short f_182;
    char _184[0x02];
    short f_186;
    char _188[0x0C];
} BoyMotionRow;

void actBoyReadyMove(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    BoyMoveOrder ord = *(BoyMoveOrder *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x30));

    while (1) {
        if ((((void *)a0 == D_00639EA8 && D_00639EA0 != 0)
                 ? ((BoyMotionRow *)(GOBJ_SUB(a0)->f_4A0 * sizeof(BoyMotionRow) + D_0055FE58))
                       ->f_182
                 : ((BoyMotionRow *)(GOBJ_SUB(a0)->f_4A0 * sizeof(BoyMotionRow) + D_0055FE58))
                       ->f_186) == 0) {
            SetMotionDirectionSmooze((void *)a0, ord.dir, 10.0f);
        } else {
            _ACTMotDirSmzDirect((void *)a0, ord.dir);
        }
        if (ord.fix) {
            *(unsigned long long *)((char *)sub + 0x490) |= 0x80000;
            *(unsigned long long *)((char *)sub + 0x490) |= 0x40;
        }
        if (ord.frames-- < 0) {
            ACTSendMailCorrect(a0, 0x10A);
        }
        if (_DistxzSqGV(test_CURRENTROOT((void *)a0), &ord) < ord.range * ord.range) {
            ACTSendMailCorrect(a0, 0x10A);
        }
        if (0.1f < *(float *)((char *)sub + 0x34C) &&
            100 < _AbsRotyGV(ord.dir, (char *)sub + 0x120)) {
            ACTSendMailCorrect(a0, 0x10A);
        }
        _ACTWait(1);
    }
}

void actBoyRescueReady(volatile int a0)
{
    char *g = *(char **)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x2E0);
    float p[4];
    float q[4];
    float step[4];
    float dir[4];
    float tmp[4];
    float np[4];

    union {
        float f[4];
        long long ll[2];
    } pts[2];

    int cnt = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 3;
    int rest, hp, r;
    int n1, n2;
    char *hold;
    int u = 0;
    int gm = *(int *)(*(char **)((char *)D_00639EA8 + 0x15C) + 0x4A0);
    int t;

    p[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
    p[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    p[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
    q[0] = ((float *)test_CURRENTROOT(g))[0];
    q[1] = ((float *)test_CURRENTROOT(g))[1];
    q[2] = ((float *)test_CURRENTROOT(g))[2];
    _OrientXZGV(dir, q, p);
    sceVu0ScaleVector(tmp, dir, -60.0f);
    sceVu0AddVector(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x2F0, q, tmp);
    sceVu0ScaleVector(tmp, dir, 0.0f);
    sceVu0AddVector(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x300, q, tmp);
    ((float *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x300))[1] += 50.0f;
    SetMotionDirection((void *)a0, dir);
    sceVu0SubVector(step, (CCPResult *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x2F0),
                    (CCPResult *)p);
    sceVu0ScaleVector(step, step, 1.0f / (float)cnt);
    t = 1;
    rest = cnt;
    while (1) {
        if (0 < rest) {
            sceVu0AddVector(np, test_CURRENTROOT((void *)a0), step);
            np[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            SetDirectRootPositionNoFitting((void *)a0, np);
        }
        rest--;
        if (*(int *)(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) * 0x194 + D_0055FFA8) == 1 ||
            (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x480) & 0x16) ||
            *(void **)(*(char **)((char *)a0 + 0x15C) + 0x4CC) != 0) {
            hold = *(char **)(*(char **)((char *)D_00639EA8 + 0x164) + 0x144);
            hp = *(int *)(*(char **)(hold + 0x164) + 0x4C);
            r = 0;
            /* ROM-proven vestigial read (listing rows 4809-4810 carry no code):
               the bytes pin a load of D_0028F4C0 here, before the call, into a
               variable live code reads elsewhere, with no division by
               D_0028F4C0[1] (a dead divide keeps its trap). Its high part is
               what loop.c hoists, and that pre-header copy is what gives the
               entry block the ROM's `li v1,10`. The statement text is not
               pinned; n1 stands in for the developer's variable. */
            n1 = D_0028F4C0[0];
            ACTGame_ConnectHand();
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 100 / 60 <= hp) {
                r = hp * ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 3) /
                    ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10);
            }
            /* ROM-proven vestigial (listing row 4819): only the bltz on r and
               the divide-by-zero trap on D_0028F4C0[1] survive of this
               statement; the quotient itself is never read. */
            if (0 <= r) {
                r = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
            }
            if (D_00639EB4 == 0) {
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x15D, D_0063A61C);
                }
            }
            n1 = GetSkeltonFocusNode(D_00639EA8, 0x16);
            n2 = GetSkeltonFocusNode(D_00639EA4, 6);
            pts[0].f[0] = *(float *)(*(char **)(*(char **)((char *)D_00639EA8 + 0x15C) + 0xC) +
                                     n1 * 0x40 + 0x30);
            pts[0].f[1] = *(float *)(*(char **)(*(char **)((char *)D_00639EA8 + 0x15C) + 0xC) +
                                     n1 * 0x40 + 0x34);
            pts[0].f[2] = *(float *)(*(char **)(*(char **)((char *)D_00639EA8 + 0x15C) + 0xC) +
                                     n1 * 0x40 + 0x38);
            pts[1].f[0] = *(float *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x15C) + 0xC) +
                                     n2 * 0x40 + 0x30);
            pts[1].f[1] = *(float *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x15C) + 0xC) +
                                     n2 * 0x40 + 0x34);
            pts[1].f[2] = *(float *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x15C) + 0xC) +
                                     n2 * 0x40 + 0x38);
            SetDirectRootPositionNoFittingWithNodePoint((void *)a0, 6, pts[0].f, 0.05f);
            u = t++;
        }
        if (gm == 641) {
            if ((u / 30) & 1) {
                ACTSendMailCorrect(a0, 0x160);
            } else {
                ACTSendMailCorrect(a0, 0x15F);
            }
        } else {
            if ((u / 15) & 1) {
                ACTSendMailCorrect(a0, 0x160);
            } else {
                ACTSendMailCorrect(a0, 0x15F);
            }
        }
        _ACTWait(1);
    }
}

extern int ResetMotionProgramInterpInfo(char *a0, int a1);

void actBoyDitch3mReady(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);
    float p[4];
    float q[4];
    int c = 0;
    int a;
    int b;

    ACTAdjustPlane(a0, BOY_WALL(a0) + 0x8C0);
    _ACTWait(1);
    ResetMotionProgramInterpInfo((char *)a0, 35);
    ResetMotionProgramInterpInfo((char *)a0, 1);

    while (1) {
        a = 1;
        b = 0;
        switch (*(unsigned int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34)) {
        case 4:
        case 90:
            p[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
            p[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
            p[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            q[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
            q[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
            q[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
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

        if (GOBJ_ACT(D_00639EA8)->unk34 != 4 &&
            _DistSqGV(test_CURRENTROOT(D_00639EA4), (char *)sub + 0x510) < 90000.0f &&
            _DistSqGV(test_CURRENTROOT(D_00639EA8), (char *)sub + 0x510) < 90000.0f) {
            c = 1;
        }

        if (c != 0) {
            if (GOBJ_ACT(D_00639EA8)->unk34 == 4) {
                *(int *)(BOY_WALL(a0) + 0x3C8) = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 3;
            }
            _ACTParaStatus_Set((void *)a0, 40);
            _ACTCharStatus_Set((void *)a0, 29, -1.0f, 0);
            HANG_TARGET(a0)->f348 = 30.0f;
            ACTSendMailCorrect(a0, 0x187);
        }

        /* Two branches with one body: the listing gives the b test a row of
           its own (4992) and keeps only the second copy (4993-4994); the
           post-reload cross-jump merges the first into it, after the
           allocator has counted c's test in both (which puts c in s2). */
        if (a != 0 && (*(int *)((char *)sub + 0x2E0) & 8) == 0) {
            ACTSendMailCorrect(a0, 0x189);
            if (c != 0) {
                ACTSendMailCorrect(a0, 0x18A);
            }
        } else if (b != 0) {
            ACTSendMailCorrect(a0, 0x189);
            if (c != 0) {
                ACTSendMailCorrect(a0, 0x18A);
            }
        } else {
            if (D_00639EA0 == 0) {
                if (ditch_check_heroin_position() != 0) {
                    if (D_00639EA8 != 0) {
                        iosOmSendMail(D_00639EA8, 0x18C, D_0063A61C);
                    }
                }
                if (IsCorrectPosition(D_00639EA8) == 0) {
                    if (D_00639EA8 != 0) {
                        iosOmSendMail(D_00639EA8, 0x18D, D_0063A61C);
                    }
                }
            }
            if (GOBJ_ACT(D_00639EA8)->unk34 == 4 && c == 0) {
                float dy;

                b = 0;
                dy = test_CURRENTROOT(D_00639EA8)->f4 - test_CURRENTROOT(D_00639EA4)->f4;
                if (_DistxzSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) <
                        10000.0f &&
                    ABSF(BOYGIRL_DY()) < 100.0f) {
                    b = 1;
                }
                if (_DistxzSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) <
                        78400.0f &&
                    ABSF(BOYGIRL_DY()) < 200.0f && 50.0f < dy && dy < 200.0f) {
                    b = 1;
                }
                GetSkeltonPosition(p, D_00639EA8, 22);
                GetSkeltonPosition(q, D_00639EA4, 6);
                if (_DistSqGV(p, q) < 3600.0f) {
                    b = 1;
                }
                if (*(unsigned char *)((char *)sub + 0x530) != 0) {
                    b = 0;
                }
                if (b != 0) {
                    if (D_00639EA8 != 0) {
                        iosOmSendMail(D_00639EA8, 0x18F, D_0063A61C);
                    }
                    ACTSendMailCorrect(a0, 0x18B);
                }
            }
        }
        _ACTWait(1);
    }
}

extern char D_0055FFA8[];
/* kept local: this TU's uses of _MoveGV do not fit the prototype in gv.h */
extern void _MoveGV(float *dst, float *from, float *to, float d);

void actBoyRescueGirlBhang(volatile int a0)
{
    float tgt[4];
    float mv[4];
    float boy[4];
    float girl[4];
    Act *sub = GOBJ_ACT(a0);
    int mode;
    int connect = 1;

    *(void **)((char *)sub + 0x18) = (void *)afterBoyRescueGirlBhang;
    while (1) {
        mode = 0;
        switch (GOBJ_ACT(D_00639EA8)->unk34) {
        case 0x1C:
            mode = 1;
            break;
        case 0x1D:
            mode = 2;
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2 < *(int *)((char *)sub + 0x4C)) {
                if (connect) {
                    ACTGame_ConnectHand();
                    connect = 0;
                }
            }
            break;
        }
        if (mode != 0) {
            if (*(int *)((char *)sub + 0x4C) < 0xA) {
                boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
                boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
                boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
                girl[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
                girl[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
                girl[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
                tgt[0] = girl[0];
                tgt[2] = girl[2];
                tgt[1] = boy[1];
                _MoveGV(mv, boy, tgt, 5.0f);
                SetRootPosition((void *)a0, mv);
            }
        }
        if (*(int *)(GOBJ_SUB(a0)->f_4A0 * 0x194 + D_0055FFA8) == 1) {
            if (mode == 1) {
                ACTSendMailCorrect(a0, 0x15B);
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x51, D_0063A61C);
                }
                GOBJ_ACT(D_00639EA8)->f_44 = 0x66;
            }
            if (mode == 2) {
                ACTSendMailCorrect(a0, 0x15B);
                if (D_00639EA8 != 0) {
                    iosOmSendMail(D_00639EA8, 0x40, D_0063A61C);
                }
            }
        }
        if (mode == 0) {
            ACTSendMailCorrect(a0, 0xC7);
        }
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of RequestStageChangeSimple do not fit the prototype in script.h */
extern int RequestStageChangeSimple(void *a0, int a1, int a2, int a3, float a4, float a5);

inline int RequestStageChangeKidnapEnd(void *a0, int a1)
{
    int rv = 0;
    if (D_00639EA4 != 0) {
        rv = RequestStageChangeSimple(a0, 0, 0, 0, 0.25f, 4.0f) & 0xFF;
        if (rv != 0) {
            Vec16 buf = {{-1000000.0f, 0.0f, 0.0f}};

            BOYEFSTAGE[0] = 1;
            *(int *)(BOYEFSTAGE + 4) = a1;
            ACTGame_StageChangeGObjDirect(D_00639EA4, a0, &buf, 0);
        }
    }
    return rv;
}

/* kept local: this TU's uses of InsertCamera_SetNoraml do not fit the prototype in camera-root.h */
extern void InsertCamera_SetNoraml(float *a, float *b, int c, int d);

void SetStatusBoy_OtherStageGirlPinch(void)
{
    float buf[4];
    float cam[4];
    float pos[4];
    char *g = (char *)D_00639EA4;
    char *w;
    float a;
    float b;
    float t;
    int frames;

    a = _ACTGame_GetParamF(0xD);
    b = _ACTGame_GetParamF(0xE);
    t = a * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f +
        b * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f;
    ExecuteSEPackage(0, 0x7F);
    GetOtherStageGirlOrient(buf, GetCurrentCameraSet2());
    w = *(char **)(*(char **)(g + 0x164) + 0x688);
    frames = (int)t;
    *(int *)(w + 0x4B0) = frames;
    *(float *)(w + 0x4A0) = buf[0];
    *(float *)(w + 0x4A4) = buf[1];
    *(float *)(w + 0x4A8) = buf[2];
    cam[0] = GetCurrentCameraSet2()[0];
    cam[1] = GetCurrentCameraSet2()[1];
    cam[2] = GetCurrentCameraSet2()[2];
    pos[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    pos[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    pos[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    InsertCamera_SetNoraml(cam, pos, frames, 0);
}

extern char D_002A84F8[];
extern void *D_0063A70C;
/* not declared by the headers this TU includes; the act.c entry points as
   girl_act.c declares them for actGirlStart */
extern char *actInitialize(void *self);
extern void actInitialize_ext_charcter(void *self);
extern void actInitialize_only_charcter(void *self);
extern void actInitialize_geo(void *self);
extern int actCreateSubThread(void *entry, int prio);
extern void subCommonIdle(void);
extern void subBoyBrainMain(int a0);
extern void *MatrixDrive_GetMatrix(void);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void LightTorchOnOfWeaponWithNoSE(void *w);

void actBoyStart(int a0)
{
    char *work;
    void *g;

    D_0063C1F4 = BOYINFO.escort;
    BOYINFO.escort = 0;

    ((int *)D_006C0AD0)[4] = -1;

    D_0063C1F5 = 0;
    D_0063C1F6 = 0;
    D_0063C1F7 = 0;
    D_0063C1F8 = 0;
    D_0063C1F9 = 0;

    D_0063C1FC = 0;
    debug_StdPrintfDummy("actBoyStart:%p\n", a0);

    work = actInitialize(a0);
    *(void **)(work + 0x68C) = D_006C0AC0;

    GetRootPosition(work + 0x110, (void *)a0);

    actInitialize_ext_charcter(a0);
    actInitialize_only_charcter(a0);
    actInitialize_geo(a0);

    *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x680) + 0x254) =
        (int)(_ACTGame_GetParamF(0x21) * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) /
              60.0f);
    ACTGame_LwsEffectInit(a0);

    *(int *)(work + 0x180) = 0;
    *(int *)(work + 0x184) = 0;

    D_0063A70C = 0;
    ACTParaStatus_Init(a0);
    _ACTCharStatus_Init(a0);

    _ACTWait(1);

    D_00639EC0 = (void *)a0;

    *(float *)(work + 0x1E0) = _ACTGame_GetParamF(0x13);
    *(int *)(work + 0x48) = 0;

    if (BOYINFO.boyID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.boyID);
        if (g != 0) {
            PickupWeapon(g, (void *)a0, 0x16);
            *(void **)(work + 0x150) = g;
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
            ACTSendMailCorrect(a0, 0x35);
            *(void **)(work + 0x184) = *(void **)(work + 0x154) = g;
        } else {
            BOYINFO.girlID = 0;
        }
        D_0063C1F6 = 1;
    }

    if (BOYINFO.layoutID != 0) {
        g = isysGObjSearchFromObjLayoutID(BOYINFO.layoutID);
        if (g != 0) {
            Vec16 p0 = {{0.0f, 0.0f, -50.0f, 1.0f}};
            Vec16 p1 = {{0.0f, 0.0f, 50.0f, 1.0f}};
            BoyWallWork cw;

            CopyMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)((char *)g + 0x15C) + 0xC));
            MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
            sceVu0ApplyMatrix(&cw, MatrixDrive_GetMatrix(), &p0);
            sceVu0ApplyMatrix((char *)&cw + 0x10, MatrixDrive_GetMatrix(), &p1);
            cw.f70 = 0.0f;
            ClipWall(&cw);
            if (cw.f88 == 0) {
                /* "!!! cannot find the sofa's wall !!!" */
                debug_StdPrintfDummy("！！！ソファの壁を見付けることができません！！！\n");
            } else {
                D_0063C1F8 = 1;
                D_0063C1F9 = 1;
                D_006C0AB0.pos = cw.f80;
                D_006C0AB0.hit = cw.f88;
                D_0063AA08 = 0;
                ActSendMail_WithAdditionalData((void *)a0, 0x36, (void *)a0, &D_006C0AB0);
                if (BOYINFO.bit32 && D_00639EA8 != 0) {
                    ActSendMail_WithAdditionalData(D_00639EA8, 0x36, D_00639EA8, &D_006C0AB0);
                }
            }
        } else {
            BOYINFO.layoutID = 0;
        }
    }

    D_0063C1F7 = 0;

    *(void **)(work + 0xD0) = D_002A84F8;

    actCreateSubThread(subBoyBrainMain, 20);
    D_0063A70C = (void *)actCreateSubThread(subBoyControl, 21);
    actCreateSubThread(subBoyCollision, 21);
    actCreateSubThread(subCommonIdle, 21);

    *(void **)(work + 0xD4) = D_002A84F8 + 0x78;
    ACTSendMailCorrect(a0, 0xC7);

    _ACTWait(1);

    if (BOYINFO.fire && D_00639EA8 != 0) {
        iosOmSendMail(D_00639EA8, 0x3F, (void *)a0);
        debug_StdPrintfDummy("hand connect start\n");
        /* Disabled in retail: the way-begin report of the landing.  What the
           bytes pin: its text in .rodata right after "hand connect start\n",
           with no instruction; the listing's lines 5749-5750, empty between
           this print (5748) and the final wait (5751), are where it fits.
           What they cannot: the condition that disabled it.  girl_act.c's
           actGirlDitch3mExec carries the same pair. */
        if (0) {
            debug_StdPrintfDummy("WBP set [landing]\n");
        }
    }
    _ACTWait(0);
}

/* kept local: this TU's uses of ConvertStickToAbsCoord do not fit the prototype in act.h */
extern void ConvertStickToAbsCoord();
/* kept local: this TU's uses of _RotyGV do not fit the prototype in gv.h */
extern int _RotyGV();

/* `stick` is never named in the body: the ROM leaves $a1 untouched and
   ConvertStickToAbsCoord reads it straight out of the incoming register, so the
   stick record reaches it through the argument register alone. */
inline int CorrectStickInfo(void *dir, void *stick)
{
    int buf[4];
    ConvertStickToAbsCoord(buf);
    return _RotyGV(buf, dir);
}

inline void *GetBoyWeaponGObj(void)
{
    char *g = (char *)D_00639EA4;
    if (g != 0) {
        return *(void **)(*(char **)(g + 0x164) + 0x150);
    }
    return 0;
}

typedef struct {
    char pad00[0x18C];
    unsigned int flags18C;
    char pad190[4];
} BoyParaRow;

inline void actBoyStand(volatile int a0)
{
    BoyParaRow *row = (BoyParaRow *)(GOBJ_SUB(a0)->f_4A0 * sizeof(BoyParaRow) + D_0055FE58);

    if ((row->flags18C >> 8) & 1) {
        ACTAdjustPlane(a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
    }
    while (1) {
        _ACTWait(1);
    }
}

inline void actBoyHang(volatile int a0)
{
    char *g = (char *)a0;
    ACTAdjustPlane(a0, *(char **)(*(char **)(g + 0x164) + 0x688) + 0x8B0);
    _ACTWait(0);
}

inline void actBoyBHang(volatile int a0)
{
    char *g = (char *)a0;
    ACTAdjustPlane(a0, *(char **)(*(char **)(g + 0x164) + 0x688) + 0x8B0);
    _ACTWait(0);
}

inline void actBoyHangBefore(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    ACTAdjustPlane(a0, (char *)HANG_TARGET(a0) + 0x8C0);
    HANG_TARGET(a0)->f470 = *(float *)((char *)sub + 0x4C0);
    HANG_TARGET(a0)->f474 = *(float *)((char *)sub + 0x4C4);
    HANG_TARGET(a0)->f478 = *(float *)((char *)sub + 0x4C8);
    HANG_TARGET(a0)->f480 = *(S12 *)((char *)sub + 0x630);
    while (1) {
        ACTSendMailCorrect(a0, 0x128);
        _ACTWait(1);
    }
}

inline void actBoyBeslam(volatile int a0)
{
    char *p = (char *)GOBJ_SUB(a0) + 0x130;

    sceVu0ScaleVector(p, test_CURRENTORIENT(D_0063C200), 30.0f);
    while (1) {
        ACTSendMailCorrect(a0, 0x13A);
        _ACTWait(1);
    }
}

inline void actBoyRescueSrc(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actBoySupportGBBegin(volatile int a0)
{
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x17D, D_0063A61C);
        }
        ACTSendMailCorrect(a0, 0x17B);
        _ACTWait(1);
    }
}

static inline unsigned char IsBoyStatus_SupportGB(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34);
    if (st < 0x6B) {
        if (st >= 0x68) {
            return 1;
        }
    }
    return 0;
}

inline void actBoySupportGBLoop(volatile int a0)
{
    while (1) {
        if (!IsBoyStatus_SupportGB()) {
            ACTSendMailCorrect(a0, 0xE2);
        }
        _ACTWait(1);
    }
}

inline void actBoySupportGBEnd(volatile int a0)
{
    while (1) {
        if (D_00639EA8 != 0) {
            iosOmSendMail(D_00639EA8, 0x17F, D_0063A61C);
        }
        ACTSendMailCorrect(a0, 0xC7);
        _ACTWait(1);
    }
}

inline void actBoySupportBGBegin(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0x183);
        _ACTWait(1);
    }
}

inline void actBoyDitch3mExec(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0x190);
        _ACTWait(1);
    }
}

inline void actBoyHangG3M(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    *(void **)((char *)sub + 0x18) = (void *)afterBoyHangG3M;
    while (1) {
        if (0.1f < *(float *)((char *)sub + 0x34C) || (*(int *)((char *)sub + 0x2E0) & 0x10)) {
            ACTSendMailCorrect(a0, 0x192);
            if (D_00639EA8 != 0) {
                iosOmSendMail(D_00639EA8, 0x195, D_0063A61C);
            }
        }
        _ACTWait(1);
    }
}

inline unsigned char IsAbleBoyControl(void)
{
    return D_0063C1F5;
}

inline void ACTSearchEnemy(void *a0, int *out_id, float *out_vec)
{
    float buf[4];
    void *node;
    int best;
    float thresh = 300.0f;

    node = isysGObjSearchFromObjKindID_begin((*(int *)((char *)a0 + 0xC) ^ 1) ? 1 : 4);
    *out_id = 0;
    best = 0x5A;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
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
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}

inline void DeleteBoyWeapon(void)
{
    union {
        float f[4];
        long long ll[2];
    } buf;

    char *sub;

    if (D_00639EA4 != 0) {
        sub = *(char **)((char *)D_00639EA4 + 0x164);
        if (*(void **)(sub + 0x150) != 0) {
            ReleaseWeapon(*(void **)(sub + 0x150));
            memset(&buf, 0, 0x10);
            buf.f[0] = 10000000.0f;
            SetDirectRootPositionNoFitting(*(void **)(sub + 0x150), buf.f);
            gamesysObjInfoPosSetStage(*(int **)(sub + 0x150), 0, 0, stage_no);
            *(int *)(*(char **)(sub + 0x150) + 0x16C) = 0;
        }
        D_006C0B30[2] = 0;
        ((int *)D_006C0AD0)[0] = 0;
        *(void **)(sub + 0x150) = 0;
    }
}

inline int isLiftBoyEnable(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);
    if (st >= 0x60) {
        return 1;
    }
    if (st < 0x5E) {
        return 1;
    }
    return 0;
}

inline void SetKidnapInfo(int a0, int a1)
{
    D_006C0B30[5] = a0;
    D_006C0B30[6] = a1;
}

inline void GetKidnapInfo(int *a0, int *a1)
{
    *a0 = D_006C0B30[5];
    *a1 = D_006C0B30[6];
}

inline void PrivInsCamSet(float *pos, float *tgt, int a2, int a3, int a4, float f5, float f6,
                          unsigned char a7)
{
    D_006C0B50.pos[0] = pos[0];
    D_006C0B50.pos[1] = pos[1];
    D_006C0B50.pos[2] = pos[2];
    D_006C0B50.tgt[0] = tgt[0];
    D_006C0B50.tgt[1] = tgt[1];
    D_006C0B50.tgt[2] = tgt[2];
    D_006C0B50.unk20 = a2;
    D_006C0B50.unk24 = a3;
    D_006C0B50.unk28 = a4;
    D_006C0B50.unk2C = f5;
    D_006C0B50.unk30 = f6;
    D_006C0B50.unk34 = a7;
    D_006C0B50.on = 1;
}

inline int IsBoyStatus_EnemyMustWait(void)
{
    char *sub;
    unsigned int st;

    if (D_00639EA4 == 0) {
        debug_assert(__FILE__, 5795);
        __assert(__FILE__, 5795, D_0063A6D0);
        return 0;
    }
    sub = *(char **)((char *)D_00639EA4 + 0x164);
    st = *(unsigned int *)(sub + 0x34);
    if (st >= 0x13) {
        if (st >= 0x16) {
            if (st < 0x18) {
                return 1;
            }
        } else if (*(int *)(*(char **)(sub + 0x680) + 0x29C) != 0) {
            return 1;
        }
    }
    if (st == 0x15 || 0 < *(int *)(*(char **)(sub + 0x688) + 0x37C)) {
        return 1;
    }
    return 0;
}

inline int IsGirlEscortedInNextStage(void)
{
    return (int)((unsigned char)((unsigned long long)D_006C0AD0[1] >> 35)) & 1;
}

inline unsigned char IsGirlEscortedInCurrentStage(void)
{
    return D_0063C1F4;
}

inline int GetSaveSofaLayoutID(void)
{
    int *a = (int *)D_00639EA4;
    int *b = (int *)D_00639EA8;
    int *pa, *pb, *r;
    int v;
    if (a == 0)
        goto err;
    if (b == 0)
        goto err;
    pa = (int *)a[0x164 / 4];
    v = pa[0x34 / 4];
    if (v != 0x2D)
        goto err;
    pb = (int *)b[0x164 / 4];
    if (pb[0x34 / 4] != v)
        goto err;
    r = (int *)pa[0x160 / 4];
    return r[2];
err:
    return -1;
}

inline void OnGirlEscortFlag(void)
{
    D_006C0AD0[1] |= 0x800000000LL;
}

inline void SetBoyWeaponGObj(void *w)
{
    if (D_00639EA4 != 0 && w != 0) {
        SwapBoyWeapon(0, w, D_00639EA4);
    }
}

inline int IsBoyStatus_NotDanger(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);
    if (st < 0x17) {
        if (st >= 0x14) {
            return 1;
        }
    }
    return 0 < *(int *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x688) + 0x37C);
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

inline int PrivInsCamChk(void)
{
    return D_006C0B50.on != 0;
}

inline unsigned char PrivInsCamChk_Control(void)
{
    return D_006C0B50.unk34;
}

inline int *GetbufpCharacterPacket(void)
{
    return D_006C0B30;
}

inline int GetsizeCharacterPacket(void)
{
    return 32;
}

inline void MakeCharacterPacket(void)
{
    char *pkt = (char *)D_006C0B30;
    char *sub;
    char *g;

    *(BoyKidnapWork *)D_006C0B30 = D_0029C670;
    if (D_00639EA4 != 0) {
        sub = *(char **)((char *)D_00639EA4 + 0x164);
        if (*(char **)(sub + 0x150) != 0) {
            *(int *)(pkt + 0x8) = *(int *)(*(char **)(sub + 0x150) + 0x8);
        }
        if (*(char **)(sub + 0x154) != 0) {
            *(int *)(pkt + 0xC) = *(int *)(*(char **)(sub + 0x154) + 0x8);
        }
        if (*(int *)(sub + 0x34) == 0x2D) {
            *(int *)(pkt + 0x10) = *(int *)(*(char **)(sub + 0x160) + 0x8);
        }
        g = (char *)D_00639EA8;
        if (g != 0 && GOBJ_ACT(g)->unk34 == 0x2D) {
            *(int *)(pkt + 0x1C) |= 1;
        }
        BoyInfoUpdate_StageChange();
        *(int *)(pkt + 0x1C) =
            (*(int *)(pkt + 0x1C) & ~0x10000) |
            (((int)((unsigned char)((unsigned long long)D_006C0AD0[1] >> 34)) & 1) << 16);
        *(unsigned char *)(pkt + 0x1D) =
            (int)((unsigned char)((unsigned long long)D_006C0AD0[1] >> 33)) & 1;
        *(CharPos *)pkt = BOYINFO.f50;
    }
}

inline void BoyInfoUpdate_StageChange(void)
{
    char *g = (char *)D_00639EA4;
    Act *sub = GOBJ_ACT(g);
    char *w;
    int x;

    BOYINFO.torch = 0;
    w = *(char **)((char *)sub + 0x150);
    if (w != 0) {
        x = ACTGame_isWeaponEnableCatchfire(w);
        if (x != 0) {
            if (IsTorchLightOn(x)) {
                BOYINFO.torch = 1;
            }
        }
    }
    BOYINFO.fire = 0;
    if (ACTGame_FLAG_TETSUNAGI()) {
        BOYINFO.fire = 1;
    }
}

typedef struct {
    CharPos pos; /* 0x00 */
    int boyID;   /* 0x08 */
    int girlID;  /* 0x0C */
    int f10;     /* 0x10 */
    int f14;
    int f18;
    unsigned int b1C : 8; /* 0x1C */
    unsigned int b1D : 8;
    unsigned int h1E : 16; /* 0x1E */
} CharacterPacket;

inline void ReadCharacterPacket(void)
{
    CharacterPacket *p = (CharacterPacket *)D_006C0B30;

    BOYINFO.boyID = p->boyID;
    BOYINFO.girlID = p->girlID;
    BOYINFO.layoutID = p->f10;
    BOYINFO.bit32 = p->b1C;
    BOYINFO.fire = p->b1D;
    BOYINFO.torch = p->h1E;
    BOYINFO.f50 = p->pos;
}

inline void ACTSearchGObj(void *a0, int a1, int a2, int *out_id, float *out_vec, float thresh)
{
    float buf[4];
    void *node;
    int best;

    node = isysGObjSearchFromObjKindID_begin(a1);
    *out_id = 0;
    best = a2;
    if (node != 0) {
        do {
            if (*(int *)((char *)node + 0x16C) != 0) {
                CCPResult *r1 = test_CURRENTROOT(a0);
                if (_DistGV(r1, test_CURRENTROOT(node)) < thresh) {
                    int sign;
                    int dist;
                    CCPResult *r4 = test_CURRENTROOT(node);
                    sceVu0SubVector(buf, r4, test_CURRENTROOT(a0));
                    sign = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    if (sign < 0) {
                        dist = -((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
                    } else {
                        dist = ((int (*)(void *, void *))_RotyGV)(buf, test_CURRENTORIENT(a0));
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
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
}

extern S12 InitialColInfo;
extern char D_0063A700[];

inline void afterBoySwim(volatile int a0)
{
    RequestChangeHandMode((void *)a0, 0, 3, 0, 0, 0, 0);
    *(S12 *)((char *)GOBJ_SUB(a0) + 0x1C0) = InitialColInfo;
    debug_StdPrintfDummy(D_0063A700);
}

inline void actBoyJump(volatile int a0)
{
    while (1) {
        ACTSendMailCorrect(a0, 0xBD);
        _ACTWait(1);
    }
}

inline void afterBoyTakeWeapon(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    SwapBoyWeapon(BOYINFO.weapon, BOYINFO.nextWeapon, (void *)a0);
    *(void **)((char *)sub + 0x150) = BOYINFO.nextWeapon;
}

inline void afterBoyHangG3M(int x)
{
    volatile int local = x;
}

inline void afterBoyRescueGirlBhang(volatile int a0)
{
    ACTGame_DisconnectHand();
}

/* kept local: this TU's uses of _ACTWait do not fit the prototype in act.h */
extern void _ACTWait();

inline void subBoyBrainMain(int a0)
{
    volatile int local = a0;
    while (1) {
        _ACTWait(1);
    }
}

inline void SetBoyInfo(int *a0, int *a1)
{
    int n;
    int i;
    if (a0 != 0) {
        ((int *)D_006C0AD0)[0] = a0[2];
    } else {
        ((int *)D_006C0AD0)[0] = 0;
    }
    i = 0;
    n = 1;
    if (a1 != i) {
        ((int *)D_006C0AD0)[n] = a1[2];
    } else {
        ((int *)D_006C0AD0)[n] = i;
    }
}

inline void GetBoyRootPositionForCamera(float *out)
{
    float buf[4];
    char *g = (char *)D_00639EA4;
    char *sub;

    sub = *(char **)(g + 0x164);
    GetRootPosition(buf, g);
    if (_DistSqGV(buf, sub + 0x110) < 40000.0f) {
        out[0] = *(float *)(sub + 0x110);
        out[1] = *(float *)(sub + 0x114);
        out[2] = *(float *)(sub + 0x118);
    } else {
        GetRootPosition(sub + 0x110, g);
        out[0] = buf[0];
        out[1] = buf[1];
        out[2] = buf[2];
    }
}

inline void Boy_Init(void)
{
    *(BoyWork *)D_006C0AD0 = D_0029C610;
    *(BoyKidnapWork *)D_006C0B30 = D_0029C670;
}
