#include "common.h"

typedef struct EBSlot {
    unsigned short f0;          /* 0x00 status */
    char pad2[2];
    void *f04;                  /* 0x04 target GObj */
    float f08;                  /* 0x08 */
    float f0C;                  /* 0x0C */
    int f10;                    /* 0x10 message */
    int f14;                    /* 0x14 */
    void *f18;                  /* 0x18 owner GObj */
} EBSlot;
extern int eBrainBoyChaseCount;
extern int eBrainGirlChaseCount;
extern void *D_0063C2CC;
extern int D_0063C2D0;
extern int D_006E6750[];
extern char D_00555580[];
extern void debug_StdPrintfDummy(const char *);
typedef struct StageLabelRange {
    char pad0[0x128];
    int labelTop;               /* 0x128 */
    int labelEnd;               /* 0x12C */
    char pad130[0x194 - 0x130];
} StageLabelRange;
extern StageLabelRange D_005F5D50[];
extern char D_005555A8[];
extern char D_005555B8[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
typedef struct GenGeo {
    char pad0[0x46];
    unsigned char kind;         /* 0x46 */
    char pad47[1];
    unsigned int f48;           /* 0x48 */
} GenGeo;
extern GenGeo D_002C2DC8[];
extern char D_005555C8[];
extern int GetMotherGenerator(int label);
/* prototypes: their order is the inline tail's emission order */
void eBrainInit(void);
int eBrainStatusSet(void *a0, int a1);
void eBrainSendMes(void *gop, int mes);
int GetStageFromLabel(int label);
int eBrainGetTargetGeneratorFromLabelStage(int label, int stage);
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
        if (st != 1) p->f14 = 0;
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
        if (((EBSlot *)D_006E6750)[i].f18 == gop) break;
    }
    if (i == 0x20)
        return 0;
    else
        return &((EBSlot *)D_006E6750)[i];
}
inline void eBrainInit(void)
{
    int *p = D_006E6750;
    int i;
    eBrainGirlChaseCount = 0;
    eBrainBoyChaseCount = 0;
    D_0063C2CC = 0;
    p = (int *)((char *)p + 0x37C);
    D_0063C2D0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}
inline int eBrainStatusSet(void *a0, int a1) {
    EBSlot *slot;
    int i;
    if (a1 != 4) return 0;
    for (i = 0; i < 0x20; i++) {
        if (((EBSlot *)D_006E6750)[i].f18 == 0) break;
    }
    if (i < 0x20) slot = &((EBSlot *)D_006E6750)[i];
    else slot = 0;
    if (slot == 0) {
        debug_StdPrintfDummy(D_00555580);
        return 0;
    }
    slot->f18 = a0;
    slot->f0 = 0;
    slot->f10 = 0;
    return (int)slot;
}
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainProcess);
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
        debug_assert(D_005555A8, 0x1D8);
        __assert(D_005555A8, 0x1D8, D_005555B8);
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
        debug_assert(D_005555A8, 0x1FA);
        __assert(D_005555A8, 0x1FA, D_005555C8);
    }
    return no;
}
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabel);
extern void *D_00639EA4;
extern void *D_00639EA8;
extern int D_0063C2C4;
extern int D_0063C2C8;
extern EBSlot *D_006E6AD0[];
extern EBSlot *D_006E6B50[];
extern float D_006391D8;
extern float D_006391DC;
extern void GetRootPosition(void *out, void *gobj);
extern int ACTCheckViewCl(void *gop, void *target, void *pos, int deg, float dist);
extern void *memset(void *dst, int c, int n);
extern int eBrainGetTargetGeneratorFromLabel(int label);
extern void *isysGObjSearchFromObjLayoutID(int id);

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
    if (D_0063C2D0 != 0 && p->f0 == 1) {
        eBrainSetStatus(p, 8);
    }

    do {
        changed = 0;
        switch (p->f0) {
        case 0:
        {
            int n;
            int cnt;
            int found;
            int boyIdx;
            int girlIdx;

            found = 0;
            cnt = 0;
            for (n = 0; n < D_0063C2C4; n++) {
                EBSlot *e = D_006E6AD0[n];
                if (p == e) {
                    found = 1;
                    break;
                }
                if (e != 0) cnt++;
            }
            boyIdx = -1;
            if (found && cnt + eBrainBoyChaseCount <= 31) boyIdx = n;
            found = 0;
            cnt = 0;
            for (n = 0; n < D_0063C2C8; n++) {
                EBSlot *e = D_006E6B50[n];
                if (p == e) {
                    found = 1;
                    break;
                }
                if (e != 0) cnt++;
            }
            girlIdx = -1;
            if (found && cnt + eBrainGirlChaseCount <= 31) girlIdx = n;

            {
                int order[3];
                int i;

                memset(order, 0, sizeof(order));
                i = 0;
                if (boyIdx >= 0) {
                    if (girlIdx >= 0) {
                        if (D_006E6AD0[boyIdx]->f08 < D_006E6B50[girlIdx]->f0C) {
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
                D_006E6AD0[boyIdx] = D_006E6B50[girlIdx] = 0;
                changed = 1;
            }
            break;
        }
        case 1:
            p->f04 = D_00639EA4;
            if (p->f14 >= 181) {
                if (p->f0C < p->f08 + D_006391D8) {
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
            if (p->f08 < D_006391DC) {
                if (eBrainCanSeeTarget(gop, D_00639EA4)) {
                    eBrainSetStatus(p, 1);
                    changed = 1;
                }
            }
            if (D_0063C2CC == 0) {
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
            if (D_0063C2D0 == 0) {
                eBrainSetStatus(p, 0);
            }
            break;
        }
    } while (changed);

    if (D_0063C2CC != 0 && D_0063C2CC != gop && p->f0 == 2) {
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
        D_0063C2CC = gop;
        break;
    case 10:
        if (D_0063C2CC == gop) D_0063C2CC = 0;
        eBrainSetStatus(p, 7);
        break;
    case 4:
    case 5:
        if (D_0063C2CC == gop) D_0063C2CC = 0;
        break;
    }
}
