
void func_001CE7C8(volatile int *self)
{
  int n;
  volatile int pad;
  int i;
  int *new_var2;
  int new_var;
  n = new_var;
  new_var = ((int *) self[0x57])[0x22];
  i = 0;
 do { } while (0);
  new_var2 = (int *) self[0x57];
  while (i < n)
  {
    int *arr_ptr = (int *) new_var2[0x200];
    *((int *) (((0, arr_ptr))[5] + (2 * (i * 2)))) = 1;
    i++;
  }

}
