#include "common.h"

#include "mv_defs.h"

#include "r5900.h"

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispClear);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setDispEnv);
extern void setDispEnv(int *self, int a1, int a2);

void setImageSize(int *self, int a1, int a2)
{
    int lim = self[0x3C / 4];
    if (a2 <= lim) {
        a2 = lim;
    }
    setDispEnv(self, a1, a2);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", sendDispEnv);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispCreate);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", dispSetTags);
extern int sceGsPutDispEnv();

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
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", vblankHandler);
void dispDelete(void) {}
void loadImage(int a0) {
    *(volatile unsigned int *)0x1000A030 = phys_addr(a0);
    *(volatile unsigned int *)0x1000A020 = 0;
    *(volatile unsigned int *)0x1000A000 = 0x105;
}
extern char voBuf[];
extern int D_0063C0BC;
extern void voBufDecCount(int *p);

int handler_endimage(void)
{
    if (D_0063C0BC != 0) {
        voBufDecCount(voBuf);
        D_0063C0BC = 0;
    }
    SYNC();
    EI();
    return 0;
}
extern int D_0063C0B4;
extern int D_0063C0B8;
extern int D_0063C5C4;
extern int sceGsSyncV(int a0);

void startDisplay(int a0) {
    while (sceGsSyncV(0) == a0);
    *(volatile int *)&D_0063C0B8 = 1;
    D_0063C5C4 = 0;
    *(volatile int *)&D_0063C0B4 = 0;
}
void endDisplay(void) {
    D_0063C0B8 = 0;
    D_0063C5C4 = 0;
}
void *setDMAscTag(void *a0, int a1, unsigned int a2, int a3, int p4, int p5, int p6) {
    unsigned long long g1 = ((unsigned long long)a1 << 63) | (unsigned int)p6;
    unsigned long long g2 = ((unsigned long long)(unsigned int)p4 << 28)
        | ((unsigned long long)(unsigned int)a3 << 31);
    unsigned long long g3 = ((unsigned long long)(a2 & 0xFFFFFFF0) << 32)
        | ((unsigned long long)(unsigned int)p5 << 26);
    *(long long *)a0 = g1 | g2 | g3;
    return (char *)a0 + 0x10;
}
void *setGIFtag(int *a0, long long a1, int a2, int a3, int p4, int p5, int p6, int p7) {
    int hi = (p5 << 14) | (a2 << 28);
    int lo = (a3 << 26) | (p4 << 15);
    a0[0] = (p6 << 15) | p7;
    a0[1] = hi | lo;
    a0[2] = (int)(a1 & 0xFFFFFFFFLL);
    a0[3] = (int)(a1 >> 32);
    return (char *)a0 + 0x10;
}
void *setGIFad(int *a0, int a1, long long a2) {
    a0[0] = (int)(a2 & 0xFFFFFFFFLL);
    a0[1] = (int)(a2 >> 32);
    a0[2] = a1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
char *setTEXFLUSH(char *p) {
    *(int *)(p + 0) = 0;
    *(int *)(p + 8) = 0x3F;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0xC) = 0;
    return p + 0x10;
}
void *setTEX1_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 2)
        | ((unsigned long long)(unsigned int)a3 << 5)
        | ((unsigned long long)(unsigned int)p4 << 6)
        | ((unsigned long long)(unsigned int)p5 << 9)
        | ((unsigned long long)(unsigned int)p6 << 19)
        | ((long long)p7 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x14;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
void *setTEX0_1(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7,
                 unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 14)
        | ((unsigned long long)(unsigned int)a3 << 20)
        | ((unsigned long long)(unsigned int)p4 << 26)
        | ((unsigned long long)(unsigned int)p5 << 30)
        | ((long long)p6 << 34)
        | ((long long)p7 << 35)
        | ((unsigned long long)p8 << 37)
        | ((unsigned long long)p9 << 51)
        | ((unsigned long long)p10 << 55)
        | ((unsigned long long)p11 << 56)
        | ((unsigned long long)p12 << 61);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 6;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
void *setPRIM(int *a0, int a1, int a2, int a3, int p4, int p5, int p6, int p7, unsigned int p8, unsigned int p9) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 3)
        | ((unsigned long long)(unsigned int)a3 << 4)
        | ((unsigned long long)(unsigned int)p4 << 5)
        | ((unsigned long long)(unsigned int)p5 << 6)
        | ((unsigned long long)(unsigned int)p6 << 7)
        | ((unsigned long long)(unsigned int)p7 << 8)
        | ((unsigned long long)p8 << 9)
        | ((unsigned long long)p9 << 10);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
void *setUV(int *a0, int a1, int a2) {
    long long t = (unsigned int)a1 | ((unsigned long long)(unsigned int)a2 << 16);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 3;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
void *setRGBAQ(int *a0, int a1, int a2, int a3, int p4, int p5) {
    long long t = (unsigned int)a1
        | ((unsigned long long)(unsigned int)a2 << 8)
        | ((unsigned long long)(unsigned int)a3 << 16)
        | ((unsigned long long)(unsigned int)p4 << 24)
        | ((long long)p5 << 32);
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 1;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setXYZ2);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setFRAME_1);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setTEST_1);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setSCISSOR_1);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setXYOFFSET_1);
void *setPRMODECONT(int *a0, int a1) {
    long long t = (unsigned int)a1;
    a0[0] = (int)(t & 0xFFFFFFFFLL);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x1A;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setPRMODE);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setCLAMP_1);
int *setBITBLTBUF(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a3 << 56) | (a2 << 48) | (a1 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x50;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}
int *setTRXPOS(int *a0, long long a1, long long a2, long long a3)
{
    long long t = (a1 << (27 + 32)) | (a3 << 48) | (a2 << 32);
    a0[1] = (int)(t >> 32);
    a0[2] = 0x51;
    a0[0] = 0;
    a0[3] = 0;
    return a0 + 4;
}
void *setTRXREG(int *a0, int a1, int a2) {
    unsigned long long v = (unsigned int)a1;
    unsigned long long packed = ((unsigned long long)a2 << 32) | v;
    a0[0] = (int)v;
    a0[1] = (int)(packed >> 32);
    a0[2] = 0x52;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_disp", setTRXDIR);
