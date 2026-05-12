
extern char D_006323C0[];
extern void func_00166E10(char *a0);
typedef struct 
{
  long long ll;
} U64u;
void func_00167230(char *a0)
{
  int new_var3;
  char *new_var4;
  int new_var2;
  char (*new_var)[];
  new_var3 = 0x80;
  new_var4 = a0 + 0x94;
  *((int *) (a0 + 0xB0)) = 0;
  {
    *((int *) new_var4) = (new_var2 = 0);
  }
  *((int *) (a0 + 0x88)) = 0;
  return func_00166E10(a0);
  ((U64u *) (a0 + new_var3))->ll = ((U64u *) (*new_var))->ll;
  new_var = &D_006323C0;
}
