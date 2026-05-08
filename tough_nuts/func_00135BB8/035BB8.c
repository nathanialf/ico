
extern void func_00139598(void *p);
int func_00135BB8(void *a0)
{
  {
    void *p = ((char *) a0) - 8;
    for (;;)
    {
      void *next;
      p = ((char *) next) - 8;
      func_00139598(p);
      next = *((void **) (((char *) p) + 4));
      if (next == 0)
      {
        break;
      }
    }

  }
  return 0;
}
