
extern int D_00631AE4;
extern int D_006325B4;
extern void func_00203AA0(int x);
extern int func_0017D6D8(int x, int y, float t);
extern void func_001B6FD8(int x);
extern int func_0017B258(int x);
extern void func_001297A0(int x, int y, int z);
extern int func_0012AA80(int x);
void func_00229F30(volatile int x)
{
  while (func_0017D6D8(x, D_00631AE4, 100.0f) == 0)
  {
    func_00203AA0(1);
  }

  func_001B6FD8(0x33);
  D_006325B4 = func_0017B258(0x73);
  func_001297A0(0x140, 1, 0);
  while (func_0012AA80(0x140) == 0)
  {
    func_00203AA0(1);
  }

  func_00203AA0(1);
  func_001B6FD8(0x32);
  D_006325B4 = 0;
}
