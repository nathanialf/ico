char *strstr(char *a0, char *a1)
{
  int new_var2;
  char c = a0[0];
  char n0 = a1[0];
  char nj;
  char new_var3;
  char hj;
  char new_var;
  int j;
  if (c == 0)
  {
    return (n0 == 0) ? (a0) : ((char *) 0);
  }
  search:
  if (n0 == 0)
  {
    return a0;
  }

  new_var2 = 0;
  c = a0[new_var2];
  new_var = n0;
  if (new_var != c)
  {
    a0++;
    goto next;
  }
  j = 1;
  inner:
  nj = a1[j];

  if (nj == 0)
  {
    return a0;
  }
  hj = a0[j];
  if (nj == hj)
  {
    j++;
    goto inner;
  }
  j = 0;
  a0++;
  next:
  c = a0[new_var2];

  new_var3 = a1[new_var2];
  if (c != j)
  {
    n0 = new_var3;
    goto search;
  }
  return (char *) new_var2;
}
