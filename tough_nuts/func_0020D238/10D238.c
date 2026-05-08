
extern int D_00631AE4;
extern int D_00631AE8;
extern void func_0017C9B0(int x);
extern void func_001297A0(int x, int y, int z);
extern void func_00203AA0(int x);
extern int func_0012AA80(int x);
extern void func_0017E330(int x, int y, int z, float a, float b);
void func_0020D238(int unused)
{
  float *new_var2;
  float new_var;
  func_0017C9B0(6);
  func_001297A0(0x2F9, 1, 0);
  while (func_0012AA80(0x2F9) == 0)
  {
    func_00203AA0(1);
  }

  func_00203AA0(1);
  new_var2 = &new_var;
  new_var = 8.0f;
  func_0017E330(6, D_00631AE4, D_00631AE8, 1.0f, *new_var2);
}
