
extern int D_007097F0[];
extern char D_00619E40[];
extern void func_001E6D68(int a0);
extern void func_001A6E28(char *a0);
void func_001E8598(int idx)
{
  int new_var;
  int *new_var2;
  if (idx < 0)
  {
    goto end;
  }
  new_var = 0x18;
  {
    int *p = (int *) (((char *) D_007097F0) - (-(idx * new_var)));
    new_var = p[0];
    if (new_var != 0)
    {
      return func_001A6E28(D_00619E40);
      new_var2 = p;
    }
  }
  end:
  ;

  ;
  ;
  ;
  ;
  return func_001E6D68(new_var2[5]);
}
