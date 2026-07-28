/* func_00139FE8 (ios/memory.c) — iosMemInitPartition: align args, size-check,
 * build a "<PARTITION>" header + nested "<FREE AREA>" partition, printf.
 *
 * STATUS: structurally + register-allocation matched. 12-diff near-miss after
 * 20 genuine distinct iterations (the strict pre-park budget). Residue is pure
 * ee-gcc INSTRUCTION SCHEDULING -> decomp-permuter target.
 *
 * WHAT IS MATCHED (and how):
 *  - `register int count __asm__("$5")`: count is computed after the size-check
 *    where the a1 param dies; the original reuses $5/a1 for it. Pinning fixed
 *    the entire regalloc cascade (21 -> 5 diffs). [memory: pin computed var to
 *    a dead arg reg]
 *  - args (m->f38, m->f3C-1) computed into locals before the trailing zero
 *    stores; (unsigned)>>4 for count (srl); packed 16-byte struct copy for the
 *    unaligned name tags (ldl/ldr/sdl/sdr).
 *  - `__asm__ __volatile__("":::"memory")` after the f44 store pins it first
 *    in the header-store run (14 -> 12).
 *
 * REMAINING 12 DIFFS (instruction scheduling — every C change just trades one
 * for another; confirmed over 20 iters, oscillates 12<->14<->19<->30<->45):
 *   1. the count `subu` (hi - f) is interleaved into the F70 %hi/%lo lui+addiu
 *      in the original; ours floats after the name copy. (MATERIALIZE fixes it
 *      but costs a lui/srl swap.)
 *   2. the two `hi` stores f30(0x30)/f3C(0x3C) get swapped by the scheduler
 *      (and a 2nd memory barrier to pin them disrupts the F90 lui interleave).
 *   3. tail: the m->f38/m->f3C reloads + the f->f2C=0 (jal-delay) get reordered.
 *
 * Run: tools/permute_run.sh func_00139FE8 (needs ios/ asm-path support — the
 * harness currently resolves asm/matchings/cod/<off>/; point it at
 * asm/nonmatchings/ios/memory/func_00139FE8.s).
 */

extern unsigned char D_00556F50[];
extern unsigned char D_00556F70[];
extern unsigned char D_00556F80[];
extern unsigned char D_00556F90[];
extern void func_001A6E28(const char *fmt, ...);

struct Part00139FE8
{
    unsigned char name[0x10];
    unsigned char gap[0x10];
    int f20, f24, f28, f2C;
    int f30, f34, f38, f3C;
    int f40, f44;
    int pad[2];
};

struct P16_00139FE8
{
    long long a;
    long long b;
} __attribute__((packed));

int func_00139FE8(int a0, int a1)
{
    struct Part00139FE8 *m = (struct Part00139FE8 *) ((a0 + 0xF) & 0xFFFFFFF0u);
    int hi = (a1 + 1) & 0xFFFFFFF0u;
    struct Part00139FE8 *f;
    register int count __asm__("$5");

    if ((unsigned int) (hi - (int) m) < 0xA0)
    {
        func_001A6E28(D_00556F50);
        return 0;
    }
    f = m + 1;
    {
        int diff = hi - (int) f;
        *(struct P16_00139FE8 *) m->name = *(struct P16_00139FE8 *) D_00556F70;
        count = (int) ((unsigned int) diff >> 4);
    }
    m->f44 = (int) f;
    __asm__ __volatile__("" : : : "memory");
    m->f34 = count;
    m->f40 = count;
    m->f30 = hi;
    m->f38 = (int) f;
    m->f3C = hi;
    m->f2C = 0;
    m->f20 = 0;
    m->f24 = 0;
    m->f28 = 0;
    *(struct P16_00139FE8 *) f->name = *(struct P16_00139FE8 *) D_00556F80;
    f->f20 = 0;
    {
        int arg1, arg2;
        f->f34 = m->f34 - 4;
        arg2 = m->f3C - 1;
        arg1 = m->f38;
        f->f24 = 0;
        f->f28 = 0;
        f->f2C = 0;
        func_001A6E28(D_00556F90, arg1, arg2);
    }
    return (int) m;
}
