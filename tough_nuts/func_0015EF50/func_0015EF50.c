
extern int func_001E29E8(int a0, int a1, int a2);
int func_0015EF50(int a0)
{
  int *new_var2;
  int *new_var;
  int new_var4;
  int *s0 = *((int **) (((char *) a0) + 0x164));
  unsigned int new_var3;
  unsigned int v0 = func_001E29E8(0, 0, (int) (((char *) s0) + 0x610));
  do
  {
    if (1)
    {
      new_var = (int *) (((char *) s0) + 0x120);
      new_var3 = v0;
      *new_var = new_var3;
    }
    new_var2 = (int *) (v0 + 0xC);
    new_var4 = *new_var2;
    *new_var = new_var3;
    return new_var4 != 0;
  }
  while (0);
}
