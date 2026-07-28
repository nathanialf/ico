#include "common.h"


struct GObj { int unk0; int unk4; int unk8; char pad[0x168]; };
extern unsigned int D_00633CA4;
extern struct GObj *D_00633CA0;
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableInit);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjInit);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", cut_gobj_link);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemoveAll);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", add_gobj_to_tail);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", add_gobj_to_head);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjMove);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjMoveHead);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAddAfterGObj);

int isysGObjAddBeforeGObj(void)
{
    int result = 0;
    unsigned int i;
    for (i = 0; i < D_00633CA4; i++) {
        if (*(int *)((char *)D_00633CA0 + i * 0x174) != 0) {
            result++;
        }
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGetNbAllocedGObjs);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAlloc);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemove);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableAdd);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableRemove);

extern char D_00281A70[];
extern void isysGObjInit(int a0);

void isysGObjMoveAfterGObj(int self, int other)
{
    unsigned char t;
    int u;
    isysGObjInit(self);
    t = *(unsigned char *)(other + 0x18);
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x14);
    *(int *)(self + 0x10) = other;
    *(int *)(self + 0x14) = u;
    *(int *)(other + 0x14) = self;
    *(int *)(self + 0x1C) = *(int *)(other + 0x1C);
    if (*(int *)(self + 0x14) == 0) {
        *(int *)(D_00281A70 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjMoveBeforeGObj);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAdd);

void *isysGObjAddHead(int a0) {
    unsigned int i;
    for (i = 0; i < D_00633CA4; i++) {
        char *e = (char *)D_00633CA0 + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == 1 && *(int *)(e + 8) == a0)
            return e;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjSearchFromObjLayoutID);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjSearchFromObjKindID_begin);

