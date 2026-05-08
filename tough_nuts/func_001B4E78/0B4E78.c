
extern int D_00633028;
extern int D_0063305C;
extern int D_00274EEC[];
extern int D_0063304C;
extern int func_001B7288(int a0);
int func_001B4E78(void)
{
  if (D_00633028 == 0)
  {
    return -1;
  }
  D_00274EEC[0] = 7;
  D_0063305C = 1;
  func_001B7288(0);
  D_0063304C = (float) 0;
  return 0x33;
}
