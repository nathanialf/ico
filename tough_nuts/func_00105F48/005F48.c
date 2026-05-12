
void func_00105F48(int dst, void *src)
{
  register int pinned_a0 asm("$4") = (double) (((unsigned long long) dst) | 0x20000000);
  pinned_a0;
  asm __volatile__("lq $a2, 0($a1)" : : : "memory");
  asm __volatile__("sq $a2, 0($a0)" : : : "memory");
  asm __volatile__("lq $a2, 0x10($a1)" : : : "memory");
  asm __volatile__("sq $a2, 0x10($a0)" : : : "memory");
  asm __volatile__("lq $a2, 0x20($a1)" : : : "memory");
  asm __volatile__("sq $a2, 0x20($a0)" : : : "memory");
  asm __volatile__("lq $a2, 0x30($a1)" : : : "memory");
  asm __volatile__("sq $a2, 0x30($a0)" : : : "memory");
  asm __volatile__("nop");
}
