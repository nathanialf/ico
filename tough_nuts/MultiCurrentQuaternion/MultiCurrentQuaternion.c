float MultiCurrentQuaternion(float x)
{
    float t;
    x += 50.0f;
    t = (float)(int)(x * D_00628CAC) * 200.0f;
    x -= t;
    if (x < 100.0f) {
        return x * D_00628CB0 - 0.5f;
    }
    return -(x - 100.0f) * D_00628CB4 + 0.5f;
}
