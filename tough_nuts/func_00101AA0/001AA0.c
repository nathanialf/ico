
extern int D_006349E0[];
extern void func_00100950(int a0, int *buf);
void func_00101AA0(int a0, int a1, unsigned char a2)
{
  int buf[4];
  buf[0] = a0 & 0xFFFF;
  buf[1] = a1;
  buf[2] = a2;
  buf[3] = ((int) D_006349E0) | 0x20000000;
  func_00100950(1, buf);
}
