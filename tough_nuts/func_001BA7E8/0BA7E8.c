
extern int func_001B8EB0(int *self, int zero);
int func_001BA7E8(int *self)
{
  int *p = (int *) ((int *) self[0x15C / 4])[0x800 / 4];
  int ret = func_001B8EB0(self, 0);
  unsigned short new_var;
  if (ret == (-1))
  {
    p[0x1C8 / 4] = 0;
    new_var = 0x1C0;
    p[new_var / 4] = 0;
    p[0x1C4 / 4] = 0;
    p[new_var / 4] = 0;
    return 0;
  }
  return ret;
}
