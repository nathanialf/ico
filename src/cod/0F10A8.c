
extern unsigned char D_0070D4D8[];
extern char D_0061A598[];
extern void func_001A6E28(char *p);
int func_001F10A8(int idx)
{
  int *entry;
  entry = ((char *) D_0070D4D8) - (-(idx * 0x18));
  if (((int *) entry)[0xC / 4] < 0)
  {
    func_001A6E28(D_0061A598);
    return 4;
  }
  return ((int *) (((char *) D_0070D4D8) + (idx * 0x18)))[0x8 / 4];
}
