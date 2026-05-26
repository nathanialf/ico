/* func_0013BA68 (ios/pad.c) — sibling of the matched func_0013B610. Iterates
 * all 16 pad slots (D_006A6DB0, 0x18 stride); per active slot calls
 * func_0013C920(slot[1], *slot); on nonzero ret clamps *(ret+2) = min(scaled,
 * 0xFF); on zero ret bumps the slot counter + maybe clears it + calls the
 * 5-arg func_0013C110 (same dual-pin mask as B610).
 *
 * STATUS: 25 diffs (from 56). Structure + FRAME correct. MATCHED parts:
 *   slot loop, do-while w/ reload-v-at-bottom, func_0013C920/func_0013C110
 *   arities, dual-pin mask ($20=0xFFFFFFFF + wi pinned $6, reuse struct
 *   U32_0013B610), branch-direction (clamp out-of-line via goto), divu-by-ff
 *   (ff=register so gcc emits the dead div-by-zero break), void return.
 * REMAINING (hand-grind codegen residuals, permuter OUT — packed lwl/lwr):
 *   - clamp emits movz (inverse form) vs original movn; non-inverse form
 *     gives movn but materializes a 2nd 0xFF in s5 (sltu 255 vs sltiu 256).
 *   - cnt compare: original sll/sra (short sign-ext) vs my andi (zero-ext).
 *   - v reload reg (v0 vs v1) + a2=ff (daddu a2,s1) scheduling into bne delay.
 * Recipe cousins: [[dual_pin_read_and_mask_const]],
 * [[body_out_of_line_branch_direction]], [[store_then_clamp]].
 */
extern unsigned char *func_0013C920(int a0, int a1);

void func_0013BA68(void)
{
    int *slot = D_006A6DB0;
    register int ff REG("$17") = 0xFF;
    register unsigned long long mask REG("$20") = 0xFFFFFFFFULL;
    int i = 0xF;
    int v = slot[0];
    do
    {
        i--;
        if (v != 0)
        {
            unsigned char *ret = func_0013C920(slot[0x4 / 4], v);
            if (ret != 0)
            {
                goto clamp_BA68;
            }
            {
                unsigned short cnt = *(unsigned short *) ((char *) slot + 0x12) + 1;
                short lim = *(short *) ((char *) slot + 0x10);
                *(unsigned short *) ((char *) slot + 0x12) = cnt;
                if (lim != 0 && (short) cnt >= lim)
                {
                    slot[0] = 0;
                    goto next_BA68;
                }
                {
                    register int wi REG("$6") =
                        ((struct U32_0013B610 *) ((char *) slot + 0xC))->v;
                    func_0013C110(slot[0x4 / 4], slot[0x8 / 4], wi & mask, slot[0], 0);
                }
                goto next_BA68;
            }
        clamp_BA68:
            {
                unsigned int prod = *((unsigned char *) slot + 0x14) * ret[2];
                int result;
                prod = prod / ff;
                result = prod;
                if (prod > 0xFF)
                {
                    result = ff;
                }
                ret[2] = result;
            }
        }
    next_BA68:
        slot = (int *) ((char *) slot + 0x18);
        v = slot[0];
    } while (i != -1);
}
