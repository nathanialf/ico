
extern void func_001FBA80(void);
extern void func_001FBAA8(int a0, int a1, int a2);
extern void func_001FB8B8(void);
extern int D_00555830[];
void func_0011FF30(void)
{
  int new_var;
  int new_var2;
  new_var = 2;
  func_001FBA80();
  new_var2 = (int) D_00555830;
 do { func_001FBAA8(new_var, new_var2, 4); } while (0);
  func_001FB8B8();
}
