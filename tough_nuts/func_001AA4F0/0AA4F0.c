
extern char D_00615B48[];
extern char D_006EE030[];
extern int D_00632C88[];
extern int D_00632C80;
extern void func_00264DF8(char *p, int *q, char *r, int *s);
extern int func_00247380(char *p, int *q);
void func_001AA4F0(int *self, int *other)
{
  int r;
  func_00264DF8(D_006EE030, D_00632C88, D_00615B48, self);
  r = func_00247380(D_006EE030, other);
  r = (r = 0);
  D_00632C80 = r;
}
