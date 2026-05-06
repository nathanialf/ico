void func_00118190(void) {
    __asm__ __volatile__(
        "vsub.xyzw $vf1, $vf0, $vf0\n\t"
        "vsubw.x $vf2, $vf0, $vf0w\n\t"
        "vaddx.y $vf14, $vf1, $vf5x\n\t"
        "vaddx.z $vf14, $vf1, $vf6x\n\t"
        "vaddy.x $vf15, $vf1, $vf4y\n\t"
        "vaddy.z $vf15, $vf1, $vf6y\n\t"
        "vaddz.x $vf16, $vf1, $vf4z\n\t"
        "vaddz.y $vf16, $vf1, $vf5z\n\t"
        "vmulx.xyz $vf17, $vf7, $vf2x\n\t"
        "vmove.yz $vf4, $vf14\n\t"
        "vmove.xz $vf5, $vf15\n\t"
        "vmove.xy $vf6, $vf16\n\t"
        "vmove.w $vf17, $vf0\n\t"
        "vmulax.xyzw $ACC, $vf4, $vf17x\n\t"
        "vmadday.xyzw $ACC, $vf5, $vf17y\n\t"
        "vmaddaz.xyzw $ACC, $vf6, $vf17z\n\t"
        "vmaddw.xyzw $vf7, $vf0, $vf17w\n\t"
        "nop"
        : : : "memory"
    );
}
