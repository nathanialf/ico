extern void func_001002E0(void);

void func_00100BE8(void) {
    func_001002E0();
    __asm__ __volatile__("sync");
}
