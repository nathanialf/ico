extern int func_0010EB60(float x);

int func_0010EC08(float f12, float f13)
{
    if (f12 < 0.0f) {
        int r = func_0010EB60(f13);
        return -(short)r;
    }
    return func_0010EB60(f13);
}
