
extern int func_00102E08(volatile long a0);
struct u64_packed
{
  long long v;
};
void func_0019F4E8(int *self, struct u64_packed *src)
{
  int new_var;
  struct u64_packed *dst;
  long long new_var2;
  long long new_var3;
  do
  {
  }
  while (0);
  func_00102E08((int) self);
  new_var2 = src->v;
  new_var = 0x15C;
  dst = (struct u64_packed *) self[new_var / 4];
  dst->v = new_var3;
  new_var3 = new_var2;
}
