
extern int func_00105F00(int a0, void *a1);
void func_0017E838(int a0, float f1, float f2, float f3)
{
  float local[4];
  if (1)
  {
    local[0] = f1;
 do { local[1] = f2; } while (0);
    local[2] = f3;
    *((int *) (&local[3])) = 0;
    func_00105F00((*((int *) (((char *) a0) + 0x15C))) + 0x670, local);
  }
}
