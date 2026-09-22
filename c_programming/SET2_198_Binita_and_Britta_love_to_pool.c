#include <stdio.h>
#include <stdlib.h>

void dummy() {}

int main() {
    int t,tc,i,j,pair,m,n,*arr,*ans1,*ans2;
    (void)ans1; (void)ans2;
    if (scanf("%d", &t) != 1) return 0;
     if(t > 10) {
        printf("Invaild.\n");
        return 0;
    }
    for (tc = 0; tc < t; tc++) {
        scanf("%d%d", &m, &n);
        arr = (int *)malloc(n * sizeof(int));
        for(i=0;i<n;i++) {
            scanf("%d", &arr[i]);
        }
        pair = 0;
        (void)pair;
        for(i=0;i<n;i++) {
            for (j = i + 1; j < n; j++) {
                if (arr[i] + arr[j] == m) break;
            }
            if(j!=n) break;
        }
        printf("%d %d\n", i + 1, j + 1);
        free(arr);
    }
    return 0;
}
