
extern int func_001E29E8(int a0, int a1, int a2);
int func_0015EF50(int a0)
{
  int *new_var;
  int *s0 = *((int **) (((char *) a0) + 0x164));
  unsigned int v0 = func_001E29E8(0, 0, (int) (((char *) s0) + 0x610));
 do { new_var = (int *) (((char *) s0) + 0x120); *new_var = v0; return (*((int *) (v0 + 0xC))) != 0; } while (0);
}
