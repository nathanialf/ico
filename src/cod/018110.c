void func_00118110(void) {
    __asm__ __volatile__(
        "vsub.xyzw $vf1, $vf0, $vf0\n\t"
        "vaddx.y $vf14, $vf1, $vf5x\n\t"
        "vaddx.z $vf14, $vf1, $vf6x\n\t"
        "vaddx.w $vf14, $vf1, $vf7x\n\t"
        "vaddy.x $vf15, $vf1, $vf4y\n\t"
        "vaddy.z $vf15, $vf1, $vf6y\n\t"
        "vaddy.w $vf15, $vf1, $vf7y\n\t"
        "vaddz.x $vf16, $vf1, $vf4z\n\t"
        "vaddz.y $vf16, $vf1, $vf5z\n\t"
        "vaddz.w $vf16, $vf1, $vf7z\n\t"
        "vaddw.x $vf17, $vf1, $vf4w\n\t"
        "vaddw.y $vf17, $vf1, $vf5w\n\t"
        "vaddw.z $vf17, $vf1, $vf6w\n\t"
        "vmove.yzw $vf4, $vf14\n\t"
        "vmove.xzw $vf5, $vf15\n\t"
        "vmove.xyw $vf6, $vf16\n\t"
        "vmove.xyz $vf7, $vf17\n\t"
        "nop"
        : : : "memory"
    );
}
