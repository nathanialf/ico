
extern void func_00105F00(void *dst, void *src);
void func_00106A98(void *dst, char *self)
{
  void *new_var2;
  char *new_var;
  void **new_var3;
  new_var = self;
  new_var3 = &new_var2;
  new_var2 = dst;
  goto dummy_label_831807;
  func_00105F00(*new_var3, (*((char **) (new_var + 0x15C))) + 0x5C0);
 dummy_label_831807: ;
}
