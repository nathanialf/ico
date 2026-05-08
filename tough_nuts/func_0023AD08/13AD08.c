
typedef struct 
{
  long long lo;
  long long hi;
} V16;
extern V16 D_0061C380;
extern int D_00631AE8;
extern void func_0017DF38(int, int, V16 *, int, float);
void func_0023AD08(volatile unsigned int x)
{
  V16 local = D_0061C380;
  V16 *new_var;
  (void) x;
  new_var = &local;
  func_0017DF38(D_00631AE8, 0, new_var, 0, 100.0f);
}
