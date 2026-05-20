
void func_001CE778(volatile int *self)
{
  int n;
  int *new_var;
  int i;
  int **new_var2;
  int new_var3;
  new_var2 = &new_var;
  new_var = (int *) self[0x57];
  n = (*new_var2)[0x22];
  i = 0;
  while (i < n)
  {
    int *arr_ptr = (int *) new_var[0x200];
    new_var3 = 4;
    new_var = (int *) ((i * new_var3) + arr_ptr[5]);
    *new_var = 0;
    i++;
  }

}
