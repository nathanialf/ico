#include "common.h"

typedef struct { long long a; long long b; } Blk16;

INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04eriver);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE06ariver);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10lstrong2);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE19ataki);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE02astrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE02ataki);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE02atakib);
extern int GetCameraGroupCurrent(void);

int stageSE03tsuiro(void) {
    int r = GetCameraGroupCurrent();
    if (r == 3 || r == 9) {
        return -1;
    }
    return 0;
}
int stageSE03tnotSuiro(void) {
    int r = GetCameraGroupCurrent();
    int busy = (r == 3 || r == 9) ? -1 : 0;
    if (busy != 0) {
        return 0;
    }
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04agate);
extern int D_00639CE0;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE04bstrong(void *a0) {
    float v;
    if (D_0063C07C == D_00639CE0) {
        v = D_0063C078;
    } else {
        D_0063C07C = D_00639CE0;
        v = GetRegularizedWindSpeed(GetCameraPos__pn()) * 0.5f + 0.5f;
        D_0063C078 = v;
    }
    *(float *)((char *)a0 + 0x18) = v;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04ewind);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04eriverDown);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE06astrong);
extern int * GetCameraPos();

int stageSE06abirdIn(int *self)
{
  float *p = (float *) GetCameraPos((int) self);
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
  float *p = (float *) GetCameraPos((int) self);
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
extern int UpdateRootPosition__p4() __asm__("GetCameraPos");
extern int func_00255520(int a0);

int stageSE06ataimatsu(int *self) {
    float *p = (float *)UpdateRootPosition__p4((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return func_00255520((int)self);
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08astrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08astrong2);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08anoise3);
extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08ataimatsu(int a0)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(a0);
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        return 0;
    }
    return func_00255520(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08bcrane);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08brail);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE09asea);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10lstrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10rstrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10rstrong2);
int stageSE13arain(char *a0)
{
    float *v1 = *(float **)(a0 + 0x34);
    v1[0] = 118.0f;
    v1[1] = -192.0f;
    v1[2] = -46.0f;
    *(float *)(a0 + 0x1C) = 0.5f;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE13cNoise);
int stageSE13dterrace(void) {
    float *p = (float *)GetCameraPos();
    if (p[1] > -1000.0f) return 0;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE13dstrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17astrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE18awind);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17brain);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17bstrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17btaki);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE19astrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE19arain);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE20astrong);
int stageSE20astrong2(void *a0) {
    float f;
    if (D_0063C07C == D_00639CE0) {
        f = D_0063C078;
    } else {
        D_0063C07C = D_00639CE0;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}
extern int D_00639CE0;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE22astrong(void *a0) {
    float f;
    if (D_0063C07C == D_00639CE0) {
        f = D_0063C078;
    } else {
        float e;
        D_0063C07C = D_00639CE0;
        e = GetRegularizedWindSpeed(GetCameraPos__pn());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        f = e;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f * 0.5f;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE22arain);
int stageSE24astrong(void *a0) {
    float f;
    if (D_0063C07C == D_00639CE0) {
        f = D_0063C078;
    } else {
        D_0063C07C = D_00639CE0;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE24arain);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE24ariver);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE47anoise);
