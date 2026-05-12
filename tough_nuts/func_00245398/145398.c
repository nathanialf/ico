
void func_00245398(int *queue, long long val)
{
  int *p = (int *) queue[0];
  int lo;
  int hi = (int) (val >> 32);
  p[0] = (int) val;
  p[1] = hi;
  queue[0] = (int) (p + 2);
}
