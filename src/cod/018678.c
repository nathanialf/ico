void func_00118678(void *dst) {
    __asm__ __volatile__(
        "vmove.xyzw $vf17, $vf0\n\tvmr32.xyzw $vf16, $vf17\n\tvmr32.xyzw $vf15, $vf16\n\tvmr32.xyzw $vf14, $vf15\n\tsqc2 $vf14, 0($a0)\n\tsqc2 $vf15, 16($a0)\n\tsqc2 $vf16, 32($a0)\n\tsqc2 $vf17, 48($a0)\n\tnop"
        : : : "memory"
    );
}
