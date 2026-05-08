
int func_0010A0C8(float *dst, char *src)
{
  int i;
  unsigned char new_var;
  int n;
  int idx;
  int offset;
  float *p;
  if (src[1] != 0)
  {
    return 0;
  }
  new_var = (unsigned char) src[2];
  n = (unsigned char) src[3];
  if (n == 0)
  {
    return 0;
  }
  idx = new_var;
  offset = (idx * 8) + 0x10;
  p = (float *) (src + offset);
  for (i = 0; i < n; i++)
  {
    *(dst++) = *(p++);
  }

  return 1;
}
