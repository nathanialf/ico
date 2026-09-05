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
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTarget);
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
