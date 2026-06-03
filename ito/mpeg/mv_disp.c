#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispClear);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setDispEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setImageSize);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", sendDispEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispCreate);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispSetTags);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", vblankHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", dispDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", loadImage);

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
