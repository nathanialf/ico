
int *func_0023F778(int *a0, long long a1, long long a2)
{
  long long t = (((long long) a2) << 32) | ((long long) a1);
  a0[0] = (int) a1;
  a0[1] = (int) (t >> 32);
  a0[2] = 0x52;
  a0[3] = 0;
  return a0 + 4;
}
