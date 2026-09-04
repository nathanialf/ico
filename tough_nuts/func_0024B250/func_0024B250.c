
typedef struct 
{
  char pad0[0x10];
  int f10;
  char pad14[0x8];
} PObjA8B8Ent;
extern PObjA8B8Ent D_007112D0[][4];
extern int scePadGetButtonMask(int a0);
int scePadInfoPressMode(int a0, int a1)
{
  int new_var2;
  int ret = 0;
  int new_var;
  if (D_007112D0[a0][new_var].f10 == 0)
  {
    new_var = a1;
    return ret;
  }
  new_var2 = a0;
  return scePadGetButtonMask(new_var2) == 0x3FFFF;
}
