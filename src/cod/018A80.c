void func_00118A80(void *dst) {
    __asm__ __volatile__(
        ".set noreorder\n\t"
        "vrnext.x $vf1, $R\n\t"
        "vrnext.y $vf1, $R\n\t"
        "vrnext.z $vf1, $R\n\t"
        "vsubw.xyz $vf1, $vf1, $vf0w\n\t"
        "sqc2 $vf1, 0($a0)\n\t"
        ".set reorder"
        : : : "memory"
    );
}
