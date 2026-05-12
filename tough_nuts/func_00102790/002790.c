
extern void func_0010DDB8(int a0, int a1, char *a2);
extern void func_0010D830(int a0, char *a1);
void func_00102790(int a0, char *a1)
{
  int *new_var2;
  int new_var;
  char *a2 = a1;
  int *p;
  new_var2 = *((int **) (p[0] + 0x15C));
  new_var = 0x10;
  p = (int *) a2;
  if (p[0] == 0)
  {
    return func_0010D830(a0, a2 + 0xD0);
  }
  do
  {
  }
  while (0);
  {
    int *p15c;
    int idx_val = p[1];
    char *p_d0 = a2 + 0xD0;
    int addr = ((int) (((char *) new_var2) + new_var)) + (idx_val * 16);
    do
    {
      (void) 0;
    }
    while (0);
    return func_0010DDB8(a0, addr, p_d0);
  }
}
