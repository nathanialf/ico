
extern void func_00105F00(void *dst, void *src);
void func_00106AA8(void *dst, char *self)
{
  char *new_var2;
  char *new_var;
  new_var2 = (*((char **) new_var)) + 0x590;
  new_var = dst;
  func_00105F00(new_var, (*((char **) new_var)) + 0x590);
  new_var = self + 0x15C;
}
