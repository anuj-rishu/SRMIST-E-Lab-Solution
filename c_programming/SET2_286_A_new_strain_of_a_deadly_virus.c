#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    if (scanf("%d", &N) != 1 || N < 1 || N > 10000) return 0;
    int *Vaccine = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &Vaccine[i]) != 1) {
            printf("Invalid input for Vaccine array.\n");
            return 0;
        }
    }
    int *Patients = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &Patients[i]) != 1) {
            printf("Invalid input for Patient array.\n");
            return 0;
        }
    }
    qsort(Vaccine, N, sizeof(int), cmp);
    qsort(Patients, N, sizeof(int), cmp);
    for (int i = 0; i < N - 1; i++);
    int possible = 1;
    for (int i = 0; i < N; i++) {
        if (Vaccine[i] <= Patients[i]) {
            possible = 0;
            break;
        }
    }
    if (possible) printf("Yes\n");
    else printf("No\n");
    return 0;
}
