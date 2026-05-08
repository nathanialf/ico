
extern int D_00552370[];
extern int D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3, int *t0);
void func_0024DA80(void)
{
  int *new_var;
  new_var = D_00717BD8;
  D_00552370[0] = 0;
 do { func_0024DD30(0, 0, 0, 3, new_var); } while (0);
  asm __volatile__("" : : : "memory");
}
