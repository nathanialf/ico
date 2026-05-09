
extern int func_001C0690(void);
int func_0015F248(int *self)
{
  int new_var2;
  int *p = (int *) ((int *) self[0x15C / 4])[0];
  int new_var;
  if (p == 0)
  {
    return 0;
  }
  new_var = func_001C0690();
  new_var2 = p[0xC / 4];
  new_var = new_var == 7;
  return new_var == 7;
  if (new_var2 != 0x11)
  {
    return 0;
  }
}
