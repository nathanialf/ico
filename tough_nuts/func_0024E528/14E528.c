
extern char D_00717C50[];
extern int *func_0024E4C8(int);
int func_0024E528(int a0, int a1)
{
  char *entry = &D_00717C50[(a0 * 0x70) + (a1 * 0x1C)];
  if ((*((int *) ((&D_00717C50[(a0 * 0x70) + (a1 * 0x1C)]) + 0x10))) == 0)
  {
    return 0;
  }
  return *((int *) (((char *) func_0024E4C8(a0)) + 0x58));
}
