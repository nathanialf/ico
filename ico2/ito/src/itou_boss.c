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
                    idx = buf[(int)(_GetRandom() * cnt)];
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

/* census gene_enemy, a file static (MAIN.MAP puts the only global gene_enemy in
   queen.o), takes the name as static gene_enemy once this body is C: the stub
   assembles a glabel that would emit a global gene_enemy binding against
   ico2/ito/src/queen's at 0x001A2A10 */
INCLUDE_ASM("asm/nonmatchings/ico2/ito/src/itou_boss", func_001A08F8);

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

/* func_001A08F8 is the census gene_enemy, this TU's static twin of src/queen's
   global; the ROM passes its address as the sub-thread entry. */

/* listing lines 157-162: send an enemy off-world and clear its live flag
   (also inlined into the census gene_enemy at func_001A08F8) */
static inline void sendEnemyAway(char *o)
{
    float pos[4];
    pos[2] = pos[1] = pos[0] = 4294967296.0f;
    pos[3] = 0.0f;
    SetRootPosition(o, pos);
    *(int *)(*(char **)(o + 0x15C) + 0x74) = 0;
}

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
        actCreateSubThread(func_001A08F8, 21);
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
