
extern void func_0013CD30(void);
extern void func_0013CD70(void);
extern void func_0013D098(void);
extern int D_006321A8;
void func_0013CF38(int *self)
{
  void (*new_var3)(void);
  void *cd30 = (void *) func_0013CD30;
  void *new_var;
  int new_var2;
  new_var3 = &func_0013CD70;
  self[0] = (new_var2 = 0);
  if (cd30 == 0)
  {
    cd30 = (new_var = (void *) func_0013D098);
  }
  self[1] = (int) cd30;
  self[2] = (int) (*new_var3);
  self[3] = (int) (&D_006321A8);
}
