
extern unsigned int D_00633718;
extern unsigned int D_0063371C;
int func_001F1108(void)
{
  unsigned int a = D_00633718;
  unsigned int b;
  int ret = 1;
  ret = (int) (a + 0x1000);
  if (D_0063371C < D_00633718)
  {
    b += 0x28000;
  }
  if ((b >= D_00633718) && (((int) b) < ret))
  {
    ret = 0;
  }
  return ret;
}
