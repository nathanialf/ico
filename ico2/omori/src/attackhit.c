#include "common.h"

typedef struct AttackPack {
    /* 0x00 */ unsigned char active;
    /* 0x01 */ unsigned char f01;
    /* 0x02 */ char pad02[2];
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
    /* 0x61 */ unsigned char hasDir;
    /* 0x62 */ char pad62[2];
    /* 0x64 */ int f64;
    /* 0x68 */ int f68;
    /* 0x6C */ int f6C;
    /* 0x70 */ float dir[4];
} __attribute__((aligned(16))) AttackPack;

/* the zeroed template every pack starts from; group and group2 start at -1 */
static const AttackPack attackPackInit = {0, 0, {0, 0}, 0, 0, -1, -1};

extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern float GetQueenBallThickness(void);
/* prototypes: their order is the inline tail's emission order */
void CommonAttackCenter(char *a0);
int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind);
void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius);
extern float sceVu0InnerProduct(void *a, void *b);
extern void sceVu0OuterProduct(void *out, void *a, void *b);
extern void sceVu0Normalize(void *out, void *a);
extern float _DistGV(void *a, void *b);

/* listing lines 174-185 */
static inline int inner_check_core(float *d0, float *d1, float *d2)
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

/* listing lines 186-202 */
static inline int inner_check_sub(float *p, float *o, float *a, float *b)
{
    float d0[4];
    float d1[4];
    float d2[4];
    /* the 0x40 frame slot the ROM reserves and never reads: the listing's
       fourth difference vector, whose line compiled out */
    float d3[4];

    sceVu0SubVector(d0, p, o);
    sceVu0SubVector(d1, a, o);
    sceVu0SubVector(d2, b, o);
    return inner_check_core(d0, d1, d2);
}

int inner_check(float *p, float *o, float *a, float *b, float r, float t)
{
    float n[4];
    unsigned char ok;
    float lim;
    float d;

    ok = inner_check_sub(p, o, a, b);

    if (ok == 0) {
        return 0;
    }
    lim = (_DistGV(o, a) + _DistGV(o, b)) * 0.5;
    if (_DistGV(p, o) < lim + r) {
        float v0[4];
        float v1[4];
        float v2[4];

        sceVu0SubVector(v2, p, o);
        sceVu0SubVector(v0, a, o);
        sceVu0SubVector(v1, b, o);
        sceVu0OuterProduct(n, v0, v1);
        sceVu0Normalize(n, n);
        d = sceVu0InnerProduct(n, v2);
        if (d < 0.0f) {
            d = -d;
        }
        if (d < t) {
            return 1;
        }
    }
    return 0;
}

typedef struct {
    char _00[0x10];
    /* 0x10 */ int f10;
    /* 0x14 */ int f14;
    /* 0x18 */ float f18;
    /* 0x1C */ float f1C;
    /* 0x20 */ unsigned int b0 : 1;
    unsigned int b1 : 1;
    unsigned int b2 : 1;
    unsigned int b3 : 1;
    unsigned int b4 : 1;
    unsigned int brest : 27;
} AttackKindEntry;

extern const AttackKindEntry attackData[];

typedef struct {
    /* 0x00 */ float f00;
    char _04[4];
    /* 0x08 */ float f08;
    char _0C[0x14];
    /* 0x20 */ unsigned int f20;
} WeaponKindEntry;

extern WeaponKindEntry D_00318EB8[];
extern int CheckWeaponKind(void *w);
extern float *test_CURRENTROOT(void *gobj);
extern void _OrientGV(float *dst, float *a, float *b);
extern void sceVu0ScaleVector(void *dst, void *src, float s);

/* the 0x5C word is written through a union view at this one site: the ROM pins the
   weapon-table flag load behind this store, which only an alias-set-0 store does */
union PackPowerWord {
    float f;
    int i;
    int m;
};

extern int GetMotionFrameFlag1(char *gobj);
extern void WeaponCurPos(void *w, float *a, float *b, float *c);
extern int GetSkeltonFocusNode(char *gobj, int node);
extern void sceVu0AddVector(void *d, void *a, void *b);
extern int actEnemy_isLargeEnemy(char *gobj);

/* listing lines 296-308 */
static inline int GetAttackKindIndex(char *p)
{
    int id = *(int *)(p + 0x4A0);
    int i;
    int m;

    for (i = 0; i < 20; i++) {
        if (id == attackData[i].f10) {
            return i;
        }
    }
    return 0;
}

/* listing lines 315-319 */
static inline void GetFocusNodePos(char *gobj, int node, float *out)
{
    int idx = GetSkeltonFocusNode(gobj, node);
    float *m = (float *)((idx << 6) + *(int *)(*(char **)(gobj + 0x15C) + 0xC));

    out[0] = m[12];
    out[1] = m[13];
    out[2] = m[14];
}

void MakeAttackPack_Actor(AttackPack *pack, char *gobj, void *weapon)
{
    float v0[4];
    float v1[4];
    char *ext;
    int k;
    int wk;

    ext = *(char **)(gobj + 0x164);
    k = GetAttackKindIndex(*(char **)(gobj + 0x15C));
    *pack = attackPackInit;
    pack->actor = gobj;
    if (k == 0) {
        return;
    }
    if (GetMotionFrameFlag1(gobj) == 0) {
        return;
    }
    pack->group = k;
    pack->group2 = *(int *)(ext + 0x450) | (k << 16);
    switch (attackData[k].b0) {
    case 1:
        if (weapon == 0) {
            return;
        }
        wk = CheckWeaponKind(weapon);
        WeaponCurPos(weapon, pack->center, pack->from, pack->to);
        pack->radius0 = (D_00318EB8 + wk)->f00;
        pack->radius1 = 20.0f;
        ((union PackPowerWord *)&pack->power)->f = attackData[k].f1C * D_00318EB8[wk].f08;
        pack->active = 1;
        pack->f60 = ((D_00318EB8 + wk)->f20 >> 1) & 1;
        if (pack->f60 == 0) {
            return;
        }
        _OrientGV(v0, pack->center, pack->to);
        _OrientGV(v1, pack->from, pack->to);
        sceVu0ScaleVector(v0, v0, pack->radius0);
        sceVu0ScaleVector(v1, v1, pack->radius0);
        sceVu0AddVector(pack->center, pack->to, v0);
        sceVu0AddVector(pack->from, pack->to, v1);
        break;

    case 0:
        GetFocusNodePos(gobj, attackData[k].f14, v0);
        pack->center[0] = v0[0];
        pack->center[1] = v0[1];
        pack->center[2] = v0[2];
        pack->from[0] = v0[0];
        pack->from[1] = v0[1];
        pack->from[2] = v0[2];
        if (attackData[k].b4 != 0) {
            pack->to[0] = test_CURRENTROOT(gobj)[0];
            pack->to[1] = test_CURRENTROOT(gobj)[1];
            pack->to[2] = test_CURRENTROOT(gobj)[2];
            pack->radius0 = _DistGV(pack->to, pack->center);
        } else {
            pack->to[0] = v0[0];
            pack->to[1] = v0[1];
            pack->to[2] = v0[2];
            pack->radius0 = attackData[k].f18;
        }
        pack->radius1 = attackData[k].f18;
        pack->power = attackData[k].f1C;
        pack->active = 1;
        if (*(int *)(gobj + 0xC) == 4) {
            if (actEnemy_isLargeEnemy(gobj) != 0) {
                pack->radius0 = pack->radius0 * 4.0f;
                pack->radius1 = pack->radius1 * 4.0f;
            }
            if (*(int *)(gobj + 0xC) == 4) {
                if ((*(int *)(*(int *)(*(char **)(gobj + 0x164) + 0x680) + 0x210) & 1) != 0) {
                    pack->f01 = 1;
                }
            }
        }
        break;
    }
}

/* listing lines ~405-435: shared by _AttackCenter and AttackCenter_WithDir */
static inline void SetupAttackPack(AttackPack *pack, char *gop, int group, float *pos, float *ofs,
                                   float radius)
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

/* GObj kind -> attack class, terminated by kind -1 */
static const AttackGroupTable attackGroupTable = {
    {{1, 0}, {4, 1}, {47, 1}, {54, 1}, {53, 1}, {53, 1}, {62, 1}, {2, 3}, {63, 1}, {-1, 0}}};

int AttackCheckSameGroup(char *self, char *other, char *third)
{
    AttackGroupTable tbl = attackGroupTable;
    unsigned int g0 = 2;
    unsigned int g1 = 2;
    int i;
    int m;
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

extern char *D_00639EA4;
extern int CheckWeaponKind(void *w);
extern int iosOmSendMail(void *gobj, int mail, void *arg);
extern float *test_CURRENTROOT(void *gobj);
extern void _OrientGV(float *dst, float *a, float *b);
extern int BreakItemWithAttackHit(char *gobj, float *dir);
extern void GetRootPosition(void *dst, void *self);
extern void sceVu0ScaleVector(void *dst, void *src, float s);

void AttackMail(char *self, AttackPack *pack)
{
    float v0[4];
    float v1[4];
    float v2[4];
    char *attacker;
    char *aext;
    int e;
    float *r0;
    void *weapon;
    int group;
    int kind;
    int hard;
    float power;

    attacker = (char *)pack->actor;
    aext = *(char **)(attacker + 0x164);
    group = pack->group;
    weapon = 0;
    if (aext != 0) {
        weapon = *(void **)(aext + 0x150);
    }
    hard = 0;
    if (group < 0) {
        power = 10.0f;
    } else if (weapon == 0) {
        power = attackData[group].f1C;
    } else {
        kind = CheckWeaponKind(weapon);
        power = attackData[group].f1C * D_00318EB8[kind].f08;
        hard = (D_00318EB8 + kind)->f20 & 1;
    }
    iosOmSendMail(self, 13, attacker);

    if (*(int *)(self + 0xC) == 19) {
        if (pack->hasDir != 0) {
            sceVu0ScaleVector(v0, pack->dir, -1.0f);
        } else {
            r0 = test_CURRENTROOT(attacker);
            _OrientGV(v0, r0, test_CURRENTROOT(self));
        }
        BreakItemWithAttackHit(self, v0);
    }

    e = *(int *)(self + 0x164);
    if (e != 0 && e + 0x1B0 != 0 && *(int *)(e + 0x680) != 0) {
        *(char **)(e + 0x1B0) = attacker;
        *(int *)(e + 0x1D0) = (int)power;
        *(int *)(*(int *)(self + 0x164) + 0x1D4) = pack->group2;
        *(char *)(*(int *)(self + 0x164) + 0x1D8) = attackData[group].b1 || pack->f01;
        *(char *)(*(int *)(self + 0x164) + 0x1DB) = attackData[group].b2 || hard;
        *(char *)(*(int *)(self + 0x164) + 0x1D9) = attackData[group].b3;
        if (attacker == D_00639EA4) {
            *(unsigned long long *)(aext + 0x20) &= ~0x100000000ULL;
        }
        GetRootPosition(v0, attacker);
        GetRootPosition(v1, self);
        sceVu0SubVector(v2, v0, v1);
        sceVu0Normalize(v2, v2);
        *(float *)(*(int *)(self + 0x164) + 0x1C0) = v2[0];
        *(float *)(*(int *)(self + 0x164) + 0x1C4) = v2[1];
        *(float *)(*(int *)(self + 0x164) + 0x1C8) = v2[2];
        if (pack->hasDir != 0) {
            sceVu0ScaleVector((void *)(*(int *)(self + 0x164) + 0x1C0), pack->dir, -1.0f);
        }
    }
}

extern float QueenBallRadius(char *gobj);
extern int QueenBarrierInqBreakable(void);
extern float QueenBarrierRadius(char *gobj);
extern float _ACTGame_GetParamF(int idx);
extern float GetAttackCheckBoundaryRadius(char *gobj);
extern void _InterGV(float *dst, float *a, float *b, float ta, float tb);
extern float _DistSqGV(void *a, void *b);

int AttackCheckHit(AttackPack *pack, char *gobj, short *out)
{
    float w[4];
    unsigned char flags[112];
    float v[3][4];
    float acc[4];
    char *sk;
    int n;
    int i;
    int m;
    int j;
    int hitR;
    float rad;
    float t;

    sk = *(char **)(gobj + 0x15C);
    n = *(int *)(sk + 0x88);
    if (n == 0) {
        n = 1;
    }
    switch (*(int *)(gobj + 0xC)) {
    case 53:
        rad = QueenBallRadius(gobj);
        rad = rad + _ACTGame_GetParamF(31);
        hitR = (int)rad;
        i = 0;
        break;

    case 54:
        if (QueenBarrierInqBreakable() == 0) {
            hitR = 0;
            i = 0;
            break;
        }
        rad = QueenBarrierRadius(gobj);
        rad = rad + _ACTGame_GetParamF(32);
        hitR = (int)rad;
        i = 0;
        break;

    case 63:
        hitR = (int)GetAttackCheckBoundaryRadius(gobj);
        i = 0;
        break;

    case 19:
    case 62:
        hitR = 50;
        i = 0;
        break;

    case 4:
        hitR = (int)(*(float *)(*(int *)(*(char **)(gobj + 0x164) + 0x680) + 0x1E0) * 30.0f);
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
    if (pack->f60 != 0) {
        v[0][0] = test_CURRENTROOT(pack->actor)[0];
        v[0][1] = test_CURRENTROOT(pack->actor)[1];
        v[0][2] = test_CURRENTROOT(pack->actor)[2];
        v[1][0] = pack->center[0];
        v[1][1] = pack->center[1];
        v[1][2] = pack->center[2];
        v[2][0] = pack->from[0];
        v[2][1] = pack->from[1];
        v[2][2] = pack->from[2];
        acc[0] = 0.0f;
        acc[1] = 0.0f;
        acc[2] = 0.0f;
        for (m = 0; m < 3; m++) {
            sceVu0AddVector(acc, acc, v[m]);
        }
        sceVu0ScaleVector(acc, acc, 0.33333334f);
        rad = _DistGV(acc, v[0]);
        for (m = 0; m < 3; m++) {
            sceVu0SubVector(v[m], v[m], acc);
        }
        for (m = 0; m < 3; m++) {
            sceVu0ScaleVector(v[m], v[m], (rad + 30.0f) / rad);
        }
        for (m = 0; m < 3; m++) {
            sceVu0AddVector(v[m], v[m], acc);
        }
        for (i = 0; i < n; i++) {
            if (inner_check((float *)(*(int *)(sk + 0xC) + (i << 6) + 0x30), v[0], v[1], v[2], 0.0f,
                            100.0f) != 0) {
                flags[i] = 1;
            }
        }
    } else {
        for (t = 0.0f; t < pack->radius0; t += pack->radius1) {
            _InterGV(w, pack->to, pack->center, t, pack->radius0 - t);
            for (i = 0; i < n; i++) {
                if (_DistSqGV((float *)(*(int *)(sk + 0xC) + (i << 6) + 0x30), w) <
                    ((float)hitR + pack->radius1) * ((float)hitR + pack->radius1)) {
                    if (!(_DistSqGV((float *)(*(int *)(sk + 0xC) + (i << 6) + 0x30), w) <
                          ((float)hitR + pack->thickness) * ((float)hitR + pack->thickness))) {
                        flags[i] = 1;
                    }
                }
            }
        }
    }
    for (i = 0, j = 0; i < n; i++) {
        if (flags[i] != 0) {
            if (out != 0) {
                out[j] = i;
            }
            j++;
        }
    }
    if (out != 0) {
        out[j] = -1;
    }
    return j;
}

extern char *D_00639EA8;
extern int D_0063B23C;
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char *isysGObjGetExist_begin(void);
extern char *isysGObjGetExist_next(char *gobj);
extern int ACTChkAttackIgnore_BOY(char *gobj, void *actor);
extern int ACTChkAttackIgnore_GIRL(char *gobj, void *actor);
extern int ACTChkAttackIgnore_ENEMY(char *gobj, void *actor);
extern int AttackCheckHit(AttackPack *pack, char *gobj, short *out);

#define EXT(o) (*(char **)((o) + 0x164))

int AttackGenerate(AttackPack *pack)
{
    char *g;
    char *hit;
    int arg;

    hit = 0;
    if (pack->active == 0) {
        return 0;
    }
    debug_StdPrintfDummy("flag ok\n");
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        if (*(int *)(g + 0x16C) == 0) {
            continue;
        }
        if (AttackCheckSameGroup(pack->actor, g, (char *)pack->f08) != 0) {
            continue;
        }
        debug_StdPrintfDummy("group ok\n");
        if (!((EXT(g) != 0 && EXT(g) + 0x1B0 != 0 && *(int *)(EXT(g) + 0x680) != 0) ||
              *(int *)(g + 0xC) == 19)) {
            continue;
        }
        if (EXT(g) != 0 && EXT(g) + 0x1B0 != 0 && *(int *)(EXT(g) + 0x680) != 0 &&
            *(char *)(EXT(g) + 0x1DA) != 0) {
            continue;
        }
        debug_StdPrintfDummy("invincible ok\n");
        if (g == D_00639EA4 && ACTChkAttackIgnore_BOY(g, pack->actor) != 0) {
            continue;
        }
        if (g == D_00639EA8 && ACTChkAttackIgnore_GIRL(g, pack->actor) != 0) {
            continue;
        }
        if (*(int *)(g + 0xC) == 4 && ACTChkAttackIgnore_ENEMY(g, pack->actor) != 0) {
            continue;
        }
        arg = 0;
        if (EXT(g) != 0 && EXT(g) + 0x1B0 != 0) {
            if (*(int *)(EXT(g) + 0x680) != 0) {
                arg = *(int *)(EXT(g) + 0x680) + 0xF0;
            }
        }
        if (AttackCheckHit(pack, g, (short *)arg) == 0) {
            continue;
        }
        debug_StdPrintfDummy("geometry ok\n");
        if (EXT(g) != 0 && *(int *)(EXT(g) + 0x1B0) != 0 &&
            *(int *)(EXT(g) + 0x1D4) == pack->group2) {
            debug_StdPrintfDummy("id equal error\n");
            continue;
        }
        if (D_0063B23C != 0 && pack->actor == D_00639EA4 && *(int *)(g + 0xC) == 4 &&
            ((int)(*(unsigned long long *)(EXT((char *)pack->actor) + 0x20) >> 32) & 1) == 0) {
            continue;
        }
        AttackMail(g, pack);
        hit = g;
        debug_StdPrintfDummy("mail send ok [%d]\n", pack->group2);
        if (EXT(hit) != 0 && *(int *)(EXT(hit) + 0x1B0) != 0 && *(int *)(hit + 0xC) == 4) {
            _OrientGV((float *)(*(int *)(EXT(hit) + 0x680) + 0xE0), pack->center, pack->from);
        }
    }
    return (int)hit;
}

inline void CommonAttackCenter(char *a0)
{
    AttackPack pack;
    MakeAttackPack_Actor(&pack, a0, *(void **)(*(char **)(a0 + 0x164) + 0x150));
    AttackGenerate(&pack);
}

inline int _AttackCenter(char *gop, int group, float *pos, float *ofs, float radius, int kind)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(__FILE__, 931);
        __assert(__FILE__, 931, "gop!=NULL");
    }
    SetupAttackPack(&pack, gop, group, pos, ofs, radius);
    pack.f08 = kind;
    return AttackGenerate(&pack);
}

inline void AttackCenter_WithDir(char *gop, int group, float *pos, float *dir, float radius)
{
    AttackPack pack;

    if (gop == 0) {
        debug_assert(__FILE__, 951);
        __assert(__FILE__, 951, "gop!=NULL");
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
