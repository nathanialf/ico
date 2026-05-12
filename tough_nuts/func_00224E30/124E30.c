
extern void func_00202208(unsigned int a0);
extern void func_00203AA0(int a0);
extern int func_0017B230(int a0);
extern int *func_0017E188(int a0);
void func_00224E30(volatile unsigned int a0)
{
  volatile int local;
  unsigned int copy;
  func_00202208(a0);
  func_00203AA0(1);
  if (func_0017B230(0xCE) != 0)
  {
    *((int *) (((char *) func_0017E188(0x4FC)) + 0x16C)) = 0;
  }
}
