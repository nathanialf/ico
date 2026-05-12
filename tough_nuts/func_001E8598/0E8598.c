
extern int D_007097F0[];
extern char D_00619E40[];
extern void func_001E6D68(int a0);
extern void func_001A6E28(char *a0);
void func_001E8598(int idx)
{
  if (idx < 0)
  {
    goto end;
  }
  {
    int *p = (int *) (((char *) D_007097F0) - (-(idx * 0x18)));
    if (p[0] != 0)
    {
      return func_001A6E28(D_00619E40);
      return func_001E6D68(p[5]);
    }
  }
  end:
  ;

  ;
  ;
}
