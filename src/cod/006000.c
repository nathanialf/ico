float func_00106000(void *p) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a0)\n\t"
        "vmul.xyz $vf4, $vf4, $vf4\n\t"
        "vaddy.x $vf4, $vf4, $vf4y\n\t"
        "vaddz.x $vf4, $vf4, $vf4z\n\t"
        ".word 0x4A0403BD\n\t"
        "vwaitq\n\t"
        ".set noreorder\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
