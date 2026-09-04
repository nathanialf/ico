#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/itou_boss", effect_end_func);
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", bossCtrlBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", BossEnemyFunc);
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", func_001A08F8);
extern unsigned char D_006E9A30[];
extern void memset(void *a0, int a1, int a2);

void itou_boss_gflag_init(void) {
    memset(D_006E9A30, 0, 0xD50);
}
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", BossCtrlDL);
extern int stage_no;
int InqCapsuleGhostBossStage(void) {
    int r = 0;
    if (stage_no == 0x56 || stage_no == 3 || stage_no == 0x2E) r = 1;
    return r;
}
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", actBossCtrlStart);
extern char D_005557E0[];
extern char D_005564F0[];
extern char D_00556860[];
extern char D_00556870[];
extern void *D_0063A438;
extern signed char D_006E9A40[];
extern void actInitialize();
extern void actInitialize_ext_charcter(void *a0);
extern void debug_StdPrintfDummy(char *msg, int n);
extern void ico_m33_to_quat(void *a0, void *a1);
extern int iosMallocDebug(void *ptr, int a1, char *file, int line);
extern void sceVu0CopyVector(void *a0, void *a1);

int InitBossCtrlGeo(void *a0) {
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
    q_arr = (char (*)[])&D_005557E0;
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
void CapsuleGhostBossStart(void) {
    D_006E9A30[0] = 1;
}
INCLUDE_ASM("asm/nonmatchings/src/itou_boss", InqCapsuleGhostBossEnd);
extern char *GetParticleEffectData(void);
void gene_eff_end_func(void) {
    **(int **)(GetParticleEffectData() + 0x70) = 1;
}
