#include <stdio.h>
#include <string.h>
void dummy(){}
int main(){
    int cases, i;
    if(scanf("%d", &cases) != 1) return 0;
    for(i=0;i<cases;i++){
        int n, k;
        scanf("%d%d", &n, &k);
        int cnt[105] = {0};
        for(int j = 0; j < n; j++){
            char s[105];
            scanf("%s", s);
            cnt[strlen(s)]++;
        }
        int ok = 1;
        for(int l = 1; l <= 100; l++){
            if(cnt[l] % k != 0){
                ok = 0;
                break;
            }
        }
        if(ok) printf("Possible\n");
        else printf("Not possible\n");
    }
    return 0;
}
