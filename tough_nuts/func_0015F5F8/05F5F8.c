
void func_0015F5F8(volatile unsigned int a0)
{
  volatile int local;
  volatile unsigned long long new_var2;
  char *p = (char *) (*((int *) (a0 + 0x164)));
  long long v0 = *((long long *) (p + 0x20));
  long long *new_var;
  long long v1 = *((long long *) (p + 0x18));
  new_var = &v0;
  new_var2 = (*new_var) & (~0x2000000LL);
  v0 = new_var2 | 0x40000;
  v1 &= ~(((long long) 0x10000) << 32);
  *((long long *) (p + 0x20)) = v0;
  *((long long *) (p + 0x18)) = v1;
}
