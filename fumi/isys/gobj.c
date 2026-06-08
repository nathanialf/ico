#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjKindTableInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", cut_gobj_link);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjRemoveAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", add_gobj_to_tail);

extern void isysGObjInit(int a0);
extern int  isysGObjRemoveAll(int a0, int a1, int a2);

void add_gobj_to_head(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjInit(a0);
    return isysGObjRemoveAll(a0, s1, new_var);
}

extern int  add_gobj_to_tail(int a0, int a1, int a2);

void isysGObjMove(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjInit(a0);
    return add_gobj_to_tail(a0, s1, new_var);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMoveHead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAddAfterGObj);

extern struct GObj *D_0062BFA8;
extern unsigned int D_0062BFAC;

int isysGObjAddBeforeGObj(void)
{
    int result = 0;
    unsigned int i;
    for (i = 0; i < D_0062BFAC; i++) {
        if (*(int *)((char *)D_0062BFA8 + i * 0x174) != 0) {
            result++;
        }
    }
    return result;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGetNbAllocedGObjs);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAlloc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjRemove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjKindTableAdd);


extern char D_0027DE10[];

void isysGObjKindTableRemove(int self, int other)
{
    int u, w;
    unsigned char t;
    isysGObjInit(self);
    t = *(unsigned char *)(other + 0x18);
    *(int *)(self + 0x14) = other;
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x10);
    w = *(int *)(other + 0x1C);
    *(int *)(self + 0x10) = u;
    *(int *)(other + 0x10) = self;
    *(int *)(self + 0x1C) = w;
    if (*(int *)(self + 0x10) == 0) {
        *(int *)(D_0027DE10 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}


extern char D_0027DDF0[];

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
        *(int *)(D_0027DDF0 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMoveBeforeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAddHead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjSearchFromObjLayoutID);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjSearchFromObjKindID_begin);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A2F50;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE10;  /* stride 0x4 */

/* end struct shapes */
