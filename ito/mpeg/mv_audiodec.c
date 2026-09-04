#include "common.h"

typedef struct { float f0; float f4; float f8; } AudFrame;

typedef struct { long long a; long long b; } Blk16;


extern int * UpdateRootPosition();
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023C380);
ASM_LIT4_SLOT(D_00631804, -5770.0f);
ASM_LIT4_SLOT(D_00631808, 2090.0f);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE06astrong);
ASM_LIT4_SLOT(D_0063180C, -1753.0f);
ASM_LIT4_SLOT(D_00631810, -1145.0f);
ASM_LIT4_SLOT(D_00631814, 0.3f);
ASM_LIT4_SLOT(D_00631818, 0.05f);

int stageSE06abirdIn(int *self)
{
  float *p = (float *) UpdateRootPosition((int) self);
  int v0 = 0;
  if (p[0] < 300.0f)
  {
    if (848.0f < p[2])
    {
      v0 = -1;
    }
  }
 do { return v0; } while (0);
}

int stageSE06abirdOut(int *self)
{
  int new_var;
  float *p = (float *) UpdateRootPosition((int) self);
  int v0 = -1;
  if (p[0] < 300.0f)
  {
    new_var = 2;
    if (848.0f < p[new_var])
    {
      v0 = 0;
    }
  }
 do { return v0; } while (0);
}

extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");
extern int func_0023B728(int a0);

int stageSE06ataimatsu(int *self) {
    float *p = (float *)UpdateRootPosition__p4((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return func_0023B728((int)self);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE08astrong);
ASM_LIT4_SLOT(D_0063181C, 0.05f);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE08astrong2);
ASM_LIT4_SLOT(D_00631820, 0.05f);

extern Blk16 D_0061C3B0;
extern Blk16 D_0061C3C0;
extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08anoise3(int self)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(self);
    b1 = D_0061C3B0;
    b2 = D_0061C3C0;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        *(float *)(self + 0x18) = 1.0f;
    } else {
        *(float *)(self + 0x18) = 0.2f;
    }
    return -1;
}

extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");

int stageSE08ataimatsu(int a0)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(a0);
    b1 = D_0061C3B0;
    b2 = D_0061C3C0;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        return 0;
    }
    return func_0023B728(a0);
}

extern int D_00631960;
extern float D_00633B48;
extern int D_00633B4C;
extern float DispWireLetter(void *a0);
extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");

int stageSE08bcrane(void *a0) {
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    float f;
    p->f0 = 1148.0f;
    p->f4 = -4521.0f;
    p->f8 = 1514.0f;
    if (D_00633B4C == D_00631960) {
        f = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        f = DispWireLetter((void *)UpdateRootPosition__p4());
        f = f * 0.5f + 0.5f;
        D_00633B48 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE08brail);
ASM_LIT4_SLOT(D_00631834, -3679.0f);
ASM_LIT4_SLOT(D_00631838, 6186.0f);


int stageSE09asea(char *a0) {
    AudFrame *p = *(AudFrame **)(a0 + 0x34);
    p->f0 = 1800.0f;
    p->f4 = 585.0f;
    p->f8 = -5000.0f;
    *(float *)(a0 + 0x18) = 1.0f;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE10lstrong);
ASM_LIT4_SLOT(D_00631844, 773.0f);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE10rstrong);
ASM_LIT4_SLOT(D_00631848, 0.3f);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CC18);

int stageSE13arain(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    v1[0] = 118.0f;
    v1[1] = -192.0f;
    v1[2] = -46.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}


int stageSE13cNoise(int a0)
{
    float *v1 = *(float **)(a0 + 0x34);

    v1[0] = -133.0f;
    v1[1] = -5698.0f;
    v1[2] = -966.0f;
    return 1;
}

int stageSE13dterrace(void) {
    float *p = (float *)UpdateRootPosition();
    if (p[1] > -1000.0f) return 0;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE13dstrong);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE17astrong);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE18awind);
ASM_LIT4_SLOT(D_00631854, 1125.0f);
ASM_LIT4_SLOT(D_00631858, 2125.0f);
ASM_LIT4_SLOT(D_0063185C, 0.7f);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", stageSE17brain);
ASM_LIT4_SLOT(D_00631860, -5500.0f);
ASM_LIT4_SLOT(D_00631864, -3800.0f);
ASM_LIT4_SLOT(D_00631868, 1700.0f);

