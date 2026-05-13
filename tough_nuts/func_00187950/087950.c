
int func_00187950(int *a0, int a1)
{
  int sum = 0;
  int i;
  i = 0;
  if (a1 > i)
  {
    int hi = a0[0xF];
    int lo = a0[0xE];
    i = i;
    do
    {
      sum = sum + (hi - lo);
      i++;
    }
    while (i < a1);
  }
  return sum;
}
