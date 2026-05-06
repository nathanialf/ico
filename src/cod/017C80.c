void func_00117C80(void) {
    __asm__ __volatile__(
        "vsqi.xyzw $vf4, ($vi15++)\n\tvsqi.xyzw $vf5, ($vi15++)\n\tvsqi.xyzw $vf6, ($vi15++)\n\tvsqi.xyzw $vf7, ($vi15++)\n\tnop"
        : : : "memory"
    );
}
