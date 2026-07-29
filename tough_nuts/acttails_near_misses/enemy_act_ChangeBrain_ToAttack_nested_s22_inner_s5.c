/* conv-14 draft — src/enemy_act.c
 *
 * func_00163890 written as a GNU C NESTED FUNCTION of its caller
 * ChangeBrain_ToAttack.  This PROVES the arg-in-$2 class: MIPS
 * STATIC_CHAIN_REGNUM is $2 (ee-gcc mips.h:1793), so a nested function
 * receives its parent's frame in $2 and the caller materialises it with
 * `move $2,$sp` in the jal delay slot — exactly what ROM has.  The
 * `__asm__("func_00163890")` declaration forces the emitted symbol name
 * (gcc otherwise mangles nested functions to `inner.N`), and gcc emits the
 * nested function BEFORE the parent, matching the ROM layout
 * (func_00163890 @0x163890 < ChangeBrain_ToAttack @0x163950).
 *
 * STATE: inner sites=5, outer sites=22.  NOT MATCHED — do not commit as-is.
 * Both must reach sites 0 together (they are one C function now).
 * See decomp/convpass_ledger_3.md, conv-14.
 *
 * Paste in place of BOTH INCLUDE_ASM lines (func_00163890 first, then
 * ChangeBrain_ToAttack).  All the __asm__-aliased externs are needed because
 * this sits at ~line 264, before enemy_act.c's own declarations of
 * DispCollisionPC (672), D_00274EC0 (722), BoxBarSoundOn, debug_assertMessage
 * and _ACTWait.
 */

extern char D_00559168[];
extern int D_00633D00[];
extern int D_00274EC0[];
extern int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);
extern void BoxBarSoundOn__cbta(void *a0, int a1) __asm__("BoxBarSoundOn");
extern void debug_assertMessage__cbta(char *m) __asm__("debug_assertMessage");
extern unsigned int _ACTWait__cbta(int a0) __asm__("_ACTWait");
extern int D_00631AE8__cbta __asm__("D_00631AE8");
extern int D_00632390__cbta __asm__("D_00632390");
extern void func_001624D8(volatile int a0);
extern void GetHeightOfWallFromGObj(void *out, void *obj);
extern void PairSetGeometry__cbta(void *a0) __asm__("PairSetGeometry");
extern void func_001919A0__cbta(void *a0, int a1) __asm__("func_001919A0");

void ChangeBrain_ToAttack(volatile int a0) {
    float buf10[4];
    float buf20[4];
    int *p;
    int i;
    int ok;
    void *de8 = (void *)D_00631AE8__cbta;

    void inner(void) __asm__("func_00163890");
    void inner(void) {
        int self = a0;
        int mode = *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x1E0);
        int v;
        if (mode == 0) {
            v = 8;
        } else if (mode == 2) {
            v = 0xB;
        } else {
            v = 0xA;
        }
        *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x200) = v;
        D_00633D00[0] = D_00631AE8__cbta;
        if (D_00633D00 != 0) {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = D_00631AE8__cbta;
        } else {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = D_00632390__cbta;
        }
    }

    p = *(int **)(a0 + 0x164);
    p[0x33C / 4] = 0;
    p[0x110 / 4] = 0;
    p[0x114 / 4] = 0;
    p[0x118 / 4] = 0;
    for (i = 0; i < (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]; i++) {
        PairSetGeometry__cbta((void *)a0);
        _ACTWait__cbta(1);
    }
    ok = (unsigned char)DispCollisionPC((void *)a0, (int)de8,
                                        (int)((char *)p + 0x110),
                                        (int)func_001624D8, 0, 130.0f);
    GetHeightOfWallFromGObj(buf10, de8);
    GetHeightOfWallFromGObj(buf20, (void *)a0);
    {
        float d = buf10[1] - buf20[1];
        if (d < 0.0f) {
            d = -d;
        }
        if (50.0f < d) {
            ok = 0;
        }
    }
    if (ok == 0) {
        p[0x118 / 4] = 0;
        p[0x33C / 4] = 0;
        p[0x110 / 4] = 0;
        p[0x114 / 4] = 0;
        _ACTWait__cbta(0x1E);
        func_001919A0__cbta((void *)a0, 5);
        BoxBarSoundOn__cbta((void *)a0, 0xF0);
        _ACTWait__cbta(0);
    }
    for (;;) {
        debug_assertMessage__cbta(D_00559168);
        inner();
        _ACTWait__cbta(1);
    }
}
