
extern int D_00633604;
extern int D_0063360C;
extern int D_0070C9C8[];
void func_001EBAE8(int a0, int a1)
{
  int idx = D_00633604;
  int *p;
  int new_var;
  int *new_var2;
  new_var2 = &a1;
  D_0063360C = *new_var2;
  p = D_0070C9C8 + idx;
  new_var = idx;
  idx = new_var + 1;
  *p = a0;
  D_00633604 = idx;
}
