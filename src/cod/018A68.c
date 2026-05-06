float func_00118A68(void) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "vrnext.x $vf1, $R\n\t"
        "vsubw.x $vf1, $vf1, $vf0w\n\t"
        "qmfc2.ni $a3, $vf1\n\t"
        "mtc1 $a3, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
