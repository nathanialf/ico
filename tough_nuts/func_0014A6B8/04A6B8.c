
extern int *D_00631AE4;
extern unsigned char D_0055CFD8[];
int func_0014A6B8(int *a0)
{
  int *p = (int *) ((unsigned int) a0[0x59]);
  char *entry;
  int idx;
  int new_var2;
  int new_var;
  long long new_var3;
  if (a0 != D_00631AE4)
  {
    return 0;
  }
  new_var = 0x4C;
  idx = p[0xC];
  new_var3 = 1;
  entry = ((char *) (&D_0055CFD8[0])) + (idx * 0x50);
  new_var2 = ((((unsigned int) (*((int *) (entry + new_var)))) >> 9) & new_var3) == 0;
  if (new_var2)
  {
    return 0;
  }
  return p[0x60];
}
