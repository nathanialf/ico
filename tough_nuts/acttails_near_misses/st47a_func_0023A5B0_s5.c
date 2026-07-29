/* func_0023A5B0 — st47a, rc 9 / 5 sites (acttails-10 reconstruction).
 * NOTE: conv-13 recorded a 4-site best for this function but saved no source, so
 * this is the first tracked seed; it is one site WORSE than that unrecorded best.
 * Built from the MATCHED siblings func_0023A668 / func_0023A700 / func_0023A548,
 * which establish the template: `volatile int a0` param + a leading `int x = a0;`
 * whose value is DEAD (it is the ROM's `lw v0,0(sp)` at the top — a volatile read
 * gcc may not delete) + `gobj = (ActB4Obj *)actInitialize(a0)`.
 * Structure and instruction COUNT are exact; the whole residual is one event:
 *   ROM  : lui v1(D) / lui a2(fn) / lw a0,0(sp) / addiu v1 / addiu a2 / addiu a1
 *          / sw v1,0xC4(s0) / sw zero,0x16C(v0) / jal / sw a2,4(v1)
 *   ours : sw zero,0x16C(v0) FIRST, then the two %hi/%lo pairs re-lettered.
 * NEW measurement (acttails-10): the store's early retirement is caused by the
 * VOLATILE READ of the param at the BoxBarSoundOn call site — dropping it
 * (`BoxBarSoundOn(x, 0x18D)`) moves both `lui`s ahead of the store, proving the
 * store's sched2 priority comes from that read, not from statement order.
 * Re-measured and still refuted here: all 6 tail-statement permutations WITH an
 * `int q` temp separating the QueenDeadChk call from its store (statement order
 * is inert; A-first and C-first give identical streams); the store spelled as a
 * pointer store and as a `short` store (alias-set change is inert, so the
 * read->store dependence is a volatile FLUSH, not an alias conflict);
 * a non-volatile param.
 * Next lever: keep the `lw a0,0(sp)` in the block but get it AHEAD of the three
 * stores in the RTL — i.e. find the dev construct that reads the volatile param
 * for BoxBarSoundOn's argument before the stores without giving `x` a
 * callee-saved home (ROM's frame saves only s0/ra, so it is NOT a live local).
 */
extern int D_004D3FD0[];
extern void func_00239FE0(volatile int a0);
extern int actInitialize__a5b0(int a0) __asm__("actInitialize");
extern void stage_KillPlayBgAnimation__a5b0(int a0, int a1, int a2) __asm__("stage_KillPlayBgAnimation");

void func_0023A5B0(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize__a5b0(a0);
    _ACTWait(1);
    if (func_0017B230(0x2E) == 0) {
        stage_KillPlayBgAnimation__a5b0(0x94, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x1CC) + 0x16C) = 0;
        D_004D3FD0[1] = (int)func_00239FE0;
        gobj->unkC4 = D_004D3FD0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation__a5b0(0x95, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x1CC) + 0x16C) = 1;
    }
}
