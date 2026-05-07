/*
 * func_001442E0 — DMA-tag-style ID generator.
 *
 * Increments a 28-bit counter (D_0063223C) and returns it OR'd with
 * 0x10000000 in the upper 4 bits. The 0x10000000 bit pattern is the
 * shape of a PS2 EE DMA source-chain tag's `id` field (CNT tag = bits
 * 28..30 of the tag word). Most likely a per-frame / per-transaction
 * DMA tag-id allocator from the rendering layer.
 *
 * Near-miss vs. original asm: ee-gcc 2.96 -O2 -G8 -mips3 emits an
 * identical operation sequence except it allocates the loaded value
 * into $v0 (eliding the return-move), where the original keeps the
 * value in $v1 and emits a `daddu $v0, $v1, $zero` for the return.
 * 9 insns vs. 10. Functionally equivalent; not byte-matching. Tried
 * unsigned-vs-signed type, split temp, register __asm__("$3"), and
 * volatile-load — none budges the regalloc.
 */
extern int D_0063223C;

int func_001442E0(void)
{
    int next = ((D_0063223C + 1) & 0x0FFFFFFF) | 0x10000000;
    D_0063223C = next;
    return next;
}
