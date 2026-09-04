#include "common.h"

#include "vu0.h"

#include "sugiCommon.h"

typedef struct {
    float v[4];
    unsigned short a;
    unsigned short b;
} ClothBuf;

extern void CopyVector(void *dst, void *src);

void GetChainExWeightGlobalPos(int a0, int a1, int a2)
{
    CopyVector(a0, a1 + a2 * 0x50 + 0x30);
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bindExWeight);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bind2);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", calc2);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainAnimation);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", SetChainExtendedWeight);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimation);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", yTension);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", xTension);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimationFix4Points);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", clipCylinderCollision);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitChains);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitClothes);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitClothesNoShade);
extern int buffer_ID;
extern int matrixptr;
extern void _SetCurrentMatrix(int a0);
extern void dl_SetDLPriority(int a0);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetGsReg(int a0, int a1);
extern void gif_StartPacketPri(int a0);
extern void p2o_SetDefaultEnviroment(void);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void prim_UpdateMesh3D(int a0, int a1, int a2);
extern int tex_GetTextureNo(void *a0);

void DispClothMesh(int *a0, void *a1, void *a2) {
    int t;
    dl_SetDLPriority(2);
    p2o_SetDefaultEnviroment();
    prim_UpdateMesh3D(a0[0], 5, buffer_ID);
    gif_StartPacketPri(2);
    gif_SetAlpha(1, 7, 0x80);
    gif_SetGsReg(8, 0);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    if (a0[4] != 0) {
        t = tex_GetTextureNo((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    prim_DispMesh3D(a0[0], a1, a2, t);
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispMeshWire);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispCloth4D);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispCloth4DWithAdd);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D_preProcess);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", proc);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D_postProcess);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", _getCloth4D);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetCloth4D);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetCloth4DWithDetail);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetCloth4DWithTight);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitCloth4D);
extern void MatrixDrive_GetTurnYAngleXZ(unsigned short *o1, unsigned short *o2, float x, float y, float z);
extern void RotQuaternionX(void *a0, int a1);
extern void RotQuaternionZ(void *a0, int a1);
extern void SetIdentityQuaternion(void *a0);
extern void SubVectorXYZ(void *a0, void *a1, void *a2);

void GetChainNodeGlobalQuaternion(void *a0, int *a1, int count) {
    ClothBuf buf;
    SetIdentityQuaternion(a0);
    if (count > 0) {
        char *base = *(char **)a1;
        int off = count * 16;
        SubVectorXYZ(&buf, base + off, base + (off - 16));
        MatrixDrive_GetTurnYAngleXZ(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
        RotQuaternionX(a0, (short)-buf.a);
        RotQuaternionZ(a0, (short)-buf.b);
    }
}
void MoveChainExtendedWeight(int a0, int a1, float f)
{
    *(float *)(a0 + a1 * 0x50 + 0x10) = f;
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitChainVelocity);
void DeleteChainExtendedWeight(int *a0, int a1)
{
    int *p = (int *)((char *)a0 + a1 * 0x50);
    *(float *)((char *)p + 0x10) = -1.0f;
    a0[3] = a0[3] - 1;
}
float GetChainNodeID(int a0, float f)
{
    return f / *(float *)(a0 + 0x14);
}
extern void CopyVector(void *a0, void *a1);
extern char D_0028FEF0[];

void ResetClothAnimation(int *a0, int *a1, int *a2) {
    int outer = a2[0];
    int inner = a2[2];
    int i = 0;
    int j;

    if (outer > 0) {
        do {
            for (j = 1; j < inner; j++) {
                char *p = (char *)a0[i];
                CopyVector(p + j * 16, p);
                CopyVector((char *)a1[i] + j * 16, D_0028FEF0);
            }
            i++;
        } while (i < outer);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainExWeightGlobalQuaternion);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainCollision);
void FSqrtInv(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_WORD(0x4A0403BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZInvLength(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void getXZLengthSquare(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_QMFC2_NI(v0, 4);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}
void subAndGetInvLength(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_V3OP(vsub.xyzw, 4, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}
void scaleAndAddVectorXYZ(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x0, a2);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xyz, 5, 5, 6, x);
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}
void scaleVectorXZ(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 5);
    VU0_NOREORDER_END();
    VU0_V3OP_BC(vmulx.xz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, a0);
    VU0_NOP();
}
void tensionMoveNoReduce(void *a0, void *a1, void *a2, float f12)
{
    int sp_buf[4];
    register float q __asm__("$f0");
    register float scaled __asm__("$f12") = f12;
    VU0_LSV(lqc2, 1, 0x0, a1);
    VU0_LSV(lqc2, 2, 0x0, a2);
    VU0_REG("vsub.xyzw $vf4, $vf1, $vf2");
    VU0_V3OP(vmul.xyz, 3, 4, 4);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_REG("vrsqrt Q, $vf0w, $vf3x");
    VU0_LSV(sqc2, 4, 0x0, sp);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_REG("mul.s $f12, $f12, $f0");
    VU0_NOREORDER_END();

    VU0_LSV(lqc2, 4, 0x0, a2);
    VU0_LSV(lqc2, 5, 0x0, sp);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 6);
    VU0_NOREORDER_END();
    VU0_REG("vmulx.xyz $vf5, $vf5, $vf6x");
    VU0_V3OP(vadd.xyz, 4, 4, 5);
    VU0_LSV(sqc2, 4, 0x0, a0);
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", tensionMove);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCrossPoint);
int checkOverThePlane(void *a0, void *a1)
{
    if (0.0f < plane_distance(a0, a1)) return 1;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", checkFrontAcross);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", LockZAnimation);
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D_planeClip);
