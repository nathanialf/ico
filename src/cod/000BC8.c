extern void func_001002D0(void);

void func_00100BC8(void) {
    func_001002D0();
    __asm__ __volatile__("sync");
}
