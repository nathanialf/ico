float func_0010E928(void *a, void *b) {
    __asm__ __volatile__(
        "lqc2 $vf14, 0($a0)\n\tlqc2 $vf15, 0($a1)\n\tvmul.xyzw $vf15, $vf14, $vf15\n\tvaddy.x $vf15, $vf15, $vf15y\n\tvaddz.x $vf15, $vf15, $vf15z\n\tvaddw.x $vf15, $vf15, $vf15w\n\tqmfc2.ni $v0, $vf15\n\tmtc1 $v0, $f0\n\tnop"
        : : : "memory"
    );
}
