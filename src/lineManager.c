#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLine);
extern int D_0063B8E8;
extern void gif_SetGsReg();

void Draw2DLineSeg_Start(void)
{
    gif_SetGsReg(0, D_0063B8E8);
}
INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLineSeg_Loop);
INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLineG);
INCLUDE_ASM("asm/nonmatchings/src/lineManager", _getLine);
extern void Draw2DLine();
extern void _FTOI4Vector();
extern int _getLine();

void DrawLine(int *p1, int *p2, int a2, int a3)
{
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    if (_getLine(t0, t1, p1, p2) < 0) return;
    _FTOI4Vector(t2, t0);
    _FTOI4Vector(t3, t1);
    Draw2DLine(t2, t3, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/lineManager", DrawLineG);
