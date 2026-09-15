/* Vendor SCE library run, attribution INFERRED: libsndn2.a.  Neither disc map names
 * a member for these 44 functions (MAIN.MAP is an older link whose .text ends before
 * them; SRCFILE.TXT carries them with symbols but no source paths).  The evidence
 * is the neighbour the map does attest: libsndn2.a(sound.o) calls the _Sg family,
 * _SgSndn2Remote carries the library's name, and retail links the block directly
 * before sound.o.  The member name is unknown, so the file takes the family's.
 * VMA 0x273228..0x276AD0. */
#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern unsigned char D_00731C00[];

void *_SgGetSlotContext(int a0)
{
    return &D_00731C00[a0 * 0x58];
}

extern unsigned char D_00732C80[];

void *_SgGetSeqContext(int a0)
{
    return &D_00732C80[a0 * 0x54];
}

extern int D_00733C40[];

void *_SgGetComContext(void)
{
    return D_00733C40;
}

extern unsigned char D_00731600[];

void *_SgGetVabContext(int a0)
{
    return &D_00731600[a0 * 0xC];
}

extern int D_00735F00[];

void _SgSetSeVolValue(int a0, int a1)
{
    D_00735F00[a0] = a1;
}

int _SgGetSeVolValue(int a0)
{
    return D_00735F00[a0];
}

void *_SgSetSeContext(void)
{
    return D_00735F00;
}

extern int D_00736100[];

void *_SgGetHeadContext(void)
{
    return D_00736100;
}

extern int D_00735EC0[];

int _SgGetIop2EeContext(void)
{
    return D_00735EC0[0];
}

extern unsigned char D_00733CC0[];

void *_SgGetPacketCntext(int a0, int a1)
{
    unsigned char *p = &D_00733CC0[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgCalledTickProc);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSetPkAdd);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeMain);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgBgmMain);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSetRealtimeTickProc);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSetRealtimeVolume);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgTableEnvAdd);

extern void *_SgGetComContext(void);

int _SgSeqKeyOnSlot(void)
{
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

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeKeyOnSlot);

extern void *_SgGetHeadContext(void);

int _SgSeKeyOff(char *a0)
{
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

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeqKeyOff);

int _SgIntoKeyOn(int a0, int a1, int a2)
{
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

int _SgPitchTableVag(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    _SgSetPkAdd(4, a0, (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | a4, (a5 << 24) | a6);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeqSeVolume);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgPan);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgEndSeq);

void _SgTempoChange(int *a0)
{
    unsigned char *p = (unsigned char *)(a0[2] + a0[1]);
    void *q = _SgGetComContext();
    *(unsigned short *)((char *)a0 + 0x1E) = p[2] | (p[3] << 8);
    *(int *)((char *)a0 + 0x10) =
        ((((int)*(unsigned short *)((char *)a0 + 0x20) * *(unsigned short *)((char *)a0 + 0x1E))
          << 12) /
         *(unsigned short *)((char *)q + 0x3A)) /
        0x3C;
    a0[1] += 4;
}

void _SgProgChange(int *a0)
{
    int *p;
    unsigned short idx;
    char *base;
    char *v2;
    if ((*(a0 + 0)) & 2) {
        p = (int *)_SgGetHeadContext();
        idx = *((unsigned short *)(((char *)a0) + 0x4E));
        v2 = (char *)(*((int *)(((char *)p) + 0x10)));
        ;
        *((((char *)(*((int *)(((char *)p) + 8)))) + (idx << 4)) + 0x12) =
            *((unsigned char *)(v2 + 1));
        idx = *((unsigned short *)(((char *)a0) + 0x4E));
        base = ((char *)(*((int *)(((char *)p) + 8)))) + (idx << 4);
        *(base + 0x1A) = 0x40;
        idx = *((unsigned short *)(((char *)a0) + 0x4E));
        base = ((char *)(*((int *)(((char *)p) + 8)))) + (idx << 4);
        *(base + 0x1B) = 0x40;
    }
    *(a0 + 1) += 2;
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContMod);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContModLoop);
/* Reverted to asm 2026-09-15: the only body in the tree that the raw
 * toolchain cannot produce. ROM puts `cvt.s.w $f1,$f1` in the delay slot of
 * the `b` that joins the two arms of the float divide; ee-gcc emits the cvt
 * before the b and ee-as 2.9-991111 never swaps an instruction into a branch
 * delay slot (probed: default, -O, -O0, -g excepted, .set bopt, every -mcpu
 * and -mips level). It matched only through the compile_c.sh `mtc1;cvt;b`
 * reorder rewrite, retired with the rest. Seed: tails/seeds/
 * sg.rewrite_cop1_mtc1cvtb_SgContPolta_TU.c, ledger: docs/rewrite_ledger.md. */
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContPolta);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContVol);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContPan);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContDump);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContSeLoop);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContParam);

void _SgContLoopCount(void *a0)
{
    void *s0 = a0;
    void *p = _SgGetHeadContext();
    int t = *(unsigned short *)((char *)s0 + 0x28);
    int val;
    int pval;
    if (t == 1)
        goto case1;
    if (t >= 2)
        goto ge2;
    if (t == 0)
        goto case0;
    goto done;
ge2:
    if (t == 2)
        goto case12;
    goto done;
case0:
    {
        int q0 = *(int *)((char *)p + 0x10);
        int b0 = *(unsigned char *)((char *)q0 + 0x2);
        *(short *)((char *)s0 + 0x2A) = 0;
        *(short *)((char *)s0 + 0x26) = b0;
        goto done;
    }
case1:
case12:
    {
        int q12 = *(int *)((char *)p + 0x10);
        int b12 = *(unsigned char *)((char *)q12 + 0x2);
        *(short *)((char *)s0 + 0x2A) = b12;
    }
done:
    val = *(int *)((char *)s0 + 0x4);
    *(int *)((char *)s0 + 0x4) = val + 3;
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContLoop);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgBendForm);

void _SgDeltaTime(char *s)
{
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

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeqSeRrEnd);

int _SgfadeParam(int a0, int a1, int a2, int a3)
{
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgInit);

extern char D_00736140[];
extern int sceSifCallRpc();

int _SgSndn2Remote(int a0, int a1, int a2, int a3, int a4, int a5)
{
    return sceSifCallRpc(D_00736140, a0, a1, a2, a4, a3, a5, 0, 0);
}
