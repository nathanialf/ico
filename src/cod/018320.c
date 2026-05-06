float func_00118320(void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a0)\n\t"
        "lqc2 $vf2, 0($a1)\n\t"
        "vaddw.x $vf3, $vf0, $vf0w\n\t"
        "vmul.xyz $vf2, $vf1, $vf2\n\t"
        "vaddax.x $ACC, $vf0, $vf2x\n\t"
        "vmadday.x $ACC, $vf3, $vf2y\n\t"
        "vmaddz.x $vf2, $vf3, $vf2z\n\t"
        "qmfc2.ni $v0, $vf2\n\t"
        "mtc1 $v0, $f0"
        : : : "memory"
    );
}
