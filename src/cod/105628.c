typedef struct Nd { int pad[2]; struct Nd *f8; struct Nd *fC; char pad2[0x40 - 16]; } Nd;
extern char D_004CAEC0[];
extern Nd D_004CC1E0[];
int func_00205628(int a0, int a1)
{
    int *ch = (int *)&D_004CAEC0[a0 * 0x34];
    Nd *node = &D_004CC1E0[a1];
    Nd *old;
    node->f8 = 0;
    old = (Nd *)ch[2];
    ch[2] = (int)node;
    node->fC = old->f8;
    old->f8 = node;
    return 0;
}
