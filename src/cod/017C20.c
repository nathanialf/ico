float func_00117C20(float x) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $a2, $f12\n\t"
        "qmtc2.ni $a2, $vf1\n\t"
        ".word 0x4A0103BD\n\t"
        "vwaitq\n\t"
        "cfc2.ni $a3, $vi22\n\t"
        "mtc1 $a3, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
