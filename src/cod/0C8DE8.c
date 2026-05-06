float func_001C8DE8(float x) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "mfc1 $t0, $f12\n\t"
        "qmtc2.ni $t0, $vf4\n\t"
        "vrsqrt $Q, $vf0w, $vf4x\n\t"
        "vwaitq\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
