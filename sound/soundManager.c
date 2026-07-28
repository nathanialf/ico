#include "common.h"








extern void ActPara_GetDefTbl(char *self, int bit);
extern int setParticleEffect();
extern void ACTLookTargetSystem_Exec(void);
extern int D_00557ED0[];
extern void debug_assertMessage();
extern void _ACTGame_SearchGObj();
extern int *D_00631AE4;
extern void *D_00631AE8;
extern void ExecIcoMisc();
extern unsigned char D_005F2FB8[];
extern void soundAllocIopFree(int a0);
extern void soundSeEnvDefaultSet(int idx);
extern void AdpcmFadeCloseAll(int val);
extern void soundVBlank(int arg);
extern void Ee2Iop();
extern void debug_DispSEInfo(int a0, int a1);
extern void soundDataSegNextStageNotUseClose();
INCLUDE_ASM("asm/nonmatchings/sound/soundManager", sndBgmReadyNextStage);

extern char D_00557E78[];
extern char D_005D49E0[];
extern char D_006A98B0[];

int sndInit(void)
{
    char *e = D_006A98B0;
    int sz = 0x3C;
    int i = 0x2F;
    do {
        if (*(int *)(e + 0x30) != 0) {
            debug_assertMessage((int)D_00557E78, *(short *)(e + 0x10),
                          (unsigned int)(*(int *)(e + 0x38) - (int)D_005D49E0) / sz);
        }
        e += 0x40;
        i--;
    } while (i >= 0);
    __asm__ __volatile__("break");
}

void sndManager(int *a, int *b)
{
    Ee2Iop(1, a);
    Ee2Iop(2, a);
    soundVBlank(1);
    debug_DispSEInfo(1, 0);
    soundDataSegNextStageNotUseClose(a, b);
}

void func_001447E0(int idx)
{
    short new_var;
    soundSeEnvDefaultSet(idx);
    AdpcmFadeCloseAll(0);
    new_var = 0x18C;
    soundAllocIopFree(*((unsigned short *) ((((char *) D_005F2FB8) + (idx * 0x194)) + new_var)));
}

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00144828);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_001448D8);

void func_00144928(int a0)
{
    ExecIcoMisc(*(int *)(a0 + 0xC), *(int *)(a0 + 0x8));
}

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00144938);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00144A08);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00144B58);

void func_00144DF0(void)
{
    _ACTGame_SearchGObj(D_00631AE4, 1, 4, 5, D_00631AE8, 0, 0);
}

void func_00144E10(void)
{
    _ACTGame_SearchGObj(D_00631AE4, 1, 4, 0, 0, 0, 0);
}

void func_00144E30(void)
{
    ACTLookTargetSystem_Exec();
    debug_assertMessage(D_00557ED0);
}

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00144E58);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145048);

void func_00145300(int *a0)
{
    int *v0 = (int *)a0[0x164 / 4];
    int *v1 = (int *)v0[0x670 / 4];
    int a1 = v1[0x1B8 / 4];
    if (a1 == 0) {
        return;
    }
    return setParticleEffect(0x1B1, a1, 1);
}

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145328);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_001454F8);

void func_00145638(int a0)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x90) = 0;
    ActPara_GetDefTbl(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145648);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_001457A8);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145900);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145988);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145C40);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00145FB0);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00146200);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_001466B0);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00147E88);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00148278);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00148340);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00148E60);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00149210);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00149768);

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00149898);

