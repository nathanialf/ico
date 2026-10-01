#include "sugiCommon.h"
#include "spider.h"
#include "debug.h"
#include "gamesys.h"
#include "memory.h"
#include "obj_manager.h"
#include "generator.h"
#include "Matrix.h"
#include "Primitive.h"
#include "a_p_1.h"
#include "act_a_p_1.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "spiderGroupManager.h"
#include <stdlib.h>
#include "main.h"
#include "GifPacket.h"

/* kept local: void * here, int in ios.h */
extern void *ios_partition_sugipon;

/* spider.o's whole .rodata run starts here.  These three are named objects,
   not literals at their use sites: the two group-wake messages are used near
   the end of the file and the ROM has them second and third in the run. */
static const char spiderFile[] = __FILE__;

/* tried to wake a spider group that already has a parent; this is invalid */
static const char spiderWakeHasParentMsg[] =
    "親のいる蜘蛛グループを起こそうとしました。これは無効です\n";

/* tried to wake a spider group with no parent written in the table; invalid */
static const char spiderWakeNoParentMsg[] =
    "蜘蛛グループを起こそうとしましたが、表に親が書かれていません。これは無効です\n";

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

/* RECONSTRUCTION, read from the ROM.  The 64-byte record InitSpiderLayoutGeo
   allocates and hangs at the object's work word: the group's state (-1 laid
   out, 0 entered in the group manager, 1 awake, 2 calling the master back),
   the member spiders, and the counters SpiderLayoutGeo runs. */
typedef struct {
    int state;              /* 0x00 */
    char pad04[0x1C];       /* 0x04 */
    int n;                  /* 0x20, member count */
    char **members;         /* 0x24, the member AP1 objects */
    int awake;              /* 0x28 */
    unsigned int entryWait; /* 0x2C */
    unsigned int infoWait;  /* 0x30 */
    int kind;               /* 0x34, index into the kind table */
    int wakeFrom;           /* 0x38, first member to wake, -1 for none */
    int revived;            /* 0x3C */
} SpiderWork;

/* the three words MemorySpiderLayout saves */
typedef struct {
    int awake;   /* 0x0 */
    int alive;   /* 0x4 */
    int revived; /* 0x8 */
} SpiderMemory;

SpiderWork *InitSpiderLayoutGeo(char *self, char *lay)
{
    SpiderLay l;
    SpiderWork *w;
    int n;
    int i;
    int k;

    w = iosMallocDebug((int)ios_partition_sugipon, sizeof(SpiderWork), spiderFile, 43);
    l = *(SpiderLay *)lay;

    k = *(int *)(lay + 0x30);
    n = D_0062B588[k].n;
    w->n = n;
    w->kind = k;
    w->members = iosMallocDebug((int)ios_partition_sugipon, n * 4, spiderFile, 47);
    w->awake = 0;
    w->state = -1;
    w->entryWait = 0;
    w->infoWait = 0;
    w->wakeFrom = -1;
    w->revived = 0;

    for (i = 0; i < n; i++) {
        *(float *)((char *)&l + 0x14) = random_signed_b() * 3.1415927f;
        w->members[i] = MakeAP1GObj(&l);
        SetAP1VisualState(w->members[i], 0);
    }
    return w;
}

/* listing lines 78-88 */
static inline void wakeSpiderGroup(char *self)
{
    SpiderWork *w;
    int n;
    int i;

    w = GOBJ_SUB(self)->f_830;

    n = w->n;
    w->awake = 1;
    for (i = 0; i < n; i++) {
        WakeUpAP1(w->members[i]);
        SetAP1VisualState(w->members[i], 1);
    }
}

void WakeUpLayoutedSpiders(void *self)
{
    wakeSpiderGroup((char *)self);
    ExecuteSEPackage((char *)self, 106);
}

/* listing lines 324-331 */
static inline void setSpiderGroupHost(char *self, void *host)
{
    SpiderWork *w;
    int i;

    w = GOBJ_SUB(self)->f_830;
    for (i = 0; i < w->n; i++) {
        if (w->members[i] != 0) {
            SetAP1HostGObj(w->members[i], host);
        }
    }
}

typedef union {
    char *p;
    int i;
} SpiderWord;

/* The prior-level pass reads the actor extension through a union view: the
   `w->state = 2;` status store in the caller has to kill this load, which only
   an alias-set-0 union member does. */
/* listing lines 336-341 */
static inline void setSpiderGroupPrior(char *self)
{
    SpiderWork *w;
    int i;

    w = (SpiderWork *)((SpiderWord *)(((SpiderWord *)(self + 0x15C))->p + 0x830))->p;
    for (i = 0; i < w->n; i++) {
        if (w->members[i] != 0) {
            SetAP1PriorLevel(w->members[i], 1);
        }
    }
}

/* listing lines 392-396 */
static inline void callSpidersToGirl(char *self)
{
    if (boyGObj != 0) {
        setSpiderGroupHost(self, boyGObj);
    }
}

/* listing lines 402-407 */
static inline int callSpidersToBoy(char *self)
{
    if (girlGObj != 0) {
        setSpiderGroupHost(self, girlGObj);
        return 1;
    }
    return 0;
}

int CallSpidersToReviveEnemy(char *self)
{
    SpiderWork *w;

    w = GOBJ_SUB(self)->f_830;
    if (w->state == 1) {
        if (callSpidersToBoy(self)) {
            EntryToSpiderGroupManagerForReviveMaster(self, girlGObj);
            w->state = 2;
            setSpiderGroupPrior(self);
        } else {
            callSpidersToGirl(self);
        }
    }
    return 1;
}

/* the TU's .sdata opens with the layout entry count SpiderLayoutGeo prints */
static int spiderEntryCount = 0; /* derived name */

/* listing lines 69-76 */
static inline void setAllSpiderPositions(char *self, float *pos)
{
    SpiderWork *w;
    int n;
    int i;

    w = GOBJ_SUB(self)->f_830;
    n = w->n;
    for (i = 0; i < n; i++) {
        SetDirectRootPosition(w->members[i], pos);
    }
}

void SpiderLayoutGeo(char *self)
{
    float pos[4];
    SpiderWork *w;
    int i;

    w = GOBJ_SUB(self)->f_830;
    switch (*(int *)w) {
    case -1: {
        char *host = *(char **)*(char **)(self + 0x15C);

        if (host != 0 && *(int *)(host + 0xC) != 33) {
            setSpiderGroupHost(self, host);
        } else {
            callSpidersToGirl(self);
            if (D_0062B588[w->kind].f14 == 1) {
                if (callSpidersToBoy(self) == 0) {
                    /* an order came to target the heroine, but this stage has no heroine */
                    debug_StdPrintfDummy(
                        "蜘蛛のターゲットをヒロインにせよと言う命令がありましたが\nこのステージにヒロインはいません。\n");
                }
            }
        }
        if (w->entryWait++ >= 11) {
            if (w->revived == 0) {
                debug_StdPrintfDummy("entry %d\n", spiderEntryCount++);
                EntrySpiderGroupManager(self);
                w->state = 0;
            } else {
                debug_StdPrintfDummy("entry revived %d\n", spiderEntryCount++);
                EntryRevivedSpiderGroupManager(self);
                w->state = 0;
            }
        }
        break;
    }
    case 0:
        if (w->wakeFrom != -1) {
            wakeSpiderGroup(self);
            for (i = w->wakeFrom; i < w->n; i++) {
                iosOmSendMail(w->members[i], 223, w->members[i]);
                SetAP1VisualState(w->members[i], 0);
            }
            w->state = 1;
        } else {
            char *gen = *(char **)*(char **)(self + 0x15C);

            if (gen != 0 && *(int *)(gen + 0xC) != 33 && IsActCharDead(gen) == 0) {
                if (*(void **)(*(char **)(gen + 0x164) + 0x54) != 0) {
                    GetGeneratorSafePosition(pos, *(void **)(*(char **)(gen + 0x164) + 0x54));
                    setAllSpiderPositions(self, pos);
                }
                WakeUpLayoutedSpiders(self);
                w->state = 1;
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

    if (w->infoWait++ >= 31) {
        w->infoWait = 0;
        gamesysObjInfoUniqDataSet(self);
    }
}

/* the debug display's selected line (MAIN.MAP spider.o) */
int sgSelLine = 0;

/* spider.o's whole .data run: the white the debug wire sphere is drawn in. */
static int spiderWireColor[4] = {0xFF, 0xFF, 0xFF, 0xFF};

/* The rest of spider.o's .rodata run: the compiler puts SpiderLayoutGeo's
   switch table ahead of these, so they are named objects declared after it. */
static const char spiderStatusFmt[] = "%c SE:%s AI:%s";

static const char spiderRestoreFmt[] = "restore: %p\n";

static const char spiderWakeFmt[] = "     WAKE: %s\n";

static const char spiderAliveFmt[] = "    ALIVE: %d\n";

static const char spiderReviveFmt[] = "   REVIVE: %d\n";

void DispAllMemberOfSpider(char *self, int *col)
{
    SpiderWork *g;
    char *p;
    int i;

    g = GOBJ_SUB(self)->f_830;
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
            prim_DispWireSphere(50.0f, col, 4, 4);
            gif_EndPacket();
            debug_PrintfDummy(400, sgInfoLine * 10 + 50,
                              (col[0] << 24) | (col[1] << 16) | (col[2] << 8) | 0xFF,
                              spiderStatusFmt, sgInfoLine == sgSelLine ? 62 : 32,
                              GetAP1Mode(g->members[i]), GetAP1AIMode(g->members[i]));
            if (sgInfoLine == sgSelLine) {
                gif_StartPacketPri(11);
                gif_SetZTest(1);
                gif_SetAlpha(1, 5, 128);
                prim_DispWireSphere(100.0f, spiderWireColor, 4, 4);
                gif_EndPacket();
            }
            sgInfoLine++;
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
        prim_DispWireSphere(100.0f, col, 4, 4);
        gif_EndPacket();
    }
}

void SetSpiderGroupReviveStatus(char *a0)
{
    SpiderWork *p = GOBJ_SUB(a0)->f_830;
    p->revived = 1;
    gamesysObjInfoUniqDataSet(a0);
    debug_StdPrintfDummy("SET %d\n", *(int *)(a0 + 8));
}

int DeadAllSpiders(char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int i;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
        if (o != 0) {
            iosOmSendMail(o, 0x26, o);
        }
    }
    return 0;
}

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 148-151) shared by
   GetAliveSpiders and MemorySpiderLayout; it has no out-of-line copy. */
static inline int CountAliveSpiders(char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int i;
    int n = 0;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
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
    Sub15C *oi = *(Sub15C **)(gp + 0x15C);
    SpiderWork *sg = oi->f_830;
    char *own = *(char **)oi;

    if (own != 0 && *(int *)(own + 0xC) != 0x21 && IsActCharDead(own) == 0) {
        return sg->n;
    }
    if (sg->awake) {
        return CountAliveSpiders(gp);
    }
    return -1;
}

char *DeleteSpiderFromLayoutGroup(char *a0, int a1)
{
    char **arr = ((SpiderWork *)GOBJ_SUB(a0)->f_830)->members;
    char *r = arr[a1];
    arr[a1] = 0;
    return r;
}

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 219-222) that
   clears the dead members out of a spider group; it has no out-of-line copy. */
static inline void RemoveDeadLayoutSpiders(SpiderWork *sg)
{
    int i;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
        if (o != 0) {
            if (IsActCharDead(o)) {
                sg->members[i] = 0;
            }
        }
    }
}

int GetNearestOfLayoutSpiders(float *dist, char *gp, void *center)
{
    float pos[4];
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int nearest = -1;
    int i;

    RemoveDeadLayoutSpiders(sg);

    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
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

int CheckSpidersInsideOfReviveRange(int *out, char *gp, void *center)
{
    float pos[4];
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    char **p = sg->members;
    int i;
    int n = 0;

    for (i = 0; i < sg->n; i++, p++) {
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

int RestoreSpiderLayoutExtGeo(char *a0, char *a1)
{
    SpiderWork *p = GOBJ_SUB(a0)->f_830;
    int *ex = (int *)(a1 + 0x30);

    if (*(int *)(a1 + 0x30)) {
        p->wakeFrom = ex[1];
    }
    if (ex[2]) {
        p->revived = 1;
    }
    debug_StdPrintfDummy(spiderRestoreFmt, a0);
    debug_StdPrintfDummy(spiderWakeFmt, *(int *)(a1 + 0x30) ? "YES" : "NO");
    debug_StdPrintfDummy(spiderAliveFmt, ex[1]);
    debug_StdPrintfDummy(spiderReviveFmt, ex[2]);
    return 1;
}

/* the debug display's line counter (MAIN.MAP spider.o), the last object of the
   TU's .sdata, after RestoreSpiderLayoutExtGeo's two answers */
int sgInfoLine = 0;

int MemorySpiderLayout(SpiderMemory *dst, char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int awake = sg->awake;

    dst->awake = awake;
    if (awake) {
        dst->alive = CountAliveSpiders(gp);
    } else {
        dst->alive = 0;
    }
    dst->revived = sg->revived;
    return 1;
}

/* Unnamed in MAIN.MAP: a static-inline helper (listing rows 71-74) shared by
   WakeUpSpidersFromGenerator and SpiderLayoutGeo; it has no out-of-line copy. */
static inline void SetLayoutedSpidersRootPosition(char *gp, void *pos)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int num = sg->n;
    int i;
    for (i = 0; i < num; i++) {
        SetDirectRootPosition(sg->members[i], pos);
    }
}

void WakeUpSpidersFromGenerator(char *gp)
{
    float pos[4];
    char *gen = *(char **)(*(char **)(gp + 0x15C));

    if (gen != 0) {
        if (*(int *)(gen + 0xC) != 0x21) {
            debug_StdPrintfDummy(spiderWakeHasParentMsg);
            return;
        }
    } else {
        debug_StdPrintfDummy(spiderWakeNoParentMsg);
        return;
    }
    GetGeneratorSafePosition(pos, gen);
    SetLayoutedSpidersRootPosition(gp, pos);
    WakeUpLayoutedSpiders(gp);
}

/* INTERIM: stand-in for the TU's own DeleteSpiderFromLayoutGroup, which ROM
   inlines here (listing rows 257-259 inside this function).  The plain
   definition above stays until the TU's inline tail is laid out. */
static inline char *DeleteSpiderFromLayoutGroup_inl(char *gp, int idx)
{
    char **arr = ((SpiderWork *)GOBJ_SUB(gp)->f_830)->members;
    char *r = arr[idx];
    arr[idx] = 0;
    return r;
}

void DeleteAllSpidersOfLayoutGroup(char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int i;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
        if (o != 0) {
            SetAP1DeadStatus(o);
            DeleteSpiderFromLayoutGroup_inl(gp, i);
        }
    }
    sg->n = 0;
}

void SleepSpiderGroup(char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int i;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
        if (o != 0) {
            iosOmSendMail(o, 0x20, o);
        }
    }
}

void WakeupSpiderGroup(char *gp)
{
    SpiderWork *sg = GOBJ_SUB(gp)->f_830;
    int i;
    for (i = 0; i < sg->n; i++) {
        char *o = sg->members[i];
        if (o != 0) {
            iosOmSendMail(o, 0x1F, o);
        }
    }
}
