
extern int func_0026F3A0(int p, int q);
extern unsigned char D_00717C50[];
int *func_0024E4C8(int a0, int a1)
{
  int new_var;
  int *p = *((int **) ((((char *) D_00717C50) + (a0 * 0x70)) + (a1 * 0x1C)));
  func_0026F3A0((int) p, (int) (((char *) p) + 0x100));
  new_var = (p[0x58 / 4] < p[0xD8 / 4]) << 7;
  return (int *) (((char *) p) + new_var);
}
