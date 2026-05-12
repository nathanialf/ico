
int func_002609E8(float f)
{
  union 
  {
    float f;
    int i;
  } u;
  u.f = f;
 do { } while (0);
  return (int) (((unsigned int) (0x7F800000 - (u.i & 0x7FFFFFFF))) >> 31);
}
