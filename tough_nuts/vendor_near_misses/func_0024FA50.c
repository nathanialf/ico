/* func_0024FA50 — NEAR MISS, 6 diff sites (was 15).  NOT a match; do not
 * paste this back into src/ without re-measuring.
 *
 * Frame is 0x80 on both sides, which is the structural gauge for this
 * function: the ROM holds SIX callee-saved values (a0, addr, len, and the
 * %hi of D_00718040, D_005523D4, D_00717FC0).  Any shape that gives 0x70 is
 * on the wrong branch regardless of its diff count.
 *
 * Three levers got it from 15 sites to 6, in this order:
 *   1. ONE SPELLING PER SYMBOL.  Referencing D_00717FC0 as both the char[]
 *      and a word view makes gcc materialize two %hi values for one symbol,
 *      which costs the sixth callee-saved register.  This fixed the frame.
 *   2. THE DATA MODEL.  The block is a 0x30 struct: eight header words then
 *      a 0x10 inline buffer at +0x20 (exactly the size it submits).  13 -> 8.
 *   3. PIN THE SUBEXPRESSION.  gcc reassociates
 *      `((addr-1) & ~0xF) - (addr - 0x10)` into `((addr-1) & ~0xF) + 16 - addr`,
 *      which changes both the instruction sequence and the store order.
 *      Routing `addr - 0x10` through its own local stops it.  8 -> 6.
 *
 * REFUTED (do not repeat): removing the `head` local (14); storing a0 after
 * the if/else — a0 overshoots s2 -> s4 (14); giving the copy loop its own
 * `char *dst` (12).
 *
 * RESIDUAL, 6 sites, two classes:
 *   a) the block address sits in $a2 in the ROM and $a3 here — one
 *      permutation, and the ROM derives the LOOP's base through a second
 *      copy (`daddu a3,s2,zero` then `addiu a0,a3,0`) rather than from the
 *      %hi again.  That is the dual-address idiom; the obvious spelling for
 *      it (a `char *dst` local) makes things worse, so it needs a different
 *      route to the same shape.
 *   b) in the else branch the ROM stores 0x18, 0xC, 0x14 — which IS the
 *      source order here — but gcc hoists the 0x14 (head) store to the
 *      front because head is computed first and its store is ready early.
 */

/* §5.10 word views of the device block and the request block.  This
 * function references each of them TWICE across calls, so the ROM keeps
 * only their %hi in a callee-saved register and re-folds %lo per use --
 * which is what an indexed array gives.  Both the field accesses AND the
 * call arguments go through the SAME spelling: mixing the char[] and the
 * word view makes gcc materialize two separate %hi values for one symbol,
 * which is what costs the extra callee-saved register. */
extern int D_00717FC0_w[] __asm__("D_00717FC0");
/* The 0x30-byte request block as this function uses it: a word header and
 * a 0x10-byte inline buffer at +0x20, which is exactly the 0x30 it
 * submits. */
typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    char buf[0x10];
} SplitReq;

extern SplitReq D_00718040_s __asm__("D_00718040");

/* Plain (0x30) sub-template that SPLITS an unaligned transfer: everything
 * up to the next 16-byte boundary is copied into the request block itself
 * (at +0x20) and only the aligned remainder is handed to the peer, which
 * can only DMA whole cache lines.  A transfer of 0x10 bytes or less is all
 * head and no remainder. */
int func_0024FA50(int a0, char *addr, int len) {
    unsigned int i;
    int base;
    int head;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    if (D_00717FC0_w[9] == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    D_00718040_s.f0 = a0;
    if (len < 0x11) {
        D_00718040_s.f14 = len;
        D_00718040_s.fC = 0;
        D_00718040_s.f18 = 0;
    } else {
        base = (int)addr - 0x10;
        head = (((int)addr - 1) & 0xFFFFFFF0) - base;
        D_00718040_s.f18 = (int)(addr + head);
        D_00718040_s.fC = len - head;
        D_00718040_s.f14 = head;
    }
    i = 0;
    if (D_00718040_s.f14 != 0) {
        do {
            D_00718040_s.buf[i] = addr[i];
            i++;
        } while (i < (unsigned int)D_00718040_s.f14);
    }
    func_001007A0(0);
    r = func_00246458(D_00717FC0_w, 6, 1, &D_00718040_s, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 6;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

