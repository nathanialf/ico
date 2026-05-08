
extern volatile int D_00632C90;
extern volatile int D_00632C94;
extern volatile int D_00632C98;
extern volatile int D_00632C9C;
extern volatile int D_00632CA0;
extern volatile int D_00632CA4;
extern volatile int D_00633E58;
void func_001AA098(void)
{
  int new_var;
  D_00632CA0 = 0;
  *((volatile int *) 0x10000000) = 0;
  new_var = 0;
  D_00632C9C = new_var;
  new_var = new_var;
  D_00632C98 = new_var;
  D_00633E58 = new_var;
  D_00632C94 = new_var;
  D_00632C90 = new_var;
  D_00632CA4 = new_var;
}
