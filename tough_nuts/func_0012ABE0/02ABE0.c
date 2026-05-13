
extern char D_00674058[];
extern int D_00633C54;
void func_0012ABE0(int key, int val)
{
  char *base;
  int count = D_00633C54;
  int i = 0;
  if (count > 0)
  {
    do
    {
      int *entry = *((int **) (base + 0x280));
      if (entry[0x16] == key)
      {
        entry[0x14] = val;
        count = D_00633C54;
      }
      i++;
      base += 0x290;
    }
    while (i < count);
  }
  base = D_00674058;
}
