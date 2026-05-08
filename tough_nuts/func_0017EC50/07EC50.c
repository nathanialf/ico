
void func_0017EC50(void *a0, float f)
{
  long * volatile *pp = (long * volatile *) (((char *) a0) + 0x164);
  int new_var;
  long *p = *pp;
  char *new_var2;
  new_var2 = ((char *) p) + 0x20;
  new_var = 0x678;
  *((long *) new_var2) = (*((long *) new_var2)) | 0x100000;
 do { } while (0);
  {
    int **q = (int **) (*pp);
    int *r = *((int **) (((char *) q) + new_var));
    *((float *) (((char *) r) + 0x340)) = f;
  }
}
