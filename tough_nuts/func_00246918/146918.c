
extern void func_00101A40(int *self);
extern void func_00101A88(void);
int *func_00246918(int *self)
{
  int *p;
  func_00101A40(self);
  p = (int *) self[0xC / 4];
  if (((int *) self[0xC / 4]) != 0)
  {
    self[0x4 / 4] = 1;
    self[0xC / 4] = ((int *) self[0xC / 4])[0x3C / 4];
  }
  else
  {
  }
  func_00101A88();
  self[0x4 / 4] = 0;
  return p;
}
