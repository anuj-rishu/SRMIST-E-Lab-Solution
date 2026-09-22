#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int n,*sticks;
    if (scanf("%d", &n) != 1) return 0;
     if(n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    sticks=(int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &sticks[i]);
    int *p = sticks;
    for (int i = 1; i < n; i++) {
        int key = *(p + i);
        int j = i - 1;
        while(j>=0&&(*(p+j))>key) {
            *(p + j + 1) = *(p + j);
            j--;
        }
        *(p + j + 1) = key;
    }
    for (int i = n - 3; i >= 0; i--) {
        if ((long long)sticks[i] + sticks[i + 1] > sticks[i + 2]) {
            printf("%d %d %d\n", sticks[i], sticks[i + 1], sticks[i + 2]);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
