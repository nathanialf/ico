
extern void func_00140A20(int *a0);
void func_00140B30(int *a0, int idx, short val)
{
  short *arr = a0[0xB];
  int new_var2;
  int *new_var;
  arr[((idx * 2) + (0x40 / 2)) + 1] = val;
  new_var2 = 0x3C / 2;
  arr[(idx * 2) + new_var2] = val;
  new_var = a0;
  return func_00140A20(new_var);
}
