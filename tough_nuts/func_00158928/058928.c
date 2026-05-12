
extern void func_001C0708(int);
extern void func_001E9DF0(void);
inline int *inline_fn(char *arg0)
{
  return *((int **) (arg0 + 0x164));
}

void func_00158928(char *a0)
{
  int *p = inline_fn(a0);
  int x = p[0x30 / 4];
  if (x == 0x31)
  {
    return func_001C0708(p[0x148 / 4]);
  }
  if (x == 0x33)
  {
  }
  return func_001E9DF0();
}
