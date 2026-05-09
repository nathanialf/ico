
extern void func_00245318(int *self, int a1, int a2);
void func_002451D0(int *self, int flag)
{
  int *p;
  int tag;
  int *new_var;
  func_00245318(self, 2, 3);
  new_var = (int *) self[0];
  p = (int *) self[0];
  self[0] = (int) (((char *) ((int *) self[0])) + 4);
  self[3] = (int) ((int *) self[0]);
  tag = (flag) ? (0xD0000000) : (0x50000000);
  *new_var = tag;
}
