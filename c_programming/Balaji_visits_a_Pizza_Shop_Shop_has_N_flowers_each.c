#include <stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    if(n>5) return puts("You bought too much of pizzas:This offer not allowed for weekend") * 0;
    int a[10], cnt[20005] = {0};
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
        if(a[i] <= 10000) cnt[a[i]]++;
    }
    int ans = 0;
    for(int i=0;i<=10000;i++){
        if(cnt[i]){
            ans++;
            i += 4;
        }
    }
    printf("%d\n", ans);
    return 0;
}
