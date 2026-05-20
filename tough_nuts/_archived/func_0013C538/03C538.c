
typedef void (*func_0013C538_FnPtr)(int *p, int x);
void func_0013C538(int *self)
{
  func_0013C538_FnPtr fn = (func_0013C538_FnPtr) self[0x8 / 4];
  do
  {
    {
      int *p = (int *) self[0];
      while (p != 0)
      {
        ;
        fn((int *) ((int *) self[0])[0x34 / 4], self[0xC / 4]);
        p = (int *) p[0x34 / 4];
      }

    }
    self[0] = 0;
  }
  while (0);
}
