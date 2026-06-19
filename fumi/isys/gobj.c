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

/* m2c scaffold from asm/aug6/nonmatchings/fumi/isys/gobj/isysGetNbAllocedGObjs.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern char D_00551DE0[];
extern void *D_0062A308;
extern void *iosFree(void *pool, int size, char *file, int line);

void isysGetNbAllocedGObjs(unsigned int n) {
    struct GObj *base;
    char *p;
    unsigned int i;
    base = (struct GObj *)iosFree(D_0062A308, n * 0x174, D_00551DE0, 0xAE);
    D_0062BFAC = n;
    D_0062BFA8 = base;
    i = 0;
    if (n != 0) {
        p = (char *)base;
        do {
            *(int *)(p + 0x0) = 0;
            *(int *)(p + 0x15C) = 0;
            *(int *)(p + 0x8) = -1;
            *(int *)(p + 0x4) = -1;
            p += 0x174;
            i++;
        } while (i < n);
    }
}


extern void *D_006A2F50[];
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern char D_00551DE0[];
extern char D_0062C348[];
extern void isysGObjInit(int a0);
extern void isysGObjProcAddS(int a0);

void isysGObjAlloc(char *a0) {
    int kind = *(int *)(a0 + 0xC);
    int proc = *(int *)(a0 + 0x2C);
    char *p;
    if ((unsigned)(kind - 1) >= 0x42) goto init;
    p = (char *)D_006A2F50[kind];
    if (p == a0) {
        D_006A2F50[kind] = *(void **)(a0 + 0x3C);
        goto init;
    }
    if (p == 0) goto init;
    if (*(char **)(p + 0x3C) != a0) {
        do {
            if (p == 0) {
                func_001AAD00(D_00551DE0, 0x92);
                func_00260380(D_00551DE0, 0x92, D_0062C348);
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjRemove);

extern void *D_006A2F50[];
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern char D_00551DE0[];
extern char D_0062C348[];

void isysGObjKindTableAdd(char *a0) {
    int kind = *(int *)(a0 + 0xC);
    char *p;
    if ((unsigned)(kind - 1) >= 0x42) return;
    p = (char *)D_006A2F50[kind];
    if (p == a0) {
        D_006A2F50[kind] = *(void **)(a0 + 0x3C);
        return;
    }
    if (p == 0) return;
    if (*(char **)(p + 0x3C) != a0) {
        do {
            if (p == 0) {
                func_001AAD00(D_00551DE0, 0x92);
                func_00260380(D_00551DE0, 0x92, D_0062C348);
            }
            p = *(char **)(p + 0x3C);
        } while (*(char **)(p + 0x3C) != a0);
    }
    *(void **)(p + 0x10) = *(void **)(a0 + 0x3C);
}


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

void *isysGObjAddHead(int a0) {
    unsigned int i;
    for (i = 0; i < D_0062BFAC; i++) {
        char *e = (char *)D_0062BFA8 + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == 1 && *(int *)(e + 8) == a0)
            return e;
    }
    return 0;
}

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
