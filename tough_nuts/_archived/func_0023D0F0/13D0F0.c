
extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;
extern float D_00631890;
extern float D_00631894;
int func_0023D0F0(int *self)
{
  int **new_var6;
  char *new_var7;
  float f;
  float *new_var8;
  float new_var11;
  char *new_var3;
  int new_var9;
  int *new_var;
  int *p = (int *) self[0x34 / 4];
  char *new_var2;
  int *new_var10;
  float new_var4;
  float *new_var5;
  int v;
  new_var4 = D_00631890;
  new_var4 = D_00631894;
  *((float *) (((char *) p) + 8)) = -397.0f;
  new_var2 += 0x18;
  new_var10 = p;
  new_var6 = &new_var;
  new_var3 = (char *) new_var10;
  new_var2 = (char *) (*new_var6);
  p = *new_var6;
  *((float *) new_var2) = f;
  *((float *) (((char *) p) + 0)) = new_var11;
  new_var = (char *) p;
  new_var11 = new_var4;
  new_var2 = new_var3;
  *(new_var5 = (float *) (new_var2 + 4)) = new_var11;
  f = D_00633B48;
  *(new_var5 = (float *) (new_var2 + 4)) = new_var11;
  new_var7 = new_var;
  if (D_00633B4C != D_00631960)
  {
    D_00633B4C = D_00631960;
    new_var = self;
    v = func_0018CF60((int) new_var);
    f = func_001F5298(v);
    new_var8 = &f;
    f = ((*new_var8) * (new_var4 = 0.5f)) + new_var4;
  }
  else
  {
    D_00633B48 = f;
    if (new_var9 = 1)
    {
      new_var4 = D_00631894;
    }
  }
  *((float *) (new_var7 + 0x18)) = f;
  return new_var9;
}
