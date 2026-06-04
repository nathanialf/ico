#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispClear);

extern float D_00629B60, D_00629B64;

int setDispEnv(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float a = D_00629B60;
    float b = D_00629B64;
    p[0] = a;
    p[2] = b;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setImageSize);

extern float D_00629B6C, D_00629B70, D_00629B74;

int sendDispEnv(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float a = D_00629B6C;
    float b = D_00629B70;
    float c = D_00629B74;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispSetTags);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", vblankHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispDelete);

extern float D_00629B8C, D_00629B90;

typedef struct { float f0; float f4; float f8; } LoadImg;
typedef struct { char _0[0x1C]; float f1C; char _20[0x14]; LoadImg *f34; } Disp;

unsigned int loadImage(char *a0) {
    LoadImg *p = *(LoadImg **)(a0 + 0x34);
    p->f0 = D_00629B8C;
    p->f8 = D_00629B90;
    *(volatile float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

extern float D_00629B94, D_00629B98;

int handler_endimage(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float a = D_00629B94;
    float b = D_00629B98;
    p[0] = a;
    p[2] = b;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", startDisplay);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", endDisplay);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setDMAscTag);

extern float D_00629BA4;
extern void brainStatusDel(float a0);

void setGIFtag(void) {
    brainStatusDel(*(volatile float *)&D_00629BA4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setGIFad);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setTEXFLUSH);

extern void func_00201470(void);

void setTEX1_1(void) {
    func_00201470();
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setTEX0_1);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setPRIM);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setUV);
