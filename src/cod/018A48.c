void func_00118A48(float seed) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $a2, $f12\n\t"
        "qmtc2.ni $a2, $vf1\n\t"
        ".set reorder\n\t"
        "vaddw.x $vf2, $vf1, $vf0w\n\t"
        "vadd.x $vf1, $vf1, $vf1\n\t"
        "vrinit $R, $vf2x\n\t"
        "vrxor $R, $vf1x\n\t"
        "nop"
        : : : "memory"
    );
}
