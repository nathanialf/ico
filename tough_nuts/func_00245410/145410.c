
extern void func_00100890(int *flag, long long *result);
void func_00245410(void)
{
  int flag;
  int new_var2;
  long long result;
  int new_var;
  volatile int new_var3;
  flag = 0;
  new_var3 = flag;
  func_00100890(&flag, &result);
  *((volatile int *) 0x1000F000) = 4;
  new_var2 = 4;
  new_var = 0x1000F000;
  while ((((*((volatile int *) new_var)) & new_var2) == 0) && (new_var3 == 0))
  {
  }

  *((volatile int *) new_var) = new_var2;
  return result;
}
