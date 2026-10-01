#include "debug.h"
#include "act-game.h"
#include "commonact.h"
#include "ebrain.h"
#include "typedef.h"
#include "brain.h"
#include "main.h"
#include "gv.h"

extern ObjKindEnt objKindData[];

static inline void brainSetTargetTimer(BrainTarget *t)
{
    int n;

    if (t->gobj != 0) {
        n = (int)objKindData[((PObjGObj *)t->gobj)->kind].targetTime;
        if (n != -1) {
            n = n * ((0x3C - systemStatus[0] * 0xA) / systemStatus[1]);
        }
    } else {
        n = -1;
    }
    t->timer = n;
}

Brain brainGirl = {0};

void brainAddLevel(BrainTarget *t, float lv);
void brainSetLevel(int *b, BrainTarget *t, float lv);

void brainAddLevelGirl(float lv)
{
    if (brainGirl.cur != 0) {
        brainAddLevel(brainGirl.cur, lv);
    }
}

void brainInit(void)
{
    Brain *b = &brainGirl;
    int i;

    b->girl = 0;
    b->cur = 0;
    b->wC = 0;
    b->w10 = 0;
    for (i = 0; i < 40; i++) {
        b->tgt[i].gobj = 0;
    }
    b->f14 = 0.0f;
    b->idx = -1;
    b->h1C = 0;
    b->w8 = 0;
    eBrainInit();
}

void OverrideBrainStatusByGObj(Brain *b, int gobj, float f8, float f10, float fC)
{
    BrainTarget *t;
    int i;

    for (i = 0; i < 40; i++) {
        if (b->tgt[i].gobj == gobj) {
            t = &b->tgt[i];
            t->f8 = f8;
            t->fC = fC;
            t->f10 = f10;
            t->level = 0.0f;
            return;
        }
    }
    /* "failed to override the brain level" */
    debug_StdPrintfDummy("ブレインレベルのオーバーライドに失敗しました\n");
}

typedef struct {
    char _0[0x46];
    unsigned char b46;
    char _47[1];
    unsigned int w48;
} BrainDefEnt;

extern BrainDefEnt objLayout[];

static inline void brainSetTargetSub(Brain *b, int gobj, float lvl, int k)
{
    float fc = objKindData[k].f28;
    float f10 = objKindData[k].f2C;
    BrainTarget *t;
    int i;

    for (i = 0; i < 40; i++) {
        if (b->tgt[i].gobj == 0) {
            break;
        }
    }
    if (i == 0x28) {
        return;
    }
    t = &b->tgt[i];
    t->gobj = gobj;
    t->level = 0.0f;
    t->f8 = lvl;
    t->fC = fc;
    t->f10 = f10;
    t->b18 = 0;
    t->b19 = 0;
    *(int *)&t->b18 &= ~0x10000;
    brainSetTargetTimer(t);
}

void brainStatusDefaultSet(Brain *b, int gobj, int idx)
{
    BrainDefEnt *d = objLayout + idx;
    int k = d->b46;

    if ((d->w48 >> 20) & 1) {
        if (objKindData[k].f30 != 0) {
            brainSetTargetSub(b, gobj, (float)objKindData[k].f30, k);
        }
    }
}

static inline void brainLevelUp(BrainTarget *t) /* derived name */
{
    float d = t->f10;

    if (t->level <= t->f8) {
        float r;
        t->level = t->level + d;
        if (t->level < 0.0f) {
            r = 0.0f;
        } else if (t->level > t->f8) {
            r = t->f8;
        } else {
            r = t->level;
        }
        t->level = r;
    }
}

/* brainCheckView's body, for the caller above its definition */
static inline int brainCheckView_INTERIM(Brain *b, BrainTarget *t)
{
    if (t->b19 != 0) {
        return 1;
    }
    return ACTGameView_Check(b->girl, t->gobj) != 0;
}

void brainLevelProcess(Brain *b)
{
    int i;

    b->f14 = b->f14 - _ACTGame_GetParamF(24) * 0.1f;
    if (b->f14 < b->f18) {
        b->f14 = b->f18;
    }
    for (i = 0; i < 40; i++) {
        BrainTarget *t = &b->tgt[i];

        if (t->gobj == 0) {
            continue;
        }
        if (*(int *)(t->gobj + 0x16C) == 0) {
            t->level = 0.0f;
            continue;
        }
        if (b->w8 != 0) {
            t->level = 0.0f;
            continue;
        }
        if (t != b->cur && t->level > 1.9 && girlGObj != 0 &&
            ((int)(*(long long *)(*(int *)((char *)girlGObj + 0x164) + 0x20) >> 27) & 1)) {
            float r;
            /* 3.40282347e+38f is FLT_MAX */
            if (ACTGameViewSimple_Check(b->girl, t->gobj) != 0) {
                t->level = t->level - 0.002;
            } else {
                t->level = t->level - 0.005;
            }
            if (t->level < 1.9) {
                r = 1.9f;
            } else if (t->level > 3.40282347e+38f) {
                r = 3.40282347e+38f;
            } else {
                r = t->level;
            }
            t->level = r;
            continue;
        }
        if (brainCheckView_INTERIM(b, t) == 0) {
            continue;
        }
        brainLevelUp(t);
        if (t->f8 < t->level) {
            float r;
            t->level = t->level - t->f10 / 10.0f;
            if (t->level < t->f8) {
                r = t->f8;
            } else if (t->level > 3.40282347e+38f) {
                r = 3.40282347e+38f;
            } else {
                r = t->level;
            }
            t->level = r;
        }
    }
}

/* brainGetLevel's body, for brainGetTarget above its definition */
static inline float brainGetLevel_INTERIM(Brain *b, BrainTarget *t)
{
    if (b->cur == t) {
        return t->level + b->f14;
    }
    return t->level;
}

void brainGetTarget(Brain *b)
{
    BrainTarget *best = 0;
    BrainTarget *t;
    float r;
    /* the winner index */
    volatile int idx;
    int n;
    int lv;
    int i;

    for (i = 0; i < 40; i++) {
        if (b->tgt[i].gobj == 0) {
            continue;
        }
        t = &b->tgt[i];
        if (best == 0 || brainGetLevel_INTERIM(b, t) > brainGetLevel_INTERIM(b, best)) {
            best = t;
            idx = i;
        } else if (best != 0 && brainGetLevel_INTERIM(b, t) == brainGetLevel_INTERIM(b, best)) {
            if (girlGObj != 0) {
                if (_DistSqGV(test_CURRENTROOT((void *)t->gobj), test_CURRENTROOT(girlGObj)) <
                    _DistSqGV(test_CURRENTROOT((void *)best->gobj), test_CURRENTROOT(girlGObj))) {
                    best = t;
                    idx = i;
                }
            }
        }
    }

    if (b->wC != 0) {
        b->wC = 0;
        b->w10 = b->w10 + 1;
    } else {
        b->w10 = b->w10 - 1;
    }
    if (b->w10 >= 0) {
        n = b->w10 > (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 3 +
                         (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 12
                ? (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 3 +
                      (0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 12
                : b->w10;
    } else {
        n = 0;
    }
    b->w10 = n;

    if ((0x3C - systemStatus[0] * 0xA) / systemStatus[1] / 3 < b->w10) {
        best = b->cur;
        for (i = 0; i < 40; i++) {
            t = &b->tgt[i];
            if (t == best) {
                idx = i;
                break;
            }
        }
    }

    b->idx = -1;
    if (best != 0) {
        b->idx = idx;
        lv = (int)(brainGetLevel_INTERIM(b, best) - b->f14);

        b->f20 = (float)lv / 10.0f;
        if (b->f20 < 0.0f) {
            r = 0.0f;
        } else if (b->f20 > 1.0f) {
            r = 1.0f;
        } else {
            r = b->f20;
        }
        b->f20 = r;
        if (lv > 0) {
            if (best->b18 != 0 || lv < 2) {
                b->h1C = 1;
            } else if (lv < 4) {
                b->h1C = 2;
            } else {
                b->h1C = 3;
            }
        } else {
            b->h1C = 0;
        }
    }
}

void brainStatusDel(char *self)
{
    *(int *)(self + 0x0) = 0;
}

float brainGetLevel(Brain *b, BrainTarget *t)
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

void brainInitGirlSet(void *a0, int a1)
{
    int *base = (int *)&brainGirl;
    int *p = (int *)((char *)base + 0x28);
    int key;
    int t;
    brainGirl.girl = (int)a0;
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
    Brain *b = &brainGirl;

    if (b->cur != 0) {
        brainAddLevel(b->cur, lv);
        if (flag != 0) {
            *(int *)&b->cur->b18 |= 0x10000;
        }
    }
}

void brainAddLevelGop(int gobj, float lv)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 40; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            brainAddLevel(&((BrainTarget *)tgt)[i], lv);
        }
    }
}

void brainSubLevelGop(int gobj, float lv)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 40; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            float r;
            ((BrainTarget *)tgt)[i].level = ((BrainTarget *)tgt)[i].level - lv;
            /* 3.40282347e+38f is FLT_MAX */
            if (((BrainTarget *)tgt)[i].level < 0.0f) {
                r = 0.0f;
            } else if (((BrainTarget *)tgt)[i].level > 3.40282347e+38f) {
                r = 3.40282347e+38f;
            } else {
                r = ((BrainTarget *)tgt)[i].level;
            }
            ((BrainTarget *)tgt)[i].level = r;
        }
    }
}

void brainSetLevelGop(int gobj, int a1, int a2, float lv)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 40; i++) {
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
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    BrainTarget *e;
    int i;

    for (i = 0; i < 40; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            e = &((BrainTarget *)tgt)[i];
            goto found;
        }
    }
    e = 0;
found:
    return brainDecTimer(e);
}

void brainSetSpMode(void)
{
    brainGirl.wC = 1;
}

void brainLockGirl(void)
{
    brainGirl.w8 = 1;
}

void brainUnlockGirl(void)
{
    brainGirl.w8 = 0;
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

void brainSetLevel(int *b, BrainTarget *t, float lv)
{
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
