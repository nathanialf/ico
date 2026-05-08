
extern void func_001F2320(void);
extern void *func_00203B40(void *fp, int prio);
void func_001F22E0(int *self)
{
  char *new_var;
  void *r = func_00203B40((void *) func_001F2320, 0x15);
  *self = 0;
  new_var = ((char *) r) + 0x20;
 do { *((int **) new_var) = self; } while (0);
}
