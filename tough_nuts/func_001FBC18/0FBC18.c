
extern int D_004C7710[];
int func_001FBC18(void)
{
  int idx;
  int *p;
  int new_var;
  int end_off;
  int adj_cur;
  idx = D_004C7710[0];
  adj_cur = D_004C7710[4] - 0x80000;
  p = D_004C7710 + idx;
  new_var = 1;
  end_off = p[new_var];
  idx = end_off - adj_cur;
  return idx >> 4;
}
