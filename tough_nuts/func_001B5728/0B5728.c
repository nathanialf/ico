
extern int D_00275254[];
extern int D_0063304C;
extern void func_001B7288(int a0);
int func_001B5728(void)
{
  if ((D_00275254[0] & 0x10) == 0)
  {
    func_001B7288(0);
    return -1;
  }
  D_0063304C = 0;
  return 0x1A;
}
