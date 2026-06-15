#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", TestDispChainAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainExWeightGlobalPos);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", bindExWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", bind2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", calc2);

extern void dpk_SwapBuffer(int a0);
extern void func_0010F068(void);
extern void setLight(int a0, int a1, int a2);
extern int D_00629C40;
extern void gif_SpriteOffset(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern void gif_SpriteOrg(int a0, int a1);
extern void func_0010F9D0(void);
extern void _PopCurrentMatrix(int a0);
extern int D_00629C70;
extern int func_0012FC48(void *a0);
extern void prim_DispParticle(int a0, void *a1, void *a2, int a3);

void GetChainAnimation(int *a0, void *a1, void *a2) {
    int t;
    dpk_SwapBuffer(2);
    func_0010F068();
    setLight(a0[0], 5, D_00629C40);
    gif_SpriteOffset(2);
    gsb_SetFrame(1, 7, 0x80);
    gif_SpriteOrg(8, 0);
    func_0010F9D0();
    _PopCurrentMatrix(D_00629C70 + 0x100);
    if (a0[4] != 0) {
        t = func_0012FC48((char *)a0 + 0x18);
    } else {
        t = -1;
    }
    prim_DispParticle(a0[0], a1, a2, t);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", SetChainExtendedWeight);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetClothAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", clipCylinderCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitChains);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitClothes);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispClothMesh);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispMeshWire);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", DispCloth4D);

extern void GetMatrixFromQuaternion(void *a0);
extern void MatrixDrive_GetTurnXAngleZY(void *a0, void *a1, void *a2);
extern void MatrixDrive_PushMatrixWithNoCopy(unsigned short *o1, unsigned short *o2, float x, float y, float z);
extern void func_0010E448(void *a0, int a1);
extern void func_0010E588(void *a0, int a1);

typedef struct {
    float v[4];
    unsigned short a;
    unsigned short b;
} ClothBuf;

void getCloth4D_preProcess(void *a0, int *a1, int count) {
    ClothBuf buf;
    GetMatrixFromQuaternion(a0);
    if (count > 0) {
        char *base = *(char **)a1;
        int off = count * 16;
        MatrixDrive_GetTurnXAngleZY(&buf, base + off, base + (off - 16));
        MatrixDrive_PushMatrixWithNoCopy(&buf.a, &buf.b, buf.v[0], buf.v[1], buf.v[2]);
        func_0010E448(a0, (short)-buf.a);
        func_0010E588(a0, (short)-buf.b);
    }
}

void proc(void *a0, int a1, float a2) {
    *(float *)((char *)a0 + a1 * 0x50 + 0x10) = a2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", getCloth4D);

void getCloth4D_postProcess(char *a0, int a1) {
    *(float *)(a0 + a1 * 0x50 + 0x10) = -1.0f;
    *(int *)(a0 + 0xC) -= 1;
}

float GetCloth4D(void *a0, float a1) {
    return a1 / *(float *)((char *)a0 + 0x14);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", InitCloth4D);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", GetChainNodeGlobalQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothAnimation", MoveChainExtendedWeight);

float InitChainVelocity(float a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf4\n"
        "vrsqrt $Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2", "$8");
    return ret;
}

float DeleteChainExtendedWeight(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        ".word 0x4A0403BD\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float GetChainNodeID(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        "vrsqrt $Q, $vf0w, $vf4x\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}
