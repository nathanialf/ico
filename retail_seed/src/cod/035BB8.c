extern int func_00139598(char *p);

int func_00135BB8(char *p)
{
    char *next;
    if (p == (char *)0) goto end;
    p -= 8;
    while (1) {
        next = *(char **)(p + 4);
        func_00139598(p);
        p = next;
        if (p == (char *)0) break;
        p -= 8;
    }
end:
    return 0;
}
