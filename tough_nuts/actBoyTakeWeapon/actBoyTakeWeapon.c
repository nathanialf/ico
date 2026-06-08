/* fumi/src/boyact.c — actBoyTakeWeapon seed (rc9-11).
   funcCommonJumpDircorrect(a0, *(*(a0+0x164)+0x678)+0x7C0); _ACTWait(0).
   Residual: ROM SPILLS a0 to the stack (frame 0x20: sw a0,0(sp); lw $2,0(sp);
   lw $4,0(sp)) and reloads it twice; gcc -O2 keeps a0 in a reg (frame 0x10).
   &a0 gets folded away. Permuter target (no mode-TI) — find the spill-forcing form. */
void actBoyTakeWeapon(int *a0) {
    funcCommonJumpDircorrect(a0, *(int *)(*(int *)((char *)a0 + 0x164) + 0x678) + 0x7C0);
    _ACTWait(0);
}
