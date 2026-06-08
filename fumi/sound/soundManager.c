#include "common.h"

/* soundManager 0x164 actor-state view (local) */
typedef struct { char _0[0x80]; int f_80; } SndState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", sndBgmReadyNextStage);

extern void debug_assertMessage();
extern char D_006A3370[];

extern char D_00552178[];

extern char D_005CD670[];

int sndInit(void)
{
    char *e = D_006A3370;
    int sz = 0x3C;
    int i = 0x2F;
    do {
        if (*(int *)(e + 0x30) != 0) {
            debug_assertMessage((int)D_00552178, *(short *)(e + 0x10),
                          (unsigned int)(*(int *)(e + 0x38) - (int)D_005CD670) / sz);
        }
        e += 0x40;
        i--;
    } while (i >= 0);
    __asm__ __volatile__("break");
}

extern void debug_DispSEInfo(int x, int y);
extern void soundDataSegNextStageNotUseClose(int *a, int *b);
extern void Ee2Iop(int x, int *p);
extern void soundVBlank(int x);

void sndManager(int *a, int *b)
{
    Ee2Iop(1, a);
    Ee2Iop(2, a);
    soundVBlank(1);
    debug_DispSEInfo(1, 0);
    soundDataSegNextStageNotUseClose(a, b);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143298);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001432E0);

extern void ExecIcoMisc(int a0, int a1);

void func_001433E0(int *a0) {
    ExecIcoMisc(a0[3], a0[2]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001433F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001434C0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143610);

extern void *D_00629DE4, *D_00629DE8;
extern void _ACTGame_SearchGObj(void *a0, int a1, int a2, int a3, void *a4, int a5, int a6);

void func_001438A8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 5, D_00629DE8, 0, 0);
}

void func_001438C8(void) {
    _ACTGame_SearchGObj(D_00629DE4, 1, 4, 0, 0, 0, 0);
}

extern void ACTLookTargetSystem_Exec(void);
extern char D_005521D0[];

void func_001438E8(void) {
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_005521D0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143910);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143B00);

extern void setParticleEffect(int a0, int a1, int a2);

void func_00143DB8(void *a0) {
    int x = *(int *)(*(int *)(*(int *)((char *)a0 + 0x164) + 0x670) + 0x1B8);
    if (x) {
        setParticleEffect(0x1B0, x, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143DE0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00143FB0);

extern void ActPara_GetDefTbl(void *a0, int a1);

void func_001440F0(void *a0) {
    SndState *p = *(SndState **)((char *)a0 + 0x164);
    p->f_80 = 0;
    ActPara_GetDefTbl(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144100);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144260);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001443B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144440);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001446F8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_001449B8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/soundManager", func_00144C10);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552210;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552240;  /* stride 0x4 */

/* end struct shapes */
