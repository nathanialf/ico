
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
  struct Pack8 *new_var7;
  long long new_var4;
  volatile char *new_var8;
  int *new_var5;
  int new_var3;
  new_var5 = self;
  new_var4 = (long long) 0x1A8;
  ;
  new_var8 = (volatile char *) new_var5[0x57];
  do
  {
    new_var = 0x1A0;
    other = (char *) new_var5[0x59];
  }
  while (((long long) 0x1A8) * 0);
  new_var = 0x180;
  base = new_var8;
  *((int *) (new_var6 = (new_var2 = base + 0x188))) = *new_var5;
  new_var5 = (int *) (base + new_var4);
  new_var7 = (struct Pack8 *) (base + new_var);
  *((struct Pack8 *) (base + new_var)) = *new_var7;
  new_var3 = *new_var5;
  *(new_var7 = (struct Pack8 *) (new_var5 = other + 0x610)) = *new_var7;
  *((int *) (other + 0x618)) = new_var3;
}
