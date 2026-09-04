extern int D_0054ABD0[];
extern char D_006289D8[];
extern int D_0054ABF0[];
extern char D_0054BD90[];
extern int D_0054ABD0[];
extern char D_006289D8[];
extern int D_0054ABF0[];
extern char D_0054BD90[];

int sceCdSync(int a0)
{
  short new_var;
  if (a0 == 0)
  {
    if (D_0054ABD0[0] > 0)
    {
      scePrintf(D_006289D8);
    }
    new_var = 0x3C;
    goto test;
    body:
    sceCdDelayThread(new_var);

    test:
    if (D_0054ABF0[0] != 0)
    {
      goto body;
    }

    if (sceSifCheckStatRpc(D_0054BD90) != 0)
    {
      goto body;
    }
    return 0;
  }
  if (D_0054ABF0[0] != 0)
  {
    return 1;
  }
  if (sceSifCheckStatRpc(D_0054BD90))
  {
  }
  return 0;
  return 1;
}
