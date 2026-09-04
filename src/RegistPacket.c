#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setShape);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispBoxLine);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_clipPacketBoundingBox);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_transMicroCode);
extern void mc_SetMicroCode();

void reg_chooseMicroCode(char *self, int b, int c)
{
    long long v_ll = *(long long *)(self + 0x60);
    int v_int = *(int *)(self + 0x60);
    mc_SetMicroCode(v_int & 1, ((int)(v_ll >> 5)) & 3, 0, b, c);
}
void reg_chooseSpecularMicroCode(int a0, int a1, int a2)
{
    mc_SetMicroCode(a0, 1, 1, a1, a2);
}
void reg_chooseReflectionMicroCode(int a0, int a1, int a2)
{
    mc_SetMicroCode(a0, 1, 2, a1, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setMatrix_105);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setLight_109);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setNMatrixPacket);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setMatrix_116);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setLight_120);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setMMatrixPacket);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setCMatrixPacket);
extern char D_0054FB80[];
extern int D_0063B124;
extern void dl_CloseDma();
extern void dl_OpenDma();
extern void dl_SetDLPriority(int a0);
extern int tex_TransTexture(int a0, int a1);

void func_00121428(char *a0, int a1, int a2) {
    short h;
    dl_SetDLPriority(4);
    h = *(short *)(a0 + 0x86);
    if (h >= 0) {
        D_0063B124 += tex_TransTexture(h, 4);
    }
    dl_OpenDma(2, D_0054FB80, 5);
    dl_CloseDma();
    reg_chooseSpecularMicroCode(a2, a1, 4);
    dl_OpenDma(2, *(void **)(a0 + 0x98), (*(int *)(a0 + 0x90) & 0xFFFFFF) >> 4);
    dl_CloseDma();
}
void reg_transMaterialPacket(short *self, int *p)
{
    short idx = self[0x80/2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
        dl_OpenDma(2, v, 6);
        dl_CloseDma();
    }
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setDissolve);
extern char D_0054FC60[];

void reg_resetDissolve(int a0)
{
    dl_SetDLPriority(a0);
    dl_OpenDma(2, D_0054FC60, 4);
    dl_CloseDma();
}
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispNObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispMObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispSObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispCObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispPoint);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispLine);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_dispPointLineObj);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setMatrix_190);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", setLight_194);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setNMatrixPacketNoLightCalc);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispAccessoryWithShadow);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_RenderReflection);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_setEMatrixPacket);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispEnemy);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispMultiPri);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", reg_DispObj);
extern void reg_dispSObj();

void reg_DispObj2(int a0, int a1, int a2, int a3)
{
    reg_dispSObj(a0, a1, a2, a3);
}
extern int D_0063A168;

void reg_SetScissorSw(int val) {
    D_0063A168 = val;
}
extern int tex_TransTexture__pn() __asm__("tex_TransTexture");

void reg_TransTexturePacket(int a0)
{
    if (a0 >= 0) {
        D_0063B124 += tex_TransTexture__pn(a0);
    }
}
void reg_Init(void) {
    D_0063A168 = 0;
}
int reg_GetShinePri(int a0)
{
    switch (a0) {
        case 1: return 7;
        case 2: return 8;
        case 3: return 9;
    }
    return 7;
}
