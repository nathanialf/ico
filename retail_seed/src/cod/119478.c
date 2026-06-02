
extern void func_00202208(unsigned int a0);
extern void func_00203AA0(int a0);
extern int func_0017B230(int a0);
extern int *func_0017E188(int a0);
void func_00219478(volatile unsigned int a0)
{
  volatile int local;
  unsigned int unused = a0;
  (void) unused;
  {
    register unsigned int _v asm("$4");
    asm volatile("lw %0, %1" : "=r"(_v) : "m"(a0));
    asm volatile("nop");
    func_00202208(_v);
  }
  func_00203AA0(1);
  if (func_0017B230(0xCD) != 0)
  {
    *((int *) (((char *) func_0017E188(0x3EE)) + 0x16C)) = 0;
  }
}
