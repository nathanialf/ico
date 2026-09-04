#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern void setD3_CHCR(int *a0);
extern void setD4_CHCR(int *a0);

void sceIpuStopDMA(void *a0) {
    setD4_CHCR((int *)1);
    ((int *)a0)[0] = *(volatile int *)0x1000B410;
    ((int *)a0)[1] = *(volatile int *)0x1000B430;
    ((int *)a0)[2] = *(volatile int *)0x1000B420;
    ((int *)a0)[3] = *(volatile int *)0x1000B400;
    while (*(volatile int *)0x10002010 & 0xF0) {
    }
    setD3_CHCR((int *)0);
    ((int *)a0)[4] = *(volatile int *)0x1000B010;
    ((int *)a0)[5] = *(volatile int *)0x1000B020;
    ((int *)a0)[6] = *(volatile int *)0x1000B000;
    ((int *)a0)[7] = *(volatile int *)0x10002020;
    ((int *)a0)[8] = *(volatile int *)0x10002010;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceIpuRestartDMA);
int sceIpuSync(int a0) {
    int r = 0;
    switch (a0) {
    case 0:
        while (*(volatile int *)0x10002010 < 0) {
        }
        r = 0;
        break;
    case 1:
        r = (unsigned)*(volatile int *)0x10002010 >> 31;
        break;
    }
    return r;
}
extern void DIntr(int *self);
extern void EIntr(void);

void func_002725D8(int *a0) {
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceIpuInit);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", GetRomName);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", IsT10K);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetLanguage);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfSetT10kConfig);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetAspect);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetSpdif);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetTimeZone);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetDateNotation);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetSummerTime);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetTimeNotation);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", tobcd);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", frombcd);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", convertfrombcd);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", converttobcd);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", adddate);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", subdate);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", addhour);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", subhour);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", AdjustTime);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetGMTfromRTC);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", sceScfGetLocalTimefromRTC);
extern unsigned char D_00731C00[];

void *_SgGetSlotContext(int a0) {
    return &D_00731C00[a0 * 0x58];
}
extern unsigned char D_00732C80[];

void *_SgGetSeqContext(int a0) {
    return &D_00732C80[a0 * 0x54];
}
extern int D_00733C40[];

void *_SgGetComContext(void) {
    return D_00733C40;
}
extern unsigned char D_00731600[];

void *_SgGetVabContext(int a0) {
    return &D_00731600[a0 * 0xC];
}
extern int D_00735F00[];

void _SgSetSeVolValue(int a0, int a1) {
    D_00735F00[a0] = a1;
}
int _SgGetSeVolValue(int a0) {
    return D_00735F00[a0];
}
void *_SgSetSeContext(void) {
    return D_00735F00;
}
extern int D_00736100[];

void *_SgGetHeadContext(void) {
    return D_00736100;
}
extern int D_00735EC0[];

int _SgGetIop2EeContext(void) {
    return D_00735EC0[0];
}
extern unsigned char D_00733CC0[];

void *_SgGetPacketCntext(int a0, int a1) {
    unsigned char *p = &D_00733CC0[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgCalledTickProc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSetPkAdd);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSeMain);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgBgmMain);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSetRealtimeTickProc);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSetRealtimeVolume);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgTableEnvAdd);
extern void *_SgGetComContext(void);

int _SgSeqKeyOnSlot(void) {
    int *mgr = _SgGetComContext();
    int best_idx = -1;
    int best_val = -1;
    int i;
    int idx;
    unsigned char *obj;
    int divisor;
    int one;

    i = 0;
    do {
        idx = (unsigned int)mgr[0xC] % 0x30;
        obj = _SgGetSlotContext(idx);
        if ((*(int *)obj & 0x100) == 0 && obj[0x51] == 0) {
            return idx;
        }
        mgr[0xC]++;
    } while (++i < 0x30);
    divisor = 0x30;
    one = 1;
    i = 0x2F;
    do {
        idx = (unsigned int)mgr[0xC] % divisor;
        obj = _SgGetSlotContext(idx);
        if ((*(int *)obj & 0x100) == 0 && obj[0x51] == one) {
            int v = *(int *)(obj + 4);
            if ((unsigned int)v < (unsigned int)best_val) {
                best_idx = idx;
                best_val = v;
            }
        }
        mgr[0xC]++;
    } while (--i >= 0);
    return best_idx;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSeKeyOnSlot);
extern void *_SgGetHeadContext(void);

int _SgSeKeyOff(char *a0) {
    long long mask16 = 0;
    long long mask19 = 0;
    char *p18 = (char *)_SgGetComContext();
    char *p20 = (char *)_SgGetHeadContext();
    char *elem = (char *)_SgGetSlotContext(0);
    int i;
    for (i = 0; i < 0x30; i++, elem += 0x58) {
        char *q;
        if (*(unsigned char *)(elem + 0x51) != 2) {
            continue;
        }
        if (!(*(int *)elem & 4)) {
            continue;
        }
        q = *(char **)(p20 + 0x10);
        if (*(unsigned short *)(elem + 0x2C) != *(unsigned char *)(q + 3)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x4E) != *(unsigned char *)(q + 1)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x54) != *(unsigned short *)(a0 + 0x18)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x50) == *(unsigned short *)(a0 + 0x4C)) {
            mask16 |= (1LL << i);
        } else {
            mask19 |= (1LL << i);
        }
    }
    if (mask16 == 0) {
        mask16 = mask19;
    }
    for (i = 0; i < 0x30; i++) {
        if ((mask16 >> i) & 1) {
            *(long long *)(p18 + 0x28) |= (1LL << i);
        }
    }
    *(int *)(a0 + 4) += 4;
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSeqKeyOff);
int _SgIntoKeyOn(int a0, int a1, int a2) {
    int *r = (int *)_SgGetHeadContext();
    if (a0 == 0xFF) {
        a0 = 1;
    } else {
        int off = a1 << 4;
        int base = r[1] + off;
        unsigned char *b = (unsigned char *)base;
        r[1] = base;
        if (a2 < b[0]) {
            a0 = 0;
        } else {
            int c = b[1];
            a0 = (c >= a2);
        }
        r[1] = base - off;
    }
    return a0;
}
extern void _SgSetPkAdd(int a0, int a1, int a2, int a3);

int _SgPitchTableVag(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    _SgSetPkAdd(4, a0, (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | a4,
                  (a5 << 24) | a6);
    return 0;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSeqSeVolume);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgPan);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgEndSeq);
void _SgTempoChange(int *a0) {
    unsigned char *p = (unsigned char *)(a0[2] + a0[1]);
    void *q = _SgGetComContext();
    *(unsigned short *)((char *)a0 + 0x1E) = p[2] | (p[3] << 8);
    *(int *)((char *)a0 + 0x10) =
        ((((int)*(unsigned short *)((char *)a0 + 0x20)
           * *(unsigned short *)((char *)a0 + 0x1E)) << 12)
         / *(unsigned short *)((char *)q + 0x3A)) / 0x3C;
    a0[1] += 4;
}
void _SgProgChange(int *a0)
{
  int *p;
  unsigned short idx;
  char *base;
  char *v2;
  if ((*(a0 + 0)) & 2)
  {
    p = (int *) _SgGetHeadContext();
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    v2 = (char *) (*((int *) (((char *) p) + 0x10)));
    ;
    *((((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4)) + 0x12) = *((unsigned char *) (v2 + 1));
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    base = ((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4);
    *(base + 0x1A) = 0x40;
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    base = ((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4);
    *(base + 0x1B) = 0x40;
  }
  *(a0 + 1) += 2;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContMod);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContModLoop);
void _SgContPolta(char *a0)
{
    char *p;
    char *mgr;
    char *ctx;
    char *s;
    int i;
    int n;
    int v;
    int two;

    p = (char *)_SgGetSlotContext(0);
    mgr = (char *)_SgGetComContext();
    ctx = (char *)_SgGetHeadContext();
    two = 2;
    n = 0xF;
    i = 0x2F;
    do {
        if (*(unsigned char *)(p + 0x51) == two &&
            *(unsigned char *)(p + 0x54) == *(unsigned short *)(a0 + 0x18)) {
            s = *(char **)(ctx + 0x10);
            if (*(unsigned short *)(p + 0x2C) == *(unsigned char *)(s + 0x4) &&
                *(unsigned char *)(p + 0x4E) == *(unsigned char *)(s + 0x5) &&
                *(unsigned char *)(p + 0x50) == *(unsigned short *)(a0 + 0x4C)) {
                *(int *)p |= 0x20;
                v = (*(unsigned short *)(mgr + 0x3A) * *(unsigned char *)(s + 0x2)) / n;
                *(short *)(p + 0x4C) = (short)v;
                if (*(unsigned char *)(s + 0x3) & 0x80) {
                    *(float *)(p + 0x44) = (float)*(signed char *)(s + 0x3) / (float)(short)v;
                } else {
                    *(float *)(p + 0x44) = (float)*(unsigned char *)(s + 0x3) / (float)(short)v;
                }
            }
        }
        i -= 1;
        p += 0x58;
    } while (i >= 0);
    *(int *)(a0 + 0x4) += 6;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContVol);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContPan);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContDump);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContSeLoop);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContParam);
void _SgContLoopCount(void *a0) {
    void *s0 = a0;
    void *p = _SgGetHeadContext();
    int t = *(unsigned short *)((char *)s0 + 0x28);
    int val;
    int pval;
    if (t == 1) goto case1;
    if (t >= 2) goto ge2;
    if (t == 0) goto case0;
    goto done;
ge2:
    if (t == 2) goto case12;
    goto done;
case0: {
    int q0 = *(int *)((char *)p + 0x10);
    int b0 = *(unsigned char *)((char *)q0 + 0x2);
    *(short *)((char *)s0 + 0x2A) = 0;
    *(short *)((char *)s0 + 0x26) = b0;
    goto done;
}
case1:
case12: {
    int q12 = *(int *)((char *)p + 0x10);
    int b12 = *(unsigned char *)((char *)q12 + 0x2);
    *(short *)((char *)s0 + 0x2A) = b12;
}
done:
    val = *(int *)((char *)s0 + 0x4);
    *(int *)((char *)s0 + 0x4) = val + 3;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgContLoop);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgBendForm);
void _SgDeltaTime(char *s) {
    unsigned char *base = *(unsigned char **)(s + 0x8);
    int acc = 0;
    unsigned char b;
    do {
        int idx = *(int *)(s + 0x4);
        acc <<= 7;
        b = base[idx];
        idx++;
        *(int *)(s + 0x4) = idx;
        acc |= (b & 0x7F);
    } while (b & 0x80);
    if (*(unsigned short *)(s + 0x1E) & 0xFFFF) {
        *(int *)(s + 0x14) += acc << 12;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSeqSeRrEnd);
int _SgfadeParam(int a0, int a1, int a2, int a3) {
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgInit);
extern char D_00736140[];
extern int sceSifCallRpc();

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_272338", _SgSndn2Remote);
