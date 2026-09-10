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

        char b;
    } u_188;

    unsigned int f_18C;
    unsigned int f_190;
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
        if (0.0f <= *(float *)((char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x330)) {
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

extern int GetSkeltonFocusNode(void *a0, void *a1);
extern float _DistGV(void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float *test_CURRENTORIENT(char *a0);
extern int _RotyGV(void *a, void *b);

int ACTCheckView(char *self, void *a1, void *a2, void *a3, float f)
{
    float pos[4];
    float v[4];
    float d[4];
    float *m;
    int n;

    n = GetSkeltonFocusNode(self, (void *)0x23) << 6;
    m = (float *)(n + *(int *)(*(char **)(self + 0x15C) + 0xC));
    pos[0] = m[12];
    pos[1] = m[13];
    pos[2] = m[14];
    if (_DistGV(pos, a2) < f) {
        return 1;
    }
    if ((int)a3 >= 360) {
        return 1;
    }
    /* SRCFILE.TXT rows put the whole of each arm on ONE source line (1666 /
       1667) -- a three-component vector set; v[3] is zeroed on the next line.
       The duplicated v[0]/v[2] stores are cross-jumped back into one copy. */
    if (*(int *)(self + 0xC) == 4) {
        v[0] = 0.0f;
        v[1] = -1.0f;
        v[2] = 0.0f;
    } else {
        v[0] = 0.0f;
        v[1] = 1.0f;
        v[2] = 0.0f;
    }
    v[3] = 0.0f;
    sceVu0ApplyMatrix(v, (char *)*(int *)(*(char **)(self + 0x15C) + 0xC) + n, v);
    sceVu0SubVector(d, a2, pos);
    if (0.8f < (v[1] < 0.0f ? -v[1] : v[1])) {
        v[0] = test_CURRENTORIENT(self)[0];
        v[1] = test_CURRENTORIENT(self)[1];
        v[2] = test_CURRENTORIENT(self)[2];
    }
    if ((int)a3 / 2 < (_RotyGV(v, d) < 0 ? -_RotyGV(v, d) : _RotyGV(v, d))) {
        return 0;
    }
    return 1;
}

/* One table: a 100-entry object list, two parallel per-entry int arrays
   (the full view result and the simple one), the entry count and the
   round-robin cursor the loop below advances one entry per frame. */
typedef struct {
    char *obj[100];  /* 0x000 */
    int view[100];   /* 0x190 */
    int simple[100]; /* 0x320 */
    int num;         /* 0x4B0 */
    int cur;         /* 0x4B4 */
} ActGameViewTbl;

extern ActGameViewTbl D_006C0470;
extern void GetRootPosition(void *dst, void *self);
extern int *test_CURRENTROOT(int *a0);
extern void GetSkeltonPosition(float *dst, char *obj, void *a2);
extern void RequestClipCollision(void *w);
extern void ClipWall(void *);
extern void ClipFloor(void *);

/* The view work record is reached as `self->act->view`, and the two chase
   loads are spelled as int reads: that puts them in the same alias set as the
   table's own int fields, so the `simple[i]` / `cur` stores in the later arms
   invalidate the chase and the arm re-reads it, while the record's own
   pointer slots (the clip callback, the target object, the cleared result
   pointer) leave it alone. */
void ACTGameView_Loop(char *self)
{
    float pos[4];
    int i;

    i = D_006C0470.cur;
    if (D_006C0470.simple[i] != 0) {
        GetRootPosition(pos, D_006C0470.obj[i]);
        D_006C0470.view[i] = ACTCheckView(self, D_006C0470.obj[i], pos, (void *)0x96, 300.0f);
    } else {
        D_006C0470.view[i] = 0;
    }

    switch (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800)) {
    case 0:
        if (5000.0f <
            _DistGV(test_CURRENTROOT((int *)self), test_CURRENTROOT((int *)D_006C0470.obj[i]))) {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 6;
        } else {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 1;
        }
        break;
    case 1:
        *(void (**)(void *))(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7F4) = ClipWall;
        *(char **)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7F0) = D_006C0470.obj[i];
        *(void **)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7A0) = 0;
        GetSkeltonPosition((float *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x730), self,
                           (void *)0x23);
        GetRootPosition(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x740, D_006C0470.obj[i]);
        RequestClipCollision(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x720);
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 2;
        break;
    case 2:
        if (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x720) != 0) {
            if (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7B8) != 0) {
                *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 6;
            } else {
                *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 3;
            }
        }
        break;
    case 3:
        *(void (**)(void *))(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7F4) = ClipFloor;
        *(char **)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7F0) = D_006C0470.obj[i];
        *(void **)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7A0) = 0;
        GetSkeltonPosition((float *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x730), self,
                           (void *)0x23);
        GetRootPosition(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x740, D_006C0470.obj[i]);
        RequestClipCollision(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x720);
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 4;
        break;
    case 4:
        if (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x720) != 0) {
            if (*(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x7C4) != 0) {
                *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 6;
            } else {
                *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 5;
            }
        }
        break;
    case 5:
        D_006C0470.simple[i] = 1;
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 7;
        break;
    case 6:
        D_006C0470.simple[i] = 0;
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 7;
        break;
    case 7:
        D_006C0470.cur++;
        if (!(D_006C0470.cur < D_006C0470.num)) {
            D_006C0470.cur = 0;
        }
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x688) + 0x800) = 0;
        break;
    }
}

extern void DispMultiBgaManagerWithKind(int a0, int a1, int a2);

void ACTGame_LwsEffectProcess(char *a0)
{
    int m = *(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x1B8);
    if (m != 0) {
        DispMultiBgaManagerWithKind(0x1F8, m, 1);
    }
}

extern int *test_CURRENTROOT(int *a0);
extern float _DistxzSqGV(void *a, void *b);

/* Both absolute values are MACRO-shaped: ROM re-calls test_CURRENTROOT twice
   per arm of the height test and _RotyGV once per arm of the angle test, i.e.
   the classic `((x) < 0 ? -(x) : (x))` triple evaluation. */
int _ACTGame_SearchGObj(char *self, char *tgt, float range, float height, int angle, float *out)
{
    float buf[4];
    int n;

    if (!(_DistxzSqGV(test_CURRENTROOT((int *)self), test_CURRENTROOT((int *)tgt)) <
          range * range)) {
        return 0;
    }
    if ((((float *)test_CURRENTROOT((int *)self))[1] - ((float *)test_CURRENTROOT((int *)tgt))[1] <
                 0.0f
             ? -(((float *)test_CURRENTROOT((int *)self))[1] -
                 ((float *)test_CURRENTROOT((int *)tgt))[1])
             : ((float *)test_CURRENTROOT((int *)self))[1] -
                   ((float *)test_CURRENTROOT((int *)tgt))[1]) < height) {
        sceVu0SubVector(buf, test_CURRENTROOT((int *)tgt), test_CURRENTROOT((int *)self));
        n = _RotyGV(buf, test_CURRENTORIENT(self)) < 0 ? -_RotyGV(buf, test_CURRENTORIENT(self))
                                                       : _RotyGV(buf, test_CURRENTORIENT(self));
        if (n < angle) {
            out[0] = buf[0];
            out[1] = buf[1];
            out[2] = buf[2];
            return 1;
        }
    }
    return 0;
}

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

extern void ACTGame_InnerVelocityUpdate(char *self);
extern void SetDirectMotionProgramInterpInfo(char *self, int prog, float f);
extern void ACTGame_GirlBeforeFunc(char *self);
extern char D_005577D0[];

/* One 0x50-byte record per act status, indexed by sub->0x34. */
typedef struct {
    char _00[0x4C];
    unsigned int f_4C;
} StatusAttr;

/* The motion-play-speed-ratio mode at work+0x54 is an enumerated mode, not a
   plain int: ACTGame_SetMotionPlaySpeedRatio_Exec dispatches on 0..2, and the
   ROM proves the type here -- only an enum-typed store lets the scheduler
   hoist the neighbouring +0x37C timer load past it (an `int` store aliases
   that load and pins it below). */
typedef enum { MPSR_OFF, MPSR_ONESHOT, MPSR_HOLD } MpsrMode;

/* The 64-bit actor status words are a union view in the dev's TU: the ROM
   re-reads sub+0x18 after every `int` store to the work block, which only a
   union whose members include a 32-bit integer produces -- a plain
   `unsigned long long` load survives an `int` store under TBAA. */
typedef union {
    unsigned long long q;
    unsigned int w[2];
} ActStatusWord;

extern int D_0063AA08;

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTLookTarget_Init (lines 2183-2187) and
   ACTGame_SetMotionPlaySpeedRatio_Clear (lines 2489-2490) here, so both are
   `inline` in the dev's TU; while this tail still has asm members a deferred
   inline would land at the object end instead of at its ROM slot, so the
   public bodies stay plain definitions further down and this caller uses the
   static stand-ins.  Collapse to one `inline` definition each at layout. */
static inline void actLookTarget_Init(char *a0)
{
    char *s = *(char **)(a0 + 0x164);
    *(int *)(s + 0xA8) = 0;
    *(int *)(s + 0xB0) = 0;
    *(int *)(s + 0xAC) = 0;
}

static inline void actGame_SetMotionPlaySpeedRatio_Clear(char *a0)
{
    char *p = (char *)*(int *)((char *)*(int *)(a0 + 0x164) + 0x680);
    *(float *)(p + 0x58) = 1.0f;
    *(MpsrMode *)(p + 0x54) = MPSR_OFF;
}

/* self->0x164->0x688 -- the per-actor motion work block.  Every use in this
   function re-derives the chase (the ROM reloads both links after each
   store), so it is spelled as one accessor rather than a cached local. */
#define ACTWORK(g) ((char *)*(int *)((char *)*(int *)((g) + 0x164) + 0x688))

void ACTGame_BeforeFunc(char *self)
{
    char *s = (char *)*(int *)(self + 0x164);

    *(float *)((char *)*(int *)(s + 0x688) + 0x348) = 3.0f;
    ACTGame_InnerVelocityUpdate(self);

    switch (*(unsigned int *)(s + 0x34)) {
    case 1:
    case 2:
    case 3: {
        char *p = (char *)*(int *)(self + 0x164);
        *(int *)(p + 0x1B0) = 0;
        *(char *)(p + 0x1DA) = 0;
        break;
    }
    }

    if (((int)(*(unsigned long long *)(s + 0x20) >> 40) & 1) == 0 &&
        ((int)(&D_0055FE58[*(int *)((char *)*(int *)(self + 0x15C) + 0x4A0)])->f_18C >= 0 ||
         *(int *)((char *)*(int *)(self + 0x15C) + 0x4F8) != 0)) {
        GetRootPosition(s + 0x110, self);
    }

    *(unsigned long long *)(s + 0x20) &= ~(1ULL << 41);
    *(unsigned long long *)(s + 0x20) &= ~(1ULL << 40);

    ACTParaStatus_Clear(self);
    _ACTCharStatus_Clear(self);
    actLookTarget_Init(self);

    memset(s + 0x47C, 0, 0x10);
    memset(s + 0x48C, 0, 0x10);

    actGame_SetMotionPlaySpeedRatio_Clear(self);

    if (*(int *)(ACTWORK(self) + 0x37C) > 0) {
        (*(int *)(ACTWORK(self) + 0x37C))--;
    }
    if (*(short *)(s + 0x13A) > 0) {
        (*(short *)(s + 0x13A))--;
    }
    if (*(int *)(ACTWORK(self) + 0x384) > 0) {
        (*(int *)(ACTWORK(self) + 0x384))--;
    }
    if (*(int *)(ACTWORK(self) + 0x388) > 0) {
        (*(int *)(ACTWORK(self) + 0x388))--;
    }
    if (*(int *)(ACTWORK(self) + 0x390) != 0) {
        (*(int *)(ACTWORK(self) + 0x390))--;

        switch (*(unsigned int *)(s + 0x34)) {
        case 2:
        case 3:
            break;

        default:
            *(int *)(ACTWORK(self) + 0x390) = 0;
            break;
        }
        if (D_0063AA08 != 0) {
            *(int *)(ACTWORK(self) + 0x390) = 0;
        }
    }

    if (D_00639EA8 != 0 && *(int *)((char *)*(int *)(D_00639EA8 + 0x164) + 0x34) == 0x6F &&
        *(int *)((char *)*(int *)(D_00639EA8 + 0x164) + 0x144) == (int)self &&
        ((int)(*(unsigned long long *)(s + 0x20) >> 21) & 1) == 0) {
        (*(int *)(ACTWORK(self) + 0x39C))++;
    } else {
        *(int *)(ACTWORK(self) + 0x39C) = 0;
    }

    if (*(int *)(ACTWORK(self) + 0x394) != 0) {
        (*(int *)(ACTWORK(self) + 0x394))--;
    }
    if (*(int *)(ACTWORK(self) + 0x38C) > 0) {
        (*(int *)(ACTWORK(self) + 0x38C))--;
        SetDirectMotionProgramInterpInfo(self, 0x2C, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 1, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0x22, 0.0f);
        SetDirectMotionProgramInterpInfo(self, 0x23, 0.0f);
    }
    if (*(int *)(ACTWORK(self) + 0x3A0) != 0) {
        (*(int *)(ACTWORK(self) + 0x3A0))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3A4) != 0) {
        (*(int *)(ACTWORK(self) + 0x3A4))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3AC) != 0) {
        (*(int *)(ACTWORK(self) + 0x3AC))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3B0) != 0) {
        (*(int *)(ACTWORK(self) + 0x3B0))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3B4) != 0) {
        (*(int *)(ACTWORK(self) + 0x3B4))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3C4) != 0) {
        (*(int *)(ACTWORK(self) + 0x3C4))--;
    }
    if (*(int *)(ACTWORK(self) + 0x3C8) != 0) {
        (*(int *)(ACTWORK(self) + 0x3C8))--;
    }

    if ((int)(((ActStatusWord *)(s + 0x18))->q >> 36) & 1) {
        (*(int *)(ACTWORK(self) + 0x3B8))++;
    } else {
        *(int *)(ACTWORK(self) + 0x3B8) = 0;
    }
    if ((int)(((ActStatusWord *)(s + 0x18))->q >> 37) & 1) {
        (*(int *)(ACTWORK(self) + 0x3BC))++;
    } else {
        *(int *)(ACTWORK(self) + 0x3BC) = 0;
    }

    if ((((&D_0055FE58[*(int *)((char *)*(int *)(self + 0x15C) + 0x4A0)])->f_18C >> 14) & 1) ||
        ((((StatusAttr *)(D_005577D0 + *(int *)((char *)*(int *)(self + 0x164) + 0x34) * 0x50))
              ->f_4C >>
          14) &
         1)) {
        ((ActStatusWord *)(s + 0x18))->q |= 1ULL << 38;
        if (self == D_00639EA4) {
            if (D_00639EA8 != 0) {
                *(int *)(ACTWORK(D_00639EA8) + 0x3B0) =
                    (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1];
            }
        }
    }

    if ((int)(((ActStatusWord *)(s + 0x18))->q >> 38) & 1) {
        (*(int *)(ACTWORK(self) + 0x3C0))++;
    } else {
        *(int *)(ACTWORK(self) + 0x3C0) = 0;
    }

    if (self == D_00639EA8) {
        ACTGame_GirlBeforeFunc(self);
    }

    if (*(int *)(self + 0x8) == 0xEAD) {
        if ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 2 < *(int *)(s + 0x10)) {
            if (!(D_00639EA8 != 0 &&
                  *(int *)((char *)*(int *)(D_00639EA8 + 0x164) + 0x34) == 0x6F &&
                  *(int *)((char *)*(int *)(D_00639EA8 + 0x164) + 0x144) == (int)self)) {
                *(unsigned long long *)(s + 0x20) &= ~(1ULL << 30);
            }
        }
    }
}

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
    int r;

    if (s != 0) {
        r = (*(unsigned long long *)(s + 0x58) >> bit) & 1;
        if (r != 0) {
            return 1;
        }
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

/* act-game.c:2853-2859 -- masks the 16-byte request-flag block in place. */
static inline void andRequestFlags(char *d, char *m)
{
    int i;
    for (i = 15; i >= 0; i--) {
        *d = *d & *m;
        d++;
        m++;
    }
}

void FunctionAboutClingedStatus(char *self)
{
    int buf[4];
    char *s;
    int *g;
    int clinged;
    int mode;
    int st;
    char *p;
    unsigned char cl;

    clinged = 0;
    mode = 0;
    s = *(char **)(self + 0x164);
    g = isysGObjSearchFromObjKindID_begin(4);
    while (g != 0) {
        if (self == actEnemy_GetClingTarget(g)) {
            clinged = 1;
            break;
        }
        g = isysGObjSearchFromObjKindID_next(g);
    }
    if (clinged != 0) {
        actCharStatus_Set(self, 30, 0.0f, 0);
        actParaStatus_Set(self, 37);
    }
    cl = actCharStatus_Check(self, 30);
    if (cl != 0) {
        st = *(int *)(s + 0x34);
        if (st != 0) {
            if ((unsigned int)st >= 4) {
                if (st == 15) {
                    mode = 1;
                    if (*(int *)(s + 0x4C) == 0) {
                        p = *(char **)((char *)*(int *)(self + 0x164) + 0x680);
                        *(int *)(p + 0x260) += 1;
                        if (*(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x260) >=
                            5) {
                            mode = 2;
                        }
                    }
                }
            } else {
                mode = 1;
            }
        }
    } else {
        *(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x260) = 0;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        memset(buf, 0, 0x10);
        buf[0] |= 0x1000;
        andRequestFlags(s + 0x48C, (char *)buf);
        actGame_SetMotionPlaySpeedRatio_Reserve(self, 6, 1.0f / ((float)clinged * 0.25f + 1.0f));
        break;
    case 2:
        g = isysGObjSearchFromObjKindID_begin(4);
        while (g != 0) {
            if (self == actEnemy_GetClingTarget(g)) {
                iosOmSendMail(g, 0xD6, self);
                break;
            }
            g = isysGObjSearchFromObjKindID_next(g);
        }
        *(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x260) = 0;
        break;
    }
}

/* The environment work block the actor rebuilds every frame: 464 bytes at
   +0x4B0, plus the four sub-blocks that survive the rebuild. */
typedef struct {
    long long d[0x1D0 / 8];
} EnvWork;

/* 8-aligned 16-byte and 4-aligned 32-byte sub-blocks of that work area. */
typedef struct {
    long long d[2];
} EnvPair;

typedef struct {
    float f[8];
} EnvOct;

extern MotionRec D_0055FE58[];
extern void *memset(void *a0, int a1, int a2);
extern float *test_CURRENTORIENT(char *a0);
extern void ACTGetEnvironment(char *self, void *a1, float *orient, void *a3, void *a4);
extern void ACTSetEnvAllmighty(char *self);
extern void ACTGetWish_FromPad(char *self, void *a1);
extern void FunctionAboutClingedStatus(char *self);

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTGame_CheckPriInputFrame (line 1255) here and into its own
   ROM slot, so it is `inline` in the dev's TU; while this tail still has asm
   members a deferred inline would land at the object end instead of at its ROM
   slot, so the public body below stays a plain definition and this caller uses
   the static stand-in.  Collapses to one `inline` definition at layout. */
static inline unsigned char actGame_CheckPriInputFrame(char *a0)
{
    short e;
    short s;

    e = D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)].f_184;
    if ((float)e < *(float *)(*(char **)(a0 + 0x15C) + 0x4AC) && e != -1) {
        return 1;
    }
    s = D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)].f_180;
    if (s != -1 && *(float *)(*(char **)(a0 + 0x15C) + 0x4AC) < (float)s) {
        return 1;
    }
    return 0;
}

/* OR the 16 pending-request bytes into the live request bytes. */
static inline void actEnv_OrRequestBytes(unsigned char *dst, unsigned char *src)
{
    int i;

    for (i = 15; i >= 0; i--, dst++, src++) {
        *dst |= *src;
    }
}

void ACTEnvGetTest(char *self, void *a1)
{
    EnvWork old;
    char *s = *(char **)(self + 0x164);

    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 59);
    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 60);
    *(unsigned long long *)(s + 0x18) &= ~(1ULL << 61);
    *(unsigned long long *)(s + 0x20) &= ~(1ULL << 19);
    *(unsigned long long *)(s + 0x20) &= ~(1ULL << 38);
    *(unsigned long long *)(s + 0x20) &= ~(1ULL << 39);

    switch (*(int *)(s + 0x34)) {
    case 38:
    case 107:
        *(EnvOct *)(s + 0x620) = *(EnvOct *)(*(char **)(self + 0x15C) + 0x180);
        break;

    default:
        old = *(EnvWork *)(s + 0x4B0);
        memset(s + 0x4B0, 0, sizeof(EnvWork));
        *(EnvPair *)(s + 0x5C0) = *(EnvPair *)((char *)&old + 0x110);
        *(EnvOct *)(s + 0x620) = *(EnvOct *)((char *)&old + 0x170);
        *(EnvOct *)(s + 0x660) = *(EnvOct *)((char *)&old + 0x1B0);
        *(EnvOct *)(s + 0x640) = *(EnvOct *)((char *)&old + 0x190);
        ACTGetEnvironment(self, a1, test_CURRENTORIENT(self), s + 0x47C, s + 0x4B0);
        break;

    case 10:
    case 12:
    case 14:
    case 26:
    case 36:
    case 45:
    case 46:
    case 47:
    case 48:
    case 51:
    case 52:
    case 53:
    case 54:
    case 63:
    case 64:
    case 65:
    case 66:
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 88:
    case 104:
    case 105:
    case 106:
        break;
    }

    ACTSetEnvAllmighty(self);
    ACTGetWish_FromPad(self, a1);

    if (actGame_CheckPriInputFrame(self)) {
        actEnv_OrRequestBytes((unsigned char *)(s + 0x49C), (unsigned char *)(s + 0x48C));
    } else {
        memset(s + 0x49C, 0, 0x10);
    }

    if ((int)(*(unsigned long long *)(s + 0x498) >> 39) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 39;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 44) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 44;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 45) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 45;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 50) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 50;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 51) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 51;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 52) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 52;
    }
    if ((int)(*(unsigned long long *)(s + 0x498) >> 53) & 1) {
        *(unsigned long long *)(s + 0x488) |= 1ULL << 53;
    }
    FunctionAboutClingedStatus(self);
}

extern void ACTSendMailCorrect(char *self, int mail);
extern void ActSendMail_WithAdditionalData(char *self, int mail, char *from, void *data);
extern int CheckWeaponKind();
extern int rand(void);
extern int GetMotionFrameFlag1(char *self);
extern int CompareAttribute(int attr, int mask);
extern void GetOrientOfWall(void *out, int n, void *vec);
extern void SetMotionDirection(char *self, float *dir);
extern void GetCollisCenterPositionSimple(float *dst, int a1, int a2);
extern void SwapGV(void *a, void *b);
extern float sceVu0InnerProduct(void *a, void *b);
extern void SetRootPosition(char *self, void *pos);
extern void debug_StdPrintfDummy();
extern char D_005525E8[];
extern char *D_00639EA0;

/* The actor's orient-request bitfield: three 64-bit request words at
   sub+0x478, each paired with the permission mask 16 bytes further on. */
#define ORQ(s, i) (((ActStatusWord *)((s) + 0x478))[i].q)
#define ORM(s, i) (((ActStatusWord *)((s) + 0x478))[(i) + 2].q)
#define ORBIT(w, b) ((int)((w) >> (b)) & 1)

/* INTERIM: the listing inlines GetSkeltonPosition (lines 2597-2599) into the
   two skeleton fills below.  The out-of-line copy at its own ROM slot re-derives
   `obj->p_15C->0xC` for each of the three components (the alias-set-0 union
   store kills the load through the unknown `dst` pointer); the INLINED copy
   does not, because `dst` is then a known stack slot and gcc's base
   disambiguation drops the conflict.  Our build does not reproduce that
   context-sensitivity, so the inline site carries its own stand-in with the
   base hoisted into a local -- measured: the shared re-spelled spelling costs
   8 extra words per fill here, and the hoisted spelling costs 12 words in the
   out-of-line body.  Collapses to one `inline` definition at layout. */
static inline void getSkeltonPositionInline(float *dst, char *obj, void *a2)
{
    char *p =
        (char *)((GetSkeltonFocusNode(obj, a2) << 6) + *(int *)((int)((GObj *)(obj))->p_15C + 0xC));
    ((IntFloat *)dst)[0].f = *(float *)(p + 0x30);
    ((IntFloat *)dst)[1].f = *(float *)(p + 0x34);
    ((IntFloat *)dst)[2].f = *(float *)(p + 0x38);
}

/* INTERIM (see the GetSkeltonFocusNode note in src/motionManager2.c): the
   listing inlines ACTGame_NoWeapon (lines 2122-2123) here, so it is `inline`
   in the dev's TU; while this tail still has asm members a deferred inline
   would land at the object end instead of at its ROM slot, so the public body
   below stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline unsigned char actGame_NoWeapon(char *a0)
{
    char *w = *(char **)(*(char **)(a0 + 0x164) + 0x150);
    unsigned char r = 0;
    if (w == 0 || CheckWeaponKind(w) == 0)
        r = 1;
    return r;
}

void ActOrientTest(char *self)
{
    float v0[4];
    HandWork w1;
    float p1[4];
    float sk1[4];
    float sk2[4];
    float d1[4];
    HandWork w2;
    float p2[4];
    float d2[4];
    float c1[4];
    HandWork w3;
    float sk3[4];
    float sk4[4];
    float d3[4];
    float ow[4];
    char *s = *(char **)(self + 0x164);
    char *vel;
    int hitA;
    int hitB;
    int near;
    int i;

    if (ORBIT(ORQ(s, 0), 39) && ORBIT(ORM(s, 0), 39)) {
        ACTSendMailCorrect(self, 189);
    }
    if (ORBIT(ORQ(s, 0), 40) && ORBIT(ORM(s, 0), 40)) {
        ACTSendMailCorrect(self, 191);
    }
    if (ORBIT(ORQ(s, 0), 41) && ORBIT(ORM(s, 0), 41)) {
        ACTSendMailCorrect(self, 192);
    }
    if (ORBIT(ORQ(s, 0), 42) && ORBIT(ORM(s, 0), 42)) {
        ACTSendMailCorrect(self, 193);
    }
    if (ORBIT(ORQ(s, 0), 43) && ORBIT(ORM(s, 0), 43)) {
        ACTSendMailCorrect(self, 197);
    }
    if (ORBIT(ORQ(s, 0), 44) && ORBIT(ORM(s, 0), 44)) {
        if (*(int *)(self + 0xC) == 4) {
            if (rand() & 1) {
                ACTSendMailCorrect(self, 205);
            } else {
                ACTSendMailCorrect(self, 207);
            }
        } else {
            ACTSendMailCorrect(self, 205);
        }
    }
    if (ORBIT(ORQ(s, 0), 45) && ORBIT(ORM(s, 0), 45)) {
        ACTSendMailCorrect(self, 206);
    }
    if (ORBIT(ORQ(s, 0), 51) && ORBIT(ORM(s, 0), 51)) {
        ACTSendMailCorrect(self, 279);
    }
    if (self != D_00639EA4) {
        if (ORBIT(ORQ(s, 0), 50) && ORBIT(ORM(s, 0), 50)) {
            ACTSendMailCorrect(self, 278);
        }
        if (ORBIT(ORQ(s, 0), 52) && ORBIT(ORM(s, 0), 52)) {
            ACTSendMailCorrect(self, 280);
        }
        if (ORBIT(ORQ(s, 0), 53) && ORBIT(ORM(s, 0), 53)) {
            ACTSendMailCorrect(self, 281);
        }
    }
    if (ORBIT(ORQ(s, 0), 55) && ORBIT(ORM(s, 0), 55)) {
        ACTSendMailCorrect(self, 203);
    }
    if (ORBIT(ORQ(s, 0), 54) && ORBIT(ORM(s, 0), 54)) {
        if (actGame_NoWeapon(self)) {
            ACTSendMailCorrect(self, 202);
        } else {
            ACTSendMailCorrect(self, 201);
        }
    }
    if (ORBIT(ORQ(s, 0), 56) && ORBIT(ORM(s, 0), 56)) {
        ACTSendMailCorrect(self, 348);
    }
    if (ORBIT(ORQ(s, 0), 58) && ORBIT(ORM(s, 0), 58)) {
        ACTSendMailCorrect(self, 345);
    }
    if (ORBIT(ORQ(s, 0), 57) && ORBIT(ORM(s, 0), 57)) {
        ACTSendMailCorrect(self, 346);
    }
    if (ORBIT(ORQ(s, 0), 59) && ORBIT(ORM(s, 0), 59)) {
        ACTSendMailCorrect(self, 378);
    }
    if (ORBIT(ORQ(s, 0), 62) && ORBIT(ORM(s, 0), 62)) {
        ACTSendMailCorrect(self, 209);
    }
    if (ORBIT(ORQ(s, 0), 63) && ORBIT(ORM(s, 0), 63)) {
        ACTSendMailCorrect(self, 210);
    }
    if (ORBIT(ORQ(s, 1), 0) && ORBIT(ORM(s, 1), 0)) {
        ACTSendMailCorrect(self, 212);
    }
    if (ORBIT(ORQ(s, 1), 1) && ORBIT(ORM(s, 1), 1)) {
        ACTSendMailCorrect(self, 213);
    }
    if (ORBIT(ORQ(s, 1), 2) && ORBIT(ORM(s, 1), 2)) {
        ActSendMail_WithAdditionalData(self, 263, self, ACTWORK(self) + 2064);
    }
    if (ORBIT(ORQ(s, 1), 3) && ORBIT(ORM(s, 1), 3)) {
        ActSendMail_WithAdditionalData(self, 264, self, ACTWORK(self) + 2112);
    }
    if (ORBIT(ORQ(s, 1), 4) && ORBIT(ORM(s, 1), 4)) {
        ActSendMail_WithAdditionalData(self, 265, self, ACTWORK(self) + 2160);
    }
    if (ORBIT(ORQ(s, 0), 60) && ORBIT(ORM(s, 0), 60)) {
        ACTSendMailCorrect(self, 174);
        ACTSendMailCorrect(self, 173);
    }
    if (ORBIT(ORQ(s, 0), 61) && ORBIT(ORM(s, 0), 61)) {
        ACTSendMailCorrect(self, 166);
    }
    if (ORBIT(ORQ(s, 1), 11) && ORBIT(ORM(s, 1), 11)) {
        ACTSendMailCorrect(self, 216);
        debug_StdPrintfDummy(D_005525E8);
    } else if (*(int *)(s + 0x34) == 43) {
        ACTSendMailCorrect(self, 217);
    }
    if (ORBIT(ORQ(s, 1), 12) && ORBIT(ORM(s, 1), 12)) {
        ACTSendMailCorrect(self, 218);
    }
    if (ORBIT(ORQ(s, 1), 13) && ORBIT(ORM(s, 1), 13)) {
        ACTSendMailCorrect(self, 219);
    }
    if (ORBIT(ORQ(s, 1), 14) && ORBIT(ORM(s, 1), 14)) {
        ACTSendMailCorrect(self, 220);
    }
    if (ORBIT(ORQ(s, 1), 15) && ORBIT(ORM(s, 1), 15)) {
        ACTSendMailCorrect(self, 223);
    }
    if (ORBIT(ORQ(s, 1), 16) && ORBIT(ORM(s, 1), 16)) {
        ACTSendMailCorrect(self, 224);
    }
    if (ORBIT(ORQ(s, 1), 17) && ORBIT(ORM(s, 1), 17)) {
        ACTSendMailCorrect(self, 225);
    }
    if (ORBIT(ORQ(s, 1), 36) && ORBIT(ORM(s, 1), 36)) {
        ACTSendMailCorrect(self, 121);
    }
    if (ORBIT(ORQ(s, 1), 38) && ORBIT(ORM(s, 1), 38)) {
        ACTSendMailCorrect(self, 122);
    }
    if (ORBIT(ORQ(s, 1), 40) && ORBIT(ORM(s, 1), 40)) {
        ACTSendMailCorrect(self, 130);
    }
    if (ORBIT(ORQ(s, 1), 39) && ORBIT(ORM(s, 1), 39)) {
        ACTSendMailCorrect(self, 127);
    }
    if (ORBIT(ORQ(s, 1), 41) && ORBIT(ORM(s, 1), 41)) {
        ACTSendMailCorrect(self, 131);
    }
    if (ORBIT(ORQ(s, 1), 42) && ORBIT(ORM(s, 1), 42)) {
        ACTSendMailCorrect(self, 132);
    }
    if (ORBIT(ORQ(s, 1), 43) && ORBIT(ORM(s, 1), 43)) {
        ACTSendMailCorrect(self, 123);
    }
    if (ORBIT(ORQ(s, 1), 44) && ORBIT(ORM(s, 1), 44)) {
        ACTSendMailCorrect(self, 124);
        ACTSendMailCorrect(self, 125);
    }
    if (ORBIT(ORQ(s, 1), 33) && ORBIT(ORM(s, 1), 33)) {
        ACTSendMailCorrect(self, 118);
    }
    if (ORBIT(ORQ(s, 1), 34) && ORBIT(ORM(s, 1), 34)) {
        ACTSendMailCorrect(self, 119);
    }
    if (ORBIT(ORQ(s, 1), 35) && ORBIT(ORM(s, 1), 35)) {
        ACTSendMailCorrect(self, 120);
    }
    if (ORBIT(ORQ(s, 1), 5) && ORBIT(ORM(s, 1), 5)) {
        if (self == D_00639EA8) {
            int ok = 0;
            if (D_00639EA0 != 0) {
                ok = 1;
            }
            if (*(int *)((char *)*(int *)(self + 0x164) + 0x34) == 0x75) {
                ok = 1;
            }
            if (ok) {
                ACTSendMailCorrect(self, 114);
            }
        } else {
            ACTSendMailCorrect(self, 114);
        }
    }
    if (ORBIT(ORQ(s, 1), 6) && ORBIT(ORM(s, 1), 6)) {
        ACTSendMailCorrect(self, 324);
    }
    if (ORBIT(ORQ(s, 1), 8) && ORBIT(ORM(s, 1), 8)) {
        ACTSendMailCorrect(self, 325);
    }
    if (ORBIT(ORQ(s, 1), 7) && ORBIT(ORM(s, 1), 7)) {
        ACTSendMailCorrect(self, 326);
    }
    if (ORBIT(ORQ(s, 1), 9) && ORBIT(ORM(s, 1), 9)) {
        ACTSendMailCorrect(self, 328);
    }
    if (ORBIT(ORQ(s, 1), 18) && ORBIT(ORM(s, 1), 18)) {
        ACTSendMailCorrect(self, 317);
    }
    if (ORBIT(ORQ(s, 1), 19) && ORBIT(ORM(s, 1), 19)) {
        ACTSendMailCorrect(self, 318);
    }
    if (ORBIT(ORQ(s, 1), 20) && ORBIT(ORM(s, 1), 20)) {
        ACTSendMailCorrect(self, 319);
    }
    if (ORBIT(ORQ(s, 1), 22) && ORBIT(ORM(s, 1), 22)) {
        ACTSendMailCorrect(self, 320);
    }
    if (ORBIT(ORQ(s, 1), 23) && ORBIT(ORM(s, 1), 23)) {
        ACTSendMailCorrect(self, 320);
    }
    if (ORBIT(ORQ(s, 1), 27) && ORBIT(ORM(s, 1), 27)) {
        ACTSendMailCorrect(self, 317);
    }
    if (ORBIT(ORQ(s, 1), 28) && ORBIT(ORM(s, 1), 28)) {
        ACTSendMailCorrect(self, 318);
    }
    if (ORBIT(ORQ(s, 1), 29) && ORBIT(ORM(s, 1), 29)) {
        ACTSendMailCorrect(self, 319);
    }
    if (ORBIT(ORQ(s, 1), 55) && ORBIT(ORM(s, 1), 55)) {
        ACTSendMailCorrect(self, 42);
    }
    if (ORBIT(ORQ(s, 1), 56) && ORBIT(ORM(s, 1), 56)) {
        ACTSendMailCorrect(self, 41);
    }
    if (ORBIT(ORQ(s, 1), 57) && ORBIT(ORM(s, 1), 57)) {
        ACTSendMailCorrect(self, 135);
    }
    if (ORBIT(ORQ(s, 1), 58) && ORBIT(ORM(s, 1), 58)) {
        ACTSendMailCorrect(self, 136);
    }
    if (ORBIT(ORQ(s, 1), 63) && ORBIT(ORM(s, 1), 63)) {
        ACTSendMailCorrect(self, 297);
    }
    if (ORBIT(ORQ(s, 2), 0) && ORBIT(ORM(s, 2), 0)) {
        ACTSendMailCorrect(self, 299);
    }
    if ((ORBIT(ORQ(s, 2), 1) && ORBIT(ORM(s, 2), 1)) ||
        (ORBIT(ORQ(s, 2), 2) && ORBIT(ORM(s, 2), 2))) {
        ACTSendMailCorrect(self, 295);
    }
    if (ORBIT(ORQ(s, 1), 53) && ORBIT(ORM(s, 1), 53)) {
        ACTSendMailCorrect(self, 301);
    }
    if (ORBIT(ORQ(s, 1), 54) && ORBIT(ORM(s, 1), 54)) {
        ACTSendMailCorrect(self, 146);
    }
    if (ORBIT(ORQ(s, 1), 45) && ORBIT(ORM(s, 1), 45)) {
        ACTSendMailCorrect(self, 295);
    }
    if (ORBIT(ORQ(s, 1), 46) && ORBIT(ORM(s, 1), 46)) {
        ACTSendMailCorrect(self, 300);
    }
    if (ORBIT(ORQ(s, 1), 47) && ORBIT(ORM(s, 1), 47)) {
        ACTSendMailCorrect(self, 306);
        if (stage_no == 32) {
            ACTSendMailCorrect(self, 308);
        }
    }
    if (ORBIT(ORQ(s, 1), 48) && ORBIT(ORM(s, 1), 48)) {
        ACTSendMailCorrect(self, 307);
    }
    if (ORBIT(ORQ(s, 1), 50) && ORBIT(ORM(s, 1), 50)) {
        ACTSendMailCorrect(self, 310);
    }
    if (ORBIT(ORQ(s, 1), 51) && ORBIT(ORM(s, 1), 51)) {
        ACTSendMailCorrect(self, 311);
    }
    if (ORBIT(ORQ(s, 1), 49) && ORBIT(ORM(s, 1), 49)) {
        ACTSendMailCorrect(self, 309);
    }
    if (ORBIT(ORQ(s, 1), 52) && ORBIT(ORM(s, 1), 52)) {
        ACTSendMailCorrect(self, 312);
    }
    if (ORBIT(ORQ(s, 2), 10) && ORBIT(ORM(s, 2), 10)) {
        ACTSendMailCorrect(self, 90);
    }
    if (ORBIT(ORQ(s, 2), 11) && ORBIT(ORM(s, 2), 11)) {
        ACTSendMailCorrect(self, 91);
    }
    if (ORBIT(ORQ(s, 2), 12) && ORBIT(ORM(s, 2), 12)) {
        (*(int *)(ACTWORK(self) + 0x3A8))++;
    } else {
        *(int *)(ACTWORK(self) + 0x3A8) = 0;
    }
    if (ORBIT(ORQ(s, 2), 7) && ORBIT(ORM(s, 2), 7)) {
        ACTSendMailCorrect(self, 72);
        *(int *)(s + 0x44) = 106;
    }
    if (ORBIT(ORQ(s, 2), 8) && ORBIT(ORM(s, 2), 8)) {
        ACTSendMailCorrect(self, 72);
        *(int *)(s + 0x44) = 108;
    }
    if (ORBIT(ORQ(s, 2), 9) && ORBIT(ORM(s, 2), 9)) {
        ACTSendMailCorrect(self, 72);
        *(int *)(s + 0x44) = 110;
    }
    if (ORBIT(ORQ(s, 1), 24) && ORBIT(ORM(s, 1), 24)) {
        ACTSendMailCorrect(self, 321);
    }
    if (ORBIT(ORQ(s, 1), 25) && ORBIT(ORM(s, 1), 25)) {
        ACTSendMailCorrect(self, 322);
    }
    if (ORBIT(ORQ(s, 1), 26) && ORBIT(ORM(s, 1), 26)) {
        ACTSendMailCorrect(self, 323);
    }
    if (ORBIT(ORQ(s, 1), 62) && ORBIT(ORM(s, 1), 62)) {
        ACTSendMailCorrect(self, 165);
    }
    if (ORBIT(ORQ(s, 2), 13) && ORBIT(ORM(s, 2), 13)) {
        ACTSendMailCorrect(self, 392);
    }
    if (ORBIT(ORQ(s, 2), 14) && ORBIT(ORM(s, 2), 14)) {
        vel = s + 0x4C0;
        sceVu0ScaleVector(v0, vel,
                          -sceVu0InnerProduct((char *)*(int *)(self + 0x15C) + 0x130, vel));
        sceVu0AddVector((char *)*(int *)(self + 0x15C) + 0x130,
                        (char *)*(int *)(self + 0x15C) + 0x130, v0);
        SetRootPosition(self, s + 0x540);
    }
    if (*(int *)(*(char **)((char *)*(int *)(self + 0x164) + 0x680) + 0x29C) > 0) {
        ACTSendMailCorrect(self, 111);
    }
    if (((&D_0055FE58[*(int *)((char *)*(int *)(self + 0x15C) + 0x4A0)])->f_190 >> 2) & 1) {
        if (GetMotionFrameFlag1(self)) {
            memset(&w1, 0, 0xC0);
            getSkeltonPositionInline(sk1, self, (void *)0x33);
            getSkeltonPositionInline(sk2, self, (void *)0x2F);
            sceVu0AddVector(p1, sk1, sk2);
            sceVu0ScaleVector(p1, p1, 0.5f);
            p1[1] = p1[1] + 50.0f;
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), 50.0f);
            sceVu0AddVector(&w1, p1, d1);
            sceVu0ScaleVector(d1, test_CURRENTORIENT(self), -50.0f);
            sceVu0AddVector((char *)&w1 + 0x10, p1, d1);
            w1._70 = 0.0f;
            ClipWall(&w1);
            if (CompareAttribute(w1._98, 0x2000)) {
                ACTSendMailCorrect(self, 327);
            }
            if (CompareAttribute(w1._98, 0x20000)) {
                if (*(int *)(s + 0x68C) != 0) {
                    if (GetMotionFrameFlag1(self)) {
                        char *ext;
                        *(U64ag *)*(int *)(s + 0x68C) = *(U64ag *)((char *)&w1 + 0x80);
                        ext = (char *)*(int *)(s + 0x68C);
                        *(int *)(ext + 8) = *(int *)((char *)&w1 + 0x88);
                        ActSendMail_WithAdditionalData(self, 298, self, ext);
                    }
                }
            }
        }
    }
    if (((&D_0055FE58[*(int *)((char *)*(int *)(self + 0x15C) + 0x4A0)])->f_190 >> 3) & 1) {
        memset(&w2, 0, 0xC0);
        near = 0;
        p2[0] = ((float *)test_CURRENTROOT((int *)self))[0];
        p2[1] = ((float *)test_CURRENTROOT((int *)self))[1];
        p2[2] = ((float *)test_CURRENTROOT((int *)self))[2];
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), -50.0f);
        sceVu0AddVector(&w2, p2, d2);
        sceVu0ScaleVector(d2, test_CURRENTORIENT(self), 50.0f);
        sceVu0AddVector((char *)&w2 + 0x10, p2, d2);
        hitA = 0;
        w2._70 = 0.0f;
        ClipWall(&w2);
        hitB = 0;
        if (CompareAttribute(w2._98, 0x400)) {
            hitA = 1;
        }
        if (CompareAttribute(w2._98, 0xC000)) {
            hitB = 1;
        }
        if (hitA || hitB) {
            GetCollisCenterPositionSimple(c1, w2._80, w2._88);
            if (_DistxzSqGV(c1, test_CURRENTROOT((int *)self)) < 400.0f) {
                near = 1;
            }
        }
        if (hitA && near) {
            ACTSendMailCorrect(self, 139);
        }
        if (hitB && near) {
            ACTSendMailCorrect(self, 310);
        }
    }
    if (*(int *)(s + 0xD8) == 313) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (((int)(*(unsigned long long *)(s + 0x20) >> 42) & 1) == 0) {
            continue;
        }
        memset(&w3, 0, 0xC0);
        getSkeltonPositionInline(sk3, self, (void *)0x33);
        getSkeltonPositionInline(sk4, self, (void *)0x2F);
        sceVu0AddVector(c1, sk3, sk4);
        sceVu0ScaleVector(c1, c1, 0.5f);
        c1[1] = c1[1] + 50.0f;
        sceVu0ScaleVector(d3, test_CURRENTORIENT(self), 50.0f);
        _ApplyRyGV(d3, -1.5707964f);
        sceVu0AddVector(&w3, c1, d3);
        sceVu0ScaleVector(d3, test_CURRENTORIENT(self), 50.0f);
        _ApplyRyGV(d3, 1.5707964f);
        sceVu0AddVector((char *)&w3 + 0x10, c1, d3);
        if (i == 1) {
            SwapGV(&w3, (char *)&w3 + 0x10);
        }
        w3._70 = 0.0f;
        ClipWall(&w3);
        if (w3._88 != 0) {
            GetOrientOfWall(ow, w3._88, &w3._80);
            SetMotionDirection(self, ow);
            *(unsigned long long *)(s + 0x20) &= ~(1ULL << 42);
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act-game", GetGirlHandlinkClInfo);
ASM_LIT4_SLOT(D_00638CE0, 12100.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", hand_able_connect);
ASM_LIT4_SLOT(D_00638CE4, 10000.0f);
INCLUDE_ASM("asm/nonmatchings/src/act-game", ACTGame_CommonLoop);
ASM_LIT4_SLOT(D_00638CE8, 160000.0f);

extern char *D_00639EA4;
extern char *D_00639EA8;
extern int stage_no;
extern int GetSkeltonFocusNode(void *a0, void *a1);
extern float *test_CURRENTORIENT(char *a0);
extern int *test_CURRENTROOT(int *a0);
extern void GetRootPosition(void *dst, void *self);
extern void ScpCallCameraGetTarget(float *dst);
extern void debug_NMarker(float *pos, int r, int g, int b, float size);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern int gamesysGetGirlStageIDAndPosition(int *buf);
extern void OtherStagePositionGet(float *dst, int stage, int id, int *buf);

/* INTERIM: the same stand-in as getGirlPositionAtThisStage further down this
   file (the listing inlines GetGirlPositionAtThisStage, lines 4063-4067, into
   GetTarget as well).  Its public definition sits at its own ROM slot below
   this one, so a copy has to be in scope here; collapses to one `inline`
   definition at layout. */
static inline void getGirlPosAtThisStage(float *dst)
{
    int buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(dst, stage_no, id, buf);
}

/* The look-target candidate table: 27 rows, one column per character kind
   (self->_164->_48). */
extern int D_0055FD10[][3];

void ACTLookTargetSystem_Exec(char *self)
{
    char *s = (char *)((int *)self)[89];

    /* GNU nested function: the listing names it GetTarget.374 and passes
       ACTLookTargetSystem_Exec's frame as the static chain, from which it
       reads `self` and `s`. */
    int GetTarget(int kind, float *pos, int *pmode)
    {
        float dir[4];
        float p[4];
        char *target = 0;
        int rv = 0;

        switch (kind) {
        case 13:
            getSkeltonPosition(p, self, (void *)0x23);
            sceVu0ScaleVector(dir, (char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x4A0,
                              300.0f);
            sceVu0AddVector(pos, p, dir);
            *(float *)((char *)*(int *)(self + 0x15C) + 0x45C) = 0.3f;
            *(float *)((char *)*(int *)(self + 0x15C) + 0x464) = 0.3f;
            *(float *)((char *)*(int *)(self + 0x15C) + 0x468) = 0.3f;
            rv = 1;
            break;
        case 12:
            target = *(char **)(s + 0x88);
            break;
        case 10:
            target = *(char **)(s + 0x78);
            break;
        case 5:
            target = *(char **)(s + 0x7C);
            break;
        case 4:
            target = D_00639EA8;
            if (target == 0 && (*(unsigned long long *)(s + 0x20) & 0x3800000) == 0x800000) {
                getGirlPosAtThisStage(pos);
                rv = 1;
            }
            if ((int)(*(unsigned long long *)(s + 0x20) >> 24) & 3) {
                ScpCallCameraGetTarget(pos);
                target = 0;
                rv = 1;
            }
            break;
        case 11:
            GetRootPosition(pos, *(char **)(s + 0x74));
            pos[1] = *(float *)&test_CURRENTROOT((int *)self)[1];
            *pmode = 2;
            rv = 1;
            break;
        case 6:
            if ((int)(*(unsigned long long *)(s + 0x20) >> 23) & 1) {
                target = D_00639EA8;
                *pmode = 2;
                if (target == 0) {
                    getGirlPosAtThisStage(pos);
                    rv = 1;
                }
            }
            if ((int)(*(unsigned long long *)(s + 0x20) >> 24) & 3) {
                ScpCallCameraGetTarget(pos);
                target = 0;
                rv = 1;
            }
            break;
        case 8:
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(char **)(s + 0x80);
            } else {
                target = D_00639EA4;
            }
            break;
        case 9:
            target = *(char **)(s + 0x84);
            break;
        case 7:
            target = D_00639EA4;
            if (*(int *)(s + 0x10) % 15 / 10 != 0) {
                target = *(char **)(s + 0x80);
            }
            break;
        case 3:
            target = D_00639EA4;
            break;
        case 1:
            sceVu0ScaleVector(pos, test_CURRENTORIENT(self), 200.0f);
            pos[1] = 0.0f;
            sceVu0AddVector(pos, test_CURRENTROOT((int *)self), pos);
            rv = 1;
            break;
        case 2:
            sceVu0ScaleVector(pos, test_CURRENTORIENT(self), *(float *)(s + 0x5E8));
            pos[1] = 150.0f;
            sceVu0AddVector(pos, test_CURRENTROOT((int *)self), pos);
            rv = 1;
            break;
        case 14:
            pos[0] = *(float *)((char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x520);
            pos[1] = *(float *)((char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x524);
            pos[2] = *(float *)((char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x528);
            rv = 1;
            break;
        }
        if (target != 0) {
            if (target == D_00639EA4) {
                /* the listing writes these two statements out at act-game.c
                   4202-4203 instead of calling GetSkeltonPosition, so the
                   node comes off `target` and the skeleton off the global. */
                int idx = GetSkeltonFocusNode(target, (void *)0x23) << 6;
                ((IntFloat *)pos)[0].f =
                    *(float *)(idx + *(int *)((int)((GObj *)D_00639EA4)->p_15C + 0xC) + 0x30);
                ((IntFloat *)pos)[1].f =
                    *(float *)(idx + *(int *)((int)((GObj *)D_00639EA4)->p_15C + 0xC) + 0x34);
                ((IntFloat *)pos)[2].f =
                    *(float *)(idx + *(int *)((int)((GObj *)D_00639EA4)->p_15C + 0xC) + 0x38);
            } else {
                GetRootPosition(pos, target);
            }
            rv = 1;
        }
        return rv;
    }

    float pos[4];
    int mode = 1;
    int found = 0;
    int col = ((int *)s)[18];
    int flags;
    int i;

    flags = 0;
    if (actCharStatus_Check(self, 32)) {
        flags = 1;
    }
    if (actCharStatus_Check(self, 13)) {
        flags |= 0x10;
    }
    if (actCharStatus_Check(self, 14)) {
        flags |= 0x20;
    }
    if (actCharStatus_Check(self, 28)) {
        if (*(float *)((char *)*(int *)((char *)*(int *)(self + 0x164) + 0x688) + 0x32C) < 300.0f) {
            flags |= 0x40;
        } else {
            flags |= 0x800;
        }
    }
    if (actCharStatus_Check(self, 10)) {
        flags |= 0x800000;
    }
    if (actCharStatus_Check(self, 11)) {
        flags |= 0x1000;
    }
    if (actCharStatus_Check(self, 15)) {
        if (self == D_00639EA8) {
            if ((int)(*(unsigned long long *)(s + 0x20) >> 14) & 1) {
                flags |= 0x200;
            }
        } else {
            flags |= 0x200;
        }
    }
    if (actCharStatus_Check(self, 5)) {
        flags |= 0x20000;
    }
    if (actCharStatus_Check(self, 25)) {
        flags |= 0x400;
    }
    if (actCharStatus_Check(self, 26)) {
        flags |= 0x100;
    }
    if (actCharStatus_Check(self, 31)) {
        flags |= 0x2000;
    }
    if (actCharStatus_Check(self, 3)) {
        flags |= 0x8000;
    }
    if (actCharStatus_Check(self, 2)) {
        flags |= 0x4000;
    }
    if (actCharStatus_Check(self, 6)) {
        flags |= 0x40000;
    }
    if (actCharStatus_Check(self, 7)) {
        flags |= 0x80000;
    }
    if (actCharStatus_Check(self, 33)) {
        flags |= 0x2;
    }
    if (actCharStatus_Check(self, 34)) {
        flags |= 0x4;
    }
    if (actCharStatus_Check(self, 35)) {
        flags |= 0x8;
    }
    if (actCharStatus_Check(self, 4)) {
        flags |= 0x10000;
    }
    if (actCharStatus_Check(self, 27)) {
        flags |= 0x4000000;
    }
    if (actCharStatus_Check(self, 18)) {
        flags |= 0x80;
    }
    if (actCharStatus_Check(self, 12)) {
        flags |= 0x100000;
    }
    if (actCharStatus_Check(self, 0)) {
        flags |= 0x200000;
    }
    if (actCharStatus_Check(self, 1)) {
        flags |= 0x400000;
    }
    if (actCharStatus_Check(self, 17)) {
        if (*(float *)(s + 0x70) < 1000.0f) {
            flags |= 0x1000000;
        }
        if (*(float *)(s + 0x70) < 300.0f) {
            flags |= 0x2000000;
        }
    }
    for (i = 0; i < 27; i++) {
        int kind = D_0055FD10[i][col];
        if ((flags >> i) & 1) {
            if (GetTarget(kind, pos, &mode) != 0) {
                found = 1;
                break;
            }
        }
    }
    if (found != 0) {
        *(float *)((char *)((IntFloat *)(self + 0x15C))->i + 0x390) = pos[0];
        *(float *)((char *)((IntFloat *)(self + 0x15C))->i + 0x394) = pos[1];
        *(float *)((char *)((IntFloat *)(self + 0x15C))->i + 0x398) = pos[2];
        *(int *)((char *)((IntFloat *)(self + 0x15C))->i + 0x380) = mode;
        if (self == D_00639EA8) {
            debug_NMarker((float *)((char *)*(int *)(self + 0x15C) + 0x390), 0xFF, 0xFF, 0xFF,
                          100.0f);
        }
    } else {
        *(int *)((char *)*(int *)(self + 0x15C) + 0x380) = 0;
    }
}

extern char D_0063A6A0[];
extern char D_0063A6A8[];
extern float D_002ADAF0[];
extern void sceVu0ScaleVector(void *dst, void *src, float k);
extern int GetItemKind(int item);
extern void ThrowItem(int item, float *v);
extern void HoldItem(int item, char *self);
extern void ReleaseItem(int item);
extern void ACTSendMailCorrect(char *self, int mail);
extern void SetBoyInfo(int *a0, int *a1);
extern void GetRootPosition(void *dst, void *obj);
extern void SetDirectRootPositionNoFittingWithNodePoint(void *a0, void *a1, void *a2, float a3);
extern char *D_00639EA4;
extern char *D_00639EA8;
extern int D_00639EBC;

/* INTERIM: the listing inlines _ACTGame_GetParamF (act-game.c:4375) into
   ACTItemThrow and keeps it at its own ROM slot, so it is `inline` in the
   dev's TU; while this tail still has asm members a deferred inline would
   land at the object end instead of at its ROM slot, so the public body
   above stays a plain definition and this caller uses the static stand-in.
   Collapses to one `inline` definition at layout. */
static inline float actGame_GetParamF(int idx)
{
    return D_002ADAF0[idx];
}

void ACTItemWatchMotion(char *self)
{
    MotionRec *rec = &D_0055FE58[*(int *)((char *)*(int *)(self + 0x15C) + 0x4A0)];
    char *sub = (char *)*(int *)(self + 0x164);
    int mode = rec->u_188.w >> 19;
    int frame = rec->u_188.b;

    /* Nested inline (dev lines 4456-4464): the "take the pending item"
       request, expanded at the four motion arms below. */
    inline void ItemHold(void)
    {
        if (*(int *)(sub + 0x180) != 0) {
            return;
        }
        if ((*(int *)(sub + 0x180) = *(int *)(sub + 0x184)) == 0) {
            return;
        }
        HoldItem(*(int *)(sub + 0x180), self);
    }

    /* Nested inline (dev lines 4474-4476): drop whatever is held.  The two
       slots hold the held / pending item object POINTERS (the same values the
       head block above compares against the other actor's pair), so they are
       read and cleared through `char **`. */
    inline void ItemRelease(void)
    {
        if (*(char **)(sub + 0x180) == 0) {
            return;
        }
        ReleaseItem((int)*(char **)(sub + 0x180));
        *(char **)(sub + 0x184) = *(char **)(sub + 0x180) = 0;
    }

    /* A real GNU nested function: ROM passes the parent's frame in $2
       (STATIC_CHAIN_REGNUM) and the body reads `sub` at 0($2) and `self`
       at 4($2) through it. */
    void ACTItemThrow(void)
    {
        float v[4];
        int kind;

        if (*(int *)(sub + 0x180) == 0) {
            return;
        }
        sceVu0ScaleVector(v, test_CURRENTORIENT(self), actGame_GetParamF(9) + actGame_GetParamF(9));
        kind = GetItemKind(*(int *)(sub + 0x180));
        if (kind == 1 || kind == 6) {
            debug_StdPrintfDummy(D_0063A6A0);
            v[0] *= 0.5f;
            v[1] -= 25.0f;
            v[2] *= 0.5f;
        }
        ThrowItem(*(int *)(sub + 0x180), v);
        *(int *)(sub + 0x184) = *(int *)(sub + 0x180) = 0;
    }

    mode &= 7;

    if (self == D_00639EA8 && D_00639EA4 != 0) {
        if (*(char **)(sub + 0x184) != 0) {
            char *o = *(char **)(D_00639EA4 + 0x164);
            if (*(char **)(sub + 0x184) == *(char **)(o + 0x184) ||
                *(char **)(sub + 0x184) == *(char **)(o + 0x180)) {
                *(char **)(sub + 0x184) = 0;
            }
        }
        if (*(char **)(sub + 0x180) != 0) {
            char *o = *(char **)(D_00639EA4 + 0x164);
            if (*(char **)(sub + 0x180) == *(char **)(o + 0x184) ||
                *(char **)(sub + 0x180) == *(char **)(o + 0x180)) {
                *(char **)(sub + 0x180) = 0;
            }
        }
    }

    switch (mode) {
    case 2:
        if ((float)frame < *(float *)(*(char **)(self + 0x15C) + 0x4AC)) {
            ItemHold();
        } else if (*(int *)(sub + 0x180) != 0) {
            float pos[4];
            GetRootPosition(pos, *(int *)(sub + 0x180));
            SetDirectRootPositionNoFittingWithNodePoint(self, (void *)0x16, pos, 0.2f);
            debug_StdPrintfDummy(D_0063A6A8);
        }
        break;

    case 4:
        if (*(float *)(*(char **)(self + 0x15C) + 0x4AC) < (float)frame) {
            ItemHold();
        } else {
            ItemRelease();
        }
        break;

    case 3:
        if (*(float *)(*(char **)(self + 0x15C) + 0x4AC) < (float)frame) {
            ItemHold();
        } else {
            ACTItemThrow();
        }
        break;

    case 1:
        ItemHold();
        break;

    case 0:
        ItemRelease();
        break;
    }

    if (self == D_00639EA4 && D_00639EBC == 0) {
        *(int *)(sub + 0x154) = *(int *)(sub + 0x180);
        SetBoyInfo(*(void **)(sub + 0x150), *(void **)(sub + 0x180));
    }
    if (self == D_00639EA8) {
        *(int *)(sub + 0x154) = *(int *)(sub + 0x180);
        if (mode != 0) {
            int item = *(int *)(sub + 0x180);
            int drop = 0;
            if (item != 0) {
                drop = *(int *)(item + 0x16C) == 0;
            }
            if (*(int *)(sub + 0x180) == 0 && *(int *)(sub + 0x184) == 0) {
                drop = 1;
            }
            if (drop) {
                *(int *)(sub + 0x154) = *(int *)(sub + 0x180) = *(int *)(sub + 0x184) = 0;
                ACTSendMailCorrect(self, 0x7E);
            }
        }
    }
}

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

extern ActGameViewTbl D_006C0470;

void ACTGameView_Init(void)
{
    D_006C0470.num = 0;
    D_006C0470.cur = 0;
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

extern int D_0063A6B4;
extern void ClipWallField(void *);
extern int CompareAttribute(int attr, int mask);

int ACTCheckCollis_WAY(float f, void *p0, void *p1, void *actor, void *posout)
{
    HandWork work;
    int flag;
    int attr;

    memset(&work, 0, 0xC0);
    flag = actor ? *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) : 0;
    work._70 = f;
    D_0063A6B4 = 0;
    sceVu0CopyVector(&work, (int)p0);
    sceVu0CopyVector((char *)&work + 0x10, (int)p1);
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
    }
    ClipWall(&work);
    attr = work._98;
    if (flag != 0) {
        *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
    }
    /* The wall record is published on BOTH paths: SRCFILE.TXT rows put the
       surviving `sw ...%gp_rel(D_0063A6B4)` on line 1586 with a seven-line
       gap (1579-1585) above it, i.e. an else arm; jump.c cross-jumps the two
       copies back into the one store ROM carries. */
    if (work._88 == 0) {
        if (flag != 0) {
            *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 0;
        }
        ClipWallField(&work);
        if (flag != 0) {
            *(int *)((char *)*(int *)((char *)actor + 0x15C) + 0x74) = 1;
        }
        if (work._88 == 0) {
            return 0;
        }
        D_0063A6B4 = work._80;
    } else {
        D_0063A6B4 = work._80;
    }
    if (CompareAttribute(attr, 0x30000) != 0) {
        return 0;
    }
    if (posout != 0) {
        *(float *)((char *)posout + 0) = work._20;
        *(float *)((char *)posout + 4) = work._24;
        *(float *)((char *)posout + 8) = work._28;
    }
    return 1;
}

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
    int n = D_006C0470.num++;
    if (n >= 100) {
        debug_StdPrintfDummy(D_00552400);
        debug_assert(D_00552420, 0x6FF);
        __assert(D_00552420, 0x6FF, D_0063A698);
    }
    D_006C0470.obj[n] = a1;
    D_006C0470.view[n] = 0;
    D_006C0470.simple[n] = 0;
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
    int n = D_006C0470.num++;
    if (n >= 100) {
        debug_StdPrintfDummy(D_00552400);
        debug_assert(D_00552420, 0x6FF);
        __assert(D_00552420, 0x6FF, D_0063A698);
    }
    D_006C0470.obj[n] = a1;
    D_006C0470.view[n] = 0;
    D_006C0470.simple[n] = 0;
}

int ACTGameView_Check(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006C0470.num; i++) {
        if ((int)D_006C0470.obj[i] == a1) {
            return *(unsigned char *)&D_006C0470.view[i];
        }
    }
    return 0;
}

int ACTGameViewSimple_Check(int a0, int a1)
{
    int i;
    for (i = 0; i < D_006C0470.num; i++) {
        if ((int)D_006C0470.obj[i] == a1) {
            return *(unsigned char *)&D_006C0470.simple[i];
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

unsigned char ACTGame_NoWeapon(char *a0)
{
    char *w = *(char **)(*(char **)(a0 + 0x164) + 0x150);
    unsigned char r = 0;
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

/* INTERIM: the listing inlines ACTLookTarget_Init (lines 2183-2187) into
   _ACTLookTarget_Set as well; the static stand-in is defined once, above
   ACTGame_BeforeFunc (its other inline site).
   Collapses to one `inline` definition at layout. */
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

int ACTGame_GetCurrentCallStatus(char *a0)
{
    char *s = (char *)*(int *)(a0 + 0x164);
    int st;

    if (a0 != D_00639EA4) {
        return 0;
    }
    switch (D_0055FE58[*(int *)((char *)*(int *)(a0 + 0x15C) + 0x4A0)].u_188.h.hi & 7) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 0;
    }
    if (((int)(*(unsigned long long *)(s + 0x478) >> 46) & 1) &&
        ((int)(*(unsigned long long *)(s + 0x488) >> 46) & 1)) {
        st = *(int *)(s + 0x34);
        if ((unsigned int)st < 4) {
            if (st != 0) {
                return 2;
            }
        }
    }
    return 0;
}

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

extern MotionRec D_0055FE58[];
extern char *D_00639EA8;
extern void SetMotionPlaySpeedRatio(char *a0, float f);

void ACTGame_SetMotionPlaySpeedRatio_Exec(char *a0)
{
    float ratio;
    int keep;

    ratio = 1.0f;
    keep = (unsigned int)*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x54) < 3 &&
           a0 == D_00639EA8;
    if (*(int *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x54) == 1) {
        if (((&D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)])->f_18C >> 30) & 1) {
            ratio = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x58);
            keep = 0;
        }
    } else {
        if ((((&D_0055FE58[*(int *)(*(char **)(a0 + 0x15C) + 0x4A0)])->f_18C >> 26) & 1) == 0) {
            ratio = *(float *)(*(char **)(*(char **)(a0 + 0x164) + 0x680) + 0x58);
        }
    }
    if (keep) {
        ratio = 1.0f;
    }
    /* The dev's wrapper macro expanded to a do/while(0) block; the back-edge
       is what keeps this a real `jal` with a frame instead of the tail call
       ee-gcc makes of a trailing void call (decomp/NOTES.md, "Defeating an
       over-eager sibling-call"). It emits no instructions of its own. */
    do {
        SetMotionPlaySpeedRatio(a0, ratio);
    } while (0);
}

void GetGirlPositionAtThisStage(float *a0)
{
    int buf[4];
    int id = gamesysGetGirlStageIDAndPosition(buf);
    OtherStagePositionGet(a0, stage_no, id, buf);
}
