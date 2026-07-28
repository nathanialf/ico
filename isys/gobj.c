#include "common.h"

struct GObj__p4 {
    struct GObj__p4 *f_0;       /* 0x00 */
    int          f_4;       /* 0x04 */
    int          f_8;       /* 0x08 */
    char         pad_C[4];  /* 0x0C */
    struct GObj__p4 *f_10;      /* 0x10 */
    struct GObj__p4 *f_14;      /* 0x14 */
    unsigned char f_18;     /* 0x18 */
    char         pad_19[3]; /* 0x19 */
    int          f_1C;      /* 0x1C */
    char         pad_20[8]; /* 0x20 */
    int          f_28;      /* 0x28 */
    int          f_2C;      /* 0x2C */
    int          f_30;      /* 0x30 */
    char         pad_34[0x24]; /* 0x34 */
    int          f_58;      /* 0x58 */
    char         pad_5C[0x100]; /* 0x5C */
    int          f_15C;     /* 0x15C */
    char         pad_160[4]; /* 0x160 */
    int          f_164;     /* 0x164 */
    char         pad_168[8]; /* 0x168 */
    int          f_170;     /* 0x170 */
};


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

extern int D_006321C0;
extern struct GObj__p4 *D_00633CA0__p4 __asm__("D_00633CA0");

void *isysGObjSearchFromObjKindID_begin(struct GObj__p4 *g)
{
    struct GObj__p4 *p;
    struct GObj__p4 *end;
    int kind;

    if (D_006321C0 == 0) goto direct;
    p = g;
    end = &D_00633CA0__p4[D_00633CA4 - 1];
    kind = *(int *)g->pad_C;
    while (p != end) {
        p++;
        if (p->f_4 == 1 && *(int *)p->pad_C == kind) {
            goto found;
        }
    }
    return 0;
found:
    return p;
direct:
    return *(void **)(g->pad_34 + 8);
}

