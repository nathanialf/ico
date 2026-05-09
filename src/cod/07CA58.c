
extern int *func_0013EB50(int x);
extern int *func_0013EBE0(int *p);
void func_0017CA58(int x)
{
  unsigned int new_var;
  int *p = func_0013EB50(x);
  while (p != 0)
  {
    new_var = (int) 0xFFFFFFFFU;
    p[0x50 / 4] = new_var;
    p = func_0013EBE0(p);
  }

}
