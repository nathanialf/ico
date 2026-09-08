#include "common.h"
#include "ico/types.h"

typedef struct {
    char _0[0x1C];
    int f_1C;
    char _20[4];
} WeaponEntry;

typedef struct {
    long long w;
} __attribute__((packed)) U64ag;

typedef struct {
    char _00[0x20];
    float _20, _24, _28;
    char _2c[0x44];
    float _70;
    char _74[0x0C];
    int _80;
    char _84[0x04];
    int _88;
    int _8c;
    char _90[0x04];
    int _94;
    int _98;
    char _9c[0x24];
} HandWork;

typedef union {
    int i;
    float f;
} IntFloat;

/* The 0x194-byte-per-entry motion record table, indexed by the object's
   current motion id (obj->0x15C->0x4A0). */
typedef struct {
    char _000[0x150];
    int f_150;
    char _154[0x2C];
    short f_180;
    short f_182;
    short f_184;
    char _186[0x02];

    union {
        unsigned int w;

        struct {
            unsigned short lo, hi;
        } h;
    } u_188;

    unsigned int f_18C;
    char _190[0x04];
} MotionRec;

extern MotionRec D_0055FE58[];
extern void gamesysObjInfoCls(int a0, int a1);
extern int stage_no;
extern void gamesysObjInfoPosSetStage(char *a0, int a1, int a2, int a3);

void ACTGame_SaveActorInformation(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    if (((int)(*(unsigned long long *)(s + 0x18) >> 39) & 1) && *(int *)(s + 0x4C) % 30 == 0) {
        gamesysObjInfoPosSetStage(a0, *(int *)(s + 0x444), 0, stage_no);
    }
}

void ACTGame_DeleteActorInformation(int *a0)
{
    gamesysObjInfoCls(a0[3], a0[2]);
}

/* The exit table: one 40-byte entry per exit, in .rodata. */
typedef struct {
    float pos[3];
    float rot[3];
    int f_18;
    int f_1C;
    int f_20;
    int f_24;
} ExitData;

extern const ExitData D_0055C518[];
extern int exit_no;
extern void test_nextstage_firstwalk_set(int unused, int a, int b, int c);
extern void sceVu0ScaleVector(void *dst, void *src, float k);

void EXITDATA_GetNextPosition(int idx, float *pos, float *rot)
{
    exit_no = idx;
    test_nextstage_firstwalk_set(idx, D_0055C518[idx].f_18, D_0055C518[idx].f_1C,
                                 D_0055C518[idx].f_20);

    pos[0] = -D_0055C518[idx].pos[0];
    pos[1] = -D_0055C518[idx].pos[1];
    pos[2] = -D_0055C518[idx].pos[2];

    rot[0] = D_0055C518[idx].rot[0];
    rot[1] = D_0055C518[idx].rot[1];
    rot[2] = D_0055C518[idx].rot[2];

    sceVu0ScaleVector(rot, rot, 0.017453292f);
}

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4S;

extern char *D_00639EA8;
extern void *memset(void *a0, int a1, int a2);
extern void _ApplyRyGV(void *v, float ry);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void gamesysObjInfoPosNewStageSet(char *self, char *other, int v, float *tmp_a,
                                         float *tmp_b);

void ACTGame_StageChangeGObj(char *self, int idx)
{
    float tmp_a[4];
    float tmp_b[4];
    float buf[4];
    Vec4S buf2;
    Vec4S buf3;

    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    if (*(int *)(self + 0xC) == 0x11) {
        memset(buf, 0, 0x10);
        buf[2] = 250.0f;
        _ApplyRyGV(buf, -tmp_b[1]);
        sceVu0AddVector(tmp_a, tmp_a, buf);
    }
    if (self == D_00639EA8) {
        if (0.0f <= *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x330)) {
            memset(&buf3, 0, 0x10);
            buf3.z = -*(float *)(*(char **)(*(char **)(D_00639EA8 + 0x164) + 0x688) + 0x330);
            buf2 = buf3;
            _ApplyRyGV(&buf2, -tmp_b[1]);
            sceVu0AddVector(tmp_a, tmp_a, &buf2);
        }
    }
    gamesysObjInfoPosNewStageSet((char *)*(int *)(self + 0x8), (char *)*(int *)(self + 0xC),
                                 D_0055C518[idx].f_24, tmp_a, tmp_b);
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetActors_Debug);

extern char *D_00639EA4;
extern char *D_00639EA8;
extern void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6,
                                  float *p7);

void ACTGame_TryConnectHand(void)
{
    RequestChangeHandMode(D_00639EA4, 1, 5, 5, (int)D_00639EA8, 0, 0);
}

void ACTGame_TryDisconnectHand(void)
{
    RequestChangeHandMode(D_00639EA4, 1, 5, 0, 0, 0, 0);
}

extern void ACTGame_DisconnectHand(void);
extern const char D_005523F0[];
extern void debug_StdPrintfDummy();

void ACTGame_DisconnectHand_WithMail(void)
{
    ACTGame_DisconnectHand();
    debug_StdPrintfDummy(D_005523F0);
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckView);
ASM_LIT4_SLOT(D_00638CCC, 0.8f);
ASM_LIT4_SLOT(D_00638CD0, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGameView_Loop);
ASM_LIT4_SLOT(D_00638CD4, 5000.0f);

extern void DispMultiBgaManagerWithKind(int a0, int a1, int a2);

void ACTGame_LwsEffectProcess(char *a0)
{
    int m = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1B8);
    if (m != 0) {
        DispMultiBgaManagerWithKind(0x1F8, m, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", _ACTGame_SearchGObj);

extern int D_0063B13C;
extern char D_00552450[];
extern void debug_Printf(int a, int b, int c, const char *d, int e);
extern void GetRootPosition(void *dst, void *self);
extern int GetSkeltonFocusNode(void *a0, void *a1);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines GetSkeltonPosition (line 2244) here, so it is `inline` in
   the dev's TU; while this tail still has asm members a deferred inline would
   land at the object end instead of at its ROM slot, so the public body above
   stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void getSkeltonPosition(float *dst, char *obj, void *a2)
{
    int idx = GetSkeltonFocusNode(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}

int ACTLookTarget_Exec(char *a0)
{
    float pos[4];
    char *s = *(char **)(a0 + 0x164);
    char *t = *(char **)(s + 0xA8);
    int rv;
    int b0;

    if (D_0063B13C & 1) {
        debug_Printf(0xA, 0xAA, 0x0FFFFFFF, D_00552450,
                     *(int *)((char *)*(int *)(a0 + 0x15C) + 0x380));
    }
    rv = 0;
    if (*(int *)(s + 0xAC) == 0) {
        *(int *)((char *)*(int *)(a0 + 0x15C) + 0x380) = 0;
    } else {
        if (t == 0) {
            pos[0] = *(float *)(s + 0xC0);
            pos[1] = *(float *)(s + 0xC4);
            pos[2] = *(float *)(s + 0xC8);
        } else if (t == D_00639EA4) {
            getSkeltonPosition(pos, t, (void *)0x23);
        } else {
            GetRootPosition(pos, t);
        }
        b0 = *(int *)(s + 0xB0);
        rv = 1;
        ((IntFloat *)((char *)*(int *)(a0 + 0x15C) + 0x390))->f = pos[0];
        ((IntFloat *)((char *)*(int *)(a0 + 0x15C) + 0x394))->f = pos[1];
        ((IntFloat *)((char *)*(int *)(a0 + 0x15C) + 0x398))->f = pos[2];
        *(int *)((char *)*(int *)(a0 + 0x15C) + 0x380) = b0;
    }
    return rv;
}

extern void _ACTParaStatus_Set(char *a0, int a1);

void ACTParaStatus_Clear(char *a0)
{
    *(long long *)(*(char **)(a0 + 0x164) + 0x90) = 0;
    _ACTParaStatus_Set(a0, 0);
}

extern void ActPara_MakeTbl(int a0, long long a1, int a2);
extern int ActPara_GetDefTbl(void);
extern void SetParallelMotionTable(char *self, int tbl, int def, int a3, int a4);
extern float _GetRandom(void);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines _ACTParaStatus_Set (lines 2287-2288) here, so it is
   `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the
   public body below stays a plain definition and this caller uses the static
   stand-in.  Collapses to one `inline` definition at layout. */
static inline void actParaStatus_Set(char *a0, int bit)
{
    char *s = (char *)*(int *)(a0 + 0x164);
    *(unsigned long long *)(s + 0x90) |= (1ULL << bit) & ~*(unsigned long long *)(s + 0xA0);
}

void ACTParaStatus_Exec(char *self)
{
    char *s = (char *)*(int *)(self + 0x164);
    char *sub;
    char *p;
    int changed;

    changed = 0;
    if ((int)(*(unsigned long long *)(s + 0x20) >> 16) & 1) {
        actParaStatus_Set(self, 42);
    }
    if ((int)(*(unsigned long long *)(s + 0x20) >> 17) & 1) {
        actParaStatus_Set(self, 43);
    }
    if (*(unsigned long long *)(s + 0x90) != *(unsigned long long *)(s + 0x98)) {
        *(unsigned long long *)(s + 0x98) = *(unsigned long long *)(s + 0x90);
        changed = 1;
    }
    p = *(char **)(s + 0x680);
    if ((*(int *)(p + 0x5C))++ >= 121) {
        sub = *(char **)(self + 0x15C);
        if ((*(int *)(sub + 0x480) & 0x16) || *(int *)(sub + 0x4CC) != 0) {
            if (D_0055FE58[*(int *)(sub + 0x4A0)].f_150 == 1) {
                *(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x5C) = 0;
                *(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x60) =
                    (int)(_GetRandom() * 10.0f);
                changed = 1;
            }
        }
    }
    actParaStatus_Set(self, 1);
    if (changed == 0) {
        return;
    }
    ActPara_MakeTbl(*(int *)((char *)*(int *)(self + 0x164) + 0x688), *(long long *)(s + 0x90),
                    *(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x60));
    SetParallelMotionTable(
        self, *(int *)((char *)*(int *)(self + 0x164) + 0x688), ActPara_GetDefTbl(), 0,
        (int)*(float *)(*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x348));
}

extern float D_0063A69C[];
extern int D_0028F4C0[];
extern int *test_CURRENTROOT(int *a0);
extern float _DistGV(void *a, void *b);
extern int actEnemyFlagCheckActive(void *g);
extern int *isysGObjSearchFromObjKindID_begin(int);
extern int *isysGObjSearchFromObjKindID_next(int *);
extern void *memset(void *a0, int a1, int a2);
extern char *D_00639EA4;
extern char *D_00639EA8;

void _ACTCharStatus_Clear(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    int old = *(int *)(s + 0x7C);
    int *sel;
    int *g;
    float nearest;
    float d;

    memset(s + 0x58, 0, 0x38);
    if (a0 == D_00639EA4 || a0 == D_00639EA8) {
        nearest = D_0063A69C[0];
        sel = 0;
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            d = _DistGV(test_CURRENTROOT((int *)a0), test_CURRENTROOT(g));
            if (actEnemyFlagCheckActive(g)) {
                if (d < nearest) {
                    sel = g;
                    nearest = d;
                }
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        *(int **)(s + 0x7C) = sel;
        if (a0 == D_00639EA4) {
            if (old != 0 &&
                *(int *)(s + 0x10) % ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 2) != 0) {
                *(int *)(s + 0x7C) = old;
            }
        }
    }
}

extern int GetSkeltonFocusNode(void *a0, void *a1);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);

void GetSkeltonOrient(float *out, void *obj, int node)
{
    int n = GetSkeltonFocusNode(obj, (void *)node);
    if (*(int *)((char *)obj + 0xC) == 4) {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = -1.0f;
        *(int *)((char *)out + 0x8) = 0;
    } else {
        *(int *)((char *)out + 0x0) = 0;
        ((IntFloat *)((char *)out + 0x4))->f = 1.0f;
        *(int *)((char *)out + 0x8) = 0;
    }
    *(int *)((char *)out + 0xC) = 0;
    sceVu0ApplyMatrix(out, (char *)(*(int *)(*(int *)((char *)obj + 0x15C) + 0xC) + (n << 6)), out);
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_InnerVelocityUpdate);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_BeforeFunc);

extern char *actEnemy_GetClingTarget(void *g);
extern int iosOmSendMail();

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines _ACTCharStatus_Set (2430-2431), _ACTCharStatus_Check
   (2469-2472) and ACTGame_SetMotionPlaySpeedRatio_Reserve (2493-2496) here,
   so they are `inline` in the dev's TU; while this tail still has asm members
   a deferred inline would land at the object end instead of at its ROM slot,
   so the public bodies below stay plain definitions and this caller uses the
   static stand-ins.  Collapses to one `inline` definition at layout. */
static inline void actCharStatus_Set(char *a0, int bit, float f, int val)
{
    char *s = *(char **)(a0 + 0x164);

    *(long long *)(s + 0x58) |= 1LL << bit;

    switch (bit) {
    case 8:
        *(float *)(s + 0x68) = f;
        break;
    case 5:
        *(float *)(s + 0x6C) = f;
        break;
    case 17:
        *(float *)(s + 0x70) = f;
        break;
    case 18:
        *(int *)(s + 0x74) = val;
        break;
    case 10:
        *(int *)(s + 0x78) = val;
        break;
    case 2:
        *(int *)(s + 0x7C) = val;
        break;
    case 11:
        *(int *)(s + 0x88) = val;
        break;
    }
}

static inline unsigned char actCharStatus_Check(char *a0, int bit)
{
    char *s = (char *)*(int *)(a0 + 0x164);
    int r = 0;
    if (s != 0) {
        r = (*(unsigned long long *)(s + 0x58) >> bit) & 1;
    }
    if (r != 0) {
        return 1;
    }
    return 0;
}

static inline void actGame_SetMotionPlaySpeedRatio_Reserve(char *a0, unsigned int a1, float f)
{
    char *p = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    if (*(unsigned int *)(p + 0x54) <= a1) {
        *(float *)(p + 0x58) = f;
        *(unsigned int *)(p + 0x54) = a1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", FunctionAboutClingedStatus);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTEnvGetTest);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ActOrientTest);
ASM_LIT4_SLOT(D_00638CD8, -1.5707964f);
ASM_LIT4_SLOT(D_00638CDC, 1.5707964f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetGirlHandlinkClInfo);
ASM_LIT4_SLOT(D_00638CE0, 12100.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", hand_able_connect);
ASM_LIT4_SLOT(D_00638CE4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CommonLoop);
ASM_LIT4_SLOT(D_00638CE8, 160000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", GetTarget);
ASM_LIT4_SLOT(D_00638CEC, 0.3f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTLookTargetSystem_Exec);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTItemThrow);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTItemWatchMotion);
ASM_LIT4_SLOT(D_00638CF0, 0.2f);

extern void GetRootPosition(void *dst, void *self);
extern float _DistSqGV(int *a0, int a1);
extern float IsPointIsInScreen(void *dst, void *root);
extern void PrivInsCamSet(void *a0, void *a1, void *a2, int a3, int a4, int a5, float f0, float f1);

void ACTGame_InsertCamera_GirlIsPinch(void)
{
    float p0[4];
    float p1[4];
    float p2[4];

    if (D_00639EA4 == 0 || D_00639EA8 == 0) {
        return;
    }
    GetRootPosition(p0, D_00639EA4);
    GetRootPosition(p1, D_00639EA8);
    if (_DistSqGV((int *)p0, (int)p1) < 22500.0f) {
        return;
    }
    if (IsPointIsInScreen(p2, test_CURRENTROOT((int *)D_00639EA8)) > 0.0f) {
        return;
    }
    if (D_00639EA4 == 0 || D_00639EA8 == 0) {
        return;
    }
    PrivInsCamSet(test_CURRENTROOT((int *)D_00639EA4), test_CURRENTROOT((int *)D_00639EA8),
                  D_00639EA4, (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 100 / 60,
                  (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 45 / 60, 1, 0.05f, 0.25f);
}

extern char D_00552420[];
extern char D_0063A698[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

/* The pending hand-mode command record: two ints at +0x314 (connect) and
   +0x31C (disconnect) of the actor's hand work block. */
typedef struct {
    int f_0;
    int f_4;
} HandModeCmd;

void RequestChangeHandMode(char *self, int mode, int pri, int flag, int p5, int p6, float *p7)
{
    HandModeCmd *hmc = 0;

    /* updateHMC is a nested function in the ROM: RequestChangeHandMode
       passes it a static chain in $2 (STATIC_CHAIN_REGNUM) which it spills
       to 0(sp), and reads self/mode/pri/flag/p5/p6/p7 and hmc out of the
       parent frame through it.  The listing names it updateHMC.415. */
    void updateHMC(void)
    {
        hmc->f_0 = flag;
        hmc->f_4 = pri;
        switch (mode) {
        case 0:
            *(int *)(*(char **)(self + 0x15C) + 0x310) = hmc->f_0;
            *(int *)(*(char **)(self + 0x15C) + 0x314) = p5;
            *(int *)(*(char **)(self + 0x15C) + 0x318) = p6;
            if (p7 != 0) {
                *(float *)(*(char **)(self + 0x15C) + 0x320) = p7[0];
                *(float *)(*(char **)(self + 0x15C) + 0x324) = p7[1];
                *(float *)(*(char **)(self + 0x15C) + 0x328) = p7[2];
            }
            break;
        case 1:
            *(int *)(*(char **)(self + 0x15C) + 0x2B0) = hmc->f_0;
            *(int *)(*(char **)(self + 0x15C) + 0x2B4) = p5;
            *(int *)(*(char **)(self + 0x15C) + 0x2B8) = p6;
            if (p7 != 0) {
                *(float *)(*(char **)(self + 0x15C) + 0x2C0) = p7[0];
                *(float *)(*(char **)(self + 0x15C) + 0x2C4) = p7[1];
                *(float *)(*(char **)(self + 0x15C) + 0x2C8) = p7[2];
            }
            break;
        }
    }

    switch (mode) {
    case 0:
        hmc = (HandModeCmd *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x314);
        break;
    case 1:
        hmc = (HandModeCmd *)(*(char **)(*(char **)(self + 0x164) + 0x680) + 0x31C);
        break;
    default:
        debug_assert(D_00552420, 4727);
        __assert(D_00552420, 4727, D_0063A698);
        break;
    }
    if (pri < 3) {
        if (pri > 0) {
            if (flag == 0) {
                if (hmc->f_4 != pri) {
                    return;
                }
            }
        }
    }
    if (hmc->f_4 == 0 || hmc->f_0 == 0) {
        updateHMC();
    } else if (pri >= hmc->f_4) {
        updateHMC();
    }
}

extern char *D_00639EA4;

int ACTNotNeedCameraOffset(char *a0)
{
    char *s;
    if (a0 != 0 && a0 == D_00639EA4) {
        s = *(char **)(a0 + 0x164);
        if (s != 0) {
            return (int)(*(unsigned long long *)(s + 0x20) >> 41) & 1;
        }
    }
    return 0;
}

void ACTGameCollisionOn(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 1;
    ((int *)self[0x57])[0x153] = 1;
    ((int *)self[0x57])[0x152] = 1;
    ((int *)self[0x57])[0x1F] = 1;
}

void ACTGameCollisionOff(volatile int *self)
{
    ((int *)self[0x57])[0x151] = 0;
    ((int *)self[0x57])[0x153] = 0;
    ((int *)self[0x57])[0x152] = 0;
    ((int *)self[0x57])[0x1F] = 0;
}

int ACTGame_CheckItemMotion(char *a0)
{
    MotionRec *rec = &D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)];
    return (rec->u_188.w >> 19) & 7;
}

int ACTGame_CheckHandMotion(char *a0, char *a1)
{
    MotionRec *rec0 = &D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)];
    MotionRec *rec1 = &D_0055FE58[*(int *)(*(char **)(a1 + 0x15C) + 0x4A0)];
    int b0 = (rec0->f_18C >> 18) & 1;
    int b1 = (rec1->f_18C >> 18) & 1;
    return b0 & b1;
}

extern void gamesysObjInfoPosNewStageSet(char *self, char *other, int v, float *tmp_a,
                                         float *tmp_b);

void ACTGame_StageChangeGObjID(char *self, char *other, int idx)
{
    float tmp_a[4];
    float tmp_b[4];
    EXITDATA_GetNextPosition(idx, tmp_a, tmp_b);
    gamesysObjInfoPosNewStageSet(self, other, D_0055C518[idx].f_24, tmp_a, tmp_b);
}

extern void *memset(void *a0, int a1, int a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

void ACTGame_StageChangeGObjDirect(int *a0, int a1, void *a2, int a3)
{
    float buf0[4];
    float buf1[4];
    memset(buf1, 0, 0x10);
    buf1[1] = (float)a3 * 3.1415927f / 180.0f;
    sceVu0ScaleVector(buf0, a2, -1.0f);
    gamesysObjInfoPosNewStageSet((char *)a0[2], (char *)a0[3], a1, buf0, buf1);
}

int ACTGame_FLAG_LIFEPINCH(char *a0)
{
    if (*(float *)(*(char **)(a0 + 0x164) + 0x1E0) <= 20.0f)
        return 1;
    return 0;
}

extern char *D_00639EA8;

/* Returns a char-width boolean: the three PAIR_IsStatus_* sites the listing
   inlines this into all mask the result with `andi 0xff`, which only a
   narrower-than-int return type produces.  The `int` intermediate keeps the
   SI->QI conversion at the `return`; folding it into the `& 1` (i.e. writing
   the expression directly in the return) makes gcc distribute the narrowing
   over the mask and emit a second `andi`. */
unsigned char ACTGame_FLAG_TETSUNAGI(void)
{
    char *g = D_00639EA8;
    int flag;
    if (g == 0)
        return 0;
    flag = (int)(*(unsigned long long *)(*(char **)(g + 0x164) + 0x18) >> 40) & 1;
    return flag;
}

int ACTGame_FLAG_TETSUNAGI_VISUAL(void)
{
    char *g = D_00639EA8;
    if (g == 0)
        return 0;
    return (int)(*(unsigned long long *)(*(char **)(g + 0x164) + 0x18) >> 42) & 1;
}

extern int GetSkeltonFocusNode(void *a0, void *a1);

void GetSkeltonPosition(float *dst, char *obj, void *a2)
{
    int idx = GetSkeltonFocusNode(obj, a2) << 6;
    ((IntFloat *)dst)[0].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(idx + *(int *)((int)((GObj *)(obj))->p_15C + 0xC) + 0x38);
}

extern float FSqrt(float a0);
extern void GetSkeltonPosition__pn(void *a0, void *a1, int a2) __asm__("GetSkeltonPosition");
extern void SetDirectRootPositionNoFittingWithNodePoint(void *a0, void *a1, void *a2, float a3);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void SetDirectRootPositionWithNodePointLimit(void *a0, void *a1, void *a2, float farg0, float farg1)
{
    float buf0[4];
    float buf18[4];
    float buf16[4];

    GetSkeltonPosition__pn(buf0, a0, a1);
    sceVu0SubVector(buf16, a2, buf0);
    if (farg1 < FSqrt(buf16[0] * buf16[0] + buf16[1] * buf16[1] + buf16[2] * buf16[2])) {
        sceVu0Normalize(buf16, buf16);
        sceVu0ScaleVector(buf16, buf16, farg1);
        sceVu0AddVector(buf18, buf0, buf16);
        if (0.0f < buf18[1] - *(float *)((char *)a2 + 4)) {
            buf18[1] = *(float *)((char *)a2 + 4);
        }
        SetDirectRootPositionNoFittingWithNodePoint(a0, a1, buf18, 1.0f);
        return;
    }
    SetDirectRootPositionNoFittingWithNodePoint(a0, a1, a2, farg0);
}

extern int D_006C0470[];

void ACTGameView_Init(void)
{
    int *p = D_006C0470;
    *(int *)((char *)p + 0x4B0) = 0;
    *(int *)((char *)p + 0x4B4) = 0;
}

void ACTCharctrl_Lock(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 48);
    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 49);
}

void ACTCharctrl_Unlock(char *a0)
{
    char *p = *(char **)(a0 + 0x164);
    *(unsigned long long *)(p + 0x18) |= (1ULL << 48);
    *(unsigned long long *)(p + 0x18) |= (1ULL << 49);
}

extern char *D_00639EA4;
extern char *D_00639EA8;

void ACTGame_ConnectHand(void)
{
    char *s = *(char **)(D_00639EA8 + 0x164);
    RequestChangeHandMode(D_00639EA8, 0, 5, 6, (int)D_00639EA4, 0, 0);
    RequestChangeHandMode(D_00639EA4, 1, 5, 5, (int)D_00639EA8, 0, 0);
    *(unsigned long long *)(s + 0x18) |= (1ULL << 40);
}

extern char *D_00639EA4;
extern char *D_00639EA8;

void ACTGame_DisconnectHand(void)
{
    char *s = *(char **)(D_00639EA8 + 0x164);
    RequestChangeHandMode(D_00639EA8, 0, 5, 0, 0, 0, 0);
    RequestChangeHandMode(D_00639EA4, 1, 5, 0, 0, 0, 0);
    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 40);
}

extern char *D_00639EA4;

void PAIR_GetPosition_BOY(float *a0, float *a1)
{
    float *q = (float *)*(char **)(D_00639EA4 + 0x164);
    a0[0] = q[0x500 / 4];
    a0[1] = q[0x504 / 4];
    a0[2] = q[0x508 / 4];
    a1[0] = q[0x4C0 / 4];
    a1[1] = q[0x4C4 / 4];
    a1[2] = q[0x4C8 / 4];
}

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTGame_FLAG_TETSUNAGI (lines 1175-1177) into the three
   PAIR_IsStatus_* predicates below, so it is `inline` in the dev's TU; while
   this tail still has asm members a deferred inline would land at the object
   end instead of at its ROM slot, so the public body above stays a plain
   definition and these callers use the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline unsigned char actGame_FLAG_TETSUNAGI(void)
{
    char *g = D_00639EA8;
    int flag;
    if (g == 0)
        return 0;
    flag = (int)(*(unsigned long long *)(*(char **)(g + 0x164) + 0x18) >> 40) & 1;
    return flag;
}

int PAIR_IsStatus_BOY_PULL(void)
{
    switch (*(unsigned int *)(*(char **)(D_00639EA4 + 0x164) + 0x34)) {
    case 0x4E:
    case 0x4F:
        return 1;

    case 1:
    case 2:
    case 3:
        if (actGame_FLAG_TETSUNAGI()) {
            return 1;
        }
        break;
    }
    return 0;
}

int PAIR_IsStatus_GIRL_PULL(void)
{
    switch (*(unsigned int *)(*(char **)(D_00639EA8 + 0x164) + 0x34)) {
    case 4:
    case 0x45:
    case 0x50:
    case 0x51:
        return 1;

    case 1:
    case 2:
    case 3:
        if (actGame_FLAG_TETSUNAGI()) {
            return 1;
        }
        break;
    }
    return 0;
}

int PAIR_IsStatus_BOY_WAIT(void)
{
    char *b = D_00639EA4;

    if (b != 0) {
        switch (*(unsigned int *)(*(char **)(b + 0x164) + 0x34)) {
        case 0x4E:
        case 0x58:
            if (D_0055FE58[*(int *)(*(char **)(b + 0x15C) + 0x4A0)].f_150 == 1) {
                return 1;
            }
            break;
        }
    }
    return 0;
}

extern char *D_00639EA4;

void PAIR_GetPosition_BOY_DITCH(float *a0, float *a1)
{
    float *q = (float *)*(char **)(D_00639EA4 + 0x164);
    a0[0] = q[0x510 / 4];
    a0[1] = q[0x514 / 4];
    a0[2] = q[0x518 / 4];
    a1[0] = q[0x520 / 4];
    a1[1] = q[0x524 / 4];
    a1[2] = q[0x528 / 4];
}

int PAIR_IsStatus_BOY_DITCH(void)
{
    char *b = D_00639EA4;

    switch (*(unsigned int *)(*(char **)(b + 0x164) + 0x34)) {
    case 0x58:
        if (D_0055FE58[*(int *)(*(char **)(b + 0x15C) + 0x4A0)].f_150 != 1) {
            break;
        }
        /* fall through */
    case 0x59:
    case 0x5C:
        return 1;

    case 1:
    case 2:
    case 3:
        if (actGame_FLAG_TETSUNAGI()) {
            return 1;
        }
        break;
    }
    return 0;
}

extern char *D_00639EA4;
extern char D_005577D0[];

int ACTGame_isHangChain(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    if (a0 == D_00639EA4) {
        char *attr = D_005577D0 + *(int *)(s + 0x34) * 0x50;
        if ((*(unsigned int *)(attr + 0x4C) >> 2) & 1) {
            return *(int *)(s + 0x190);
        }
    }
    return 0;
}

extern int ACTGame_isWeaponCombustible(void);
extern int GetTorchGObjOfWeapon(int *self);

int ACTGame_isWeaponEnableCatchfire(int *self)
{
    unsigned long new_var;
    int ret = 0;
    new_var = ACTGame_isWeaponCombustible();
    if (new_var != 0) {
        ret = GetTorchGObjOfWeapon(self);
    }
    return ret;
}

extern void ClipWall(void *);
extern void ClipFloor(void *);
extern void sceVu0CopyVector(void *buf, int x);

int ACTCheckCollis_WF(float f, void *p0, void *p1, void *actor, void *posout)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    sceVu0CopyVector(&work, (int)p0);
    sceVu0CopyVector((char *)&work + 0x10, (int)p1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (work._88 == 0) {
        ClipFloor(&work);
        if (work._94 == 0) {
            rv = 0;
        }
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv & 0xFF;
}

extern void ClipWall(void *);
extern void GetOrientOfWall(void *out, int n, void *vec);
extern void *memset(void *a0, int a1, int a2);
extern void sceVu0CopyVector(void *buf, int x);

int ACTCheckCollis_W(float f, void *hand0, void *hand1, void *actor, void *posout, void *magtarget,
                     int *flagout)
{
    HandWork work;
    int flag;
    int rv;
    int cnt;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    sceVu0CopyVector(&work, (int)hand0);
    sceVu0CopyVector((char *)&work + 0x10, (int)hand1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (flagout != 0) {
        *flagout = work._98;
    }
    cnt = work._88;
    if (cnt == 0) {
        rv = 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    if (cnt != 0 && magtarget != 0) {
        GetOrientOfWall(magtarget, cnt, &work._80);
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv & 0xFF;
}

int ACTCheckCollis_CI(int a0, int a1, int *a2, char *a3)
{
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    *(int *)(buf + 0x70) = 0;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 0x10, a1);
    ClipWall(buf);
    if (a2 != 0) {
        *a2 = *(int *)(buf + 0x98);
    }
    if (a3 != 0) {
        *(U64ag *)a3 = *(U64ag *)(buf + 0x80);
        *(int *)(a3 + 8) = *(int *)(buf + 0x88);
    }
    return *(int *)(buf + 0x88) != 0;
}

extern int D_0063A6B0;

int ACTCheckCollis_WELL(float f, void *p0, void *p1, void *actor, void *posout)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    D_0063A6B0 = 0;
    sceVu0CopyVector(&work, (int)p0);
    sceVu0CopyVector((char *)&work + 0x10, (int)p1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipFloor(&work);
    if (work._94 == 0) {
        rv = 0;
    } else {
        D_0063A6B0 = work._8c;
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTCheckCollis_WAY);

extern void ClipWall(void *);
extern void ClipFloor(void *);
extern void sceVu0CopyVector(void *buf, int x);
extern int ACTCheckView(char *self, void *a1, void *a2, void *a3, float f);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTCheckCollis_VIEW (line 1606) here and in
   ACTCheckViewClDetail, so it is `inline` in the dev's TU; while this tail
   still has asm members a deferred inline would land at the object end
   instead of at its ROM slot, so the public body below stays a plain
   definition and these callers use the static stand-in.  Collapses to one
   `inline` definition at layout. */
static inline unsigned char actCheckCollis_VIEW(float f, void *p0, void *p1, void *actor)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;

    if (!(_DistSqGV((int *)p0, (int)p1) < 25000000.0f)) {
        return 1;
    }

    work._70 = f;
    sceVu0CopyVector(&work, (int)p0);
    sceVu0CopyVector((char *)&work + 0x10, (int)p1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (work._88 == 0) {
        ClipFloor(&work);
        if (work._94 == 0) {
            rv = 0;
        }
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv;
}

int ACTCheckViewCl(char *self, void *a1, void *a2, void *a3, float f)
{
    float pos[4];
    float *m;
    int n;

    if (*(int *)(self + 0xC) == 4) {
        return 1;
    }
    n = GetSkeltonFocusNode(self, (void *)0x23) << 6;
    m = (float *)(n + *(int *)((int)((GObj *)(self))->p_15C + 0xC));
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    if (ACTCheckView(self, a1, a2, a3, f) == 0) {
        return 0;
    }
    return actCheckCollis_VIEW(0.0f, pos, a2, a1) == 0;
}

extern char D_00552400[];
extern char D_00552420[];
extern char D_0063A698[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern int *isysGObjSearchFromObjKindID_begin(int);
extern int *isysGObjSearchFromObjKindID_next(int *);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTGameView_Add (line 1788) here, so it is `inline` in the
   dev's TU; while this tail still has asm members a deferred inline would
   land at the object end instead of at its ROM slot, so the public body
   below stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void actGameView_Add(char *a0, char *a1)
{
    int n = D_006C0470[0x4B0 / 4]++;
    if (n >= 100) {
        debug_StdPrintfDummy(D_00552400);
        debug_assert(D_00552420, 0x6FF);
        __assert(D_00552420, 0x6FF, D_0063A698);
    }
    *(char **)&D_006C0470[n] = a1;
    *(int *)((char *)D_006C0470 + n * 4 + 0x190) = 0;
    *(int *)((char *)D_006C0470 + n * 4 + 0x320) = 0;
}

void ACTGameView_FirstSet(void)
{
    int *g;

    g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        actGameView_Add((char *)g, (char *)g);
        g = isysGObjSearchFromObjKindID_next(g);
    }
}

extern char D_00552400[];
extern char D_00552420[];
extern char D_0063A698[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

/* D_006C0470 is one table: a 100-entry object list at +0x000, two parallel
   100-entry int arrays at +0x190 and +0x320, and the entry count at +0x4B0.
   The list slot holds a pointer, so its store is in a different alias set
   from the two int stores -- that is what lets ROM schedule the +0x190
   address ahead of the list address. */
void ACTGameView_Add(char *a0, char *a1)
{
    int n = D_006C0470[0x4B0 / 4]++;
    if (n >= 100) {
        debug_StdPrintfDummy(D_00552400);
        debug_assert(D_00552420, 0x6FF);
        __assert(D_00552420, 0x6FF, D_0063A698);
    }
    *(char **)&D_006C0470[n] = a1;
    *(int *)((char *)D_006C0470 + n * 4 + 0x190) = 0;
    *(int *)((char *)D_006C0470 + n * 4 + 0x320) = 0;
}

int ACTGameView_Check(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006C0470[0x4B0 / 4]; i++) {
        if (D_006C0470[i] == a1) {
            return *((unsigned char *)&D_006C0470[i] + 0x190);
        }
    }
    return 0;
}

int ACTGameViewSimple_Check(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006C0470[0x12C]; i++) {
        if (D_006C0470[i] == a1) {
            return *(unsigned char *)((char *)D_006C0470 + i * 4 + 0x320);
        }
    }
    return 0;
}

extern int CheckWeaponKind();
extern WeaponEntry D_00318EB8[];

int ACTGame_GetMotOrientFromWeapon(int a0)
{
    int rv;
    if (a0 != 0) {
        rv = D_00318EB8[CheckWeaponKind(a0)].f_1C;
    } else {
        rv = 0;
    }
    return rv;
}

int ACTGame_NoWeapon(char *a0)
{
    char *w = *(char **)(*(char **)(a0 + 0x164) + 0x150);
    int r = 0;
    if (w == 0 || CheckWeaponKind(w) == 0)
        r = 1;
    return r;
}

int ACTGame_isWeaponCombustible(void)
{
    return CheckWeaponKind() == 1;
}

extern const float D_0063A6AC[];
extern float _DistSqGV(int *a0, int a1);
extern int *isysGObjSearchFromObjKindID_begin(int);
extern int *isysGObjSearchFromObjKindID_next(int *);
extern int *test_CURRENTROOT(int *a0);

int *ACTGame_GetNearestGObj(int a0, int a1)
{
    float best_val = D_0063A6AC[0];
    int *best = 0;
    int *node;

    node = isysGObjSearchFromObjKindID_begin(a1);
    if (node != 0) {
        do {
            float val = _DistSqGV(test_CURRENTROOT(node), a0);
            if (val < best_val) {
                best_val = val;
                best = node;
            }
            node = isysGObjSearchFromObjKindID_next(node);
        } while (node != 0);
    }
    return best;
}

void ACTLookTarget_Init(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    *(int *)(s + 0xA8) = 0;
    *(int *)(s + 0xB0) = 0;
    *(int *)(s + 0xAC) = 0;
}

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTLookTarget_Init (lines 2183-2187) into
   _ACTLookTarget_Set, so it is `inline` in the dev's TU; while this tail
   still has asm members a deferred inline would land at the object end
   instead of at its ROM slot, so the public body above stays a plain
   definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline void actLookTarget_Init(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    *(int *)(s + 0xA8) = 0;
    *(int *)(s + 0xB0) = 0;
    *(int *)(s + 0xAC) = 0;
}

int _ACTLookTarget_Set(char *a0, int a1, float *a2, int a3, int a4)
{
    char *s = *(char **)(a0 + 0x164);
    int ret = 0;

    if (a3 == 6) {
        actLookTarget_Init(a0);
    } else if (a3 >= *(int *)(s + 0xAC)) {
        *(int *)(s + 0xA8) = a1;
        if (a2 != 0) {
            *(float *)(s + 0xC0) = a2[0];
            *(float *)(s + 0xC4) = a2[1];
            *(float *)(s + 0xC8) = a2[2];
        }
        *(int *)(s + 0xB0) = a4;
        *(int *)(s + 0xAC) = a3;
        ret = 1;
    }
    return ret;
}

extern void ActPara_InitSystem(void);
extern void ActPara_MakeTbl(int a0, long long a1, int a2);

void ACTParaStatus_Init(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    ActPara_InitSystem();
    ACTParaStatus_Clear(a0);
    ActPara_MakeTbl(*(int *)(*(char **)(a0 + 0x164) + 0x688), *(long long *)(s + 0x90), 0);
    *(long long *)(s + 0x98) = *(long long *)(s + 0x90);
}

void _ACTParaStatus_Set(char *a0, int bit)
{
    char *s = *(char **)(a0 + 0x164);
    *(unsigned long long *)(s + 0x90) |= (1ULL << bit) & ~*(unsigned long long *)(s + 0xA0);
}

unsigned long long _ACTParaStatus_Check(char *a0, int bit)
{
    char *s = *(char **)(a0 + 0x164);
    return (*(unsigned long long *)(s + 0x90) >> bit) & 1;
}

void _ACTCharStatus_Init(int **a0)
{
    long long *p = (long long *)a0[0x59];
    p[0xB] = 0;
    p[0xC] = 0;
}

void _ACTCharStatus_Set(char *a0, int bit, float f, int val)
{
    char *s = *(char **)(a0 + 0x164);

    *(long long *)(s + 0x58) |= 1LL << bit;

    switch (bit) {
    case 8:
        *(float *)(s + 0x68) = f;
        break;

    case 5:
        *(float *)(s + 0x6C) = f;
        break;

    case 17:
        *(float *)(s + 0x70) = f;
        break;

    case 18:
        *(int *)(s + 0x74) = val;
        break;

    case 10:
        *(int *)(s + 0x78) = val;
        break;

    case 2:
        *(int *)(s + 0x7C) = val;
        break;

    case 11:
        *(int *)(s + 0x88) = val;
        break;
    }
}

unsigned long long _ACTCharStatus_Check(char *a0, int bit)
{
    char *s = *(char **)(a0 + 0x164);
    unsigned long long r = 0;
    if (s != 0) {
        r = (*(unsigned long long *)(s + 0x58) >> bit) & 1;
    }
    return r;
}

void _ACTCharStatus_Exec(void) {}

void _ACTSetEnemyDisappearSpeed(char *a0, float f)
{
    *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x688) + 0x334) = f;
}

void ACTGame_SetMotionPlaySpeedRatio_Reserve(char *a0, unsigned int a1, float f)
{
    char *p = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    if (*(unsigned int *)(p + 0x54) <= a1) {
        *(float *)(p + 0x58) = f;
        *(unsigned int *)(p + 0x54) = a1;
    }
}

extern float D_002ADAF0[];

float _ACTGame_GetParamF(int idx)
{
    return D_002ADAF0[idx];
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_GetCurrentCallStatus);

int ACTGame_CheckPriInputFrame(char *a0)
{
    short f;

    f = D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)].f_184;
    if ((float)f < *(float *)(*(char **)(a0 + 0x15C) + 0x4AC) && f != -1) {
        return 1;
    }
    f = D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)].f_180;
    if (f != -1 && *(float *)(*(char **)(a0 + 0x15C) + 0x4AC) < (float)f) {
        return 1;
    }
    return 0;
}

extern int iosOmSendMail(char *a0, int mail);

void ACTGame_SendSoundMail(char *a0, int mail, int a2, int a3, int a4)
{
    switch (mail) {
    case 0x1A0:
        if (a4 != 0 && *(short *)(*(char **)(a0 + 0x164) + 0x13A) > 0) {
            break;
        }
        iosOmSendMail(a0, 0x1A0);
        if (a3 == 0) {
            break;
        }
        *(int *)(*(char **)(a0 + 0x164) + 0x134) = a3;
        *(unsigned long long *)(*(char **)(a0 + 0x164) + 0x138) =
            (*(unsigned long long *)(*(char **)(a0 + 0x164) + 0x138) & ~1ULL) | (a4 & 1);
        break;

    case 0x1A1:
        iosOmSendMail(a0, 0x1A1);

        *(int *)(*(char **)(a0 + 0x164) + 0x134) = a3;
        break;
    }
}

extern int InitMultiBgaManager(int a0);

void ACTGame_LwsEffectInit(char *a0)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1B8) = InitMultiBgaManager(1);
}

extern int *test_CURRENTROOT(int *a0);
extern void ActGame_GetOrientQ(void *q, void *v, int deg);
extern void _OrientXZGV(void *dst, void *a, void *b);
extern void stage_SetLoopFlag(int key, int a1);
extern void stage_SetFrameStep(int key, int a1);
extern void EntryMultiBgaManager(int id, int a1, int a2, int *root, void *q);

void ACTGame_LwsEffect_Guard(char *a0)
{
    float q[4];
    float v[4];
    char *p;

    _OrientXZGV(v, test_CURRENTROOT((int *)D_00639EA4), test_CURRENTROOT((int *)a0));
    ActGame_GetOrientQ(q, v, 0);

    stage_SetLoopFlag(0x1F8, 0);
    stage_SetFrameStep(0x1F8, 1);
    p = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    EntryMultiBgaManager(*(int *)(p + 0x1B8), 0, -1, test_CURRENTROOT((int *)a0), q);
}

extern void sceVu0ScaleVector(void *dst, void *src, float k);
extern float _GetDirection(void *v);
extern void SetIdentityQuaternion(void *q);
extern void RotQuaternionY(void *q, int ang);

void ActGame_GetOrientQ(void *q, void *v, int deg)
{
    float tmp[4];
    int n;

    sceVu0ScaleVector(tmp, v, -1.0f);
    n = (int)(_GetDirection(tmp) / 3.1415927f * 180.0f) + deg;
    SetIdentityQuaternion(q);
    RotQuaternionY(q, (short)(n * 32768 / 180));
}

extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);

void _GetRootObjectOrient(void *a0, char *a1)
{
    float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};
    sceVu0ApplyMatrix(a0, *(void **)(*(char **)(a1 + 0x15C) + 0xC), v);
}

extern void ReleaseItem(int item);

void ACTItemForceDrop(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    int item = *(int *)(s + 0x180);
    if (item != 0) {
        ReleaseItem(item);
        *(int *)(s + 0x180) = 0;
        *(int *)(s + 0x184) = 0;
    }
}

extern int gamesysGetGirlStageIDAndPosition(int *buf);
extern void OtherStagePositionGet(float *dst, int stage, int id, int *buf);
extern void _OrientGV(float *dst, float *a, float *b);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines GetGirlPositionAtThisStage (lines 4063-4067) here, so it is
   `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the
   public body below stays a plain definition and this caller uses the static
   stand-in.  Collapses to one `inline` definition at layout. */
static inline void getGirlPositionAtThisStage(float *dst)
{
    int buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(dst, stage_no, id, buf);
}

void GetOtherStageGirlOrient(float *a0, float *a1)
{
    float pos[4];
    getGirlPositionAtThisStage(pos);
    _OrientGV(a0, pos, a1);
}

extern int D_0063AA08;

int ACTChkAttackIgnore_BOY(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    if (*(int *)(s + 0x34) == 0x35 ||
        (*(int *)(*(char **)(s + 0x688) + 0x394) != 0 && D_0063AA08 != 0) ||
        ((int)(*(unsigned long long *)(s + 0x18) >> 35) & 1) == 0) {
        return 1;
    }
    return 0;
}

int ACTChkAttackIgnore_GIRL(char *a0, int *a1)
{
    char *s = *(char **)(a0 + 0x164);
    switch (*(int *)(s + 0x34)) {
    case 0x6F:
        return 1;

    case 5:
        if (a1 != 0 && a1[3] == 0x11) {
            return 1;
        }
        break;
    }
    return 0;
}

extern int D_0028F4C0[];

int ACTChkAttackIgnore_ENEMY(char *a0)
{
    char *s = *(char **)(a0 + 0x164);

    switch (*(int *)(s + 0x34)) {
    case 0x67:
        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] / 2 < *(int *)(s + 0x4C)) {
            return 1;
        }
        break;

    case 6:
        if (((int)(*(unsigned long long *)(s + 0x18) >> 57) & 1) && stage_no != 0x56 &&
            stage_no != 3 && stage_no != 0x2E) {
            return 1;
        }
        break;
    }
    return 0;
}

extern float _DistSqGV(int *a0, int a1);
extern void ClipFloor(void *);

unsigned char ACTCheckCollis_VIEW(float f, void *p0, void *p1, void *actor)
{
    HandWork work;
    int flag;
    int rv;

    memset(&work, 0, 0xC0);
    rv = 1;
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;

    if (!(_DistSqGV((int *)p0, (int)p1) < 25000000.0f)) {
        return 1;
    }

    work._70 = f;
    sceVu0CopyVector(&work, (int)p0);
    sceVu0CopyVector((char *)&work + 0x10, (int)p1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    if (work._88 == 0) {
        ClipFloor(&work);
        if (work._94 == 0) {
            rv = 0;
        }
    }
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    return rv;
}

int ACTCheckViewClDetail(char *self, void *a1, void *a2, void *a3, float f)
{
    float pos[4];
    float *m;
    int n;
    int ret;

    if (*(int *)(self + 0xC) == 4) {
        return 1;
    }
    n = GetSkeltonFocusNode(self, (void *)0x23) << 6;
    m = (float *)(n + *(int *)((int)((GObj *)(self))->p_15C + 0xC));
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    ret = ACTCheckView(self, a1, a2, a3, f);
    if (actCheckCollis_VIEW(0.0f, pos, a2, a1)) {
        return 0;
    }
    if (ret != 0) {
        return 1;
    }
    return 2;
}

void ACTGame_SetMotionPlaySpeedRatio_Clear(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x164) + 0x680);
    *(float *)(p + 0x58) = 1.0f;
    *(int *)(p + 0x54) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_SetMotionPlaySpeedRatio_Exec);

void GetGirlPositionAtThisStage(float *a0)
{
    int buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(a0, stage_no, id, buf);
}
