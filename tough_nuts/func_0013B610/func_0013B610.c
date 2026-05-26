/* func_0013B610 (ios/pad.c) — pad-slot allocator: scan D_006A6DB0 for a free
 * slot, init it, call func_0013C110, assign a wrapping ID (D_0063218C).
 *
 * STATUS: 8 diffs (was 57) over ~56 iterations. Structure 100% correct AND the
 * zero-ext mask is now MATCHED. The residual 8 (7 real + 1 cosmetic jal-reloc)
 * is gcc-owned instruction SCHEDULING of the call-arg register-moves
 * interleaved with the field stores -> decomp-permuter target.
 *
 * STRUCTURAL TRUTHS FOUND (each a real fix, not scheduling):
 *  - scan loop: goto found/notfound shape from sibling func_0013B8F0
 *    (a `for` loop emits bnel + wrong regalloc).
 *  - do NOT keep `idc` across the call: pass D_0063218C directly, RELOAD after
 *    — else idc is a 2nd callee-saved reg and slot spills s0->s1 (frame +0x10).
 *  - func_0013C110 is **5 args** ($4-$8): 5th arg `0` (the `daddu t0,zero`=a4).
 *  - branch DIRECTION via block placement: success body AFTER fail: label,
 *    reached only by forward `goto store` -> gcc lays it out-of-line as the
 *    bne target (see [[body_out_of_line_branch_direction]]).
 *  - ANCHOR(ff) breaks gcc's store-to-load constant-fold of the 0xC..0xF
 *    bytes -> restores the real lwl/lwr (see [[anchor_breaks_store_to_load_fold]]).
 *
 *  *** THE MASK CRACK (the prior "permuter floor", now SOLVED) ***
 *  The 3rd arg is `(unaligned signed int read of slot+0xC) & 0xFFFFFFFF`
 *  -> original `lwl a2; lwr a2; lui v1,0xffff; dsrl32 v1; and a2,a2,v1`.
 *  ee-gcc only emits this EXACT form (mask in v1, in-place `and a2,a2,v1`,
 *  read into a2) when you DUAL-PIN:
 *    register unsigned long long mask REG("$3") = 0xFFFFFFFFULL;  // mask -> v1
 *    register int wi REG("$6") = ((struct U32{int v}__packed__*)(s+0xC))->v;
 *    func(..., wi & mask, ...);          // wi pinned to the arg reg a2 ($6)
 *  Pinning the INT read to $6 makes lwl/lwr target a2 directly (in-place AND);
 *  pinning the mask CONSTANT to $3 puts it in v1 with the fresh lui+dsrl32.
 *  An unsigned read, a ull `w` local, or `(...)->v & 0xFFFFFFFFLL` inline all
 *  give the wrong form (no-mask / dsll32 shift / `and a2,v0,a2` + extra dsrl32).
 *  This took 18 -> 8 diffs. (see [[dual_pin_read_and_mask_const]])
 *
 * REMAINING (gcc-owned scheduling, plateaued at 8 across ~13 store-order perms
 *  + anchor/pin variants): gcc emits the flag store (sh a1,16) and the
 *  `a1=a3` (id) call-move EARLY and the mask materialization + `a4=0` call-move
 *  LATE; the original interleaves them mid-stores. Store source-order is inert
 *  (all perms = 8); the call-arg moves are gcc-generated -> permuter.
 */

extern int D_00632110;
extern int func_0013C110(int a0, int a1, unsigned long long a2, int a3, int a4);

struct U32_0013B610
{
    int v;
} __attribute__((packed));

typedef struct
{
    int f0;
    int f4;
    int f8;
    unsigned char fC, fD, fE, fF;
    short f10;
    short f12;
    unsigned char f14;
    unsigned char pad[3];
} PadSlot0013B610;

int func_0013B610(int *a0, int a1)
{
    int *slot;
    {
        int *p = D_006A6DB0;
        int i = 0xF;
        while (1)
        {
            if (*p == 0)
            {
                goto found;
            }
            i--;
            if (i == -1)
            {
                goto notfound;
            }
            p = (int *)((char *) p + 0x18);
        }
    notfound:
        slot = 0;
        goto have;
    found:
        slot = p;
    have:;
    }
    if (a0 == 0)
    {
        goto fail;
    }
    {
        int chk = D_00632110;
        if (chk == 0)
        {
            return chk;
        }
    }
    if (slot == 0)
    {
        goto fail;
    }
    {
        PadSlot0013B610 *ps = (PadSlot0013B610 *) slot;
        unsigned char *s = (unsigned char *) slot;
        const T_005F2F00_rec *rec = &D_005F2F00[a1];
        register int id REG("$7") = rec->id;
        int base = *a0 + 0x1A4;
        register unsigned short flag REG("$5") = rec->flag;
        register int ff REG("$9") = 0xFF;
        register unsigned long long mask REG("$3") = 0xFFFFFFFFULL;
        int r;
        ANCHOR(ff);
        ps->fE = ff;
        ps->fF = 0x20;
        ps->f10 = flag;
        ps->fD = 0;
        ps->fC = 0;
        ps->f14 = ff;
        ps->f8 = id;
        ps->f12 = 0;
        ps->f4 = base;
        {
            register int wi REG("$6") = ((struct U32_0013B610 *) (s + 0xC))->v;
            r = func_0013C110(base, id, wi & mask, D_0063218C, 0);
        }
        if (r != 0)
        {
            goto store;
        }
    }
fail:
    return 0;
store:
    {
        int idc = D_0063218C;
        slot[0] = idc;
        idc = idc + 1;
        D_0063218C = idc;
        if (idc == 0)
        {
            D_0063218C = 1;
        }
        return slot[0];
    }
}
