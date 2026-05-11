
extern long long D_0061BD00[];
extern long long D_0061BD10[];
extern int D_00631AE8;
extern int D_006325B4;
extern volatile char func_0017DF38(int x, int y, int *buf, int z, float t);
extern void func_0017E4F0(int x, int y, int *buf, int z);
extern void func_001B6FD8(int x);
extern void func_00182C08(void);
void func_00218DD0(int x_unused)
{
  int buf1[4];
  int buf2[4];
  long long new_var2;
  int *new_var;
  new_var = &buf1[0];
  new_var2 = D_0061BD00[1];
  do
  {
    asm __volatile__("" : : "r"(x_unused));
  }
  while (0);
  *((long long *) new_var) = D_0061BD00[0];
  *((long long *) (&buf1[2])) = new_var2;
  func_0017DF38(D_00631AE8, 0, buf1, 0, 100.0f);
  *((long long *) (&buf2[0])) = D_0061BD10[0];
  *((long long *) (&buf2[2])) = D_0061BD10[1];
  func_0017E4F0(D_00631AE8, 0x13, buf2, 0xB4);
  func_001B6FD8(0x32);
  D_006325B4 = 0;
  func_00182C08();
}
