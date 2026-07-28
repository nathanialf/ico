#include "common.h"

typedef struct { float f0; float f4; float f8; } LoadImg;





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

extern float D_00631880;
extern int D_00631960;
extern float D_00633B48;
extern int D_00633B4C;
extern float DispWireLetter(void *a0);
extern void *UpdateRootPosition(void);

int setImageSize(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    p[0] = D_00631880;
    p[2] = -3296.0f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

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

extern float D_00631890;
extern float D_00631894;

int dispCreate(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    float a = D_00631890, b = D_00631894;
    p[0] = a;
    p[1] = b;
    p[2] = -398.0f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

int dispSetTags(void *a0) {
    float f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

int dispSwitch(void *a0) {
    float f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        float e;
        D_00633B4C = D_00631960;
        e = DispWireLetter(UpdateRootPosition());
        e = e * 0.5f + 0.5f;
        D_00633B48 = e;
        f = e;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f * 0.5f;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", vblankHandler);

int dispDelete(void *a0) {
    float f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

extern const float D_006318A4;
extern const float D_006318A8;

unsigned int loadImage(char *a0) {
    LoadImg *p = *(LoadImg **)(a0 + 0x34);
    p->f0 = D_006318A4;
    p->f8 = D_006318A8;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

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

extern float D_006318BC;
extern void brainStatusDel(float a0);

void setGIFtag(void) {
    brainStatusDel(*(volatile float *)&D_006318BC);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setGIFad);

extern int D_00632DB8;
extern void GetCylinderCollisionWithExceptOwnCollision(void *a0);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void brainGetLevel(void *a0, float f, int b, int c);
extern void func_00102858(void *a0);

void setTEXFLUSH(void *a0, int a1, float *a2)
{
    int buf[4];
    int v17 = 1;
    int v18;
    float f = a2[0];
    if (a2[1] < 0.5f) {
        v17 = 0;
    }
    if (a2[2] < 0.5f) {
        v18 = 0;
    } else {
        v18 = 1;
    }
    if (D_00632DB8 != 0) {
        if (v18) {
            v17 = 1;
        }
    }
    GetCylinderCollisionWithExceptOwnCollision(a0);
    func_00102858(a0);
    GetRootMatrixByDObj(buf, a0);
    brainGetLevel(a0, f, v17, v18);
}

void setTEX1_1(int a0, int a1, int a2, int a3)
{
    func_00203D90(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setTEX0_1);

extern void *func_0013ECF8(void *a0);
extern void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
extern void *isysGObjRemoveObjDL(void);

void setPRIM(void *a0, int a1) {
    void *p = isysGObjRemoveObjDL();
    while (p != 0) {
        iosOmBeforeFuncStandard(p, a1, a0);
        p = func_0013ECF8(p);
    }
}

extern int D_00621F78[];
extern char D_00621FA8[];

void setUV(void *a0, int a1)
{
    int i;
    for (i = 0; i < 0x1F; i++) {
        char *entry = D_00621FA8 + i * 8;
        if (*(int *)((char *)a0 + 8) == *(int *)entry) {
            int idx = *(int *)(entry + 4);
            if (a1 > 0) {
                if (idx < 5) {
                    continue;
                }
                idx += a1;
            }
            {
                int v18 = D_00621F78[idx];
                void *o = isysGObjRemoveObjDL();
                if (o != 0) {
                    do {
                        iosOmBeforeFuncStandard(o, v18, a0);
                        o = func_0013ECF8(o);
                    } while (o != 0);
                }
            }
        }
    }
}

