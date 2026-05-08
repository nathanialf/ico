
int func_0017D0D0(void *a0, short a1)
{
  short *p;
  if (a0 == 0)
  {
    goto out;
  }
  p = *((short **) (((char *) a0) + 0x2C));
  if (p == 0)
  {
    out:
    return 0;

    goto out;
  }
  *((short *) (((char *) p) + 0x44)) = a1;
  return 1;
}
