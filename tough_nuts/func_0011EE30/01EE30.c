
extern void func_00118C68(int a0, int a1, int a2, int a3, int t0);
void func_0011EE30(char *self, int a1, int a2)
{
  long long val = *((long long *) (self + 0x60));
  int low = *((int *) (self + 0x60));
  int new_var;
  int bits = ((int) ((val << 27) >> 32)) & 3;
  return func_00118C68(new_var = low & 1, bits, low, a1, a2);
  low = 0;
}
