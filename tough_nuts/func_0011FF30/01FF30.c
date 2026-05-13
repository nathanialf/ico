
extern void func_001FBA80(void);
extern void func_001FBAA8(int a, char *p, int n);
extern void func_001FB8B8(void);
extern char D_00555830[];
void func_0011FF30(void)
{
  unsigned short new_var3;
  char *new_var;
  char *new_var2;
  func_001FBA80();
  new_var3 = 2;
  new_var = D_00555830;
  do
  {
    new_var2 = new_var;
    func_001FBAA8(new_var3, new_var2, new_var3 = 4);
  }
  while (0);
  func_001FB8B8();
}
