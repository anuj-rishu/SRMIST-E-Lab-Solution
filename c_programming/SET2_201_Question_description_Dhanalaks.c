#include <stdio.h>
int main(){
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    if(n>5) return puts("Invalid input") * 0;
    int a[10];
    for(i = 0; i < n; i++) scanf("%d", &a[i]);
    int max = 0;
    for(i=0;i<(n-k+1);i++){
        int sum = 0;
        for (j=0;j<k;j++) sum += a[i + j];
        if(max<sum) max=sum;
    }
    printf("%d\n", max);
    return 0;
}
