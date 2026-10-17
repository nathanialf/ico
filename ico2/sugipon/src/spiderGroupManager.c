#include "debug.h"
#include "debug_exception.h"
#include "gobj.h"
#include "generator.h"
#include "act_a_p_1.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "spiderGroupManager.h"
#include "spider.h"
#include "main.h"
#include <assert.h>
#include "include_asm.h"

/* the manager's counters and the revive state */
static int reviveNext = 0; /* derived name */

static int spiderGroupIdCount = 0; /* derived name */

static int spiderGroupCount = 0; /* derived name */

static int reviveGroupIdCount = 0; /* derived name */

static int execFrame = 0; /* derived name */

static GObj *reviveMaster = 0; /* derived name */

static int reviveCounter = 0; /* derived name */

static int reviveDone = 0; /* derived name */

typedef struct { /* field names derived */
    GObj *group; /* 0x00 */
    int spider;  /* 0x04, the spider's index in the group */
} SpiderPair;    /* derived name */

typedef struct { /* field names derived */
    GObj *gobj;  /* 0x00 */
    int rev; /* 0x04, the enemy layout object locked for the revive, held as a word: typed GObj *, the store order of EntrySpiderGroupManager moves (measured) */
} SpiderGroupEnt; /* derived name */

/* the spiders found inside a revive range, the pairs picked out of them,
   the registered group ids, the group table and the group ids the revive
   walk works from */
static int spidersInRange[100]; /* derived name */

static SpiderPair spiderPairs[5]; /* derived name */

/* the registered groups' GObj handles, held as words: typed GObj *, the
   store order of EntrySpiderGroupManager moves (measured) */
static int spiderGroupIds[64]; /* derived name */

static SpiderGroupEnt spiderGroups[64]; /* derived name */

static GObj *reviveGroupIds[64]; /* derived name */

/* one RGBA tint per spider group, alpha 128 throughout */
static int spiderGroupColors[7][4] = {{127, 0, 0, 128}, {64, 127, 0, 128}, {0, 64, 127, 128},
                                      {0, 127, 0, 128}, {64, 0, 127, 128}, {127, 64, 0, 128},
                                      {64, 64, 64, 128}}; /* derived name */

inline void InitSpiderGroupManager(void)
{
    spiderGroupIdCount = 0;
    reviveGroupIdCount = 0;

    spiderGroupCount = 0;

    reviveMaster = 0;

    reviveNext = 0;

    execFrame = 0;

    reviveCounter = 0;
    reviveDone = 0;
}

inline GObj *getReviveEnemyGObj(int count)
{
    GObj *p = isysGObjSearchFromObjKindID_begin(4);
    int i;
    {
        for (i = 0; i < count; i++) {
            if (p == 0) {
                return 0;
            }
            p = isysGObjSearchFromObjKindID_next(p);
        }
    }
    return p;
}

inline void EntryRevivedSpiderGroupManager(GObj *group)
{
    int idx = spiderGroupIdCount;
    spiderGroupIdCount = idx + 1;
    spiderGroupIds[idx] = (int)group;
}

INCLUDE_ASM(EntrySpiderGroupManager);

inline void EntryToSpiderGroupManagerForReviveMaster(GObj *group, GObj *master)
{
    reviveGroupIds[reviveGroupIdCount++] = group;
    reviveMaster = master;
}

INCLUDE_ASM(tryToRevive);

INCLUDE_ASM(ExecSpiderGroupManager);

inline void DispAllSpiderGroups(void)
{
    int v = pad[0].flags;
    sgInfoLine = 0;
    if (v & 0x1000) {
        sgSelLine = sgSelLine - 1;
    }
    if (v & 0x4000) {
        sgSelLine = sgSelLine + 1;
    }
    {
        int i;
        for (i = 0; i < spiderGroupIdCount; i++) {
            DispAllMemberOfSpider((GObj *)spiderGroupIds[i], spiderGroupColors[i]);
        }
    }
}
