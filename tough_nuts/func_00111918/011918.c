
extern char D_004C7710[];
void func_00111918(long a0, long a1)
{
  long * volatile *head = (long * volatile *) (D_004C7710 + 0x10);
  long *p = *head;
  *p = a1;
  *p = a0;
  p++;
  *head = p;
  p++;
  *head = p;
}
