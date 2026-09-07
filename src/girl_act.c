#include "common.h"

typedef struct {
    char _0[0x20];
    float f_20;        /* 0x20 */
    char _24[0x0C];
    float sub30[4];    /* 0x30 */
    float sub40[4];    /* 0x40 */
    float f_50;        /* 0x50 */
    float f_54;        /* 0x54 */
    unsigned char f_58;  /* 0x58 */
    unsigned char f_59;
    unsigned char f_5A;
    unsigned char f_5B;
    unsigned char f_5C;
    unsigned char f_5D;
    unsigned char f_5E;
} GirlStand;

union GAIF { int i; float f; };
extern int GetSkeltonFocusNode(void *obj, int kind);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);

void GetEyeDirection(char *dir, char *obj)
{
    int node = GetSkeltonFocusNode(obj, 0x23);
    if (*(int *)(obj + 0xC) == 4) {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = -1.0f;
        *(int *)(dir + 0x8) = 0;
    } else {
        *(int *)(dir + 0x0) = 0;
        ((union GAIF *)(dir + 0x4))->f = 1.0f;
        *(int *)(dir + 0x8) = 0;
    }
    *(int *)(dir + 0xC) = 0;
    sceVu0ApplyMatrix(dir, (char *)(*(int *)(*(int *)(obj + 0x15C) + 0xC) + (node << 6)), dir);
}
extern void ACTGame_DisconnectHand(void);
extern char D_00553990[];
extern void debug_StdPrintfDummy__pn(void *a0) __asm__("debug_StdPrintfDummy");

void funcGirlHandDisconnect(void) {
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy__pn(D_00553990);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", motGirlHand50);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", motGirlHand100);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", motGirlHand200);
extern int D_002A5580[];
extern void brainClsTargetLevel();

void GirlBrainClearTarget(void)
{
    brainClsTargetLevel(D_002A5580);
}
extern void ACTGame_SetMotionPlaySpeedRatio_Reserve(void *a0, int a1, float f);
void SetTurnSpeedInEscape(char *a0) {
    if (*(int *)(*(char **)(a0 + 0x164) + 0x34) == 10) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve(a0, 5, 1.5f);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", sort_list);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_MakeOthersList);
ASM_LIT4_SLOT(D_00638F64, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainHideCheckIntercept);
ASM_LIT4_SLOT(D_00638F68, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_CheckWarningMode);
ASM_LIT4_SLOT(D_00638F6C, 160000.0f);
ASM_LIT4_SLOT(D_00638F70, 40000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_DecideMode);
extern char D_002A2E70[];
extern int *D_00639EA4;
extern void *D_00639EA8;
extern void GetRootPosition(void *out, void *obj);
extern void GetRootProjectionPosOfGObj(void *out, void *obj);

void girlBrainMain_PositionUpdate(void) {
    GetRootPosition(D_002A2E70 + 0x00, D_00639EA8);
    GetRootPosition(D_002A2E70 + 0x20, D_00639EA4);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x10, D_00639EA8);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x30, D_00639EA4);
}
extern char D_0029D650[];
extern void *memset(void *dst, int c, int n);
void girlBrainMain_Init(void) {
    memset(D_0029D650, 0, 0x5920);
}
typedef struct {
    char _0[0x58F8];
    int  runMode;
    int  wait;
    int  timer;
    int  limit;
} GirlBrainWork;
extern float D_002A5594[];
extern char D_0029D4A0[];
extern char D_005D3EF0[];
extern int rand(void);

void ChangeRunMode(int mode)
{
    volatile int home;
    int uninit;
    int n;
    int t;
    int lo;
    int hi;

    home = uninit;
    ((GirlBrainWork *)D_0029D650)->runMode = mode;
    ((GirlBrainWork *)D_0029D650)->timer = 0;
    ((GirlBrainWork *)D_0029D650)->wait = rand() % 3;
    n = (int)D_002A5594[0];
    n = n / 3;
    n = (n < 0) ? 0 : ((n < 4) ? n : 3);
    t = *(int *)(D_0029D4A0 + n * 16);
    lo = *(int *)(t * 16 + mode * 8 + D_005D3EF0);
    hi = *(int *)(D_005D3EF0 + (t * 16 + mode * 8) + 4);
    ((GirlBrainWork *)D_0029D650)->limit = lo + rand() % (hi - lo);
}
ASM_LIT4_SLOT(D_00638F74, 250000.0f);
ASM_LIT4_SLOT(D_00638F78, 22500.0f);
ASM_LIT4_SLOT(D_00638F7C, 160000.0f);
ASM_LIT4_SLOT(D_00638F80, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrainMain);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Pulledup);
extern int D_006C1E20[];
extern void GetSkeltonOrient(float *out, void *obj, int node);
extern int _RotyGV(void *buf, void *vec);

static inline void ATGoalTurnSet(int prio, int dir, float *v)
{
    if (prio >= D_006C1E20[0]) {
        D_006C1E20[0] = prio;
        D_006C1E20[1] = dir;
        *(float *)&D_006C1E20[4] = v[0];
        *(float *)&D_006C1E20[5] = v[1];
        *(float *)&D_006C1E20[6] = v[2];
    }
}

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
            ATGoalTurnSet(2, 2, v);
        } else {
            ATGoalTurnSet(2, 1, v);
        }
        ret = 1;
    }
    return ret;
}
ASM_LIT4_SLOT(D_00638F84, 2300.0f);
ASM_LIT4_SLOT(D_00638F88, 850.0f);
ASM_LIT4_SLOT(D_00638F8C, 2300.0f);
ASM_LIT4_SLOT(D_00638F90, 850.0f);
ASM_LIT4_SLOT(D_00638F94, 750.0f);
ASM_LIT4_SLOT(D_00638F98, 650.0f);
ASM_LIT4_SLOT(D_00638F9C, 950.0f);
ASM_LIT4_SLOT(D_00638FA0, 1900.0f);
ASM_LIT4_SLOT(D_00638FA4, 870.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", checkWaterfallResult);
ASM_LIT4_SLOT(D_00638FA8, 90000.0f);
ASM_LIT4_SLOT(D_00638FAC, 10000.0f);
ASM_LIT4_SLOT(D_00638FB0, 40000.0f);
ASM_LIT4_SLOT(D_00638FB4, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Attract);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", _girlBrainHide_MakeHidePoint);
extern void GetRootMotionOrient(float *out, void *obj);
extern int _RotyGV(void *buf, void *vec);
extern void ACTSendMailCorrect(void *a0, int mail);
extern void debug_StdPrintfDummy();
extern char D_00553BF0[];
extern char D_00553C00[];

void girlBrainHide_GoalTurn(float *dir, unsigned char sendMail)
{
    float mo[4];
    float eye[4];
    char *girl;
    char *p;
    int r;

    girl = (char *)D_00639EA8;
    GetRootMotionOrient(mo, girl);
    r = _RotyGV(mo, dir);
    r = (r < 0) ? -r : r;
    if (r >= 0x2E) {
        p = *(char **)(*(char **)(girl + 0x164) + 0x688);
        *(float *)(p + 0x3F0) = dir[0];
        *(float *)(p + 0x3F4) = dir[1];
        *(float *)(p + 0x3F8) = dir[2];
        GetEyeDirection((char *)eye, girl);
        if (_RotyGV(eye, dir) > 0) {
            debug_StdPrintfDummy(D_00553BF0);
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xEC);
            } else {
                ACTSendMailCorrect(girl, 0xEE);
            }
        } else {
            debug_StdPrintfDummy(D_00553C00);
            if (sendMail) {
                ACTSendMailCorrect(girl, 0xEB);
            } else {
                ACTSendMailCorrect(girl, 0xED);
            }
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isHideRecheck);
ASM_LIT4_SLOT(D_00638FB8, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Hide);
ASM_LIT4_SLOT(D_00638FBC, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00174CE8);
ASM_LIT4_SLOT(D_00638FC0, 10000.0f);
ASM_LIT4_SLOT(D_00638FC4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawaySearchPoint);
ASM_LIT4_SLOT(D_00638FC8, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainRunawayMoveByWay);
ASM_LIT4_SLOT(D_00638FCC, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Escape);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", ClipTwinVector);
ASM_LIT4_SLOT(D_00638FD0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", GetSafePosition);
ASM_LIT4_SLOT(D_00638FD4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", Danger_Bomb);
ASM_LIT4_SLOT(D_00638FD8, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001762A0);
ASM_LIT4_SLOT(D_00638FDC, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", Danger_Gondola);
ASM_LIT4_SLOT(D_00638FE0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176838);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", Danger_Box);
ASM_LIT4_SLOT(D_00638FE4, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00177098);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", Danger_Rotobject);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_HideAdvance);
ASM_LIT4_SLOT(D_00638FE8, 1500.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isEnterHideadv_EnemyLocation);
extern int D_00639EA4__pn __asm__("D_00639EA4");
extern void *D_00629DE4, *D_00639EA8__pn __asm__("D_00639EA8");
extern float _DistxzSqGV(void *, void *);
extern int isEnterHideadv_EnemyLocation(void *, void *);

int isEnterHideadv(void) {
    char buf[0x20];
    int rv = 0;
    float diff;
    if (D_00639EA4__pn == 0) {
        goto ret0;
    }
    if (D_00639EA8__pn == 0) {
        return 0;
    }
    GetRootProjectionPosOfGObj(buf, D_00639EA4__pn);
    GetRootProjectionPosOfGObj(buf + 0x10, D_00639EA8__pn);
    diff = *(float *)(buf + 0x4) - *(float *)(buf + 0x14);
    if (diff < 0.0f) {
        if (-diff > 200.0f) {
            goto set;
        }
        goto test;
    }
    if (diff > 200.0f) {
    set:
        rv = 1;
    }
test:
    if (rv == 0) {
        goto ret0;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 22500.0f) {
        return 1;
    }
    if (_DistxzSqGV(buf, buf + 0x10) < 250000.0f) {
        if (isEnterHideadv_EnemyLocation(buf, buf + 0x10) != 0) {
            return 1;
        }
    }
ret0:
    return 0;
}
extern int D_0028F8F4[];
extern unsigned char D_0063A8E0[4];
extern unsigned char D_0063A8E4;
extern char D_0063A8E8[];
extern char D_00553C78[];
extern int D_0063C244;
extern void debug_StdPrintfDummy();
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
extern int _RotyGV(void *buf, void *vec);
extern int ACTWayMove_BeginDetail(void *obj, float *b, float *a, void *tgt, int e, int f);
extern int ACTWayMove_NextDetail(void *obj, char *w, float *a, int d, int e);
extern void debug_Marker(void *buf, int a1, int a2, int a3, float f12, float f13);

/* girl_brain_main.c.inc:313-317 (rows outside WayTest's span => static inline) */
static inline void dispWayMarker(char *p)
{
    float buf[4];
    sceVu0ScaleVector(buf, (float *)(p + 0x10), -1.0f);
    debug_Marker(buf, 0xFF, 0, 0, 70.0f, 0.0f);
}

void WayTest(void)
{
    float a[4];
    float b[4];
    char *s;
    void *g;
    int r;

    g = D_00639EA8;
    s = *(char **)((char *)g + 0x164);
    GetRootProjectionPosOfGObj(b, g);
    GetRootProjectionPosOfGObj(a, D_00639EA4);
    if ((D_0028F8F4[0] & 8) || D_0063A8E0[3]) {
        debug_StdPrintfDummy(D_0063A8E8);
        D_0063A8E4 = ACTWayMove_BeginDetail(g, b, a, D_00639EA4, 0, 0);
        D_0063A8E0[3] = 0;
    }
    if (D_0063A8E4) {
        if (!ACTWayMove_NextDetail(g, s + 0x120, a, 0, 0)) {
            debug_StdPrintfDummy(D_00553C78);
        }
        dispWayMarker(s + 0x400);
    }
    if (*(float *)(s + 0x3F8) < 100.0f) {
        *(float *)(s + 0x34C) = 0.0f;
    } else {
        *(float *)(s + 0x34C) = 1.0f;
    }
    r = _RotyGV(s + 0x3E0, s + 0x120);
    r = (r < 0) ? -r : r;
    if (r >= 0x5B) {
        D_0063C244 = D_0063C244 + 1;
        *(float *)(s + 0x120) = *(float *)(s + 0x3E0);
        *(float *)(s + 0x124) = *(float *)(s + 0x3E4);
        *(float *)(s + 0x128) = *(float *)(s + 0x3E8);
    } else {
        *(float *)(s + 0x120) = *(float *)(s + 0x3E0);
        *(float *)(s + 0x124) = *(float *)(s + 0x3E4);
        *(float *)(s + 0x128) = *(float *)(s + 0x3E8);
        D_0063C244 = 0;
    }
    dispWayMarker(*(char **)(s + 0x380));
    dispWayMarker(*(char **)(s + 0x384));
}
ASM_LIT4_SLOT(D_00638FF4, 0.001f);
ASM_LIT4_SLOT(D_00638FF8, 0.1f);
ASM_LIT4_SLOT(D_00638FFC, 0.1f);
ASM_LIT4_SLOT(D_00639000, 0.99f);
ASM_LIT4_SLOT(D_00639004, 0.1f);
ASM_LIT4_SLOT(D_00639008, 0.99f);
ASM_LIT4_SLOT(D_0063900C, 0.1f);
ASM_LIT4_SLOT(D_00639010, 0.1f);
ASM_LIT4_SLOT(D_00639014, 0.1f);
ASM_LIT4_SLOT(D_00639018, 0.1f);
ASM_LIT4_SLOT(D_0063901C, 0.1f);
ASM_LIT4_SLOT(D_00639020, 0.1f);
ASM_LIT4_SLOT(D_00639024, 0.1f);
ASM_LIT4_SLOT(D_00639028, 0.1f);
ASM_LIT4_SLOT(D_0063902C, 0.1f);
ASM_LIT4_SLOT(D_00639030, 250000.0f);
ASM_LIT4_SLOT(D_00639034, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlControl);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlCollision);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_GetDistHand);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Update);
extern GirlStand D_002A2F70;
extern int _RotyGV(void *buf, void *vec);

void HandMgr_Judge(void) {
    volatile int home;
    int uninit;
    float one = 1.0f;
    home = uninit;
    if (D_002A2F70.f_20 < 2.0f) {
        D_002A2F70.f_58 = 1;
    }
    if ((_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30) < 0
            ? -_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)
            : _RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)) >= 0x3D) {
        D_002A2F70.f_59 = 1;
    }
    if (D_002A2F70.f_54 > 15.0f) {
        D_002A2F70.f_5E = 1;
    }
    if (one * 100.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5A = 1;
    }
    if (one * 125.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5B = 1;
    }
    if (one * 135.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5C = 1;
    }
    if (D_002A2F70.f_50 < 90.0f) {
        D_002A2F70.f_5D = 1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Print);
ASM_LIT4_SLOT(D_00639038, 0.9f);
ASM_LIT4_SLOT(D_0063903C, 1.1f);
ASM_LIT4_SLOT(D_00639040, 1.4f);
ASM_LIT4_SLOT(D_00639044, 1.3f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", HandMgr_Speed);
extern char D_0055FE58[];

void GetBoyMode(int *mode, int *p1, int *p2, int *p3)
{
    /* Static-chain home: GetBoyMode is a gcc nested function of
       actGirlHand (caller sets $2 = its $sp before the jal), so the
       prologue stores the incoming chain register into frame slot 0.
       Same stand-in as the matched sibling HandMgr_Judge above; it is
       replaced by a real nested definition once actGirlHand is C.  */
    volatile int home;
    int uninit;
    char *rec;
    home = uninit;
    *mode = ((int *)D_00639EA4[0x59])[0xD];
    *p1 = 0;
    *p2 = 0;
    *p3 = 0;
    switch (*mode) {
    case 14:
        *mode = 1;
        break;
    case 15:
        *mode = 1;
        break;
    case 8:
        *mode = 1;
        break;
    case 2:
    case 3:
        if (((int *)D_00639EA4[0x59])[0x55] != 0) {
            *mode = 2;
        }
        rec = D_0055FE58 + ((int *)D_00639EA4[0x57])[0x128] * 0x194;
        switch ((*(unsigned int *)(rec + 0x188) >> 22) & 3) {
        case 1:
            *mode = 2;
            break;
        case 2:
            *mode = 3;
            break;
        }
        if (*mode == 3) {
            unsigned long long f = *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            } else if ((int)(f >> 32) & 1) {
                *mode = 2;
            }
        }
        if (*mode == 2) {
            unsigned long long f = *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            }
        }
        break;
    case 36:
        if (((int *)D_00639EA4[0x59])[0xF] == 0x5E) {
            *p2 = 1;
        } else {
            *mode = 1;
        }
        break;
    case 5:
    case 13:
    case 17:
    case 18:
    case 68:
        *mode = 3;
        break;
    }
}
ASM_LIT4_SLOT(D_00639048, 0.1f);
ASM_LIT4_SLOT(D_0063904C, -1.5707964f);
ASM_LIT4_SLOT(D_00639050, 0.1f);
ASM_LIT4_SLOT(D_00639054, 0.7f);
ASM_LIT4_SLOT(D_00639058, 0.6f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand);
extern void PAIR_GetPosition_BOY(float *boy, float *dir);
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern void *test_CURRENTROOT(void *a0);
extern float _DistxzGV(void *a, void *b);
extern void StartCorrectPosition(void *obj, float *dst, float *cur, float dist, int flag);
extern int IsCorrectPosition(void *obj);
extern void ContinueCorrectPosition(void *obj);
extern int PAIR_IsStatus_BOY_PULL(void);
extern void ACTSendMailCorrect(void *a0, int mail);
extern void _ACTWait(int n);

void actGirlPulledReady(volatile int a0)
{
    float boy[4];
    float dir[4];
    float pos[4];
    float dst[4];
    float d;
    float v;

    GetRootPosition(pos, (void *)a0);
    PAIR_GetPosition_BOY(boy, dir);
    sceVu0ScaleVector(dst, dir, 30.0f);
    sceVu0AddVector(dst, boy, dst);
    dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    sceVu0ScaleVector(dir, dir, -1.0f);
    d = _DistxzGV(pos, dst) * 0.5f;
    v = (d < 1.0f) ? 1.0f : ((d > 20.0f) ? 20.0f : d);
    StartCorrectPosition((void *)a0, dst, dir, v, 1);
    while (IsCorrectPosition((void *)a0)) {
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)a0, 0x50);
        }
        _ACTWait(1);
    }
}
typedef struct { int w[8]; } GirlPullBlk;
extern void afterGirlHand(unsigned int a0);
extern void afterGirlPulledGo(void *a0);
extern void ACTGame_ConnectHand(void);
extern void *memset(void *dst, int c, int n);
extern void RotQuaternionY(float *q, int a1);
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q,
                                          float x, float y, float z, float w);
extern int PAIR_IsStatus_BOY_PULL(void);
extern int D_0028F4C0[];

void actGirlPulledGo(volatile int a0)
{
    float q[4];
    char *s;
    int m;

    s = *(char **)((char *)a0 + 0x164);
    *(void **)(s + 0x14) = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    *(GirlPullBlk *)(*(char **)((char *)a0 + 0x15C) + 0x180) =
        *(GirlPullBlk *)(s + 0x620);
    *(int *)(*(char **)((char *)a0 + 0x15C) + 0x634) = 1;
    *(char **)(s + 0x18) = (char *)afterGirlPulledGo;
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    while (1) {
        if (!PAIR_IsStatus_BOY_PULL()) {
            ACTSendMailCorrect((void *)a0, 0x53);
            ACTSendMailCorrect((void *)a0, 0x54);
        } else {
            m = *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);
            if (m == 2 || m == 3) {
                ACTSendMailCorrect((void *)a0, 0x55);
                ACTSendMailCorrect((void *)a0, 0x56);
            }
            if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < *(int *)(s + 0x4C)) {
                ACTSendMailCorrect((void *)a0, 0x57);
            }
        }
        _ACTWait(1);
    }
}
extern void PAIR_GetPosition_BOY_DITCH(float *bpos, float *gpos);
extern void debug_NMarker(void *pos, int r, int g, int b, float size);
extern int PAIR_IsStatus_BOY_DITCH(void);

void actGirlDitch3mReady(volatile int a0)
{
    float gpos[4];
    float now[4];
    float bpos[4];

    GetRootPosition(now, (void *)a0);
    PAIR_GetPosition_BOY_DITCH(bpos, gpos);
    bpos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    StartCorrectPosition((void *)a0, bpos, gpos, 20.0f, 1);
    while (IsCorrectPosition((void *)a0)) {
        debug_NMarker(bpos, 0, 0, 0xFF, 100.0f);
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)a0, 0x18E);
        }
        _ACTWait(1);
    }
}
extern int D_0028F4C0[];
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);

void actGirlReadyMove(volatile int a0)
{
    float dst[4];
    float dir[4];
    char *p;
    int n;

    n = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 80.0f / 60.0f);
    dst[0] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x230);
    dst[1] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x234);
    dst[2] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x238);
    dir[0] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x240);
    dir[1] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x244);
    dir[2] = *(float *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x680) + 0x248);
    dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    StartCorrectPosition((void *)a0, dst, dir, (float)n, 1);
    while (IsCorrectPosition((void *)a0)) {
        debug_Arrow(100.0f, test_CURRENTROOT((void *)a0), dir, 0xFF, 0, 0xFF);
        ContinueCorrectPosition((void *)a0);
        _ACTWait(1);
    }
    while (1) {
        ACTSendMailCorrect((void *)a0, 0x10C);
        _ACTWait(1);
    }
}
extern char *D_0063A61C;
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void gflagOff(int a0);
extern void ACTGameCollisionOn(void *a0);
extern void ACTSetPositionWithFitting(void *a0, float *pos);
extern void SetMotionDirection(void *a0, float *dir);
extern int ACTGame_CheckHandMotion(void *a0, void *a1);
extern void ACTGame_DisconnectHand(void);
extern void GetSkeltonPosition(float *out, void *obj, int node);
extern float _DistSqGV(void *a, void *b);
extern void afterGirlHand(unsigned int a0);
extern void _OrientXZGV(void *out, void *a, void *b);
extern void sceVu0SubVector(void *out, void *a, void *b);

void actGirlRescueDst(volatile int a0)
{
    float dir[4];
    float q[4];
    float pos[4];
    float p1[4];
    float p2[4];
    float dst[4];
    char *s;
    char *w;
    int n;
    int done;

    s = *(char **)((char *)a0 + 0x164);
    memset(q, 0, 16);
    n = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 3;
    done = 0;
    *(void **)(s + 0x14) = (void *)afterGirlHand;
    ACTGame_ConnectHand();
    ACTGameCollisionOn((void *)a0);
    gflagOff(393);
    pos[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
    pos[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
    pos[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
    pos[1] = *(float *)(*(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) + 0x304);
    ACTSetPositionWithFitting((void *)a0, pos);
    w = *(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680);
    _OrientXZGV(q, w + 0x2F0, w + 0x300);
    sceVu0SubVector(dir,
                    *(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) + 0x300,
                    test_CURRENTROOT((void *)a0));
    sceVu0ScaleVector(dir, dir, 1.0f / (float)n);
    SetMotionDirection((void *)a0, q);
    while (1) {
        if (!ACTGame_CheckHandMotion(D_00639EA4, D_00639EA8)) {
            ACTGame_DisconnectHand();
            done = 1;
        }
        if (!done && ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2 < *(int *)(s + 0x4C)) {
            GetSkeltonPosition(p1, D_00639EA4, 6);
            GetSkeltonPosition(p2, D_00639EA8, 22);
            if (!(_DistSqGV(p1, p2) < 400.0f)) {
                iosOmSendMail(D_00639EA4, 248, D_0063A61C);
            }
            ACTSendMailCorrect((void *)a0, 198);
        }
        if (n > 0) {
            sceVu0AddVector(dst, test_CURRENTROOT((void *)a0), dir);
            dst[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            ACTSetPositionWithFitting((void *)a0, dst);
        }
        iosOmSendMail(D_00639EA4, 350, D_0063A61C);
        n--;
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}
extern void *memset(void *dst, int c, int n);
extern void RotQuaternionY(float *q, int a1);
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q,
                                          float x, float y, float z, float w);
extern void ACTGame_ConnectHand(void);
extern void _InterGV(float *dst, float *a, float *b, float t0, float t1);
extern void afterGirlSupportBGBegin(unsigned int a0);

void actGirlSupportBGBegin(volatile int a0)
{
    float v1[4];
    float v2[4];
    float dst[4];
    float q[4];
    char *s;
    int i;

    i = 0;
    s = *(char **)((char *)a0 + 0x164);
    v1[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
    v1[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
    v1[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
    v2[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
    v2[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
    v2[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    memset(q, 0, 0x10);
    q[3] = 1.0f;
    RotQuaternionY(q, 0);
    SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
    *(void **)(s + 0x14) = (void *)afterGirlSupportBGBegin;
    ACTGame_ConnectHand();
    while (1) {
        if (i++ < 6) {
            _InterGV(dst, v1, v2, (float)i, (float)(5 - i));
        }
        ACTSendMailCorrect((void *)a0, 0x184);
        _ACTWait(1);
    }
}
extern int girlcalled;
extern int GirlInfo;
extern int D_0063A954;
extern int D_0063B180;
extern char D_00554078[];
extern char D_002A84F8[];
extern void subGirlCollision(void);
extern void subCommonIdle(void);
extern void subGirlBrainMain(void);
extern void subGirlControl(void);
extern void actCreateSubThread(void *entry, int prio);
extern char *actInitialize(void *self);
extern void actInitialize_ext_charcter(void *self);
extern void actInitialize_only_charcter(void *self);
extern void actInitialize_geo(void *self);
extern float _ACTGame_GetParamF(int idx);
extern void ACTGame_LwsEffectInit(void *self);
extern void ACTLookTarget_Init(void *self);
extern void ACTParaStatus_Init(void *self);
extern void _ACTCharStatus_Init(void *self);
extern void ACTGameView_FirstSet(void *self);
extern void brainInitGirlSet(void *self, void *girl);
extern int D_0028F4C0[];
extern void debug_StdPrintfDummy();

void actGirlStart(void *self)
{
    char *p;

    girlcalled = 0;
    D_0063A954 = 0;
    GirlInfo = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 30;
    debug_StdPrintfDummy(D_00554078, self);
    p = actInitialize(self);
    actInitialize_ext_charcter(self);
    actInitialize_only_charcter(self);
    actInitialize_geo(self);
    *(int *)(*(char **)(*(char **)((char *)self + 0x164) + 0x680) + 0x254) =
        (int)(_ACTGame_GetParamF(0x22)
              * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f);
    ACTGame_LwsEffectInit(self);
    ACTLookTarget_Init(self);
    *(int *)(p + 0x180) = 0;
    *(int *)(p + 0x184) = 0;
    ACTParaStatus_Init(self);
    _ACTCharStatus_Init(self);
    _ACTWait(1);
    ACTGameView_FirstSet(self);
    brainInitGirlSet(self, D_00639EA4);
    if (D_0063B180 != 0) {
        actCreateSubThread(subGirlBrainMain, 0x14);
    }
    *(char **)(p + 0xD0) = D_002A84F8;
    actCreateSubThread(subGirlControl, 0x15);
    actCreateSubThread(subGirlCollision, 0x15);
    actCreateSubThread(subCommonIdle, 0x15);
    *(char **)(p + 0xD4) = D_002A84F8 + 0x78;
    *(int *)(p + 0x350) = 0;
    *(float *)(p + 0x1E0) = 100.0f;
    *(int *)(p + 0x48) = 1;
    ACTSendMailCorrect(self, 0xC7);
    _ACTWait(0);
}
extern void ACTSendMailCorrect(void *a0, int mail);
extern void *test_CURRENTORIENT(void *a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void sceVu0Normalize(void *out, void *in);

void GirlAct_BoyAndMeCollisionMail(void *a0)
{
    float vec[4];
    float boyPos[4];
    float myPos[4];
    float ang;

    ACTSendMailCorrect(a0, 0x10D);

    if (((int *)D_00639EA4[0x59])[0xD] == 1) {
        return;
    }
    GetRootPosition(boyPos, D_00639EA4);
    GetRootPosition(myPos, a0);

    sceVu0SubVector(vec, boyPos, myPos);
    sceVu0Normalize(vec, vec);

    ang = _RotyGV(vec, test_CURRENTORIENT(a0));

    if ((ang < 0.0f ? -ang : ang) < 45.0f) {
        ACTSendMailCorrect(a0, 0x10E);
        return;
    } else if ((ang < 0.0f ? -ang : ang) > 135.0f) {
        ACTSendMailCorrect(a0, 0x10F);
        return;
    } else if (ang > 45.0f) {
        ACTSendMailCorrect(a0, 0x110);
        return;
    } else {
        ACTSendMailCorrect(a0, 0x111);
    }
}
extern char D_005577D0[];

typedef struct {
    float x;    /* 0x00 */
    float y;    /* 0x04 */
    float z;    /* 0x08 */
    int f_0C;   /* 0x0C */
    int f_10;   /* 0x10 */
    float f_14; /* 0x14 */
    float f_18; /* 0x18 */
} EscortPoint;  /* 0x1C */

extern EscortPoint D_0055BA60[98];
extern void *test_CURRENTROOT(void *a0);
extern float _DistGV(void *a, void *b);
extern float _DistSqGV(void *a, void *b);
extern float _ACTGame_GetParamF(int idx);

static inline unsigned char isGirlEscortStatus(void)
{
    char *s = *(char **)((char *)D_00639EA8 + 0x164);
    int mode = *(int *)(s + 0x34);
    char *attr = D_005577D0 + mode * 0x50;
    if (((*(unsigned int *)(attr + 0x4C) >> 13) & 1) && mode != 0x6F
            && ((int)(*(unsigned long long *)(s + 0x20) >> 46) & 1)) {
        return 1;
    }
    return 0;
}

static inline EscortPoint *searchEscortPoint(int a0, int a1)
{
    EscortPoint *p;
    int i;
    for (i = 0; i < 98; i++) {
        p = &D_0055BA60[i];
        if (p->f_0C == a0 && p->f_10 == a1) {
            return p;
        }
    }
    return 0;
}

int IsGirlStatusEscortEnable(int a0, int a1)
{
    float v[4];
    EscortPoint *p;
    float d;

    if (D_00639EA4 != 0 && D_00639EA8 != 0
            && isGirlEscortStatus()) {
        p = searchEscortPoint(a0, a1);
        if (p != 0) {
            v[0] = -p->x;
            v[1] = -p->y;
            v[2] = -p->z;
            d = _DistGV(v, test_CURRENTROOT(D_00639EA8));
            if (d < p->f_14) {
                *(float *)(*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x688) + 0x330) = d * p->f_18;
                return 1;
            }
        } else {
            if (_DistSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8))
                    < _ACTGame_GetParamF(5) * _ACTGame_GetParamF(5)) {
                return 1;
            }
        }
    }
    return 0;
}
typedef union { float f[4]; long long ll[2]; } Vec4;
typedef union { int c[4]; long long ll[2]; } Col4;

extern Vec4 D_005540A0;   /* { FLT_MAX, 0, 0, 1 } : "no girl" position */
extern Col4 D_00554090;   /* { 0, 0x10, 0x20, 0x80 } : wire sphere colour */
extern int D_0063B228;    /* debug display switch */
extern int stage_no;

extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void sceVu0UnitMatrix(void *a0);
extern void gif_StartPacketPri(int a0);
extern void gif_SetZTest(int a0);
extern void gif_EndPacket(void);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);

static inline void dispEscortSphere(void *pos, float r, unsigned char in)
{
    Col4 col;

    if (D_0063B228) {
        MatrixDrive_PushMatrix();
        col = D_00554090;
        if (in) {
            col.c[0] = 0xFF;
        }
        gif_StartPacketPri(0xB);
        gif_SetZTest(1);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(pos);
        prim_DispWireSphere(&col, 0x10, 8, r);
        gif_EndPacket();
        MatrixDrive_PopMatrix();
    }
}

void DebugDispAutoEscort(void)
{
    Vec4 pos = D_005540A0;
    Vec4 v;
    EscortPoint *p;
    int i;
    int in;

    if (D_0063B228 == 0) {
        return;
    }
    if (D_00639EA8 != 0 && isGirlEscortStatus()) {
        pos.f[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
        pos.f[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
        pos.f[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
    }
    for (i = 1; i < 16; i++) {
        p = searchEscortPoint(stage_no, i);
        if (p != 0) {
            v.f[0] = -p->x;
            v.f[1] = -p->y;
            v.f[2] = -p->z;
            in = _DistSqGV(&v, &pos) < p->f_14 * p->f_14;
            dispEscortSphere(&v, p->f_14, in);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHintPoint);
extern int D_006C1E20[];
extern int ACTGame_FLAG_TETSUNAGI(void);
extern void GetSkeltonPosition(float *out, void *obj, int node);

void ACTGame_GirlBeforeFunc(void *self)
{
    float boyPos[4];
    float girlPos[4];
    char *s;

    s = (char *)*(int *)((char *)self + 0x164);
    D_006C1E20[0] = 0;
    D_006C1E20[1] = 0;
    if (*(int *)(s + 0x34) != 69) {
        *(unsigned long long *)(s + 0x20) &= ~0x100000ULL;
    }
    *(unsigned long long *)(s + 0x18) &= ~0x40000000000ULL;
    if (ACTGame_FLAG_TETSUNAGI()) {
        if (*(int *)(s + 0x34) == 5 || *(int *)(s + 0x34) == 69) {
            *(unsigned long long *)(s + 0x18) |= 0x40000000000ULL;
        } else {
            GetSkeltonPosition(boyPos, D_00639EA4, 6);
            GetSkeltonPosition(girlPos, D_00639EA8, 22);
            if (_DistSqGV(boyPos, girlPos) < 900.0f) {
                *(unsigned long long *)(s + 0x18) |= 0x40000000000ULL;
            }
        }
    }
}
extern int D_002A2E2C[];

void *FindGirlPullupFloorBoxGObj(void) {
    void *g = D_00639EA8;
    if (D_002A2E2C[0] == 7 &&
        *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x4E) {
        return *(void **)(*(char **)(*(char **)((char *)g + 0x164) + 0x688) + 0x374);
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBBegin);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBLoop);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlSupportGBEnd);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHangG3M);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlDitch3mExec);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlStand);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlWalk);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlRun);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHang);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBHang);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlAttack);
extern int D_0028F4C0[];
extern void _ACTLookTarget_Set(void *self, void *target, float *pos, int kind, int flag);

void actGirlBecall(volatile int a0)
{
    int i;

    for (i = 0; i < (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2; i++) {
        _ACTLookTarget_Set((void *)a0, D_00639EA4, 0, 5, 1);
        _ACTWait(1);
    }
    ACTSendMailCorrect((void *)a0, 252);
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlBehanged);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlAttractAction);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHintVoice);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlCannotReach);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand50);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlHand50);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand100);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlHand100);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", actGirlHand200);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", afterGirlHand200);
int NotNeedBackHand(void) {
    char *g = D_00639EA8;
    char *w = *(char **)(g + 0x164);

    if ((((int)(*(unsigned long long *)(w + 0x18) >> 40)) & 1) == 0) {
        return 1;
    }
    if (*(int *)(w + 0x34) == 0x45 && D_002A2F70.f_5D != 0 && D_002A2F70.f_58 == 0) {
        return 1;
    }
    return 0;
}
void SetGirlDangerGObj(int a0) {
    char *g = D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = a0;
    }
}
void ClearGirlDangerGObj(void) {
    char *g = (char *)D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = 0;
    }
}
void subGirlBrain_Idle(volatile int a0) {
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x164) + 0x34C) = 0;
    _ACTWait(0);
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Hesitate);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Becarry);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Busy);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_DangerEnv);
int enemy_list_compare(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}
typedef struct {
    float a[4];        /* 0x00 start point   */
    float b[4];        /* 0x10 end point     */
    float pos[4];      /* 0x20 clipped point */
    char  _30[0x40];
    float f_70;        /* 0x70 radius/height */
    char  _74[0x14];
    int   f_88;        /* 0x88 wall hit      */
    char  _8c[0x08];
    int   f_94;        /* 0x94 floor hit     */
    char  _98[0x28];
} ClipWork;
extern void ClipWall(void *);
extern void ClipWallField(void *);
extern void ClipFloor(void *);

int ACTCheckCollis_SAFE(float height, float *p0, float *p1, void *actor, float *posout, int radius)
{
    ClipWork work;
    float tmp[4];
    int flag;
    int rv;

    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;

    work.f_70 = (float)radius;
    work.a[0] = p0[0];
    work.a[1] = p0[1];
    work.a[2] = p0[2];
    work.b[0] = p1[0];
    work.b[2] = p1[2];
    work.b[1] = p0[1];

    tmp[0] = p1[0];
    tmp[1] = p0[1];
    tmp[2] = p1[2];

    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (work.f_88 == 0) {
        ClipWallField(&work);
        if (work.f_88 == 0) goto no_wall;
    }
    tmp[0] = work.pos[0];
    tmp[1] = work.pos[1];
    tmp[2] = work.pos[2];
no_wall:
    work.a[0] = tmp[0];
    work.a[1] = tmp[1];
    work.a[2] = tmp[2];
    work.b[0] = tmp[0];
    work.b[2] = tmp[2];
    work.b[1] = tmp[1] + height;
    ClipFloor(&work);
    if (work.f_94 == 0) {
        rv = 0;
    } else {
        work.pos[1] -= 10.0f;
    }
    if (posout != 0) {
        posout[0] = work.pos[0];
        posout[1] = work.pos[1];
        posout[2] = work.pos[2];
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv;
}
extern void ACTGame_DisconnectHand(void);
extern void ACTWay_SetBeginPositionIllegal(char *self);
extern char D_00553E50[];
extern void debug_StdPrintfDummy();
extern void iosPadActStop(int key);

void afterGirlHand(unsigned int a0)
{
  volatile unsigned int local = a0;
 do { ACTGame_DisconnectHand(); debug_StdPrintfDummy(D_00553E50); iosPadActStop(7); ACTWay_SetBeginPositionIllegal(local); } while (0);
}
void afterGirlPulledGo(void *a0) {
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x634) = 0;
}
extern char D_00554048[];
void actGirlJump(volatile int a0) {
    char *g = (char *)a0;
    char *s = *(char **)(g + 0x164);
    debug_StdPrintfDummy(D_00554048);
    *(int *)(s + 0x34) = 4;
    _ACTWait(0);
}
void afterGirlSupportBGBegin(unsigned int a0)
{
    volatile unsigned int local = a0;
    ACTGame_DisconnectHand();
}
int isMustCheckCylinder(void *a, void *b) {
    if ((a == (void *)D_00639EA4 && b == D_00639EA8) || (a == D_00639EA8 && b == (void *)D_00639EA4)) {
        if (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) == 0x51) {
            return 1;
        }
    }
    return 0;
}
extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, void *a6);
void afterGirlHintPoint(volatile int a0) {
    RequestChangeHandMode((void *)a0, 1, 4, 0, 0, 0, 0);
}
