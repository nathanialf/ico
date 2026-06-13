/* rc2 seed for staffRollMain (common/src/staffroll.c).
   Externs needed (place above the function in the TU):
     extern float D_0062C1C4, D_0062C1C0, D_0062B45C, D_0062B460;
     extern int D_0062B474, D_0062B458, D_004B8C80[], D_0062C1C8, D_0062C1DC, D_0062C1CC, D_0062C1D8;
     extern unsigned char D_00700770[];
     extern void func_00260568(void *a0, int a1, int a2);
*/
void staffRollMain(int a0, float arg) {
    D_0062C1C4 = 0.0f;
    D_0062B474 = a0;
    D_0062B458 = 1;
    D_004B8C80[0] = 0x500;
    D_0062C1C0 = arg + arg;
    D_0062B45C = D_0062C1C4;
    D_0062C1C8 = 0;
    D_0062C1DC = 0;
    D_0062C1CC = 0;
    D_0062C1D8 = 0;
    D_0062B460 = D_0062C1C4;
    func_00260568(D_00700770, 0, 0x12C0);
}
