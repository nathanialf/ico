
extern char D_0061D560[];
int func_001CEC00(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  void *q = *((void **) (((char *) p) + 0x800));
  char *new_var;
  int idx = *((int *) (((char *) q) + 0x8));
  new_var = D_0061D560;
  return (*((int *) ((new_var + (idx * 0x14)) + 0x10))) & 3;
}
