#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    while(t--){
        int n;
        if(scanf("%d", &n) != 1) break;
        if(n < 0 || n > 4){
            puts("Invalid");
            continue;
        }
        int a[10], b[10];
        int i;
        for(i=1;i<=n;i++){
            scanf("%d", &a[i]);
            b[i] = a[i] - i;
        }
        int max_len = 0;
        int dp[10];
        for(i = 1; i <= n; i++){
            if(b[i] < 0){
                dp[i] = 0;
                continue;
            }
            dp[i] = 1;
            for(int j = 1; j < i; j++){
                if(b[j] >= 0 && b[j] <= b[i] && dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1;
                }
            }
            if(dp[i] > max_len) max_len = dp[i];
        }
        printf("%d\n", n - max_len);
    }
    return 0;
}
