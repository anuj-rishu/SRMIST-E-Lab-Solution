#include <stdio.h>

static int n,k,count;

int main() {
    scanf("%d %d",&n,&k);
    if(n>25) {
        printf("N should be between 1 and 25\n");
        return 0;
    }
    int i, arr[25];
    for(i=0;i<n;i++)
        arr[i]=i+1;
    for(int i=2;i<=k;i++)
        for(count=1;count<n;count++)
            arr[count]=(arr[count]+arr[count-1])%1000000007;
    printf("%d\n",arr[n-1]);
    return 0;
}
