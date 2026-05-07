float func_00118A68(void)
{
    __asm__ __volatile__(".set noreorder");
    __asm__ __volatile__("vrnext.x $vf1, $R");
    __asm__ __volatile__("vsubw.x $vf1, $vf1, $vf0w");
    __asm__ __volatile__("qmfc2.ni $a3, $vf1");
    __asm__ __volatile__("mtc1 $a3, $f0");
    __asm__ __volatile__(".set reorder");
}
