void func_00117CB0(void *vec) {
    __asm__ __volatile__(
        ".set noat\n\t"
        "lqc2 $vf8, 0($a0)\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n\t"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n\t"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n\t"
        "vmaddw.xyzw $vf7, $vf7, $vf8w\n\t"
        "nop"
        : : : "memory"
    );
}
