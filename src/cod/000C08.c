extern void func_001002F0(void);

void func_00100C08(void) {
    func_001002F0();
    __asm__ __volatile__("sync");
}
