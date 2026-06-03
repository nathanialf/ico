#include "common.h"

int InitSpiderLayoutGeo(void *a0, void *a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(unsigned short *)((char *)q + 0x20) = *(unsigned short *)((char *)a1 + 0x30);
    *(int *)((char *)q + 0x24) = *(short *)((char *)a1 + 0x32);
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", WakeUpLayoutedSpiders);

void getCallPoint(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(int *)((char *)q + 0x34) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", CallSpidersToReviveEnemy);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", SpiderLayoutGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DispAllMemberOfSpider);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", SetSpiderGroupReviveStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", DeleteSpiderFromLayoutGroup);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", GetNearestOfLayoutSpiders);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", CheckSpidersInsideOfReviveRange);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", RestoreSpiderLayoutGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", RestoreSpiderLayoutExtGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spider", MemorySpiderLayout);
