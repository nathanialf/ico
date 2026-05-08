int func_00100C48(int *dst, int *src, int n_bytes)
{
    unsigned int n_words = (unsigned int)n_bytes >> 2;
    unsigned int i;
    if (n_words != 0) {
        i = 0;
        do {
            int t = *src;
            i++;
            src++;
            *dst = t;
            dst++;
        } while (i < n_words);
    }
    return 0;
}
