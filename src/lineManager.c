#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/lineManager", Draw2DLine);
extern int D_0063B8E8;
extern void gif_SetGsReg();

void Draw2DLineSeg_Start(void)
{
    gif_SetGsReg(0, D_0063B8E8);
}
extern void gif_SpriteOrg_ll(int a0, long long a1) __asm__("gif_SetGsReg");

void Draw2DLineSeg_Loop(int *a0, int *a1, int *a2) {
    gif_SpriteOrg_ll(1, (long long)a2[0] | ((long long)a2[1] << 8) | ((long long)a2[2] << 16) | ((long long)a2[3] << 24));
    gif_SpriteOrg_ll(5, (long long)a0[0] | ((long long)a0[1] << 16) | ((long long)a0[2] << 32));
    gif_SpriteOrg_ll(5, (long long)a1[0] | ((long long)a1[1] << 16) | ((long long)a1[2] << 32));
}
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
extern void Draw2DLineG(int *a0, int *a1, int *a2, int *a3, int a4);
extern void _FTOI4Vector__pn(int *out, int *src) __asm__("_FTOI4Vector");
extern void _InitCurrentMatrix();
extern int _getLine__pn(int *t0, int *t1, int *p1, int *p2) __asm__("_getLine");

void DrawLineG(int *a0, int *a1, int *a2, int *a3, int a4) {
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    int r;

    _InitCurrentMatrix();
    r = _getLine__pn(t0, t1, a0, a2);
    if (r == -1) {
        return;
    }
    _FTOI4Vector__pn(t2, t0);
    _FTOI4Vector__pn(t3, t1);
    if (r != 0) {
        Draw2DLineG(t3, a1, t2, a3, a4);
    } else {
        Draw2DLineG(t2, a1, t3, a3, a4);
    }
}
