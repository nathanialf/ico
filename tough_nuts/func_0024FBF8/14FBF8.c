
extern int func_00100410(int a0);
extern int func_001002A0(int a, void (*p)(int), int v);
extern void func_00100440(int a);
extern void func_0024FBD0(int);
void func_0024FBF8(int a0)
{
  void (*handler)(int) = func_0024FBD0;
  int masked = a0 & 0xFFFF;
  int v;
 do { v = func_00100410(a0); } while (0);
  func_001002A0(masked, handler, v);
  return func_00100440(masked);
}
