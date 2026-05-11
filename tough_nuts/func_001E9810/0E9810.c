
extern int D_00631AE4;
extern void func_001E9588(int *p);
extern void func_00104508(int *buf, int *p);
extern float func_001C8D08(int x, int *buf, float t);
void func_001E9810(int *self)
{
  int buf[16];
  int *q;
  int new_var;
  int *base;
  float result;
  func_001E9588(self);
  new_var = self[0x15C / 4];
  base = (int *) D_00631AE4;
  q = (int *) ((int *) new_var)[0x800 / 4];
  func_00104508(buf, base);
  result = func_001C8D08(q[0], buf, 200.0f);
  if (result > (result * 0.0f))
  {
 do { } while (0);
    *((float *) (((char *) ((int *) base[0x15C / 4])) + 0x618)) = result;
  }
}
