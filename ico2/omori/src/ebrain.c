#include "common.h"
#include "debug.h"
#include "gobj.h"
#include "act-game.h"
#include "boyact.h"
#include "generator.h"
#include "geometryManager.h"
#include "ebrain.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"

extern int eBrainBoyChaseCount;
extern int eBrainGirlChaseCount;

/* .sbss and .bss, owned by ebrain.o and reached only from this file (MAIN.MAP
   names no symbol in either run), each in the ROM's run order: how many
   enemies are registered against the boy and against the girl, the enemy
   holding the girl, and whether the boy's state makes every enemy wait; then
   the slot pool and the two registration lists. */
static int boyTargetNum;

static int girlTargetNum;

static void *girlHolder;

static int enemiesWait;

static int ebrainSlots[224];

extern StageLabelRange D_005F5D50[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern GenGeo D_002C2DC8[];

static inline void eBrainSetStatus(EBSlot *p, int newst)
{
    int st = p->f0;

    switch (st) {
    case 1:
        eBrainBoyChaseCount--;
        break;
    case 2:
        eBrainGirlChaseCount--;
        break;
    }
    switch (newst) {
    case 1:
        eBrainBoyChaseCount++;
        if (st != 1)
            p->f14 = 0;
        break;
    case 2:
        eBrainGirlChaseCount++;
        break;
    }
    p->f0 = newst;
}

static inline EBSlot *eBrainGetPacket(void *gop)
{
    int i;

    for (i = 0; i < 0x20; i++) {
        if (((EBSlot *)ebrainSlots)[i].f18 == gop)
            break;
    }
    if (i == 0x20)
        return 0;
    else
        return &((EBSlot *)ebrainSlots)[i];
}

inline void eBrainInit(void)
{
    int *p = ebrainSlots;
    int i;
    eBrainGirlChaseCount = 0;
    eBrainBoyChaseCount = 0;
    girlHolder = 0;
    p = (int *)((char *)p + 0x37C);
    enemiesWait = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}

inline int eBrainStatusSet(void *a0, int a1)
{
    EBSlot *slot;
    int i;
    if (a1 != 4)
        return 0;
    for (i = 0; i < 0x20; i++) {
        if (((EBSlot *)ebrainSlots)[i].f18 == 0)
            break;
    }
    if (i < 0x20)
        slot = &((EBSlot *)ebrainSlots)[i];
    else
        slot = 0;
    if (slot == 0) {
        debug_StdPrintfDummy("eBrainStatusSet: ebrain area over\n");
        return 0;
    }
    slot->f18 = a0;
    slot->f0 = 0;
    slot->f10 = 0;
    return (int)slot;
}

extern void *D_00639EA4;
extern void *D_00639EA8;

static EBSlot *boyTargets[32];

static EBSlot *girlTargets[32];

static inline void eBrainRegistTarget(EBSlot **list, int n, EBSlot *e, int w)
{
    int j;
    EBSlot *cur = e;
    EBSlot *t;
    float key = cur->dist[w];
    float tk;

    for (j = 0; j < n; j++) {
        t = list[j];
        tk = t->dist[w];

        if (key < tk) {
            list[j] = cur;
            cur = t;
            key = tk;
        }
    }
    list[j] = cur;
}

void eBrainProcess(void)
{
    float bpos[4];
    float gpos[4];
    float epos[4];
    float d[4];
    EBSlot *s;
    int i;

    girlTargetNum = 0;
    boyTargetNum = 0;

    if (D_00639EA4 == 0) {
        if (D_00639EA8 == 0)
            return;
    } else {
        enemiesWait = IsBoyStatus_EnemyMustWait();
        GetRootPosition(bpos, D_00639EA4);
    }

    if (D_00639EA8 != 0) {
        GetRootPosition(gpos, D_00639EA8);
    }

    for (i = 0; i < 0x20; i++) {
        s = &((EBSlot *)ebrainSlots)[i];
        if (s->f18 == 0)
            continue;

        GetRootPosition(epos, s->f18);
        sceVu0SubVector(d, epos, bpos);
        s->dist[0] = sceVu0InnerProduct(d, d);
        sceVu0SubVector(d, epos, gpos);
        s->dist[1] = sceVu0InnerProduct(d, d);

        if (s->f0 == 0) {
            if (D_00639EA4 != 0) {
                eBrainRegistTarget(boyTargets, boyTargetNum, s, 0);
                boyTargetNum = boyTargetNum + 1;
            }
            if (D_00639EA8 != 0) {
                eBrainRegistTarget(girlTargets, girlTargetNum, s, 1);
                girlTargetNum = girlTargetNum + 1;
            }
        } else if (s->f0 == 1) {
            s->f14++;
        }
    }
}

inline int GetStageFromLabel(int label)
{
    int stage = -1;
    int i;

    for (i = 0; i < 0x6A; i++) {
        if (label >= D_005F5D50[i].labelTop && label < D_005F5D50[i].labelEnd) {
            stage = i;
            break;
        }
    }
    if (!(stage > 0)) {
        debug_assert("src/ebrain.c", 472);
        __assert("src/ebrain.c", 472, "UseStageNo>0");
    }
    return stage;
}

inline int eBrainGetTargetGeneratorFromLabelStage(int label, int stage)
{
    int pri = -1;
    int no = -1;
    int i;
    int ret;
    int st;
    int f;

    ret = GetMotherGenerator(label);
    if (ret != -1)
        return ret;

    st = stage;
    for (i = D_005F5D50[st].labelTop; i < D_005F5D50[st].labelEnd; i++) {
        GenGeo *g = &D_002C2DC8[i];
        if (g->kind == 0x21) {
            f = g->f48 >> 17;
            f &= 1;
            if (pri < f) {
                pri = f;
                no = i;
            }
        }
    }
    if (!(no > 0)) {
        debug_assert("src/ebrain.c", 506);
        __assert("src/ebrain.c", 506, "GeneratorLabel>0");
    }
    return no;
}

int eBrainGetTargetGeneratorFromLabel(int label)
{
    int no = -1;
    int pri = -1;
    int stage;
    int i;
    int ret;
    int st;
    int f;

    ret = GetMotherGenerator(label);
    if (ret != -1)
        return ret;

    stage = -1;
    for (i = 0; i < 0x6A; i++) {
        if (label >= D_005F5D50[i].labelTop && label < D_005F5D50[i].labelEnd) {
            stage = i;
            break;
        }
    }
    if (!(stage > 0)) {
        debug_assert("src/ebrain.c", 472);
        __assert("src/ebrain.c", 472, "UseStageNo>0");
    }

    st = stage;
    for (i = D_005F5D50[st].labelTop; i < D_005F5D50[st].labelEnd; i++) {
        GenGeo *g = &D_002C2DC8[i];
        if (g->kind == 0x21) {
            f = g->f48 >> 17;
            f &= 1;
            if (pri < f) {
                pri = f;
                no = i;
            }
        }
    }
    if (!(no > 0)) {
        debug_assert("src/ebrain.c", 542);
        __assert("src/ebrain.c", 542, "GeneratorLabel>0");
    }
    return no;
}

static inline int eBrainCanSeeTarget(void *gop, void *target)
{
    float mypos[4];
    float tpos[4];

    if (target == 0)
        return 0;
    GetRootPosition(mypos, gop);
    GetRootPosition(tpos, target);
    return ACTCheckViewCl(gop, target, tpos, 180, 100.0f);
}

EBSlot *eBrainGetTarget(void *gop)
{
    EBSlot *p;
    int changed;

    p = eBrainGetPacket(gop);
    if (p == 0)
        return 0;

    switch (p->f10) {
    case 1:
    case 5:
        eBrainSetStatus(p, 1);
        break;
    case 2:
        eBrainSetStatus(p, 2);
        break;
    case 3:
        eBrainSetStatus(p, 5);
        break;
    case 4:
        eBrainSetStatus(p, 0);
        break;
    case 6:
        if (D_00639EA8 != 0) {
            eBrainSetStatus(p, 3);
        }
        break;
    case 7:
        eBrainSetStatus(p, 4);
        break;
    }
    p->f10 = 0;
    if (enemiesWait != 0 && p->f0 == 1) {
        eBrainSetStatus(p, 8);
    }

    do {
        changed = 0;
        switch (p->f0) {
        case 0: {
            int n;
            int cnt;
            int found;
            int boyIdx;
            int girlIdx;

            found = 0;
            cnt = 0;
            for (n = 0; n < boyTargetNum; n++) {
                EBSlot *e = boyTargets[n];
                if (p == e) {
                    found = 1;
                    break;
                }
                if (e != 0)
                    cnt++;
            }
            boyIdx = -1;
            if (found && cnt + eBrainBoyChaseCount <= 31)
                boyIdx = n;
            found = 0;
            cnt = 0;
            for (n = 0; n < girlTargetNum; n++) {
                EBSlot *e = girlTargets[n];
                if (p == e) {
                    found = 1;
                    break;
                }
                if (e != 0)
                    cnt++;
            }
            girlIdx = -1;
            if (found && cnt + eBrainGirlChaseCount <= 31)
                girlIdx = n;

            {
                int order[3];
                int i;

                memset(order, 0, sizeof(order));
                i = 0;
                if (boyIdx >= 0) {
                    if (girlIdx >= 0) {
                        if (boyTargets[boyIdx]->dist[0] < girlTargets[girlIdx]->dist[1]) {
                            order[0] = 1;
                            order[1] = 2;
                        } else {
                            order[0] = 2;
                            order[1] = 1;
                        }
                    } else {
                        order[0] = 1;
                    }
                } else if (girlIdx >= 0) {
                    order[0] = 2;
                }
                for (; order[i] != 0; i++) {
                    if (order[i] == 1) {
                        if (eBrainCanSeeTarget(gop, D_00639EA4)) {
                            eBrainSetStatus(p, 1);
                            break;
                        }
                    } else {
                        if (eBrainCanSeeTarget(gop, D_00639EA8)) {
                            eBrainSetStatus(p, 2);
                            break;
                        }
                    }
                }
            }
            if (p->f0 != 0) {
                boyTargets[boyIdx] = girlTargets[girlIdx] = 0;
                changed = 1;
            }
            break;
        }
        case 1:
            p->f04 = D_00639EA4;
            if (p->f14 >= 181) {
                if (p->dist[1] < p->dist[0] + 250000.0f) {
                    if (eBrainCanSeeTarget(gop, D_00639EA8)) {
                        eBrainSetStatus(p, 2);
                        changed = 1;
                    }
                }
            }
            break;
        case 2:
            p->f04 = D_00639EA8;
            break;
        case 5:
            p->f04 = D_00639EA8;
            if (p->dist[0] < 250000.0f) {
                if (eBrainCanSeeTarget(gop, D_00639EA4)) {
                    eBrainSetStatus(p, 1);
                    changed = 1;
                }
            }
            if (girlHolder == 0) {
                eBrainSetStatus(p, 1);
                changed = 1;
            }
            break;
        case 4:
            p->f04 = isysGObjSearchFromObjLayoutID(
                eBrainGetTargetGeneratorFromLabel(*(int *)((char *)gop + 8)));
            break;
        case 6:
            p->f04 = 0;
            break;
        case 3:
            if (eBrainCanSeeTarget(gop, D_00639EA8)) {
                eBrainSetStatus(p, 2);
                changed = 1;
            }
            break;
        case 8:
            p->f04 = D_00639EA4;
            if (enemiesWait == 0) {
                eBrainSetStatus(p, 0);
            }
            break;
        }
    } while (changed);

    if (girlHolder != 0 && girlHolder != gop && p->f0 == 2) {
        eBrainSetStatus(p, 5);
    }
    return p;
}

inline void eBrainSendMes(void *gop, int mes)
{
    EBSlot *p = eBrainGetPacket(gop);

    p->f10 = mes;
    switch (mes) {
    case 9:
        girlHolder = gop;
        break;
    case 10:
        if (girlHolder == gop)
            girlHolder = 0;
        eBrainSetStatus(p, 7);
        break;
    case 4:
    case 5:
        if (girlHolder == gop)
            girlHolder = 0;
        break;
    }
}
