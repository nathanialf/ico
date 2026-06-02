
extern int D_00631914;
extern int D_00631900;
extern int D_00275254[];
extern int func_00104C80(void);
int func_001024B8(void)
{
  int ret = 0;
  if (D_00631914 != D_00631900)
  {
    D_00631914 = D_00631900;
    func_00104C80();
    ret = 0;
    ret = (D_00275254[0] & 0x800) != ret;
  }
  return ret;
}
