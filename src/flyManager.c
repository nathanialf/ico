#include "common.h"


extern int D_006333D8;
void DispFlyInfo(void) {
    D_006333D8 = 0;
}

extern void ClipWallField(void *a0, int a1);
extern float D_00631250;
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void func_002641D8(void *a0, int a1, int a2);

int InitFlyInfo(char *out, void *a1) {
    char buf[0xC0];
    if (D_006333D8 == 0) {
        return 0;
    }
    func_002641D8(buf, 0, 0xC0);
    MatrixDrive_TurnObjectMatrix(buf, a1);
    MatrixDrive_TurnObjectMatrix(buf + 0x10, a1);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + D_00631250;
    ClipWallField(buf, D_006333D8);
    if (*(int *)(buf + 0x94) != 0) {
        int v = *(int *)(buf + 0x98) & 0xF;
        int n;
        *(float *)out = *(float *)(buf + 0x24);
        if (v == 1) {
            n = 0;
        } else {
            n = v * 100;
        }
        n = -n;
        *(int *)(out + 0xC) = 0;
        *(float *)(out + 0x8) = (float)n;
        *(float *)(out + 0x4) = *(float *)out + (float)n;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/flyManager", InitFlyManager);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", GetFlyLimitHeight);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", GetFlyLimitClearance);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", func_001D0818);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", func_001D0918);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", func_001D0B60);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", func_001D0D18);

INCLUDE_ASM("asm/nonmatchings/src/flyManager", func_001D0FA8);

