
int *func_0013C920(int **head_ptr, int key)
{
  unsigned short new_var2;
  unsigned char new_var;
  int *p;
  int **new_var5;
  int *new_var3;
  unsigned char new_var4;
  new_var5 = head_ptr;
  new_var = (new_var2 = 0);
  if (new_var5 == new_var)
  {
    new_var2 = new_var;
    return new_var2;
  }
  p = *new_var5;
  if (p == new_var2)
  {
 do { new_var4 = new_var2; return new_var4; } while (0);
  }
  do
  {
    if (key == p[0xA])
    {
      new_var3 = p;
      do
      {
        return new_var3;
      }
      while (0);
    }
    p = (int *) p[0xD];
  }
  while (p != new_var4);
  return new_var4;
}
