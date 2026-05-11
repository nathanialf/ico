
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
  int *new_var6;
  int *new_var3;
  int new_var8;
  int new_var10;
  volatile int new_var;
  int **new_var9;
  int *new_var11;
  char *new_var2;
  int *new_var5;
  int **new_var4;
  int new_var7;
  func_001A6E28(D_006322F0, new_var11);
  new_var8 = 0;
  new_var4 = &self;
  do
  {
    new_var5 = *new_var4;
    do
    {
      new_var3 = (int *) new_var5[0x15C / 4];
      p = &(*((struct U64 *) D_00282660)).v;
      ;
      do
      {
        do
        {
          p = new_var3;
          new_var2 = (char *) p;
        }
        while (new_var10 = new_var8);
        new_var7 = 8;
        new_var2 = D_00282660;
        ;
        new_var6 = (int *) (new_var2 + 0x1C8);
      }
      while (0);
      *new_var6 = *((int *) (new_var2 + new_var7));
    }
    while (new_var8);
    ((struct U64 *) ((new_var2 + new_var7) + 0x1C0))->v = *p;
    new_var11 = self;
  }
  while (0);
  new_var9 = &(*new_var4);
  func_00158960(*new_var9, 0);
}
