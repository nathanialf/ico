#include "common.h"






extern int D_00632028;
extern int prim_DeleteParticle();
extern void dpk_SwapBuffer(int a0);
extern char D_00555830[];
extern void dl_GetPri();
extern void dpk_Init();
extern void pac_getWeight();
extern void pac_makeClusterStrip();
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setShape);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispBoxLine);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_clipPacketBoundingBox);

int func_0011E708(int a0, int a1, int a2, int a3)
{
    return prim_DeleteParticle(a0, a1, a2, a3, D_00632028);
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011E728);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_chooseMicroCode);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_chooseSpecularMicroCode);

void reg_chooseReflectionMicroCode(char *a0)
{
    int *p820 = *(int **)(a0 + 0x820);
    if (*((signed char *)p820 + 0x2F) != 0) {
        return pac_makeClusterStrip(3);
    }
    {
        int *p844 = *(int **)(a0 + 0x844);
        if (*(int *)((char *)p844 + 0xF0) == 0) {
            return pac_makeClusterStrip(1);
        }
    }
    return pac_makeClusterStrip(2);
}

void func_0011EE30(char *self, int b, int c)
{
    long long v_ll = *(long long *)(self + 0x60);
    int v_int = *(int *)(self + 0x60);
    pac_getWeight(v_int & 1, ((int)(v_ll >> 5)) & 3, 0, b, c);
}

void func_0011EE58(int a0, int a1, int a2)
{
    pac_getWeight(a0, 1, 1, a1, a2);
}

void reg_setNMatrixPacket(int a0, int a1, int a2)
{
    pac_getWeight(a0, 1, 2, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setMMatrixPacket);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setCMatrixPacket);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_transMaterialPacket);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setDissolve);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_resetDissolve);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispNObj);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispMObj);

extern char D_00555750[];
extern int D_00632CA4;
extern int dl_GetPri__p4(void) __asm__("dl_GetPri");
extern void dpk_Init__p4(int a0, void *a1, int a2) __asm__("dpk_Init");
extern void dpk_SwapBuffer__p4() __asm__("dpk_SwapBuffer");
extern int tex_SetClutAnimation(int a0, int a1);

void reg_dispSObj(char *a0, int a1, int a2) {
    short h;
    dpk_SwapBuffer__p4(4);
    h = *(short *)(a0 + 0x86);
    if (h >= 0) {
        D_00632CA4 += tex_SetClutAnimation(h, 4);
    }
    dpk_Init__p4(2, D_00555750, 5);
    dl_GetPri__p4();
    func_0011EE58(a2, a1, 4);
    dpk_Init__p4(2, *(void **)(a0 + 0x98), (*(int *)(a0 + 0x90) & 0xFFFFFF) >> 4);
    dl_GetPri__p4();
}

void reg_dispCObj(short *self, int *p)
{
    short idx = self[0x80/2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
        dpk_Init(2, v, 6);
        dl_GetPri();
    }
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispPoint);

void reg_dispLine(int a0)
{
    dpk_SwapBuffer(a0);
    dpk_Init(2, D_00555830, 4);
    dl_GetPri();
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispPointLineObj);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setNMatrixPacketNoLightCalc);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispAccessoryWithShadow);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_RenderReflection);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setEMatrixPacket);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispEnemy);

