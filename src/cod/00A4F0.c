
extern char D_00275850[];
extern void func_00105F00(int *p, char *q);
extern void func_00243AD0(int *a, int *b, int *c);
void func_0010A4F0(int *self)
{
  int *p = (int *) self[0x15C / 4];
  int *p1 = (int *) (((char *) p) + 0x230);
  int *p2 = (int *) (((char *) p) + 0xA0);
  int ret;
  func_00105F00(p1, D_00275850);
  func_00243AD0((int *) (((char *) p) + 0x250), p2, p1);
  ret = -1;
  *((int *) (((char *) p2) + 0x180)) = ret;
  return ret;
}
