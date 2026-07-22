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

extern float D_00629B68;
extern int D_0062BE54;
extern int D_00629C60;
extern float D_0062BE50;
extern float DispWireLetter(void *a0);

int setImageSize(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    p[0] = D_00629B68;
    p[2] = -3296.0f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        D_0062BE54 = D_00629C60;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_0062BE50 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

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

extern float D_00629B78, D_00629B7C;

int dispCreate(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    float a = D_00629B78, b = D_00629B7C;
    p[0] = a;
    p[1] = b;
    p[2] = -398.0f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        D_0062BE54 = D_00629C60;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_0062BE50 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

extern int D_0062BE54;
extern int D_00629C60;
extern float D_0062BE50;
extern float DispWireLetter(void *a0);

int dispSetTags(void *a0) {
    float f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        D_0062BE54 = D_00629C60;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_0062BE50 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

int dispSwitch(void *a0) {
    float f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        float e;
        D_0062BE54 = D_00629C60;
        e = DispWireLetter(UpdateRootPosition());
        e = e * 0.5f + 0.5f;
        D_0062BE50 = e;
        f = e;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f * 0.5f;
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_disp", vblankHandler);

int dispDelete(void *a0) {
    float f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        D_0062BE54 = D_00629C60;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_0062BE50 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

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

extern void GetCylinderCollisionWithExceptOwnCollision(void *a0);
extern void func_00102828(void *a0);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void brainGetLevel(void *a0, float f, int b, int c);
extern int D_0062B080;

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
    if (D_0062B080 != 0) {
        if (v18) {
            v17 = 1;
        }
    }
    GetCylinderCollisionWithExceptOwnCollision(a0);
    func_00102828(a0);
    GetRootMatrixByDObj(buf, a0);
    brainGetLevel(a0, f, v17, v18);
}

extern void func_00201470(void);

void setTEX1_1(void) {
    func_00201470();
}

struct RecA_tex { char pad[0x34]; int x34; char pad2[0x4C - 0x38]; };
struct RecB_tex { int x0; char pad[0x8]; int xC; int x10; };
extern struct RecA_tex D_002A0A90[];
extern struct RecB_tex D_0029B128[];

void setTEX0_1(int a0) {
    int e;
    struct RecB_tex *p;
    if (a0 < 0) return;
    e = D_002A0A90[a0].x34;
    if (e != 0) {
        p = &D_0029B128[e];
    } else {
        p = 0;
    }
    if (p == 0) return;
    if ((p->x10 & 1) == 1u) {
        p->xC = 0x32E;
    }
    if (p->xC == 0x32E) {
        p->xC = p->x0;
    }
}

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

extern char D_0061C270[];
extern int D_0061C240[];

void setUV(void *a0, int a1)
{
    int i;
    for (i = 0; i < 0x1F; i++) {
        char *entry = D_0061C270 + i * 8;
        if (*(int *)((char *)a0 + 8) == *(int *)entry) {
            int idx = *(int *)(entry + 4);
            if (a1 > 0) {
                if (idx < 5) {
                    continue;
                }
                idx += a1;
            }
            {
                int v18 = D_0061C240[idx];
                void *o = isysGObjRemoveObjDL();
                if (o != 0) {
                    do {
                        iosOmBeforeFuncStandard(o, v18, a0);
                        o = func_0013E7E0(o);
                    } while (o != 0);
                }
            }
        }
    }
}
