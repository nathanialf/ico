#include "common.h"
#include "lineManager.h"
#include "GifPacket.h"
#include "typedef.h"

extern int D_0063B8E8;
/* kept local: this TU's uses of _FTOI4Vector do not fit the prototype in Matrix.h */
extern void _FTOI4Vector();
/* kept local: this TU's uses of _InitCurrentMatrix do not fit the prototype in Matrix.h */
extern void _InitCurrentMatrix();
extern int D_0063B8E4;

void Draw2DLine(int *p1, int *p2, int *color, int z)
{
    gif_SetGsReg(0, D_0063B8E4);
    gif_SetGsReg(1, (long long)color[0] | ((long long)color[1] << 8) | ((long long)color[2] << 16) |
                        ((long long)color[3] << 24));
    if (z == 0) {
        gif_SetGsReg(5, (long long)p1[0] | ((long long)p1[1] << 16) | ((long long)p1[2] << 32));
        gif_SetGsReg(5, (long long)p2[0] | ((long long)p2[1] << 16) | ((long long)p2[2] << 32));
    } else {
        gif_SetGsReg(5, (long long)p1[0] | ((long long)p1[1] << 16) | ((long long)z << 32));
        gif_SetGsReg(5, (long long)p2[0] | ((long long)p2[1] << 16) | ((long long)z << 32));
    }
}

void Draw2DLineSeg_Start(void)
{
    gif_SetGsReg(0, D_0063B8E8);
}

void Draw2DLineSeg_Loop(int *a0, int *a1, int *a2)
{
    gif_SetGsReg(1, (long long)a2[0] | ((long long)a2[1] << 8) | ((long long)a2[2] << 16) |
                        ((long long)a2[3] << 24));
    gif_SetGsReg(5, (long long)a0[0] | ((long long)a0[1] << 16) | ((long long)a0[2] << 32));
    gif_SetGsReg(5, (long long)a1[0] | ((long long)a1[1] << 16) | ((long long)a1[2] << 32));
}

extern int D_0063B8EC;

void Draw2DLineG(int *p1, int *c1, int *p2, int *c2, int z)
{
    gif_SetGsReg(0, D_0063B8EC);
    if (z == 0) {
        gif_SetGsReg(1, (long long)c1[0] | ((long long)c1[1] << 8) | ((long long)c1[2] << 16) |
                            ((long long)c1[3] << 24));
        gif_SetGsReg(5, (long long)p1[0] | ((long long)p1[1] << 16) | ((long long)p1[2] << 32));
        gif_SetGsReg(1, (long long)c2[0] | ((long long)c2[1] << 8) | ((long long)c2[2] << 16) |
                            ((long long)c2[3] << 24));
        gif_SetGsReg(5, (long long)p2[0] | ((long long)p2[1] << 16) | ((long long)p2[2] << 32));
    } else {
        gif_SetGsReg(1, (long long)c1[0] | ((long long)c1[1] << 8) | ((long long)c1[2] << 16) |
                            ((long long)c1[3] << 24));
        gif_SetGsReg(5, (long long)p1[0] | ((long long)p1[1] << 16) | ((long long)z << 32));
        gif_SetGsReg(1, (long long)c2[0] | ((long long)c2[1] << 8) | ((long long)c2[2] << 16) |
                            ((long long)c2[3] << 24));
        gif_SetGsReg(5, (long long)p2[0] | ((long long)p2[1] << 16) | ((long long)z << 32));
    }
}

extern char *matrixptr;
extern int D_0063A07C;
extern int D_0063A080;
extern void *MatrixDrive_GetMatrix(void);
/* kept local, as declared in Matrix.h: this TU does not include that header
 * (its _FTOI4Vector and _InitCurrentMatrix do not fit DrawLine's uses) */
extern void _SetCurrentMatrix(void *m);
extern void _MulCurrentMatrixL(void *m);
extern void _ApplyCurrentMatrix(void *dst, void *src);
extern void _CopyVector(void *dst, void *src);

/* Project a 3D segment to screen space and clip it to the screen, answering
 * -1 when it is off screen, else whether the end points were swapped.  The
 * listing puts the parameter moves on line 115 and the helpers' bodies on
 * rows 120 to 223 inside the span, so the helpers are nested inline functions
 * (sugipon's style, as boy.c and staticBlur.c).  Rows 149 to 174 are one
 * helper: the near clip and the projection share its parameter copies ($v0,
 * $a0).  The four VU0 blocks carry no memory clobber, like sugiCommon.h's
 * distance_squared: the ROM keeps o2's first coordinate in a register across
 * the X and Y clips.  The end points are VECTOR initialisers (lines 244 and
 * 245), built in a temporary and block-copied as box.c's are. */
int _getLine(float *o1, float *o2, float *p1, float *p2)
{
    inline void swapVector(float *a, float *b)
    {
        float t[4];

        _CopyVector(t, a);
        _CopyVector(a, b);
        _CopyVector(b, t);
    }

    inline int sortByX(float *a, float *b)
    {
        if (a[0] > b[0]) {
            swapVector(a, b);
            return 1;
        }
        return 0;
    }

    inline int sortByY(float *a, float *b)
    {
        if (a[1] > b[1]) {
            swapVector(a, b);
            return 1;
        }
        return 0;
    }

    inline int sortByZ(float *a, float *b)
    {
        if (a[2] > b[2]) {
            swapVector(a, b);
            return 1;
        }
        return 0;
    }

    inline void perspLine(float *o1, float *o2, float *a, float *b)
    {
        if (a[2] < 1.0f) {
            __asm__ __volatile__(".set noreorder\n\t"
                                 "lqc2 $vf8, 0x0(%0)\n\t"
                                 "lqc2 $vf9, 0x0(%1)\n\t"
                                 "vsub.z $vf14, $vf9, $vf8\n\t"
                                 "vsubz.w $vf15, $vf0, $vf8z\n\t"
                                 "vdiv Q, $vf15w, $vf14z\n\t"
                                 "vsub.xy $vf16, $vf9, $vf8\n\t"
                                 "vwaitq\n\t"
                                 "vmulq.xy $vf16, $vf16, Q\n\t"
                                 "vaddw.z $vf8, $vf0, $vf0w\n\t"
                                 "vadd.xy $vf8, $vf8, $vf16\n\t"
                                 "sqc2 $vf8, 0x0(%0)"
                                 "\n\t.set reorder"
                                 :
                                 : "r"(a), "r"(b));
        }
        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%0)\n\t"
                             "lqc2 $vf9, 0x0(%1)\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf9x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf9y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf9z\n\t"
                             "vmaddw.xyzw $vf11, $vf7, $vf9w\n\t"
                             "vdiv Q, $vf0w, $vf10w\n\t"
                             "vwaitq\n\t"
                             "vmulq.xyzw $vf10, $vf10, Q\n\t"
                             "vdiv Q, $vf0w, $vf11w\n\t"
                             "vwaitq\n\t"
                             "vmulq.xyzw $vf11, $vf11, Q\n\t"
                             "sqc2 $vf10, 0x0(%2)\n\t"
                             "sqc2 $vf11, 0x0(%3)"
                             "\n\t.set reorder"
                             :
                             : "r"(a), "r"(b), "r"(o1), "r"(o2));
    }

    inline void clipAtX(float *d, float *a, float *b, float x)
    {
        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "lqc2 $vf9, 0x0(%2)\n\t"
                             "mfc1 $8, %3\n\t"
                             "qmtc2.ni $8, $vf2\n\t"
                             "vsub.x $vf15, $vf2, $vf8\n\t"
                             "vsub.x $vf14, $vf9, $vf8\n\t"
                             "vdiv Q, $vf15x, $vf14x\n\t"
                             "vmove.x $vf16, $vf2\n\t"
                             "vsub.yz $vf16, $vf9, $vf8\n\t"
                             "vwaitq\n\t"
                             "vmulq.yz $vf16, $vf16, Q\n\t"
                             "vadd.yz $vf16, $vf16, $vf8\n\t"
                             "sqc2 $vf16, 0x0(%0)"
                             "\n\t.set reorder"
                             :
                             : "r"(d), "r"(a), "r"(b), "f"(x));
    }

    inline void clipAtY(float *d, float *a, float *b, float y)
    {
        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "lqc2 $vf9, 0x0(%2)\n\t"
                             "mfc1 $8, %3\n\t"
                             "qmtc2.ni $8, $vf2\n\t"
                             "vsuby.x $vf15, $vf2, $vf8y\n\t"
                             "vsub.y $vf14, $vf9, $vf8\n\t"
                             "vdiv Q, $vf15x, $vf14y\n\t"
                             "vaddx.y $vf16, $vf0, $vf2x\n\t"
                             "vsub.xz $vf16, $vf9, $vf8\n\t"
                             "vwaitq\n\t"
                             "vmulq.xz $vf16, $vf16, Q\n\t"
                             "vadd.xz $vf16, $vf16, $vf8"
                             "\n\tsqc2 $vf16, 0x0(%0)"
                             "\n\t.set reorder"
                             :
                             : "r"(d), "r"(a), "r"(b), "f"(y));
    }

    float r0[4];
    float r1[4];
    int rev = 0;
    VECTOR w0 = {p1[0], p1[1], p1[2], 1.0f};
    VECTOR w1 = {p2[0], p2[1], p2[2], 1.0f};

    _SetCurrentMatrix(MatrixDrive_GetMatrix());
    _MulCurrentMatrixL(matrixptr + 0x80);
    _ApplyCurrentMatrix(r0, &w0);
    _ApplyCurrentMatrix(r1, &w1);

    if (sortByZ(r0, r1))
        rev = !rev;
    if (r1[2] < 1.0f)
        return -1;
    _SetCurrentMatrix(matrixptr + 0xC0);
    perspLine(o1, o2, r0, r1);

    if (sortByX(o1, o2))
        rev = !rev;
    if (2048.0f + D_0063A07C * 0.5f <= o1[0])
        return -1;
    if (o2[0] <= 2048.0f - D_0063A07C * 0.5f)
        return -1;
    if (o1[0] < 2048.0f - D_0063A07C * 0.5f)
        clipAtX(o1, o1, o2, 2048.0f - D_0063A07C * 0.5f);
    if (2048.0f + D_0063A07C * 0.5f < o2[0])
        clipAtX(o2, o1, o2, 2048.0f + D_0063A07C * 0.5f);

    if (sortByY(o1, o2))
        rev = !rev;
    if (2048.0f + D_0063A080 * 0.5f <= o1[1])
        return -1;
    if (o2[1] <= 2048.0f - D_0063A080 * 0.5f)
        return -1;
    if (o1[1] < 2048.0f - D_0063A080 * 0.5f)
        clipAtY(o1, o1, o2, 2048.0f - D_0063A080 * 0.5f);
    if (2048.0f + D_0063A080 * 0.5f < o2[1])
        clipAtY(o2, o1, o2, 2048.0f + D_0063A080 * 0.5f);
    return rev;
}

void DrawLine(int *p1, int *p2, int a2, int a3)
{
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    if (_getLine(t0, t1, p1, p2) < 0)
        return;
    _FTOI4Vector(t2, t0);
    _FTOI4Vector(t3, t1);
    Draw2DLine(t2, t3, a2, a3);
}

void DrawLineG(int *a0, int *a1, int *a2, int *a3, int a4)
{
    int t0[4];
    int t1[4];
    int t2[4];
    int t3[4];
    int r;

    _InitCurrentMatrix();
    r = _getLine(t0, t1, a0, a2);
    if (r == -1) {
        return;
    }
    _FTOI4Vector(t2, t0);
    _FTOI4Vector(t3, t1);
    if (r != 0) {
        Draw2DLineG(t3, a1, t2, a3, a4);
    } else {
        Draw2DLineG(t2, a1, t3, a3, a4);
    }
}
