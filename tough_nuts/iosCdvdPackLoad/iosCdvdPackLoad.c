int iosCdvdPackLoad(int *self)
{
    unsigned char entry[0x20];
    const char *new_var;
    int count;
    int size;
    char *name;
    int n;

    iosCdvdLoad(self, &count, 4);
    if (count-- <= 0)
    {
        goto end;
    }
    name = (char *) self + 0x34;
loop:
    {
        iosCdvdLoad(self, entry, 0x20);
        new_var = D_00550D98;
        func_00261188((unsigned char *) name, new_var, (int) entry);
        cdvd_normpath((int) name);
        func_002614F8((int) &D_0027A8A8[D_0062A25C * 0x30], (unsigned char *) name);

        iosCdvdLoad(self, &size, 4);
        n = D_0062A25C;
        {
            int rounded = size / 0x800;
            *(int *) &D_0027A8A8[n * 0x30 - 8] = rounded + self[0x134 / 4];
        }
        iosCdvdLoad(self, &D_0027A8A8[n * 0x30 - 4], 4);
        D_0062A25C = D_0062A25C + 1;
    }
    if (count-- > 0)
    {
        goto loop;
    }
end:
    return 1;
}
