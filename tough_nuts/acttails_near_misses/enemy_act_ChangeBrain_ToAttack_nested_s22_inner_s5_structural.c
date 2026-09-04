/* conv-17 seed — src/enemy_act.c, nested pair func_00163890 / ChangeBrain_ToAttack.
 * inner sites=5 (STRUCTURE-CORRECT), outer sites=22.  NOT MATCHED.
 *
 * SUPERSEDES the conv-16 inner_s3 seed.  That one scored 3 sites but was
 * STRUCTURALLY WRONG: gcc folded the address test away entirely, so the built
 * body had no branch at all.  This one scores 5 but restores ROM's branch and
 * its per-arm re-derivation of the destination chain.  Structure over count.
 *
 * The construct that keeps the test unfolded (proven in a minimal TU against
 * this compiler -- it emits exactly ROM's `la` / `bne` / value-load):
 *
 *     int *pd = &D_00633D00;      <- pointer local, declared BEFORE the store
 *     D_00633D00 = <value>;       <- store to the OBJECT by name, not via pd
 *     if (pd) { ...->f20C = *pd; } else { ...->f20C = D_00632390; }
 *
 * Storing THROUGH pd instead (`*pd = v;`) lets -fdelete-null-pointer-checks
 * remove the test; naming the value in the true arm instead of `*pd` also
 * folds it.  Both were measured.
 *
 * REMAINING RESIDUAL: the 3-way mode select.  Ours emits `movz`; ROM branches
 * three ways and TAIL-DUPLICATES the continuation into each arm, re-loading
 * the parent's `a0` through the static chain (`lw $6,0($5)`) per arm.
 * Measured on this base and refuted: referencing the parent's volatile `a0`
 * at every use instead of one cached read (6 sites), goto-CFG mode select
 * (5 sites), both together (7 sites).
 */

extern char D_00559168[];
extern int D_00633D00;
extern int D_00274EC0[];
extern int DispCollisionPC(void *a0, int a1, int a2, int a3, unsigned char a4, float a5);
extern void BoxBarSoundOn__cbta(void *a0, int a1) __asm__("BoxBarSoundOn");
extern void debug_assertMessage__cbta(char *m) __asm__("debug_StdPrintfDummy");
extern unsigned int _ACTWait__cbta(int a0) __asm__("_ACTWait");
extern int D_00631AE8__cbta __asm__("D_00631AE8");
extern int D_00632390__cbta __asm__("D_00632390");
extern void func_001624D8(volatile int a0);
extern void GetRootProjectionPosOfGObj(void *out, void *obj);
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
        {
            int *pd = &D_00633D00;
            D_00633D00 = D_00631AE8__cbta;
            if (pd) {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = *pd;
        } else {
            *(int *)(*(int *)(*(int *)(self + 0x164) + 0x670) + 0x20C) = D_00632390__cbta;
            }
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
    GetRootProjectionPosOfGObj(buf10, de8);
    GetRootProjectionPosOfGObj(buf20, (void *)a0);
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
