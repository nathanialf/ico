
extern char D_00275860[];
extern int D_00633634;
extern int D_00633638;
extern int func_0011C028(int x, char *p, int z, int w, float t);
void func_001EF9E0(void)
{
  char *new_var;
  unsigned long long new_var2;
  new_var2 = 0xFFFFFF80;
  D_00633634 = func_0011C028(0x10, D_00275860, new_var2, 0, 80.0f);
  new_var = D_00275860;
  D_00633638 = func_0011C028(0x10, new_var, new_var2, 0, 80.0f);
}
