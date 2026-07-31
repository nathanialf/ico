#include "common.h"

typedef struct { float f0; float f4; float f8; } AudFrame;

typedef struct { long long a; long long b; } Blk16;


extern int * UpdateRootPosition();
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023C380);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecCreate);

int audioDecEndPut(int *self)
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

int sendToIOP2area(int *self)
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

int audioDecSendToIOP(int *self) {
    float *p = (float *)UpdateRootPosition__p4((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return func_0023B728((int)self);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecDelete);

extern Blk16 D_0061C3B0;
extern Blk16 D_0061C3C0;
extern float D_00631824;
extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");
extern int preload(int a, Blk16 *b, Blk16 *c);

int audioDecReset(int self)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(self);
    b1 = D_0061C3B0;
    b2 = D_0061C3C0;
    if (preload(ret, &b1, &b2) == 0) {
        *(float *)(self + 0x18) = 1.0f;
    } else {
        *(float *)(self + 0x18) = *(volatile float *)&D_00631824;
    }
    return -1;
}

extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");

int audioDecIsPreset(int a0)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(a0);
    b1 = D_0061C3B0;
    b2 = D_0061C3C0;
    if (preload(ret, &b1, &b2) == 0) {
        return 0;
    }
    return func_0023B728(a0);
}

extern float D_00631828;
extern float D_0063182C;
extern float D_00631830;
extern int D_00631960;
extern float D_00633B48;
extern int D_00633B4C;
extern float DispWireLetter(void *a0);
extern int UpdateRootPosition__p4() __asm__("UpdateRootPosition");

int audioDecStart(void *a0) {
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    float f;
    p->f0 = D_00631828;
    p->f4 = D_0063182C;
    p->f8 = D_00631830;
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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecPause);

extern const float D_0063183C;
extern const float D_00631840;

int audioDecResume(char *a0) {
    AudFrame *p = *(AudFrame **)(a0 + 0x34);
    p->f0 = 1800.0f;
    p->f4 = D_0063183C;
    p->f8 = D_00631840;
    *(float *)(a0 + 0x18) = 1.0f;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CA40);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CB80);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CC18);

int func_0023CC78(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    v1[0] = 118.0f;
    v1[1] = -192.0f;
    v1[2] = -46.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}

extern const float D_0063184C;
extern const float D_00631850;

int func_0023CCB8(int a0)
{
    float *v1 = *(float **)(a0 + 0x34);

    v1[0] = -133.0f;
    v1[1] = D_0063184C;
    v1[2] = D_00631850;
    return 1;
}

int func_0023CCE0(void) {
    float *p = (float *)UpdateRootPosition();
    if (p[1] > -1000.0f) return 0;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CD20);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CDD8);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CE38);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CEC8);

