
extern int D_004C75B0[];
extern int D_004C75C0[];
void func_001F55D8(void)
{
  int new_var;
  new_var = D_004C75B0[1];
  D_004C75C0[0] = D_004C75B0[0];
  D_004C75C0[1] = new_var;
  D_004C75C0[2] = D_004C75B0[2];
}
