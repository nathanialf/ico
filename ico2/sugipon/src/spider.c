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
#include "ios.h"
#include "include_asm.h"

/* the file name and the two group-wake messages */
static const char spiderFile[] = __FILE__; /* derived name */

/* tried to wake a spider group that already has a parent; this is invalid */
static const char spiderWakeHasParentMsg[] =
    "親のいる蜘蛛グループを起こそうとしました。これは無効です\n"; /* derived name */

/* tried to wake a spider group with no parent written in the table; invalid */
static const char spiderWakeNoParentMsg[] =
    "蜘蛛グループを起こそうとしましたが、表に親が書かれていません。これは無効です\n"; /* derived name */

/* The 64-byte record InitSpiderLayoutGeo allocates and hangs at the object's
   work word: the group's state (-1 laid out, 0 entered in the group manager,
   1 awake, 2 calling the master back), the member spiders, and the counters
   SpiderLayoutGeo runs. */
typedef struct SpiderWork { /* field names derived */
    int state;              /* 0x00 */
    char pad04[28];         /* 0x04 */
    int n;                  /* 0x20, member count */
    GObj **members;         /* 0x24, the member AP1 objects */
    int awake;              /* 0x28 */
    unsigned int entryWait; /* 0x2C */
    unsigned int infoWait;  /* 0x30 */
    int kind;               /* 0x34, index into the kind table */
    int wakeFrom;           /* 0x38, first member to wake, -1 for none */
    int revived;            /* 0x3C */
} SpiderWork;               /* derived name */

/* the three words MemorySpiderLayout saves */
typedef struct SpiderMemory { /* field names derived */
    int awake;                /* 0x0 */
    int alive;                /* 0x4 */
    int revived;              /* 0x8 */
} SpiderMemory;               /* derived name */

SpiderWork *InitSpiderLayoutGeo(GObj *self, SObjSimpleSetting *lay)
{
    SObjSimpleSetting l;
    SpiderWork *w;
    int n;
    int i;
    int k;

    w = iosMallocDebug(ios_partition_sugipon, sizeof(SpiderWork), spiderFile, 43);
    l = *lay;

    k = lay->obj;
    n = spiderDef[k].count;
    w->n = n;
    w->kind = k;
    w->members = iosMallocDebug(ios_partition_sugipon, n * 4, spiderFile, 47);
    w->awake = 0;
    w->state = -1;
    w->entryWait = 0;
    w->infoWait = 0;
    w->wakeFrom = -1;
    w->revived = 0;

    for (i = 0; i < n; i++) {
        l.rot[1] = random_signed_b() * 3.1415927f;
        w->members[i] = MakeAP1GObj(&l);
        SetAP1VisualState(w->members[i], 0);
    }
    return w;
}

static inline void wakeSpiderGroup(GObj *self) /* derived name */
{
    SpiderWork *w;
    int n;
    int i;

    w = GOBJ_SUB(self)->work;

    n = w->n;
    w->awake = 1;
    for (i = 0; i < n; i++) {
        WakeUpAP1(w->members[i]);
        SetAP1VisualState(w->members[i], 1);
    }
}

INCLUDE_ASM(WakeUpLayoutedSpiders);

static inline void setSpiderGroupHost(GObj *self, GObj *host) /* derived name */
{
    SpiderWork *w;
    int i;

    w = GOBJ_SUB(self)->work;
    for (i = 0; i < w->n; i++) {
        if (w->members[i] != 0) {
            SetAP1HostGObj(w->members[i], host);
        }
    }
}

static inline void setSpiderGroupPrior(GObj *self) /* derived name */
{
    SpiderWork *w;
    int i;

    w = GOBJ_SUB(self)->work;
    for (i = 0; i < w->n; i++) {
        if (w->members[i] != 0) {
            SetAP1PriorLevel(w->members[i], 1);
        }
    }
}

static inline void callSpidersToBoy(GObj *self) /* derived name */
{
    if (boyGObj != 0) {
        setSpiderGroupHost(self, boyGObj);
    }
}

static inline int callSpidersToGirl(GObj *self) /* derived name */
{
    if (girlGObj != 0) {
        setSpiderGroupHost(self, girlGObj);
        return 1;
    }
    return 0;
}

INCLUDE_ASM(CallSpidersToReviveEnemy);

/* the layout entry count SpiderLayoutGeo prints */
static int spiderEntryCount = 0; /* derived name */

static inline void setAllSpiderPositions(GObj *self, float *pos) /* derived name */
{
    SpiderWork *w;
    int n;
    int i;

    w = GOBJ_SUB(self)->work;
    n = w->n;
    for (i = 0; i < n; i++) {
        SetDirectRootPosition(w->members[i], pos);
    }
}

INCLUDE_ASM(SpiderLayoutGeo);

/* the debug display's selected line */
int sgSelLine = 0;

/* the white the debug wire sphere is drawn in */
static int spiderWireColor[4] = {255, 255, 255, 255}; /* derived name */

/* the debug display's formats */
static const char spiderStatusFmt[] = "%c SE:%s AI:%s"; /* derived name */

static const char spiderRestoreFmt[] = "restore: %p\n"; /* derived name */

static const char spiderWakeFmt[] = "     WAKE: %s\n"; /* derived name */

static const char spiderAliveFmt[] = "    ALIVE: %d\n"; /* derived name */

static const char spiderReviveFmt[] = "   REVIVE: %d\n"; /* derived name */

INCLUDE_ASM(DispAllMemberOfSpider);

INCLUDE_ASM(SetSpiderGroupReviveStatus);

INCLUDE_ASM(DeadAllSpiders);

/* shared by GetAliveSpiders and MemorySpiderLayout */
static inline int CountAliveSpiders(GObj *gp) /* derived name */
{
    SpiderWork *sg = GOBJ_SUB(gp)->work;
    int i;
    int n = 0;
    for (i = 0; i < sg->n; i++) {
        GObj *o = sg->members[i];
        if (o != 0) {
            if (IsActCharDead(o) == 0) {
                n++;
            }
        }
    }
    return n;
}

INCLUDE_ASM(GetAliveSpiders);

/* the body of DeleteSpiderFromLayoutGroup, which DeleteAllSpidersOfLayoutGroup
   inlines and DeleteSpiderFromLayoutGroup calls */
static inline GObj *DeleteSpiderFromLayoutGroup_inl(GObj *gp, int idx) /* derived name */
{
    GObj **arr = ((SpiderWork *)GOBJ_SUB(gp)->work)->members;
    GObj *r = arr[idx];
    arr[idx] = 0;
    return r;
}

INCLUDE_ASM(DeleteSpiderFromLayoutGroup);

/* clear the dead members out of a spider group */
static inline void RemoveDeadLayoutSpiders(SpiderWork *sg) /* derived name */
{
    int i;
    for (i = 0; i < sg->n; i++) {
        GObj *o = sg->members[i];
        if (o != 0) {
            if (IsActCharDead(o)) {
                sg->members[i] = 0;
            }
        }
    }
}

INCLUDE_ASM(GetNearestOfLayoutSpiders);

INCLUDE_ASM(CheckSpidersInsideOfReviveRange);

int RestoreSpiderLayoutGeo(void)
{
    return 1;
}

INCLUDE_ASM(RestoreSpiderLayoutExtGeo);

/* the debug display's line counter */
int sgInfoLine = 0;

INCLUDE_ASM(MemorySpiderLayout);

/* shared by WakeUpSpidersFromGenerator and SpiderLayoutGeo */
static inline void SetLayoutedSpidersRootPosition(GObj *gp, void *pos) /* derived name */
{
    SpiderWork *sg = GOBJ_SUB(gp)->work;
    int num = sg->n;
    int i;
    for (i = 0; i < num; i++) {
        SetDirectRootPosition(sg->members[i], pos);
    }
}

INCLUDE_ASM(WakeUpSpidersFromGenerator);

INCLUDE_ASM(DeleteAllSpidersOfLayoutGroup);

INCLUDE_ASM(SleepSpiderGroup);

INCLUDE_ASM(WakeupSpiderGroup);
