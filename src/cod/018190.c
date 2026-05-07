void func_00118190(void)
{
    __asm__ __volatile__("vsub.xyzw $vf1, $vf0, $vf0");
    __asm__ __volatile__("vsubw.x $vf2, $vf0, $vf0w");
    __asm__ __volatile__("vaddx.y $vf14, $vf1, $vf5x");
    __asm__ __volatile__("vaddx.z $vf14, $vf1, $vf6x");
    __asm__ __volatile__("vaddy.x $vf15, $vf1, $vf4y");
    __asm__ __volatile__("vaddy.z $vf15, $vf1, $vf6y");
    __asm__ __volatile__("vaddz.x $vf16, $vf1, $vf4z");
    __asm__ __volatile__("vaddz.y $vf16, $vf1, $vf5z");
    __asm__ __volatile__("vmulx.xyz $vf17, $vf7, $vf2x");
    __asm__ __volatile__("vmove.yz $vf4, $vf14");
    __asm__ __volatile__("vmove.xz $vf5, $vf15");
    __asm__ __volatile__("vmove.xy $vf6, $vf16");
    __asm__ __volatile__("vmove.w $vf17, $vf0");
    __asm__ __volatile__("vmulax.xyzw $ACC, $vf4, $vf17x");
    __asm__ __volatile__("vmadday.xyzw $ACC, $vf5, $vf17y");
    __asm__ __volatile__("vmaddaz.xyzw $ACC, $vf6, $vf17z");
    __asm__ __volatile__("vmaddw.xyzw $vf7, $vf0, $vf17w");
    __asm__ __volatile__("nop");
}
