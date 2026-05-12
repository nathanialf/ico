
extern char D_0061D560[];
int func_001CEC30(char *self)
{
  char *p = *((char **) ((*((char **) (self + 0x15C))) + 0x800));
  int new_var;
  int idx = *((int *) (p + 8));
  unsigned int val;
  char *new_var3;
  unsigned int *new_var2;
  new_var = 3;
  new_var3 = D_0061D560;
  new_var2 = (unsigned int *) ((new_var3 + (idx * 0x14)) + 0x10);
  return ((*new_var2) >> 2) & new_var;
}
