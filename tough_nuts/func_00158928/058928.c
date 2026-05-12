
extern void func_001C0708(int);
extern void func_001E9DF0(void);
inline int *inline_fn(char *arg0);
inline int inline_fn2(int *arg0)
{
  return arg0[0x148 / 4];
}

void func_00158928(char *a0)
{
  int *p;
  int x = p[0x30 / 4];
  if (x == 0x31)
  {
    return func_001C0708(inline_fn2(p));
    p = inline_fn(a0);
  }
  if (x == 0x33)
  {
  }
  return func_001E9DF0();
}
