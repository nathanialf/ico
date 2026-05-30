extern int D_004C49A8[];
extern char D_00565060[];

void func_001D4E30(int target)
{
    int i;
    int (*data)[100] = (int (*)[100])D_00565060;
    for (i = 0; i <= 0x43D; i++) {
        if (data[i][77] == target) D_004C49A8[i] = 0;
    }
}
