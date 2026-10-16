#include <stdio.h>
int temp[1000005];

int main() {
    int disk, size, i, x;
    scanf("%d", &disk);
    size = disk;
    for (i = 0; i < disk; i++) {
        scanf("%d", &x);
        temp[x] = 1;
        while (temp[size]) {
            printf("%d ", size);
            temp[size--] = 0;
        }
        puts("");
    }
    return 0;
}
