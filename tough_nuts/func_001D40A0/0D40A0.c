
int func_001D40A0(char *a0)
{
  int *p15c = *((int **) (a0 + 0x15C));
  int v0_p800 = *((int *) (((char *) p15c) + 0x800));
  int v1 = *((int *) v0_p800);
  unsigned long long new_var;
  int result;
  int new_var2;
  new_var2 = *((int *) (a0 + 0x16C));
  if (v1 == 1)
  {
    goto set;
    do
    {
    }
    while (0);
  }
  new_var = 0;
  result = new_var;
  if (new_var2 != new_var)
  {
    goto end;
  }
  set:
  result = 1;

  end:
  return result;

}
