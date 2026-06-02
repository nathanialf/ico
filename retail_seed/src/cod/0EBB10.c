
extern int *func_0013EB50(int x);
extern int *func_0013EBE0(int *p);
int *func_001EBB10(int count)
{
  int *p = func_0013EB50(4);
  int i;
  {
    for (i = 0; i < count; i++)
    {
      if (p == 0)
      {
        return 0;
      }
      p = func_0013EBE0(p);
    }

  }
  return p;
}
