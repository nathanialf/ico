
void func_00149EA8(char *a0)
{
  unsigned long new_var;
  int * volatile *new_var2;
  int *p;
  p = *((int * volatile *) (a0 + 0x15C));
  p[0x544 / 4] = 1;
  new_var = 0x54C / 4;
  p = *((int * volatile *) (a0 + 0x15C));
  p[new_var] = 1;
  p = *((int * volatile *) (a0 + 0x15C));
 new_var2 = &(*((int * volatile *) (a0 + 0x15C))); do { p[0x548 / 4] = 1; ; } while (0);
  (*new_var2)[0x7C / 4] = 1;
}
