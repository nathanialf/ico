
extern void func_002641D8(int *buf, int a, int len);
extern void func_002438B8(int *self, int x, int *buf);
void func_0014B708(int *self, int *other)
{
  int buf[16];
  int new_var2;
  int new_var;
  func_002641D8(buf, 0, 0x10);
  new_var2 = 4;
  new_var = other[0x15C / new_var2];
  *((float *) (((char *) buf) + 0x8)) = 1.0f;
  func_002438B8(self, ((int *) new_var)[0xC / 4], buf);
}
