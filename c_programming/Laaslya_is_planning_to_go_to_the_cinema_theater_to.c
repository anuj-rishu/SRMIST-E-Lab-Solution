#include <stdio.h>

void dummy() {}

void tHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n > 1) tHanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Move disk %d from rod %c to rod %c\n", n, from_rod, to_rod);
    if (n > 1) tHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main() {
    int n;
    scanf("%d", &n);
    if (n < 1 || n > 1000) return printf("Invalid Input\n") * 0;
    tHanoi(n, 'A', 'C', 'B');
}
