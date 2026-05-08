
extern int func_001BA668(void);
int func_001BA6B0(int *self)
{
  int x = ((int *) ((int *) self[0x15C / 4])[0x800 / 4])[0x8 / 4];
  int new_var;
  new_var = x;
  if ((new_var < 2) || (x = new_var >= 6))
  {
    func_001BA668();
    return 1;
  }
  return 0;
}
