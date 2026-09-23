#include "common.h"
#include "itou_boss.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "act-game.h"
#include "act.h"
#include "enemy_act.h"
#include "script.h"
#include "Matrix.h"
#include "StageAnimation.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "quaternion.h"
#include "generator.h"
#include "sugiCommon.h"
#include <string.h>
#include <libvu0.h>

extern signed char D_006E9A40[];
/* kept local: this TU's uses of GetParticleEffectData do not fit the prototype in particleEffect.h */
extern char *GetParticleEffectData();
/* kept local: this TU's uses of pbga_start do not fit the prototype in itou_sub.h */
extern void pbga_start(void *a0, int a1);

void effect_end_func(void *a0)
{
    signed char *e;

    if (isysGObjSearchFromObjKindID_begin(65) != 0) {
        e = D_006E9A40 + *(int *)(GetParticleEffectData(a0) + 0x70) * 0x40;
        pbga_start(e, 0x228);
        _CopyVector(*(char **)e + 0x20, e + 0x20);
        CopyQuaternion(*(char **)e + 0x30, e + 0x10);
        e[4] = 2;
        ExecuteSEPackage(0, 0x65);
    }
}

/* kept local: this TU's uses of GatherEffect_Set do not fit the prototype in gather_effect.h */
extern int GatherEffect_Set(int kind, void *pos, void *tmpl, void *v, void *fn, float f);

void bossCtrlBeforeFunc(char *self)
{
    int buf[0x35];
    float pos[4];
    char *p;
    char *e;
    int idx;
    signed char *e2;
    int i;
    unsigned int j;
    int cnt;
    int r;

    p = self + 0x54;
    for (i = 0; i < *(int *)(p + 4); i++) {
        e = p + (i * 8 + 8);
        if (*(int *)e == 18) {
            if (*(int *)(e + 4) != 0) {
                cnt = 0;
                for (j = 0; j < 53; j++) {
                    if (D_006E9A40[j * 0x40 + 4] == 0) {
                        buf[cnt++] = j;
                    }
                }
                if (cnt > 0) {
                    idx = buf[(int)(random_unit() * cnt)];
                    e2 = D_006E9A40 + idx * 0x40;
                    GetRootPosition(pos, *(int *)(e + 4));
                    r = GatherEffect_Set(12, pos, IdentityQuaternion, e2 + 0x20,
                                         (void *)effect_end_func, 1.0f);
                    if (r >= 0) {
                        *(int *)(GetParticleEffectData(r) + 0x70) = idx;
                        e2[4] = 1;
                    }
                }
            }
            ExecuteSEPackage((int)self, 100);
        }
    }
    *(int *)(p + 4) = 0;
}

extern unsigned char D_006E9A30[];
extern int stage_no;

/* INTERIM: the January listing inlines InqCapsuleGhostBossStage into
   BossEnemyFunc, but this TU's own out-of-line copy has to stay at its ROM
   slot, so the caller uses this stand-in until the tail is all C. */
static inline int InqCapsuleGhostBossStage_stand_in(void)
{
    int r = 0;
    if (stage_no == 0x56 || stage_no == 3 || stage_no == 0x2E)
        r = 1;
    return r;
}

void BossEnemyFunc(void *self)
{
    if (*(signed char *)D_006E9A30 != 0 && InqCapsuleGhostBossStage_stand_in() != 0) {
        _ACTSetEnemyDisappearSpeed(self, 6.0f);

        switch (*(int *)(*(char **)((char *)self + 0x15C) + 0x4A0)) {
        default:
            break;
        case 905:
            ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 2.0f, 0);
            break;
        case 955:
        case 956:
        case 957:
            ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 2.0f, 0);
            break;
        case 927:
        case 928:
        case 929:
            ACTGame_SetMotionPlaySpeedRatio_Reserve(self, 1.2f, 0);
            break;
        }
    }
}

extern volatile int D_006EA780[];
extern int D_0028F8F0[];
extern int D_0028F4C0[];
extern char D_00556840[];
extern char *D_00639EA4;
extern int D_0063B13C;
extern int D_0063C2EC;
extern int D_0063C2F0;
/* kept local: this TU's uses of ico_m33_to_quat do not fit the prototype in itou_sub.h */
extern void ico_m33_to_quat(void *a0, void *a1);
extern void gene_eff_end_func(void);
/* defined in ico2/sugipon/src/particleEffect.c; no header declares it */
extern void SetParticleEffectClipEnableFlag(int a0, int a1);

/* listing lines 157-162: send an enemy off-world and clear its live flag
   (inlined into actBossCtrlStart and into the census gene_enemy below) */
static inline void sendEnemyAway(char *o)
{
    float pos[4];
    pos[2] = pos[1] = pos[0] = 4294967296.0f;
    pos[3] = 0.0f;
    SetRootPosition(o, pos);
    *(int *)(*(char **)(o + 0x15C) + 0x74) = 0;
}

/* listing lines 150-155: drop an enemy at a position and mark its actor live
   (inlined only into the census gene_enemy below) */
static inline void putEnemyAt(char *o, float *pos)
{
    SetRootPosition(o, pos);
    *(int *)(*(char **)(o + 0x15C) + 0x74) = 1;
}

/* census gene_enemy, a file static (MAIN.MAP puts the only global gene_enemy in
   queen.o), so it is spelled `static gene_enemy` here; the global of that name
   lives in ico2/ito/src/queen at 0x001A2A10. Do not make it global. */
static void gene_enemy(volatile int a0)
{
    int no = D_0063C2EC;
    volatile int *flag = &D_006EA780[D_0063C2EC++];
    signed char *buf[53];
    char *o;
    void *c;
    signed char *p;
    int i;
    unsigned int j;
    int total;
    int alive;
    int freen;
    int num;

    _ACTWait(1);

    i = 0;
    for (o = (char *)isysGObjSearchFromObjKindID_begin(0x21); o != 0;
         o = (char *)isysGObjSearchFromObjKindID_next(o), i++) {
        if (i == no) {
            break;
        }
    }

    for (;; _ACTWait(1)) {
        total = 0;
        alive = 0;
        if (stage_no == 0x56) {
            if ((D_0028F8F0[1] & 0x40) != 0) {
                D_006E9A30[0] = 1;
            }
        }
        if (*(signed char *)D_006E9A30 != 0) {
            c = isysGObjSearchFromObjKindID_begin(4);
            while (c != 0) {
                total++;
                if (isEnemyHyde(c) == 0) {
                    alive++;
                }
                c = isysGObjSearchFromObjKindID_next(c);
            }
            if ((D_0063B13C & 1) != 0) {
                debug_Printf(10, 90, 0xFFFFFFFF, D_00556840, alive, total);
            }
            num = 0;
            freen = 0;
            for (j = 0; j < 53; j++) {
                p = D_006E9A40 + j * 0x40;
                if (p[4] <= 0 && p[0x34] == 0) {
                    buf[num++] = p;
                }
                if (p[4] <= 0) {
                    freen++;
                }
            }
            if (total >= freen) {
                total = freen;
            }
            if (alive + D_0063C2F0 < total && num > 0 && o != 0) {
                float pp[4];
                float pos[4];
                float dir[4];
                float m[4][4];
                signed char *sel;
                /* RULING-VESTIGIAL-EXCEPTION (supervisor 2026-09-24, under the user's
                   2026-09-21 standard for dead assignments the ROM proves).
                   The initialiser is dead (r is set from GatherEffect_Set below
                   before any read) and flow deletes it after loop, so it emits
                   no bytes; the declaration form follows this TU's own
                   `int r = 0;` in InqCapsuleGhostBossStage. What the bytes pin:
                   the outer loop reached loop.c's first pass with 231 or more
                   real insns (230 without this line). The threshold is
                   1 + 63 non-fixed registers = 64, less 3 per move, so after
                   six moves the q copy (life 5) needs 46 * 5 >= insns; at 230
                   it moves in the first pass ahead of the inline pos copy and
                   the preheader reads `daddu $30,$17` before `daddu $21,$16`,
                   at 231 or more it is left for the second pass and follows
                   it as in the ROM. What they cannot pin: which dead
                   statement it was, its text or its line (SRCFILE.TXT rows
                   240 to 245 above the first statement are code-free, as a
                   deleted initialiser's row is). */
                int r = 0;

                sel = buf[(int)(random_unit() * num)];
                sceVu0CopyVector(pos, *(char **)(sel + 0x30));
                D_0063C2F0++;
                sel[0x34] = 1;
                *flag = 0;
                r = GatherEffect_Set(12, sel + 0x20, sel + 0x10, pos, (void *)gene_eff_end_func,
                                     1.0f);
                if (r >= 0) {
                    *(volatile int **)(GetParticleEffectData(r) + 0x70) = flag;
                    SetParticleEffectClipEnableFlag(r, 0);
                    ExecuteSEPackage(a0, 0x63);
                    while (*flag == 0) {
                        _ACTWait(1);
                    }
                }
                putEnemyAt(o, pos);
                GetRootPosition(pp, D_00639EA4);
                sceVu0SubVector(dir, pp, pos);
                sceVu0Normalize(dir, dir);
                sceVu0UnitMatrix(m);
                m[1][0] = 0.0f;
                m[1][1] = 1.0f;
                m[1][2] = 0.0f;
                m[1][3] = 0.0f;
                sceVu0CopyVector(m[2], dir);
                sceVu0OuterProduct(m[0], m[1], m[2]);
                /* SRCFILE.TXT rows 277-278 and 281 are code-free around the two
                   q statements (279, 280): q has its own block */
                {
                    float q[4];
                    ico_m33_to_quat(q, m);
                    SetRootQuaternion(o, q);
                }
                Generator_Call(o);
                while (GeneratorWorkEnd(o) == 0) {
                    _ACTWait(1);
                }
                D_0063C2F0--;
                sel[0x34] = 0;
                _ACTWait(((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 5);
                sendEnemyAway(o);
            }
        }
    }
}

void BossCtrlGeo(void *self)
{
    if (*(signed char *)D_006E9A30 != 0)
        scpWakeupEnemyAll();
    else
        scpSleepEnemyAll();
}

void itou_boss_gflag_init(void)
{
    memset(D_006E9A30, 0, 0xD50);
}

extern int D_0063B13C;
extern char D_00556880[];

void BossCtrlDL(void)
{
    signed char *base;
    signed char *e;
    unsigned int k;
    int n;

    n = 0;
    base = D_006E9A40;
    for (k = 0; k < 53; k++) {
        e = base + k * 0x40;
        if (e[4] >= 2) {
            if (stage_DispBgAnimation(e) != 0) {
                pbga_start(e, 0x229);
                _CopyVector(*(char **)e + 0x20, e + 0x20);
                CopyQuaternion(*(char **)e + 0x30, e + 0x10);
            }
        }
        if (e[4] != 0) {
            n++;
        }
    }
    if ((D_0063B13C & 1) != 0) {
        debug_Printf(10, 60, 0xFFFFFFFF, D_00556880, n, 53);
    }
}

int InqCapsuleGhostBossStage(void)
{
    int r = 0;
    if (stage_no == 0x56 || stage_no == 3 || stage_no == 0x2E)
        r = 1;
    return r;
}

extern char D_00556850[];
extern int D_0063C2EC;
extern int D_0063C2F0;

/* listing lines 327-333: the boss controller's actor start */
static inline void bossCtrlInit(void *a0)
{
    actInitialize(a0);
    _ACTWait(1);
    D_0063C2F0 = 0;
}

void actBossCtrlStart(void *a0)
{
    int no;
    char *o;
    int i;

    no = 0;
    bossCtrlInit(a0);
    D_0063C2EC = 0;
    o = (char *)isysGObjSearchFromObjKindID_begin(33);
    while (o != 0) {
        sendEnemyAway(o);
        no++;
        o = (char *)isysGObjSearchFromObjKindID_next(o);
    }
    debug_StdPrintfDummy(D_00556850, no);
    for (i = 0; i < no; i++) {
        actCreateSubThread(gene_enemy, 21);
    }
}

extern char D_005557E0[];
extern char D_005564F0[];
extern char D_00556860[];
extern char D_00556870[];
extern void *D_0063A438;
/* kept local: this TU's uses of ico_m33_to_quat do not fit the prototype in itou_sub.h */
extern void ico_m33_to_quat(void *a0, void *a1);

int InitBossCtrlGeo(void *a0)
{
    int ret;
    unsigned int k;
    signed char *base;
    signed char *e;
    char *m;
    char (*q_arr)[];
    char *q;
    char *r;

    ret = iosMallocDebug(D_0063A438, 0, D_00556860, 0x15E);
    actInitialize(a0);
    actInitialize_ext_charcter(a0);
    debug_StdPrintfDummy(D_00556870, 0x35);

    base = D_006E9A40;
    m = (char *)base + 0x20;
    q_arr = (char (*)[]) & D_005557E0;
    r = D_005564F0;
    q = *q_arr;
    k = 0;
    do {
        e = base + k * 0x40;
        *(int *)e = 0;
        if (e[4] == 1) {
            e[4] = 2;
        }
        sceVu0CopyVector(m, q);
        ico_m33_to_quat(m - 0x10, q - 0x30);
        *(char **)(e + 0x30) = r;
        q += 0x40;
        m += 0x40;
        r += 0x10;
        k++;
    } while (k < 0x35);
    return ret;
}

void CapsuleGhostBossStart(void)
{
    D_006E9A30[0] = 1;
}

int InqCapsuleGhostBossEnd(void)
{
    int no = 0;
    unsigned int cnt = 0;
    void *o;

    if (isysGObjSearchFromObjKindID_begin(65) != 0) {
        signed char *base = D_006E9A40;
        unsigned int i = 0;
        do {
            if (base[i * 0x40 + 4] >= 2) {
                cnt++;
            }
            i++;
        } while (i < 0x35);
    }
    o = isysGObjSearchFromObjKindID_begin(4);
    while (o != 0) {
        if (isEnemyHyde(o) == 0) {
            no++;
        }
        o = isysGObjSearchFromObjKindID_next(o);
    }
    return cnt >= 0x35 && no == 0;
}

/* kept local: this TU's uses of GetParticleEffectData do not fit the prototype in particleEffect.h */
extern char *GetParticleEffectData(void);

void gene_eff_end_func(void)
{
    **(int **)(GetParticleEffectData() + 0x70) = 1;
}
