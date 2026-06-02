
extern int func_0017B230(int x);
extern float D_006317E4;
extern float D_006317E8;
int func_0023C0E8(int *self)
{
  int new_var3;
  float new_var2;
  float *p;
  int *new_var4;
  float new_var;
  int new_var5;
  p = (float *) self[0x34 / 4];
  new_var3 = 0;
  new_var = 482.0f;
  p[new_var3] = D_006317E4;
  new_var2 = D_006317E8;
  p[1] = new_var2;
  p[2] = new_var;
  *((float *) (((char *) self) + 0x1C)) = 0.5f;
  new_var5 = func_0017B230(0x5F);
  if (new_var5)
  {
    new_var4 = self;
    *((int *) (((char *) new_var4) + 0x18)) = 0;
  }
  return 1;
}
