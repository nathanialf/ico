#include "common.h"

/* spider 0x7F0 view (local; 0x20/0x24 also read as packed ushort elsewhere) */
typedef struct { char _0[0x20]; unsigned short f_20; char _pad22[2]; int f_24; char _pad28[0xC]; int f_34; } SpiderGeo;

int InitSpiderLayoutGeo(void *a0, void *a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    q->f_20 = *(unsigned short *)((char *)a1 + 0x30);
    q->f_24 = *(short *)((char *)a1 + 0x32);
    return 1;
}

int WakeUpLayoutedSpiders(void *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    unsigned short *q = *(unsigned short **)((char *)p + 0x7F0);
    *(unsigned short *)a0 = q[0x10];
    *(unsigned short *)((char *)a0 + 2) = q[0x12];
    return 1;
}

void getCallPoint(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    q->f_34 = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", CallSpidersToReviveEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", SpiderLayoutGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DispAllMemberOfSpider);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", SetSpiderGroupReviveStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DeleteSpiderFromLayoutGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", GetNearestOfLayoutSpiders);

extern void func_001AB9F8(void *a0);
extern void debug_assertMessage(char *fmt, int val);
extern char D_0062D740[];

void CheckSpidersInsideOfReviveRange(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    SpiderGeo *q = *(SpiderGeo **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x3C) = 1;
    func_001AB9F8(a0);
    debug_assertMessage(D_0062D740, *(int *)((char *)a0 + 0x8));
}

int RestoreSpiderLayoutGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    int *r = *(int **)((char *)q + 0x24);
    int v = r[a1];
    r[a1] = 0;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", RestoreSpiderLayoutExtGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", MemorySpiderLayout);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_10;  /* 0x10 */
} S_0061D730;  /* stride 0x20 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612B70;  /* stride 0x4 */

/* end struct shapes */
