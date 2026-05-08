
extern void func_00263520(float *a, int *b);
extern void func_00263388(int a0, int a1, int a2, long long a3);
void func_00263FB0(float f12)
{
  int *new_var;
  int buf[8];
  *((float *) (((char *) buf) + 0x10)) = f12;
  new_var = buf;
 do { func_00263520((float *) (((char *) buf) + 0x10), buf); func_00263388(buf[0], new_var[1], buf[2], (long long) (((unsigned long long) ((unsigned int) buf[3])) << 30)); } while (0);
}
