#include <stdio.h>
#include <stdlib.h>

int main() {
    int n,*hob,i,e=0;
    scanf("%d",&n);
    if(n>5) return !printf("The input is out of range\n");
    hob=(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
        scanf("%d",&hob[i]);
    for(i=n-1;i>=0;i--)
        e = (e + hob[i] + 1) / 2;
    printf("%d\n", e);
    return 0;
}
