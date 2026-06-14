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

extern const float D_00629B8C, D_00629B90;

typedef struct { float f0; float f4; float f8; } LoadImg;

unsigned int loadImage(char *a0) {
    LoadImg *p = *(LoadImg **)(a0 + 0x34);
    p->f0 = D_00629B8C;
    p->f8 = D_00629B90;
    *(float *)(a0 + 0x1C) = 0.5f;
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

extern float D_00629B9C;
extern float D_00629BA0;

int startDisplay(int self) {
    float *p = (float *)UpdateRootPosition(self);
    float x = p[1];
    float r;
    if (x < D_00629B9C) {
        r = 0.0f;
    } else if (-122.0f < x) {
        r = 1.0f;
    } else {
        r = (x - D_00629B9C) / D_00629BA0;
    }
    *(float *)(self + 0x18) = 1.0f - r;
    return -1;
}

extern int setDMAscTag(void *p);
typedef struct { char pad[0x190]; } DispBuf;
extern DispBuf D_005EBCC8[];
extern char D_0062DCE8[];

int endDisplay(int a0) {
    int buf[0x40];
    void *p;
    if (a0 == -1) {
        p = D_0062DCE8;
    } else {
        p = (void *)&D_005EBCC8[a0];
    }
    return setDMAscTag(p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setDMAscTag);

extern float D_00629BA4;
extern void brainStatusDel(float a0);

void setGIFtag(void) {
    brainStatusDel(*(volatile float *)&D_00629BA4);
}

extern int func_00260568(void *a0, int a1, int a2);
extern int MoveNextStage_Clear(int a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
extern char D_00286A90[];
extern int func_0017F518(void *a0, int a1, int a2);

int setGIFad(void) {
    char buf[0x40];
    int r;
    func_00260568(buf, 0, 0x40);
    *(float *)(buf + 0x20) = 1.0f;
    *(float *)(buf + 0x24) = 1.0f;
    *(float *)(buf + 0x28) = 1.0f;
    r = MoveNextStage_Clear(0x3B, 0x44, -1, 0, buf, 1, 7, 0);
    func_0017F518(D_00286A90, r, 1);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setTEXFLUSH);

extern void func_00201470(void);

void setTEX1_1(void) {
    func_00201470();
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setTEX0_1);

extern void *isysGObjRemoveObjDL(void);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void *func_0013E7E0(void *a0);

void setPRIM(void *a0, int a1) {
    void *p = isysGObjRemoveObjDL();
    while (p != 0) {
        iosOmBeforeFuncStandard(p, a1, a0);
        p = func_0013E7E0(p);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", setUV);
