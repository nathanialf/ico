#include "common.h"

typedef struct { float f0; float f4; float f8; } AudFrame;

typedef struct { float f0; float f4; float f8; } LoadImg;

typedef struct { long long a; long long b; } Blk16;

INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSEtaimatsu);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04eriver);
ASM_LIT4_SLOT(D_00639B18, -5500.0f);
ASM_LIT4_SLOT(D_00639B1C, 3500.0f);
ASM_LIT4_SLOT(D_00639B20, -5750.0f);
ASM_LIT4_SLOT(D_00639B24, -6500.0f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE06ariver);
ASM_LIT4_SLOT(D_00639B28, 0.05f);
ASM_LIT4_SLOT(D_00639B2C, 0.4f);
ASM_LIT4_SLOT(D_00639B30, 0.1f);
ASM_LIT4_SLOT(D_00639B34, -757.0f);
ASM_LIT4_SLOT(D_00639B38, 759.0f);
ASM_LIT4_SLOT(D_00639B3C, 0.7f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10lstrong2);
ASM_LIT4_SLOT(D_00639B40, 773.0f);
ASM_LIT4_SLOT(D_00639B44, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE19ataki);
ASM_LIT4_SLOT(D_00639B48, -1526.0f);
ASM_LIT4_SLOT(D_00639B4C, -1227.0f);
ASM_LIT4_SLOT(D_00639B50, 759.0f);
ASM_LIT4_SLOT(D_00639B54, -1194.0f);
ASM_LIT4_SLOT(D_00639B58, -1837.0f);
ASM_LIT4_SLOT(D_00639B5C, -987.0f);
ASM_LIT4_SLOT(D_00639B60, -2788.0f);
ASM_LIT4_SLOT(D_00639B64, 0.8f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE02astrong);
int stageSE02ataki(char *self) {
    float *p = *(float **)(self + 0x34);
    p[0] = 785.0f;
    p[2] = 482.0f;
    *(float *)(self + 0x1C) = 0.5f;
    if (gflagChk(0x6A)) {
        *(int *)(self + 0x18) = 0;
    }
    return 1;
}
int stageSE02atakib(char *self) {
    float *p = *(float **)(self + 0x34);
    p[0] = 785.0f;
    p[1] = 1786.0f;
    p[2] = 482.0f;
    *(float *)(self + 0x1C) = 0.5f;
    if (gflagChk(0x6A)) {
        *(int *)(self + 0x18) = 0;
    }
    return 1;
}
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
ASM_LIT4_SLOT(D_00639B74, -1300.0f);
ASM_LIT4_SLOT(D_00639B78, 750.0f);
ASM_LIT4_SLOT(D_00639B7C, 2050.0f);
extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE04bstrong(void *a0) {
    float v;
    if (D_0063C07C == frame_count) {
        v = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        v = GetRegularizedWindSpeed(GetCameraPos__pn()) * 0.5f + 0.5f;
        D_0063C078 = v;
    }
    *(float *)((char *)a0 + 0x18) = v;
    return -1;
}
int stageSE04ewind(char *a0) {
    float x = ((float *)GetCameraPos__pn())[2];
    float f;
    if (x < -5770.0f) {
        f = 0.0f;
    } else if (x > -4900.0f) {
        f = 1.0f;
    } else {
        f = (x - -5770.0f) / 870.0f;
    }
    *(float *)(a0 + 0x18) = 1.0f - f;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE04eriverDown);
ASM_LIT4_SLOT(D_00639B8C, -5770.0f);
ASM_LIT4_SLOT(D_00639B90, 2090.0f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE06astrong);
ASM_LIT4_SLOT(D_00639B94, -1753.0f);
ASM_LIT4_SLOT(D_00639B98, -1145.0f);
ASM_LIT4_SLOT(D_00639B9C, 0.3f);
ASM_LIT4_SLOT(D_00639BA0, 0.05f);
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
extern int stageSEtaimatsu(int a0);

int stageSE06ataimatsu(int *self) {
    float *p = (float *)UpdateRootPosition__p4((int)self);
    if (p[0] < 300.0f) {
        if (848.0f < p[2]) {
            return stageSEtaimatsu((int)self);
        }
    }
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08astrong);
ASM_LIT4_SLOT(D_00639BA4, 0.05f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08astrong2);
ASM_LIT4_SLOT(D_00639BA8, 0.05f);
extern Blk16 D_00623110;
extern Blk16 D_00623120;
extern int scpTriggerPosBox(int a, Blk16 *b, Blk16 *c);

int stageSE08anoise3(int self)
{
    Blk16 b1;
    Blk16 b2;
    int ret = UpdateRootPosition__p4(self);
    b1 = D_00623110;
    b2 = D_00623120;
    if (scpTriggerPosBox(ret, &b1, &b2) == 0) {
        *(float *)(self + 0x18) = 1.0f;
    } else {
        *(float *)(self + 0x18) = 0.2f;
    }
    return -1;
}
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
    return stageSEtaimatsu(a0);
}
int stageSE08bcrane(void *a0) {
    AudFrame *p = *(AudFrame **)((char *)a0 + 0x34);
    float f;
    p->f0 = 1148.0f;
    p->f4 = -4521.0f;
    p->f8 = 1514.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)UpdateRootPosition__p4());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE08brail);
ASM_LIT4_SLOT(D_00639BBC, -3679.0f);
ASM_LIT4_SLOT(D_00639BC0, 6186.0f);
int stageSE09asea(char *a0) {
    AudFrame *p = *(AudFrame **)(a0 + 0x34);
    p->f0 = 1800.0f;
    p->f4 = 585.0f;
    p->f8 = -5000.0f;
    *(float *)(a0 + 0x18) = 1.0f;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10lstrong);
ASM_LIT4_SLOT(D_00639BCC, 773.0f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE10rstrong);
ASM_LIT4_SLOT(D_00639BD0, 0.3f);
int stageSE10rstrong2(int self) {
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed((void *)GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)(self + 0x18) = f;
    return -1;
}
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
    float *p = (float *)GetCameraPos();
    if (p[1] > -1000.0f) return 0;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE13dstrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17astrong);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE18awind);
ASM_LIT4_SLOT(D_00639BDC, 1125.0f);
ASM_LIT4_SLOT(D_00639BE0, 2125.0f);
ASM_LIT4_SLOT(D_00639BE4, 0.7f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17brain);
ASM_LIT4_SLOT(D_00639BE8, -5500.0f);
ASM_LIT4_SLOT(D_00639BEC, -3800.0f);
ASM_LIT4_SLOT(D_00639BF0, 1700.0f);
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE17bstrong);
ASM_LIT4_SLOT(D_00639BF4, -5500.0f);
ASM_LIT4_SLOT(D_00639BF8, -3800.0f);
ASM_LIT4_SLOT(D_00639BFC, 1700.0f);
int stageSE17btaki(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = -5136.0f;
    b = 1518.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}
int stageSE19astrong(void *a0) {
    float *p = *(float **)((char *)a0 + 0x34);
    float f;
    p[0] = 1548.0f;
    p[2] = -3296.0f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
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
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return 1;
}
int stageSE20astrong2(void *a0) {
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}
extern int frame_count;
extern float D_0063C078;
extern int D_0063C07C;
extern void *GetCameraPos__pn(void) __asm__("GetCameraPos");
extern float GetRegularizedWindSpeed(void *a0);

int stageSE22astrong(void *a0) {
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        float e;
        D_0063C07C = frame_count;
        e = GetRegularizedWindSpeed(GetCameraPos__pn());
        e = e * 0.5f + 0.5f;
        D_0063C078 = e;
        f = e;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f * 0.5f;
    return -1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE22arain);
ASM_LIT4_SLOT(D_00639C20, -1355.0f);
ASM_LIT4_SLOT(D_00639C24, 6645.0f);
ASM_LIT4_SLOT(D_00639C28, 0.3f);
int stageSE24astrong(void *a0) {
    float f;
    if (D_0063C07C == frame_count) {
        f = D_0063C078;
    } else {
        D_0063C07C = frame_count;
        f = GetRegularizedWindSpeed(GetCameraPos__pn());
        f = f * 0.5f + 0.5f;
        D_0063C078 = f;
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
int stageSE24ariver(char *self) {
    float a, b;
    float *p = *(float **)(self + 0x34);
    a = 1478.0f;
    b = 1484.0f;
    p[0] = a;
    p[2] = b;
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/stageSEProc", stageSE47anoise);
ASM_LIT4_SLOT(D_00639C3C, -3422.0f);
ASM_LIT4_SLOT(D_00639C40, 3300.0f);
