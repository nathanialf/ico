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
    /* 0x50 */ unsigned char hasDir;
    /* 0x51 */ char pad51[15];
    /* 0x60 */ float dir[4];
} __attribute__((aligned(16))) AttackPack; /* derived name */

/* the zeroed template every pack starts from; group and group2 start at -1 */
static const AttackPack attackPackInit = {0, 0, {0, 0}, 0, -1, -1}; /* derived name */

#include "attackhit.h"
#include <libvu0.h>
#include "main.h"

typedef struct { /* field names derived */
    /* 0x00 */ float radius;
    char pad04[4];
    /* 0x08 */ float power; /* the attack power multiplier */
    char pad0C[20];
    /* 0x20 */ unsigned int unguardable : 1; /* bit fields, as attackData's flag word */
    unsigned int sweep : 1;                  /* the swing sweeps; nothing in this build reads it */
    unsigned int padBits : 30;
} WeaponKindEntry; /* derived name */

/* the data-only member weapon-def.o, read through this file's view of its
   rows; no header declares it. const, as the table sits in .rodata (weapon.c
   declares it so) */
extern const WeaponKindEntry weaponKind[];

/* the attack table row of the actor's current motion, 0 when none matches */
static inline int GetAttackKindIndex(Sub15C *p) /* derived name */
{
    int id = p->ctrl.motion;
    int i;

    for (i = 0; i < 19; i++) {
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

static void MakeAttackPack_Actor(AttackPack *pack, GObj *gobj, GObj *weapon)
{
    float v0[4];
    Act *ext;
    int k;
    int wk;

    ext = GOBJ_ACT(gobj);
    k = GetAttackKindIndex(GOBJ_SUB(gobj));
    *pack = attackPackInit;
    pack->actor = gobj;
    if (k == 0) {
        return;
    }
    if (GetMotionFrameFlag1(gobj) == 0) {
        return;
    }
    pack->group = k;
    pack->group2 = ext->attackGroup | (k << 16);
    switch (attackData[k].weapon) {
    case 1:
        if (weapon == 0) {
            return;
        }
        wk = CheckWeaponKind(weapon);
        WeaponCurPos(weapon, pack->center, pack->from, pack->to);
        pack->radius0 = weaponKind[wk].radius;
        pack->radius1 = 20.0f;
        pack->power = attackData[k].power * weaponKind[wk].power;
        pack->active = 1;
        break;

    case 0:
        GetFocusNodePos(gobj, attackData[k].focusNode, v0);
        pack->center[0] = v0[0];
        pack->center[1] = v0[1];
        pack->center[2] = v0[2];
        pack->from[0] = v0[0];
        pack->from[1] = v0[1];
        pack->from[2] = v0[2];
        pack->to[0] = v0[0];
        pack->to[1] = v0[1];
        pack->to[2] = v0[2];
        pack->radius0 = attackData[k].radius;
        pack->radius1 = attackData[k].radius;
        pack->power = attackData[k].power;
        pack->active = 1;
        if (gobj->kind == 4) {
            if (actEnemy_isLargeEnemy(gobj) != 0) {
                pack->radius0 = pack->radius0 * 4.0f;
                pack->radius1 = pack->radius1 * 4.0f;
            }
            if (gobj->kind == 4) {
                if ((GOBJ_ACT(gobj)->enemy->flags.w.bits & 1) != 0) {
                    pack->down = 1;
                }
            }
        }
        break;
    }
}

/* shared by AttackCenter and AttackCenter_WithDir */
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
        pack->thickness = pack->radius1 - 100.0f;
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
    {{1, 0}, {4, 1}, {46, 1}, {53, 1}, {52, 1}, {52, 1}, {61, 1}, {2, 3}, {62, 1}, {-1, 0}}};

static int AttackCheckSameGroup(GObj *self, GObj *other)
{
    AttackGroupTable tbl = attackGroupTable;
    unsigned int g0 = 2;
    unsigned int g1 = 2;
    int i;

    for (i = 0; tbl.p[i].kind >= 0; i++) {
        if (self->kind == tbl.p[i].kind) {
            g0 = tbl.p[i].cls;
        }
    }
    for (i = 0; tbl.p[i].kind >= 0; i++) {
        if (other->kind == tbl.p[i].kind) {
            g1 = tbl.p[i].cls;
        }
    }
    switch (g1) {
    case 2:
        return 1;
    case 3:
        return g0 < 2;
    }
    return g1 == g0;
}

/* whether the attack's nodes include the target's focus node 35 */
static inline int AttackHitFocusNode(GObj *self) /* derived name */
{
    int node = GetSkeltonFocusNode(self, 35);
    int i;

    for (i = 0; GOBJ_ACT(self)->enemy->hitNodes[i] != -1; i++) {
        if (GOBJ_ACT(self)->enemy->hitNodes[i] == node) {
            return 1;
        }
    }
    return 0;
}

static void AttackMail(GObj *self, AttackPack *pack)
{
    float v0[4];
    float v1[4];
    float v2[4];
    GObj *attacker;
    Act *aext;
    GObj *weapon;
    int group;
    int kind;
    int hard;
    int mail;
    float power;

    attacker = pack->actor;
    aext = GOBJ_ACT(attacker);
    group = pack->group;
    weapon = 0;
    if (aext != 0) {
        weapon = aext->weapon;
    }
    hard = 0;
    if (group < 0) {
        power = 10.0f;
    } else if (weapon == 0) {
        power = attackData[group].power;
    } else {
        kind = CheckWeaponKind(weapon);
        power = attackData[group].power * weaponKind[kind].power;
        hard = weaponKind[kind].unguardable;
    }
    mail = 13;
    if (GOBJ_ACT(self)->enemy->liftKind == 3) {
        if (AttackHitFocusNode(self)) {
            mail = 14;
        }
    }
    iosOmSendMail(self, mail, attacker);

    GOBJ_ACT(self)->attacker = attacker;
    GOBJ_ACT(self)->damage = (int)power;
    GOBJ_ACT(self)->hitGroup = pack->group2;
    GOBJ_ACT(self)->downHit = attackData[group].down || pack->down;
    GOBJ_ACT(self)->unguardable = attackData[group].unguardable || hard;
    GOBJ_ACT(self)->stoneHit = attackData[group].stone;
    if (attacker == boyGObj) {
        aext->flags20.ll &= ~0x80000ULL;
    }
    GetRootPosition(v0, attacker);
    GetRootPosition(v1, self);
    sceVu0SubVector(v2, v0, v1);
    sceVu0Normalize(v2, v2);
    GOBJ_ACT(self)->attackDir[0] = v2[0];
    GOBJ_ACT(self)->attackDir[1] = v2[1];
    GOBJ_ACT(self)->attackDir[2] = v2[2];
    if (pack->hasDir != 0) {
        sceVu0ScaleVector(GOBJ_ACT(self)->attackDir, pack->dir, -1.0f);
    }
}

static int AttackCheckHit(AttackPack *pack, GObj *gobj, short *out)
{
    float w[4];
    unsigned char flags[112];
    Sub15C *sk;
    int n;
    int i;
    int j;
    int hitR;
    float rad;
    float t;

    sk = GOBJ_SUB(gobj);
    n = sk->skelNodeNum;
    if (n == 0) {
        n = 1;
    }
    switch (gobj->kind) {
    case 52:
        rad = QueenBallRadius(gobj);
        rad = rad + _ACTGame_GetParamF(29);
        hitR = (int)rad;
        i = 0;
        break;

    case 53:
        if (QueenBarrierInqBreakable() == 0) {
            hitR = 0;
            i = 0;
            break;
        }
        rad = QueenBarrierRadius(gobj);
        rad = rad + _ACTGame_GetParamF(30);
        hitR = (int)rad;
        i = 0;
        break;

    case 62:
        hitR = (int)GetAttackCheckBoundaryRadius(gobj);
        i = 0;
        break;

    case 61:
        hitR = 50;
        i = 0;
        break;

    case 4:
        hitR = (int)(GOBJ_ACT(gobj)->enemy->bodySize * 30.0f);
        i = 0;
        break;

    default:
        hitR = 30;
        i = 0;
        break;
    }
    for (i = 0; i < n; i++) {
        flags[i] = 0;
    }
    for (t = 0.0f; t < pack->radius0; t += pack->radius1) {
        _InterGV(w, pack->to, pack->center, t, pack->radius0 - t);
        for (i = 0; i < n; i++) {
            if (_DistSqGV((float *)(sk->nodeMtx + (i << 6) + 48), w) <
                ((float)hitR + pack->radius1) * ((float)hitR + pack->radius1)) {
                if (!(_DistSqGV((float *)(sk->nodeMtx + (i << 6) + 48), w) <
                      ((float)hitR + pack->thickness) * ((float)hitR + pack->thickness))) {
                    flags[i] = 1;
                }
            }
        }
    }
    for (i = 0, j = 0; i < n; i++) {
        if (flags[i] != 0) {
            out[j] = i;
            j++;
        }
    }
    out[j] = -1;
    return j;
}

static GObj *AttackGenerate(AttackPack *pack)
{
    GObj *g;
    GObj *hit;

    hit = 0;
    if (pack->active == 0) {
        return 0;
    }
    debug_StdPrintfDummy("flag ok\n");
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        if (g->active == 0) {
            continue;
        }
        if (AttackCheckSameGroup(pack->actor, g) != 0) {
            continue;
        }
        debug_StdPrintfDummy("group ok\n");
        if (!(GOBJ_ACT(g) != 0 && GOBJ_ACT(g)->enemy != 0)) {
            continue;
        }
        if (GOBJ_ACT(g)->hit != 0) {
            continue;
        }
        debug_StdPrintfDummy("invincible ok\n");
        if (g == boyGObj && ACTChkAttackIgnore_BOY(g) != 0) {
            continue;
        }
        if (g == girlGObj && ACTChkAttackIgnore_GIRL(g) != 0) {
            continue;
        }
        if (g->kind == 4 && ACTChkAttackIgnore_ENEMY(g) != 0) {
            continue;
        }
        /* the enemy work records the nodes the attack hits */
        if (AttackCheckHit(pack, g, GOBJ_ACT(g)->enemy->hitNodes) == 0) {
            continue;
        }
        debug_StdPrintfDummy("geometry ok\n");
        if (GOBJ_ACT(g) != 0 && GOBJ_ACT(g)->attacker != 0 &&
            GOBJ_ACT(g)->hitGroup == pack->group2) {
            debug_StdPrintfDummy("id equal error\n");
            continue;
        }
        if (debug_one_hit_only != 0 && pack->actor == boyGObj && g->kind == 4 &&
            ((int)(GOBJ_ACT(pack->actor)->flags20.ll >> 19) & 1) == 0) {
            continue;
        }
        AttackMail(g, pack);
        hit = g;
        debug_StdPrintfDummy("mail send ok [%d]\n", pack->group2);
        if (GOBJ_ACT(hit) != 0 && GOBJ_ACT(hit)->attacker != 0 && hit->kind == 4) {
            /* the enemy work records the direction the attack came from */
            _OrientGV(GOBJ_ACT(hit)->enemy->hitDir, pack->center, pack->from);
        }
    }
    return hit;
}

inline void CommonAttackCenter(GObj *gobj)
{
    AttackPack pack;
    MakeAttackPack_Actor(&pack, gobj, GOBJ_ACT(gobj)->weapon);
    AttackGenerate(&pack);
}

inline GObj *AttackCenter(GObj *gop, int group, float *pos, float *ofs, float radius)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(__FILE__, 749);
        __assert(__FILE__, 749, "gop!=NULL");
    }
    SetupAttackPack(&pack, gop, group, pos, ofs, radius);
    return AttackGenerate(&pack);
}

inline void AttackCenter_WithDir(GObj *gop, int group, float *pos, float *dir, float radius)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(__FILE__, 768);
        __assert(__FILE__, 768, "gop!=NULL");
    }
    SetupAttackPack(&pack, gop, group, pos, dir, radius);
    if (dir != 0) {
        pack.hasDir = 1;
        pack.dir[0] = dir[0];
        pack.dir[1] = dir[1];
        pack.dir[2] = dir[2];
    }
    AttackGenerate(&pack);
}

void EnemyAttackCenter(GObj *gobj) {}

void BoyAttackCenter(GObj *gobj) {}
