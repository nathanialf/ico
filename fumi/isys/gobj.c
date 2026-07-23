#include "common.h"
/* isys/gobj .rodata — __FILE__ + GObj alloc assert strings, VMA 0x551DE0..0x551E28 */
const char D_00551DE0[0x10] = "isys/gobj.c";
const char D_00551DF0[0x10] = "isys:null GObj\n";
const char D_00551E00[0x28] = "isys:not enough memory for GObj\n";
char D_0027DE10[0x20] = {0};  /* active-GObj pointer table (.data), VMA 0x27DE10 */

extern char D_0027DDF0[];
extern unsigned int D_0062A4CC;
extern unsigned int D_0062A4D0;
extern void isysGetNbAllocedGObjs(unsigned int n);
extern void func_0013D870(void);

void isysGObjKindTableInit(unsigned int n)
{
    int i;

    for (i = 0; i < 8; i++) {
        ((int *)D_0027DDF0)[i] = 0;
        ((int *)D_0027DE10)[i] = 0;
    }
    isysGetNbAllocedGObjs(n);
    D_0062A4CC = 0;
    D_0062A4D0 = 0;
    func_0013D870();
}


extern void debug_assertMessage();

void isysGObjInit(int a0)
{
    if (a0 == 0) {
        debug_assertMessage(D_00551DF0);
        return;
    }
    if (*(int *)(a0 + 0x14) == 0) {
        if (*(int *)(a0 + 0x10) == 0) goto tables;
    } else {
        *(int *)(*(int *)(a0 + 0x14) + 0x10) = *(int *)(a0 + 0x10);
    }
    if (*(int *)(a0 + 0x10) != 0) {
        *(int *)(*(int *)(a0 + 0x10) + 0x14) = *(int *)(a0 + 0x14);
    }
tables:
    if (a0 == *(int *)(D_0027DDF0 + *(unsigned char *)(a0 + 0x18) * 4)) {
        *(int *)(D_0027DDF0 + *(unsigned char *)(a0 + 0x18) * 4) = *(int *)(a0 + 0x10);
    }
    if (a0 == *(int *)(D_0027DE10 + *(unsigned char *)(a0 + 0x18) * 4)) {
        *(int *)(D_0027DE10 + *(unsigned char *)(a0 + 0x18) * 4) = *(int *)(a0 + 0x14);
    }
}


extern void *D_006A2F50[];
extern char D_0062C348[];
extern struct GObj *D_0062BFA8;
extern unsigned int D_0062BFAC;
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
extern void isysGObjInit(int a0);
extern void isysGObjProcAddS(int a0);
extern void func_0013D870(void);

void cut_gobj_link(void) {
    unsigned int i = 0;
    if (D_0062BFAC != 0) {
        void **list = D_006A2F50;
        char *file = D_00551DE0;
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
            base = (int)D_0062BFA8;
            gobj = (char *)(i * stride + base);
            if (*(int *)gobj != 0) {
                kind = *(int *)(gobj + 0xC);
                proc = *(int *)(gobj + 0x2C);
                if ((unsigned)(kind - 1) < 0x42) {
                    p = (char *)list[kind];
                    if (p == gobj) {
                        list[kind] = *(void **)(gobj + 0x3C);
                    } else if (p != 0) {
                        if (*(char **)(p + 0x3C) != gobj) {
                            do {
                                if (p == 0) {
                                    func_001AAD00(file, 0x92);
                                    func_00260380(file, 0x92, D_0062C348);
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
        } while (i < D_0062BFAC);
    }
    func_0013D870();
}


void isysGObjRemoveAll(int a0, int a1, int a2)
{
    int head, tail, p, q;

    a1 &= 0xFF;
    *(unsigned char *)(a0 + 0x18) = a1;
    *(int *)(a0 + 0x1C) = a2;
    head = (int)((void **)D_0027DDF0)[a1];
    if (head == 0) {
        *(int *)(D_0027DDF0 + a1 * 4) = a0;
        *(int *)(a0 + 0x14) = 0;
        *(int *)(a0 + 0x10) = 0;
        *(int *)(D_0027DE10 + a1 * 4) = a0;
        return;
    }
    if ((unsigned int)a2 < *(unsigned int *)(head + 0x1C)) {
        *(int *)(a0 + 0x14) = 0;
        *(int *)(a0 + 0x10) = head;
        *(int *)(D_0027DDF0 + a1 * 4) = a0;
        *(int *)(head + 0x14) = a0;
        return;
    }
    tail = (int)((void **)D_0027DE10)[a1];
    if ((unsigned int)a2 >= *(unsigned int *)(tail + 0x1C)) {
        *(int *)(a0 + 0x14) = tail;
        *(int *)(a0 + 0x10) = 0;
        *(int *)(D_0027DE10 + a1 * 4) = a0;
        *(int *)(tail + 0x10) = a0;
        return;
    }
    p = head;
    for (;;) {
        q = *(int *)(p + 0x10);
        if ((unsigned int)a2 < *(unsigned int *)(q + 0x1C)) {
            break;
        }
        p = q;
    }
    *(int *)(a0 + 0x14) = p;
    *(int *)(a0 + 0x10) = *(int *)(p + 0x10);
    *(int *)(p + 0x10) = a0;
    *(int *)(*(int *)(a0 + 0x10) + 0x14) = a0;
}


void add_gobj_to_tail(char *a0, int a1, int a2)
{
    int head, tail, p, q;

    a1 &= 0xFF;
    *(unsigned char *)(a0 + 0x18) = a1;
    *(int *)(a0 + 0x1C) = a2;
    head = (int)((void **)D_0027DDF0)[a1];
    if (head == 0) {
        *(int *)(D_0027DDF0 + a1 * 4) = (int)a0;
        *(int *)(a0 + 0x14) = 0;
        *(int *)(a0 + 0x10) = 0;
        *(int *)(D_0027DE10 + a1 * 4) = (int)a0;
        return;
    }
    if (*(unsigned int *)(head + 0x1C) >= (unsigned int)a2) {
        *(int *)(a0 + 0x14) = 0;
        *(int *)(a0 + 0x10) = head;
        *(int *)(D_0027DDF0 + a1 * 4) = (int)a0;
        *(int *)(head + 0x14) = (int)a0;
        return;
    }
    tail = (int)((void **)D_0027DE10)[a1];
    if (*(unsigned int *)(tail + 0x1C) < (unsigned int)a2) {
        *(int *)(a0 + 0x14) = tail;
        *(int *)(a0 + 0x10) = 0;
        *(int *)(D_0027DE10 + a1 * 4) = (int)a0;
        *(int *)(tail + 0x10) = (int)a0;
        return;
    }
    p = head;
    for (;;) {
        q = *(int *)(p + 0x10);
        if (*(unsigned int *)(q + 0x1C) >= (unsigned int)a2) {
            break;
        }
        p = q;
    }
    *(int *)(a0 + 0x14) = p;
    *(int *)(a0 + 0x10) = *(int *)(p + 0x10);
    *(int *)(p + 0x10) = (int)a0;
    *(int *)(*(int *)(a0 + 0x10) + 0x14) = (int)a0;
}


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

struct GObj {
    struct GObj *f_0;       /* 0x00 */
    int          f_4;       /* 0x04 */
    int          f_8;       /* 0x08 */
    char         pad_C[4];  /* 0x0C */
    struct GObj *f_10;      /* 0x10 */
    struct GObj *f_14;      /* 0x14 */
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
};                          /* size 0x174 */

extern struct GObj *D_0062BFA8;
extern unsigned int D_0062BFAC;
extern void debug_assertMessage();

void *isysGObjMoveHead(int a0, struct GObj *o)
{
    unsigned int i;
    struct GObj *e;
    struct GObj *u;
    int w;
    unsigned char t;

    for (i = 0; i < D_0062BFAC; i++) {
        if (D_0062BFA8[i].f_0 == 0) {
            break;
        }
    }
    if (i == D_0062BFAC) {
        debug_assertMessage(D_00551E00);
        e = 0;
    } else {
        struct GObj *p = (struct GObj *)(i * 0x174 + (int)D_0062BFA8);
        p->f_164 = 0;
        p->f_170 = 0;
        e = p;
    }
    if (e == 0) {
        debug_assertMessage(D_00551E00);
        return 0;
    }
    if (o == 0) {
        debug_assertMessage(D_00551DF0);
        return 0;
    }
    e->f_0 = e;
    e->f_28 = a0;
    t = o->f_18;
    e->f_14 = o;
    e->f_18 = t;
    u = o->f_10;
    w = o->f_1C;
    e->f_10 = u;
    o->f_10 = e;
    e->f_1C = w;
    if (e->f_10 == 0) {
        ((struct GObj **)D_0027DE10)[e->f_18] = e;
    }
    e->f_15C = 0;
    e->f_8 = -1;
    e->f_4 = -1;
    e->f_2C = 0;
    e->f_30 = 0;
    e->f_58 = 0;
    return e;
}


extern char D_0027DDF0[];

void *isysGObjAddAfterGObj(int a0, struct GObj *o)
{
    unsigned int i;
    struct GObj *e;
    struct GObj *u;
    struct GObj *rv;
    int w;
    int m1;
    unsigned char t;

    for (i = 0; i < D_0062BFAC; i++) {
        if (D_0062BFA8[i].f_0 == 0) {
            break;
        }
    }
    if (i == D_0062BFAC) {
        debug_assertMessage(D_00551E00);
        e = 0;
    } else {
        struct GObj *p = (struct GObj *)(i * 0x174 + (int)D_0062BFA8);
        p->f_164 = 0;
        p->f_170 = 0;
        e = p;
    }
    if (e == 0) {
        debug_assertMessage(D_00551E00);
        return 0;
    }
    if (o == 0) {
        debug_assertMessage(D_00551DF0);
        return 0;
    }
    e->f_0 = e;
    e->f_28 = a0;
    t = o->f_18;
    e->f_18 = t;
    u = o->f_14;
    e->f_10 = o;
    e->f_14 = u;
    o->f_14 = e;
    w = o->f_1C;
    e->f_1C = w;
    if (e->f_14 == 0) {
        ((struct GObj **)D_0027DDF0)[e->f_18] = e;
    }
    e->f_15C = 0;
    e->f_8 = -1;
    e->f_4 = -1;
    e->f_2C = 0;
    e->f_30 = 0;
    e->f_58 = 0;
    return e;
}


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

extern int D_0062A4C0;
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(struct GObj *g);
extern void isysGObjKindTableAdd(char *a0);

void isysGObjRemove(char *a0, int a1)
{
    char *p;
    int in_range;

    if (D_0062A4C0 != 0) {
        *(int *)(a0 + 0xC) = a1;
        return;
    }
    p = isysGObjSearchFromObjLayoutID(*(int *)(a0 + 0xC));
    do {
        in_range = (unsigned int)a1 < 0x43;
    } while (0);
    while (p != 0) {
        if (p == a0) {
            isysGObjKindTableAdd(a0);
            break;
        }
        isysGObjSearchFromObjKindID_begin((struct GObj *)p);
    }
    *(int *)(a0 + 0xC) = a1;
    if (in_range) {
        if (D_006A2F50[a1] == 0) {
            D_006A2F50[a1] = a0;
        } else {
            p = (char *)D_006A2F50[a1];
            while (*(char **)(p + 0x3C) != 0) {
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x3C) = a0;
        }
        *(int *)(a0 + 0x3C) = 0;
    }
}


extern void *D_006A2F50[];
extern void func_001AAD00(char *a0, int a1);
extern void func_00260380(char *a0, int a1, char *a2);
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

void *isysGObjMoveBeforeGObj(int a0, int a1, int a2)
{
    unsigned int i;
    struct GObj *e;
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;

    for (i = 0; i < D_0062BFAC; i++) {
        if (D_0062BFA8[i].f_0 == 0) {
            break;
        }
    }
    if (i == D_0062BFAC) {
        debug_assertMessage(D_00551E00);
        e = 0;
    } else {
        struct GObj *p = (struct GObj *)(i * 0x174 + (int)D_0062BFA8);
        p->f_164 = 0;
        p->f_170 = 0;
        e = p;
    }
    if (e == 0) {
        debug_assertMessage(D_00551E00);
        return 0;
    }
    e->f_28 = a0;
    e->f_0 = e;
    isysGObjRemoveAll((int)e, s1, new_var);
    e->f_15C = 0;
    e->f_8 = -1;
    e->f_4 = -1;
    e->f_2C = 0;
    e->f_30 = 0;
    e->f_58 = 0;
    *(int *)e->pad_C = 0;
    return e;
}


void *isysGObjAdd(int a0, int a1, int a2)
{
    unsigned int i;
    struct GObj *e;
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;

    for (i = 0; i < D_0062BFAC; i++) {
        if (D_0062BFA8[i].f_0 == 0) {
            break;
        }
    }
    if (i == D_0062BFAC) {
        debug_assertMessage(D_00551E00);
        e = 0;
    } else {
        struct GObj *p = (struct GObj *)(i * 0x174 + (int)D_0062BFA8);
        p->f_164 = 0;
        p->f_170 = 0;
        e = p;
    }
    if (e == 0) {
        debug_assertMessage(D_00551E00);
        return 0;
    }
    e->f_28 = a0;
    e->f_0 = e;
    add_gobj_to_tail((char *)e, s1, new_var);
    e->f_15C = 0;
    e->f_8 = -1;
    e->f_4 = -1;
    e->f_2C = 0;
    e->f_30 = 0;
    e->f_58 = 0;
    return e;
}


void *isysGObjAddHead(int a0) {
    unsigned int i;
    for (i = 0; i < D_0062BFAC; i++) {
        char *e = (char *)D_0062BFA8 + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == 1 && *(int *)(e + 8) == a0)
            return e;
    }
    return 0;
}

extern int D_0062A4C0;

void *isysGObjSearchFromObjLayoutID(int id)
{
    struct GObj *p;
    struct GObj *end;

    if (D_0062A4C0 == 0) goto table;
    p = D_0062BFA8 - 1;
    end = &D_0062BFA8[D_0062BFAC - 1];
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
    if ((unsigned)(id - 1) < 0x42) {
        return D_006A2F50[id];
    }
    goto ret0;
}


void *isysGObjSearchFromObjKindID_begin(struct GObj *g)
{
    struct GObj *p;
    struct GObj *end;
    int kind;

    if (D_0062A4C0 == 0) goto direct;
    p = g;
    end = &D_0062BFA8[D_0062BFAC - 1];
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



/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A2F50;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE10;  /* stride 0x4 */

/* end struct shapes */
