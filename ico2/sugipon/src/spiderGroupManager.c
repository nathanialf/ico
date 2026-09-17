#include "common.h"
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

extern int D_0063BAE0;
extern int D_0063BAE4;
extern int D_0063BAE8;
extern int D_0063BAEC;
extern int D_0063BAF0;
extern int D_0063BAF4;
extern int D_0063BAF8;
extern int D_0063BAFC;

typedef struct {
    int group;    /* 0x00 */
    void *spider; /* 0x04 */
} SpiderPair;

typedef struct {
    void *gobj; /* 0x00 */
    int rev;    /* 0x04 */
} SpiderGroupEnt;

/* .bss, owned by spiderGroupManager.o (0x5B8, the run and MAIN.MAP's own size),
   in the ROM's run order: the spiders found inside a revive range, the pairs
   picked out of them, the registered group ids, the group table and the group
   ids the revive walk works from. */
static int spidersInRange[100];

static SpiderPair spiderPairs[5];

static int spiderGroupIds[64];

static SpiderGroupEnt spiderGroups[64];

static int reviveGroupIds[64];

extern int D_0028F8F4[];

/* one RGBA tint per spider group, alpha 0x80 throughout */
static int spiderGroupColors[7][4] = {{0x7F, 0x00, 0x00, 0x80}, {0x40, 0x7F, 0x00, 0x80},
                                      {0x00, 0x40, 0x7F, 0x80}, {0x00, 0x7F, 0x00, 0x80},
                                      {0x40, 0x00, 0x7F, 0x80}, {0x7F, 0x40, 0x00, 0x80},
                                      {0x40, 0x40, 0x40, 0x80}};

extern int D_0063BAC4;
extern int D_0063BADC;

inline void InitSpiderGroupManager(void)
{
    D_0063BAE4 = 0;
    D_0063BAEC = 0;

    D_0063BAE8 = 0;

    D_0063BAF4 = 0;

    D_0063BAE0 = 0;

    D_0063BAF0 = 0;

    D_0063BAF8 = 0;
    D_0063BAFC = 0;
}

inline int *getReviveEnemyGObj(int count)
{
    int *p = isysGObjSearchFromObjKindID_begin(4);
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

extern char D_0063BB00[];
extern void __assert(char *file, int line, char *expr);

inline void EntryRevivedSpiderGroupManager(int a0)
{
    int idx = D_0063BAE4;
    D_0063BAE4 = idx + 1;
    spiderGroupIds[idx] = a0;
}

/* listing lines 96-103 */
void EntrySpiderGroupManager(int gobj)
{
    int *p;

    spiderGroups[D_0063BAE8].gobj = (void *)gobj;
    p = getReviveEnemyGObj(D_0063BAE4);
    if (p != 0) {
        debug_StdPrintfDummy("LOCK %p for LABEL %d, ID:%d\n", p, p[2], D_0063BAE8);
        LockEnemyGenerate(p);
        *(int *)((char *)p + 0x16C) = 0;
    } else {
        debug_assertMessage(
            "src/spiderGroupManager.c", 85,
            "No valid enemy layout data for spider.\n(Lack of enemy layout for spider revive.)\n");
        __assert("src/spiderGroupManager.c", 85, D_0063BB00);
    }
    spiderGroups[D_0063BAE8].rev = (int)p;
    D_0063BAE8 = D_0063BAE8 + 1;
    EntryRevivedSpiderGroupManager(gobj);
}

inline void EntryToSpiderGroupManagerForReviveMaster(int a0, int a1)
{
    int idx = D_0063BAEC;
    int *p;
    int new_var;
    int *new_var2;
    new_var2 = &a1;
    D_0063BAF4 = *new_var2;
    p = reviveGroupIds + idx;
    new_var = idx;
    idx = new_var + 1;
    *p = a0;
    D_0063BAEC = idx;
}

/* listing lines 124-171 */
int tryToRevive(void)
{
    float pos[4];
    int k = 0;
    int i;
    int j;
    int n;
    void *p;

    if (D_0063BAF4 != 0) {
        GetRootPosition(pos, D_0063BAF4);
        pos[1] -= *(float *)(*(int *)(D_0063BAF4 + 0x15C) + 0x160);
        for (i = 0; i < D_0063BAEC; i++) {
            n = CheckSpidersInsideOfReviveRange(spidersInRange, reviveGroupIds[i], pos);
            if (n != 0) {
                for (j = 0; j < n; j++) {
                    spiderPairs[k].group = reviveGroupIds[i];
                    spiderPairs[k].spider = spidersInRange[j];
                    k++;
                    if (k == 5) {
                        if (D_0063BAE0 < D_0063BAE8) {
                            int m;

                            p = spiderGroups[D_0063BAE0].rev;
                            UnlockEnemyGenerate(p);
                            debug_StdPrintfDummy("UNLOCK %p: (id:%d)\n", p, D_0063BAE0);
                            *(int *)((char *)p + 0x16C) = 1;
                            if (DirectCallEnemy(p, 0, pos, ZUnitVector, 0) == 0) {
                                return 0;
                            }
                            ExecuteSEPackage(p, 107);
                            for (m = 0; m < 5; m++) {
                                SetAP1DeadStatus(DeleteSpiderFromLayoutGroup(
                                    spiderPairs[m].group, spiderPairs[m].spider));
                            }
                            SetSpiderGroupReviveStatus(spiderGroups[D_0063BAE0].gobj);
                            D_0063BAE0++;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

extern int D_0063B138;
extern int D_0028F4C0[];

void ExecSpiderGroupManager(void)
{
    int i;
    int total;
    int groups;

    if ((D_0063BAF0 & 0xF) == 0) {
        tryToRevive();
    }

    if (D_0063BAE4 != 0 && D_0063BAFC == 0) {
        groups = 0;
        total = 0;
        for (i = 0; i < D_0063BAE4; i++) {
            int n = GetAliveSpiders(spiderGroupIds[i]);
            if (n >= 0) {
                total += n;
                groups++;
            }
        }

        if (groups != 0 && total > 0 && total < 5) {
            D_0063BAF8 = D_0063BAF8 + 1;
            if (D_0063B138 != 0) {
                debug_PrintfDummy(400, 120, 0xFFFFFFFF, "COUNTER %d/%d", D_0063BAF8,
                                  (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 45);
            }
        }

        if ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 45 < D_0063BAF8) {
            for (i = 0; i < D_0063BAE4; i++) {
                if (GetAliveSpiders(spiderGroupIds[i]) >= 0) {
                    DeadAllSpiders(spiderGroupIds[i]);
                }
            }
            D_0063BAFC = 1;
        }

        if (D_0063B138 != 0) {
            if (groups != 0) {
                debug_PrintfDummy(400, 110, 0xFFFFFFFF, "REMAIN %d", total);
            } else {
                debug_PrintfDummy(400, 110, 0xFFFFFFFF, "NO GROUP WAKEUPED");
            }
        }
    }

    D_0063BAF0 = D_0063BAF0 + 1;
}

inline void DispAllSpiderGroups(void)
{
    int v = D_0028F8F4[0];
    D_0063BADC = 0;
    if (v & 0x1000) {
        D_0063BAC4 = D_0063BAC4 - 1;
    }
    if (v & 0x4000) {
        D_0063BAC4 = D_0063BAC4 + 1;
    }
    {
        int i;
        for (i = 0; i < D_0063BAE4; i++) {
            DispAllMemberOfSpider(spiderGroupIds[i], spiderGroupColors[i]);
        }
    }
}
