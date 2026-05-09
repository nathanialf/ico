
extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;
int func_0023D170(int *self)
{
  char *new_var;
  float f;
  new_var = (char *) self;
  f = D_00633B48;
  if (D_00633B4C != D_00631960)
  {
    D_00633B4C = D_00631960;
    f = func_001F5298(func_0018CF60((int) self));
    f = (f * 0.5f) + 0.5f;
  }
  else
  {
    D_00633B48 = f;
  }
  *((float *) (new_var + 0x18)) = f;
  return -1;
}
