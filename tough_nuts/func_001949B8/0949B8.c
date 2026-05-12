
int func_001949B8(int a0)
{
  int result;
  int new_var;
  new_var = a0 < 0x2D;
  if (a0 < (-0x87))
  {
    result = 0xB4;
  }
  else
    if (a0 < (-0x2D))
  {
    result = -0x5A;
  }
  else
    if (new_var)
  {
    result = 0;
  }
  else
  {
    new_var = a0 <= 0x86;
    result = 0xB4;
    if (new_var)
    {
      result = 0x5A;
    }
  }
  return result;
}
