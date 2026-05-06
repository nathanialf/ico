void func_00117C40(void) {
    __asm__ __volatile__(
        "vmove.xyzw $vf7, $vf0\n\tvmr32.xyzw $vf6, $vf7\n\tvmr32.xyzw $vf5, $vf6\n\tvmr32.xyzw $vf4, $vf5\n\tviaddi $vi15, $vi0, 0\n\tnop"
        : : : "memory"
    );
}
