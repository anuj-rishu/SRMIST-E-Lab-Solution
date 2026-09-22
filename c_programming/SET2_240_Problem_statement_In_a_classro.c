#include <stdio.h>
int main(){
    int t;
    scanf("%d", &t);
    while(t!= 0){
        t--;
        int n;
        scanf("%d", &n);
        int a[10];
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        if(n > 5){
            puts("Wrong Information: Provide Proper Details");
            break;
        } else {
            int min = 100, max = 0;
            for(int i = 0; i < n; i++){
                int cnt = 1;
                for(int j = i - 1; j >= 0 && a[j+1] - a[j] <= 2; j--) cnt++;
                for(int j = i + 1; j < n && a[j] - a[j-1] <= 2; j++) cnt++;
                if(cnt < min) min = cnt;
                if(cnt > max) max = cnt;
            }
            printf("%d %d\n", min, max);
        }
    }
    return 0;
}
