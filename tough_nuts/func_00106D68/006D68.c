
extern int D_00553BE0[];
extern float func_00168C18(int *a, int *b);
extern void func_001A6E28(int *a);
void func_00106D68(int *self)
{
  char *p;
  int *new_var2;
  char *new_var;
  float r = func_00168C18((int *) (((char *) self[0x15C / 4]) + 0x1D0), (int *) (((char *) self[0x15C / 4]) + 0x250));
  new_var = p + 0x254;
  *((float *) new_var) = r;
  new_var2 = D_00553BE0;
  func_001A6E28(new_var2);
}
