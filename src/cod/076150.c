
extern void func_001A6E28(char *p);
extern void func_00203AA0(int a0);
extern char D_00559AE8[];
void func_00176150(volatile unsigned int a0)
{
  volatile int local;
  int *new_var;
  int *s0;
  new_var = *((int **) (a0 + 0x164));
  func_001A6E28(D_00559AE8);
  s0 = new_var;
  s0[0x30 / 4] = 0x4;
  func_00203AA0(0);
}
