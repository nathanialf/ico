/* func_001332B8 (ios/cdvd.c) — iosCdvdMgrSearchFile-style filename search.
 *
 * STATUS: structurally matched; near-miss on the tail (permuter target).
 *
 * REQUIRED BUILD FIX (without this the link FAILS with
 * "R_MIPS_GPREL16 truncated against .sdata.D_0027E520"):
 *   D_0027E520 is reconstructed as `unsigned char D_0027E520[8]` (8 bytes),
 *   so ee-gcc puts it in .sdata and addresses it gp-relative. But it lives at
 *   0x27E520 (far from _gp 0x6388F0) — in the real game it is the base of the
 *   0x30-stride struct array, so the original uses absolute lui+addiu.
 *   FIX (two coordinated edits):
 *     ios/cdvd.c:      unsigned char D_0027E520[8]
 *                        __attribute__((section(".data.D_0027E520"))) = { 0 };
 *     ico.us.slinky.ld: KEEP(build/ios/cdvd.o(.data.D_0027E520));  (was .sdata.*)
 *   Same bytes, same VMA (0x27E520) -> data SHA preserved; gcc now emits
 *   absolute addressing. See memory: sdata_small_symbol_force_data_section.
 *
 * REMAINING DIFFS (tail only, ~1-2 insns; permuter/postprocess class):
 *   original tail computes the entry address TWICE (rematerializes rather than
 *   keeping it live across the ld-restores):
 *       addiu a0,s3,-6880    ; a0 = D_0027E520
 *       addu  a1,a0,v1       ; a1 = base + idx     (OUT addr, fresh, base+idx)
 *       lw    v0,4(a1)       ; out src = entry.f1
 *       addu  v1,v1,a0       ; v1 = idx + base     (RET addr, compound on idx)
 *       ld    s4,64(sp)
 *       lw    v0,0(v1)       ; return = entry.f0
 *   The clean `table[i].f1 / table[i].f0` form below CSE's the address (one
 *   addu).  Forcing dual via an off-anchor (`int off=i*0x30; ... __asm__("":"+r"(off))`)
 *   works but then the OUT addu operand order (base+idx vs idx+base) and the
 *   ld s4 / lw v0 epilogue schedule each flip depending on which of base/off is
 *   "freshest" — pinning base to $4 + value to $2 + off-anchor got it to exactly
 *   2 diffs (OUT operand order + ld/lw swap) but no C arrangement closed both.
 *   -> hand off to decomp-permuter (rematerialization + commutativity + epilogue
 *      scheduling are its strengths).
 */

extern unsigned char D_0027E520[];
extern unsigned char D_0027E528[];
extern const char D_00556818[];
extern unsigned int D_00631F54;
extern const char D_00631F68[];
extern int func_00265024(int *a0, const char *a1);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);

struct E001332B8
{
    int f0;
    int f1;
    unsigned char pad[0x28];
};

int func_001332B8(int *name, int *out)
{
    int i = 0;
    if ((int) D_00631F54 > 0)
    {
        do
        {
            if (func_00265024(name, (const char *) &D_0027E528[i * 0x30]) == 0)
            {
                goto found;
            }
            i++;
        } while (i < (int) D_00631F54);
    }
    func_001AD768(D_00556818, 0x1E3);
    func_00263FF0(D_00556818, 0x1E3, D_00631F68);
found:
    {
        struct E001332B8 *table = (struct E001332B8 *) D_0027E520;
        out[0] = table[i].f1;
        return table[i].f0;
    }
}
