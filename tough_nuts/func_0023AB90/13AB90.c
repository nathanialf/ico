
typedef struct 
{
  long long lo;
  long long hi;
} V16;
extern V16 D_0061C360;
extern int D_00631AE8;
extern void func_0017DF38(int, int, V16 *, int, float);
void func_0023AB90(volatile int x)
{
  V16 local = D_0061C360;
  (void) x;
  func_0017DF38(D_00631AE8, 0, &local, 0, 100.0f);
}
