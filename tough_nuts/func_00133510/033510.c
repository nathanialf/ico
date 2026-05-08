
extern char D_00556AE8[];
extern int func_0024DAB8(int x, int y, int z, int *buf);
extern void func_001A6E28(char *p);
int func_00133510(int a0, int a1, int a2, int *out)
{
  int new_var;
  int buf;
  int v;
  *out = 0;
  v = func_0024DAB8(a2 >> 11, a1, 1, &buf);
  new_var = v << 11;
  if (buf != 0)
  {
    func_001A6E28(D_00556AE8);
    *out = 1;
  }
  return new_var;
}
