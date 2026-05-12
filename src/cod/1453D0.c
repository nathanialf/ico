void func_002453D0(void)
{
  int new_var;
  new_var = 0x1000F000;
  *((volatile int *) new_var) = 4;
  while (((*((volatile int *) new_var)) & 4) == 0)
  {
  }

  *((volatile int *) new_var) = 4;
}
