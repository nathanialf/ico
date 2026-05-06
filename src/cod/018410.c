void func_00118410(void *dst, void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf1, 0($a1)\n\tlqc2 $vf2, 0($a2)\n\tvmulx.x $vf1, $vf1, $vf2x\n\tvmuly.y $vf1, $vf1, $vf2y\n\tvmulz.z $vf1, $vf1, $vf2z\n\tsqc2 $vf1, 0($a0)\n\tnop"
        : : : "memory"
    );
}
