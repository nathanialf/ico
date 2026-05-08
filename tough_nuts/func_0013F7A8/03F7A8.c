
extern void func_0013F3F0(int, int, volatile unsigned long, unsigned char, int, int);
void func_0013F7A8(int a, int b, int c, int d, int e)
{
  func_0013F3F0(a, a, b, c, d, e);
  asm __volatile__("" : : : "memory");
}
