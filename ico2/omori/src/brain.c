#include "debug.h"
#include "act-game.h"
#include "commonact.h"
#include "ebrain.h"
#include "typedef.h"
#include "brain.h"
#include "main.h"
#include "gv.h"
#include "gamesys.h"
#include "include_asm.h"

static inline void brainSetTargetTimer(BrainTarget *t) /* derived name */
{
    int n;

    if (t->gobj != 0) {
        n = (int)objKindData[t->gobj->kind].targetTime;
        if (n != -1) {
            n = n * ((60 - systemStatus[0] * 10) / systemStatus[1]);
        }
    } else {
        n = -1;
    }
    t->timer = n;
}

Brain brainGirl = {0};

static void brainAddLevel(BrainTarget *t, float lv);
static void brainSetLevel(Brain *b, BrainTarget *t, float lv);

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
    b->spMode = 0;
    b->spCount = 0;
    for (i = 0; i < 20; i++) {
        b->tgt[i].gobj = 0;
    }
    b->threshold = 0.0f;
    b->idx = -1;
    b->targetType = 0;
    b->lock = 0;
    eBrainInit();
}

static inline BrainTarget *brainSetTargetSub(Brain *b, GObj *gobj, float levelCap, float capStep,
                                             float rate) /* derived name */
{
    BrainTarget *t;
    int i;

    for (i = 0; i < 20; i++) {
        if (b->tgt[i].gobj == 0) {
            break;
        }
    }
    if (i == 20) {
        debug_StdPrintfDummy("brainStatusDefaultSet: brain target area over\n");
        return 0;
    }
    t = &b->tgt[i];
    t->gobj = gobj;
    t->level = 0.0f;
    t->levelCap = levelCap;
    t->capStep = capStep;
    t->rate = rate;
    t->lookOnly = 0;
    t->alwaysSeen = 0;
    brainSetTargetTimer(t);
    return t;
}

INCLUDE_ASM(OverrideBrainStatusByGObj);

void brainStatusDefaultSet(Brain *b, GObj *gobj, int idx)
{
    GenGeo *d = objLayout + idx;
    int k = d->kind;

    /* bit 20 of the layout row's flags puts the object in the girl's brain */
    if ((d->flags >> 20) & 1) {
        if (objKindData[k].brainLevel != 0) {
            brainSetTargetSub(b, gobj, (float)objKindData[k].brainLevel,
                              objKindData[k].brainCapStep, objKindData[k].brainRate);
        }
    }
}

static inline void brainLevelUp(BrainTarget *t) /* derived name */
{
    float d = t->rate;

    if (t->level <= t->levelCap) {
        float r;
        t->level = t->level + d;
        if (t->level < 0.0f) {
            r = 0.0f;
        } else if (t->level > t->levelCap) {
            r = t->levelCap;
        } else {
            r = t->level;
        }
        t->level = r;
    }
}

/* whether the girl sees the target, brainCheckView's test inlined into
   brainLevelProcess */
static inline int brainTargetInView(Brain *b, BrainTarget *t) /* derived name */
{
    if (t->alwaysSeen != 0) {
        return 1;
    }
    return ACTGameView_Check(b->girl, t->gobj) != 0;
}

INCLUDE_ASM(brainLevelProcess);

/* the target's level as the chooser weighs it, the current target holding
   the threshold on top: brainGetLevel's body inlined into brainGetTarget */
static inline float brainTargetLevel(Brain *b, BrainTarget *t) /* derived name */
{
    if (b->cur == t) {
        return t->level + b->threshold;
    }
    return t->level;
}

INCLUDE_ASM(brainGetTarget);

BrainTarget *brainStatusSet(Brain *b, GObj *gobj, float levelCap, float capStep, float rate)
{
    return brainSetTargetSub(b, gobj, levelCap, capStep, rate);
}

void brainStatusDel(char *self)
{
    *(int *)(self + 0x0) = 0;
}

float brainGetLevel(Brain *b, BrainTarget *t)
{
    if (b->cur == t) {
        return t->level + b->threshold;
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
    b->targetType = 0;
    t->levelCap = t->levelCap - t->capStep;
    if (t->levelCap < t->level) {
        t->levelCap = t->level;
    }
    brainSetTargetTimer(t);
}

void brainInitGirlSet(GObj *girl, GObj *cur)
{
    Brain *b = &brainGirl;
    BrainTarget *t = b->tgt;
    b->girl = girl;
    if (t->gobj == 0) {
        return;
    }
    do {
        if (t->gobj == cur) {
            b->cur = t;
        }
        ACTGameView_Add(girl, t->gobj);
        t++;
    } while (t->gobj != 0);
}

void brainAddLevelGop(GObj *gobj, float lv)
{
    int i;

    for (i = 0; i < 20; i++) {
        if (brainGirl.tgt[i].gobj == gobj) {
            brainAddLevel(&brainGirl.tgt[i], lv);
        }
    }
}

/* brainSubLevelGop, brainSetLevelGop and brainDecTargetTimer walk the
   targets from an int address; brainGirl.tgt[i] or a BrainTarget pointer
   moves .text in each */
void brainSubLevelGop(GObj *gobj, float lv)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 20; i++) {
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

void brainSetLevelGop(GObj *gobj, float lv, int lookOnly, int alwaysSeen)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    int i;

    for (i = 0; i < 20; i++) {
        if (((BrainTarget *)tgt)[i].gobj == gobj) {
            ((BrainTarget *)tgt)[i].lookOnly = lookOnly;
            ((BrainTarget *)tgt)[i].alwaysSeen = alwaysSeen;
            brainSetLevel((Brain *)brain, &((BrainTarget *)tgt)[i], lv);
        }
    }
}

static inline int brainDecTimer(BrainTarget *e) /* derived name */
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

int brainDecTargetTimer(GObj *gobj)
{
    int brain = (int)&brainGirl;
    int tgt = brain + 0x28;
    BrainTarget *e;
    int i;

    for (i = 0; i < 20; i++) {
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
    brainGirl.spMode = 1;
}

void brainLockGirl(void)
{
    brainGirl.lock = 1;
}

void brainUnlockGirl(void)
{
    brainGirl.lock = 0;
}

static void brainAddLevel(BrainTarget *t, float lv)
{
    float r;

    t->level = t->level + t->rate * lv;
    if (t->level < 0.0f) {
        r = 0.0f;
    } else if (t->level > 10.0f) {
        r = 10.0f;
    } else {
        r = t->level;
    }
    t->level = r;
}

static void brainSetLevel(Brain *b, BrainTarget *t, float lv)
{
    int cond;
    if (t->alwaysSeen != 0) {
        cond = 1;
    } else {
        cond = ACTGameView_Check(b->girl, t->gobj) != 0;
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

int brainCheckView(Brain *b, BrainTarget *t)
{
    if (t->alwaysSeen != 0) {
        return 1;
    }
    return ACTGameView_Check(b->girl, t->gobj) != 0;
}
