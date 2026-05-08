
void func_001F4098(int *self)
{
  int *p = (int *) self[0x15C / 4];
  int *q = (int *) p[0x800 / 4];
  int v = q[0x8 / 4];
  int ret = -1;
  if (v != 0)
  {
    int *r = (int *) ((int *) v)[0x15C / 4];
    r[0x630 / 4] = 0;
  }
  q[0x4 / 4] = 0;
  q[0xC / 4] = ret;
 do { q[0x8 / 4] = 0; } while (0);
}
