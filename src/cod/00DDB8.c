void func_0010DDB8(void *dst, void *q1, void *q2)
{
    __asm__ __volatile__("lqc2 $vf11, 0($a1)" : : : "memory");
    __asm__ __volatile__("lqc2 $vf12, 0($a2)" : : : "memory");
    __asm__ __volatile__("vmul.xyzw $vf13, $vf11, $vf12");
    __asm__ __volatile__("vaddy.x $vf13, $vf13, $vf13y");
    __asm__ __volatile__("vaddz.x $vf13, $vf13, $vf13z");
    __asm__ __volatile__("vsubx.w $vf13, $vf13, $vf13x");
    __asm__ __volatile__("vmulw.xyz $vf14, $vf12, $vf11w");
    __asm__ __volatile__("vmulw.xyz $vf15, $vf11, $vf12w");
    __asm__ __volatile__("vopmula.xyz $ACC, $vf12, $vf11");
    __asm__ __volatile__("vopmsub.xyz $vf16, $vf11, $vf12");
    __asm__ __volatile__("vadd.xyz $vf13, $vf14, $vf15");
    __asm__ __volatile__("vadd.xyz $vf13, $vf13, $vf16");
    __asm__ __volatile__("sqc2 $vf13, 0($a0)" : : : "memory");
    __asm__ __volatile__("nop");
}
