void func_00118160(void) {
    __asm__ __volatile__(
        "vsub.xyzw $vf1, $vf0, $vf0\n\t"
        "vaddx.y $vf14, $vf1, $vf5x\n\t"
        "vaddx.z $vf14, $vf1, $vf6x\n\t"
        "vaddy.x $vf15, $vf1, $vf4y\n\t"
        "vaddy.z $vf15, $vf1, $vf6y\n\t"
        "vaddz.x $vf16, $vf1, $vf4z\n\t"
        "vaddz.y $vf16, $vf1, $vf5z\n\t"
        "vmove.yz $vf4, $vf14\n\t"
        "vmove.xz $vf5, $vf15\n\t"
        "vmove.xy $vf6, $vf16\n\t"
        "nop"
        : : : "memory"
    );
}
