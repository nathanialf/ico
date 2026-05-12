
extern int *D_00553244;
int func_00264D60(void)
{
  int *p = D_00553244;
  int seed = p[0x58 / 4];
  ;
  p[0x58 / 4] = (seed * 0x41C64E6D) + 0x3039;
  return ((seed * 0x41C64E6D) + 0x3039) & 0x7FFFFFFF;
}
