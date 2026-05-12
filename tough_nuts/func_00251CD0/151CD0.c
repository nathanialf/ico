
int func_00251CD0(int *a0, int idx, int new_v0, int store_v1)
{
  int *base = (int *) a0[0x10];
  int new_var2;
  int *v1 = (int *) ((((char *) base) + 0xC) + (idx * 8));
  int new_var;
  int *v0 = (int *) (((char *) base) + (idx * 8));
  int old;
  new_var2 = v1[0];
  new_var = 0x10;
  v0[new_var / 4] = store_v1;
  old = new_var2;
  v1[0] = new_v0;
  return old;
}
