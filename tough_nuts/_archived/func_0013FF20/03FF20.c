
extern int *D_00281A70[];
int *func_0013FF20(int target)
{
  int **arr = D_00281A70;
  int *new_var;
  int i;
  int *node;
  for (i = 0; i < 8; i++)
  {
    node = arr[i];
    new_var = node;
    if (1)
    {
    }
    while (new_var != 0)
    {
      if (node[0] == target)
      {
        return node;
      }
      node = (int *) node[0x10 / 4];
    }

  }

  return 0;
}
