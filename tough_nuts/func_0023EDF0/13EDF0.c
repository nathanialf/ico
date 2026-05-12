
extern void func_00241F20(int *a0);
void func_0023EDF0(int *a0, int flag)
{
  int src;
  int new_var;
  new_var = flag;
  if (new_var != 0)
  {
    src = a0[0x2C / 4];
  }
  else
  {
    src = a0[0x28 / 4];
  }
  {
    int cur = a0[0x10 / 4];
    cur = cur & (~0x1FF);
    cur = cur | (src & 0x1FF);
    a0[0x10 / 4] = cur;
  }
  return func_00241F20(a0);
}
