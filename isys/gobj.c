#include "common.h"

struct GObj__p4 { int unk0; int unk4; int unk8; char pad[0x168]; };

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableInit);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjInit);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", cut_gobj_link);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemoveAll);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", add_gobj_to_tail);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", add_gobj_to_head);
extern void add_gobj_to_tail(int a0, int a1, int a2);
extern void cut_gobj_link(int a0);

void isysGObjMove(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_link(a0);
    return add_gobj_to_tail(a0, s1, new_var);
}
extern void add_gobj_to_head(char *a0, int a1, int a2);

void isysGObjMoveHead(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_link(a0);
    return add_gobj_to_head(a0, s1, new_var);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAddAfterGObj);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAddBeforeGObj);
extern struct GObj__pn *D_0063C1A8;
extern unsigned int D_0063C1AC;

int isysGetNbAllocedGObjs(void)
{
    int result = 0;
    unsigned int i;
    for (i = 0; i < D_0063C1AC; i++) {
        if (*(int *)((char *)D_0063C1A8 + i * 0x174) != 0) {
            result++;
        }
    }
    return result;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAlloc);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemove);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableAdd);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableRemove);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjMoveAfterGObj);
extern char D_0029C4F0[];
extern void cut_gobj_link(int a0);

void isysGObjMoveBeforeGObj(int self, int other)
{
    unsigned char t;
    int u;
    cut_gobj_link(self);
    t = *(unsigned char *)(other + 0x18);
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x14);
    *(int *)(self + 0x10) = other;
    *(int *)(self + 0x14) = u;
    *(int *)(other + 0x14) = self;
    *(int *)(self + 0x1C) = *(int *)(other + 0x1C);
    if (*(int *)(self + 0x14) == 0) {
        *(int *)(D_0029C4F0 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAdd);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjAddHead);
void *isysGObjSearchFromObjLayoutID(int a0) {
    unsigned int i;
    for (i = 0; i < D_0063C1AC; i++) {
        char *e = (char *)D_0063C1A8 + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == 1 && *(int *)(e + 8) == a0)
            return e;
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjSearchFromObjKindID_begin);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjSearchFromObjKindID_next);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjSearchFromLabelTypeID);
extern struct GObj__p4 *D_0063C1A8__pn __asm__("D_0063C1A8");

struct GObj__p4 *isysGObjGetExist_begin(void)
{
    struct GObj__p4 *start = D_0063C1A8__pn - 1;
    struct GObj__p4 *end = (struct GObj__p4 *)((char *)D_0063C1A8__pn + (D_0063C1AC * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjGetExist_next);
extern int D_0063A60C;

void isysGObjActiveLink(int bit, int set)
{
    if (set != 0) goto set_path;
    D_0063A60C &= ~(1 << bit);
    return;
set_path:
    D_0063A60C |= (1 << bit);
}
extern int D_0063A610;

void isysGObjActiveDlLink(int bit, int set)
{
    if (set != 0) goto set_path;
    D_0063A610 &= ~(1 << bit);
    return;
set_path:
    D_0063A610 |= (1 << bit);
}
