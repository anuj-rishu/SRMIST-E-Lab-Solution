#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int n,k,*c,i;
    int a = 0;
    scanf("%d", &n);
    scanf("%d", &k);
    if(n>5) {
        printf("The value of 'n' exceeds the permissible range\n");
    } else {
        c=(int *)malloc(n*sizeof(int));
        for(i=0;i<n;i++)
            scanf("%d", &c[i]);
        qsort(c, n, sizeof(int), cmp);
        for(i=n-1;i>=0;i--)
            a += (1 + (n - 1 - i) / k) * c[i];
        printf("%d\n", a);
    }
    return 0;
}
