
extern char D_00565060[];
int func_001E4838(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  int idx = *((int *) (((char *) p) + 0x4A0));
  int new_var;
  new_var = 0x184;
  return (((unsigned int) (*((int *) ((D_00565060 + (idx * 0x190)) + new_var)))) >> 28) & 3;
}
