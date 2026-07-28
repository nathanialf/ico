#include "common.h"






extern void func_00132DC0();
extern int  D_00633CB8[2];
extern int  D_006A94E0[];
extern int  D_00633CC0;
extern int func_0025DF50(unsigned long long a0);
INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmStop);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmOpen);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmClose);

void AdpcmInterStereoVolumeSet(int a0)
{
    func_0025DF50(*(long long *)(a0 + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmInterLeaveVolumeSet);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmVolumeSet);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", adpcmPauseRequest);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmIopBuffAlloc);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmOpenSync);

void func_00140B70(int val) {
    D_00633CC0 = val;
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140B78);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140BE0);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmUseAreaGet);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", func_00140D58);

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", AdpcmFreeAreaGet);

void AdpcmInterStereoVolumeSetAll(short a0)
{
    int *p = D_006A94E0;
    int *end = (int *)((char *)p + 0xB0);
    do {
        if (*p != 0) {
            *(short *)((char *)p + 0x44) = a0;
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);
}

int AdpcmInterLeaveVolumeGet(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v != 0) count = next;
    } while (n >= 0);
    return count;
}

int AdpcmVolumeGet(void)
{
    int count = 0;
    int *p = D_00633CB8;
    int n = 1;
    do {
        int v = *p;
        int next = count + 1;
        p++;
        n--;
        if (v == 0) count = next;
    } while (n >= 0);
    return count;
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", GetDitchPosition);

short DebugActOrientFlag(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}

short ACTGetEnvironment(char *self) {
    return *(short *)(*(char **)(self + 0x2C) + 0x3C);
}

INCLUDE_ASM("asm/nonmatchings/sound/adpcm_init", ACTSetEnvAllmighty);

void GetSofaPosition(void) {}

void GetCollisCenterPositionSimple(void) {}

int CheckWallAttributeEdegWall(int a0, int a1)
{
    func_00132DC0(a0, *(int *)(a1 + 0xC), 0x5C000);
    return 1;
}

void func_00141160(void) {}

