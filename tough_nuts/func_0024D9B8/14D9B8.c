
extern int D_00552370[];
extern char D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3);
void func_0024D9B8(int a0, int a1, int a2)
{
  register char *t0 asm("$8");
  D_00552370[0] = 0;
  t0 = D_00717BD8;
  asm __volatile__("" : : "r"(t0));
  func_0024DD30(a0, a1, a2, 5);
  asm __volatile__("");
}
