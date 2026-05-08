
extern int D_00632028;
extern char D_007097F0[];
extern int func_001E83F8(int x);
int func_001E8B68(int unused, void *p, int z)
{
  int idx;
  char *e;
  (void) unused;
  idx = func_001E83F8(D_00632028);
  if (idx != (-1))
  {
    e = &D_007097F0[idx * 0x18];
    *((int *) ((&D_007097F0[idx * 0x18]) + 0x10)) = z;
    *((int *) ((&D_007097F0[idx * 0x18]) + 0x8)) = 1;
    *((void **) ((&D_007097F0[idx * 0x18]) + 0xC)) = p;
  }
  return idx;
}
