void func_00118AA0(void *dst) {
    __asm__ __volatile__(
        "vrnext.xyz $vf1, $R\n\tvsubw.xyz $vf1, $vf1, $vf0w\n\tsqc2 $vf1, 0($a0)\n\tnop"
        : : : "memory"
    );
}
