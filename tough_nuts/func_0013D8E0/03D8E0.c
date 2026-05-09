
extern int D_006A6F30[];
extern char D_00557958[];
extern void func_001A6E28(char *p);
int func_0013D8E0(unsigned int a0)
{
  int new_var3;
  unsigned int new_var;
  int new_var2;
  new_var = a0;
  new_var3 = D_006A6F30[new_var];
  new_var2 = 0;
  if (new_var < 0x101)
  {
    return new_var3;
  }
  func_001A6E28(D_00557958);
  return new_var2;
}
