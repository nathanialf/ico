#include "common.h"
#include "sugiCommon.h"

extern void WakeUpAP1(void *ap1);
extern void SetAP1VisualState(void *ap1, int state);
extern void ExecuteSEPackage(char *self, int id);
extern void *D_0063A438;
extern char D_00620B60[];
extern void *iosMallocDebug(int heap, int size, char *file, int line);
extern void *MakeAP1GObj(void *lay);

typedef struct {
    char pad[0x10];
    int n;
    int f14;
    char pad2[8];
} SpiderKindRec;

extern SpiderKindRec D_0062B588[];

typedef struct {
    long long w[8];
} SpiderLay;

char *InitSpiderLayoutGeo(char *self, char *lay)
{
    SpiderLay l;
    char *w;
    int n;
    int i;
    int k;

    w = (char *)iosMallocDebug((int)D_0063A438, 64, D_00620B60, 43);
    l = *(SpiderLay *)lay;

    k = *(int *)(lay + 0x30);
    n = D_0062B588[k].n;
    *(int *)(w + 0x20) = n;
    *(int *)(w + 0x34) = k;
    *(char **)(w + 0x24) = (char *)iosMallocDebug((int)D_0063A438, n * 4, D_00620B60, 47);
    *(int *)(w + 0x28) = 0;
    *(int *)(w + 0x00) = -1;
    *(int *)(w + 0x2C) = 0;
    *(int *)(w + 0x30) = 0;
    *(int *)(w + 0x38) = -1;
    *(int *)(w + 0x3C) = 0;

    for (i = 0; i < n; i++) {
        *(float *)((char *)&l + 0x14) = random_signed_b() * 3.1415927f;
        *(void **)(*(char **)(w + 0x24) + i * 4) = MakeAP1GObj(&l);
        SetAP1VisualState(*(void **)(*(char **)(w + 0x24) + i * 4), 0);
    }
    return w;
}

/* listing lines 78-88 */
static inline void wakeSpiderGroup(char *self)
{
    char *w;
    int n;
    int i;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);

    n = *(int *)(w + 0x20);
    *(int *)(w + 0x28) = 1;
    for (i = 0; i < n; i++) {
        WakeUpAP1(*(void **)(*(char **)(w + 0x24) + i * 4));
        SetAP1VisualState(*(void **)(*(char **)(w + 0x24) + i * 4), 1);
    }
}

void WakeUpLayoutedSpiders(void *self)
{
    wakeSpiderGroup((char *)self);
    ExecuteSEPackage((char *)self, 106);
}

extern void *D_00639EA4;
extern void *D_00639EA8;
extern void SetAP1HostGObj(void *ap1, void *host);
extern void SetAP1PriorLevel(void *ap1, int level);
extern void EntryToSpiderGroupManagerForReviveMaster(char *self, void *host);

/* listing lines 324-331 */
static inline void setSpiderGroupHost(char *self, void *host)
{
    char *w;
    int i;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    for (i = 0; i < *(int *)(w + 0x20); i++) {
        if (*(void **)(*(char **)(w + 0x24) + i * 4) != 0) {
            SetAP1HostGObj(*(void **)(*(char **)(w + 0x24) + i * 4), host);
        }
    }
}

typedef union {
    char *p;
    int i;
} SpiderWord;

/* The prior-level pass reads the actor extension through a union view: the
   `*(int *)w = 2;` status store in the caller has to kill this load, which only
   an alias-set-0 union member does. */
/* listing lines 336-341 */
static inline void setSpiderGroupPrior(char *self)
{
    char *w;
    int i;

    w = ((SpiderWord *)(((SpiderWord *)(self + 0x15C))->p + 0x830))->p;
    for (i = 0; i < *(int *)(w + 0x20); i++) {
        if (*(void **)(*(char **)(w + 0x24) + i * 4) != 0) {
            SetAP1PriorLevel(*(void **)(*(char **)(w + 0x24) + i * 4), 1);
        }
    }
}

/* listing lines 392-396 */
static inline void callSpidersToGirl(char *self)
{
    if (D_00639EA4 != 0) {
        setSpiderGroupHost(self, D_00639EA4);
    }
}

/* listing lines 402-407 */
static inline int callSpidersToBoy(char *self)
{
    if (D_00639EA8 != 0) {
        setSpiderGroupHost(self, D_00639EA8);
        return 1;
    }
    return 0;
}

int CallSpidersToReviveEnemy(char *self)
{
    char *w;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    if (*(int *)w == 1) {
        if (callSpidersToBoy(self)) {
            EntryToSpiderGroupManagerForReviveMaster(self, D_00639EA8);
            *(int *)w = 2;
            setSpiderGroupPrior(self);
        } else {
            callSpidersToGirl(self);
        }
    }
    return 1;
}

extern int D_0063BAC0;
extern int iosOmSendMail(void *gop, int msg, void *sender);
extern char D_00620C00[];
extern char D_00620C60[];
extern char D_00620C70[];
extern void debug_StdPrintfDummy();
extern void EntrySpiderGroupManager(char *self);
extern void EntryRevivedSpiderGroupManager(char *self);
extern void GetGeneratorSafePosition(void *pos, void *gen);
extern void SetDirectRootPosition(void *obj, void *pos);
extern void gamesysObjInfoUniqDataSet(char *self);

/* listing lines 69-76 */
static inline void setAllSpiderPositions(char *self, float *pos)
{
    char *w;
    int n;
    int i;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    n = *(int *)(w + 0x20);
    for (i = 0; i < n; i++) {
        SetDirectRootPosition(*(void **)(*(char **)(w + 0x24) + i * 4), pos);
    }
}

void SpiderLayoutGeo(char *self)
{
    float pos[4];
    char *w;
    int i;

    w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    switch (*(int *)w) {
    case -1: {
        char *host = *(char **)*(char **)(self + 0x15C);

        if (host != 0 && *(int *)(host + 0xC) != 33) {
            setSpiderGroupHost(self, host);
        } else {
            callSpidersToGirl(self);
            if (D_0062B588[*(int *)(w + 0x34)].f14 == 1) {
                if (callSpidersToBoy(self) == 0) {
                    debug_StdPrintfDummy(D_00620C00);
                }
            }
        }
        if ((*(unsigned int *)(w + 0x2C))++ >= 11) {
            if (*(int *)(w + 0x3C) == 0) {
                debug_StdPrintfDummy(D_00620C60, D_0063BAC0++);
                EntrySpiderGroupManager(self);
                *(int *)w = 0;
            } else {
                debug_StdPrintfDummy(D_00620C70, D_0063BAC0++);
                EntryRevivedSpiderGroupManager(self);
                *(int *)w = 0;
            }
        }
        break;
    }
    case 0:
        if (*(int *)(w + 0x38) != -1) {
            wakeSpiderGroup(self);
            for (i = *(int *)(w + 0x38); i < *(int *)(w + 0x20); i++) {
                iosOmSendMail(*(void **)(*(char **)(w + 0x24) + i * 4), 223,
                              *(void **)(*(char **)(w + 0x24) + i * 4));
                SetAP1VisualState(*(void **)(*(char **)(w + 0x24) + i * 4), 0);
            }
            *(int *)w = 1;
        } else {
            char *gen = *(char **)*(char **)(self + 0x15C);

            if (gen != 0 && *(int *)(gen + 0xC) != 33 && IsActCharDead(gen) == 0) {
                if (*(void **)(*(char **)(gen + 0x164) + 0x54) != 0) {
                    GetGeneratorSafePosition(pos, *(void **)(*(char **)(gen + 0x164) + 0x54));
                    setAllSpiderPositions(self, pos);
                }
                WakeUpLayoutedSpiders(self);
                *(int *)w = 1;
            }
        }
        break;
    case 2:
    case 3:
        break;
    case 1:
    default: {
        char *dead = *(char **)*(char **)(self + 0x15C);

        if (dead != 0 && *(int *)(dead + 0xC) != 33) {
            if (IsActCharDead(dead) != 0) {
                CallSpidersToReviveEnemy(self);
            }
        }
        break;
    }
    }

    if ((*(unsigned int *)(w + 0x30))++ >= 31) {
        *(int *)(w + 0x30) = 0;
        gamesysObjInfoUniqDataSet(self);
    }
}

extern int D_0063BAC4;
extern int D_0063BADC;
extern char D_00620CA8[];
extern int D_004ECFA0[];
extern void GetRootPosition(void *out, void *obj);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *m);
extern void MatrixDrive_RotMatrixX(short a);
extern void MatrixDrive_RotMatrixY(short a);
extern void MatrixDrive_RotMatrixZ(short a);
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetAlpha(int a, int b, int c);
extern void prim_DispWireSphere(void *col, int a1, int a2, float r);
extern void gif_EndPacket(void);
extern int GetAP1Mode(void *ap1);
extern int GetAP1AIMode(void *ap1);
extern int rand(void);
extern void debug_PrintfDummy(int x, int y, unsigned int color, char *fmt, ...);

typedef struct {
    char pad[0x20];
    int n;
    void **members;
} SpiderGrp;

void DispAllMemberOfSpider(char *self, int *col)
{
    SpiderGrp *g;
    char *p;
    int i;

    g = *(SpiderGrp **)(*(char **)(self + 0x15C) + 0x830);
    for (i = 0; i < g->n; i++) {
        if (g->members[i] != 0) {
            _UnitMatrix(MatrixDrive_GetMatrix());
            GetRootPosition((char *)MatrixDrive_GetMatrix() + 0x30, g->members[i]);
            MatrixDrive_RotMatrixX((short)rand());
            MatrixDrive_RotMatrixY((short)rand());
            MatrixDrive_RotMatrixZ((short)rand());
            gif_StartPacketPri(11);
            gif_SetZTest(1);
            gif_SetAlpha(1, 5, 128);
            prim_DispWireSphere(col, 4, 4, 50.0f);
            gif_EndPacket();
            debug_PrintfDummy(400, D_0063BADC * 10 + 50,
                              (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF, D_00620CA8,
                              D_0063BADC == D_0063BAC4 ? 62 : 32, GetAP1Mode(g->members[i]),
                              GetAP1AIMode(g->members[i]));
            if (D_0063BADC == D_0063BAC4) {
                gif_StartPacketPri(11);
                gif_SetZTest(1);
                gif_SetAlpha(1, 5, 128);
                prim_DispWireSphere(D_004ECFA0, 4, 4, 100.0f);
                gif_EndPacket();
            }
            D_0063BADC++;
        }
    }

    p = *(char **)*(char **)(self + 0x15C);
    if (p != 0 && *(int *)(p + 0xC) != 33) {
        _UnitMatrix(MatrixDrive_GetMatrix());
        GetRootPosition((char *)MatrixDrive_GetMatrix() + 0x30, *(void **)*(char **)(self + 0x15C));
        MatrixDrive_RotMatrixX((short)rand());
        MatrixDrive_RotMatrixY((short)rand());
        MatrixDrive_RotMatrixZ((short)rand());
        gif_StartPacketPri(11);
        gif_SetZTest(1);
        gif_SetAlpha(1, 5, 128);
        prim_DispWireSphere(col, 4, 4, 100.0f);
        gif_EndPacket();
    }
}

extern char D_0063BAC8[];

void SetSpiderGroupReviveStatus(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x3C) = 1;
    gamesysObjInfoUniqDataSet(a0);
    debug_StdPrintfDummy(D_0063BAC8, *(int *)(a0 + 8));
}

extern int iosOmSendMail(void *gop, int msg, void *sender);

int DeadAllSpiders(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x26, o);
        }
    }
    return 0;
}

extern int IsActCharDead(void *gop);

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 148-151) shared by
   GetAliveSpiders and MemorySpiderLayout; it has no out-of-line copy. */
static inline int CountAliveSpiders(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    int n = 0;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            if (IsActCharDead(o) == 0) {
                n++;
            }
        }
    }
    return n;
}

int GetAliveSpiders(char *gp)
{
    char *oi = *(char **)(gp + 0x15C);
    char *sg = *(char **)(oi + 0x830);
    char *own = *(char **)oi;

    if (own != 0 && *(int *)(own + 0xC) != 0x21 && IsActCharDead(own) == 0) {
        return *(int *)(sg + 0x20);
    }
    if (*(char **)(sg + 0x28)) {
        return CountAliveSpiders(gp);
    }
    return -1;
}

char *DeleteSpiderFromLayoutGroup(char *a0, int a1)
{
    char **arr = *(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x24);
    char *r = arr[a1];
    arr[a1] = 0;
    return r;
}

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 219-222) that
   clears the dead members out of a spider group; it has no out-of-line copy. */
static inline void RemoveDeadLayoutSpiders(char *sg)
{
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            if (IsActCharDead(o)) {
                (*(char ***)(sg + 0x24))[i] = 0;
            }
        }
    }
}

int GetNearestOfLayoutSpiders(float *dist, char *gp, void *center)
{
    float pos[4];
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int nearest = -1;
    int i;

    RemoveDeadLayoutSpiders(sg);

    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            float d;

            GetRootPosition(pos, o);
            d = distance_squared(center, pos);
            if (d < *dist) {
                nearest = i;
                *dist = d;
            }
        }
    }
    return nearest;
}

extern void GetRootPosition(void *out, void *obj);

int CheckSpidersInsideOfReviveRange(int *out, char *gp, void *center)
{
    float pos[4];
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    char **p = *(char ***)(sg + 0x24);
    int i;
    int n = 0;

    for (i = 0; i < *(int *)(sg + 0x20); i++, p++) {
        if (*p != 0) {
            if (IsActCharDead(*p) == 0) {
                GetRootPosition(pos, *p);

                if (distance_squared(pos, center) < 10000.0f) {
                    out[n] = i;
                    n++;
                }
            }
        }
    }
    return n;
}

int RestoreSpiderLayoutGeo(void)
{
    return 1;
}

extern char D_00620CB8[];
extern char D_00620CC8[];
extern char D_0063BAD0[];
extern char D_0063BAD8[];
extern char D_00620CD8[];
extern char D_00620CE8[];

int RestoreSpiderLayoutExtGeo(char *a0, char *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int *ex = (int *)(a1 + 0x30);

    if (*(int *)(a1 + 0x30)) {
        *(int *)(p + 0x38) = ex[1];
    }
    if (ex[2]) {
        *(int *)(p + 0x3C) = 1;
    }
    debug_StdPrintfDummy(D_00620CB8, a0);
    debug_StdPrintfDummy(D_00620CC8, *(int *)(a1 + 0x30) ? D_0063BAD0 : D_0063BAD8);
    debug_StdPrintfDummy(D_00620CD8, ex[1]);
    debug_StdPrintfDummy(D_00620CE8, ex[2]);
    return 1;
}

int MemorySpiderLayout(char *dst, char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    char *lay = *(char **)(sg + 0x28);

    *(char **)dst = lay;
    if (lay) {
        *(int *)(dst + 4) = CountAliveSpiders(gp);
    } else {
        *(int *)(dst + 4) = 0;
    }
    *(int *)(dst + 8) = *(int *)(sg + 0x3C);
    return 1;
}

extern char D_00620B70[];
extern char D_00620BB0[];
extern void GetGeneratorSafePosition(void *pos, void *gen);
extern void SetDirectRootPosition(void *obj, void *pos);
extern void WakeUpLayoutedSpiders(void *gp);

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 71-74) shared by
   WakeUpSpidersFromGenerator and SpiderLayoutGeo; it has no out-of-line copy. */
static inline void SetLayoutedSpidersRootPosition(char *gp, void *pos)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int num = *(int *)(sg + 0x20);
    int i;
    for (i = 0; i < num; i++) {
        SetDirectRootPosition((*(char ***)(sg + 0x24))[i], pos);
    }
}

void WakeUpSpidersFromGenerator(char *gp)
{
    float pos[4];
    char *gen = *(char **)(*(char **)(gp + 0x15C));

    if (gen != 0) {
        if (*(int *)(gen + 0xC) != 0x21) {
            debug_StdPrintfDummy(D_00620B70);
            return;
        }
    } else {
        debug_StdPrintfDummy(D_00620BB0);
        return;
    }
    GetGeneratorSafePosition(pos, gen);
    SetLayoutedSpidersRootPosition(gp, pos);
    WakeUpLayoutedSpiders(gp);
}

extern void SetAP1DeadStatus(void *gop);

/* INTERIM: stand-in for the TU's own DeleteSpiderFromLayoutGroup, which ROM
   inlines here (listing rows 257-259 inside this function).  The plain
   definition above stays until the TU's inline tail is laid out. */
static inline char *DeleteSpiderFromLayoutGroup_inl(char *gp, int idx)
{
    char **arr = *(char ***)(*(char **)(*(char **)(gp + 0x15C) + 0x830) + 0x24);
    char *r = arr[idx];
    arr[idx] = 0;
    return r;
}

void DeleteAllSpidersOfLayoutGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            SetAP1DeadStatus(o);
            DeleteSpiderFromLayoutGroup_inl(gp, i);
        }
    }
    *(int *)(sg + 0x20) = 0;
}

extern int iosOmSendMail(void *gop, int msg, void *sender);

void SleepSpiderGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x20, o);
        }
    }
}

void WakeupSpiderGroup(char *gp)
{
    char *sg = *(char **)(*(char **)(gp + 0x15C) + 0x830);
    int i;
    for (i = 0; i < *(int *)(sg + 0x20); i++) {
        char *o = (*(char ***)(sg + 0x24))[i];
        if (o != 0) {
            iosOmSendMail(o, 0x1F, o);
        }
    }
}
