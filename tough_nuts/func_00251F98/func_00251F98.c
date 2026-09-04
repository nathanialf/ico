void _decode_motion_vector(int *a0, int a1, int a2, int a3, int a4)
{
  int limit;
  int base;
  int delta;
  int *ptr = a0;
  limit = 16 << a1;
  base = *ptr;
  if (a4)
  {
    base = base >> 1;
  }
  if (a2 > 0)
  {
    base = (((a2 - 1) << a1) + (base + 1)) + a3;
    if (base >= limit)
    {
      base = base - (limit << 1);
    }
  }
  else
    if (a2 < 0)
  {
    base = base - 1;
    delta = ((~a2) << a1) + a3;
    base = base - delta;
    if (base < (-limit))
    {
      base = base + (limit << 1);
    }
  }
  *ptr = (a4) ? (base << 1) : (base);
}
