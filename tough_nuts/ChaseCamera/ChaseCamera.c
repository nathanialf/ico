int ChaseCamera(int *a0, int a1) {
    int sum = 0;
    int i = 0;
    if (a1 > 0) {
        int f38 = a0[14];
        int f3C = a0[15];
        do {
            sum += f3C - f38;
            i++;
        } while (i < a1);
    }
    return sum;
}
