
extern int D_004C7710[];
void func_001FBBE0(void)
{
  int *p = D_004C7710;
  int idx = p[0] ^ 1;
  int new_var;
  new_var = p[idx + 1];
  p[0] = idx;
  {
    int v1_val = new_var;
    p[7] = 0;
    p[4] = v1_val;
    p[5] = 0;
    p[6] = 0;
  }
}
