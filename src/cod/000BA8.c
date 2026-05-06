extern void func_001002C0(void);

void func_00100BA8(void) {
    func_001002C0();
    __asm__ __volatile__("sync");
}
