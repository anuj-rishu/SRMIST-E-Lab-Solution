#include <stdio.h>
#include <stdlib.h>

void printAns(int n, int *inv) {
    for (int x = 1; x <= n; x++)
        printf("%d\n", inv[inv[x]]);
}

int main() {
    int n,*arr,i,x,y;
    scanf("%d", &n);
    if (n > 10) {
        printf("Invaild.\n");
        return 0;
    }
    arr=(int *)malloc((n+1)*sizeof(int));
    (void)x; (void)y;
    int inv[25];
    for(i=1;i<=n;i++) {
        scanf("%d", &arr[i]);
        inv[arr[i]] = i;
    }
    printAns(n, inv);
    return 0;
}
