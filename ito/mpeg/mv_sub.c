#include "common.h"





extern int sceGsPutDispEnv();
extern int SgStPcmLseek(unsigned int a0, unsigned int a1);
extern int SgStPcmPlay(unsigned long long a0);
extern int SgStPcmStop(unsigned long long a0);
extern void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2);
extern void iosMallocCheckLeak2();
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", ObjAction_Init);

extern void func_0023E170__p4(void *a0) __asm__("func_0023E170");

void copy2area(int a0) {
    func_0023E170__p4(*(void **)(a0 + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023D8A8);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", audioDecEndPut);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", sendToIOP2area);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", audioDecSendToIOP);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", pcmCallback);

void func_0023E170(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023E180);

void audioDecReset(int *self)
{
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    *(volatile int *)((char *)self + 0x50) = 0;
    *(volatile int *)((char *)self + 0) = 0;
    *(volatile int *)((char *)self + 0x2C) = 0;
    *(volatile int *)((char *)self + 0x34) = 0;
    *(volatile int *)((char *)self + 0x38) = 0;
    *(volatile int *)((char *)self + 0x40) = 0;
    *(volatile int *)((char *)self + 0x54) = 0;
    *(volatile int *)((char *)self + 0x4C) = 0;
}

int audioDecIsPreset(int *self) {
    return *(int *)((char *)self + 0x54) >= *(int *)((char *)self + 0x48);
}

void func_0023E298(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}

int audioDecPause(int a0)
{
    *(int *)a0 = 3;
    SgStPcmVolume(3, 0, 0);
    SgStPcmStop(3);
    return 0;
}

void func_0023E368(int *self)
{
    SgStPcmLseek(0, 0);
    SgStPcmLseek(1, 0);
    if (*(signed char *)((char *)self + 0x58)) {
        int half = self[0x5C / 4] / 2;
        SgStPcmVolume(3, half, half);
    } else {
        SgStPcmVolume(1, 0, self[0x5C / 4]);
        SgStPcmVolume(2, self[0x5C / 4], 0);
    }
    SgStPcmPlay(3);
    self[0] = 2;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023E400);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023E578);

extern void func_0023E578(int *self, int a1, int a2);

void setImageSize(int *self, int a1, int a2)
{
    int lim = self[0x3C / 4];
    if (a2 <= lim) {
        a2 = lim;
    }
    func_0023E578(self, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", sendDispEnv);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023E7E8);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", func_0023E890);

void dispSwitch(int *a0, int flag)
{
  int src;
  int new_var;
  new_var = flag;
  if (new_var != 0)
  {
    src = a0[0x2C / 4];
  }
  else
  {
    src = a0[0x28 / 4];
  }
  {
    int cur = a0[0x10 / 4];
    cur = cur & (~0x1FF);
    cur = cur | (src & 0x1FF);
    a0[0x10 / 4] = cur;
  }
  return sceGsPutDispEnv(a0);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_sub", vblankHandler);

