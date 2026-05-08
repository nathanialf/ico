
extern int func_0024DA80(int a0);
extern int func_0024D7B0(void);
extern void func_0024A1E0(int a0);
void func_001331D8(int a0)
{
  int *s0 = (int *) a0;
  int v0;
 do { s0[0xC / 4] = 0; } while (0);
  v0 = func_0024DA80(a0);
  if (v0 == 0)
  {
    s0[0xC / 4] = func_0024D7B0();
  }
  return func_0024A1E0(s0[0x160 / 4]);
}
