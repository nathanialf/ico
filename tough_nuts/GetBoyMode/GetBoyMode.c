/* GetBoyMode — coloring-wall rc6 (from rc59). FULL STRUCTURE RECOVERED.
 * Residual: clamp/mode-register coloring cluster. mode lands in $2 (build)
 * vs $3 (ROM), and the clamp emits movz+$6 (build) vs movn+slti+separate-$4
 * (ROM). COUPLED: movn forms (if(mode>3)mode=3;idx=mode / explicit bool)
 * give movn but pull div-const 3 to $3 (rc12); ternary/movz forms keep
 * div-const 3 in $6 (rc6). Could not get movn AND div-const=$6 via source.
 * Permuter-domain coloring flip.
 * Verified benign (matched sibling proves): subu/addiu sp + j/jr = normalized.
 * Levers that WORKED: int-array alias D_boyg for D_0027EE30 (base+offset not
 * folded); D_00286AA4 array-alias -> explicit lui/lwc1; clamp goto-CFG (bltz
 * out-of-line); reorder f0(off+0) before f4(off+4) to stop +4 symbol fold;
 * ternary clamp fixed div-const cascade. Path: 59->34->25->24->16->14->12->6. */
extern unsigned char D_0027EE30[];
extern int func_002610F0(void);
extern float D_00286AA4[] __asm__("D_00286AA4");
extern int D_0027EC78[];
extern int D_005CA7B0[];
extern int D_boyg[] __asm__("D_0027EE30");

void GetBoyMode(int arg) {
    volatile int home;
    int uninit;
    int r0, mode, idx, k, off, f0, f4, r1;
    home = uninit;
    D_boyg[0x58E8 / 4] = arg;
    D_boyg[0x58F0 / 4] = 0;
    r0 = func_002610F0();
    D_boyg[0x58EC / 4] = r0 % 3;
    mode = (int)D_00286AA4[0] / 3;
    idx = 3;
    if (mode < 0) {
        goto zero;
    }
    idx = mode > 3 ? 3 : mode;
    goto have_idx;
zero:
    idx = 0;
have_idx:
    k = D_0027EC78[idx * 4];
    off = arg * 8 + k * 16;
    f0 = *(int *)((char *)D_005CA7B0 + off);
    f4 = *(int *)((char *)D_005CA7B0 + off + 4);
    r1 = func_002610F0();
    D_boyg[0x58F4 / 4] = f0 + r1 % (f4 - f0);
}
