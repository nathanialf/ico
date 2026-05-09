
extern int func_0018CF60(int x);
extern float func_001F5298(int x);
extern float D_00633B48;
extern int D_00633B4C;
extern int D_00631960;
extern float D_00631880;
int func_0023D050(int *self)
{
  float f;
  char *new_var;
  int *p = (int *) self[0x34 / 4];
  int new_var2;
  float new_var3;
  int v;
  new_var = self;
  new_var3 = D_00631880;
  *((float *) (((char *) p) + 8)) = -3300.0f;
  *((float *) (((char *) p) + 0)) = new_var3;
  if (D_00633B4C != D_00631960)
  {
    D_00633B4C = D_00631960;
    v = (new_var2 = func_0018CF60((int) new_var));
    f = func_001F5298(v);
    f = (f * 0.5f) + 0.5f;
  }
  else
  {
    do
    {
      D_00633B48 = f;
    }
    while (0);
  }
  new_var = (char *) self;
  *((float *) (new_var + 0x18)) = f;
  f = D_00633B48;
  if (!self)
  {
  }
  return 1;
}
