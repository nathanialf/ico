#include "common.h"


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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecSendToIOP);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", pcmCallback);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecDelete);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecReset);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecIsPreset);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecStart);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecPause);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", audioDecResume);

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

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CCB8);

int func_0023CCE0(void) {
    float *p = (float *)UpdateRootPosition();
    if (p[1] > -1000.0f) return 0;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CD20);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CDD8);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CE38);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_audiodec", func_0023CEC8);

