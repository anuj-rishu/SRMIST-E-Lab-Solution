#include <stdio.h>
#include <string.h>
void dummy(){}
int main(){
    int t;
    if(scanf("%d", &t) != 1) return 0;
    while(t--){
        char s1[100005], s2[100005];
        scanf("%s%s", s1, s2);
        int f[26] = {0};
        for(int i = 0; s1[i]; i++){
            if(s1[i] >= 'a' && s1[i] <= 'z') f[s1[i] - 'a'] = 1;
        }
        int ok = 0;
        for(int i = 0; s2[i]; i++){
            if(s2[i] >= 'a' && s2[i] <= 'z' && f[s2[i] - 'a']){
                ok = 1;
                break;
            }
        }
        if(ok) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
