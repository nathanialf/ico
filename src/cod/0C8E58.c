float func_001C8E58(void *p) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a0)\n\tvmul.xz $vf4, $vf4, $vf4\n\tvaddz.x $vf4, $vf4, $vf4z\n\tqmfc2.ni $v0, $vf4\n\tmtc1 $v0, $f0\n\tnop"
        : : : "memory"
    );
}
