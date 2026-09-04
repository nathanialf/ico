#include "common.h"






extern void func_0010ECB8();
extern void func_00102858();
extern void memcpy();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int          D_00275860[4];
extern unsigned short D_004B3D50[];
INCLUDE_ASM("asm/nonmatchings/src/icoMisc", gamesysObjInfoPosNewStageSet);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", gamesysObjInfoGet);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", gamesysObjInfoCls);

int gamesysGirlStageGet(void)
{
    if (D_004B3D50[1]) return D_004B3D50[2];
    return 4;
}

int DispIcoMisc(int a0)
{
    if (D_004B3D50[1] != 0) {
        MatrixDrive_TurnObjectMatrix(a0, (int *)((char *)D_004B3D50 + 0x10));
        return D_004B3D50[2];
    }
    MatrixDrive_TurnObjectMatrix(a0, (int *)D_00275860);
    return 4;
}

extern int D_004B3B68[];
extern int D_00632F74;

void gamesysStageExitTimeSet(int a0) {
    D_004B3B68[a0] = D_00632F74;
}

void gamesysMemoryHandlerRead(int *self, int a1, int a2)
{
    if (a1 != 0) {
        memcpy(a1, self[0] + self[0x4 / 4]);
    }
    self[0x4 / 4] = self[0x4 / 4] + a2;
}

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", gamesysMemorySave);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AE948);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AE9A8);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AE9F0);

void func_001AEA50(int a0, int a1, int a2, int a3)
{
    func_00102858(a0, a1, a2, a3);
}

void func_001AEA58(int a0, int a1, int a2, int a3)
{
    func_0010ECB8(a0, a1, a2, a3);
}

int func_001AEA60(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AEA68);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", disp_memory_partition);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF190);

INCLUDE_ASM("asm/nonmatchings/src/icoMisc", func_001AF4A0);

/* .data — carved VMA 0x4BCE90..0x4BCEB0 (2 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004BCE90[4] = {
    0x000000FF, 0x00000080, 0x00000040, 0x00000080,
};
unsigned int D_004BCEA0[4] = {
    0x00000040, 0x00000080, 0x000000FF, 0x00000080,
};

