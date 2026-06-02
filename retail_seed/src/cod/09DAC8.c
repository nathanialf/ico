
void func_0019DAC8(int *a0, int a1)
{
  int size;
  int pos;
  int cum;
  int remaining;
  int step;
  size = a0[1];
  cum = a0[3];
  pos = a0[2];
  remaining = size - cum;
  step = (a1 < remaining) ? (a1) : (remaining);
  pos += step;
  cum = cum + step;
  a0[2] = pos % size;
  a0[3] = cum;
}
