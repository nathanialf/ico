
extern char D_006A98B0[];
void func_00144208(int a0, float f12)
{
  char *new_var;
  char *entry;
  short id;
  unsigned short new_var2;
  entry = &D_006A98B0[(a0 & 0xFF) * 64];
  id = *((short *) (entry + 0x10));
  if (id < 0)
  {
    return;
  }
  ;
  new_var = entry + 0x18;
  if ((a0 >> 8) != (new_var2 = *((unsigned short *) entry)))
  {
    return;
  }
  *((float *) new_var) = f12;
}
