#include "common.h"





extern void func_00203D90();
extern float D_006318AC;
extern float D_006318B0;
extern float D_00631884;
extern float D_00631888;
extern float D_0063188C;
extern float D_00631878;
extern float D_0063187C;
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispClear);

int setDispEnv(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = D_00631878;
    b = D_0063187C;
    p[0] = a;
    p[2] = b;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setImageSize);

int sendDispEnv(int *self)
{
    float *p = (float *)self[0xD];
    register float a = D_00631884;
    register float b = D_00631888;
    register float c = D_0063188C;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispCreate);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispSetTags);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispSwitch);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", vblankHandler);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispDelete);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", loadImage);

int handler_endimage(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = D_006318AC;
    b = D_006318B0;
    p[0] = a;
    p[2] = b;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", startDisplay);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", endDisplay);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setDMAscTag);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setGIFtag);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setGIFad);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setTEXFLUSH);

void setTEX1_1(int a0, int a1, int a2, int a3)
{
    func_00203D90(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setTEX0_1);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setPRIM);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setUV);

