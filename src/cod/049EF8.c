
extern unsigned short D_00565060[];
int func_00149EF8(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  int idx = *((int *) (((char *) p) + 0x4A0));
  unsigned short *new_var;
  new_var = D_00565060;
  return ((unsigned short *) (((char *) new_var) + (idx * 0x190)))[0x186 / 2] & 7;
}
