#include "common.h"

typedef struct { float f0; float f4; float f8; } AudFrame;

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002388F0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecCreate);

extern int UpdateRootPosition(int x);

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

int sendToIOP2area(int *self) {
    float *p = (float *)UpdateRootPosition((int)self);
    int v0 = -1;
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            v0 = 0;
        }
    }
    do { return v0; } while (0);
}

extern int func_00237C98(int a0);

int audioDecSendToIOP(int *self) {
    float *p = (float *)UpdateRootPosition((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return func_00237C98((int)self);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecDelete);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecReset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecIsPreset);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecStart);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", audioDecPause);

extern const float D_00629B24, D_00629B28;

int audioDecResume(char *a0) {
    AudFrame *p = *(AudFrame **)(a0 + 0x34);
    p->f0 = 1800.0f;
    p->f4 = D_00629B24;
    p->f8 = D_00629B28;
    *(float *)(a0 + 0x18) = 1.0f;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00238FB0);

extern float D_00629B30;

int func_002390F0(int self) {
    float *p = (float *)UpdateRootPosition(self);
    float x = p[2];
    float r;
    if (x < -300.0f) {
        r = 0.0f;
    } else if (400.0f < x) {
        r = 1.0f;
    } else {
        r = (x - (-300.0f)) / 700.0f;
    }
    *(float *)(self + 0x18) = r * *(volatile float *)&D_00629B30;
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239188);

int func_002391E8(int *a0) {
    float *p = (float *)a0[0xD];
    p[0] = 118.0f;
    p[1] = -192.0f;
    p[2] = -46.0f;
    *(float *)((char *)a0 + 0x1C) = 0.5f;
    return 1;
}

extern const float D_00629B34, D_00629B38;


int func_00239228(void *a0) {
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    p->f0 = -133.0f;
    p->f4 = D_00629B34;
    p->f8 = D_00629B38;
    return 1;
}

int func_00239250(int *self) {
    float *p = (float *)UpdateRootPosition((int)self);
    int v0 = -1;
    if (-1000.0f < p[1]) {
        v0 = 0;
    }
    return v0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239290);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239348);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_002393A8);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_audiodec", func_00239438);
