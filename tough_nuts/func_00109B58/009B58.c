
struct Pack8
{
  long long x;
};
void func_00109B58(int *self)
{
  volatile char *new_var2;
  volatile char *base;
  char *other;
  unsigned char new_var;
  volatile char *new_var6;
  long long new_var4;
  int *new_var5;
  int new_var3;
  new_var4 = (long long) 0x1A8;
  new_var3 = *new_var5;
  do
  {
    new_var = 0x1A0;
    other = (char *) self[0x59];
  }
  while (0);
  base = (volatile char *) self[0x57];
  *((int *) (new_var6 = (new_var2 = base + 0x188))) = new_var3;
  new_var5 = (int *) (base + new_var4);
  *((struct Pack8 *) (base + 0x180)) = *((struct Pack8 *) (base + new_var));
  new_var3 = *new_var5;
  *((struct Pack8 *) (other + 0x610)) = *((struct Pack8 *) (base + new_var));
  *((int *) (other + 0x618)) = new_var3;
}
