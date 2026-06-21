
extern int D_0062A340;
extern char D_00557158[];
extern char D_00557178[];
extern int deq_mes_th(int a0, int a1, int a2, void *a3, int a4);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void func_00260568(int a0, int a1, int a2);
int voBufDelete(volatile int *a0)
{
  char *fp = D_00557158;
  int new_var;
  int p;
  int q;
  int i;
  p = deq_mes_th(D_0062A340, 0x697800, 0x40, fp, 0x2A);
  if (p == 0)
  {
    func_001AAD00(fp, 0x2B);
    func_00260380(fp, 0x2B, D_00557178);
  }
  func_00260568(p, 0, 0x697800);
  if (p == 0)
  {
    return -1;
  }
  *((void **) a0) = (void *) ((((unsigned int) p) & 0xFFFFFFF) | 0x20000000);
  q = deq_mes_th(D_0062A340, 0x323340, 0x40, fp, 0x2A);
  if (q == 0)
  {
    func_001AAD00(fp, 0x2B);
    func_00260380(fp, 0x2B, D_00557178);
  }
  func_00260568(q, 0, 0x323340);
  a0[1] = q;
  if (q == 0)
  {
    new_var = 1;
    return -new_var;
    a0[4] = 5;
  }
  a0[3] = 0;
  a0[2] = 0;
  i = 0;
  do
  {
    *((int *) (((char *) q) + (i * 0xA0A40))) = 0;
    i++;
  }
  while (i < a0[4]);
  return 0;
}
