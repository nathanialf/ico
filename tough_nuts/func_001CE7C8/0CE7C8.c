
void func_001CE7C8(volatile int *self)
{
  int n;
  volatile int pad;
  int i;
  n = ((int *) self[0x57])[0x22];
  i = 0;
  while (i < n)
  {
    int *arr_ptr = (int *) ((int *) self[0x57])[0x200];
    *((int *) (arr_ptr[5] + (i * 4))) = 1;
    i++;
  }

}
