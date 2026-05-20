
extern int D_002757D0[];
extern int D_0063283C;
extern int D_00631A10;
extern char D_004B2DC0[];
extern void func_0013A5B8(char *p, int *q, int x);
void func_0019FFA8(int a0_arg, unsigned char r, unsigned char g, unsigned char b, float f1, float f2)
{
  int new_var;
  int *p = D_002757D0;
  new_var = 0x80000000;
  *((int *) (((char *) p) + 0x4)) = a0_arg;
  D_0063283C = ((((int) g) << 8) | new_var) | ((((int) b) << 16) | ((int) r));
  p[0] = 1;
  D_00631A10 = 1;
  *((float *) (((char *) p) + 0xC)) = f1;
  *((float *) (((char *) p) + 0x10)) = f2;
  *(((char *) p) + 0x14) = r;
  *(((char *) p) + 0x15) = g;
  *(((char *) p) + 0x16) = b;
  func_0013A5B8(D_004B2DC0, (int *) p, 0);
}
