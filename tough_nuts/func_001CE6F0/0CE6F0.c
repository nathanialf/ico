
extern void func_001E3FC8(void *a0);
void func_001CE6F0(void *a0)
{
  int * volatile *pp = (int * volatile *) (((char *) a0) + 0x15C);
  *((int *) (((char *) (*pp)) + 0x2B0)) = 0;
 do { *((int *) (((char *) (*pp)) + 0x310)) = 0; } while (0);
  *((int *) (((char *) (*pp)) + 0x3B8)) = 0;
  *((int *) (((char *) (*pp)) + 0x3BC)) = 0;
  func_001E3FC8(a0);
}
