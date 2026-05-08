
extern char D_002E4D64[];
void func_00193F78(void)
{
  int new_var;
  new_var = 0x42;
  *((short *) (D_002E4D64 + new_var)) = 0;
  *((int *) (D_002E4D64 + 0x48)) = ((*((int *) (D_002E4D64 + 0x48))) | 0x200000) & (~0x40000);
}
