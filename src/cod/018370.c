void func_00118370(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 $vf1, 0($a1)" : : : "memory");
    __asm__ __volatile__("lqc2 $vf2, 0($a2)" : : : "memory");
    __asm__ __volatile__("vadd.xyzw $vf3, $vf1, $vf2");
    __asm__ __volatile__("sqc2 $vf3, 0($a0)" : : : "memory");
    __asm__ __volatile__("nop");
}
