
extern int func_0018CF60(int x);
extern float D_006317F8;
extern float D_006317FC;
extern float D_00631800;
int func_0023C2F0(int *self)
{
  register int *self_save asm("$16");
  float *p;
  float new_var;
  float f1;
  float f2;
  self_save = self;
 do { p = (float *) func_0018CF60((int) self_save); new_var = p[2]; } while (0);
  f1 = new_var;
  f2 = D_006317F8;
  if (f1 < f2)
  {
    f1 = 0.0f;
  }
  else
    if (f1 > D_006317FC)
  {
    f1 = 1.0f;
  }
  else
  {
    f1 = (f1 - f2) / D_00631800;
  }
  *((float *) (((char *) self_save) + 0x18)) = 1.0f - f1;
  return -1;
}
