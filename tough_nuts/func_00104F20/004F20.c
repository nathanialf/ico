
extern int D_00631B40;
extern char D_0065FA40[];
extern int func_00105F20(char *a0, char *a1);
void func_00104F20(void)
{
  int new_var3;
  char *new_var;
  int v0 = D_00631B40 + 1;
  int new_var2;
  v0 = v0 << 6;
  new_var2 = v0;
  ;
  D_00631B40 = v0;
  return func_00105F20(D_0065FA40, &D_0065FA40[new_var3 - 0x40]);
  new_var3 = new_var2;
}
