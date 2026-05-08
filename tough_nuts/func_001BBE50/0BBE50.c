
extern int D_00632010;
extern char D_006185E8[];
extern int *func_0013A0F8(int a0, int a1, char *a2, int a3);
void func_001BBE50(int a0, int *a1)
{
  int *node = func_0013A0F8(D_00632010, 0xC, D_006185E8, 0x1B);
  int new_var;
  int *child = (int *) a1[0x30 / 4];
  node[1] = 0;
  new_var = 0;
  child[0] = new_var;
  node[new_var] = (int) child;
  D_00632010 += new_var;
  node[2] = 0;
}
