#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { char _0[0x50]; unsigned char f50; unsigned char f51; char _52[6]; } P16Ent;

extern int D_0071E900[];

void *func_00258CC0(void) {
    return D_0071E900;
}

extern int D_0071EB00[];

void *func_00258CD0(void) {
    return D_0071EB00;
}

extern int D_0071E8C0[];

int func_00258CE0(void) {
    return D_0071E8C0[0];
}

extern unsigned char D_0071C6C0[];

void *_SgGetPacketCntext(int a0, int a1) {
    unsigned char *p = &D_0071C6C0[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgCalledTickProc);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSetPkAdd);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSeMain);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgBgmMain);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSetRealtimeTickProc);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSetRealtimeVolume);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgTableEnvAdd);

extern void *_SgGetSlotContext(int a0);
extern void *func_00258C68(void);

int _SgSeqKeyOnSlot(void) {
    int *mgr = func_00258C68();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSeKeyOnSlot);

int _SgSeKeyOff(char *a0) {
    long long mask16 = 0;
    long long mask19 = 0;
    char *p18 = (char *)func_00258C68();
    char *p20 = (char *)func_00258CD0();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSeqKeyOff);

int _SgIntoKeyOn(int a0, int a1, int a2) {
    int *r = (int *)func_00258CD0();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSeqSeVolume);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgPan);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgEndSeq);

void _SgTempoChange(int *a0) {
    unsigned char *p = (unsigned char *)(a0[2] + a0[1]);
    void *q = func_00258C68();
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
    p = (int *) func_00258CD0();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContMod);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContModLoop);

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
    mgr = (char *)func_00258C68();
    ctx = (char *)func_00258CD0();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContVol);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContPan);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContDump);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContSeLoop);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContParam);

void _SgContLoopCount(void *a0) {
    void *s0 = a0;
    void *p = func_00258CD0();
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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgContLoop);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgBendForm);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgSeqSeRrEnd);

int _SgfadeParam(int a0, int a1, int a2, int a3) {
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgInit);

extern char D_0071EB40[];
extern int sceSifCallRpc();

int _SgSndn2Remote(int a0, int a1, int a2, int a3, int a4, int a5) {
    return sceSifCallRpc(D_0071EB40, a0, a1, a2, a4, a3, a5, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgSndn2RemoteInit);

extern int sceSifCheckStatRpc(char *a0);

int SgSndn2RemoteSync(void)
{
    int ret = 0;
    int *p = func_00258C68();
    if (p[0x44 / 4] != 0) {
        ret = sceSifCheckStatRpc(D_0071EB40);
    }
    return ret;
}

extern void _SgInit(int a0);

void func_0025C5B8(void) {
    _SgInit(0);
}

void SgInitHot(void) {
    _SgInit(1);
}

void SgQuit(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        _SgSetPkAdd(0xB, i, 0xFFFFFF, 0);
        _SgSetPkAdd(0x28, i, 0, 0);
    }
    _SgSetPkAdd(0x1F, 0, 0, 0);
}

extern void _SgCalledTickProc(void);

void SgCalledTickProc(void) {
    void *r = func_00258C68();
    if (*(int *)((char *)r + 0x44)) {
        _SgCalledTickProc();
    }
}

void SgSetDigitalOutputMode(int a0) {
    _SgSetPkAdd(0x32, 0xA, a0, 0);
}

extern void _SgDmaCommon(int a0, int a1, void *a2, void *a3);

int SgDmaWrite(int a0, void *a1, void *a2) {
    _SgDmaCommon(0x20, a0, a1, a2);
    return 0;
}

int SgDmaRead(void *a0, int a1, void *a2) {
    _SgDmaCommon(0x21, a1, a0, a2);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", _SgDmaCommon);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgGetDmaTransferStatus);

extern int SgVabOpenFakeBody(int *a0, int a1);

int SgVabOpen(int a0, int *a1, int a2) {
    int r;
    r = SgVabOpenFakeBody(a1, a2);
    if (r != -1) {
        SgDmaWrite(a0, (void *)a2, (void *)a1[1]);
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgVabOpenFakeBody);

extern void *_SgGetSeqContext(int a0);
extern void *_SgGetVabContext(int a0);
extern void memset(void *a0, int a1, int a2);

int SgVabClose(int a0) {
    void *t;
    char *p;
    int i;
    int rv = -1;

    if ((unsigned int)(a0 - 1) < 0x7F) {
        t = _SgGetVabContext(a0);
        if (*(int *)((char *)t + 8) != 0) {
            p = (char *)_SgGetSlotContext(0);
            for (i = 0; i < 0x30; i++, p += 0x58) {
                if (*(unsigned char *)(p + 0x54) == a0 &&
                    (unsigned int)*(unsigned char *)(p + 0x50) < 0x30 &&
                    *(unsigned char *)(p + 0x51) != 3) {
                    int *obj = (int *)_SgGetSeqContext(*(unsigned char *)(p + 0x50));
                    int *q = (int *)func_00258C68();
                    *(long long *)((char *)q + 0x28) |= (long long)1 << i;
                    *obj |= 0x2000;
                    memset((char *)obj + 4, 0, 0x50);
                    *obj = 0;
                    *(int *)p |= 0x100;
                    memset(p + 4, 0, 0x54);
                    *(unsigned char *)(p + 0x50) = 0xFF;
                    *(unsigned char *)(p + 0x56) = 0xFF;
                    *(unsigned char *)(p + 0x55) = 0xFF;
                    *(unsigned char *)(p + 0x54) = 0xFF;
                    *(int *)p = 0;
                }
            }
        }
        memset(t, 0, 0xC);
        rv = 0;
    }
    return rv;
}

int SgBgmOpen(int a0, void *a1) {
    char *obj;
    void *mgr;
    void *t;
    int i;
    int rv = -1;

    if ((unsigned int)a0 < 0x80) {
        obj = (char *)_SgGetSeqContext(0);
        mgr = func_00258C68();
        t = _SgGetVabContext(a0);
        if (*(int *)((char *)a1 + 0xC) == 0x71735353 &&
            *(int *)((char *)t + 8) != 0) {
            for (i = 0; i < 0x30; i++, obj += 0x54) {
                *(volatile int *)obj |= 0x2000;
                if ((*(volatile int *)obj & 0xF) == 0) {
                    *(short *)(obj + 0x4C) = (short)i;
                    rv = i;
                    *(short *)(obj + 0x18) = (short)a0;
                    *(int *)(obj + 8) = (int)a1;
                    *(short *)(obj + 0x20) = *(unsigned short *)((char *)a1 + 2);
                    *(volatile int *)obj |= 1;
                    *(short *)(obj + 0x1E) = *(unsigned short *)((char *)a1 + 4);
                    *(int *)(obj + 4) = 0x110;
                    *(int *)(obj + 0x40) = 0x1000;
                    *(int *)(obj + 0x44) = 0x1000;
                    *(int *)(obj + 0x48) = 0x1000;
                    *(int *)(obj + 0x10) =
                        (int)((*(volatile unsigned short *)(obj + 0x20) *
                               *(unsigned short *)(obj + 0x1E))
                              << 0xC) /
                        (int)*(unsigned short *)((char *)mgr + 0x3A) / 0x3C;
                }
                *(volatile int *)obj &= 0xFFFFDFFF;
                if (rv != -1) {
                    break;
                }
            }
        }
    }
    return rv;
}

int SgBgmClose(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)_SgGetSeqContext(a0);
        p[0] |= 0x2000;
        if ((p[0] & 3) == 1) {
            memset((char *)p + 4, 0, 0x50);
            p[0] = 0;
            ret = 0;
        }
        p[0] &= 0xFFFFDFFF;
    }
    return ret;
}

void SgSetReverbEndAddr(int a0, int a1) {
    _SgSetPkAdd(0x14, a0, a1, 0);
}

void SgSetReverbType(int a0, int a1) {
    _SgSetPkAdd(0x15, a0, a1, 0);
}

void SgSetReverbDepth(int a0, int a1, int a2) {
    _SgSetPkAdd(0x16, a0, a1, a2);
}

void SgSetReverbDelaytime(int a0, int a1) {
    _SgSetPkAdd(0x17, a0, a1, 0);
}

void SgSetReverbFeedback(int a0, int a1) {
    _SgSetPkAdd(0x18, a0, a1, 0);
}

void SgSetOutputMode(int a0) {
    void *r = func_00258C68();
    *(short *)((char *)r + 0x38) = a0;
}

void SgSetTickMode(int a0) {
    void *r = func_00258C68();
    *(short *)((char *)r + 0x3A) = a0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgGetSlotStatus);

void SgSetMasterVol(int a0, int a1, int a2) {
    _SgSetPkAdd(0x28, a0, a1, a2);
}

int SgSetBgmVol(unsigned int a0, int a1, int a2) {
    int ret = -1;
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x80) {
        int *p = (int *)_SgGetSeqContext(a0);
        *(volatile int *)p |= 0x2000;
        if (a2 == 0xFFFF) {
            ret = p[0x34 / 4];
            p[0x30 / 4] = a2;
            p[0x34 / 4] = a1;
        } else {
            p[0x38 / 4] = a2;
            ret = 0;
            p[0x3C / 4] = a1;
        }
        *(volatile int *)p |= 0x200;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
    return ret;
}

extern void _SgSetSeVolValue(int a0, int a1);
extern int func_00258CA8(int a0);

int SgSetSeMasterVol(int a0, int a1) {
    int ret = -1;
    if ((unsigned int)(a0 - 1) < 0x7F && a1 >= 0) {
        if (a1 < 0x80) {
            int *p = (int *)_SgGetVabContext(a0);
            if (p[2] != 0) {
                ret = func_00258CA8(a0) & 0x7F;
                _SgSetSeVolValue(a0, a1 | 0x80);
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgBgmPlay);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgBgmStop);

void SgSetBgmTempo(unsigned int a0, int a1) {
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x3C0) {
        int *p = (int *)_SgGetSeqContext(a0);
        void *q = func_00258C68();
        *(short *)((char *)p + 0x1E) = a1;
        *(volatile int *)p |= 0x2000;
        *(int *)((char *)p + 0x10) =
            ((((int)*(unsigned short *)((char *)p + 0x20)
               * *(unsigned short *)((char *)p + 0x1E)) << 12)
             / *(unsigned short *)((char *)q + 0x3A)) / 0x3C;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
}

int SgGetBgmTempo(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        void *r = _SgGetSeqContext(a0);
        ret = *(unsigned short *)((char *)r + 0x1E);
    }
    return ret;
}

int SgGetBgmStatus(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)_SgGetSeqContext(a0);
        p[0] |= 0x2000;
        if (p[0] & 1) {
            ret = (p[0] >> 1) & 1;
            if (p[0] & 0x20) {
                ret |= 2;
            }
        }
        p[0] &= 0xFFFFDFFF;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgGetBgmChStatus);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgSetBgmPanpot);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgSePlay);

void SgSeStop(int a0) {
    unsigned int idx = a0 & 0x7FFF;
    if (idx < 0x30) {
        volatile int *p17 = _SgGetSeqContext(idx);
        *p17 |= 0x2000;
        if (*p17 & 0x4) {
            int mask8000 = a0 & 0x8000;
            P16Ent *p16 = _SgGetSlotContext(0);
            char *p19 = func_00258C68();
            int i;
            *p17 &= 0xFFFFFF77;
            *p17 |= 0x40;
            for (i = 0; i < 0x30; i++, p16++) {
                if (p16->f51 != 2) continue;
                if (p16->f50 != idx) continue;
                if (mask8000) {
                    _SgSetPkAdd(2, i, 0, 0);
                }
                *(long long *) (p19 + 0x28) |= 1LL << i;
            }
        }
        *p17 &= 0xFFFFDFFF;
    }
}

void SgSeStopAll(int a0) {
    int i;
    volatile int *p = (volatile int *)_SgGetSeqContext(0);
    for (i = 0; i < 0x30; i++) {
        p[0] |= 0x2000;
        if ((p[0] & 5) == 4) {
            SgSeStop(i | (a0 << 15));
        }
        p[0] &= 0xFFFFDFFF;
        p = (volatile int *)((char *)p + 0x54);
    }
}

void SgSetSeVolDirect(unsigned int a0, int a1, int a2) {
    if (a0 < 0x30 &&
        a1 >= -0x1000 && a1 < 0x1001 &&
        a2 >= -0x1000 && a2 < 0x1001) {
        int *p = (int *)_SgGetSeqContext(a0);
        p[0x44 / 4] = a1;
        p[0x48 / 4] = a2;
        *(volatile int *)p |= 0x2000;
        *(volatile int *)p |= 0x800;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
}

void SgSetSePitchDirect(unsigned int a0, int a1) {
    volatile int *p;
    int v, v2, v3;
    if (a0 >= 0x30) return;
    if (a1 < 0) return;
    if (a1 >= 0x4000) return;
    p = (volatile int *)_SgGetSeqContext(a0);
    v = p[0];
    *(int *)((char *)p + 0x40) = a1;
    v |= 0x2000;
    p[0] = v;
    v2 = p[0];
    v2 |= 0x400;
    p[0] = v2;
    v3 = p[0];
    v3 = (int)((unsigned int)v3 & 0xFFFFDFFFU);
    p[0] = v3;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgGetSpuSlotMalloc);

int SgSetSpuSlotFree(unsigned int a0) {
    if (a0 < 0x30) {
        unsigned char *p = (unsigned char *)_SgGetSlotContext(a0);
        if (p[0x51] == 3) {
            p[0x51] = 0;
        }
    }
    return -1;
}

void SgStAdpcmInit(void) {
    _SgSetPkAdd(0x3C, 0, 0, 0);
}

void SgStAdpcmQuit(void) {
    _SgSetPkAdd(0x3D, 0, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_258CC0", SgStAdpcmOpen);

int SgStAdpcmClose(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        _SgSetPkAdd(0x3F, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmChannelVolume(unsigned long long a0, unsigned int a1, int a2)
{
    int ret = -1;
    if (a1 < 0x4000 && a2 >= 0 && a2 < 0x4000 && (a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x40, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), (a1 << 16) | a2);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmChannelPitch(unsigned long long a0, int a1)
{
    int ret = -1;
    if (((a0 & 0xFF000000) == 0) && (a1 >= 0) && (a1 <= 0x2EE00)) {
        _SgSetPkAdd(0x41, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), a1);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmPlay(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x42, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmStop(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x43, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmIopReadAddr(int a0) {
    int ret = 0;
    if ((unsigned int)a0 < 0x30) {
        int base = func_00258CE0();
        ret = *(int *)(base + (a0 % 0x18) * 4 + (a0 / 0x18) * 0x60 + 0xC0);
    }
    return ret;
}

void SgStPcmInit(void) {
    _SgSetPkAdd(0x46, 0, 0, 0);
}

void SgStPcmQuit(void) {
    _SgSetPkAdd(0x47, 0, 0, 0);
}

int SgStPcmOpen(int *a0) {
    unsigned int n1, n2;
    int v, v2, ret;
    ret = -1;
    n1 = a0[2];
    if ((unsigned int)0x1FFFFF < n1) goto done;
    n2 = a0[3];
    if ((unsigned int)0x1FFFFF < n2) goto done;
    v = a0[0];
    if (v < 0) goto done;
    if (v < 0x10) {
        v2 = a0[1];
        _SgSetPkAdd(0x48, (v << 24) | v2, n1, n2);
        ret = 0;
    }
    done:
    return ret;
}

int SgStPcmClose(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x10) {
        _SgSetPkAdd(0x49, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

void SgStPcmSetEffect(int a0) {
    _SgSetPkAdd(0x4E, a0, 0, 0);
}

int SgStPcmPlay(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4B, (int)a0, 0, 0);
    }
    return 0;
}

int SgStPcmStop(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4C, (int)a0, 0, 0);
    }
    return 0;
}

int SgStPcmLseek(unsigned int a0, unsigned int a1)
{
    int ret = -1;
    if (a0 < 0x10) {
        if (a1 <= 0x1FFFFF) {
            _SgSetPkAdd(0x4D, (int)a0, (int)a1, 0);
            ret = 0;
        }
    }
    return ret;
}
