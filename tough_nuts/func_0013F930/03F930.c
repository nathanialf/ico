
extern void func_0013F3F0(int, int, int, unsigned char, int, int);
void func_0013F930(int a, int b, int c, int d, int e)
{
  int new_var;
  new_var = a;
  func_0013F3F0(new_var, 0, b, c, new_var = d, e);
  asm __volatile__("" : : : "memory");
}
