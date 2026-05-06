float func_00106028(void *p) {
    __asm__ __volatile__(
        "lqc2 $vf3, 0($a0)\n\tvmul.xyz $vf3, $vf3, $vf3\n\tvaddy.x $vf3, $vf3, $vf3y\n\tvaddz.x $vf3, $vf3, $vf3z\n\tqmfc2.ni $v0, $vf3\n\tmtc1 $v0, $f0\n\tnop"
        : : : "memory"
    );
}
