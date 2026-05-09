
extern int func_001F40C8(int a0);
extern int D_006124F8[];
int func_0014B000(int a0)
{
  int ret = 0;
  char *new_var;
  new_var = (char *) D_006124F8;
  {
    int idx = func_001F40C8(a0);
    ret = *((int *) ((new_var + (idx * 0x24)) + 0x1C));
  }
  return ret;
}
