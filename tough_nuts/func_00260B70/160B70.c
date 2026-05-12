
float func_00260B70(float a, float b)
{
  union 
  {
    float f;
    int i;
  } ua;
  union 
  {
    float f;
    int i;
  } ur;
  union 
  {
    float f;
    int i;
  } ub;
 do { ua.f = a; ub.f = b; ur.i = (ua.i & 0x7FFFFFFF) | (ub.i & 0x80000000); } while (0);
  return ur.f;
}
