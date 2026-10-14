#include "debug.h"
#include "gobj.h"
#include "obj_manager.h"
#include "enemy_act.h"
#include "queen.h"
#include "attackCheckBoundary.h"
#include "geometryManager.h"
#include "item.h"
#include "motionManager2.h"
#include "weapon.h"
#include "debug_exception.h"
#include "gv.h"
#include "commonact.h"
#include "act-game.h"
#include <assert.h>

typedef struct AttackPack { /* field names derived */
    /* 0x00 */ unsigned char active;
    /* 0x01 */ unsigned char down; /* the hit knocks the target down */
    /* 0x02 */ char pad02[2];
    /* 0x04 */ void *actor;
    /* 0x08 */ int group;
    /* 0x0C */ int group2;
    /* 0x10 */ float center[4];
    /* 0x20 */ float from[4];
    /* 0x30 */ float to[4];
    /* 0x40 */ float radius0;
    /* 0x44 */ float radius1;
    /* 0x48 */ float thickness;
    /* 0x4C */ float power;
    /* 0x50 */ char sweep; /* the weapon's swing sweeps the area round the actor */
    /* 0x51 */ unsigned char hasDir;
    /* 0x52 */ char pad52[14];
    /* 0x60 */ float dir[4];
} __attribute__((aligned(16))) AttackPack; /* derived name */

/* the zeroed template every pack starts from; group and group2 start at -1 */
static const AttackPack attackPackInit = {0, 0, {0, 0}, 0, -1, -1}; /* derived name */

#include "attackhit.h"
#include <libvu0.h>
#include "main.h"
#include "include_asm.h"

/* whether d1 and d2 lie on opposite sides of d0, both ahead of it */
static inline int inner_check_core(float *d0, float *d1, float *d2) /* derived name */
{
    float c1[4];
    float c2[4];

    if (0.0f <= sceVu0InnerProduct(d0, d1) && 0.0f <= sceVu0InnerProduct(d0, d2)) {
        sceVu0OuterProduct(c1, d0, d1);
        sceVu0OuterProduct(c2, d0, d2);
        if (sceVu0InnerProduct(c1, c2) < 0.0f) {
            return 1;
        }
    }
    return 0;
}

static inline int inner_check_sub(float *p, float *o, float *a, float *b) /* derived name */
{
    float d0[4];
    float d1[4];
    float d2[4];
    /* the fourth difference vector, computed and reported only by the DEBUG
       build */
    float d3[4];

    sceVu0SubVector(d0, p, o);
    sceVu0SubVector(d1, a, o);
    sceVu0SubVector(d2, b, o);
#ifdef DEBUG
    sceVu0SubVector(d3, b, a);
    scePrintf("inner check edge %f %f %f\n", d3[0], d3[1], d3[2]);
#endif
    return inner_check_core(d0, d1, d2);
}

static int inner_check(float *p, float *o, float *a, float *b, float r, float t);

typedef struct { /* field names derived */
    /* 0x00 */ float radius;
    char pad04[4];
    /* 0x08 */ float power; /* the attack power multiplier */
    char pad0C[20];
    /* 0x20 */ unsigned int flags; /* bit 0 unguardable, bit 1 the swing sweeps */
} WeaponKindEntry;                 /* derived name */

/* the data-only member weapon-def.o, read through this file's view of its
   rows; no header declares it */
extern WeaponKindEntry weaponKind[];

/* the 0x5C word as a float or an int, written through this view at one site */
union PackPowerWord { /* field names derived */
    float f;
    int i;
    int m;
};

/* the attack table row of the actor's current motion, 0 when none matches */
static inline int GetAttackKindIndex(Sub15C *p) /* derived name */
{
    int id = p->ctrl.motion;
    int i;

    for (i = 0; i < 20; i++) {
        if (id == attackData[i].motion) {
            return i;
        }
    }
    return 0;
}

static inline void GetFocusNodePos(GObj *gobj, int node, float *out) /* derived name */
{
    int idx = GetSkeltonFocusNode(gobj, node);
    float *m = (float *)((idx << 6) + GOBJ_SUB(gobj)->nodeMtx);

    out[0] = m[12];
    out[1] = m[13];
    out[2] = m[14];
}

INCLUDE_ASM(MakeAttackPack_Actor);

/* shared by _AttackCenter and AttackCenter_WithDir */
static inline void SetupAttackPack(AttackPack *pack, GObj *gop, int group, float *pos, float *ofs,
                                   float radius) /* derived name */
{
    *pack = attackPackInit;

    pack->active = 1;
    pack->actor = gop;
    pack->group = group;
    pack->group2 = group;
    pack->center[0] = pos[0];
    pack->center[1] = pos[1];
    pack->center[2] = pos[2];
    if (ofs != 0) {
        sceVu0SubVector(pack->from, pack->center, ofs);
    } else {
        pack->from[0] = pos[0];
        pack->from[1] = pos[1];
        pack->from[2] = pos[2];
    }
    pack->to[0] = pos[0];
    pack->to[1] = pos[1];
    pack->to[2] = pos[2];

    pack->radius1 = pack->radius0 = radius;

    if (gop != 0 && gop->kind == 52) {
        pack->thickness = pack->radius1 - GetQueenBallThickness();
        if (pack->thickness < 0.0f) {
            pack->thickness = 0.0f;
        }
    } else {
        pack->thickness = 0.0f;
    }

    pack->power = 20.0f;
}

typedef struct { /* field names derived */
    int kind;
    unsigned int cls;
} AttackGroupPair; /* derived name */

typedef struct { /* field names derived */
    AttackGroupPair p[10];
} AttackGroupTable; /* derived name */

/* GObj kind -> attack class, terminated by kind -1 */
static const AttackGroupTable attackGroupTable = {
    /* derived name */
    {{1, 0}, {4, 1}, {46, 1}, {53, 1}, {52, 1}, {52, 1}, {60, 1}, {2, 3}, {61, 1}, {-1, 0}}};

INCLUDE_ASM(AttackCheckSameGroup);

INCLUDE_ASM(AttackMail);

INCLUDE_ASM(AttackCheckHit);

INCLUDE_ASM(AttackGenerate);

INCLUDE_ASM_LIT(AttackCenter_WithDir);

void EnemyAttackCenter(GObj *gobj) {}

void BoyAttackCenter(GObj *gobj) {}

INCLUDE_ASM(CommonAttackCenter);

INCLUDE_ASM(AttackCenter);

INCLUDE_ASM(AttackCenter_WithDir);
