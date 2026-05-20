
extern void func_001BB7E0(void);
extern int func_00165F88(int *self);
extern void func_001CE5F8(int *self);
void func_001CE690(int *self)
{
  int new_var;
  unsigned long new_var2;
  long long flags = *((long long *) (((char *) ((int *) self[0x164 / 4])) + 0x18));
  new_var = 1;
  new_var2 = flags;
  if ((new_var2 >> 33) & new_var)
  {
    func_001BB7E0();
    if (func_00165F88(self) == 0)
    {
      func_001CE5F8(self);
    }
  }
}
