#include "common.h"


#include "vu0.h"

typedef struct {
    float v[4];
    unsigned short a;
    unsigned short b;
} ClothBuf;
INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", TestDispChainAnimation);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainExWeightGlobalPos);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bindExWeight);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", bind2);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", calc2);

extern int D_00631940;
extern int D_00631970;
extern void _PopCurrentMatrix(int a0);
extern void dpk_SwapBuffer(int a0);
extern void func_0010ECD8(void);
extern void func_0010F630(void);
extern int func_0012FD70(void *a0);
extern void gif_SpriteOffset(int a0);
extern void gif_SpriteOrg(int a0, int a1);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern void prim_DispParticle(int a0, void *a1, void *a2, int a3);
extern void setLight(int a0, int a1, int a2);

void GetChainAnimation(int *a0, void *a1, void *a2) {
    int t;
    dpk_SwapBuffer(2);
    func_0010ECD8();
    setLight(a0[0], 5, D_00631940);
    gif_SpriteOffset(2);
    gsb_SetFrame(1, 7, 0x80);
    gif_SpriteOrg(8, 0);
    func_0010F630();
    _PopCurrentMatrix(D_00631970 + 0x100);
    if (a0[4] != 0) {
        t = func_0012FD70((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    prim_DispParticle(a0[0], a1, a2, t);
}

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", SetChainExtendedWeight);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetClothAnimation);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", clipCylinderCollision);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitChains);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", InitClothes);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispClothMesh);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispMeshWire);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", DispCloth4D);

extern void GetMatrixFromQuaternion(void *a0);
extern void MatrixDrive_GetTurnXAngleZY(void *a0, void *a1, void *a2);
extern void MatrixDrive_PushMatrixWithNoCopy(unsigned short *o1, unsigned short *o2, float x, float y, float z);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E1F8(void *a0, int a1);

void getCloth4D_preProcess(void *a0, int *a1, int count) {
    ClothBuf buf;
    GetMatrixFromQuaternion(a0);
    if (count > 0) {
        char *base = *(char **)a1;
        int off = count * 16;
        MatrixDrive_GetTurnXAngleZY(&buf, base + off, base + (off - 16));
        MatrixDrive_PushMatrixWithNoCopy(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
        func_0010E0B8(a0, (short)-buf.a);
        func_0010E1F8(a0, (short)-buf.b);
    }
}

void proc(int a0, int a1, float f)
{
    *(float *)(a0 + a1 * 0x50 + 0x10) = f;
}

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", getCloth4D);

void getCloth4D_postProcess(int *a0, int a1)
{
    int *p = (int *)((char *)a0 + a1 * 0x50);
    *(float *)((char *)p + 0x10) = -1.0f;
    a0[3] = a0[3] - 1;
}

float GetCloth4D(int a0, float f)
{
    return f / *(float *)(a0 + 0x14);
}

extern char D_00275850[];
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void InitCloth4D(int *a0, int *a1, int *a2) {
    int outer = a2[0];
    int inner = a2[2];
    int i = 0;
    int j;

    if (outer > 0) {
        do {
            for (j = 1; j < inner; j++) {
                char *p = (char *)a0[i];
                MatrixDrive_TurnObjectMatrix(p + j * 16, p);
                MatrixDrive_TurnObjectMatrix((char *)a1[i] + j * 16, D_00275850);
            }
            i++;
        } while (i < outer);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", GetChainNodeGlobalQuaternion);

INCLUDE_ASM("asm/nonmatchings/src/clothAnimation", MoveChainExtendedWeight);

void InitChainVelocity(void)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(t0, 12);
    VU0_QMTC2_NI(t0, 4);
    VU0_NOREORDER_END();
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

void DeleteChainExtendedWeight(void *p0)
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

void GetChainNodeID(void *p0)
{
    VU0_LSV(lqc2, 4, 0x0, a0);
    VU0_V3OP(vmul.xz, 4, 4, 4);
    VU0_V3OP_BC(vaddz.x, 4, 4, 4, z);
    VU0_REG("vrsqrt $Q, $vf0w, $vf4x");
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(v0, 22);
    VU0_MTC1(v0, 0);
    VU0_NOREORDER_END();
}

