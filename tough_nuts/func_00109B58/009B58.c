
struct Pack8
{
  long long x;
};
void func_00109B58(int *self)
{
  volatile char *new_var2;
  volatile char *base = (volatile char *) self[0x57];
  char *other;
  unsigned char new_var;
  int new_var3;
  do
  {
    new_var = 0x1A0;
    other = (char *) self[0x59];
  }
  while (0);
  *((int *) (new_var2 = base + 0x188)) = new_var3;
  *((struct Pack8 *) (base + 0x180)) = *((struct Pack8 *) (base + new_var));
  new_var3 = *((int *) (base + ((long long) 0x1A8)));
  *((struct Pack8 *) (other + 0x610)) = *((struct Pack8 *) (base + new_var));
  *((int *) (other + 0x618)) = new_var3;
}
