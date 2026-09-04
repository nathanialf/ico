#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", UpdatePointBlur);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyEye);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyFootPrint);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", ExecEnemyFootPrints);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", EntryEnemyFootPrint);
extern void p2o_DispVU1DObj();

int DispEnemyFootPrints(int *a0)
{
    p2o_DispVU1DObj(a0[1]);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitPointBlur);
extern void gif_Draw2DStripG();
extern void gif_EndPacket();
extern void gif_SetAlpha();
extern void gif_StartPacketPri();

int DispPointBlur(int *self)
{
    gif_StartPacketPri(self[0]);
    gif_SetAlpha(1, self[0xD], 0x80);
    gif_Draw2DStripG(self[3], self[4], self[1] * 2, 1);
    gif_EndPacket();
    return 1;
}
extern char D_004E79A0[];
extern char D_004E79E0[];
extern void UpdatePointBlur(int a0, void *a1, void *a2, float a3);
extern void _MulMatrix(void *a0, int a1, void *a2);

int UpdateEnemyEye(char *a0, int a1, float f)
{
    _MulMatrix(a0 + 0x10, a1, D_004E79A0);
    if (*(int *)a0 != 0) {
        UpdatePointBlur(*(int *)(a0 + 0x4), a0 + 0x40, D_004E79E0, f * 3.0f);
    }
    return 1;
}
extern void _CopyMatrix();
extern void reg_DispMultiPri();

int DispEnemyEye(char *a0) {
    _CopyMatrix(*(int *)(*(char **)(a0 + 0x50) + 0xC), a0 + 0x10);
    reg_DispMultiPri(*(int *)(a0 + 0x50), 0xA);
    if (*(int *)a0 != 0) {
        char *fobj = *(char **)(a0 + 0x4);
        gif_StartPacketPri(*(int *)fobj);
        gif_SetAlpha(1, *(int *)(fobj + 0x34), 0x80);
        gif_Draw2DStripG(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        gif_EndPacket();
    }
    return 1;
}
int ResetEnemyEye(char *self) {
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", moveDataElements);
