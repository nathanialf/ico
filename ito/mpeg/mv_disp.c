#include "common.h"

typedef struct { float f0; float f4; float f8; } LoadImg;





extern void func_00203D90();
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", stageSE17bstrong);
ASM_LIT4_SLOT(D_0063186C, -5500.0f);
ASM_LIT4_SLOT(D_00631870, -3800.0f);
ASM_LIT4_SLOT(D_00631874, 1700.0f);

int setDispEnv(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = -5136.0f;
    b = 1518.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}

extern int D_00631960;
extern float D_00633B48;
extern int D_00633B4C;
extern float DispWireLetter(void *a0);
extern void *UpdateRootPosition(void);

int stageSE19astrong(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    p[0] = 1548.0f;
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

int stageSE19arain(int *self)
{
    float *p = (float *)self[0xD];
    register float a = 3190.0f;
    register float b = 3163.0f;
    register float c = -1332.0f;
    p[0] = a;
    p[1] = b;
    p[2] = c;
    return 1;
}


int stageSE20astrong(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    float a = -746.0f, b = -685.0f;
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

int stageSE22astrong(void *a0) {
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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", stageSE22arain);
ASM_LIT4_SLOT(D_00631898, -1355.0f);
ASM_LIT4_SLOT(D_0063189C, 6645.0f);
ASM_LIT4_SLOT(D_006318A0, 0.3f);

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


unsigned int stageSE24arain(char *a0) {
    LoadImg *p = *(LoadImg **)(a0 + 0x34);
    p->f0 = 1771.0f;
    p->f8 = -4949.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

int handler_endimage(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = 1478.0f;
    b = 1484.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", stageSE47anoise);
ASM_LIT4_SLOT(D_006318B4, -3422.0f);
ASM_LIT4_SLOT(D_006318B8, 3300.0f);

extern int GetDataFileName2(void *p);
typedef struct { char pad[0x194]; } DispBuf;
extern DispBuf D_005F3038[];
extern char D_00633B60[];

int GetDataFileName(int a0) {
    int buf[0x40];
    void *p;
    if (a0 == -1) {
        p = D_00633B60;
    } else {
        p = (void *)&D_005F3038[a0];
    }
    return GetDataFileName2(p);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", GetDataFileName2);

extern void brainStatusDel(float a0);

void setGIFtag(void) {
    brainStatusDel(0.1f);
}

extern int memset(void *a0, int a1, int a2);
extern int MoveNextStage_Clear(int a0, int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
extern char D_0028A890[];
extern int func_00182000(void *a0, int a1, int a2);

int setGIFad(void) {
    char buf[0x40];
    int r;
    memset(buf, 0, 0x40);
    *(float *)(buf + 0x20) = 1.0f;
    *(float *)(buf + 0x24) = 1.0f;
    *(float *)(buf + 0x28) = 1.0f;
    r = MoveNextStage_Clear(0x3C, 0x45, -1, 0, buf, 1, 7, 0);
    func_00182000(D_0028A890, r, 1);
    return r;
}

extern int D_00632DB8;
extern void SetDirectRootPosition(void *a0);
extern void GetRootPosition(void *a0, void *a1);
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
    SetDirectRootPosition(a0);
    func_00102858(a0);
    GetRootPosition(buf, a0);
    brainGetLevel(a0, f, v17, v18);
}

void setTEX1_1(int a0, int a1, int a2, int a3)
{
    func_00203D90(a0, a1, a2, a3);
}

struct RecA_tex { char pad[0x34]; int x34; char pad2[0x4C - 0x38]; };
struct RecB_tex { int x0; char pad[0x8]; int xC; int x10; };
extern struct RecA_tex D_002A4C48[];
extern struct RecB_tex D_0029F270[];

void setTEX0_1(int a0) {
    int e;
    struct RecB_tex *p;
    if (a0 < 0) return;
    e = D_002A4C48[a0].x34;
    if (e != 0) {
        p = &D_0029F270[e];
    } else {
        p = 0;
    }
    if (p == 0) return;
    if ((p->x10 & 1) == 1u) {
        p->xC = 0x32F;
    }
    if (p->xC == 0x32F) {
        p->xC = p->x0;
    }
}

extern void *isysGObjGetExist_next(void *a0);
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern void *isysGObjGetExist_begin(void);

void ObjAction_Mail(void *a0, int a1) {
    void *p = isysGObjGetExist_begin();
    while (p != 0) {
        iosOmSendMail(p, a1, a0);
        p = isysGObjGetExist_next(p);
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
                void *o = isysGObjGetExist_begin();
                if (o != 0) {
                    do {
                        iosOmSendMail(o, v18, a0);
                        o = isysGObjGetExist_next(o);
                    } while (o != 0);
                }
            }
        }
    }
}

