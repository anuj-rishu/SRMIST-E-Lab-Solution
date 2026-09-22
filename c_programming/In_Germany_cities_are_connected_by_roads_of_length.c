#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    if (n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    int *arr;
    arr=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) arr[i] = 0;
    for (i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        if (s >= 0 && s < n) arr[s] = 1;
    }
    int temp=0;
    for(i=0;i<n;i++) {
        int min_d = 1000;
        for (j = 0; j < n; j++) {
            if (arr[j]) {
                int d = abs(i - j);
                if (d < min_d) min_d = d;
            }
        }
        if (min_d > temp) temp = min_d;
    }
    printf("%d\n", temp);
    return 0;
}
