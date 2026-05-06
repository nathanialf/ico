
extern void func_00105F00(void *dst, void *src);
void func_00106AA8(void *dst, char *self)
{
  char *new_var2;
  char *new_var;
  long new_var3;
  char *new_var4;
  new_var2 = (new_var4 = (*((char **) new_var)) + 0x590);
  new_var3 = 0x15C;
  new_var = dst;
  new_var2 = *((char **) new_var);
  if (!dst)
  {
    func_00105F00(new_var, new_var2 + 0x590);
  }
  new_var = self + new_var3;
}
