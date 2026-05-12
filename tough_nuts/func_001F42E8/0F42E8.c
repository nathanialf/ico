
extern char D_006124F8[];
float func_001F42E8(char *self)
{
  char *p = *((char **) ((*((char **) (self + 0x15C))) + 0x800));
  int idx = *((int *) p);
  int new_var;
  new_var = 0xC;
  return (float) (*((int *) ((D_006124F8 - (-(idx * 0x24))) + new_var)));
}
