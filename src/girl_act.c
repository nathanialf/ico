#include "common.h"

typedef struct {
    char _0[0x20];
    float f_20; /* 0x20 */
    char _24[0x0C];
    float sub30[4];     /* 0x30 */
    float sub40[4];     /* 0x40 */
    float f_50;         /* 0x50 */
    float f_54;         /* 0x54 */
    unsigned char f_58; /* 0x58 */
    unsigned char f_59;
    unsigned char f_5A;
    unsigned char f_5B;
    unsigned char f_5C;
    unsigned char f_5D;
    unsigned char f_5E;
} GirlStand;

union GAIF {
    int i;
    float f;
};

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

void funcGirlHandDisconnect(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy__pn(D_00553990);
}

extern void debug_StdPrintfDummy();
extern char D_005539E8[];
extern int *D_00639EA4;
extern char *D_0063A61C;
extern int iosOmSendMail(void *a0, int a1, void *a2);
extern void ACTSendMailCorrect(void *a0, int mail);
extern void _ACTWait(int n);
extern void *SetMotionRequest(void *self, int no, void *mot);

void motGirlHand50(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_005539E8);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x5C, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 1)
            break;
        _ACTWait(1);
    }
    while (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x214 ||
           !(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x21B)) {
        *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 1, sub + 0x620);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x5D, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 2)
            break;
        _ACTWait(1);
    }
    if ((((int)(*(unsigned long long *)(sub + 0x18) >> 44)) & 1) == 0) {
        iosOmSendMail(D_00639EA4, 0x10, D_0063A61C);
        ACTSendMailCorrect((void *)a0, 7);
    }
    iosOmSendMail(D_00639EA4, 0x5E, D_0063A61C);
    *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 0x5E, sub + 0x620);
    while ((*(int *)(*(char **)(sub + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    *(int *)(sub + 0x14) = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern char D_00553A18[];

void motGirlHand100(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00553A18);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x61, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 1)
            break;
        _ACTWait(1);
    }
    while (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x214 ||
           !(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x21B)) {
        *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 1, sub + 0x620);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x62, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(D_00639EA4, 0x63, D_0063A61C);
    *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 0x65, sub + 0x620);
    while (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x214 ||
           !(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x21B)) {
        *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 1, sub + 0x620);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x64, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 8)
            break;
        _ACTWait(1);
    }
    *(int *)(sub + 0x14) = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern char D_00553A48[];
extern char D_00553A60[];
extern char D_0063A880[];
extern char D_0063A888[];
extern int D_0028F4C0[];

void motGirlHand200(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);
    int n;

    debug_StdPrintfDummy(D_00553A48);
    n = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2;
    while (1) {
        if (n <= 0)
            goto expired;
        n--;
        iosOmSendMail(D_00639EA4, 0x66, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 1)
            break;
        _ACTWait(1);
    }
    goto held;
expired:
    ACTSendMailCorrect((void *)a0, 0x6A);
    debug_StdPrintfDummy(D_00553A60, (void *)a0 == (void *)D_00639EA4 ? D_0063A880 : D_0063A888);
held:
    while (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x214 ||
           !(*(int *)(*(char **)((char *)a0 + 0x15C) + 0x4A0) < 0x21B)) {
        *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 1, sub + 0x620);
        _ACTWait(1);
    }
    _ACTWait(1);
    while (1) {
        iosOmSendMail(D_00639EA4, 0x67, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 2)
            break;
        _ACTWait(1);
    }
    iosOmSendMail(D_00639EA4, 0x68, D_0063A61C);
    *(void **)(sub + 0x130) = SetMotionRequest((void *)a0, 0x66, sub + 0x620);
    while ((*(int *)(*(char **)(sub + 0x130) + 0x5C) & 1) == 0) {
        _ACTWait(1);
    }
    while (1) {
        iosOmSendMail(D_00639EA4, 0x69, D_0063A61C);
        if (*(int *)(sub + 0xE0) & 8)
            break;
        _ACTWait(1);
    }
    *(int *)(sub + 0x14) = 0;
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x47);
        _ACTWait(1);
    }
}

extern int D_002A5580[];
extern void brainClsTargetLevel();

void GirlBrainClearTarget(void)
{
    brainClsTargetLevel(D_002A5580);
}

extern void ACTGame_SetMotionPlaySpeedRatio_Reserve(void *a0, int a1, float f);

void SetTurnSpeedInEscape(char *a0)
{
    if (*(int *)(*(char **)(a0 + 0x164) + 0x34) == 10) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve(a0, 5, 1.5f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl_act", sort_list);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", girlBrainMain_MakeOthersList);

extern void GetMatrixDirectionToZ(void *m, void *dir);
extern float FSqrt(float x);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);

int girlBrainHideCheckIntercept(float *from, float *to, char *list, int n)
{
    float d[4];
    float m[16];
    float v[4];
    int i;
    float dist;
    float flag;
    float dy;

    sceVu0SubVector(d, from, to);
    d[1] = 0.0f;
    GetMatrixDirectionToZ(m, d);
    dist = FSqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    for (i = 0; i < n; i++) {
        flag = *(int *)(*(char **)(*(char **)(list + i * 0x30) + 0x164) + 0x34) == 6 ? 1.0f : 0.0f;
        dy = *(float *)(list + i * 0x30 + 0x14) - from[1] < 0.0f
                 ? -(*(float *)(list + i * 0x30 + 0x14) - from[1])
                 : *(float *)(list + i * 0x30 + 0x14) - from[1];

        if (flag != 0.0f) {
            if (80.0f < dy) {
                continue;
            }
        } else {
            if (200.0f < dy) {
                continue;
            }
        }
        sceVu0SubVector(v, list + i * 0x30 + 0x10, to);
        v[1] = 0.0f;
        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, m, v);

        if (0.0f < v[2]) {
            if (v[2] < dist) {
                if (v[0] * v[0] + v[1] * v[1] < 10000.0f) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

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

void girlBrainMain_PositionUpdate(void)
{
    GetRootPosition(D_002A2E70 + 0x00, D_00639EA8);
    GetRootPosition(D_002A2E70 + 0x20, D_00639EA4);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x10, D_00639EA8);
    GetRootProjectionPosOfGObj(D_002A2E70 + 0x30, D_00639EA4);
}

extern char D_0029D650[];
extern void *memset(void *dst, int c, int n);

void girlBrainMain_Init(void)
{
    memset(D_0029D650, 0, 0x5920);
}

typedef struct {
    char _0[0xC90];
    int f_C90; /* 0xC90 */
    char _C94[0x0C];
    int f_CA0; /* 0xCA0 */
    char _CA4[0x4C4C];
    unsigned char f_58F0; /* 0x58F0 */
    char _58F1[0x07];
    int runMode; /* 0x58F8 */
    int wait;
    int timer;
    int limit;
    char _5908[0x0C];
    int f_5914; /* 0x5914 */
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

extern void *test_CURRENTROOT(void *a0);

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
    GetRootProjectionPosOfGObj(pa, D_00639EA4);
    GetRootProjectionPosOfGObj(pb, D_00639EA8);
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
        if (*(void **)(*(char **)((char *)D_00639EA4 + 0x15C)) != 0 &&
            *(int *)((char *)*(void **)(*(char **)((char *)D_00639EA4 + 0x15C)) + 0xC) == 17) {
            t.f[0] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[0];
            t.f[1] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[1];
            t.f[2] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[2];
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

typedef struct {
    float a[4];   /* 0x00 start point   */
    float b[4];   /* 0x10 end point     */
    float pos[4]; /* 0x20 clipped point */
    char _30[0x40];
    float f_70; /* 0x70 radius/height */
    char _74[0x14];
    int f_88; /* 0x88 wall hit      */
    char _8c[0x08];
    int f_94; /* 0x94 floor hit     */
    char _98[0x28];
} ClipWork;

extern void ClipWall(void *);
extern void ClipWallField(void *);
extern void ClipFloor(void *);
extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0Normalize(void *dst, void *src);
extern void GetRootPosition(void *out, void *obj);
extern void GetRootProjectionPosOfGObj(void *out, void *obj);
extern int GetWay_next(void *way, float *cur);
extern void DeleteGuideWay(void *way);
extern float _DistSqGV(void *a, void *b);
extern char D_0029D650[];

/* girl_brain_main.c.inc:2276-2291 (rows outside every caller's span => static
   inline; the listing inlines it three times).  True when the straight segment
   from `from` to `to` clears both the wall and the wall-field collision. */
static inline int isNoWallBetween(float *from, float *to)
{
    ClipWork work;

    work.f_70 = 10.0f;
    sceVu0CopyVector(work.a, from);
    sceVu0CopyVector(work.b, to);
    ClipWall(&work);
    if (work.f_88 == 0) {
        ClipWallField(&work);
        if (work.f_88 == 0) {
            return 1;
        }
    }
    return 0;
}

/* girl_brain_main.c.inc:2221-2226 (rows outside its callers' span => static
   inline).  True when `b` is within 100 units vertically and 100 units in the
   plane of `a`. */
static inline unsigned char isNearPoint(float *a, float *b)
{
    if ((a[1] - b[1] < 0.0f ? -(a[1] - b[1]) : a[1] - b[1]) < 100.0f) {
        if (_DistSqGV(a, b) < 10000.0f) {
            return 1;
        }
    }
    return 0;
}

int girlBrainRunawayMoveByWay(char *self, float *out, float *tgt)
{
    float d[4];
    float pos[4];
    char *sub;
    int way;
    int done;

    sub = *(char **)(self + 0x164);
    d[0] = tgt[0];
    d[1] = tgt[1];
    d[2] = tgt[2];
    switch (*(int *)(sub + 0x3A4)) {
    case 0:
        done = 0;
        GetRootProjectionPosOfGObj(pos, self);
        pos[1] = pos[1] - 0.0f;
        way = GetWay_next(sub + 0x360, pos);
        if (way == 0) {
            sceVu0CopyVector(out, sub + 0x3B0);
        } else {
            char *w;

            sceVu0CopyVector(out, sub + 0x3B0);
            w = D_0029D650;
            if (*(int *)(w + 0x5860) != way) {
                if (*(int *)(w + 0x5860) != 0) {
                    done = *(int *)(sub + 0x3C4) < 1;
                }
                *(int *)(w + 0x5860) = way;
            }
        }
        if (*(int *)(sub + 0x388) == 0) {
            if (isNoWallBetween(pos, d)) {
                *(int *)(sub + 0x3A4) = 1;
                DeleteGuideWay(sub + 0x360);
            }
        }
        if (done) {
            return 2;
        }
        break;
    case 1: {
        float cur[4];
        float dir[4];

        GetRootPosition(cur, self);
        if (isNoWallBetween(cur, d)) {
            float dx = d[0];
            float dz = d[2];

            dir[0] = dx - cur[0];
            dir[1] = 0.0f;
            dir[2] = dz - cur[2];
            sceVu0Normalize(out, dir);
            if (isNearPoint(d, cur)) {
                return 1;
            }
        }
    } break;
    }
    return 0;
}

ASM_LIT4_SLOT(D_00638FCC, 90000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", subGirlBrain_Escape);

extern float _DistGV(void *a, void *b);
extern void _InterGV(float *dst, float *a, float *b, float t0, float t1);

void ClipTwinVector(float *out, float *from, float *to, float max)
{
    float d;
    float t;

    d = _DistGV(from, to);
    if (max < d) {
        t = (d - max) / d;
        _InterGV(out, from, to, t, 1.0f - t);
    } else {
        out[0] = to[0];
        out[1] = to[1];
        out[2] = to[2];
    }
}

extern int ACTWayMove_BeginDetail(void *obj, float *b, float *a, void *tgt, int e, int f);
extern int ACTWayMove_NextDetail(void *obj, char *w, float *a, int d, int e);

/* INTERIM: ACTCheckCollis_SAFE is `inline` in the 2001 source -- the PAL
 * listing attributes girl_brain_main.c.inc:2868-2909 both to its out-of-line
 * copy (this TU's deferred-inline tail, ROM 0x0017C6D0, still spelled as a
 * plain definition further down) and to the four Danger_* GetSafePosition
 * bodies that inline it.  Marking the real definition `inline` would move its
 * out-of-line copy past the tail members that are still INCLUDE_ASM, so the
 * callers above it use this identical static-inline stand-in.  Delete it and
 * mark the real definition `inline` once the tail is complete. */
static inline int ACTCheckCollis_SAFE_inl(float height, float *p0, float *p1, void *actor,
                                          float *posout, int radius)
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
        if (work.f_88 == 0)
            goto no_wall;
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

extern void _ApplyRyGV(float *v, float ang);
extern void sceVu0AddVector(float *dst, float *a, float *b);
extern float _DistSqGV(void *a, void *b);
extern float _DistxzSqGV(void *a, void *b);
extern void _OrientXZGV(void *out, void *a, void *b);
extern void _ACTCharStatus_Set(void *obj, int id, float v, int flag);
extern void *D_006C1E44[];

static void Danger_Bomb(void *self)
{
    /* girl_brain_main.c.inc:2942 -- a GNU nested function: ROM sets the static
     * chain with `daddu $2,$29,$0` at the call and the callee homes it with
     * `sw $2,0($sp)`.  Each Danger_* parent carries its own copy (the listing
     * names them GetSafePosition.357/.364/.371/.379).  The float radius is the
     * FIRST parameter (ee-gcc still passes it in $f12 with the four pointers in
     * $a0-$a3), and the last parameter -- the boy position the callers hand in
     * and this copy never reads -- is reused as the collision flag. */
    int GetSafePosition(float rad, float *dst, float *center, float *cur, int ok)
    {
        float dir[4];
        float pos[4];
        float best;
        float d;
        int found;
        int i;

        best = 0.0f;
        found = 0;
        for (i = 0; i < 8; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            _ApplyRyGV(dir, (float)(i * 45 - 180) * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            ok = ACTCheckCollis_SAFE_inl(200.0f, center, pos, 0, pos, 40);
            if (ok) {
                d = _DistGV(center, pos);
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        if (found && _DistSqGV(dst, center) < _DistSqGV(cur, center)) {
            dst[0] = cur[0];
            dst[1] = cur[1];
            dst[2] = cur[2];
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float obj[4];
    float base[4];
    float tmp[4];
    float now[4];
    float dir[4];
    char *sub;
    void *bomb;
    long long f;
    unsigned char r;
    unsigned char r2;
    long long p;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    bomb = D_006C1E44[0];
retry:
    {
        GetRootProjectionPosOfGObj(goal, bomb);
        GetRootProjectionPosOfGObj(girl, self);
        obj[0] = ((float *)test_CURRENTROOT(bomb))[0];
        obj[1] = ((float *)test_CURRENTROOT(bomb))[1];
        obj[2] = ((float *)test_CURRENTROOT(bomb))[2];
        GetRootProjectionPosOfGObj(base, bomb);
        _ACTWait(1);
        GetSafePosition(500.0f, goal, (float *)test_CURRENTROOT(bomb), girl,
                        (int)test_CURRENTROOT(D_00639EA4));
        _ACTWait(1);
        p = ACTWayMove_BeginDetail(self, girl, goal, 0, 0, 0);
        r = p;
        if (!r) {
            _ACTWait(0);
        }
        _ACTWait(1);
        turn = 0;
        while (1) {
            _ACTCharStatus_Set(self, 11, -1.0f, (int)bomb);
            GetRootProjectionPosOfGObj(tmp, bomb);
            GetRootProjectionPosOfGObj(girl, self);
            GetRootProjectionPosOfGObj(now, bomb);
            if (!(_DistxzSqGV(now, base) < 10000.0f)) {
                goto retry;
            }
            p = ACTWayMove_NextDetail(self, sub + 0x120, goal, 0, 0);
            r2 = p;
            f = *(long long *)(sub + 0x3F0);
            if (((int)(f >> 16) & 1)) {
                turn = 0;
            }
            if (!r2) {
                turn = 1;
            } else if (((int)(f >> 17) & 1)) {
                turn = 1;
            } else if (*(float *)(sub + 0x3F8) < 50.0f) {
                turn = 1;
            } else if (turn == 0) {
                *(float *)(sub + 0x120) = *(float *)(sub + 0x3E0);
                *(float *)(sub + 0x124) = *(float *)(sub + 0x3E4);
                *(float *)(sub + 0x128) = *(float *)(sub + 0x3E8);
                *(float *)(sub + 0x34C) = 1.0f;
            }
            if (turn) {
                *(float *)(sub + 0x34C) = 0.0f;
                _OrientXZGV(dir, obj, test_CURRENTROOT(self));
                girlBrainHide_GoalTurn(dir, 1);
            }
            _ACTWait(1);
        }
    }
}

ASM_LIT4_SLOT(D_00638FD8, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001762A0);
ASM_LIT4_SLOT(D_00638FDC, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", Danger_Gondola);

extern int IsThisBoxTruck(void *a0);

/* girl_brain_main.c.inc:44-53 -- a file-scope static helper with no MAIN.MAP
 * symbol of its own; the listing attributes lines 45/50/52 to Danger_Box, to
 * its nested GetSafePosition and to subGirlBrainMain, i.e. it is inlined at
 * every site.  Name chosen here: it asks whether the boy is currently pushing
 * a truck-type box (his sub-object's status 0x34 == 0x31 and the object he
 * holds at 0x158 is box kind 7). */
static inline unsigned char isBoyPushBoxTruck(void)
{
    char *sub;
    char *box;

    if (D_00639EA4 != 0 &&
        *(int *)((sub = *(char **)((char *)D_00639EA4 + 0x164)) + 0x34) == 0x31 &&
        (box = *(char **)(sub + 0x158)) != 0 && IsThisBoxTruck(box) == 7) {
        return 1;
    }
    return 0;
}

extern void *test_CURRENTORIENT(void *a0);
extern float _GetDirection(void *orient);
extern void sceVu0ScaleVector(float *dst, float *src, float scale);
extern char D_00553C58[];
extern int D_0029D618[];

static void Danger_Box(void *self)
{
    /* girl_brain_main.c.inc:3438 -- a GNU nested function (the listing's
     * GetSafePosition.371); see Danger_Bomb for the parameter-order note.
     * This copy takes six integer parameters; the fifth (the boy root the
     * callers hand in) is never read and is reused as the collision flag. */
    int GetSafePosition(float *dst, float *way, float *center, float rad, int ok, int mode,
                        float *girl)
    {
        float dir[4];
        float pos[4];
        float from[4];
        float best;
        float d;
        int found;
        int i;
        int ang;

        best = 0.0f;
        found = 0;
        for (i = 0; i < 3; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            if (i == 0 && !isBoyPushBoxTruck()) {
                continue;
            }
            ang = (int)(_GetDirection(test_CURRENTORIENT(D_00639EA4)) / 3.1415927f * 180.0f) +
                  D_0029D618[i];
            if (ang >= 181) {
                ang -= 360;
            }
            if (ang <= -181) {
                ang += 360;
            }
            _ApplyRyGV(dir, (float)ang * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            pos[1] = center[1];
            from[0] = center[0];
            from[2] = center[2];
            from[1] = center[1] - 70.0f;
            ok = ACTCheckCollis_SAFE_inl(200.0f, from, pos, 0, pos, 40);
            if (ok) {
                d = _DistxzSqGV(way, pos);
                if (mode != 1) {
                    if (_DistxzSqGV(pos, way) < _DistxzSqGV(way, center)) {
                        continue;
                    }
                }
                if (_DistxzSqGV(pos, girl) < 3600.0f) {
                    continue;
                }
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        if (found) {
            /* ROM evaluates both calls and drops the comparison: the body of
             * this test is empty in the shipped build. */
            if (_DistSqGV(dst, way) < _DistSqGV(center, way)) {}
        } else {
            dst[0] = center[0];
            dst[1] = center[1];
            dst[2] = center[2];
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float objp[4];
    float way[4];
    float cur[4];
    float boxp[4];
    float sideA[4];
    float sideB[4];
    float ofs[4];
    float orient[4];
    float tmp[4];
    float dir[4];
    char *sub;
    void *box;
    float rad;
    long long f;
    unsigned char r;
    unsigned char r2;
    long long p;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    rad = isBoyPushBoxTruck() ? 400.0f : 200.0f;
    box = D_006C1E44[0];
    GetRootProjectionPosOfGObj(goal, box);
    GetRootProjectionPosOfGObj(girl, self);
    objp[0] = ((float *)test_CURRENTROOT(box))[0];
    objp[1] = ((float *)test_CURRENTROOT(box))[1];
    objp[2] = ((float *)test_CURRENTROOT(box))[2];
    GetRootProjectionPosOfGObj(way, box);
    orient[0] = ((float *)test_CURRENTORIENT(D_00639EA4))[0];
    orient[1] = ((float *)test_CURRENTORIENT(D_00639EA4))[1];
    orient[2] = ((float *)test_CURRENTORIENT(D_00639EA4))[2];
    boxp[0] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[0];
    boxp[1] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[1];
    boxp[2] =
        ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x158)))[2];
    cur[0] = ((float *)test_CURRENTROOT(self))[0];
    cur[1] = ((float *)test_CURRENTROOT(self))[1];
    cur[2] = ((float *)test_CURRENTROOT(self))[2];
    sceVu0ScaleVector(ofs, orient, 100.0f);
    sceVu0AddVector(sideA, boxp, ofs);
    sceVu0ScaleVector(ofs, orient, -100.0f);
    sceVu0AddVector(sideB, boxp, ofs);
    if (_DistSqGV(sideA, cur) < _DistSqGV(sideB, cur)) {
        way[0] = sideA[0];
        way[1] = sideA[1];
        way[2] = sideA[2];
    } else {
        way[0] = sideB[0];
        way[1] = sideB[1];
        way[2] = sideB[2];
    }
    _ACTWait(1);
    if (!GetSafePosition(goal, way, girl, rad, (int)test_CURRENTROOT(D_00639EA4), 0, girl)) {
        GetRootProjectionPosOfGObj(cur, box);
        if (!GetSafePosition(goal, way, cur, rad, (int)test_CURRENTROOT(D_00639EA4), 1, girl)) {
            debug_StdPrintfDummy(D_00553C58);
            goal[0] = girl[0];
            goal[1] = girl[1];
            goal[2] = girl[2];
        }
    }
    _ACTWait(1);
    p = ACTWayMove_BeginDetail(self, girl, goal, 0, 0, 0);
    r = p;
    if (!r) {
        _ACTWait(0);
    }
    *(long long *)(sub + 0x438) |= 0x10000;
    _ACTWait(1);
    turn = 0;
    while (1) {
        _ACTCharStatus_Set(self, 11, -1.0f, (int)box);
        GetRootProjectionPosOfGObj(cur, box);
        GetRootProjectionPosOfGObj(girl, self);
        GetRootProjectionPosOfGObj(tmp, box);
        p = ACTWayMove_NextDetail(self, sub + 0x120, goal, 0, 0);
        r2 = p;
        f = *(long long *)(sub + 0x3F0);
        if (((int)(f >> 16) & 1)) {
            turn = 0;
        }
        if (!r2) {
            turn = 1;
        } else if (((int)(f >> 17) & 1)) {
            turn = 1;
        } else if (*(float *)(sub + 0x3F8) < 50.0f) {
            turn = 1;
        } else if (turn == 0) {
            *(float *)(sub + 0x120) = *(float *)(sub + 0x3E0);
            *(float *)(sub + 0x124) = *(float *)(sub + 0x3E4);
            *(float *)(sub + 0x128) = *(float *)(sub + 0x3E8);
            *(float *)(sub + 0x34C) = 1.0f;
        }
        if (turn) {
            *(float *)(sub + 0x34C) = 0.0f;
            _OrientXZGV(dir, objp, test_CURRENTROOT(self));
            girlBrainHide_GoalTurn(dir, 0);
        }
        _ACTWait(1);
    }
}

static void Danger_Rotobject(void *self)
{
    /* girl_brain_main.c.inc -- a GNU nested function (the listing's
     * GetSafePosition.379); see Danger_Bomb for the parameter-order note. */
    int GetSafePosition(float rad, float *dst, float *center, float *girl, int ok)
    {
        float boy[4];
        float dir[4];
        float pos[4];
        float from[4];
        float best;
        float d;
        int found;
        int i;

        boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
        boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
        boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
        best = 0.0f;
        found = 0;
        for (i = 0; i < 4; i++) {
            memset(dir, 0, 0x10);
            dir[2] = rad;
            _ApplyRyGV(dir, (float)(i * 90 - 135) * 3.1415927f / 180.0f);
            sceVu0AddVector(pos, center, dir);
            pos[1] = girl[1];
            from[0] = girl[0];
            from[1] = girl[1] - 70.0f;
            from[2] = girl[2];
            ok = ACTCheckCollis_SAFE_inl(200.0f, from, pos, 0, pos, 30);
            if (ok) {
                d = _DistxzSqGV(boy, pos);
                if (best < d) {
                    best = d;
                    dst[0] = pos[0];
                    dst[1] = pos[1];
                    dst[2] = pos[2];
                    found = 1;
                }
            }
        }
        return found;
    }
    float goal[4];
    float girl[4];
    float objp[4];
    float base[4];
    float tmp1[4];
    float tmp2[4];
    float dir[4];
    char *sub;
    void *obj;
    int turn;

    sub = *(char **)((char *)self + 0x164);
    obj = D_006C1E44[0];
    GetRootProjectionPosOfGObj(goal, obj);
    GetRootProjectionPosOfGObj(girl, self);
    objp[0] = ((float *)test_CURRENTROOT(obj))[0];
    objp[1] = ((float *)test_CURRENTROOT(obj))[1];
    objp[2] = ((float *)test_CURRENTROOT(obj))[2];
    GetRootProjectionPosOfGObj(base, obj);
    _ACTWait(1);
    if (!GetSafePosition(300.0f, goal, (float *)test_CURRENTROOT(obj), girl,
                         (int)test_CURRENTROOT(D_00639EA4))) {
        while (1) {
            *(float *)(sub + 0x34C) = 0.0f;
            _ACTWait(1);
        }
    }
    turn = 0;
    _ACTWait(1);
    while (1) {
        _ACTCharStatus_Set(self, 11, -1.0f, (int)obj);
        GetRootProjectionPosOfGObj(tmp1, obj);
        GetRootProjectionPosOfGObj(girl, self);
        GetRootProjectionPosOfGObj(tmp2, obj);
        if (_DistxzSqGV(girl, goal) < 3600.0f) {
            turn = 1;
        } else {
            _OrientXZGV(sub + 0x120, goal, girl);
            *(float *)(sub + 0x34C) = 1.0f;
        }
        if (turn) {
            *(float *)(sub + 0x34C) = 0.0f;
            _OrientXZGV(dir, objp, test_CURRENTROOT(self));
            girlBrainHide_GoalTurn(dir, 0);
        }
        _ACTWait(1);
    }
}

extern void debug_NMarker(void *pos, int r, int g, int b, float size);
extern int ACTWay_IsMustWalkFromWay(void *obj);

/* girl_brain_main.c.inc:2-8 -- a file-scope static helper with no out-of-line
 * ROM copy (no MAIN.MAP symbol); the listing attributes lines 3/4/5/7 of the
 * .inc inside subGirlBrain_HideAdvance's move arm. */
static inline void girlBrainSetWalkRatio(void *g)
{
    float run = 1.0f;
    char *s = *(char **)((char *)g + 0x164);
    float walk = 0.5f;

    if (ACTWay_IsMustWalkFromWay(g)) {
        *(float *)(s + 0x34C) = walk;
    } else {
        *(float *)(s + 0x34C) = run;
    }
}

void subGirlBrain_HideAdvance(volatile int a0)
{
    float self_pos[4];
    float boy_pos[4];
    char *sub = *(char **)((char *)a0 + 0x164);
    long long p;
    unsigned char hit;

    GetRootProjectionPosOfGObj(self_pos, (void *)a0);
    GetRootProjectionPosOfGObj(boy_pos, D_00639EA4);
    ACTWayMove_BeginDetail((void *)a0, self_pos, boy_pos, 0, 0, 0);
    for (;;) {
        ((GirlBrainWork *)D_0029D650)->f_5914 = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
        GetRootProjectionPosOfGObj(boy_pos, D_00639EA4);
        p = ACTWayMove_NextDetail((void *)a0, sub + 0x120, boy_pos, 0, 0);
        hit = p;
        debug_NMarker(boy_pos, 0xFF, 0, 0, 100.0f);
        if (!hit || (*(float *)(sub + 0x3F8) < 100.0f &&
                     (*(float *)(sub + 0x3FC) < 0.0f ? -*(float *)(sub + 0x3FC)
                                                     : *(float *)(sub + 0x3FC)) < 100.0f)) {
            *(int *)(sub + 0x34C) = 0;
            _ACTWait(1);
            continue;
        }
        {
            /* the actor-entry home is `volatile` (the scheduler rewrites the
             * GObj slot between waits), so the arm reads it once at its top
             * and works from the captured pointer -- ROM's `lw $v0,0($sp)`
             * followed by `move $a0,$v0`. */
            void *g = (void *)a0;

            *(float *)(sub + 0x120) = *(float *)(sub + 0x3E0);
            *(float *)(sub + 0x124) = *(float *)(sub + 0x3E4);
            *(float *)(sub + 0x128) = *(float *)(sub + 0x3E8);
            girlBrainSetWalkRatio(g);
        }
        _ACTWait(1);
    }
}

ASM_LIT4_SLOT(D_00638FE8, 1500.0f);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", isEnterHideadv_EnemyLocation);

extern int D_00639EA4__pn __asm__("D_00639EA4");
extern void *D_00629DE4, *D_00639EA8__pn __asm__("D_00639EA8");
extern float _DistxzSqGV(void *, void *);
extern int isEnterHideadv_EnemyLocation(void *, void *);

int isEnterHideadv(void)
{
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

void HandMgr_Judge(void)
{
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
            unsigned long long f =
                *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
            if ((int)(f >> 33) & 1) {
                *mode = 1;
            } else if ((int)(f >> 32) & 1) {
                *mode = 2;
            }
        }
        if (*mode == 2) {
            unsigned long long f =
                *(unsigned long long *)((char *)((int *)D_00639EA4[0x59])[0x1A2] + 0x448);
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

typedef struct {
    int w[8];
} GirlPullBlk;

extern void afterGirlHand(unsigned int a0);
extern void afterGirlPulledGo(void *a0);
extern void ACTGame_ConnectHand(void);
extern void *memset(void *dst, int c, int n);
extern void RotQuaternionY(float *q, int a1);
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);
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
    *(GirlPullBlk *)(*(char **)((char *)a0 + 0x15C) + 0x180) = *(GirlPullBlk *)(s + 0x620);
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
extern int iosOmSendMail(void *a0, int a1, void *a2);
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
    sceVu0SubVector(dir, *(char **)(*(char **)((char *)D_00639EA4 + 0x164) + 0x680) + 0x300,
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
extern void SetMotionNodeFixModeParameter(void *a, void *b, int c, int d, float *q, float x,
                                          float y, float z, float w);
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
        (int)(_ACTGame_GetParamF(0x22) * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) /
              60.0f);
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
    if (((*(unsigned int *)(attr + 0x4C) >> 13) & 1) && mode != 0x6F &&
        ((int)(*(unsigned long long *)(s + 0x20) >> 46) & 1)) {
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

    if (D_00639EA4 != 0 && D_00639EA8 != 0 && isGirlEscortStatus()) {
        p = searchEscortPoint(a0, a1);
        if (p != 0) {
            v[0] = -p->x;
            v[1] = -p->y;
            v[2] = -p->z;
            d = _DistGV(v, test_CURRENTROOT(D_00639EA8));
            if (d < p->f_14) {
                *(float *)(*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x688) + 0x330) =
                    d * p->f_18;
                return 1;
            }
        } else {
            if (_DistSqGV(test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8)) <
                _ACTGame_GetParamF(5) * _ACTGame_GetParamF(5)) {
                return 1;
            }
        }
    }
    return 0;
}

typedef union {
    float f[4];
    long long ll[2];
} Vec4;

typedef union {
    int c[4];
    long long ll[2];
} Col4;

extern Vec4 D_005540A0; /* { FLT_MAX, 0, 0, 1 } : "no girl" position */
extern Col4 D_00554090; /* { 0, 0x10, 0x20, 0x80 } : wire sphere colour */
extern int D_0063B228;  /* debug display switch */
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

/* the *(sub+0x688) ACT parameter block, viewed as a struct.  Stores through it
   must be COMPONENT_REFs (MEM_IN_STRUCT_P) and not plain scalar indirections:
   alias.c can then tell them apart from the fixed-address parameter home, which
   is what lets ROM's reloads of `a0` move ahead of them. */
typedef struct {
    char _0[0x3B0];
    int f_3B0; /* 0x3B0 : frames left before the "cannot reach" retry */
    char _3B4[0x16C];
    float f_520; /* 0x520 : hint-point target position */
    float f_524;
    float f_528;
} ActPara;

extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, void *a6);
extern void _OrientXZGV(void *out, void *a, void *b);
extern int _AbsRotyGV(void *a, void *b);
extern void _ACTCharStatus_Set(void *obj, int id, float v, int flag);
extern void afterGirlHintPoint(volatile int a0);

void actGirlHintPoint(volatile int a0)
{
    float d[4];
    float p[4];
    float q[4];
    float r[4];
    float u[4];
    float o1[4];
    float o2[4];
    void *tgt;
    char *s;

    tgt = (void *)*(int *)(*(int *)(*(char **)((char *)a0 + 0x164) + 0x30));
    s = *(char **)((char *)a0 + 0x164);
    *(void **)(s + 0x18) = (void *)afterGirlHintPoint;
    sceVu0SubVector(d, test_CURRENTROOT(tgt), test_CURRENTROOT((void *)a0));
    while (1) {
        sceVu0AddVector(p, test_CURRENTROOT((void *)a0), d);
        sceVu0SubVector(p, p, test_CURRENTROOT(tgt));
        RequestChangeHandMode((void *)a0, 1, 4, 3, tgt, 0, p);
        if (D_00639EA4) {
            q[0] = ((float *)test_CURRENTROOT((void *)a0))[0];
            q[1] = ((float *)test_CURRENTROOT((void *)a0))[1];
            q[2] = ((float *)test_CURRENTROOT((void *)a0))[2];
            r[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
            r[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
            r[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            sceVu0AddVector(u, q, d);
            _OrientXZGV(o1, r, q);
            _OrientXZGV(o2, u, q);
            if (_AbsRotyGV(o1, o2) >= 121) {
                _ACTCharStatus_Set((void *)a0, 13, -1.0f, 0);
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_520 = u[0];
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_524 = u[1];
                ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_528 = u[2];
            }
        }
        _ACTCharStatus_Set((void *)a0, 14, -1.0f, 0);
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

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

void *FindGirlPullupFloorBoxGObj(void)
{
    void *g = D_00639EA8;
    if (D_002A2E2C[0] == 7 && *(int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34) == 0x4E) {
        return *(void **)(*(char **)(*(char **)((char *)g + 0x164) + 0x688) + 0x374);
    }
    return 0;
}

extern float _MoveGV(float *dst, float *from, float *to, float t);
extern void SetDirectRootPositionNoFitting(void *self, float *pos);

void actGirlSupportGBBegin(volatile int a0)
{
    float girl[4];
    float boy[4];
    float dst[4];

    for (;;) {
        girl[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
        girl[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
        girl[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
        boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
        boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
        boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
        boy[1] = girl[1];
        _MoveGV(dst, girl, boy, 20.0f);
        SetDirectRootPositionNoFitting((void *)a0, dst);
        ACTSendMailCorrect((void *)a0, 0x17E);
        _ACTWait(1);
    }
}

/* girl_act.c:3933 — the status-range test the listing attributes to its own
   line inside actGirlSupportGBLoop's loop. */
static inline unsigned char isGirlSupportGBStatus(void)
{
    unsigned int st = *(unsigned int *)(*(char **)((char *)D_00639EA4 + 0x164) + 0x34);

    if (st < 0x6B) {
        if (0x68 <= st) {
            return 1;
        }
    }
    return 0;
}

void actGirlSupportGBLoop(volatile int a0)
{
    for (;;) {
        if (!isGirlSupportGBStatus()) {
            ACTSendMailCorrect((void *)a0, 0x180);
        }
        _ACTWait(1);
    }
}

void actGirlSupportGBEnd(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

extern void ACTWay_SetBeginPositionIllegal(char *self);

void actGirlHangG3M(volatile int a0)
{
    ACTWay_SetBeginPositionIllegal((char *)a0);
    for (;;) {
        if (!PAIR_IsStatus_BOY_DITCH()) {
            ACTSendMailCorrect((void *)a0, 0x194);
        }
        _ACTWait(1);
    }
}

extern void ACTGame_ConnectHand(void);
extern void SetRootPosition(void *self, float *pos);
extern void _InterGV(float *dst, float *a, float *b, float t0, float t1);
extern char D_00553FD0[];

void actGirlDitch3mExec(volatile int a0)
{
    float boy[4];
    float girl[4];
    float dst[4];
    int i = 0;
    int go = 1;

    ACTGame_ConnectHand();
    debug_StdPrintfDummy(D_00553FD0);
    for (;;) {
        if (go) {
            boy[0] = ((float *)test_CURRENTROOT(D_00639EA4))[0];
            boy[1] = ((float *)test_CURRENTROOT(D_00639EA4))[1];
            boy[2] = ((float *)test_CURRENTROOT(D_00639EA4))[2];
            girl[0] = ((float *)test_CURRENTROOT(D_00639EA8))[0];
            girl[1] = ((float *)test_CURRENTROOT(D_00639EA8))[1];
            girl[2] = ((float *)test_CURRENTROOT(D_00639EA8))[2];
            _InterGV(dst, boy, girl, 1.0f, 1.0f);
            SetRootPosition((void *)a0, dst);
            i++;
            go = i < 3;
        }
        ACTSendMailCorrect((void *)a0, 0x193);
        _ACTWait(1);
    }
}

extern char D_00554000[];

void actGirlStand(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00554000);
    *(int *)(sub + 0x34) = 1;
    _ACTWait(0);
}

extern char D_00554018[];

void actGirlWalk(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00554018);
    *(int *)(sub + 0x34) = 2;
    _ACTWait(0);
}

extern char D_00554030[];

void actGirlRun(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00554030);
    *(int *)(sub + 0x34) = 3;
    _ACTWait(0);
}

extern void *D_00639EA0;
extern void ACTAdjustPlane(void *self, void *plane);

void actGirlHang(volatile int a0)
{
    char *s = *(char **)((char *)a0 + 0x164);
    int rope;
    /* rope-hang detected from the ACT parameter block */
    int hang = 0;

    if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x904) == 0x5A) {
        hang = *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4;
    }
    /* the debug/free camera forces the pull mail on regardless */
    rope = hang;
    if (D_00639EA0 != 0) {
        if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4) {
            rope = 1;
            ACTAdjustPlane((void *)a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
        }
    }
    for (;;) {
        if (rope && (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < *(int *)(s + 0x4C)) {
            ACTSendMailCorrect((void *)a0, 0xC7);
        }
        _ACTWait(1);
    }
}

void actGirlBHang(volatile int a0)
{
    char *s = *(char **)((char *)a0 + 0x164);
    int rope = 0;

    if (*(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x904) == 0x5A) {
        rope = *(int *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x900) == 4;
    }
    ACTAdjustPlane((void *)a0, *(char **)(*(char **)((char *)a0 + 0x164) + 0x688) + 0x8B0);
    for (;;) {
        if (rope && (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5 < *(int *)(s + 0x4C)) {
            ACTSendMailCorrect((void *)a0, 0xC7);
        }
        ACTSendMailCorrect((void *)a0, 0x150);
        _ACTWait(1);
    }
}

extern char D_00554060[];

void actGirlAttack(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00554060);
    *(int *)(sub + 0x34) = 15;
    _ACTWait(0);
}

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

void actGirlBehanged(volatile int a0)
{
    float q[4];

    for (;;) {
        memset(q, 0, 0x10);
        q[3] = 1.0f;
        RotQuaternionY(q, 0);
        SetMotionNodeFixModeParameter(D_00639EA8, D_00639EA4, 2, 6, q, 0.0f, 0.0f, 0.0f, 1.0f);
        _ACTWait(1);
    }
}

void actGirlAttractAction(volatile int a0)
{
    for (;;) {
        ACTSendMailCorrect((void *)a0, 340);
        _ACTWait(1);
    }
}

extern void _ACTCharStatus_Set(void *self, int status, float time, int flag);

void actGirlHintVoice(volatile int a0)
{
    for (;;) {
        _ACTCharStatus_Set((void *)a0, 14, -1.0f, 0);
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

void actGirlCannotReach(volatile int a0)
{
    for (;;) {
        ((ActPara *)(*(char **)(*(char **)((char *)a0 + 0x164) + 0x688)))->f_3B0 =
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10;
        ACTSendMailCorrect((void *)a0, 199);
        _ACTWait(1);
    }
}

extern char D_005539D0[];
extern char D_005539B8[];
extern void afterGirlHand50(volatile int a0);

void actGirlHand50(volatile int a0)
{
    float dir[4];
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_005539B8);
    sceVu0ScaleVector(dir, (float *)(sub + 0x4B0), -1.0f);
    SetMotionDirection((void *)a0, dir);
    SetDirectRootPositionNoFitting((void *)a0, (float *)(sub + 0x590));
    *(int *)(sub + 0xE0) = 0;
    *(void **)(sub + 0x14) = (void *)afterGirlHand50;
    do {
        _ACTWait(1);
    } while ((*(int *)(sub + 0xE0) & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x60);
        _ACTWait(1);
    }
}

extern char D_005539A0[];

void afterGirlHand50(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x60, D_0063A61C);
    ACTGame_DisconnectHand();
}

extern char D_00553A00[];
extern char D_005539D0[];
extern void afterGirlHand100(volatile int a0);

void actGirlHand100(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00553A00);
    *(int *)(sub + 0x34) = 0x53;
    *(void **)(sub + 0x14) = (void *)afterGirlHand100;
    *(int *)(sub + 0xE0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)(sub + 0xE0) & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x65);
        _ACTWait(1);
    }
}

void afterGirlHand100(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x65, D_0063A61C);
    ACTGame_DisconnectHand();
}

extern char D_00553A30[];
extern char D_005539D0[];
extern void afterGirlHand200(volatile int a0);

void actGirlHand200(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);

    debug_StdPrintfDummy(D_00553A30);
    *(int *)(sub + 0x34) = 0x54;
    *(void **)(sub + 0x14) = (void *)afterGirlHand200;
    *(int *)(sub + 0xE0) = 0;
    do {
        _ACTWait(1);
    } while ((*(int *)(sub + 0xE0) & 0x10) == 0);
    debug_StdPrintfDummy(D_005539D0);
    for (;;) {
        ACTSendMailCorrect((void *)a0, 0x6A);
        _ACTWait(1);
    }
}

void afterGirlHand200(volatile int a0)
{
    debug_StdPrintfDummy(D_005539A0);
    iosOmSendMail(D_00639EA4, 0x6A, D_0063A61C);
    ACTGame_DisconnectHand();
}

int NotNeedBackHand(void)
{
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

void SetGirlDangerGObj(int a0)
{
    char *g = D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = a0;
    }
}

void ClearGirlDangerGObj(void)
{
    char *g = (char *)D_00639EA8;
    if (g != 0) {
        *(int *)(*(char **)(*(char **)(g + 0x164) + 0x688) + 0x3E4) = 0;
    }
}

void subGirlBrain_Idle(volatile int a0)
{
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x164) + 0x34C) = 0;
    _ACTWait(0);
}

void subGirlBrain_Hesitate(volatile int a0)
{
    char *s = *(char **)((char *)a0 + 0x164);
    int i = 1;

    for (;;) {
        *(void **)(s + 0x34C) = 0;
        if (i % ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2) == 0) {
            D_0029D650[0x58F0] = 1;
        }
        i++;
        _ACTWait(1);
    }
}

void subGirlBrain_Becarry(volatile int a0)
{
    char *g = (char *)a0;
    *(int *)(*(char **)(g + 0x164) + 0x34C) = 0;
    _ACTWait(0);
}

extern int ACTGameView_Check(void *self, void *target);

void subGirlBrain_Busy(volatile int a0)
{
    char *sub = *(char **)((char *)a0 + 0x164);
    GirlBrainWork *w = (GirlBrainWork *)D_0029D650;
    int i = 0;

    *(int *)(sub + 0x34C) = 0;
    while (1) {
        if (w->f_C90) {
            _ACTCharStatus_Set((void *)a0, 2, -1.0f, w->f_CA0);
        }
        if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] < i &&
             ACTGameView_Check((void *)a0, D_00639EA4)) ||
            (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 2 < i) {
            w->f_58F0 = 1;
        }
        i++;
        _ACTWait(1);
    }
}

extern int D_006C1E40[];
extern void Danger_Bomb(void *self);
extern void Danger_Gondola(void *self);
extern void Danger_Box(void *self);
extern void Danger_Rotobject(void *self);

void subGirlBrain_DangerEnv(volatile int a0)
{
    switch (D_006C1E40[0]) {
    case 1:
        Danger_Bomb((void *)a0);
        break;
    case 2:
        Danger_Gondola((void *)a0);
        break;
    case 3:
        Danger_Box((void *)a0);
        break;
    case 4:
        Danger_Rotobject((void *)a0);
        break;
    }
    _ACTWait(0);
}

int enemy_list_compare(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}

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
        if (work.f_88 == 0)
            goto no_wall;
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
    do {
        ACTGame_DisconnectHand();
        debug_StdPrintfDummy(D_00553E50);
        iosPadActStop(7);
        ACTWay_SetBeginPositionIllegal(local);
    } while (0);
}

void afterGirlPulledGo(void *a0)
{
    void *volatile q = a0;
    int *p = *(int **)((char *)q + 0x15C);
    *(int *)((char *)p + 0x634) = 0;
}

extern char D_00554048[];

void actGirlJump(volatile int a0)
{
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

int isMustCheckCylinder(void *a, void *b)
{
    if ((a == (void *)D_00639EA4 && b == D_00639EA8) ||
        (a == D_00639EA8 && b == (void *)D_00639EA4)) {
        if (*(int *)(*(char **)((char *)D_00639EA8 + 0x164) + 0x34) == 0x51) {
            return 1;
        }
    }
    return 0;
}

extern void RequestChangeHandMode(void *a0, int a1, int a2, int a3, void *a4, int a5, void *a6);

void afterGirlHintPoint(volatile int a0)
{
    RequestChangeHandMode((void *)a0, 1, 4, 0, 0, 0, 0);
}
