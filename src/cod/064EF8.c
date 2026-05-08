
extern void func_001A6E28(char *p);
extern void func_00203AA0(int a0);
extern char D_00558F08[];
void func_00164EF8(volatile unsigned int a0)
{
  volatile int local;
  int *s0;
  s0 = *((int **) (a0 + 0x164));
  func_001A6E28(D_00558F08);
  s0[0x30 / 4] = 0x2;
  func_00203AA0(0);
}
