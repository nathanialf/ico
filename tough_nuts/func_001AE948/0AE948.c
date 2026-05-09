
typedef void (*func_001AE948_FnPtr)(int *buf, int a2);
extern void func_0017B258(int x);
void func_001AE948(int *self, int a1, int a2)
{
  int buf[2];
  func_001AE948_FnPtr fn;
  int new_var;
  buf[0] = a1;
  buf[1] = 0;
  if (fn != 0)
  {
    do
    {
      fn(buf, a2);
      fn = (func_001AE948_FnPtr) self[0];
      self += 2;
      new_var = self[0];
      fn = (func_001AE948_FnPtr) new_var;
    }
    while (fn != 0);
  }
  func_0017B258(0x169);
}
