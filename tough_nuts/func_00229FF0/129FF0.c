
extern int D_00631AE8;
extern void func_00203AA0(int x);
extern int func_0017B230(int x);
extern int func_0017D7F0(int x, int y);
extern void func_0017B288(int x);
extern void func_0017B258(int x);
void func_00229FF0(int unused)
{
  volatile int pad;
  if (D_00631AE8 == 0)
  {
    func_00203AA0(0);
  }
  while (1)
  {
    if (func_0017B230(0x9B) != 0)
    {
      if (func_0017D7F0(D_00631AE8, 0x4000000) != 0)
      {
        break;
      }
    }
    func_00203AA0(1);
  }

  func_0017B288(0x166);
  func_0017B258(0x78);
  func_0017B258(0x79);
}
