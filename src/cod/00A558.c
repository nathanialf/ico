struct Pack32 { long long a, b, c, d; };

void func_0010A558(struct Pack32 *dst, struct Pack32 *src, int n)
{
    if (n <= 0) return;
    do {
        *dst = *src;
        n--;
        src++;
        dst++;
    } while (n != 0);
}
