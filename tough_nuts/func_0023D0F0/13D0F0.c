
extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;
extern float D_00631890;
extern float D_00631894;
int func_0023D0F0(int *self)
{
  float f;
  int *new_var;
  int *p = (int *) self[0x34 / 4];
  int v;
  *((float *) (((char *) p) + 8)) = -397.0f;
  *((float *) (((char *) p) + 0)) = D_00631890;
  *((float *) (((char *) p) + 4)) = D_00631894;
  if (D_00633B4C != D_00631960)
  {
    D_00633B4C = D_00631960;
    new_var = self;
    v = func_0018CF60((int) new_var);
    f = func_001F5298(v);
    f = (f * 0.5f) + 0.5f;
    D_00633B48 = f;
  }
  else
  {
    f = D_00633B48;
  }
  *((float *) (((char *) new_var) + 0x18)) = f;
  return 1;
}
