
typedef void (*func_0013CF80_FnPtr)(int *p, int x);
void func_0013CF80(int *self)
{
  int new_var;
  func_0013CF80_FnPtr fn;
  int *new_var2;
  int *p = (int *) self[0];
  if (fn != 0)
  {
    ;
    new_var2 = p;
    while (new_var2 != 0)
    {
      fn = (func_0013CF80_FnPtr) self[0x8 / 4];
      fn(new_var2, self[0xC / 4]);
      p = (int *) p[0x34 / 4];
    }

  }
  self[0] = 0;
}
