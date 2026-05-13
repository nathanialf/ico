
void func_001CE778(volatile int *self)
{
  int n;
  int *new_var;
  int i;
  new_var = (int *) self[0x57];
  n = new_var[0x22];
  i = 0;
  while (i < n)
  {
    int *arr_ptr = (int *) new_var[0x200];
    *((int *) (arr_ptr[5] + (i * 4))) = 0;
    i++;
  }

}
