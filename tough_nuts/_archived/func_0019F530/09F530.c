
extern int func_00103018(int a0);
struct u64_packed_19F530
{
  long long v;
};
extern struct u64_packed_19F530 D_006323C0;
void func_0019F530(int *self)
{
  struct u64_packed_19F530 *dst;
  int new_var;
  new_var = (int) self;
  func_00103018(new_var);
  dst = (struct u64_packed_19F530 *) self[0x15C / 4];
  dst->v = new_var;
  new_var = (short) D_006323C0.v;
}
