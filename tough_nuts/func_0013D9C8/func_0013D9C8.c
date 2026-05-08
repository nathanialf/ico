
extern void func_00100410(void);
extern int func_00100470(int a0);
int func_0013D9C8(int a0)
{
  int v0;
  int new_var;
  if (a0 == 0)
  {
 do { } while (0);
    func_00100410();
    v0 = 0;
  }
  else
  {
    new_var = v0;
    v0 = a0;
    v0 = *((int *) (new_var + 0x30));
  }
  return func_00100470(v0);
}
