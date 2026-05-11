
extern int D_00632010;
extern char D_006185E8[];
extern int func_0013A0F8(int handle, int size, char *file, int line);
int func_001BBE50(int unused, void *obj)
{
  int buf = func_0013A0F8(D_00632010, 0xC, D_006185E8, 0x1B);
  int *p = *((int **) (((char *) obj) + 0x30));
  int new_var4;
  int *new_var2;
  int *new_var3;
  int new_var;
  new_var2 = p;
 do { new_var4 = (int) p; ; } while (0);
  *((int *) (buf + 4)) = 0;
  new_var3 = (int *) buf;
  *new_var2 = 0;
  *new_var3 = new_var4;
  *((int *) (buf + 8)) = 0;
  return buf;
}
