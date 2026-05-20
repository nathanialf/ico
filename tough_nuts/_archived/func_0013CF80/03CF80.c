
typedef void (*func_0013CF80_FnPtr)(int *p, int x);
void func_0013CF80(int *self)
{
  int new_var;
  unsigned long new_var3;
  func_0013CF80_FnPtr fn;
  int *new_var2;
  int *p = (int *) self[0];
  if (fn != 0)
  {
    ;
    new_var2 = p;
    while (p != 0)
    {
      fn = (func_0013CF80_FnPtr) self[0x8 / 4];
      new_var3 = 4;
      p = &self[0xC / 4];
      fn(new_var2, *p);
      p = (int *) p[0x34 / new_var3];
    }

  }
  self[0] = 0;
}
