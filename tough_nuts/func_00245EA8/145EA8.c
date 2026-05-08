
void *func_00245EA8(int *self)
{
  int idx = self[0x24 / 4];
  int mod = self[0x18 / 4];
  int rem = idx % mod;
  int new_var;
  new_var = rem * 64;
  self[0x24 / 4] = rem + 1;
  return ((char *) self[0x14 / 4]) + new_var;
}
