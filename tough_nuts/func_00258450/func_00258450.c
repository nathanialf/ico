/* func_00258450 — src/cod/vendor_2575C0, VMA 0x00258450, 7 insns / 0x1C bytes.
 * PARKED 2026-08-06 by user decision after ~10 rounds. NOT a floor — see notes.md.
 *
 * Best real-C candidate: ONE divergent site, all 7 ROM instructions present in
 * ROM's exact registers and order. The delay slot carries extendsidi2's
 * self-move (`move $2,$2`, printed as daddu) where ROM has `dsra32 $2,$2,0`.
 *
 * A bit-stream "peek n bits" on the 64-bit accumulator that func_00258418
 * initialises at offset 0 of the object: a0[0..1] is the u64 bit buffer,
 * a0[2]/a0[3] the read pointers, a0[8]/a0[9]/a0[0xA] base/end/size.
 * func_00258508 = peek then func_00258470 = advance. Callers compare the result
 * against MPEG start codes (0x1BA pack start, 0x1BB system header).
 *
 * The `long long` return is MEASURED-SAFE: retyping this function and its
 * callers func_00258508 / func_00258558 leaves both callers BYTE-IDENTICAL.
 * (Earlier rounds asserted the return type was pinned to 32 bits by the
 * callers' bare `daddu`. That was never measured and is false.)
 */
long long func_00258450(unsigned long long *p, int n)
{
    return (int)(*p >> (64 - n));
}
