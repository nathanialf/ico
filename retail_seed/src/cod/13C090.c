
extern int func_0017B230(int x);
extern float D_006317E0;
typedef struct 
{
  float a0;
  float a4;
  float a8;
} S;
int func_0023C090(int *self)
{
  S *p;
  float new_var;
  p = (S *) self[0x34 / 4];
  p->a0 = D_006317E0;
  p->a8 = 482.0f;
  new_var = 0.5f;
  *((float *) (((char *) self) + 0x1C)) = new_var;
  if (func_0017B230(0x5F))
  {
    *((int *) (((char *) self) + 0x18)) = 0;
  }
  return 1;
}
