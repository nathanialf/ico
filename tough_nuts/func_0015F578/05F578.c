
extern char D_006322F0[];
extern char D_00282660[];
extern void func_001A6E28(char *p, int *self);
extern void func_00158960(int *self, int x);
struct U64
{
  long long v;
};
void func_0015F578(int *self)
{
  int *p;
  int *new_var3;
  volatile int new_var;
  char *new_var2;
  int *new_var5;
  int **new_var4;
  func_001A6E28(D_006322F0, self);
  new_var4 = &self;
  new_var5 = *new_var4;
  do
  {
    new_var3 = (int *) new_var5[0x15C / 4];
    new_var = ((struct U64 *) D_00282660)->v;
    p = new_var3;
    new_var2 = (char *) p;
    ((struct U64 *) (new_var2 + 0x1C0))->v = new_var;
    new_var2 = D_00282660 + 8;
    *((int *) (new_var2 + 0x1C8)) = *((int *) new_var2);
  }
  while (0);
  func_00158960(*new_var4, 0);
}
