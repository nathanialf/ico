#include "common.h"

struct GObj__p4 { int unk0; int unk4; int unk8; char pad[0x168]; };

extern char *D_006BF380[];
void isysGObjKindTableInit(void) {
    memset(D_006BF380, 0, 0x118);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjInit);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", cut_gobj_link);
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemoveAll);
extern char D_0029C4F0[];
extern char *D_0029C510[];
void add_gobj_to_tail(int a0, int a1, int a2) {
    char *g = (char *)a0;
    unsigned char kind = a1;
    unsigned int val = a2;
    char *head;
    char *tail;
    char *p;
    g[0x18] = kind;
    *(unsigned int *)(g + 0x1C) = val;
    head = *(char **)(D_0029C4F0 + kind * 4);
    if (head == 0) {
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        return;
    }
    if (val < *(unsigned int *)(head + 0x1C)) {
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = head;
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(head + 0x14) = g;
        return;
    }
    tail = D_0029C510[kind];
    if (!(val < *(unsigned int *)(tail + 0x1C))) {
        *(char **)(g + 0x14) = tail;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        *(char **)(tail + 0x10) = g;
        return;
    }
    p = head;
    while (!(val < *(unsigned int *)(*(char **)(p + 0x10) + 0x1C))) {
        p = *(char **)(p + 0x10);
    }
    *(char **)(g + 0x14) = p;
    *(char **)(g + 0x10) = *(char **)(p + 0x10);
    *(char **)(p + 0x10) = g;
    *(char **)(*(char **)(g + 0x10) + 0x14) = g;
}
void add_gobj_to_head(char *g, int a1, int a2) {
    unsigned char kind = a1;
    unsigned int val = a2;
    char *head;
    char *tail;
    char *p;
    g[0x18] = kind;
    *(unsigned int *)(g + 0x1C) = val;
    head = *(char **)(D_0029C4F0 + kind * 4);
    if (head == 0) {
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        return;
    }
    if (!(*(unsigned int *)(head + 0x1C) < val)) {
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = head;
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(head + 0x14) = g;
        return;
    }
    tail = D_0029C510[kind];
    if (*(unsigned int *)(tail + 0x1C) < val) {
        *(char **)(g + 0x14) = tail;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        *(char **)(tail + 0x10) = g;
        return;
    }
    p = head;
    while (*(unsigned int *)(*(char **)(p + 0x10) + 0x1C) < val) {
        p = *(char **)(p + 0x10);
    }
    *(char **)(g + 0x14) = p;
    *(char **)(g + 0x10) = *(char **)(p + 0x10);
    *(char **)(p + 0x10) = g;
    *(char **)(*(char **)(g + 0x10) + 0x14) = g;
}
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
extern char *D_006BF380[];
extern char D_00551F30[];
extern char D_0063A608[];
void isysGObjRemove(char *g) {
    int kind = *(int *)(g + 0xC);
    char *proc = *(char **)(g + 0x2C);
    char *p;
    if ((unsigned int)(kind - 1) < 0x45) {
        p = D_006BF380[kind];
        if (p == g) {
            D_006BF380[kind] = *(char **)(g + 0x3C);
        } else if (p != 0) {
            while (*(char **)(p + 0x3C) != g) {
                if (p == 0) {
                    debug_assert(D_00551F30, 0x92);
                    __assert(D_00551F30, 0x92, D_0063A608);
                }
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x10) = *(char **)(g + 0x3C);
        }
    }
    cut_gobj_link((int)g);
    *(int *)g = 0;
    while (proc != 0) {
        isysGObjProcRemove(proc);
        proc = *(char **)(g + 0x2C);
    }
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjKindTableAdd);
extern char *D_006BF380[];
extern char D_00551F30[];
extern char D_0063A608[];
void isysGObjKindTableRemove(char *g) {
    int kind = *(int *)(g + 0xC);
    char *p;
    if ((unsigned int)(kind - 1) < 0x45) {
        p = D_006BF380[kind];
        if (p == g) {
            D_006BF380[kind] = *(char **)(g + 0x3C);
            return;
        }
        if (p == 0) return;
        while (*(char **)(p + 0x3C) != g) {
            if (p == 0) {
                debug_assert(D_00551F30, 0x92);
                __assert(D_00551F30, 0x92, D_0063A608);
            }
            p = *(char **)(p + 0x3C);
        }
        *(char **)(p + 0x10) = *(char **)(g + 0x3C);
    }
}
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

extern unsigned int D_0063A610__pn __asm__("D_0063A610");

void isysGObjActiveDlLink(int a0, int a1) {
    if (a1 == 0) {
        D_0063A610__pn &= ~(1 << a0);
    } else {
        D_0063A610__pn |= (1 << a0);
    }
}
