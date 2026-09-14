#include "common.h"

typedef struct AttackPack {
    /* 0x00 */ char active;
    /* 0x01 */ char pad01[3];
    /* 0x04 */ void *actor;
    /* 0x08 */ int f08;
    /* 0x0C */ int group;
    /* 0x10 */ int group2;
    /* 0x14 */ int f14;
    /* 0x18 */ int f18;
    /* 0x1C */ int f1C;
    /* 0x20 */ float center[4];
    /* 0x30 */ float from[4];
    /* 0x40 */ float to[4];
    /* 0x50 */ float radius0;
    /* 0x54 */ float radius1;
    /* 0x58 */ float thickness;
    /* 0x5C */ float power;
    /* 0x60 */ char f60;
    /* 0x61 */ char hasDir;
    /* 0x62 */ char pad62[2];
    /* 0x64 */ int f64;
    /* 0x68 */ int f68;
    /* 0x6C */ int f6C;
    /* 0x70 */ float dir[4];
} __attribute__((aligned(16))) AttackPack;

extern AttackPack D_00554A40;
extern char D_00554C68[];
extern char D_00554C78[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern float GetQueenBallThickness(void);
/* prototypes: their order is the inline tail's emission order */
void CommonAttackCenter(char *a0);
int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);
void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", inner_check);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", MakeAttackPack_Actor);

/* listing lines ~405-435: shared by _AttackCenter and AttackCenter_WithDir */
static inline void SetupAttackPack(AttackPack *pack, char *gop, int group, float *pos, float *ofs,
                                   float radius)
{
    *pack = D_00554A40;

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

    if (gop != 0 && *(int *)(gop + 0xC) == 0x35) {
        pack->thickness = pack->radius1 - GetQueenBallThickness();
        if (pack->thickness < 0.0f) {
            pack->thickness = 0.0f;
        }
    } else {
        pack->thickness = 0.0f;
    }

    pack->power = 20.0f;
}

typedef struct {
    int kind;
    unsigned int cls;
} AttackGroupPair;

typedef struct {
    AttackGroupPair p[10];
} AttackGroupTable;

extern AttackGroupTable D_00554AC0;

int AttackCheckSameGroup(char *self, char *other, char *third)
{
    AttackGroupTable tbl = D_00554AC0;
    unsigned int g0 = 2;
    unsigned int g1 = 2;
    int i;
    int k;

    if (other == self || other == third) {
        return 1;
    }
    k = *(int *)(other + 0xC);
    if (k == 19) {
        return 0;
    }
    for (i = 0; tbl.p[i].kind >= 0; i++) {
        if (*(int *)(self + 0xC) == tbl.p[i].kind) {
            g0 = tbl.p[i].cls;
        }
    }
    for (i = 0; tbl.p[i].kind >= 0; i++) {
        if (k == tbl.p[i].kind) {
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

INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackMail);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckHit);
INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackGenerate);

inline void CommonAttackCenter(char *a0)
{
    char pack[0x80];
    MakeAttackPack_Actor(pack, a0, *(int *)(*(char **)(a0 + 0x164) + 0x150));
    AttackGenerate(pack);
}

inline int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(D_00554C68, 0x3A3);
        __assert(D_00554C68, 0x3A3, D_00554C78);
    }
    SetupAttackPack(&pack, gop, group, pos, ofs, radius);
    pack.f08 = kind;
    return AttackGenerate(&pack);
}

inline void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(D_00554C68, 0x3B7);
        __assert(D_00554C68, 0x3B7, D_00554C78);
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

void EnemyAttackCenter(void) {}

void BoyAttackCenter(void) {}
