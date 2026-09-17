/* Vendor SCE library run, attribution INFERRED: libsndn2.a.  Neither disc map names
 * a member for these 44 functions (MAIN.MAP is an older link whose .text ends before
 * them; SRCFILE.TXT carries them with symbols but no source paths).  The evidence
 * is the neighbour the map does attest: libsndn2.a(sound.o) calls the _Sg family,
 * _SgSndn2Remote carries the library's name, and retail links the block directly
 * before sound.o.  The member name is unknown, so the file takes the family's.
 * VMA 0x273228..0x276AD0. */
#include "common.h"
#include <sifrpc.h>
#include <string.h>

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

/* Reverted to asm 2026-09-17 (chain 3 pass 15): 305 of 312 instructions, the
 * whole shape derived; the residual is the emission order of the status-nibble
 * switch arms.  Body and mechanism:
 * tails/seeds/sg.c3p15_SgCalledTickProc_305of312_TU.c. */
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgCalledTickProc);

/* The EE to IOP packet ring in the common context: c[0xF] is the page the ring
 * lives in and c[0x10] the write index _SgGetPacketCntext resolves to a slot.
 * The index is read and bumped through a volatile view because the IOP side
 * polls it while the EE fills the ring; the ROM proves it, reloading the count
 * after storing it. */
int _SgSetPkAdd(int a0, int a1, int a2, int a3)
{
    int *c = _SgGetComContext();
    volatile int *n = (volatile int *)&c[0x10];
    int *p = _SgGetPacketCntext(c[0xF], c[0x10]);

    if ((unsigned int)*n >= 0xFF) {
        return -1;
    }
    p[0] = a0;
    p[1] = a1;
    p[2] = a2;
    p[3] = a3;
    *n = *n + 1;
    return *n;
}

/* Reverted to asm 2026-09-17 (chain 3 pass 15): 262 of 263 instructions, the
 * whole callee-saved colouring and every other word identical.  The one
 * residual is a gcse PRE edge insertion; the mechanism and the derived body
 * are in tails/seeds/sg.c3p15_SgSeMain_262of263_strict94_TU.c. */
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSeMain);
/* Reverted to asm 2026-09-17 (chain 3 pass 15): 295 of 295 instructions with
 * fifteen differing words, all of them inside the note-count dispatch at the
 * head of the function.  The derived body and the mechanism are in
 * tails/seeds/sg.c3p15_SgBgmMain_295of295_strict15_TU.c. */
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgBgmMain);
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgSetRealtimeTickProc);

/* Realtime volume: mode 1 takes the SE volume table's value for the vab and
 * writes it at the head of the vab's 0x40 block, mode 2 takes the sequence's
 * own 0x34 level and paints it over every channel the 0x38 mask selects.  The
 * status word is read through a volatile view at each test, as elsewhere in
 * this file. Every matching voice then gets its 0x1E level and, for a keyed
 * voice, its 0x16 channel level, and is re-levelled through _SgSeqSeVolume. */
int _SgSetRealtimeVolume(int *a0)
{
    unsigned char *base;
    unsigned char *s;
    int mode = 0;
    int i;
    int k;

    if ((*(volatile int *)a0 & 5) == 4) {
        int v = _SgGetSeVolValue(*(unsigned short *)((char *)a0 + 0x18));

        if (v & 0x80) {
            *(int *)((char *)a0 + 0x30) = 0xFFFF;
            mode = 1;
            *(int *)((char *)a0 + 0x34) = v & 0x7F;
        }
    } else if ((*(volatile int *)a0 & 5) == 1) {
        if (*(volatile int *)a0 & 0x200) {
            mode = 2;
            a0[0] = *(volatile int *)a0 & 0xFFFFFDFF;
        }
    }
    switch (mode) {
    case 1:
        base = (unsigned char *)*(
            int *)(*(int *)_SgGetVabContext(*(unsigned short *)((char *)a0 + 0x18)) + 0x40);
        *base = *((unsigned char *)a0 + 0x34);
        break;
    case 2:
        base = (unsigned char *)a0[2];
        if (*(int *)((char *)a0 + 0x30) == 0xFFFF) {
            *base = *((unsigned char *)a0 + 0x34);
        }
        if (*(int *)((char *)a0 + 0x38) != 0) {
            for (i = 0; i < 0x10; i++) {
                if ((*(int *)((char *)a0 + 0x38) >> i) & 1) {
                    *(char *)(base + (i << 4) + 0x1E) = *((unsigned char *)a0 + 0x3C);
                }
            }
        }
        break;
    default:
        return -1;
    }
    s = _SgGetSlotContext(0);
    for (i = 0; i < 0x30; i++, s += 0x58) {
        k = s[0x51];
        if (k != 0 && k != 3 && s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
            *(short *)(s + 0x1E) = *base;
            if (k == 1) {
                unsigned char *vp = base + 0x1E;

                *(short *)(s + 0x16) = vp[s[0x4F] << 4];
            }
            _SgSeqSeVolume(i, a0);
        }
    }
    return 0;
}

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

/* Pick a voice slot for an SE key-on.  Pass one looks for a slot already
 * keyed by this sound (state 2) with the same 0x53 owner and 0x54 key, pass
 * two for a free slot, and the last pass steals the cheapest slot: a keyed-off
 * slot (state 1) wins over a sounding one (state 2), and a sounding slot is
 * only stolen when its 0x52 priority is at or below the caller's.  The
 * rotating cursor mgr[0xC] is what spreads the search over the 48 slots. */
int _SgSeKeyOnSlot(int a0, int a1, int a2)
{
    int *mgr = _SgGetComContext();
    int off_idx = -1;
    int off_val = -1;
    int on_idx = -1;
    int on_val = -1;
    int i;
    int idx;
    unsigned char *obj;
    int divisor;
    int one;
    int two;

    if (a0 != 0) {
        i = 0;
        do {
            idx = (unsigned int)mgr[0xC] % 0x30;
            obj = _SgGetSlotContext(idx);
            if ((*(int *)obj & 0x100) == 0 && obj[0x51] == 2 && obj[0x53] == a0 &&
                obj[0x54] == a2) {
                return idx;
            }
            mgr[0xC]++;
        } while (++i < 0x30);
    }
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
    two = 2;
    i = 0x2F;
    do {
        idx = (unsigned int)mgr[0xC] % divisor;
        obj = _SgGetSlotContext(idx);
        if ((*(int *)obj & 0x100) == 0) {
            if (obj[0x51] == one) {
                int v = *(int *)(obj + 4);
                if ((unsigned int)v < (unsigned int)off_val) {
                    off_idx = idx;
                    off_val = v;
                }
            } else if (obj[0x51] == two) {
                if (obj[0x52] <= a1) {
                    int v = *(int *)(obj + 4);
                    if ((unsigned int)v < (unsigned int)on_val) {
                        on_idx = idx;
                        on_val = v;
                    }
                }
            }
        }
        mgr[0xC]++;
    } while (--i >= 0);
    if (off_idx != -1) {
        return off_idx;
    }
    if (on_idx != -1) {
        return on_idx;
    }
    return -1;
}

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

/* Key off every voice the sequence owns: the 48 slots are matched on the
 * program byte e[1], the sequence's own 0x4E and 0x4C ids, an active 0x51 and
 * the 0x18 channel, and each match sets the sequence's bit in the common
 * context's 64-bit key-off mask at 0x28.  The slot status word is read through
 * a volatile view at every test because the tick proc updates it while the
 * sequence runs; the write-back is plain. */
int _SgSeqKeyOff(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    char *com = _SgGetComContext();
    int *head = _SgGetHeadContext();
    unsigned char *e = (unsigned char *)head[4];
    int i;

    for (i = 0; i < 0x30; i++, s += 0x58) {
        if (s[0x4E] == e[1]) {
            if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E)) {
                if (s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
                    if (s[0x51] == 1) {
                        if (s[0x54] == *(unsigned short *)((char *)a0 + 0x18)) {
                            if ((*(volatile int *)s & 4) == 0) {
                                *(int *)s = *(volatile int *)s & 0xFFFFFFF7;
                            } else if ((*(volatile int *)s & 8) != 0) {
                                *(int *)s = *(volatile int *)s & 0xFFFFFFF7;
                            }
                            *(long long *)(com + 0x28) =
                                *(long long *)(com + 0x28) | ((long long)1 << i);
                        }
                    }
                }
            }
        }
    }
    a0[1] += 3;
    return 0;
}

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

int _SgPitchTableVag(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    _SgSetPkAdd(4, a0, (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | a4, (a5 << 24) | a6);
    return 0;
}

/* Fold the slot's six 16-bit envelope and volume terms into one 64-bit product
 * and scale it by the two channel volumes at 0x44 and 0x48, giving the left and
 * right levels the IOP packet carries.  With the common context's 0x38 flag set
 * both sides take the larger magnitude, and a non-zero 0x2E folds the slot's
 * own attenuation into the top byte. */
int _SgSeqSeVolume(int a0, int *a1)
{
    unsigned char *slot = _SgGetSlotContext(a0);
    int *com = _SgGetComContext();
    long long m;
    short l;
    short r;

    m = (long long)*(unsigned short *)(slot + 0x16) * *(unsigned short *)(slot + 0x22);
    m = m * ((long long)*(unsigned short *)(slot + 0x1C) * *(unsigned short *)(slot + 0x1A));
    m = m * ((long long)*(unsigned short *)(slot + 0x18) * *(unsigned short *)(slot + 0x1E));
    l = (m * (*(unsigned short *)(slot + 0x20) >> 8) * a1[0x11]) >> 46;
    r = (m * (*(unsigned short *)(slot + 0x20) & 0xFF) * a1[0x12]) >> 46;
    if (*(unsigned short *)((char *)com + 0x38) == 1) {
        l = (l < 0) ? -l : l;
        r = (r < 0) ? -r : r;
        if (r < l) {
            r = l;
        } else {
            l = r;
        }
    }
    l = (l & 0xFFFF) >> 1;
    r = (r & 0xFFFF) >> 1;
    if (*(unsigned short *)(slot + 0x2E) != 0) {
        l = (*(unsigned short *)(slot + 0x2E) << 8) | (l >> 7);
        r = (*(unsigned short *)(slot + 0x2E) << 8) | (r >> 7);
    }
    _SgSetPkAdd(1, a0, l, r);
    return 0;
}

/* The head context's three tables: h[0] the common block, h[1] the slot table
 * and h[2] the sequence table, both indexed by a 16-byte record.  The slot
 * pointer is advanced over the record for the read and put back afterwards. */
int _SgPan(int a0, int a1)
{
    int *h = _SgGetHeadContext();
    unsigned char *seq = (unsigned char *)(h[2] + a1 * 16);
    int v;

    h[1] += a0 * 16;
    v = seq[0x14] + *(unsigned char *)(h[1] + 0xC) - 0x80;
    v += *(unsigned char *)(h[0] + 2);
    h[1] -= a0 * 16;
    if (v >= 0x80) {
        v = 0x7F;
    }
    if (v < 0) {
        v = 0;
    }
    return v;
}

/* End of sequence: a0 is the sequence context, a0[0] its status word, a0[1] the
 * event cursor, a0[5] the repeat state and 0x4C the sequence id the voices carry
 * at slot offset 0x50.  Every status word here is READ through a volatile view
 * and written back plainly: the ROM reloads the word at each update (the tick
 * proc and the IOP both touch these while the sequence runs) but keeps the
 * write-back movable, and it is the store that fills the branch delay slot. */
void _SgEndSeq(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    int i;

    if (*(volatile int *)a0 & 4) {
        a0[5] = 0;
        a0[0] = *(volatile int *)a0 & 0xFFFFEFF7;
    } else {
        a0[1] = 0x110;
        a0[0] = *(volatile int *)a0 & 0xFFFFFFFD;
    }
    a0[0] = *(volatile int *)a0 | 0x40;
    for (i = 0; i < 48; i++, s += 0x58) {
        if (s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
            if (s[0x51] == 1) {
                *(int *)s = *(volatile int *)s & 0xFFFFFFEF;
                *(short *)(s + 0x26) = 0x40;
            }
        }
    }
    *((char *)a0 + 0x51) = *((unsigned char *)a0 + 0x50);
}

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

/* Modulation controller: with bit 8 of the status word set the event carries
 * its own slot key (0x2C against the event byte 3 and 0x4E against byte 4)
 * and the cursor advances 5, otherwise the value lands in the program record
 * at 0x19 and the sequence keys the slots itself for a 3 byte event.  Both
 * loops read AND write the slot status word through a volatile view. */
void _SgContMod(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    int *head = _SgGetHeadContext();
    int i;

    if (a0[0] & 8) {
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x51] == 2) {
                if (*(unsigned short *)(s + 0x2C) == *(unsigned char *)(head[4] + 3)) {
                    if (s[0x4E] == *(unsigned char *)(head[4] + 4)) {
                        if (s[0x54] == *(unsigned short *)((char *)a0 + 0x18)) {
                            if (s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
                                *(short *)(s + 0x12) = *(unsigned char *)(head[4] + 2);
                                *(volatile int *)s = *(volatile int *)s | 0x10;
                            }
                        }
                    }
                }
            }
        }
        a0[1] += 5;
    } else {
        *(char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x19) =
            *(unsigned char *)(head[4] + 2);
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E)) {
                if (s[0x54] == *(unsigned short *)((char *)a0 + 0x18)) {
                    if (s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
                        if (s[0x51] == 1) {
                            *(short *)(s + 0x12) = *(unsigned char *)(head[4] + 2);
                            *(volatile int *)s = *(volatile int *)s | 0x10;
                        }
                    }
                }
            }
        }
        a0[1] += 3;
    }
}

/* Modulation loop-rate controller: the event byte maps to a tick period,
 * 240 / (60 - value * 58 / 127), which is stored as the slot's 0x14 rate and,
 * on the sequence-keyed path, into the program record at 0x1C. */
void _SgContModLoop(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    int *head = _SgGetHeadContext();
    int v = 240 / (60 - *(unsigned char *)(head[4] + 2) * 58 / 127);
    int i;

    if (a0[0] & 8) {
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
                *(unsigned short *)(s + 0x2C) == *(unsigned char *)(head[4] + 3) &&
                s[0x4E] == *(unsigned char *)(head[4] + 4) &&
                s[0x54] == *(unsigned short *)((char *)a0 + 0x18) &&
                s[0x50] == *(unsigned short *)((char *)a0 + 0x4C) && s[0x51] == 2) {
                *(short *)(s + 0x14) = v;
            }
        }
        a0[1] += 5;
    } else {
        *(char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x1C) = v;
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
                s[0x54] == *(unsigned short *)((char *)a0 + 0x18) &&
                s[0x50] == *(unsigned short *)((char *)a0 + 0x4C) && s[0x51] == 1) {
                *(short *)(s + 0x14) = v;
            }
        }
        a0[1] += 3;
    }
}

/* Reverted to asm 2026-09-15: the only body in the tree that the raw
 * toolchain cannot produce. ROM puts `cvt.s.w $f1,$f1` in the delay slot of
 * the `b` that joins the two arms of the float divide; ee-gcc emits the cvt
 * before the b and ee-as 2.9-991111 never swaps an instruction into a branch
 * delay slot (probed: default, -O, -O0, -g excepted, .set bopt, every -mcpu
 * and -mips level). It matched only through the compile_c.sh `mtc1;cvt;b`
 * reorder rewrite, retired with the rest. Seed: tails/seeds/
 * sg.rewrite_cop1_mtc1cvtb_SgContPolta_TU.c, ledger: docs/rewrite_ledger.md. */
INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContPolta);

/* Volume controller: with bit 8 of the status word set the event keys the
 * voices itself and their 0x34 target, 0x36 current and 0x38/0x3A step are
 * refreshed from the event and the common tempo; otherwise the value lands in
 * the program record at 0x13 and each matching voice is re-levelled through
 * _SgSeqSeVolume. */
void _SgContVol(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    char *com = _SgGetComContext();
    int *head = _SgGetHeadContext();
    int i;

    if (a0[0] & 8) {
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x51] == 2 && s[0x54] == *(unsigned short *)((char *)a0 + 0x18)) {
                unsigned char *e = (unsigned char *)head[4];

                if (*(unsigned short *)(s + 0x2C) == e[4] && s[0x4E] == e[5] &&
                    s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
                    int v;

                    *(int *)s |= 0x40;
                    *(short *)(s + 0x34) = e[3];
                    *(short *)(s + 0x36) = *(unsigned short *)(s + 0x1A);
                    v = (e[2] << 2) * *(unsigned short *)(com + 0x3A) / 60;
                    *(short *)(s + 0x38) = v;
                    *(short *)(s + 0x3A) = v;
                }
            }
        }
        a0[1] += 6;
    } else {
        *(char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x13) =
            *(unsigned char *)(head[4] + 2);
        for (i = 0; i < 48; i++, s += 0x58) {
            if (s[0x51] == 1 && s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
                s[0x54] == *(unsigned short *)((char *)a0 + 0x18) &&
                s[0x50] == *(unsigned short *)((char *)a0 + 0x4C)) {
                *(short *)(s + 0x22) = *(unsigned char *)(head[4] + 2);
                _SgSeqSeVolume(i, a0);
            }
        }
        a0[1] += 3;
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libsndn2/sg", _SgContPan);

/* Dump (damper) controller: the program record's 0x1B byte takes the event's
 * value, and when it goes to zero every voice the sequence holds either gets
 * its bit set in the common context's 64-bit key-off mask or, if the damper is
 * still down, is marked 8.  The slot status word is read through a volatile
 * view at both sites: the ROM reloads it for the mark. */
void _SgContDump(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    char *com = _SgGetComContext();
    int *head = _SgGetHeadContext();
    int i;

    *(char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x1B) =
        *(unsigned char *)(head[4] + 1);
    if (*(unsigned char *)(head[4] + 1) == 0) {
        for (i = 0; i < 0x30; i++, s += 0x58) {
            if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
                s[0x54] == *(unsigned short *)((char *)a0 + 0x18) &&
                s[0x50] == *(unsigned short *)((char *)a0 + 0x4C) &&
                (*(volatile int *)s & 4) != 0) {
                if (*(unsigned char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) +
                                       0x1B) == 0) {
                    *(long long *)(com + 0x28) = *(long long *)(com + 0x28) | ((long long)1 << i);
                } else {
                    *(int *)s = *(volatile int *)s | 8;
                }
            }
        }
    }
    a0[1] += 3;
}

/* The SE loop event: a0[0] carries the voice flags, a0[1] the event cursor,
 * a0[2] the sequence data base and a0[3] the loop target offset.  The event
 * bytes are e[2] and e[3] (the 16-bit loop target) and e[4] the repeat count;
 * the running count lives at 0x22 and the byte the loop jumps to at 0x24.
 * The flag word is read and written through a volatile view because the tick
 * proc that runs the voice updates it: the ROM reloads it in the arm that
 * clears the loop flag. */
void _SgContSeLoop(int *a0)
{
    int *p = _SgGetHeadContext();
    unsigned char *e = (unsigned char *)*(int *)((char *)p + 0x10);
    char *tbl = (char *)a0[2];

    *(volatile int *)a0 |= 0x80;
    if (e[4] != 0) {
        if (*(unsigned short *)((char *)a0 + 0x22) == e[4]) {
            *(short *)((char *)a0 + 0x22) = 0;
            *(volatile int *)a0 &= 0xFFFFFF7F;
        } else {
            int v;

            a0[3] = (e[3] << 8) + e[2];
            v = *(unsigned char *)(tbl + a0[3]);
            *(unsigned short *)((char *)a0 + 0x22) = *(unsigned short *)((char *)a0 + 0x22) + 1;
            *(short *)((char *)a0 + 0x24) = v;
        }
    } else {
        int w;

        a0[3] = (e[3] << 8) + e[2];
        w = *(unsigned char *)(tbl + a0[3]);
        *(short *)((char *)a0 + 0x24) = w;
    }
    a0[1] += 5;
}

extern void SgSetReverbType(int a0, int a1);
extern void SgSetReverbDepth(int a0, int a1, int a2);
extern void SgSetReverbDelaytime(int a0, int a1);
extern void SgSetReverbFeedback(int a0, int a1);

/* Parameter controller: the event's 0x2A selector picks one of the SPU voice
 * register fields in the head context's register block at head[1], packs the
 * event byte into it and then pushes the two packed words to every voice the
 * sequence holds through _SgSetPkAdd command 2.  The selectors that touch the
 * global reverb, and the one that only latches the 0x26 value, do not touch
 * any voice and just advance the cursor.  Every field is cleared by storing
 * the masked halfword back before the new bits are ORed in. */
void _SgContParam(int *a0)
{
    int *head = _SgGetHeadContext();
    unsigned char *s = _SgGetSlotContext(0);
    int i;

    switch (*(unsigned short *)((char *)a0 + 0x2A)) {
    case 0: {
        unsigned char *e = (unsigned char *)head[4];

        *(short *)((char *)a0 + 0x26) = e[2];
        *(short *)((char *)a0 + 0x2A) = 0;
        goto end;
    }
    case 4: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 6) = *(unsigned short *)(r + 6) & 0xFF;
        *(short *)(r + 6) = *(unsigned short *)(r + 6) | ((0x7F - e[2]) << 8);
        break;
    }
    case 5: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 6) = *(unsigned short *)(r + 6) & 0xFF;
        *(short *)(r + 6) = (*(unsigned short *)(r + 6) | ((0x7F - e[2]) << 8)) | 0x8000;
        break;
    }
    case 6: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 6) = *(unsigned short *)(r + 6) & 0xFF0F;
        *(short *)(r + 6) = *(unsigned short *)(r + 6) | (((0x7F - e[2]) >> 3) << 4);
        break;
    }
    case 7: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 6) = *(unsigned short *)(r + 6) & 0xFFF0;
        *(short *)(r + 6) = *(unsigned short *)(r + 6) | (e[2] >> 3);
        break;
    }
    case 8: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 8) = *(unsigned short *)(r + 8) & 0x3F;
        *(short *)(r + 8) = *(unsigned short *)(r + 8) | ((0x7F - e[2]) << 6);
        *(short *)(r + 8) =
            *(unsigned short *)(r + 8) | (0x4000 - *(unsigned short *)((char *)a0 + 0x2E));
        break;
    }
    case 9: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 8) = *(unsigned short *)(r + 8) & 0x3F;
        *(short *)(r + 8) = *(unsigned short *)(r + 8) | ((0x7F - e[2]) << 6) | 0x8000u;
        *(short *)(r + 8) =
            *(unsigned short *)(r + 8) | (0x4000 - *(unsigned short *)((char *)a0 + 0x2E));
        break;
    }
    case 10: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 8) = *(unsigned short *)(r + 8) & 0xFFC0;
        *(short *)(r + 8) = *(unsigned short *)(r + 8) | ((0x7F - e[2]) >> 2);
        break;
    }
    case 11: {
        unsigned char *r = (unsigned char *)head[1];
        unsigned char *e = (unsigned char *)head[4];

        *(short *)(r + 8) = *(unsigned short *)(r + 8) & 0xFFC0;
        *(short *)(r + 8) = (*(unsigned short *)(r + 8) | ((0x7F - e[2]) >> 2)) | 0x20;
        break;
    }
    case 12: {
        unsigned char *e = (unsigned char *)head[4];

        if (e[2] >= 0x41) {
            *(short *)((char *)a0 + 0x2E) = 0x4000;
        } else {
            *(short *)((char *)a0 + 0x2E) = 0;
        }
        break;
    }
    case 15:
        SgSetReverbType(0, *(unsigned char *)(head[4] + 2));
        SgSetReverbType(1, *(unsigned char *)(head[4] + 2));
        goto end;
    case 16:
        SgSetReverbDepth(0, *(unsigned char *)(head[4] + 2), *(unsigned char *)(head[4] + 2));
        SgSetReverbDepth(1, *(unsigned char *)(head[4] + 2), *(unsigned char *)(head[4] + 2));
        goto end;
    case 17:
        SgSetReverbFeedback(0, *(unsigned char *)(head[4] + 2));
        SgSetReverbFeedback(1, *(unsigned char *)(head[4] + 2));
        goto end;
    case 18:
    case 19:
        SgSetReverbDelaytime(0, *(unsigned char *)(head[4] + 2));
        SgSetReverbDelaytime(1, *(unsigned char *)(head[4] + 2));
        goto end;
    }
    for (i = 0; i < 0x30; i++, s += 0x58) {
        if (s[0x51] == 1 && s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
            s[0x50] == *(unsigned short *)((char *)a0 + 0x4C) &&
            (*(unsigned short *)((char *)a0 + 0x2C) == 0xFF ||
             *(unsigned short *)(s + 0xC) == *(unsigned short *)((char *)a0 + 0x2C))) {
            unsigned char *r = (unsigned char *)head[1];

            _SgSetPkAdd(2, i, *(unsigned short *)(r + 6), *(unsigned short *)(r + 8));
        }
    }
end:
    a0[1] += 3;
}

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

/* Loop controller dispatch on the event byte: controller numbers 0 to 15 park
 * the value at 0x2C, 0x10 arms the loop, 0x14 latches the cursor into 0xC,
 * 0x1E steps the repeat count against its limit at 0x26 and 0x7F resets.  The
 * status word is read through a volatile view at every update, as elsewhere in
 * this file. */
void _SgContLoop(int *a0)
{
    int *head = _SgGetHeadContext();
    unsigned char *e = (unsigned char *)head[4];

    switch (e[2]) {
    case 0 ... 0xF:
        *(short *)((char *)a0 + 0x2C) = e[2];
        *(short *)((char *)a0 + 0x28) = 2;
        break;
    case 0x14:
        *(short *)((char *)a0 + 0x24) = *(unsigned char *)((char *)a0 + 0x50);
        *(int *)((char *)a0 + 0xC) = a0[1];
        *(short *)((char *)a0 + 0x28) = 0;
        *(short *)((char *)a0 + 0x2A) = 0;
        break;
    case 0x1E:
        if (*(unsigned short *)((char *)a0 + 0x26) == 0x7F) {
            a0[0] = *(volatile int *)a0 | 0x80;
        } else {
            if (*(unsigned short *)((char *)a0 + 0x22) >= *(unsigned short *)((char *)a0 + 0x26)) {
                *(int *)((char *)a0 + 0xC) = 0;
                a0[0] = *(volatile int *)a0 & 0xFFFFFF7F;
                *(short *)((char *)a0 + 0x22) = 0;
                *(short *)((char *)a0 + 0x28) = 0;
                break;
            }
            *(short *)((char *)a0 + 0x22) = *(unsigned short *)((char *)a0 + 0x22) + 1;
            a0[0] = *(volatile int *)a0 | 0x80;
        }
        *(short *)((char *)a0 + 0x28) = 0;
        break;
    case 0x10:
        *(short *)((char *)a0 + 0x28) = 1;
        break;
    case 0x7F:
        *(short *)((char *)a0 + 0x28) = 2;
        *(short *)((char *)a0 + 0x2C) = 0xFF;
        break;
    }
end:
    a0[1] += 3;
}

void _SgBendForm(int *a0)
{
    unsigned char *s = _SgGetSlotContext(0);
    int *head = _SgGetHeadContext();
    int i;

    *(char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x1A) =
        *(unsigned char *)(head[4] + 1);
    for (i = 0; i < 0x30; i++, s += 0x58) {
        if (s[0x4F] == *(unsigned short *)((char *)a0 + 0x4E) &&
            s[0x54] == *(unsigned short *)((char *)a0 + 0x18) &&
            s[0x50] == *(unsigned short *)((char *)a0 + 0x4C) && s[0x51] == 1) {
            *(short *)(s + 0x26) = *(unsigned char *)(head[4] + 1);
            _SgPitchTableVag(
                i, *(unsigned short *)(s + 0x2A), s[0x4E], *(short *)(s + 0x24),
                *(unsigned char *)(head[2] + (*(unsigned short *)((char *)a0 + 0x4E) << 4) + 0x1A),
                *(unsigned short *)(s + 0x28), 0x1000);
        }
    }
    a0[1] += 2;
}

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

extern unsigned char D_00735CC0[];

/* Bring the driver up: hand the IOP side the uncached-accelerated address of
 * the EE to IOP mailbox, clear every context block, mark all 48 slots free and
 * set the common context's default tempo. */
void _SgInit(int a0)
{
    int buf[16];
    void *se = _SgSetSeContext();
    void *pk = _SgGetPacketCntext(0, 0);
    unsigned char *slot = _SgGetSlotContext(0);
    void *vab = _SgGetVabContext(0);
    char *com = _SgGetComContext();
    void *seq = _SgGetSeqContext(0);
    int i;

    D_00735EC0[0] = (int)D_00735CC0 | 0x20000000;
    buf[0] = 0x1E;
    buf[1] = a0;
    buf[4] = 0;
    _SgSndn2Remote(0x65, 0, (int)buf, (int)buf, 0x40, 0x40);
    memset(slot, 0, 0x1080);
    memset(vab, 0, 0x600);
    memset(seq, 0, 0xFC0);
    memset(com, 0, 0x50);
    memset(pk, 0, 0x1000);
    memset((void *)D_00735EC0[0], 0, 0x200);
    memset(se, 0, 0x200);
    for (i = 0; i < 48; i++, slot += 0x58) {
        slot[0x50] = 0xFF;
        slot[0x56] = 0xFF;
        slot[0x55] = 0xFF;
        slot[0x54] = 0xFF;
    }
    /* the common context is what the IOP side polls, so these four go out in
       the order they are written */
    *(volatile int *)(com + 0x48) = 0;
    *(volatile int *)(com + 0x44) = 1;
    *(volatile short *)(com + 0x3A) = 0x3C;
    *(volatile int *)(com + 0x40) = 0;
}

extern char D_00736140[];

int _SgSndn2Remote(int a0, int a1, int a2, int a3, int a4, int a5)
{
    return sceSifCallRpc(D_00736140, a0, a1, a2, a4, a3, a5, 0, 0);
}
