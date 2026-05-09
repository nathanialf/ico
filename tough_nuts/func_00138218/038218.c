
extern void func_0013A5B8(char *p, int *self, int zero, int neg2);
extern char D_00280F88[];
void func_00138218(int *self)
{
  volatile unsigned char new_var;
  new_var = *((long long *) self);
  self[0x4 / 4] = 0xD;
  *((long long *) self) = new_var & (-2LL);
  func_0013A5B8(D_00280F88, self, 0, -2);
}
