float func_00243950(void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf4, 0($a0)\n\tlqc2 $vf5, 0($a1)\n\tvmul.xyz $vf5, $vf4, $vf5\n\tvaddy.x $vf5, $vf5, $vf5y\n\tvaddz.x $vf5, $vf5, $vf5z\n\tqmfc2.ni $v0, $vf5\n\tmtc1 $v0, $f0\n\tnop"
        : : : "memory"
    );
}
