int sum_diagonal(int a[][], int r, int c) {
    int sum = 0;
    int min = r < c ? r : c;
    for (int i = 0; i < min; i++) {
        sum += a[i][i];
    }
    return sum;
}