#include "common.h"

typedef struct {
    int gobj;
    float level;
    float f8;
    float fC;
    float f10;
    int timer;
    unsigned char b18;
    unsigned char b19;
    unsigned char b1A;
    unsigned char b1B;
} BrainTarget;

typedef struct {
    int girl;
    BrainTarget *cur;
    int w8;
    int wC;
    int w10;
    float f14;
    float f18;
    short h1C;
    short _1E;
    float f20;
    short idx;
    short _26;
    BrainTarget tgt[0x28];
} Brain;

typedef struct {
    char _0[0x24];
    float f24;
    float f28;
    float f2C;
    int w30;
    char _34[0x30];
} SceneEnt;
extern SceneEnt D_002C1270[];
extern int D_0028F4C0[];

static inline void brainSetTargetTimer(BrainTarget *t)
{
    int n;

    if (t->gobj != 0) {
        n = (int)D_002C1270[*(int *)(t->gobj + 0xC)].f24;
        if (n != -1) {
            n = n * ((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);
        }
    } else {
        n = -1;
    }
    t->timer = n;
}

extern int D_002A5580[];
extern int D_002A5584[];
void brainAddLevel(BrainTarget *t, float lv);
void brainSetLevel(int *b, BrainTarget *t, float lv);

void brainAddLevelGirl(float lv)
{
    if (D_002A5584[0] != 0) {
        brainAddLevel((BrainTarget *)D_002A5584[0], lv);
    }
}
extern void eBrainInit(void);

void brainInit(void)
{
    Brain *b = (Brain *)D_002A5580;
    int i;

    b->girl = 0;
    b->cur = 0;
    b->wC = 0;
    b->w10 = 0;
    for (i = 0; i < 0x28; i++) {
        b->tgt[i].gobj = 0;
    }
    b->f14 = 0.0f;
    b->idx = -1;
    b->h1C = 0;
    b->w8 = 0;
    eBrainInit();
}
extern void debug_StdPrintfDummy(const char *fmt);
extern char D_00554C88[];

void OverrideBrainStatusByGObj(Brain *b, int gobj, float f8, float f10, float fC)
{
    BrainTarget *t;
    int i;

    for (i = 0; i < 0x28; i++) {
        if (b->tgt[i].gobj == gobj) {
            t = &b->tgt[i];
            t->f8 = f8;
            t->fC = fC;
            t->f10 = f10;
            t->level = 0.0f;
            return;
        }
    }
    debug_StdPrintfDummy(D_00554C88);
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainStatusDefaultSet);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainLevelProcess);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainGetTarget);
void brainStatusDel(char *self) {
    *(int *)(self + 0x0) = 0;
}
float brainGetLevel(Brain *b, BrainTarget *t) /* inlined by brainLevelProcess and brainGetTarget in ROM: `inline` once those are C, plain until then (the tail still has asm members) */
{
    if (b->cur == t) {
        return t->level + b->f14;
    }
    return t->level;
}
void brainClsTargetLevel(Brain *b)
{
    BrainTarget *t;

    if (b->idx == -1) {
        return;
    }
    t = &b->tgt[b->idx];
    t->level = 0.0f;
    b->h1C = 0;
    t->f8 = t->f8 - t->fC;
    if (t->f8 < t->level) {
        t->f8 = t->level;
    }
    *(int *)&t->b18 &= ~0x10000;
    brainSetTargetTimer(t);
}
extern void ACTGameView_Add(void *a0, int a1);

void brainInitGirlSet(void *a0, int a1) {
    int *base = D_002A5580;
    int *p = (int *)((char *)base + 0x28);
    int key;
    int t;
    D_002A5580[0] = (int)a0;
    key = *p;
    if (key == 0) {
        return;
    }
    do {
        if (key == a1) {
            base[1] = (int)p;
        }
        ACTGameView_Add(a0, *p);
        p = (int *)((char *)p + 0x1C);
        t = *p;
        key = t;
    } while (t != 0);
}
void brainAddLevelGirlDetail(int flag, float lv)
{
    Brain *b = (Brain *)D_002A5580;

    if (b->cur != 0) {
        brainAddLevel(b->cur, lv);
        if (flag != 0) {
            *(int *)&b->cur->b18 |= 0x10000;
        }
    }
}
void brainAddLevelGop(int gobj, float lv)
{
    int brain = (int)D_002A5580;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 0x28; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            brainAddLevel(&((BrainTarget *)tgt)[i], lv);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainSubLevelGop);
void brainSetLevelGop(int gobj, int a1, int a2, float lv)
{
    int brain = (int)D_002A5580;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 0x28; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            ((BrainTarget *)tgt)[i].b18 = a1;
            ((BrainTarget *)tgt)[i].b19 = a2;
            brainSetLevel((int *)brain, &((BrainTarget *)tgt)[i], lv);
        }
    }
}
static inline int brainDecTimer(BrainTarget *e)
{
    int t;

    if (e == 0) {
        return 0;
    }
    if (e->timer == -1) {
        return 0;
    }
    e->timer--;
    if (e->timer >= 0) {
        t = e->timer > 0xFFFFFFF ? 0xFFFFFFF : e->timer;
    } else {
        t = 0;
    }
    e->timer = t;
    return e->timer == 0;
}

int brainDecTargetTimer(int gobj)
{
    int brain = (int)D_002A5580;
    int tgt = brain + 0x28;
    BrainTarget *e;
    int i;

    for (i = 0; i < 0x28; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            e = &((BrainTarget *)tgt)[i];
            goto found;
        }
    }
    e = 0;
found:
    return brainDecTimer(e);
}
extern int D_002A558C[];

void brainSetSpMode(void) {
    D_002A558C[0] = 1;
}
extern int D_002A5588[];

void brainLockGirl(void) {
    D_002A5588[0] = 1;
}
void brainUnlockGirl(void) {
    D_002A5588[0] = 0;
}
void brainAddLevel(BrainTarget *t, float lv)
{
    float r;

    t->level = t->level + t->f10 * lv;
    if (t->level < 0.0f) {
        r = 0.0f;
    } else if (t->level > 10.0f) {
        r = 10.0f;
    } else {
        r = t->level;
    }
    t->level = r;
}
void brainSetLevel(int *b, BrainTarget *t, float lv) {
    int cond;
    if (t->b19 != 0) {
        cond = 1;
    } else {
        cond = ACTGameView_Check(*b, t->gobj) != 0;
    }
    if (cond) {
        float r;
        t->level = lv;
        if (t->level < 0.0f) {
            r = 0.0f;
        } else if (t->level > 20.0f) {
            r = 20.0f;
        } else {
            r = t->level;
        }
        t->level = r;
    }
}
int brainCheckView(int *a0, int *a1)
{
    if (((unsigned char *)a1)[0x19] != 0) {
        return 1;
    }
    return ACTGameView_Check(*a0, a1[0]) != 0;
}
