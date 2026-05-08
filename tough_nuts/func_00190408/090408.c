
void func_00190408(int *dst, int *self)
{
  long long *new_var;
  int *p = (int *) ((int *) self[0x15C / 4])[0x800 / 4];
  *new_var = *((long long *) (((char *) p) + 0xA4));
  new_var = (long long *) dst;
  *((int *) (((char *) dst) + 8)) = *((int *) (((char *) p) + 0xAC));
}
