
extern int D_005525C4[];
extern void func_00252488(int *self);
extern void func_002523A0(void);
void func_00251C28(int *self)
{
  int *p = (int *) self[0x40 / 4];
  p[0] = 0;
  p[1] = 0;
  p[2] = 0;
  self[0x8 / 4] = 0;
  p[0x80 / 4] = -1;
 do { } while (0);
  p[0xAC / 4] = 0;
  func_00252488(self);
  D_005525C4[0] = 0;
  func_002523A0();
}
