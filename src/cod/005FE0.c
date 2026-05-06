float func_00105FE0(float x) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf4\n\t"
        ".word 0x4A0403BD\n\t"
        "vwaitq\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
