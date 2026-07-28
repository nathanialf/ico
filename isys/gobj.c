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

extern char D_00557A10__p4[] __asm__("D_00557A10");
extern char D_006321C8[];
extern struct GObj__p4 *D_00633CA0__p4 __asm__("D_00633CA0");
extern void *D_006A93D0[];
extern void func_0013DD88(void);
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern void isysGObjInit(int a0);
extern void isysGObjProcAddS(int a0);

void cut_gobj_link(void) {
    unsigned int i = 0;
    if (D_00633CA4 != 0) {
        void **list = D_006A93D0;
        char *file = D_00557A10__p4;
        int stride;
        do {
            char *gobj;
            int kind;
            int proc;
            char *p;
            int base;
            do {
                stride = 0x174;
            } while (0);
            base = (int)D_00633CA0__p4;
            gobj = (char *)(i * stride + base);
            if (*(int *)gobj != 0) {
                kind = *(int *)(gobj + 0xC);
                proc = *(int *)(gobj + 0x2C);
                if ((unsigned)(kind - 1) < 0x43) {
                    p = (char *)list[kind];
                    if (p == gobj) {
                        list[kind] = *(void **)(gobj + 0x3C);
                    } else if (p != 0) {
                        if (*(char **)(p + 0x3C) != gobj) {
                            do {
                                if (p == 0) {
                                    func_001AD768(file, 0x92);
                                    func_00263FF0(file, 0x92, D_006321C8);
                                }
                                p = *(char **)(p + 0x3C);
                            } while (*(char **)(p + 0x3C) != gobj);
                        }
                        *(void **)(p + 0x10) = *(void **)(gobj + 0x3C);
                    }
                }
                isysGObjInit((int)gobj);
                *(int *)gobj = 0;
                while (proc != 0) {
                    isysGObjProcAddS(proc);
                    proc = *(int *)(gobj + 0x2C);
                }
            }
            i++;
            stride = 0x174;
        } while (i < D_00633CA4);
    }
    func_0013DD88();
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj", isysGObjRemoveAll);

INCLUDE_ASM("asm/nonmatchings/isys/gobj", add_gobj_to_tail);

extern void isysGObjInit(int a0);
extern void isysGObjRemoveAll(int a0, int a1, int a2);

void add_gobj_to_head(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjInit(a0);
    return isysGObjRemoveAll(a0, s1, new_var);
}

extern void add_gobj_to_tail(char *a0, int a1, int a2);

void isysGObjMove(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjInit(a0);
    return add_gobj_to_tail(a0, s1, new_var);
}

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

extern char D_00557A10__p4[] __asm__("D_00557A10");
extern char D_006321C8[];
extern void *D_006A93D0[];
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);
extern void isysGObjProcAddS(int a0);

void isysGObjAlloc(char *a0) {
    int kind = *(int *)(a0 + 0xC);
    int proc = *(int *)(a0 + 0x2C);
    char *p;
    if ((unsigned)(kind - 1) >= 0x43) goto init;
    p = (char *)D_006A93D0[kind];
    if (p == a0) {
        D_006A93D0[kind] = *(void **)(a0 + 0x3C);
        goto init;
    }
    if (p == 0) goto init;
    if (*(char **)(p + 0x3C) != a0) {
        do {
            if (p == 0) {
                func_001AD768(D_00557A10__p4, 0x92);
                func_00263FF0(D_00557A10__p4, 0x92, D_006321C8);
            }
            p = *(char **)(p + 0x3C);
        } while (*(char **)(p + 0x3C) != a0);
    }
    *(void **)(p + 0x10) = *(void **)(a0 + 0x3C);
init:
    isysGObjInit((int)a0);
    *(int *)a0 = 0;
    while (proc != 0) {
        isysGObjProcAddS(proc);
        proc = *(int *)(a0 + 0x2C);
    }
}

extern int D_006321C0;
extern void *D_006A93D0[];
extern void isysGObjKindTableAdd(char *a0);
extern void *isysGObjSearchFromObjKindID_begin(struct GObj__p4 *g);
extern void *isysGObjSearchFromObjLayoutID(int id);

void isysGObjRemove(char *a0, int a1)
{
    char *p;
    int in_range;

    if (D_006321C0 != 0) {
        *(int *)(a0 + 0xC) = a1;
        return;
    }
    p = isysGObjSearchFromObjLayoutID(*(int *)(a0 + 0xC));
    do {
        in_range = (unsigned int)a1 < 0x44;
    } while (0);
    while (p != 0) {
        if (p == a0) {
            isysGObjKindTableAdd(a0);
            break;
        }
        isysGObjSearchFromObjKindID_begin((struct GObj__p4 *)p);
    }
    *(int *)(a0 + 0xC) = a1;
    if (in_range) {
        if (D_006A93D0[a1] == 0) {
            D_006A93D0[a1] = a0;
        } else {
            p = (char *)D_006A93D0[a1];
            while (*(char **)(p + 0x3C) != 0) {
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x3C) = a0;
        }
        *(int *)(a0 + 0x3C) = 0;
    }
}

extern char D_00557A10[];
extern char D_006321C8[];
extern void *D_006A93D0[];
extern void func_001AD768(char *a0, int a1);
extern void func_00263FF0(char *a0, int a1, char *a2);

void isysGObjKindTableAdd(char *a0) {
    int kind = *(int *)(a0 + 0xC);
    char *p;
    if ((unsigned)(kind - 1) >= 0x43) return;
    p = (char *)D_006A93D0[kind];
    if (p == a0) {
        D_006A93D0[kind] = *(void **)(a0 + 0x3C);
        return;
    }
    if (p == 0) return;
    if (*(char **)(p + 0x3C) != a0) {
        do {
            if (p == 0) {
                func_001AD768(D_00557A10, 0x92);
                func_00263FF0(D_00557A10, 0x92, D_006321C8);
            }
            p = *(char **)(p + 0x3C);
        } while (*(char **)(p + 0x3C) != a0);
    }
    *(void **)(p + 0x10) = *(void **)(a0 + 0x3C);
}

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

extern int D_006321C0;
extern struct GObj__p4 *D_00633CA0__p4 __asm__("D_00633CA0");
extern void *D_006A93D0[];

void *isysGObjSearchFromObjLayoutID(int id)
{
    struct GObj__p4 *p;
    struct GObj__p4 *end;

    if (D_006321C0 == 0) goto table;
    p = D_00633CA0__p4 - 1;
    end = &D_00633CA0__p4[D_00633CA4 - 1];
    while (p != end) {
        p++;
        if (p->f_4 == 1 && *(int *)p->pad_C == id) {
            goto found;
        }
    }
ret0:
    return 0;
found:
    return p;
table:
    if ((unsigned)(id - 1) < 0x43) {
        return D_006A93D0[id];
    }
    goto ret0;
}

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

