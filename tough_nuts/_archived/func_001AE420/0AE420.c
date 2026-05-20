
extern int *func_001ADED8(int a0, int a1);
void func_001AE420(int a0, int a1, int a2, int a3)
{
  int *new_var2;
  int *new_var3;
  char *new_var;
  int *p = func_001ADED8(a0, a3);
  char *new_var4;
  p = (int *) (((char *) p) + 0x34);
  new_var2 = p;
  new_var3 = p;
  new_var4 = (char *) new_var3;
  new_var = new_var4 + 0x30;
  *new_var2 = a2;
  *((int *) new_var) = a1;
}
