
extern void func_001AE460(int *a0);
void func_001E9950(int *self)
{
  int new_var;
  int *p = (int *) ((int *) self[0x15C / 4])[0x800 / 4];
  int v = p[0x30 / 4];
  new_var = v;
  new_var = new_var + 1;
  if (v < 0x1F)
  {
    p[0x30 / 4] = new_var;
  }
  else
  {
    p[0x30 / 4] = 0;
    func_001AE460(self);
  }
}
