
extern void func_00258470(int *self, int a1);
void func_00258418(int *self, int a1_param, int a2, int a3)
{
  int new_var;
  self[3] = (self[2] = a1_param);
  new_var = a2;
  self[9] = new_var + a3;
  self[10] = a3;
  *((long long *) self) = 0;
  self[4] = (new_var = 0);
  *((long long *) (((char *) self) + 0x18)) = 0;
  self[8] = new_var;
  func_00258470(self, 0);
}
