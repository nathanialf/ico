float func_00118548(void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a0)\n\t"
        "lqc2 $vf2, 0($a1)\n\t"
        "vsub.xyzw $vf3, $vf1, $vf2\n\t"
        "vmul.xy $vf3, $vf3, $vf3\n\t"
        "vaddy.x $vf3, $vf3, $vf3y\n\t"
        ".word 0x4A0303BD\n\t"
        "vwaitq\n\t"
        ".set noreorder\n\t"
        "cfc2.ni $v0, $vi22\n\t"
        "mtc1 $v0, $f0\n\t"
        ".set reorder"
        : : : "memory"
    );
}
