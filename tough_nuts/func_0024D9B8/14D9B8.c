
extern int D_00552370[];
extern char D_00717BD8[];
extern void func_0024DD30(int a0, int a1, int a2, int a3);
void func_0024D9B8(int a0, int a1, int a2)
{
  int new_var;
  register char *t0 asm("$8");
 do { } while (0); new_var = 0; do { D_00552370[new_var] = new_var; t0 = D_00717BD8; asm __volatile__("" : : "r"(t0)); } while (new_var);
  func_0024DD30(a0, a1, a2, 5);
  asm __volatile__("");
}
