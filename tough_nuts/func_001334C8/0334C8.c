extern char D_006A5C80[];

int func_001334C8(void)
{
    char *p = D_006A5C80;
    char *limit = p + 0x834;
    int count = 0;
    do {
        char b = *p;
        int new_count = count + 1;
        p += 0x12C;
        if (b != 0) {
            count = new_count;
        }
    } while ((int)p < (int)limit);
    return count;
}
