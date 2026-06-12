/* func_002667C8 — parked near-miss (rc4). Apply replacing the INCLUDE_ASM line.
 * Needs before the func:
 *   extern void func_002698E8(void); extern void func_00269950(void);
 *   extern void func_002699D0(void); extern int func_00269A38(void *a0);
 * (func_00269A38 is defined later in the TU as int(void*); the others are
 *  INCLUDE_ASM siblings.) Full body recovered from the asm.
 *
 * Residual rc4 = the trailing self-store `a0[0x1C] = a0` should fill the `jr`
 * delay slot (ROM) but gcc emits it before `jr` with a nop delay. A reorg/
 * delay-fill near-miss; structure & all other stores are byte-correct. */
void func_002667C8(char *a0, short a1, short a2, int a3) {
    *(int *)(a0 + 0x54) = a3;
    *(short *)(a0 + 0xC) = a1;
    *(short *)(a0 + 0xE) = a2;
    *(void **)(a0 + 0x20) = (void *)func_002698E8;
    *(void **)(a0 + 0x24) = (void *)func_00269950;
    *(void **)(a0 + 0x28) = (void *)func_002699D0;
    *(void **)(a0 + 0x2C) = (void *)func_00269A38;
    *(int *)(a0 + 0x0) = 0;
    *(int *)(a0 + 0x4) = 0;
    *(int *)(a0 + 0x8) = 0;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x18) = 0;
    *(int *)(a0 + 0x1C) = (int)a0;
}
