/* BOUNDARY-GLUED recovery — NOT matchable as configured.
 *
 * Symbol actSt05cEne @0x0021C010 is 0x90 bytes = TWO functions:
 *   funcA @0x21C010 (0x48): the `while(1) _ACTWait(1)` actor coroutine.
 *   funcB @0x21C048 (0x48): own prologue+epilogue (BoxBarSoundOn tail).
 * The per-symbol differ compares only actSt05cEne's 0x48 in our object, so
 * funcA matches byte-perfect (real_count drops to the funcB block) but the
 * 22 residual = funcB shown as a trailing "delete". Two prologues/epilogues
 * => two source functions; no single C function can emit funcB into this
 * symbol. Resolution = CONFIG symbol-split (give 0x21C048 its own symbol)
 * then this file's two functions match per-symbol, OR a whole-ELF ninja
 * harvest (the differ false-negatives on the glued symbol).
 *
 * Same shape & fix applies to the whole rc22 "while(1)_ACTWait + 2nd
 * prologue" family in config/sweep_parked.txt, incl. actSt05cEnemy1/2.
 */
#include "common.h"

extern void _ACTWait(int a0);
extern int D_004CC460[];
extern void *D_004CC4A0[];
extern int D_0062A894;
extern void BoxBarSoundOn(int a0, int a1);
extern void func_00217CF0(void);

void actSt05cEne(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(s + 0xB0) = (int)D_004CC460;
    while (1) {
        _ACTWait(1);
    }
}

/* glued 2nd function @0x0021C048 (no symbol in scaffold) */
void func_0021C048(volatile int a0) {
    int s = *(int *)(a0 + 0x164);
    D_0062A894 = 1;
    *(int *)(s + 0xB4) = (int)D_004CC4A0;
    D_004CC4A0[1] = (void *)func_00217CF0;
    *(int *)(s + 0xB0) = 0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}
