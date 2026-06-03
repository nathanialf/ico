/* rc2 best seed (resume baseline). Only diff vs ROM: prologue sw a0 / sd ra
 * order — the volatile store floats ahead of the callee-save. */
extern void ACTLookTargetSystem_Exec(void);

void func_00173D48(void *a0) {
    void *volatile q = a0;
    ACTLookTargetSystem_Exec();
    __asm__ __volatile__("");
}
