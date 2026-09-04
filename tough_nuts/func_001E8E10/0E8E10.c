
extern char D_007097F0[];
extern void sceVu0CopyVector(char *p, int x);
void func_001E8E10(int x)
{
  char *p = D_007097F0;
  char *limit = p + 0xC00;
  do
  {
    if ((*((int *) p)) != 0)
    {
      char *callee = *((char **) (p + 0x14));
 do { if (callee != 0) { sceVu0CopyVector(callee + 0x40, x); } if (1) { } } while (0);
    }
    p += 0x18;
  }
  while (((int) p) < ((int) limit));
}
