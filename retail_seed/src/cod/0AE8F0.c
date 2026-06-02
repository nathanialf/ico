
typedef void (*func_001AE8F0_FnPtr)(int *buf, int a2);
void func_001AE8F0(int *self, int a1, int a2)
{
  func_001AE8F0_FnPtr new_var;
  int buf[2];
  int new_var2;
  func_001AE8F0_FnPtr fn;
  buf[0] = a1;
  buf[1] = 0;
  fn = (func_001AE8F0_FnPtr) self[1];
  new_var2 = fn != 0;
  if (new_var2)
  {
    do
    {
      fn(buf, a2);
      self += 2;
      new_var2 = self[1];
      new_var = (func_001AE8F0_FnPtr) new_var2;
      fn = new_var;
    }
    while (new_var2);
  }
}
